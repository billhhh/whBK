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
//#include <vector>
#include <map>

class logic_ForModule 
	: public logic_BasicModule
{
public:
	/////构造函数和析构函数
	explicit logic_ForModule(int id);//默认构造，for里面什么都不生成
	~logic_ForModule();

	logic_Tree * getCurActiveTree(); //返回当前激活树
	void setCurActiveTree(logic_Tree * tree); //设置当前激活树

	int addTree(logic_Tree * tree); //向 For Module 添加一棵树，返回错误类型，正常返回0
	int delTree(int id); //在 For Module 中删除树id，返回错误类型，正常返回0

protected:


private:
	logic_Tree * mvi_CurActiveTree; //当前哪棵树是连接for的激活状态，也可能无激活树
	std::map<int ,logic_Tree * > mvvu_treeList; //for模块中的所有树

	void Init();

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
