/* 
* 
* function: ���ҵ�ģ�顱ʵ����ʵ��
* 
* Date:2015-03-05
* 
*    Author: Bill Wang
*/

#include "logic_MyBlocksModule.h"

//���캯��
logic_MyBlocksModule::logic_MyBlocksModule() {

}

//���캯��
logic_MyBlocksModule::logic_MyBlocksModule(int mbprog_id)
	:mvi_MyBlockProgID(mbprog_id),mvi_MyBlockProg(NULL) {

}

//���캯��
logic_MyBlocksModule::logic_MyBlocksModule(logic_MyBlocksProgram *mbprog)
	:mvi_MyBlockProgID(mbprog->getID()),mvi_MyBlockProg(mbprog) {

}
