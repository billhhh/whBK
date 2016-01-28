/* 
* 
* function: ����ʵ���࣬����һ������Ĳ���
* 
* Date:2015-09-01
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_BASIC_PARA_H_
#define _LOGIC_BASIC_PARA_H_

#include <string>

enum ParaIOType{
	PARA_IN = 0,
	PARA_OUT
};

enum ParaType{
	PARA_LOGIC = 0,//�߼�
	PARA_NUM, //����
	PARA_TEXT, //�ı�
	PARA_MULTI, //��ѡ
	PARA_INPORT //�˿�����
};

class logic_BasicPara
{
public:
	int mvi_ParaID;
	ParaIOType mve_IOType; //in������out
	ParaType mve_ParaType;
	std::string mvs_Value; //����ֵ
	int mvd_Min;//��Χֵ
	int mvd_Max;

	bool mvb_IsInport; //�Ƿ����߽���

	//���ز�������
	ParaType getParaType() {
		return mve_ParaType;
	}

	//���������뻹�����������ö������
	ParaIOType getParaIOType() {
		return mve_IOType;
	}

	std::string getValue() {
		return mvs_Value;
	}

protected:


private:

};

#endif
