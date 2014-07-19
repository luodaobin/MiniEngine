#include "stdafx.h"
#include "AAbb.h"
#include "InstanceTouch.h"
DECL_INSTANCE_TOUCH(ETouch_AAbb);

struct  AAbbDefReflectionRegister
{
	AAbbDefReflectionRegister()
	{
		REGISTER_REFLECTION_MEMBER(AAbb,m_iID,INVALID_ID).Editor_SetAsPrimaryKey();
		REGISTER_REFLECTION_MEMBER(AAbb,m_sDisplayName,std::string("DefaultName")).Editor_SetAsDisplayName();
		
		GlobalDefManager::Instance().RegisterDefManger(&AAbbManager::Instance());

	}
}___AAbbDefReflectionRegister;

rewrite  void AAbb::OnArchieveReaded()
{
}

void AAbbManager::OnArchieveReaded()
{
	__AAbbManager::OnArchieveReaded();
}