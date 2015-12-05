/* 
* 
* function: for ģ��ʵ���ļ�
* 
* Date:2015-11-13
* 
*    Author: Bill Wang
*/

#include "logic_ForModule.h"

using namespace std;

logic_ForModule::logic_ForModule(int id)
	:logic_BasicModule(id,2003){
		//���ø���Ĺ��캯�� ��ʼ��id��type
		Init(); //��ʼ��
}

//����map���캯��������for�ڲ���������
logic_ForModule::logic_ForModule(int id,
						 std::map <int,logic_Tree *> &tree_map,
						 std::map <int, logic_BasicModule *> &module_map,
						 std::map <int ,logic_Tree * > &m_tree_map,
						 std::map <logic_Tree * ,int > &tree_forif_map,
						 std::map<whPort, whPort > &conn_fromto_map,
						 std::map<whPort, whPort > &conn_tofrom_map
						 ):treeMap(&tree_map),moduleMap(&module_map),mTreeMap(&m_tree_map),
						 treeForIfmap(&tree_forif_map),connFromToMap(&conn_fromto_map),connToFromMap(&conn_tofrom_map)
{
	Init();
}

logic_ForModule::~logic_ForModule() {

	Destroy(); //�����������ж���
}

void logic_ForModule::Init() {

	//��ʼ����
	mvvu_treeList.clear();
	mvi_CurActiveTree = new logic_Tree(-1); //activeTree root�ڵ���Ϊ-1
}

//������ɾ����������ģ��
void logic_ForModule::Destroy() {

	//�����������ã��������а���ģ��

}

//���ص�ǰ������
logic_Tree * logic_ForModule::getCurActiveTree() {

	return mvi_CurActiveTree;
}

//���õ�ǰ������
void logic_ForModule::setCurActiveTree(logic_Tree * tree) {

	mvi_CurActiveTree = tree;
}

//�� For Module ���һ���� id�����ش������ͣ���������0
int logic_ForModule::addTree(logic_Tree * tree) {

	int id = tree->mvi_TreeID;
	if ( mvvu_treeList.count(id) > 0 ){
		//�����Ѵ��ڣ����󷵻�
		return -1;
	}

	mvvu_treeList[id] = tree;
	return 0;
}

//�� For Module ��ɾ���� id�����ش������ͣ���������0
int logic_ForModule::delTree(logic_Tree * tree) {

	int id = tree->mvi_TreeID;
	if ( mvvu_treeList.count(id) == 0 ){
		//���ִ�ɾ����id�������ڴ��ڣ����󷵻�
		return -1;
	}

	//����ǵ�ǰ��������ɾ���ÿ�
	if( tree->mvi_TreeID == this->mvi_CurActiveTree->mvi_TreeID )
		this->mvi_CurActiveTree = NULL;

	mvvu_treeList.erase(id);
	return 0;
}

//ɾ������ĳһģ�����������
void logic_ForModule::DelAllParaConnect(int id) {

	//��������
	for( map<whPort ,whPort >::iterator it = connFromToMap->begin(); it != connFromToMap->end(); ++it ) {

		if( id == it->first.moduleId ) {

			//��� from �Ǹ�ģ�飬������� outModule ��ؾ���Ҫɾ��
			whPort outPort = it->first;
			whPort inPort = (*connFromToMap)[outPort];
			connFromToMap->erase(outPort);
			connToFromMap->erase(inPort);

		}else if(id == it->second.moduleId) {

			//��� to �Ǹ�ģ��
			whPort outPort = it->first;   // �൱�� whPort inPort = it->second;
			whPort inPort = (*connFromToMap)[outPort];
			connFromToMap->erase(outPort);
			connToFromMap->erase(inPort);
		}
	}
}
