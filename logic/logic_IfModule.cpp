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

// 	whBranch newBranch;
// 	newBranch.curActiveTree = NULL;
// 	newBranch.contentInt = INT_MIN;
// 	newBranch.contentStr = "";
// 	mvmu_BranchMap[0] = newBranch; ////////mvmu_BranchMap 要找max

	mvmis_Tree_BranchMap.clear();
}

//返回 指定 branch 当前激活树id
logic_Tree * logic_IfModule::getCurActiveTree(int branch_id) {

	//没找到，错误
	if( mvmu_BranchMap.count(branch_id)<=0 )
		return NULL;

	return mvmu_BranchMap[branch_id].curActiveTree;
}

int logic_IfModule::setCurActiveTree(int branch_id,logic_Tree * tree) {

	//没找到此 branch，错误
	if( mvmu_BranchMap.count(branch_id)<=0 )
		return -1;

	//没找到此 tree
	if ( mvmis_Tree_BranchMap.count(tree) <= 0 )
		return -2;

	mvmu_BranchMap[branch_id].curActiveTree = tree;
	return 0;
}

///// \向指定 branch 中添加一棵树
///// \return 返回错误类型，正常返回0
int logic_IfModule::addTree(int branch_id,logic_Tree * tree) {

	//没找到此 branch，错误
	if( mvmu_BranchMap.count(branch_id)<=0 )
		return -1;

	//已经有该树了
	if( mvmis_Tree_BranchMap.count(tree) > 0 )
		return -2;

	mvmis_Tree_BranchMap[tree] = branch_id;

	return 0;
}

///// \删除一棵树
int logic_IfModule::delTree(logic_Tree * tree) {

	//并没有找到该树
	if( mvmis_Tree_BranchMap.count(tree) == 0 )
		return -1;

	mvmis_Tree_BranchMap.erase(tree);

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
	newBranch.curActiveTree = NULL;
	newBranch.contentInt = INT_MIN;
	newBranch.contentStr = "";

	mvmu_BranchMap[max_branch_id] = newBranch;

	return max_branch_id;
}

//删除一个branch
//返回需要在外面删除的树id列表
std::vector<int > logic_IfModule::delBranch(int branch_id) {

	std::vector<int > L;

	//当残余branch数量只有2个或以下，不允许删除
	if( mvmu_BranchMap.size() <= 3 )
		return L;

	//找不到该branch，错误
	if( mvmu_BranchMap.count(branch_id)==0 )
		return L;

	//遍历，收集待删除的树 id 列表
	for(std::map<logic_Tree *  ,int >::iterator it = mvmis_Tree_BranchMap.begin(); it != mvmis_Tree_BranchMap.end() ; ++it ) {

		if(  branch_id == it->second ) {

			L.push_back(it->first->mvi_TreeID);
			mvmis_Tree_BranchMap.erase(it);
		}
	}

	mvmu_BranchMap.erase(branch_id);

	//如果被删掉的分支是默认分支，将默认分支设置为第一个分支
	if( branch_id == this->mvi_DefaultBranch ) {

		std::map<int, whBranch >::iterator it = mvmu_BranchMap.begin();
		++it;
		this->mvi_DefaultBranch = it->first;
	}

	return L;
}

//方便累加
int logic_IfModule::getMaxBranchId() {

	if( mvmu_BranchMap.size() == 0 )
		return 0;

	std::map<int, whBranch >::const_iterator it = mvmu_BranchMap.end();
	it--;
	return it->first;
}
