#include "stdafx.h"
#include "#CLASSNAME.h"
#include "InstanceTouch.h"
DECL_INSTANCE_TOUCH(ETouch_#CLASSNAME);

struct  #CLASSNAMEDefReflectionRegister
{
	#CLASSNAMEDefReflectionRegister()
	{
		REGISTER_REFLECTION_MEMBER(#CLASSNAME,m_iID,INVALID_ID).Editor_SetAsPrimaryKey();
		REGISTER_REFLECTION_MEMBER(#CLASSNAME,m_sDisplayName,std::string("DefaultName")).Editor_SetAsDisplayName();
		
		GlobalDefManager::Instance().RegisterDefManger(&#CLASSNAMEManager::Instance());

	}
}___#CLASSNAMEDefReflectionRegister;

rewrite  void #CLASSNAME::OnArchieveReaded()
{
}

void #CLASSNAMEManager::OnArchieveReaded()
{
	__#CLASSNAMEManager::OnArchieveReaded();
}