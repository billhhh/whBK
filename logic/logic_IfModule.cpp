/* 
* 
* function: if 模块实现文件
* 
* Date:2015-11-14
* 
*    Author: Bill Wang
*/

#include "logic_IfModule.h"
#include <limits.h>

// #define INT_MAX 0x7fffffff
// #define INT_MIN 0x80000000

logic_IfModule::logic_IfModule(int id)
	:logic_BasicModule(id,2004){
		//调用父类的构造函数 初始化id和type
		Init(); //初始化
}

logic_IfModule::~logic_IfModule() {

	//析构，子类并不用做什么
	//先析构子类，再析构父类
}

void logic_IfModule::Init() {

	mvmu_BranchMap.clear();
	whBranch newBranch;
	newBranch.curActiveTree = -1;
	newBranch.contentInt = INT_MIN;
	newBranch.contentStr = "";
	mvmu_BranchMap[0] = newBranch; ////////mvmu_BranchMap 要找max

	mvmis_TreeId_BranchMap.clear();
}

//返回 指定 branch 当前激活树id
int logic_IfModule::getCurActiveTree(int branch_id) {

	//没找到，错误
	if( mvmu_BranchMap.count(branch_id)<=0 )
		return -1;

	return mvmu_BranchMap[branch_id].curActiveTree;
}

int logic_IfModule::setCurActiveTree(int branch_id,int tree_id) {

	//没找到此 branch，错误
	if( mvmu_BranchMap.count(branch_id)<=0 )
		return -1;

	//没找到此 tree
	if ( mvmis_TreeId_BranchMap.count(tree_id)<=0 )
		return -2;

	mvmu_BranchMap[branch_id].curActiveTree = tree_id;
	return 0;
}

///// \向指定 branch 中添加一棵树
///// \return 返回错误类型，正常返回0
int logic_IfModule::addTreeId(int branch_id,int tree_id) {

	//没找到此 branch，错误
	if( mvmu_BranchMap.count(branch_id)<=0 )
		return -1;

	//已经有该树了
	if( mvmis_TreeId_BranchMap.count(tree_id) > 0 )
		return -2;

	mvmis_TreeId_BranchMap[tree_id] = branch_id;

	return 0;
}

///// \删除一棵树
int logic_IfModule::delTreeId(int tree_id) {

	//并没有找到该树
	if( mvmis_TreeId_BranchMap.count(tree_id) == 0 )
		return -1;

	mvmis_TreeId_BranchMap.erase(tree_id);

	return 0;
}


///
/// \brief get set 某个 branch 参数
///

//get 指定 branch的int content
int logic_IfModule::getBranchContentInt(int branch_id) {

	//找不到该branch，错误
	if( mvmu_BranchMap.count(branch_id)==0 )
		return -1;

	return mvmu_BranchMap[branch_id].contentInt;
}

//string
std::string logic_IfModule::getBranchContentStr(int branch_id) {

	//找不到该branch，错误
	if( mvmu_BranchMap.count(branch_id)==0 )
		return NULL;

	return mvmu_BranchMap[branch_id].contentStr;
}

///// \返回不同错误代码，正常返回0
int logic_IfModule::setBranchContent(int branch_id,int con_int) {

	//找不到该branch，错误
	if( mvmu_BranchMap.count(branch_id)==0 )
		return -1;

	mvmu_BranchMap[branch_id].contentInt = con_int;

	return 0;
}

//重载 string
int logic_IfModule::setBranchContent(int branch_id,std::string con_str) {

	//找不到该branch，错误
	if( mvmu_BranchMap.count(branch_id)==0 )
		return -1;

	mvmu_BranchMap[branch_id].contentStr = con_str;

	return 0;

}


/////增加一个branch，需要初始化 whBranch 实体
int logic_IfModule::addBranch() {

	int max_branch_id = this->getMaxBranchId();
	max_branch_id++;

	whBranch newBranch;
	newBranch.curActiveTree = -1;
	newBranch.contentInt = INT_MIN;
	newBranch.contentStr = "";

	mvmu_BranchMap[max_branch_id] = newBranch;

	return 0;
}

//删除一个branch
int logic_IfModule::delBranch(int branch_id) {

	//找不到该branch，错误
	if( mvmu_BranchMap.count(branch_id)==0 )
		return -1;

	mvmu_BranchMap.erase(branch_id);
	return 0;
}

//方便累加
int logic_IfModule::getMaxBranchId() {

	std::map<int, whBranch >::const_iterator it = mvmu_BranchMap.end();
	it--;
	return it->first;
}
