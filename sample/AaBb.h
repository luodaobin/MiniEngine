#ifndef _AABB_H_
#define _AABB_H_
#include "MgrBase.h"
#include "SimpleRefection.h"
class AAbb:public ReflectionBase
{
	DECL_REFLECTION(Operator,"../config/AAbb.xml");
public:
	int32			m_iID;
	std::string		m_sDisplayName;

	rewrite virtual void OnArchieveReaded();
private:
};

typedef DefMangerTpl<AAbb,eDefaultDef_AAbb> __AAbbManager;
class AAbbManager:public __AAbbManager;
{
public:
	static AAbb& Instance(){static AAbb _instance;return _instance;	}
	virtual void OnArchieveReaded();
private:
	AAbb(){}
};

#endif
/////////////////////////////////////////
