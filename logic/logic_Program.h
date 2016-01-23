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
#include "logic_ForModule.h"
#include "logic_IfModule.h"
#include "logic_whPort.h"
#include "logic_VarModule.h"

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

	/////!!!!!!!!!!!!!!!!!!!!!!!!!类内部操作!!!!!!!!!!!!!!!!!!!!!!!
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
	bool addLeafModule(int pre_id,int m_id); //加一个叶子节点

	///////最麻烦的方法之一，还需要同步删除参数连线，还有 for 和 if（包括散开处理）
	bool delModule(int m_id);
	int getModulePreId(int m_id); //得到某一模块的前驱id
	std::vector<int > getModulePostId(int m_id);

	//////move 操作
	int frontInsSingMove(int cur_m_id,int post_m_id); //前插move，不允许后继为0
	int backInsSingMove(int cur_m_id,int pre_m_id); //后插move，前驱为0代表move到新建树
	int frontInsMultiMove(int cur_m_id,int post_m_id); //带祖先前插move，不允许后继为0
	int backInsMultiMove(int cur_m_id,int pre_m_id); //带孩子后插move，前驱为0代表move到新建树

	int addLeafMove(int cur_m_id,int pre_m_id); //新增叶子move

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
	
	/// 向 for和if 中新加入模块
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

	void DelAllParaConnect(int id); //删除关于某一模块的所有连线

	///
	/// \brief 特殊处理for的move操作
	///
	int backInsSingMoveFor(int cur_m_id,int pre_m_id,int for_id);
	int frontInsSingMoveFor(int cur_m_id,int post_m_id,int for_id);
	int backInsMultiMoveFor(int cur_m_id,int pre_m_id,int for_id);
	int frontInsMultiMoveFor(int cur_m_id,int post_m_id,int for_id);
	int addLeafMoveFor(int cur_m_id,int pre_m_id,int for_id);

	//只在接到activeTree根节点的时候调用
	int appendActiveTreeMoveFor(int cur_m_id,int for_id); //单模块接入activeTree
	int addLeafActiveTreeMoveFor(int cur_m_id,int for_id); //activeTree直接添加叶子

	int appendActiveTreeInsertFor(int m_id,int m_type,int for_id); //单模块新插入activeTree

	///
	/// \brief 特殊处理if的move操作
	///
	int backInsSingMoveIf(int cur_m_id,int pre_m_id,int if_id,int branch_id);
	int frontInsSingMoveIf(int cur_m_id,int post_m_id,int if_id,int branch_id);
	int backInsMultiMoveIf(int cur_m_id,int pre_m_id,int if_id,int branch_id);
	int frontInsMultiMoveIf(int cur_m_id,int post_m_id,int if_id,int branch_id);
	int addLeafMoveIf(int cur_m_id,int pre_m_id,int if_id,int branch_id);

	//只在接到activeTree根节点的时候调用
	int appendActiveTreeMoveIf(int cur_m_id,int if_id,int branch_id); //单模块接入activeTree
	int addLeafActiveTreeMoveIf(int cur_m_id,int if_id,int branch_id); //activeTree直接添加叶子

	int appendActiveTreeInsertIf(int m_id,int m_type,int if_id,int branch_id); //单模块新插入activeTree

	//从prj初始化prog
	//初始化 “变量”map，v_map是引用
	void setInitVarMap(std::map<int  ,logic_VarModule*> &v_map);
	//初始化 initModule，init_m_map是副本
	void setInitModuleMap(std::map <int, logic_BasicModule *> init_m_map);

	///
	/// \brief 获取根节点
	/// \para 容器编号，如果是0，获取最外层root集合
	/// \return 根节点集合
	///
	std::vector<int > findRootsInContainer();
	std::vector<int > findRootsInContainer(int for_id);
	std::vector<int > findRootsInContainer(int if_id,int branch_id);

protected:

	///如果是 for if的activeTree，属于特殊的树，树根没有实体module
	///且 rootId = moduleId*100000+branchId，这种 tree 只维护mvmu_TreeMap
	std::map <_IdDataType,logic_Tree *> mvmu_TreeMap; // rootId 与 树实体的对应
	std::map <_IdDataType, logic_BasicModule *> mvmu_ModuleMap; //维护一个module总映射
	std::map <int ,logic_Tree * > mvmu_ModuleId_TreeMap; //维护每个 moduleID 和 tree 的映射

	//!!!!!!!!!!!!维护 treeId 和 For If 模块 Id 的映射表
	//表示tree在for和if中
	std::map <logic_Tree * ,int > mvmi_TreeId_For_IfIdMap;

	/////参数连线
	std::map<whPort, whPort > mvvu_Conn_From_ToMap; //维护 出发模块Port---结束模块Port 哈希表
	std::map<whPort, whPort > mvvu_Conn_To_FromMap; //维护 结束模块Port---出发模块Port，方便双向查找

	///////init module map
	std::map <int, logic_BasicModule *> initModuleMap;
	//变量（整个prj通用）
	std::map<_IdDataType ,logic_VarModule*> *prjVariety;

	void Init();
	void prog_Destroy();

	void updateMId_TreeMap(logic_Tree *tree); //将一棵树中所有module tree映射改为当前tree
	void recurs_update(logic_Tree *tree,logic_TreeNode *some); //和 updateMId_TreeMap() 连用，递归更新

	void recurs_GetId(logic_TreeNode *some,std::vector<int> & L);
	void recurs_GetNode(logic_TreeNode *some,std::vector<logic_TreeNode *> & L);

	//完全删除一棵树所有节点模块的所有信息（各种实体map和connection map）
	void recurs_DelTreeNodeModule(logic_TreeNode *some);

protected:
	int mvs_ProgId; //一个program，一个森林，project是森林的合集
	std::string mvs_ProgName;

	//通过id得到模块
	logic_ForModule* getForModuleById(int id);
	logic_IfModule* getIfModuleById(int id);

	//合成for和if放入tree map中的id
	inline int composeTreeId(int for_id);
	inline int composeTreeId(int if_id,int branch_id);

	//连线时检测：只有一种情况有问题，即连接自己的祖先
	//（其实判断这两个模块如果在一棵树就有问题）
	//para： cur_id是连线出口模块，another_id是被连接模块
	//
	int addLeafCheckPre(int cur_id,int another_id);

};


#endif
