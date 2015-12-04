/* 
* 
* function: 逻辑层森林组织结构
* 
* Date:2015-09-02
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_PROGRAM_H_
#define _LOGIC_PROGRAM_H_

#include <string>
#include <vector>
#include <map>
#include <assert.h>
#include "logic_Tree.h"
#include "logic_BasicModule.h"
#include "logic_Global.h"

typedef struct structPort
{
	int moduleId;
	int paraId;

	bool operator < (const structPort &port) const
	{
		if( moduleId < port.moduleId ) { //小于直接返回true
			return true;
		}else if( moduleId > port.moduleId ) { //大于返回false
			return false;
		}else {

			//如果moduleId一样，继续比较paraId，不可能都一样
			if( paraId < port.paraId )
				return true;
			else if(paraId > port.paraId)
				return false;
			else
				assert(false);
		}
	}

}whPort;  //一个出口定义，完全定义一个port

class logic_Program //等效于森林
{
public:

	explicit logic_Program(int id, std::string prog_name);
	virtual ~logic_Program();


	/////!!!!!!!!!!!!!!!!!!!!!!!!!树操作!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	bool add_Tree(_IdDataType rootId); //添加一棵 root ID为id的树
	bool add_Tree(logic_Tree * t);
	bool del_Tree(_IdDataType rootId);
	logic_Tree* search_Tree(_IdDataType rootId);
	_IdDataType search_Tree(logic_Tree* treePtr); //根据树指针找ID

	logic_Tree* getTreeFromId(int m_id); //通过一个模块id，找到所在树（通过Map映射来做）

	/////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/////!!!!!!!!!!!!!!!!!!!!!!!!!模块 Map 操作!!!!!!!!!!!!!!!!!!!!!!!
	//这个是只加入 moduleMap
	bool add_Module(_IdDataType moduleId , logic_BasicModule* modulePtr);
	bool add_Module(_IdDataType moduleId , int m_Type);
	bool del_Module(_IdDataType moduleId);
	logic_BasicModule* searchModule(_IdDataType moduleId);
	_IdDataType searchModule(logic_BasicModule* modulePtr);

	/////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	////!!!!!!!!!!!!!!!!!!!【对外接口】模块间操作!!!!!!!!!!!!!!!
	bool frontInsModule(int m_id,int post_id,int m_type); //前插，不允许后继为0
	bool appendModule(int m_id,int pre_id,int m_type); //直接后接，前驱为0代表新建树
	bool addLeafModule(int m_id,int pre_id,int m_type); //加一个叶子节点

	///////最麻烦的方法之一，还需要同步删除参数连线，还有 for 和 if（包括散开处理）
	bool delModule(int m_id);
	int getModulePreId(int m_id); //得到某一模块的前驱id
	std::vector<int > getModulePostId(int m_id);

	//////move 操作
	int frontInsSingMove(int cur_m_id,int post_m_id); //前插move，不允许后继为0
	int backInsSingMove(int cur_m_id,int pre_m_id); //后插move，前驱为0代表move到新建树
	int frontInsMultiMove(int cur_m_id,int post_m_id); //带祖先前插move，不允许后继为0
	int backInsMultiMove(int cur_m_id,int pre_m_id); //带孩子后插move，前驱为0代表move到新建树

	/////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	////!!!!!!!!!!!!!!!!!!!【对外接口】模块内部操作!!!!!!!!!!!!!!!

	std::string getModulePara(int type,int m_id,int p_id); //得到指定参数值
	void setModulePara(int m_id,int p_id,std::string p_value); //set指定参数值

	WinSwitcherType getModuleWinSwType(int m_id,int m_modeValue);
	std::string getModuleWinSwValue(int m_id);
	void setModuleWinSwValue(int m_id,std::string ws_value);

	int getModuleDaisyChainValue(int m_id);
	void setModuleDaisyChainValue(int m_id,int chain_value);

	std::vector<int > getModuleParamsIds(int m_id,int mode_value);

	int getModuleModeValue(int m_id);
	void setModuleModeValue(int m_id,int mode_id);

	/////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	////!!!!!!!!!!!!!!!!!!!【XmlIO】!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	std::map<int,logic_Tree*> getTreeMap(); //【XmlIO】
	std::map <int ,logic_BasicModule* > getModuleMap(); //【XmlIO】
	std::vector<logic_TreeNode *> getAllTreeNode(int rootID); //得到所有treenode list

	/////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//set & get
	int getID(); //ID不可修改

	void setProgramName(const std::string name);       //program name
	std::string getName();

	//获得最大 ModuleId
	int getMaxModuleId();

	std::vector<int> getAllTreeNodeId(int tree_id); //拿到指定树的所有孩子id列表


	///!!!!!!!!!!!!!!!!!!!!!!!!!!! \brief for if 模块操作
	/// 难点在 delete 上要消除里面的tree
	bool insertModuleIntoFor(int m_id,int pre_id,int m_type,int for_id);
	bool insertModuleIntoIf(int m_id,int pre_id,int m_type,int if_id,int branch_id);

	int getForActiveTree(int for_id); //for
	int getIfActiveTree(int if_id,int branch_id); //if

	void setForActiveTree(int for_id,int tree_id); //for
	void setIfActiveTree(int if_id,int branch_id,int tree_id); //if

	/// get set 某个 branch 参数
	int getIfBranchContentInt(int if_id,int branch_id); //get 指定 branch的int content
	std::string getIfBranchContentStr(int if_id,int branch_id); //string

	///// \返回不同错误代码，正常返回0，重载
	int setIfBranchContent(int if_id,int branch_id,int con_int);
	int setIfBranchContent(int if_id,int branch_id,std::string con_str); //重载 string

	//增删 if 分支
	int addIfBranch(int if_id);
	int delIfBranch(int if_id,int branch_id); //难点，需要删除分支中所有树

	int delTreeThroughId(int id); //通过一棵树id，删除树

	/// \brief 模块参数连线
	int paraConnect(int out_m_id,int out_para_id,int in_m_id,int in_para_id);
	//取消连线
	//可通过 isOut 来用outModule或者inModule删除
	void outParaDisconnect(int out_m_id,int out_para_id);
	void inParaDisconnect(int in_m_id,int in_para_id);

protected:

	std::map <_IdDataType,logic_Tree *> mvmu_TreeMap; // rootId 与 树实体的对应
	std::map <_IdDataType, logic_BasicModule *> mvmu_ModuleMap; //维护一个module总映射
	std::map <int ,logic_Tree * > mvmu_ModuleId_TreeMap; //维护每个 moduleID 和 tree 的映射

	std::map <logic_Tree * ,int > mvmi_TreeId_For_IfIdMap; //!!!!!!!!!!!!维护 treeId 和 For If 模块 Id 的映射表

	/////参数连线
	std::map<whPort, whPort > mvvu_Conn_From_ToMap; //维护 出发模块Port---结束模块Port 哈希表
	std::map<whPort, whPort > mvvu_Conn_To_FromMap; //维护 结束模块Port---出发模块Port，方便双向查找

	void Init();
	void prog_Destroy();

	void updateMId_TreeMap(logic_Tree *tree); //将一棵树中所有module tree映射改为当前tree
	void recurs_update(logic_Tree *tree,logic_TreeNode *some); //和 updateMId_TreeMap() 连用，递归更新

	void recurs_GetId(logic_TreeNode *some,std::vector<int> & L);
	void recurs_GetNode(logic_TreeNode *some,std::vector<logic_TreeNode *> & L);

	//完全删除一棵树所有节点模块的所有信息（各种实体map和connection map）
	void recurs_DelTreeNodeModule(logic_TreeNode *some);

private:
	int mvs_ProgId; //一个program，一个森林，project是森林的合集
	std::string mvs_ProgName;

};


#endif
