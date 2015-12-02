/* 
* 
* function: ��Ϣ�ӿ�
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
	MAX_VALUE = 0,//���ֵ
	MIN_VALUE, //��Сֵ
	INIT, //��ʼֵ
	CUR //��ǰֵ
};

enum MoveType
{
	BACK_SINGLE = 0, // ��ģ�� ��壨�����ߣ�
	FRONT_SINGLE,    // ��ģ�� ǰ�壨�����ߣ�
	BACK_MULTI,      // ��ģ�� ���
	FRONT_MULTI      // ��ģ�� ǰ��
};

class msgInterface
{

public:

	///!!!!!!!!!!!!!!!!!!!!!!!!!�½�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/// \brief �½�project
	/// \return ��prjID
	int newPrj();

	/// \brief ��һ��project
	void openPrj();

	/// \brief �½�program
	/// \return ��ID
	int newProg();

	/// \brief �½�ModuleID++
	/// \return ��ID
	int newModuleAddId();

	/// \brief �ı�curPrj��curProg
	void setCurPrj(int prjID);
	void setCurProg(int progID);



	///!!!!!!!!!!!!!!!!!!!!!!!!!ģ���ڲ�����!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/// \brief get��set����
	std::string getParameter(GetPType type,int m_id,int p_id);
	void setParameter(int m_id,int p_id,std::string p_value);

	/// \brief get��set�˿�ѡ����
	WinSwitcherType getWinSwType(int m_id,int m_modeValue);
	std::string getWinSwValue(int m_id);
	void setWinSwValue(int m_id,std::string ws_value);

	/// \brief get��set����
	int getDaisyChainValue(int m_id);
	void setDaisyChainValue(int m_id,int chain_value);

	/// \brief get��ʾԤ��
	bool getPreView(int m_id);

	/// \brief ��ѯ����IDs������ id �б�
	std::vector<int > getParamsIds(int m_id,int mode_value);

	/// \brief get��setģʽѡ����
	int getModeValue(int m_id);
	void setModeValue(int m_id,int mode_id);


	///!!!!!!!!!!!!!!!!!!!!!!!!!ģ������!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/// \brief ���ģ��
	/// \para ǰ������ģ��id����ǰ�壨true�����Ǻ�壬���������͵�ģ���¼���
	/// �����壬ǰ��idΪ0���൱�ڷſ�
	bool insertModule(int m_id,bool isFI,int m_type);

	bool addLeafModule(int pre_id,int m_type);
	
	/// \brief ɾ��ģ��
	bool deleteModule(int m_id);

	/// \brief �ƶ�ģ��ģ��
	/// \para cur_m_id ָ���Ǳ��϶�������ģ��id��other_m_id ָ���Ǳ������ܵ�ģ��id
	/// \return ���ش����ţ���������0
	int moveModule(int cur_m_id,int other_m_id,MoveType move_type);

	/// \brief ģ���������
	int paraConnect(int out_m_id,int out_para_id,int in_m_id,int in_para_id);
	//ȡ�����ߣ���ͨ�� isOut ����outModule����inModuleɾ��
	void paraDisconnect(int m_id,int para_id,bool isOut);

	/// \brief ��ѯǰ���ͺ��
	int getPreId(int m_id);
	std::vector<int > getPostId(int m_id);


	/// \brief for ifģ�����!!!!!!

	//bool insertModule(int m_id,bool isFI,int m_type,int parent_id,int branch_id); // Ĭ�ϲ�����������

	///���� insertModule
	/// parent_id ���������һ��for��
	bool insertModule(int m_id,bool isFI,int m_type,int for_id);
	/// ������һ�� if ����һ����֧��
	bool insertModule(int m_id,bool isFI,int m_type,int if_id,int branch_id);

	//���ص�ǰ������id��ע������id��
	int getActiveTree(int for_id); //for
	int getActiveTree(int if_id,int branch_id); //if

	void setActiveTree(int for_id,int tree_id); //for
	void setActiveTree(int if_id,int branch_id,int tree_id); //if

	/// get set ĳ�� branch ����
	int getIfBranchContentInt(int if_id,int branch_id); //get ָ�� branch��int content
	std::string getIfBranchContentStr(int if_id,int branch_id); //string
	///// \���ز�ͬ������룬��������0������
	int setIfBranchContent(int if_id,int branch_id,int con_int);
	int setIfBranchContent(int if_id,int branch_id,std::string con_str); //���� string

	//��ɾ if ��֧
	int addIfBranch(int if_id);
	int delIfBranch(int if_id,int branch_id); //�ѵ㣬��Ҫɾ����֧��������

	///����1 ��ʱѡ��
	///for if move
	///ֻ��ǰ��Ϊ0��ʱ��ʹ�ã��������ǰ����Ϊ0������ǰ��ĺ�����Ϊ0������ moveModule
	int moveModuleForIf(int cur_m_id,int other_m_id,MoveType move_type,int container_id,int ui_branch_id);

	///����2 ����UI���е�ԭ�Ӳ�����
	///��module���롢ɾ�� for �� if
	//int moveInModule(int m_id,int container_id,int ui_branch_id);
	//int moveOutModule(int m_id); //for����ifͬһ������

	/// \brief �����ҵ�ģ��

protected:

private:
	logic_Controller ctrl;
};

#endif
