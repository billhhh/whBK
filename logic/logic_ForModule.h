/* 
* 
* function: for ģ��
* 
* Date:2015-11-3
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_FOR_MODULE_H_
#define _LOGIC_FOR_MODULE_H_

#include "logic_BasicModule.h"
#include "logic_Tree.h"
//#include <vector>
#include <map>

class logic_ForModule 
	: public logic_BasicModule
{
public:
	/////���캯������������
	explicit logic_ForModule(int id);//Ĭ�Ϲ��죬for����ʲô��������
	~logic_ForModule();

	logic_Tree * getCurActiveTree(); //���ص�ǰ������
	void setCurActiveTree(logic_Tree * tree); //���õ�ǰ������

	int addTree(logic_Tree * tree); //�� For Module ���һ���������ش������ͣ���������0
	int delTree(int id); //�� For Module ��ɾ����id�����ش������ͣ���������0

protected:


private:
	logic_Tree * mvi_CurActiveTree; //��ǰ�Ŀ���������for�ļ���״̬��Ҳ�����޼�����
	std::map<int ,logic_Tree * > mvvu_treeList; //forģ���е�������

	void Init();

};

//���ͺ������ж��ض�ֵ�� vector �����Ƿ����
template <class Type>
int whIsInVector(std::vector<Type> vec,Type value ) {

	std::vector<Type>::iterator it;
	it = find(vec.begin(),vec.end(),value);

	if (it!=vec.end()){
		//vec�д���valueֵ
		return it-vec.begin();
	}else {
		//vec�в�����valueֵ
		return -1;
	}
}


#endif
