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
	_MSG_PUBLISH_NEW_MAIL_DATA=5033,
};

struct  MsgHead
{
	uint16	usSize;
	uint16	usType;
};

struct MSG_PUBLISH_NEW_MAIL_DATA : public MsgHead
{

	System_Mail_Data m_MailData;		// 邮件列表数据

	MSG_PUBLISH_NEW_MAIL_DATA()
	{
		ZeroMemory( &m_MailData, sizeof(m_MailData));
		usSize = sizeof(*this);
		usType = _MSG_PUBLISH_NEW_MAIL_DATA;
	}
};
#pragma pack(pop)

void SendAMail(int iMailID)
{
	boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    tcp::resolver::query query("127.0.0.1", "5996");
    tcp::resolver::iterator iterator = resolver.resolve(query);

	
	tcp::socket socket(io_service);
    boost::asio::connect(socket, iterator);


	MSG_PUBLISH_NEW_MAIL_DATA msg;
	msg.m_MailData.m_iMailID=iMailID;
	msg.m_MailData.m_iLan=0;

	std::stringstream ss;
	ss<<"Title Hello world "<<iMailID;
	strcpy(msg.m_MailData.m_szTitle,ss.str().c_str());
	ss.clear();
	ss<<"Mail content ......."<<iMailID<<".......";
	strcpy(msg.m_MailData.m_szContent,ss.str().c_str());


    boost::asio::write(socket, boost::asio::buffer(&msg, sizeof(msg)));
	std::cout<<"Send mail "<<iMailID<<"  OK"<<std::endl;
}
int main(int argc, char* argv[])
{
	if(argc<2)
	{
		printf("useage: mm.exe MailID1 [MailID2]\n");
		return 0;
	}
  try
  {
	
	if(argc==2)
	{
		int iMailID=::atoi(argv[1]);
		SendAMail(iMailID);
		return 0;
	}
	if(argc==3)
	{

		int min=::atoi(argv[1]);
		int max=::atoi(argv[2]);
		std::cout<<"Sending "<<max-min+1<<" mails"<<std::endl;
		for(int ii=min;ii<=max;ii++)
		{
			SendAMail(ii);
		}
		return 0;
	}
	
/////read---------------------------------

	
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
