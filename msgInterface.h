/* 
* 
* function: 消息接口
* 
* Date:2015-10-21
* 
*    Author: Bill Wang
*/

#ifndef _MSG_INTERFACE_H_
#define _MSG_INTERFACE_H_

#include <vector>
#include <string>
#include "logic/logic_Controller.h"

enum GetPType{
	MAX_VALUE = 0,//最大值
	MIN_VALUE, //最小值
	INIT, //初始值
	CUR //当前值
};

enum MoveType
{
	BACK_SINGLE = 0, // 单模块 后插（不带线）
	FRONT_SINGLE,    // 单模块 前插（不带线）
	BACK_MULTI,      // 多模块 后插
	FRONT_MULTI,     // 多模块 前插
	ADD_LEAF         //增加一个叶子
};

class msgInterface
{

public:

	///!!!!!!!!!!!!!!!!!!!!!!!!!新建!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/// \brief 新建project
	/// \return 新prjID
	int newPrj();

	/// \brief 打开一个project
	void openPrj();

	/// \brief 新建program
	/// \return 新ID
	int newProg();

	/// \brief 新建ModuleID++
	/// \return 新ID
	int newModuleAddId();

	/// \brief 改变curPrj和curProg
	void setCurPrj(int prjID);
	void setCurProg(int progID);



	///!!!!!!!!!!!!!!!!!!!!!!!!!模块内部操作!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/// \brief get、set参数
	std::string getParameter(GetPType type,int m_id,int p_id);
	void setParameter(int m_id,int p_id,std::string p_value);

	/// \brief get、set端口选择器
	WinSwitcherType getWinSwType(int m_id,int m_modeValue);
	std::string getWinSwValue(int m_id);
	void setWinSwValue(int m_id,std::string ws_value);

	/// \brief get、set菊链
	int getDaisyChainValue(int m_id);
	void setDaisyChainValue(int m_id,int chain_value);

	/// \brief get显示预览
	bool getPreView(int m_id);

	/// \brief 查询参数IDs，返回 id 列表
	std::vector<int > getParamsIds(int m_id,int mode_value);

	/// \brief get、set模式选择器
	int getModeValue(int m_id);
	void setModeValue(int m_id,int mode_id);


	///!!!!!!!!!!!!!!!!!!!!!!!!!模块间操作!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/// \brief 添加模块
	/// \para 前驱或后继模块id，是前插（true）还是后插，是哪种类型的模块新加入
	/// 如果后插，前驱id为0，相当于放空
	bool insertModule(int m_id,bool isFI,int m_type);

	bool addLeafModule(int pre_id,int m_id);
	
	/// \brief 删除模块
	bool deleteModule(int m_id);

	/// \brief 移动模块模块
	/// \para cur_m_id 指的是被拖动的主动模块id，other_m_id 指的是被动接受的模块id
	/// \return 返回错误编号，正常返回0
	int moveModule(int cur_m_id,int other_m_id,MoveType move_type);

	/// \brief 模块参数连线
	int paraConnect(int out_m_id,int out_para_id,int in_m_id,int in_para_id);
	//取消连线，只能通过inModule删除
	void paraDisconnect(int m_id,int para_id);

	/// \brief 查询前驱和后继
	int getPreId(int m_id);
	std::vector<int > getPostId(int m_id);


	/// \brief for if模块操作!!!!!!

	///
	/// \brief 此处特别注意，ui_branch_id是UI的branch id，是把一个32位整数分成：
	///		   高16位做moduleId，低15位做branchId
	///


	//bool insertModule(int m_id,bool isFI,int m_type,int parent_id,int ui_branch_id); // 默认参数方法作废

	///重载 insertModule
	/// parent_id 代表放入哪一个for中
	bool insertModule(int m_id,bool isFI,int m_type,int for_id);
	/// 放入哪一个 if 的哪一个分支中
	bool insertModule(int m_id,bool isFI,int m_type,int if_id,int ui_branch_id);


	///!!!!!!!!!!!!!!!!! 废弃 !!!!!!!!!!!!!!!!!!!!!!
	//返回当前激活树id【注意是树id】
	int getActiveTree(int for_id); //for
	int getActiveTree(int if_id,int ui_branch_id); //if

	void setActiveTree(int for_id,int tree_id); //for
	void setActiveTree(int if_id,int ui_branch_id,int tree_id); //if
	///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/// get set 某个 branch 参数
	int getIfBranchContentInt(int if_id,int ui_branch_id); //get 指定 branch的int content
	std::string getIfBranchContentStr(int if_id,int ui_branch_id); //string
	///// \返回不同错误代码，正常返回0，重载
	int setIfBranchContent(int if_id,int ui_branch_id,int con_int);
	int setIfBranchContent(int if_id,int ui_branch_id,std::string con_str); //重载 string

	//增删 if 分支
	int addIfBranch(int if_id);
	int delIfBranch(int if_id,int ui_branch_id); //难点，需要删除分支中所有树

	///方案1 暂时选定
	///跟for if 相关的所有 move
	/// \para cur_m_id 指的是被拖动的主动模块id，other_m_id 指的是被动接受的模块id
	/// \para move_type 移动模式，container_id 目的地容器id，ui_branch_id 前端的奇葩设计id
	/// \return 返回错误编号，正常返回0
	int moveModuleForIf(int cur_m_id,int other_m_id,MoveType move_type,int container_id,int ui_branch_id);

	///方案2 （给UI进行的原子操作）
	///将module加入、删除 for 和 if
	//int moveInModule(int m_id,int container_id,int ui_branch_id);
	//int moveOutModule(int m_id); //for或者if同一个函数

	///
	/// \brief 获取根节点
	/// \para 容器编号，如果是0，获取最外层root集合
	/// \return 根节点集合
	///
	std::vector<int > findRootsInContainer(int containerId);

	//找到激活树根节点
	std::vector<int > findRootsInContainerActive(int containerId);

	///
	/// \brief 项目属性
	///
	std::string getPrjName();
	int setPrjName(std::string name); //返回错误信息

	std::string getPrjDescription();
	int setPrjDescription(std::string desc);

	std::string getPrjPhotoPath();
	int setPrjPhotoPath(std::string path);

	//菊链模式开关
	int getPrjDaisyChainMode(); //是0（关）或者1（开），<0 错误
	int setPrjDaisyChainMode(int mode);

	//获取prog名字列表
	std::vector <int, std::string> getPrjProgNameMap();
	int delPrjProgThroughId(int id); //删除prog编号

	//获取 变量 名字列表
	std::vector <int, std::string> getPrjVarietyNameMap();
	int delPrjVarietyThroughId(int id);

	//获取 graph 名字列表
	std::vector <int, std::string> getPrjGraphNameMap();
	int delPrjGraphThroughId(int id);

	/// \brief 创建我的模块

protected:

private:
	logic_Controller ctrl;
};

#endif
