/* 
* 
* function: ��Ŀ����ȫ�ֱ���
* 
* Date:2016-01-27
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_PRJ_PROPERTY_GLOBAL_H_
#define _LOGIC_PRJ_PROPERTY_GLOBAL_H_

#include <string>

enum VarietyType{  //��������
	TEXT = 0,          //�ı�
	NUM,       //����
	BOOL,       //�߼�
	NUM_ARR,  //��������
	BOOL_ARR   //�߼�����
};

typedef struct
{
	VarietyType type;
	std::string name;
}VarProperty;

#endif
