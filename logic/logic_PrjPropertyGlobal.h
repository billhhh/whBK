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
	Text = 0,          //�ı�
	Numeric,       //���� 
	Boolean,       //�߼�
	NumericArray,  //��������
	BooleanArray   //�߼�����
};

typedef struct
{
	VarietyType type;
	std::string name;
}VarProperty;

#endif
