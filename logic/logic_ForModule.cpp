/* 
* 
* function: for 模块实现文件
* 
* Date:2015-11-13
* 
*    Author: Bill Wang
*/

#include "logic_ForModule.h"

logic_ForModule::logic_ForModule(int id)
	:logic_BasicModule(id,2003){
		//调用父类的构造函数 初始化id和type
		Init(); //初始化
}

logic_ForModule::~logic_ForModule() {

	//析构，子类并不用做什么
	//先析构子类，再析构父类
}

void logic_ForModule::Init() {

	//初始化类
	mvvu_treeList.clear();
	mvi_CurActiveTree = new logic_Tree(-1); //activeTree root节点编号为-1
}

//返回当前激活树
logic_Tree * logic_ForModule::getCurActiveTree() {

	return mvi_CurActiveTree;
}

//设置当前激活树
void logic_ForModule::setCurActiveTree(logic_Tree * tree) {

	mvi_CurActiveTree = tree;
}

//向 For Module 添加一棵树 id，返回错误类型，正常返回0
int logic_ForModule::addTree(logic_Tree * tree) {

	int id = tree->mvi_TreeID;
	if ( mvvu_treeList.count(id) > 0 ){
		//发现已存在，错误返回
		return -1;
	}

	mvvu_treeList[id] = tree;
	return 0;
}

//在 For Module 中删除树 id，返回错误类型，正常返回0
int logic_ForModule::delTree(logic_Tree * tree) {

	int id = tree->mvi_TreeID;
	if ( mvvu_treeList.count(id) == 0 ){
		//发现待删除树id并不存在存在，错误返回
		return -1;
	}

	//如果是当前激活树被删，置空
	if( tree->mvi_TreeID == this->mvi_CurActiveTree->mvi_TreeID )
		this->mvi_CurActiveTree = NULL;

	mvvu_treeList.erase(id);
	return 0;
}
