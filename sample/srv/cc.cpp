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
#include "md5.h"

using boost::asio::ip::tcp;

std::string g_sMd5;
int			g_iLen=0;

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
	int iStartTime=time(0);
	while(true)
	{
		iLoop++;
		char buf[20]={0};
		sprintf(buf,"%d",iLoop);
		std::string sMsg=buf;
		boost::asio::write(socket, boost::asio::buffer(sMsg.c_str(), sMsg.size()));

		
		char *reply=new char[g_iLen];
		int iStart=::time(0);
		int iReceiveLen=0;
		for(int ii=0;ii<1000;ii++)
		{
			size_t reply_length = boost::asio::read(socket, boost::asio::buffer(reply, g_iLen));
			if(reply_length!=g_iLen)
			{
				std::cout<<"Receive Len="<<reply_length<<" should be"<<g_iLen<<std::endl;
			}
			else
			{
				std::string sMd5=md5(std::string(reply,g_iLen));
				if(sMd5!=g_sMd5)
				{
					std::cout<<"Data trans Error!"<<sMd5<<" != "<<g_sMd5<<std::endl;
				}
			}
			iReceiveLen+=reply_length;
		}
		int iTimeSpan=::time(0)-iStart;
		std::cout<<"Run Receive 10000 times Over!"<<std::endl;

		std::cout<<"total received "<<iReceiveLen<<" Bytes In "<<iTimeSpan<<" sec "<<(iReceiveLen/iTimeSpan)*1.f/1024/1024<<"MB per sec"<<std::endl;
		//boost::this_thread::sleep(boost::posix_time::milliseconds( 1 ));
	}
}


int main(int argc, char* argv[])
{
	
	std::string sData="1234567890-=qwertyuuiiopasdgfghhjjkl;'zxczvxcbvcnbvbmnbmbvm,./QWEQWEQWEASSDF,NVNKJSDHFDSMCV,BMIOILM;LVMPOPOKD098759871987273924979!!@#$%^&*())1234567890-=qwertyuuiiopasdgfghhjjkl;'";
	std::stringstream ss;
	for(int ii=0;ii<1000;ii++)
	{
		ss<<sData;
	}
	std::string sRaw=ss.str();
	g_sMd5=md5(sRaw);
	g_iLen=sRaw.size();
	std::cout<<"Data Length:"<<g_iLen<<"  "<<g_sMd5<<std::endl;
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
		for(int ii=0;ii<1;ii++)
		{
			vThreads.push_back(new boost::thread(boost::bind(&DoWork,iterator,ii)));
		}
		for(int ii=0;ii<1;ii++)
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

