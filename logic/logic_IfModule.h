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
#include <vector>
#include <map>

typedef struct
{
	int curActiveTree;
	int contentInt; //分支的内容 int
	std::string contentStr; //分支的内容 string
}whBranch;

class logic_IfModule
	: public logic_BasicModule
{
public:
	/////构造函数和析构函数
	explicit logic_IfModule(int id);//默认构造，for里面什么都不生成
	~logic_IfModule();

	int getCurActiveTree(int branch_id); //返回 指定 branch 当前激活树id
	int setCurActiveTree(int branch_id,int tree_id);

	///// \向指定 branch 中添加一棵树
	///// \return 返回错误类型，正常返回0
	int addTreeId(int branch_id,int tree_id);
	///// \删除一棵树
	int delTreeId(int tree_id);


	///
	/// \brief get set 某个 branch 参数
	///
	int getBranchContentInt(int branch_id); //get 指定 branch的int content
	std::string getBranchContentStr(int branch_id); //string
	///// \返回不同错误代码，正常返回0
	int setBranchContent(int branch_id,int con_int);
	int setBranchContent(int branch_id,std::string con_str); //重载 string

	int addBranch();
	std::vector<int > delBranch(int branch_id); //返回需要在外面删除的树id列表

	int getMaxBranchId(); //方便累加

protected:


private:
	int mvi_DefaultBranch; //if块默认分支
	std::map<int , whBranch > mvmu_BranchMap; //维护每个 branch id 和 branch实体 的对应
	std::map<int , int > mvmis_TreeId_BranchMap; //维护每个 TreeId 和 branch 对应

	void Init();

};


#endif
