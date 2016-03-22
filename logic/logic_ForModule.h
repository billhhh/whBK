/* 
* 
* function: for 模块
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

	/////构造函数和析构函数
	explicit logic_ForModule(int id);//默认构造，for里面什么都不生成
	//完整map构造函数，方便for内部析构操作
	logic_ForModule(int id,
		std::map <int,logic_Tree *> &tree_map,
		std::map <int, logic_BasicModule *> &module_map,
		std::map <int ,logic_Tree * > &m_tree_map,
		std::map <logic_Tree * ,int > &tree_forif_map,
		std::map<whPort, whPort > &conn_fromto_map,
		std::map<whPort, whPort > &conn_tofrom_map,
		const logic_BasicModule &bm
		);

	~logic_ForModule(); //析构

	logic_Tree * getCurActiveTree(); //返回当前激活树
	void setCurActiveTree(logic_Tree * tree); //设置当前激活树

	int addTree(logic_Tree * tree); //向 For Module 添加一棵树，返回错误类型，正常返回0
	int delTree(logic_Tree * tree); //在 For Module 中删除树id，返回错误类型，正常返回0

	//返回该 for 模块所有树root节点
	std::vector<int > findAllRoots();
	std::vector<int > findAllRootsActive();

	std::vector<int > getAllModuleId(); //获得（本层，不包括进一层的for或if中的模块id）所有模块id

protected:


private:

	///有一棵空节点的树
	logic_Tree * mvi_CurActiveTree;
	std::map<int ,logic_Tree * > mvvu_treeList; //for模块中的所有树

	void Init();

	//////////模块内部自动处理销毁模块操作///////////////
	void Destroy(); //析构是删掉所有树和模块

	void DelAllParaConnect(int id); //删除关于某一模块的所有连线
	void DelTreeThroughPointer(logic_Tree * tree); //通过树指针，完全销毁树中的模块
	void DelActiveTree(); //删除本模块的 activeTree

	//完全删除一棵树所有节点模块的所有信息（各种实体map和connection map）
	void recurs_DelTreeModule(logic_TreeNode *some);
	void DelModule(int id); //销毁关于一个module的一切信息

	//DFS获得树id
	void recurs_GetId(logic_TreeNode *some,std::vector<int> & L);

private:
	//完全对应外部的map，方便删除操作
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

//泛型函数：判断特定值在 vector 里面是否存在
template <class Type>
int whIsInVector(std::vector<Type> vec,Type value ) {

	std::vector<Type>::iterator it;
	it = find(vec.begin(),vec.end(),value);

	if (it!=vec.end()){
		//vec中存在value值
		return it-vec.begin();
	}else {
		//vec中不存在value值
		return -1;
	}
}


#endif
