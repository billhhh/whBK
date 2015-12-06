/* 
* 
* function: for ģ��ʵ���ļ�
* 
* Date:2015-11-13
* 
*    Author: Bill Wang
*/

#include "logic_ForModule.h"
#include <assert.h>
#include "logic_WhData.h"

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

	//��activeTree����treeMap
	(*treeMap)[this->composeActiveTreeId()] = mvi_CurActiveTree;
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


///////////////////����ɾ��/////////////
//������ɾ����������ģ��
void logic_ForModule::Destroy() {

	//�����������ã��������а���ģ��

	/// Step1���������а������������� activeTree��
	for (int i = 0;i<mvvu_treeList.size() ;++i) {

		DelTreeThroughPointer(mvvu_treeList[i]);
	}

	/// Step2������ activeTree
	DelActiveTree();
}

//ͨ����ָ�룬��ȫ�������е�ģ��
void logic_ForModule::DelTreeThroughPointer(logic_Tree * tree) {

	logic_TreeNode * root = tree->getRoot();
	recurs_DelTreeModule(root); //����ģ��ʵ��

	treeForIfmap->erase(tree);
	SAFE_DELETE(tree); //������
	//Ĩ�����ۼ�
	treeMap->erase(tree->mvi_TreeID);
}

//ɾ����ģ��� activeTree
void logic_ForModule::DelActiveTree() {

	logic_TreeNode * root = mvi_CurActiveTree->getRoot();

	for (int i=0;i<root->mvvu_Children.size();++i) {
		//����û�������е�ģ��
		recurs_DelTreeModule(root->mvvu_Children[i]);
	}

	SAFE_DELETE(mvi_CurActiveTree); //������
	//Ĩ��activeTree�ۼ�
	treeMap->erase( composeActiveTreeId() );
}

//��ȫɾ��һ�������нڵ��������Ϣ������ʵ��map��connection map��
void logic_ForModule::recurs_DelTreeModule(logic_TreeNode *some) {

	///// do sth here
	int tmpId = some->getID();
	if( moduleMap->count(tmpId) == 0 )
		assert(false);

	DelModule(tmpId);

	//�� getAllTreeNodeId() ���ã��ݹ�get id
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++) {
		recurs_DelTreeModule(some->mvvu_Children[i]);
	}
}

//���ٹ���һ��module��һ����Ϣ
void logic_ForModule::DelModule(int id) {

	//ɾ������map
	moduleMap->erase(id);
	mTreeMap->erase(id);

	DelAllParaConnect(id);
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
