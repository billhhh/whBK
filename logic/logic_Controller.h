/* 
* 
* function: logic层工作控制类，完成大部分逻辑工作
* 
* Date:2015-10-21
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_CONTROLLER_H_
#define _LOGIC_CONTROLLER_H_

#include <map>
#include <queue>
#include <list>
#include "logic_Project.h"


class logic_Controller
{
public:
	logic_Controller();

	std::map <int ,logic_Project* > getAllPrj(); // 【XmlIO】get 所有prj map，方便xml持久化
	int getCurPrjId(); 

	int ctrlNewPrj(); //新建project，返回projectID
	int ctrlNewProg();//新建program，返回programID
	void ctrlSetCurPrj(int id);
	void ctrlSetCurProg(int id);
	int ctrlGetCurPrj();//得到当前的prjId
	int ctrlNewModuleAddId();

	bool ctrlDeleteProgram(const std::string progName);//根据progName删除该program
	bool ctrlImportProgram(const std::string progPath);//根据progPath导入program
	bool ctrlExportProgram(const std::string progPath, int progId);//根据progPath,和programID导program文件
	std::vector<std::string> ctrlGetProgName(int prjID);//返回项目的所有program名称
	std::vector<VarProperty> ctrlGetVariety(int prjID);//返回项目的所有变量（自定义的变量结构）
	std::string ctrlCopyProgram(const std::string progName);//copy一个program，并且返回新的program name


	bool ctrlAppendModule(int pre_id,int m_type); //后插节点，传入前驱id，如果前驱为0，代表新建树
	bool ctrlFrontInsModule(int post_id,int m_type); //前插节点，不允许新建树时调用
	bool ctrlAddLeafModule(int pre_id,int m_id); //直接加一个叶子模块

	bool ctrlDelModule(int m_id);

	int ctrlGetPreId(int m_id); //查询模块前驱id
	std::vector<int > ctrlGetPostId(int m_id);

	int ctrlGetRootModuleId(int m_id);//查询m_id的所在树的根节点的模块id
	bool ctrlIsInSameTree(int cur_m_id, int other_m_id);//查询两个module是否在同一颗树内

	std::vector<int > ctrlGetForPostId(int for_m_id);//查询for模块的根节点-1的所有后继节点
	std::vector<int > ctrlGetIfBranchPostId(int if_id, int global_branch_id);//查询if模块的某个branch的所有后继节点

	int ctrlGetForEndPreId(int for_id);//查询for模块的-2节点的前驱
	int	ctrlGetIfEndPreId(int if_id, int ui_branch_id);//查询if模块的ui_branch_id的-2节点前驱

	std::string ctrlGetParameter(int type,int m_id,int p_id);
	void ctrlSetParameter(int m_id,int p_id,std::string p_value);

	WinSwitcherType ctrlGetWinSwType(int m_id,int m_modeValue); //找到特定Win的type
	std::string ctrlGetWinSwValue(int m_id);
	void ctrlSetWinSwValue(int m_id,std::string ws_value);

	int ctrlGetDaisyChainValue(int m_id);
	void ctrlSetDaisyChainValue(int m_id,int chain_value);

	std::vector<int > ctrlGetParamsIds(int m_id,int mode_value);

	int ctrlGetModeValue(int m_id);
	void ctrlSetModeValue(int m_id,int mode_id);

	int ctrlFrontInsSingMove(int cur_m_id,int post_m_id);
	int ctrlBackInsSingMove(int cur_m_id,int pre_m_id);

	int ctrlFrontInsMultiMove(int cur_m_id,int post_m_id);
	int ctrlBackInsMultiMove(int cur_m_id,int pre_m_id);
	int ctrlAddLeafMove(int cur_m_id,int pre_m_id);

	//IO*****************
	std::map <int, logic_BasicModule *> ctrlGetInitMap();

	//*********************
	///
	/// \brief for和if处理
	///        注意：ui_branch_id需要在逻辑层合成和分开
	/// \para 传入都是ui_branch_id，但是输入给下一级函数的是正确的branch_id
	///

	bool ctrlInsertModule_For(int pre_id,bool isFI,int m_type,int for_id); //insert into for
	bool ctrlInsertModule_If(int pre_id,bool isFI,int m_type,int if_id,int ui_branch_id); //insert into if

	int ctrlGetForActiveTree(int for_id); //for
	int ctrlGetIfActiveTree(int if_id,int ui_branch_id); //if

	void ctrlSetForActiveTree(int for_id,int tree_id); //for
	void ctrlSetIfActiveTree(int if_id,int ui_branch_id,int tree_id); //if

	int ctrlGetIfBranchContentInt(int if_id,int ui_branch_id); //get 指定 branch的int content
	std::string ctrlGetIfBranchContentStr(int if_id,int ui_branch_id); //string

	int ctrlSetIfBranchContent(int if_id,int ui_branch_id,int con_int);
	int ctrlSetIfBranchContent(int if_id,int ui_branch_id,std::string con_str); //重载 string

	//增删 if 分支
	int ctrlAddIfBranch(int if_id);
	int ctrlDelIfBranch(int if_id,int ui_branch_id); //难点，需要删除分支中所有树

	/// \brief 模块参数连线
	int ctrlParaConnect(int out_m_id,int out_para_id,int in_m_id,int in_para_id);
	//取消连线
	//可通过 isOut 来用outModule或者inModule删除
	void ctrlOutParaDisconnect(int out_m_id,int out_para_id);
	void ctrlInParaDisconnect(int in_m_id,int in_para_id);


	///
	/// \brief for与if的move操作
	///
	int ctrlMoveModuleFor(int cur_m_id,int other_m_id,int move_type,int for_id);
	int ctrlMoveModuleIf(int cur_m_id,int other_m_id,int move_type,int if_id,int ui_branch_id);

	///
	/// \brief 获取根节点
	/// \para 容器编号，如果是0，获取最外层root集合
	/// \return 根节点集合
	///
	std::vector<int > ctrlFindRootsInContainer(int containerId);


	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!持久化部分!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	bool ctrlSaveCurProject();
	bool ctrlSaveProject(const std::string fileName, int prjId);
	bool ctrlLoadProject(const std::string fileName);


	///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!compiler!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	logic_Program* ctrlGetCurProgram();

	// get\set当前program名称
	std::string ctrlGetCurProgName();
	void ctrlSetCurProgName(std::string name);

	// get\set当前项目名称
	std::string ctrlGetCurPrjName();
	void ctrlSetCurPrjName(std::string name);


	///调试函数
#pragma region debug
	//控制台输出该prj的所有树
	void debug_displayTree(logic_Project* prj);

#pragma endregion debug

	///
	/// \brief 我的模块
	///
	//session1：是否可以创建我的模块，前后端第一次会话
	//接口传id列表，返回是否可创建
	int ctrlCanMyBlocks(std::vector<int > ids);


//private变量
private:

	std::map <int ,logic_Project* > prjMap;
	int curPrjId;
	int curProgId;

	//!!!!!!!init module map，保存所有的初始化 Module 指针 map 副本!!!!!!!
	///
	/// \brief load from xml which is on the disk
	///
	std::map <int, logic_BasicModule *> mvmu_InitModuleMap; //加载在内存中module Init总map


//工具private函数
private:
	void Init();
	int getMaxPrjId(); //获得最大 PrjID，方便累计
	std::string genNewPrjName(int id); //生成新 prj 的名字
	std::string whIntToString(int i);

	///
	/// \brief 逻辑层，加解密 ui_branch_id
	///

	//加密
	int encryptBranchId(int if_id,int branch_id); //返回加密后id
	//解密
	void decryptBranchId(int ui_branch_id,int &if_id,int &branch_id);
	int decryptBranchId(int ui_branch_id); //直接返回 branch_id

	///init module map函数
	void initModuleMapFunc();


	///调试函数
	void debug_displayTreeUtility(logic_TreeNode* node);
};

#endif
