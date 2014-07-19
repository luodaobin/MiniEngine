#ifndef _#HEADTAG_H_
#define _#HEADTAG_H_
#include "MgrBase.h"
#include "SimpleRefection.h"
class #CLASSNAME:public ReflectionBase
{
	DECL_REFLECTION(Operator,"../config/#CLASSNAME.xml");
public:
	int32			m_iID;
	std::string		m_sDisplayName;

	rewrite virtual void OnArchieveReaded();
private:
};

typedef DefMangerTpl<#CLASSNAME,eDefaultDef_#CLASSNAME> __#CLASSNAMEManager;
class #CLASSNAMEManager:public __#CLASSNAMEManager;
{
public:
	static #CLASSNAME& Instance(){static #CLASSNAME _instance;return _instance;	}
	virtual void OnArchieveReaded();
private:
	#CLASSNAME(){}
};

#endif
/////////////////////////////////////////
