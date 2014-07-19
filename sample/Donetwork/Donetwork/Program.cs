using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Donetwork
{
    using System;
    using System.Net;
    using System.Net.Sockets;
    using System.Text;
    using System.Threading;

    // State object for reading client data asynchronously
    public class StateObject
    {
        // Client  socket.
        public Socket workSocket = null;
        // Size of receive buffer.
        public const int BufferSize = 1024;
        // Receive buffer.
        public byte[] buffer = new byte[BufferSize];
        // Received data string.
        public StringBuilder sb = new StringBuilder();

        public Int32 iIndex = 0;
        public Int32 iReceiveCount = 0;
    }

    public class AsynchronousSocketListener
    {
        // Thread signal.
        public static ManualResetEvent allDone = new ManualResetEvent(false);
        private static Int32 iIndex = 0;

        public AsynchronousSocketListener()
        {
        }

        public static void StartListening()
        {
            // Data buffer for incoming data.
            byte[] bytes = new Byte[1024];

            // Establish the local endpoint for the socket.
            // The DNS name of the computer
            // running the listener is "host.contoso.com".
            //IPHostEntry ipHostInfo = Dns.Resolve(Dns.GetHostName());
            IPAddress ipAddress = IPAddress.Parse("127.0.0.1");

            IPEndPoint localEndPoint = new IPEndPoint(ipAddress, 6000);

            // Create a TCP/IP socket.
            Socket listener = new Socket(AddressFamily.InterNetwork,
                SocketType.Stream, ProtocolType.Tcp);

            // Bind the socket to the local endpoint and listen for incoming connections.
            try
            {
                listener.Bind(localEndPoint);
                listener.Listen(100);
                Console.WriteLine("Waiting for a connection");
                while (true)
                {
                    StateObject state = new StateObject();
                    Socket handler = listener.Accept();
                    handler.Blocking = false;
                    state.workSocket = handler;
                    iIndex++;
                    state.iIndex = iIndex;
                    handler.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0, new AsyncCallback(ReadCallback), state);

                    if (iIndex % 100 == 0)
                    {
                        Console.WriteLine("Accept {0} clients", iIndex);
                    }

                    /*
                    // Set the event to nonsignaled state.
                    allDone.Reset();

                    // Start an asynchronous socket to listen for connections.
                   listener.BeginAccept(
                        new AsyncCallback(AcceptCallback),
                        listener);

                    // Wait until a connection is made before continuing.
                    allDone.WaitOne();
                     */
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }

            Console.WriteLine("\nPress ENTER to continue");
            Console.Read();
        }

        public static void AcceptCallback(IAsyncResult ar)
        {
            // Signal the main thread to continue.

            // Get the socket that handles the client request.
            Socket listener = (Socket)ar.AsyncState;
            Socket handler = listener.EndAccept(ar);
            allDone.Set();
           
            // Create the state object.
            StateObject state = new StateObject();
            state.workSocket = handler;
            iIndex++;
            state.iIndex=iIndex;
            handler.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0, new AsyncCallback(ReadCallback), state);

            if(iIndex % 100==0)
            {
                Console.WriteLine("Accept {0} clients", iIndex);
            }
            
        }

        public static void ReadCallback(IAsyncResult ar)
        {
            String content = String.Empty;

            // Retrieve the state object and the handler socket
            // from the asynchronous state object.
            StateObject state = (StateObject)ar.AsyncState;
            Socket handler = state.workSocket;

            
            // Read data from the client socket. 
            SocketError eError;
            int bytesRead = handler.EndReceive(ar, out eError);
            if (eError != SocketError.Success)
            {
                Console.WriteLine("ReadCallback:Thread {0}:Error:{1}", Thread.CurrentThread.ManagedThreadId,eError.ToString());
            }

           

            if (bytesRead > 0)
            {
                // There  might be more data, so store the data received so far.
                state.sb.Remove(0, state.sb.Length);
                state.sb.Append(Encoding.ASCII.GetString(state.buffer, 0, bytesRead));
                state.iReceiveCount++;

                handler.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0, new AsyncCallback(ReadCallback), state);

                content = state.sb.ToString();
                
//                 if (content.IndexOf("<EOF>") > -1)
//                 {
//                    Console.WriteLine("Read {0} bytes from socket. \n Data : {1}", content.Length, content);
//                     
//                 }
              //  if(state.iIndex==1 && state.iReceiveCount%100==0)
                //{
                  //  Console.WriteLine("Read {0} bytes from socket.  Data : {1} On Thread:{2}", content.Length, content,Thread.CurrentThread.ManagedThreadId);
                //}
               
               // Send(handler, content);
                Console.WriteLine("Sending begin...");

                String sData = "1234567890-=qwertyuuiiopasdgfghhjjkl;'zxczvxcbvcnbvbmnbmbvm,./QWEQWEQWEASSDF,NVNKJSDHFDSMCV,BMIOILM;LVMPOPOKD098759871987273924979!!@#$%^&*())1234567890-=qwertyuuiiopasdgfghhjjkl;'";
                StringBuilder sb = new StringBuilder();
                for (Int32 ii = 0; ii < 1000; ii++)
                {
                    sb.Append(sData);
                }
                String sRaw = sb.ToString();
                for (Int32 ii = 0; ii < 1000; ii++)
                {
                    
                    Send(handler, sRaw,ii);
                }
                Console.WriteLine("...Sending End");
                  
                
                
               
            }
        }

        private static void Send(Socket handler, String data,int ii)
        {
            // Convert the string data to byte data using ASCII encoding.
            byte[] byteData = Encoding.ASCII.GetBytes(data);

            // Begin sending the data to the remote device.
            try
            {
                if(handler.Connected)     handler.BeginSend(byteData, 0, byteData.Length, 0, new AsyncCallback(SendCallback), handler);
            }
            catch (SocketException ex)
           {
                Console.WriteLine("------private static void Send [{0}]"+ex.ErrorCode.ToString(),ii);
           }
            
                        
        }



        private static void SendCallback(IAsyncResult ar)
        {
            try
            {
                // Retrieve the socket from the state object.
                Socket handler = (Socket)ar.AsyncState;

                // Complete sending the data to the remote device.
                SocketError eError;
                int bytesSent = handler.EndSend(ar,out eError);
                if(eError!=SocketError.Success)
                {
                    String sError = String.Format("SendCallback Thread {0}:Exception:{1}", Thread.CurrentThread.ManagedThreadId, eError.ToString());
                    Console.WriteLine(sError);
                }
                //Console.WriteLine("Sent {0} bytes to client.", bytesSent);
                //handler.Shutdown(SocketShutdown.Both);
                //handler.Close();
            }

            catch (Exception e)
            {
                String sError = String.Format("Thread {0}:Exception:{1}", Thread.CurrentThread.ManagedThreadId, e.ToString());
                Console.WriteLine(sError);
            }
        }

        public static int Main(String[] args)
        {
            StartListening();
            return 0;
        }

    }
}
