/* 
* 
* function: if 模块
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
	int contentInt; //分支的内容 int
	std::string contentStr; //分支的内容 string
}whBranch;

class logic_IfModule
	: public logic_BasicModule
{
public:

	std::string IfName;

	/////构造函数和析构函数
	explicit logic_IfModule(int id);//默认构造，for里面什么都不生成
	//完整map构造函数，方便for内部析构操作
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

	logic_Tree * getCurActiveTree(int branch_id); //返回 指定 branch 当前激活树id
	int setCurActiveTree(int branch_id,logic_Tree * tree);

	///// \向指定 branch 中添加一棵树
	///// \return 返回错误类型，正常返回0
	int addTree(int branch_id,logic_Tree * tree);
	///// \删除一棵树
	int delTree(logic_Tree * tree);


	///
	/// \brief get set 某个 branch 参数
	///
	int getBranchContentInt(int branch_id); //get 指定 branch的int content
	std::string getBranchContentStr(int branch_id); //string
	///// \返回不同错误代码，正常返回0
	int setBranchContent(int branch_id,int con_int);
	int setBranchContent(int branch_id,std::string con_str); //重载 string

	int addBranch();
	std::vector<int > delBranch(int branch_id); //返回需要在外面删除的树id列表【废弃】
	//返回错误编号
	int whDelBranch(int branch_id); //从内部删除一个branch【供外部调用】

	int getMaxBranchId(); //方便累加
	int getTreeBranch(logic_Tree * tree); //获得某个tree属于哪个branch

	bool isBranchExist(int branch_id); //判断branch是否存在

	//返回该 if 模块所有树root节点
	std::vector<int > findBranchAllRoots(int branch_id);
	std::vector<int > findBranchAllRootsActive(int branch_id);

protected:


private:
	int mvi_DefaultBranch; //if块默认分支
	std::map<int , whBranch > mvmu_BranchMap; //维护每个 branch id 和 branch实体 的对应
	std::map<logic_Tree * , int > mvmis_Tree_BranchMap; //维护每个 Tree 和 branch 对应

	void Init();

	//////////模块内部自动处理销毁模块操作///////////////
	void Destroy(); //析构是删掉所有树和模块

	void DelAllParaConnect(int id); //删除关于某一模块的所有连线
	void DelTreeThroughPointer(logic_Tree * tree); //通过树指针，完全销毁树中的模块
	void DelActiveTree(int branch_id); //删除具体branch的 activeTree

	//完全删除一棵树所有节点模块的所有信息（各种实体map和connection map）
	void recurs_DelTreeModule(logic_TreeNode *some);
	void DelModule(int id); //销毁关于一个module的一切信息

	void recurs_GetId(logic_TreeNode *some,std::vector<int> & L);

private:
	//完全对应外部的map，方便删除操作
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
