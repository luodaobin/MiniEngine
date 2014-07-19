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
#include <string>


using boost::asio::ip::tcp;
typedef int int32;
typedef short uint16;
typedef __int64 int64;

#pragma pack(push, 1)
struct System_Reward_Data
{
	int32 m_iRewardType; //ERewardItemType
	int32 m_iNumOrID;
	char m_szIGGID[21]; //玩家的IGGID
	char m_szTitle[96];
	char m_szContent[255];
};
enum
{
	_MSG_PUBLISH_AREWARD_TO_PLAER=6122,
};

struct  MsgHead
{
	uint16	usSize;
	uint16	usType;
};

struct MSG_PUBLISH_NEW_MARQUEE_DATA : public MsgHead
{

	System_Reward_Data m_Data;		// 邮件列表数据

	MSG_PUBLISH_NEW_MARQUEE_DATA ()
	{
		ZeroMemory( &m_Data, sizeof(m_Data));
		usSize = sizeof(*this);
		usType = _MSG_PUBLISH_AREWARD_TO_PLAER;
	}
};
#pragma pack(pop)

void SendAReward(std::string sPlayer, const char* szTitle,const char * szContent,int iType,int iIDOrNum)
{
	boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    tcp::resolver::query query("127.0.0.1", "5996");
    tcp::resolver::iterator iterator = resolver.resolve(query);

	
	tcp::socket socket(io_service);
    boost::asio::connect(socket, iterator);


	MSG_PUBLISH_NEW_MARQUEE_DATA msg;
	strncpy(msg.m_Data.m_szIGGID,sPlayer.c_str(),21);
	strncpy(msg.m_Data.m_szTitle,szTitle,96);
	strncpy(msg.m_Data.m_szContent,szContent,255);
	msg.m_Data.m_iRewardType=iType;
	msg.m_Data.m_iNumOrID=iIDOrNum;

    boost::asio::write(socket, boost::asio::buffer(&msg, sizeof(msg)));
	std::cout<<"Send A Reward "<<szTitle<<"  OK"<<std::endl;
}
int main(int argc, char* argv[])
{
  try
  {
	
	
	if(argc>=4)
	{
		std::string sPlayer=argv[1];
		int iType=0;
		if(argc>=5) iType=atoi(argv[4]);
		int iIDOrNum=0;
		if(argc>=6) iIDOrNum=atoi(argv[5]);

		SendAReward(sPlayer,argv[2],argv[3],iType,iIDOrNum);
	}
	else
	{
		printf("Usage : Reward [playerID] [title ][content] [rewardType] [IDorNum]\n");
	}
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
