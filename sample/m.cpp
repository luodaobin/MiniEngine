//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <fstream>
#include <boost/array.hpp>
#include <boost/asio.hpp>


using boost::asio::ip::tcp;

struct Msg
{
	unsigned short size;
	unsigned short id;
	bool bAuto;
	bool bAuto2;
};

int main(int argc, char* argv[])
{
  std::cout<<sizeof(Msg)<<std::endl;
  try
  {
  


	boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    tcp::resolver::query query("192.168.23.22", "6000");
    tcp::resolver::iterator iterator = resolver.resolve(query);

	
	tcp::socket socket(io_service);
    boost::asio::connect(socket, iterator);


	Msg msg;
	msg.size=sizeof(msg);
	msg.id=3005;
	msg.bAuto=true;
	msg.bAuto2=true;

    boost::asio::write(socket, boost::asio::buffer(&msg, sizeof(msg)));

/////read---------------------------------
	std::string sResultAll;
	
	unsigned short size=0;
    boost::asio::read(socket, boost::asio::buffer(&size, sizeof(size)));
	std::cout<<"ret size:"<<size<<std::endl;
	
	unsigned short type=0;
	boost::asio::read(socket, boost::asio::buffer(&type, sizeof(type)));
	std::cout<<"ret type:"<<type<<std::endl;

	unsigned short iMsgLen=0;
	unsigned short iSequeLen=0;
	boost::asio::read(socket, boost::asio::buffer(&iMsgLen, sizeof(iMsgLen)));
	
	std::cout<<"iMsgLen:"<<iMsgLen<<std::endl;
	char * pMsg=new char[iMsgLen+1];
	boost::asio::read(socket, boost::asio::buffer(pMsg, iMsgLen));
	pMsg[iMsgLen]=0;

	boost::asio::read(socket, boost::asio::buffer(&iSequeLen, sizeof(iSequeLen)));
	std::cout<<"iSequeLen:"<<iSequeLen<<std::endl;
	
	
	std::cout<<pMsg;
	std::string s(pMsg,iMsgLen);
	sResultAll+=s;

	std::cout<<sResultAll<<std::endl;

///----
	while (true)
	{
	
		unsigned short size=0;
		boost::asio::read(socket, boost::asio::buffer(&size, sizeof(size)));
		std::cout<<"ret size:"<<size<<std::endl;
		
		unsigned short type=0;
		boost::asio::read(socket, boost::asio::buffer(&type, sizeof(type)));
		std::cout<<"ret type:"<<type<<std::endl;
		

		if(type==3003) break;

		unsigned short iMsgLen=0;
		boost::asio::read(socket, boost::asio::buffer(&iMsgLen, sizeof(iMsgLen)));
		std::cout<<"iMsgLen:"<<iMsgLen<<std::endl;

		char * pMsg=new char[iMsgLen+1];
		boost::asio::read(socket, boost::asio::buffer(pMsg, iMsgLen));
		pMsg[iMsgLen]=0;

		
		std::string s(pMsg,iMsgLen);
		std::cout<<s<<std::endl;

		sResultAll+=s;

	}

	std::ofstream of("log.txt");
	of<<sResultAll;
	of.close();

	
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}