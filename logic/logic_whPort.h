#include <assert.h>

typedef struct structPort
{
	int moduleId;
	int paraId;

	bool operator < (const structPort &port) const
	{
		if( moduleId < port.moduleId ) { //小于直接返回true
			return true;
		}else if( moduleId > port.moduleId ) { //大于返回false
			return false;
		}else {

			//如果moduleId一样，继续比较paraId，不可能都一样
			if( paraId < port.paraId )
				return true;
			else if(paraId > port.paraId)
				return false;
			else
				assert(false);
		}
	}

}whPort;  //一个出口定义，完全定义一个port