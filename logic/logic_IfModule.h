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

typedef struct
{
	logic_Tree * curActiveTree;
	int contentInt; //��֧������ int
	std::string contentStr; //��֧������ string
}whBranch;

class logic_IfModule
	: public logic_BasicModule
{
public:
	/////���캯������������
	explicit logic_IfModule(int id);//Ĭ�Ϲ��죬for����ʲô��������
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
	std::vector<int > delBranch(int branch_id); //������Ҫ������ɾ������id�б�

	int getMaxBranchId(); //�����ۼ�

protected:


private:
	int mvi_DefaultBranch; //if��Ĭ�Ϸ�֧
	std::map<int , whBranch > mvmu_BranchMap; //ά��ÿ�� branch id �� branchʵ�� �Ķ�Ӧ
	std::map<logic_Tree * , int > mvmis_Tree_BranchMap; //ά��ÿ�� Tree �� branch ��Ӧ

	void Init();

};


#endif
