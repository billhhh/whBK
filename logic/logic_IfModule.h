/* 
* 
* function: if ģ��
* 
* Date:2015-11-14
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_IF_MODULE_H_
#define _LOGIC_IF_MODULE_H_

#include "logic_BasicModule.h"
#include "logic_Tree.h"
#include <vector>
#include <map>
#include "logic_whPort.h"
#include "logic_WhData.h"

typedef struct
{
	int branchId;
	logic_Tree * curActiveTree;
	int contentInt; //��֧������ int
	std::string contentStr; //��֧������ string
}whBranch;

class logic_IfModule
	: public logic_BasicModule
{
public:

	std::string IfName;

	/////���캯������������
	explicit logic_IfModule(int id);//Ĭ�Ϲ��죬for����ʲô��������
	//����map���캯��������for�ڲ���������
	explicit logic_IfModule(int id,
		std::map <int,logic_Tree *> &tree_map,
		std::map <int, logic_BasicModule *> &module_map,
		std::map <int ,logic_Tree * > &m_tree_map,
		std::map <logic_Tree * ,int > &tree_forif_map,
		std::map<whPort, whPort > &conn_fromto_map,
		std::map<whPort, whPort > &conn_tofrom_map,
		const logic_BasicModule &bm
		);

	~logic_IfModule();

	logic_Tree * getCurActiveTree(int branch_id); //���� ָ�� branch ��ǰ������id
	int setCurActiveTree(int branch_id,logic_Tree * tree);

	///// \��ָ�� branch �����һ����
	///// \return ���ش������ͣ���������0
	int addTree(int branch_id,logic_Tree * tree);
	///// \ɾ��һ����
	int delTree(logic_Tree * tree);


	///
	/// \brief get set ĳ�� branch ����
	///
	int getBranchContentInt(int branch_id); //get ָ�� branch��int content
	std::string getBranchContentStr(int branch_id); //string
	///// \���ز�ͬ������룬��������0
	int setBranchContent(int branch_id,int con_int);
	int setBranchContent(int branch_id,std::string con_str); //���� string

	int addBranch();
	std::vector<int > delBranch(int branch_id); //������Ҫ������ɾ������id�б�������
	//���ش�����
	int whDelBranch(int branch_id); //���ڲ�ɾ��һ��branch�����ⲿ���á�

	int getMaxBranchId(); //�����ۼ�
	int getTreeBranch(logic_Tree * tree); //���ĳ��tree�����ĸ�branch

	bool isBranchExist(int branch_id); //�ж�branch�Ƿ����

	//���ظ� if ģ��������root�ڵ�
	std::vector<int > findBranchAllRoots(int branch_id);
	std::vector<int > findBranchAllRootsActive(int branch_id);

protected:


private:
	int mvi_DefaultBranch; //if��Ĭ�Ϸ�֧
	std::map<int , whBranch > mvmu_BranchMap; //ά��ÿ�� branch id �� branchʵ�� �Ķ�Ӧ
	std::map<logic_Tree * , int > mvmis_Tree_BranchMap; //ά��ÿ�� Tree �� branch ��Ӧ

	void Init();

	//////////ģ���ڲ��Զ���������ģ�����///////////////
	void Destroy(); //������ɾ����������ģ��

	void DelAllParaConnect(int id); //ɾ������ĳһģ�����������
	void DelTreeThroughPointer(logic_Tree * tree); //ͨ����ָ�룬��ȫ�������е�ģ��
	void DelActiveTree(int branch_id); //ɾ������branch�� activeTree

	//��ȫɾ��һ�������нڵ�ģ���������Ϣ������ʵ��map��connection map��
	void recurs_DelTreeModule(logic_TreeNode *some);
	void DelModule(int id); //���ٹ���һ��module��һ����Ϣ

	void recurs_GetId(logic_TreeNode *some,std::vector<int> & L);

private:
	//��ȫ��Ӧ�ⲿ��map������ɾ������
	std::map <int,logic_Tree *> *treeMap;
	std::map <int, logic_BasicModule *> *moduleMap;
	std::map <int ,logic_Tree * > *mTreeMap;
	std::map <logic_Tree * ,int > *treeForIfmap;
	std::map<whPort, whPort > *connFromToMap;
	std::map<whPort, whPort > *connToFromMap;

	//rootId = moduleId*100000+branchId
	inline int composeActiveTreeId(int branch_id) {

		return this->mvi_ModuleID * ACTIVE_TREE_MAP_FACTOR + branch_id;
	}
};


#endif
