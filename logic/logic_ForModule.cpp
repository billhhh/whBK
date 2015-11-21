/* 
* 
* function: for ģ��ʵ���ļ�
* 
* Date:2015-11-13
* 
*    Author: Bill Wang
*/

#include "logic_ForModule.h"

logic_ForModule::logic_ForModule(int id)
	:logic_BasicModule(id,2003){
		//���ø���Ĺ��캯�� ��ʼ��id��type
		Init(); //��ʼ��
}

logic_ForModule::~logic_ForModule() {

	//���������ಢ������ʲô
	//���������࣬����������
}

void logic_ForModule::Init() {

	mvvu_treeIdList.clear();
}

//���ص�ǰ������id��ע������id��
int logic_ForModule::getCurActiveTree() {

	return mvi_CurActiveTree;
}

//���õ�ǰ������
void logic_ForModule::setCurActiveTree(int id) {

	mvi_CurActiveTree = id;
}

//�� For Module ���һ���� id�����ش������ͣ���������0
int logic_ForModule::addTreeId(int id) {

	if ( true == whIsInVector<int > (mvvu_treeIdList,id) ){
		//�����Ѵ��ڣ����󷵻�
		return -1;
	}

	mvvu_treeIdList.push_back(id);
	return 0;
}

//�� For Module ��ɾ���� id�����ش������ͣ���������0
int logic_ForModule::delTreeId(int id) {

	int pos = whIsInVector<int > (mvvu_treeIdList,id);
	if ( pos < 0 ){
		//���ִ�ɾ����id�������ڴ��ڣ����󷵻�
		return -1;
	}

	std::vector<int>::iterator tmpIt = mvvu_treeIdList.begin()+pos;
	mvvu_treeIdList.erase(tmpIt);
	return 0;
}
