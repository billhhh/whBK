/* 
* 
* function: �߼����ҵ�ģ��program��ʵ��
* 
* Date:2015-09-02
* 
*    Author: Bill Wang
*/

#include "logic_MyBlocksProgram.h"

logic_MyBlocksProgram::logic_MyBlocksProgram(int id, std::string prog_name
											 ,std::map <int, logic_BasicModule *> init_map //��ʼ��ģ��map
											 ,std::vector <logic_BasicPara *> plist //��������б�
											 ,std::map <int, logic_BasicModule *> module_map //����module_map
											 ,logic_Tree *tree //�������ṹ
											 )
	:logic_Program(id,prog_name,init_map) {

		//���������������ģ��   //��ʼģ��+����ģ��

}
