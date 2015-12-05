/* 
* 
* function: logic�㹤�������࣬��ɴ󲿷��߼�����
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

	std::map <int ,logic_Project* > getAllPrj(); // ��XmlIO��get ����prj map������xml�־û�

	int ctrlNewPrj(); //�½�project������projectID
	int ctrlNewProg();//�½�program������programID
	void ctrlSetCurPrj(int id);
	void ctrlSetCurProg(int id);
	int ctrlNewModuleAddId();

	bool ctrlAppendModule(int pre_id,int m_type); //���ڵ㣬����ǰ��id�����ǰ��Ϊ0�������½���
	bool ctrlFrontInsModule(int post_id,int m_type); //ǰ��ڵ㣬�������½���ʱ����
	bool ctrlAddLeafModule(int pre_id,int m_type); //ֱ�Ӽ�һ��Ҷ��ģ��

	bool ctrlDelModule(int m_id);

	int ctrlGetPreId(int m_id); //��ѯģ��ǰ��id
	std::vector<int > ctrlGetPostId(int m_id);

	std::string ctrlGetParameter(int type,int m_id,int p_id);
	void ctrlSetParameter(int m_id,int p_id,std::string p_value);

	WinSwitcherType ctrlGetWinSwType(int m_id,int m_modeValue); //�ҵ��ض�Win��type
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
	/// \brief for��if����
	///        ע�⣺ui_branch_id��Ҫ���߼���ϳɺͷֿ�
	/// \para ���붼��ui_branch_id�������������һ������������ȷ��branch_id
	///

	bool ctrlInsertModule_For(int pre_id,bool isFI,int m_type,int for_id); //insert into for
	bool ctrlInsertModule_If(int pre_id,bool isFI,int m_type,int if_id,int ui_branch_id); //insert into if

	int ctrlGetForActiveTree(int for_id); //for
	int ctrlGetIfActiveTree(int if_id,int ui_branch_id); //if

	void ctrlSetForActiveTree(int for_id,int tree_id); //for
	void ctrlSetIfActiveTree(int if_id,int ui_branch_id,int tree_id); //if

	int ctrlGetIfBranchContentInt(int if_id,int ui_branch_id); //get ָ�� branch��int content
	std::string ctrlGetIfBranchContentStr(int if_id,int ui_branch_id); //string

	int ctrlSetIfBranchContent(int if_id,int ui_branch_id,int con_int);
	int ctrlSetIfBranchContent(int if_id,int ui_branch_id,std::string con_str); //���� string

	//��ɾ if ��֧
	int ctrlAddIfBranch(int if_id);
	int ctrlDelIfBranch(int if_id,int ui_branch_id); //�ѵ㣬��Ҫɾ����֧��������

	/// \brief ģ���������
	int ctrlParaConnect(int out_m_id,int out_para_id,int in_m_id,int in_para_id);
	//ȡ������
	//��ͨ�� isOut ����outModule����inModuleɾ��
	void ctrlOutParaDisconnect(int out_m_id,int out_para_id);
	void ctrlInParaDisconnect(int in_m_id,int in_para_id);


	///
	/// \brief for��if��move����
	///
	int ctrlMoveModuleFor(int cur_m_id,int other_m_id,int move_type,int for_id);
	int ctrlMoveModuleIf(int cur_m_id,int other_m_id,int move_type,int if_id,int ui_branch_id);

//��Ҫprivate����
private:
	void Init();
	int getMaxPrjId(); //������ PrjID�������ۼ�
	std::string genNewPrjName(int id); //������ prj ������

	std::map <int ,logic_Project* > prjMap;
	int curPrjId;
	int curProgId;

//����private����
private:
	std::string whIntToString(int i);

	std::map <_IdDataType, logic_BasicModule *> mvmu_InitModuleMap; //�������ڴ���module Init��map

	///
	/// \brief �߼��㣬�ӽ��� ui_branch_id
	///

	//����
	int encryptBranchId(int if_id,int branch_id); //���ؼ��ܺ�id
	//����
	void decryptBranchId(int ui_branch_id,int &if_id,int &branch_id);
	int decryptBranchId(int ui_branch_id); //ֱ�ӷ��� branch_id

};

#endif
