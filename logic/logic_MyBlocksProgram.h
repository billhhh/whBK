/* 
* 
* function: �߼����ҵ�ģ��program
* 
* Date:2015-09-02
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_MY_BLOCKS_PROGRAM_H_
#define _LOGIC_MY_BLOCKS_PROGRAM_H_

#include "logic_Program.h"
#include "logic_BasicModule.h"
//#include "logic_BasicPara.h"

class logic_MyBlocksProgram
	: public logic_Program
{
public:
	//std::vector <logic_BasicPara *> mvvu_ParaList; //�ҵ�ģ������б��������������
	logic_BasicModule InputModule; //�������ģ��
	logic_BasicModule OutputModule; //�������ģ��

protected:

private:

};


#endif
