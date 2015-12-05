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
#include "logic_Project.h"

class logic_Controller
{
public:
	explicit logic_Controller();

	std::map <int ,logic_Project* > getAllPrj(); // 【XmlIO】get 所有prj map，方便xml持久化

	int ctrlNewPrj(); //新建project，返回projectID
	int ctrlNewProg();//新建program，返回programID
	void ctrlSetCurPrj(int id);
	void ctrlSetCurProg(int id);
	int ctrlNewModuleAddId();

	bool ctrlAppendModule(int pre_id,int m_type); //后插节点，传入前驱id，如果前驱为0，代表新建树
	bool ctrlFrontInsModule(int post_id,int m_type); //前插节点，不允许新建树时调用
	bool ctrlAddLeafModule(int pre_id,int m_type); //直接加一个叶子模块

	bool ctrlDelModule(int m_id);

	int ctrlGetPreId(int m_id); //查询模块前驱id
	std::vector<int > ctrlGetPostId(int m_id);

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

//重要private函数
private:
	void Init();
	int getMaxPrjId(); //获得最大 PrjID，方便累计
	std::string genNewPrjName(int id); //生成新 prj 的名字

	std::map <int ,logic_Project* > prjMap;
	int curPrjId;
	int curProgId;

//工具private函数
private:
	std::string whIntToString(int i);

	std::map <_IdDataType, logic_BasicModule *> mvmu_InitModuleMap; //加载在内存中module Init总map

	///
	/// \brief 逻辑层，加解密 ui_branch_id
	///

	//加密
	int encryptBranchId(int if_id,int branch_id); //返回加密后id
	//解密
	void decryptBranchId(int ui_branch_id,int &if_id,int &branch_id);
	int decryptBranchId(int ui_branch_id); //直接返回 branch_id

};

#endif
