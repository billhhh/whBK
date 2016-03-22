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
#include <vector>
#include <map>
#include "logic_whPort.h"
#include "logic_WhData.h"

class logic_ForModule 
	: public logic_BasicModule
{
public:

	std::string forName;

	/////���캯������������
	explicit logic_ForModule(int id);//Ĭ�Ϲ��죬for����ʲô��������
	//����map���캯��������for�ڲ���������
	logic_ForModule(int id,
		std::map <int,logic_Tree *> &tree_map,
		std::map <int, logic_BasicModule *> &module_map,
		std::map <int ,logic_Tree * > &m_tree_map,
		std::map <logic_Tree * ,int > &tree_forif_map,
		std::map<whPort, whPort > &conn_fromto_map,
		std::map<whPort, whPort > &conn_tofrom_map,
		const logic_BasicModule &bm
		);

	~logic_ForModule(); //����

	logic_Tree * getCurActiveTree(); //���ص�ǰ������
	void setCurActiveTree(logic_Tree * tree); //���õ�ǰ������

	int addTree(logic_Tree * tree); //�� For Module ���һ���������ش������ͣ���������0
	int delTree(logic_Tree * tree); //�� For Module ��ɾ����id�����ش������ͣ���������0

	//���ظ� for ģ��������root�ڵ�
	std::vector<int > findAllRoots();
	std::vector<int > findAllRootsActive();

	std::vector<int > getAllModuleId(); //��ã����㣬��������һ���for��if�е�ģ��id������ģ��id

protected:


private:

	///��һ�ÿսڵ����
	logic_Tree * mvi_CurActiveTree;
	std::map<int ,logic_Tree * > mvvu_treeList; //forģ���е�������

	void Init();

	//////////ģ���ڲ��Զ���������ģ�����///////////////
	void Destroy(); //������ɾ����������ģ��

	void DelAllParaConnect(int id); //ɾ������ĳһģ�����������
	void DelTreeThroughPointer(logic_Tree * tree); //ͨ����ָ�룬��ȫ�������е�ģ��
	void DelActiveTree(); //ɾ����ģ��� activeTree

	//��ȫɾ��һ�������нڵ�ģ���������Ϣ������ʵ��map��connection map��
	void recurs_DelTreeModule(logic_TreeNode *some);
	void DelModule(int id); //���ٹ���һ��module��һ����Ϣ

	//DFS�����id
	void recurs_GetId(logic_TreeNode *some,std::vector<int> & L);

private:
	//��ȫ��Ӧ�ⲿ��map������ɾ������
	std::map <int,logic_Tree *> *treeMap;
	std::map <int, logic_BasicModule *> *moduleMap;
	std::map <int ,logic_Tree * > *mTreeMap;
	std::map <logic_Tree * ,int > *treeForIfmap;
	std::map<whPort, whPort > *connFromToMap;
	std::map<whPort, whPort > *connToFromMap;

	//rootId = moduleId*100000
	inline int composeActiveTreeId() {

		return this->mvi_ModuleID * ACTIVE_TREE_MAP_FACTOR;
	}
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
