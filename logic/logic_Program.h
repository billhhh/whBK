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
#include "logic_Tree.h"
#include "logic_BasicModule.h"
#include "logic_Global.h"
#include "logic_ModulePortLine.h"

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

	bool delModule(int m_id);
	int getModulePreId(int m_id); //得到某一模块的前驱id
	std::vector<int > getModulePostId(int m_id);

	//////move 操作
	int frontInsSingMove(int cur_m_id,int post_m_id); //前插move
	int backInsSingMove(int cur_m_id,int pre_m_id); //后插move
	int frontInsMultiMove(int cur_m_id,int post_m_id); //带祖先前插move
	int backInsMultiMove(int cur_m_id,int pre_m_id); //带孩子后插move

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

protected:
	///////map[0] == NULL 防止 getMaxXXXId() 方法找不到，所有的 map 都沿用这个办法
	std::map <_IdDataType,logic_Tree *> mvmu_TreeMap;
	std::map <_IdDataType, logic_BasicModule *> mvmu_ModuleMap; //维护一个module总映射
	std::map <int ,logic_Tree * > mvmu_ModuleId_TreeMap; //维护每个 moduleID 和 tree 的映射

	std::vector<logic_ModulePortLine *> mvvu_ModulePortLineList; //连线表
	std::map <int ,int > mvmi_TreeId_For_IfIdMap; //!!!!!!!!!!!!维护 treeId 和 For If 模块 Id 的映射表

	void Init();
	void prog_Destroy();

	void updateMId_TreeMap(logic_Tree *tree); //将一棵树中所有module tree映射改为当前tree
	void recurs_update(logic_Tree *tree,logic_TreeNode *some); //和 updateMId_TreeMap() 连用，递归更新

	void recurs_GetId(logic_TreeNode *some,std::vector<int> & L);
	void recurs_GetNode(logic_TreeNode *some,std::vector<logic_TreeNode *> & L);

	//专注解决 for 模块的添加和删除
	void handleForAdd();
	void handleForDel();

private:
	int mvs_ProgId; //一个program，一个森林，project是森林的合集
	std::string mvs_ProgName;

};


#endif
