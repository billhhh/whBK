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
#include <list>
#include "logic/logic_Controller.h"
#include "logic/logic_BasicPara.h"

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

	/// \brief �õ���ǰ��curPrjId
	int getCurPrj();

	// get\set��ǰprogram����
	std::string getCurProgName();
	void setCurProgName(std::string name);

	// get\set��ǰ��Ŀ����
	std::string getCurPrjName();
	void setCurPrjName(std::string name);

	/// !!!!!!!!!!!!!!!!!!!!!!!!!!��Ŀ���Բ���!!!!!!!!!!!!!!!!!!!!!!!!!
	/// \brief get��Ŀ���Ե���Ϣ
	/// get��������
	std::vector<std::string> getProgName(int prjID);
	/// get �������ͺ�����
	std::vector<VarProperty> getVariety(int prjID);
	std::string copyProgram(const std::string progName);
	bool deleteProgram(const std::string progName);
	bool importProgarm(std::string progName);//progName������program��·������
	bool exportProgram(std::string progPath, int progId);//����ǰ��Ŀ�µ�progId��program�����ɳ־û��ļ�

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

	/// \brief ��ѯ���ڵ�ģ��id
	int getRootModuleId(int m_id);

	/// \brief �ж�����module�Ƿ���ͬһ������
	bool isInSameTree(int cur_m_id, int other_m_id);

	/// \brief!!!!!!!!!!!!!!!!!! for,if ģ��ǰ����̲�ѯ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//get forģ����ڵ�ĺ�̽ڵ�
	std::vector<int > getForRootPostId(int m_id);
	//get for��-2����ģ���ǰ��
	int getForEndPreId(int m_id);
	//get ifģ���ĳ��branch�ĺ�̽ڵ�
	//ui_branch_id��ifģ��ȫ�ֵ�branchid
	std::vector<int > getIfBranchPostId(int if_id, int ui_branch_id);
	//get if��ui_branch_id��-2�ڵ��ǰ��
	//�������ֵ��0��ʾ������Ϣ����
	int getIfEndPreId(int if_id,int ui_branch_id);


	/// \brief!!!!!!!!!!!!!!!!!! for ifģ�����!!!!!!
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
	std::vector<int> findRootsInContainer(int containerId);

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�־û�����!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	bool saveProject(const std::string fileName, int prjId);
	bool loadProject(const std::string fileName);



	///!!!!!!!!!!!!!!!!!!!!!!!!!!!!compile!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	///��controller����Ȩ�������벿��
	logic_Controller& getController();

	///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



	///For degug
	//��ӡ��ǰprj��̨������Program��������
	void debug_displayBackgroundTree();

	///
	/// \brief �����ҵ�ģ��
	///

	//session1���Ƿ���Դ����ҵ�ģ�飬ǰ��˵�һ�λỰ
	//�ӿڴ�id�б������Ƿ�ɴ���
	int canMyBlocks(std::vector<int > ids);
	//�õ������ҵ�ģ����Ӳ����б�
	std::vector<logic_BasicPara > getMyBlocksPara(std::vector<int > ids);

	//session2�������ɺ�ǰ��˵ڶ��λỰ
	//ǰ�˴�����̨������vector���ҵ�ģ��name���ҵ�ģ������
	//��̨����ǰ�ˣ��ҵ�ģ��id���ײ�id��
	int buildMyBlocks(std::string mbname,std::string mbdes,std::vector<logic_BasicPara > plist);

protected:

private:
	logic_Controller ctrl;
};

#endif
