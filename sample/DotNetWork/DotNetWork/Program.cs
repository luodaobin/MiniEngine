using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Net;
using System.Net.Sockets;
using System.IO;
namespace DotNetWork
{
    class ClientConnection
    {
        private TcpClient m_TcpClient;
        private NetworkStream m_ClientStream;
        private String m_sConnectionDesc;
        private Int32 m_iCount = 0;
        internal ClientConnection(TcpClient client)
        {
            m_TcpClient = client;
            m_sConnectionDesc = m_TcpClient.Client.RemoteEndPoint.ToString();
            //m_ContentDA = new ContentDataAccess();
            m_ClientStream = m_TcpClient.GetStream();
            BeginRead();
        }

        private void BeginRead()
        {

            byte[] buffer = new byte[4096];

            try
            {
                m_ClientStream.BeginRead(buffer, 0, 4096, ReadComplete, buffer);
            }
            catch (IOException)
            {
                Console.WriteLine(string.Format("BeginRead: Socket Closed"));
            }
        }
        
        private void ReadComplete(IAsyncResult iar)
        {
          //  Console.WriteLine(String.Format("ReadComplete Thread id={0}", Thread.CurrentThread.ManagedThreadId));
            try
            {
                byte[] buffer = (byte[])iar.AsyncState;
                int iBytesAvailable = m_ClientStream.EndRead(iar);

                if (0 == iBytesAvailable)
                {
                    /// - Client socket has been closed
                    Console.WriteLine("ReadComplete:BytesAvailable==0 Conection is broken!");
                    return;
                }
                else
                {
                    BeginRead();

                    m_iCount++;

                    String sValue = Encoding.UTF8.GetString(buffer, 0, iBytesAvailable);
                    if(m_iCount%1000==0)
                    {
                      //  Console.WriteLine(String.Format("FromClient:{0} len={1} on Count{2} On Thread{3}", sValue, iBytesAvailable, m_iCount, Thread.CurrentThread.ManagedThreadId));
                    }
                    

                    IAsyncResult ar = m_ClientStream.BeginWrite(buffer, 0, iBytesAvailable, WriteCompleted, null);
                  //  if (!ar.AsyncWaitHandle.WaitOne())
                   // {
                     //   Console.WriteLine("NetworkStream Async Write Failed!");
                    //}
                }
               
            }
            catch (System.Exception)
            {
                Console.WriteLine("ReadComplete Exception,Client disconnected!");
            }
        }

        private void WriteCompleted(IAsyncResult iar)
        {
            m_ClientStream.EndWrite(iar);
        }

    }
    class Server
    {
        private Thread m_ListenThread;
        private TcpListener m_Listener;
        private List<ClientConnection> m_clientList;

        public void ServerStartUp(String sIP, Int32 iPort)
        {
            m_clientList = new List<ClientConnection>();
            IPAddress lisenIP = IPAddress.Any;
            if (sIP.Length > 0)
            {
                lisenIP = IPAddress.Parse(sIP);
            }
            m_Listener = new TcpListener(lisenIP, iPort);
            m_ListenThread = new Thread(new ThreadStart(ListenForClients));
            m_ListenThread.Start();
        }

        private void ListenForClients()
        {
            Console.WriteLine(String.Format("Listen Thread id={0}", Thread.CurrentThread.ManagedThreadId));
            try
            {
                m_Listener.Start();
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ListentForClients - Start failed");
            }

            try
            {
                while (true)
                {
                    //blocks until a client has connected to the server
                    TcpClient client = m_Listener.AcceptTcpClient();

                    ClientConnection clientSocket = new ClientConnection(client);
                    m_clientList.Add(clientSocket);
                    if(m_clientList.Count %100 ==0)
                    {
                        Console.WriteLine(String.Format("New Session Start At{0}", m_clientList.Count));
                    }
                }
            }
            catch (System.Exception e)
            {
                Console.WriteLine("ListenForClients has exited");
            }
        }

    }
    class Program
    {
        static void Main(string[] args)
        {
            Server server=new Server();
            server.ServerStartUp("127.0.0.1", 6000);
            Console.WriteLine(String.Format("Main Thread id={0}", Thread.CurrentThread.ManagedThreadId));
            while(true)
            {
                Thread.Sleep(1);
            }
        }
    }
}
