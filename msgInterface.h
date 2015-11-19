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
	//bool insertModule(int m_id,bool isFI,int m_type,int parent_id,int branch_id); //���� for if

	////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/// \brief for ifģ�飬����
	/// parent_id ���������һ��for��
	bool insertModule(int m_id,bool isFI,int m_type,int for_id);
	/// branch_id Ĭ�ϲ���Ϊ0��for ����Ϊ0�������������һ�� if ����һ����֧��
	bool insertModule(int m_id,bool isFI,int m_type,int if_id,int branch_id);
	////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	bool addLeafModule(int pre_id,int m_type);
	
	/// \brief ɾ��ģ��
	bool deleteModule(int m_id);

	/// \brief �ƶ�ģ��ģ��
	/// \para cur_m_id ָ���Ǳ��϶�������ģ��id��other_m_id ָ���Ǳ������ܵ�ģ��id
	/// \return ���ش����ţ���������0
	int moveModule(int cur_m_id,int other_m_id,MoveType move_type);

	/// \brief ģ���������
	void paraConnect(int out_m_id,int out_para_id,int in_m_id,int in_para_id);

	/// \brief ��ѯǰ���ͺ��
	int getPreId(int m_id);
	std::vector<int > getPostId(int m_id);

	/// \brief �����ҵ�ģ��

protected:

private:
	logic_Controller ctrl;
};

#endif
