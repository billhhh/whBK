/* 
* 
* function: if 模块实现文件
* 
* Date:2015-11-14
* 
*    Author: Bill Wang
*/

#include "logic_IfModule.h"

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
