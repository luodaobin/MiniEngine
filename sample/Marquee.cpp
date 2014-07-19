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
typedef int int32;
typedef short uint16;

#pragma pack(push, 1)
struct System_Marquee_Data
{
	int32 m_iLan;
	int32 m_iRepeatCount;
	char m_szContent[128];
};

enum
{
	_MSG_PUBLISH_NEW_MARQUEE=6119,
};

struct  MsgHead
{
	uint16	usSize;
	uint16	usType;
};

struct MSG_PUBLISH_NEW_MARQUEE_DATA : public MsgHead
{

	System_Marquee_Data m_Data;		// 邮件列表数据

	MSG_PUBLISH_NEW_MARQUEE_DATA ()
	{
		ZeroMemory( &m_Data, sizeof(m_Data));
		usSize = sizeof(*this);
		usType = _MSG_PUBLISH_NEW_MARQUEE;
	}
};
#pragma pack(pop)

void SendMarquee(const char * szContent,int iLan,int iRepeat)
{
	boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    tcp::resolver::query query("63.251.49.111", "5996");
    tcp::resolver::iterator iterator = resolver.resolve(query);

	
	tcp::socket socket(io_service);
    boost::asio::connect(socket, iterator);


	MSG_PUBLISH_NEW_MARQUEE_DATA msg;
	msg.m_Data.m_iLan=iLan;
	msg.m_Data.m_iRepeatCount=iRepeat;
	strncpy(msg.m_Data.m_szContent,szContent,128);

    boost::asio::write(socket, boost::asio::buffer(&msg, sizeof(msg)));
	std::cout<<"Send Marque "<<szContent<<"  OK"<<std::endl;
}
int main(int argc, char* argv[])
{
  try
  {
	
	int iRepeat=1;
	int iLan=1;
	if(argc>=4)
	{
		iRepeat= atoi(argv[3]);
	}
	if(argc>=3)
	{
		iLan= atoi(argv[2]);
	}
	if(argc>=2)
	{
		
		SendMarquee(argv[1],iLan,iRepeat);
		return 0;
	}
	printf("Usage : Marquee [content] [iLan] [iRepeatCount]\n");
	
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
