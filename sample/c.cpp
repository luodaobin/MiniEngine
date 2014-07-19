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
struct System_Mail_Data
{
	int32 m_iMailID;
	int32 m_iLan;
	int32 m_iSendTime;
	char m_szTitle[128];
	char m_szContent[1280];
};

enum
{
	_MSG_NOTIFY_PUBLISH_NEW_ACTIVITY=5051,
};

struct  MsgHead
{
	uint16	usSize;
	uint16	usType;
};

struct MSG_NOTIFY_PUBLISH_NEW_ACTIVITY : public MsgHead
{
	MSG_NOTIFY_PUBLISH_NEW_ACTIVITY()
	{
		usSize = sizeof(*this);
		usType = _MSG_NOTIFY_PUBLISH_NEW_ACTIVITY;
	}
};
#pragma pack(pop)

void SendAMail()
{
	boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    tcp::resolver::query query("127.0.0.1", "5996");
    tcp::resolver::iterator iterator = resolver.resolve(query);

	
	tcp::socket socket(io_service);
    boost::asio::connect(socket, iterator);


	MSG_NOTIFY_PUBLISH_NEW_ACTIVITY msg;
	

    boost::asio::write(socket, boost::asio::buffer(&msg, sizeof(msg)));
	std::cout<<"Notify OK"<<std::endl;
}
int main(int argc, char* argv[])
{
	SendAMail();
	return 0;
}
