#include <assert.h>

typedef struct structPort
{
	int moduleId;
	int paraId;

	bool operator < (const structPort &port) const
	{
		if( moduleId < port.moduleId ) { //С��ֱ�ӷ���true
			return true;
		}else if( moduleId > port.moduleId ) { //���ڷ���false
			return false;
		}else {

			//���moduleIdһ���������Ƚ�paraId�������ܶ�һ��
			if( paraId < port.paraId )
				return true;
			else if(paraId > port.paraId)
				return false;
			else
				assert(false);
		}
	}

}whPort;  //һ�����ڶ��壬��ȫ����һ��port