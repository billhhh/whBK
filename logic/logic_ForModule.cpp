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

	mvvu_treeIdList.clear();
}

//返回当前激活树id【注意是树id】
int logic_ForModule::getCurActiveTree() {

	return mvi_CurActiveTree;
}

//设置当前激活树
void logic_ForModule::setCurActiveTree(int id) {

	mvi_CurActiveTree = id;
}

//向 For Module 添加一棵树 id，返回错误类型，正常返回0
int logic_ForModule::addTreeId(int id) {

	if ( true == whIsInVector<int > (mvvu_treeIdList,id) ){
		//发现已存在，错误返回
		return -1;
	}

	mvvu_treeIdList.push_back(id);
	return 0;
}

//在 For Module 中删除树 id，返回错误类型，正常返回0
int logic_ForModule::delTreeId(int id) {

	int pos = whIsInVector<int > (mvvu_treeIdList,id);
	if ( pos < 0 ){
		//发现待删除树id并不存在存在，错误返回
		return -1;
	}

	std::vector<int>::iterator tmpIt = mvvu_treeIdList.begin()+pos;
	mvvu_treeIdList.erase(tmpIt);
	return 0;
}
