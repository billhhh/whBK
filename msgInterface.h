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
	FRONT_MULTI,     // ��ģ�� ǰ��
	ADD_LEAF         //����һ��Ҷ��
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

	bool addLeafModule(int pre_id,int m_id);
	
	/// \brief ɾ��ģ��
	bool deleteModule(int m_id);

	/// \brief �ƶ�ģ��ģ��
	/// \para cur_m_id ָ���Ǳ��϶�������ģ��id��other_m_id ָ���Ǳ������ܵ�ģ��id
	/// \return ���ش����ţ���������0
	int moveModule(int cur_m_id,int other_m_id,MoveType move_type);

	/// \brief ģ���������
	int paraConnect(int out_m_id,int out_para_id,int in_m_id,int in_para_id);
	//ȡ�����ߣ�ֻ��ͨ��inModuleɾ��
	void paraDisconnect(int m_id,int para_id);

	/// \brief ��ѯǰ���ͺ��
	int getPreId(int m_id);
	std::vector<int > getPostId(int m_id);


	/// \brief for ifģ�����!!!!!!

	///
	/// \brief �˴��ر�ע�⣬ui_branch_id��UI��branch id���ǰ�һ��32λ�����ֳɣ�
	///		   ��16λ��moduleId����15λ��branchId
	///


	//bool insertModule(int m_id,bool isFI,int m_type,int parent_id,int ui_branch_id); // Ĭ�ϲ�����������

	///���� insertModule
	/// parent_id ���������һ��for��
	bool insertModule(int m_id,bool isFI,int m_type,int for_id);
	/// ������һ�� if ����һ����֧��
	bool insertModule(int m_id,bool isFI,int m_type,int if_id,int ui_branch_id);


	///!!!!!!!!!!!!!!!!! ���� !!!!!!!!!!!!!!!!!!!!!!
	//���ص�ǰ������id��ע������id��
	int getActiveTree(int for_id); //for
	int getActiveTree(int if_id,int ui_branch_id); //if

	void setActiveTree(int for_id,int tree_id); //for
	void setActiveTree(int if_id,int ui_branch_id,int tree_id); //if
	///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/// get set ĳ�� branch ����
	int getIfBranchContentInt(int if_id,int ui_branch_id); //get ָ�� branch��int content
	std::string getIfBranchContentStr(int if_id,int ui_branch_id); //string
	///// \���ز�ͬ������룬��������0������
	int setIfBranchContent(int if_id,int ui_branch_id,int con_int);
	int setIfBranchContent(int if_id,int ui_branch_id,std::string con_str); //���� string

	//��ɾ if ��֧
	int addIfBranch(int if_id);
	int delIfBranch(int if_id,int ui_branch_id); //�ѵ㣬��Ҫɾ����֧��������

	///����1 ��ʱѡ��
	///��for if ��ص����� move
	/// \para cur_m_id ָ���Ǳ��϶�������ģ��id��other_m_id ָ���Ǳ������ܵ�ģ��id
	/// \para move_type �ƶ�ģʽ��container_id Ŀ�ĵ�����id��ui_branch_id ǰ�˵��������id
	/// \return ���ش����ţ���������0
	int moveModuleForIf(int cur_m_id,int other_m_id,MoveType move_type,int container_id,int ui_branch_id);

	///����2 ����UI���е�ԭ�Ӳ�����
	///��module���롢ɾ�� for �� if
	//int moveInModule(int m_id,int container_id,int ui_branch_id);
	//int moveOutModule(int m_id); //for����ifͬһ������

	///
	/// \brief ��ȡ���ڵ�
	/// \para ������ţ������0����ȡ�����root����
	/// \return ���ڵ㼯��
	///
	std::vector<int > findRootsInContainer(int containerId);

	//�ҵ����������ڵ�
	std::vector<int > findRootsInContainerActive(int containerId);

	///
	/// \brief ��Ŀ����
	///
	std::string getPrjName();
	int setPrjName(std::string name); //���ش�����Ϣ

	std::string getPrjDescription();
	int setPrjDescription(std::string desc);

	std::string getPrjPhotoPath();
	int setPrjPhotoPath(std::string path);

	//����ģʽ����
	int getPrjDaisyChainMode(); //��0���أ�����1��������<0 ����
	int setPrjDaisyChainMode(int mode);

	//��ȡprog�����б�
	std::vector <int, std::string> getPrjProgNameMap();
	int delPrjProgThroughId(int id); //ɾ��prog���

	//��ȡ ���� �����б�
	std::vector <int, std::string> getPrjVarietyNameMap();
	int delPrjVarietyThroughId(int id);

	//��ȡ graph �����б�
	std::vector <int, std::string> getPrjGraphNameMap();
	int delPrjGraphThroughId(int id);

	/// \brief �����ҵ�ģ��

protected:

private:
	logic_Controller ctrl;
};

#endif
