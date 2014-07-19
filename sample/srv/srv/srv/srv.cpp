// srv.cpp: 主项目文件。

#include "stdafx.h"
//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp> 
#include <conio.h>

using boost::asio::ip::tcp;
class session;
class server
{
public:
	server(boost::asio::io_service& io_service, short port);

	void ConnectTo(const std::string & sPort);

private:
	void start_accept();

	void handle_accept(session* new_session, const boost::system::error_code& error);

	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;
	tcp::resolver resolver_;

	boost::thread m_thread;
	int m_iSessionCount;
};

//////////////////////////////////////////////////////////////////////////


class session
{
public:
	session(boost::asio::io_service& io_service)
		: socket_(io_service)
	{
	}

	tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{
		socket_.async_read_some(boost::asio::buffer(data_, max_length),
			boost::bind(&session::handle_read, this, boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
	}
	void SetServer(server * pServer)
	{
		m_pSever=pServer;
	}

private:
	void handle_read(const boost::system::error_code& error,
		size_t bytes_transferred)
	{
		if (!error)
		{
			std::string s(data_,bytes_transferred);
			if(s=="quit")
			{
				delete this;
				return;
			}
			if(s.substr(0,4)=="conn")//conn 234
			{
				std::string sPort=s.substr(5);
				std::cout<<"Connecting to port:"<<sPort<<" ..."<<std::endl;
				m_pSever->ConnectTo(sPort);
			}

			boost::asio::async_write(socket_,
				boost::asio::buffer(data_, bytes_transferred),
				boost::bind(&session::handle_write, this,
				boost::asio::placeholders::error));
		}
		else
		{
			std::cout<<"session::handle_read error! "<<error<<std::endl;
			delete this;
		}
	}

	void handle_write(const boost::system::error_code& error)
	{
		if (!error)
		{
			socket_.async_read_some(boost::asio::buffer(data_, max_length),
				boost::bind(&session::handle_read, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}
		else
		{
			std::cout<<"session::handle_write error! "<<error<<std::endl;
			delete this;
		}
	}

	tcp::socket socket_;
	enum { max_length = 1024 };
	char data_[max_length];
	server * m_pSever;


};



//////////////////////////////////////////////////////////////////////////

class chat_client
{
public:
	chat_client(boost::asio::io_service& io_service,tcp::resolver::iterator endpoint_iterator,int iIndex)
		: io_service_(io_service),
		socket_(io_service),
		m_iIndex(iIndex)

	{
		//socket_.set_option(boost::asio::socket_base::keep_alive(true));
		//socket_.io_control(boost::asio::socket_base::non_blocking_io(true));

		boost::asio::async_connect(socket_, endpoint_iterator,
			boost::bind(&chat_client::handle_connect, this,
			boost::asio::placeholders::error));
	}

private:

	void handle_connect(const boost::system::error_code& error)
	{
		if (!error)
		{
			std::cout<<m_iIndex<<":Connect OK!"<<std::endl;

			int iCounter=0;
			std::stringstream ss;
			ss<<iCounter;
			std::string sData=ss.str();
			boost::asio::async_write(
				socket_,
				boost::asio::buffer(sData.c_str(),sData.size()),
				boost::bind(&chat_client::handle_write,this,boost::asio::placeholders::error) );
		}
		else
		{
			std::cout<<m_iIndex<<": Connect Failed! "<<boost::system::system_error(error).what()<<std::endl;
			do_close();
		}
	}
	void handle_read(const boost::system::error_code& error, size_t bytes_transferred)
	{
		if (!error)
		{
			std::string s(data_,bytes_transferred);
			int iConter=atoi(s.c_str());
			if(iConter%5000==m_iIndex)
			{
				std::cout<<m_iIndex<<": Chat pip Read:"<<iConter<<std::endl;
			}

			iConter++;
			std::stringstream ss;
			ss<<iConter;
			std::string sData=ss.str();


			boost::asio::async_write(
				socket_,
				boost::asio::buffer(sData.c_str(), sData.size()),
				boost::bind(&chat_client::handle_write, this,boost::asio::placeholders::error));
		}
		else
		{
			do_close();
		}
	}

	void handle_write(const boost::system::error_code& error)
	{
		if (error)
		{
			do_close();
		}
		else
		{
			socket_.async_read_some(boost::asio::buffer(data_, max_length),
				boost::bind(&chat_client::handle_read, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));	
		}

	}

	void do_close()
	{
		socket_.close();
		std::cout<<m_iIndex<<": closed by host"<<std::endl;
		delete this;
	}

private:
	boost::asio::io_service& io_service_;
	tcp::socket socket_;
	enum { max_length = 1024 };
	char data_[max_length];
	int m_iIndex;
};

//////////////////////////////////////////////////////////////////////////

server::server(boost::asio::io_service& io_service, short port)
:io_service_(io_service),
acceptor_(io_service),
resolver_(io_service)
{

	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
	acceptor_.open(endpoint.protocol());
	//	acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	//	acceptor_.set_option(boost::asio::socket_base::enable_connection_aborted(true));
	//	acceptor_.set_option(boost::asio::socket_base::keep_alive(true));

	acceptor_.io_control(boost::asio::socket_base::non_blocking_io(true));

	acceptor_.bind(endpoint);
	acceptor_.listen(5000);

	m_iSessionCount=0;

	start_accept();
}

void server::ConnectTo(const std::string& sPort)
{
	tcp::resolver::query query("127.0.0.1", sPort);
	tcp::resolver::iterator iterator = resolver_.resolve(query);

	for(int ii=0;ii<5000;ii++)
	{
		chat_client* pNewChatClient = new chat_client(io_service_,iterator,ii);
	}
}

void server::start_accept()
{

	session* new_session = new session(io_service_);
	new_session->SetServer(this);
	acceptor_.async_accept(new_session->socket(),
		boost::bind(&server::handle_accept, this, new_session,
		boost::asio::placeholders::error));

}

void server::handle_accept(session* new_session,
						   const boost::system::error_code& error)
{

	if (!error)
	{
		start_accept();
		m_iSessionCount++;
		std::cout<<"new session start at "<<m_iSessionCount<<std::endl;
		new_session->start();
	}
	else
	{
		std::cout<<"new session failed! "<<error<<std::endl;
		delete new_session;
	}


}


int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: async_tcp_echo_server <port>\n";
			return 1;
		}

		boost::asio::io_service io_service;

		using namespace std; // For atoi.
		server s(io_service, atoi(argv[1]));

		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	
	return 0;
}