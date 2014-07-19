// cc.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

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
#include <conio.h>
#include <boost/thread/thread.hpp> 

using boost::asio::ip::tcp;

boost::asio::io_service io_service;
static void DoWork(tcp::resolver::iterator iterator,int iNum)
{
	tcp::socket socket(io_service);
	boost::system::error_code ec;
	boost::asio::connect(socket, iterator,ec);
	if(ec)
	{
		std::cout<<"Connect Failed! "<<boost::system::system_error(ec).what()<<std::endl;
		return;
	}
	boost::this_thread::sleep(boost::posix_time::milliseconds( 1000 ));
	int iLoop=0;
	while(true)
	{
		iLoop++;
		char buf[20]={0};
		sprintf(buf,"%d",iNum);
		std::string sMsg=buf;
		boost::asio::write(socket, boost::asio::buffer(sMsg.c_str(), sMsg.size()));

		char reply[20]={0};
		size_t reply_length = boost::asio::read(socket, boost::asio::buffer(reply, sMsg.size()));
		if(iNum==999&& iLoop%100==0)
		{
			std::cout<<"Reply is :"<<reply<<" On Loop"<< iLoop<<std::endl;
		}
		//boost::this_thread::sleep(boost::posix_time::milliseconds( 1 ));
	}
}


int main(int argc, char* argv[])
{
	if(argc<2)
	{
		printf("useage: cc.exe [port]");
		return 0;
	}

	try
	{


		std::cout<<"Max ThreadNum:"<<boost::thread::hardware_concurrency()<<std::endl;
		getch();

		tcp::resolver resolver(io_service);
		tcp::resolver::query query("127.0.0.1", argv[1]);
		tcp::resolver::iterator iterator = resolver.resolve(query);


		std::vector<boost::thread*> vThreads;
		for(int ii=0;ii<1000;ii++)
		{
			vThreads.push_back(new boost::thread(boost::bind(&DoWork,iterator,ii)));
		}
		for(int ii=0;ii<1000;ii++)
		{
			vThreads[ii]->join();
			delete vThreads[ii];
		}
		//boost::this_thread::sleep(boost::posix_time::seconds(30));
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
