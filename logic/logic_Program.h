/* 
* 
* function: �߼���ɭ����֯�ṹ
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

typedef struct structPort
{
	int moduleId;
	int paraId;

	bool operator < (const structPort &port) const
	{
		if( moduleId < port.moduleId ) { //С��ֱ�ӷ���true
			return true;
		}else if( moduleId > port.moduleId ) { //���ڷ���false
			return false;
		}else {

			//���moduleIdһ���������Ƚ�paraId�������ܶ�һ��
			if( paraId < port.paraId )
				return true;
			else if(paraId > port.paraId)
				return false;
			else
				assert(false);
		}
	}

}whPort;  //һ�����ڶ��壬��ȫ����һ��port

class logic_Program //��Ч��ɭ��
{
public:

	explicit logic_Program(int id, std::string prog_name);
	virtual ~logic_Program();


	/////!!!!!!!!!!!!!!!!!!!!!!!!!������!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	bool add_Tree(_IdDataType rootId); //���һ�� root IDΪid����
	bool add_Tree(logic_Tree * t);
	bool del_Tree(_IdDataType rootId);
	logic_Tree* search_Tree(_IdDataType rootId);
	_IdDataType search_Tree(logic_Tree* treePtr); //������ָ����ID

	logic_Tree* getTreeFromId(int m_id); //ͨ��һ��ģ��id���ҵ���������ͨ��Mapӳ��������

	/////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/////!!!!!!!!!!!!!!!!!!!!!!!!!ģ�� Map ����!!!!!!!!!!!!!!!!!!!!!!!
	//�����ֻ���� moduleMap
	bool add_Module(_IdDataType moduleId , logic_BasicModule* modulePtr);
	bool add_Module(_IdDataType moduleId , int m_Type);
	bool del_Module(_IdDataType moduleId);
	logic_BasicModule* searchModule(_IdDataType moduleId);
	_IdDataType searchModule(logic_BasicModule* modulePtr);

	/////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	////!!!!!!!!!!!!!!!!!!!������ӿڡ�ģ������!!!!!!!!!!!!!!!
	bool frontInsModule(int m_id,int post_id,int m_type); //ǰ�壬��������Ϊ0
	bool appendModule(int m_id,int pre_id,int m_type); //ֱ�Ӻ�ӣ�ǰ��Ϊ0�����½���
	bool addLeafModule(int m_id,int pre_id,int m_type); //��һ��Ҷ�ӽڵ�

	///////���鷳�ķ���֮һ������Ҫͬ��ɾ���������ߣ����� for �� if������ɢ������
	bool delModule(int m_id);
	int getModulePreId(int m_id); //�õ�ĳһģ���ǰ��id
	std::vector<int > getModulePostId(int m_id);

	//////move ����
	int frontInsSingMove(int cur_m_id,int post_m_id); //ǰ��move����������Ϊ0
	int backInsSingMove(int cur_m_id,int pre_m_id); //���move��ǰ��Ϊ0����move���½���
	int frontInsMultiMove(int cur_m_id,int post_m_id); //������ǰ��move����������Ϊ0
	int backInsMultiMove(int cur_m_id,int pre_m_id); //�����Ӻ��move��ǰ��Ϊ0����move���½���

	/////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	////!!!!!!!!!!!!!!!!!!!������ӿڡ�ģ���ڲ�����!!!!!!!!!!!!!!!

	std::string getModulePara(int type,int m_id,int p_id); //�õ�ָ������ֵ
	void setModulePara(int m_id,int p_id,std::string p_value); //setָ������ֵ

	WinSwitcherType getModuleWinSwType(int m_id,int m_modeValue);
	std::string getModuleWinSwValue(int m_id);
	void setModuleWinSwValue(int m_id,std::string ws_value);

	int getModuleDaisyChainValue(int m_id);
	void setModuleDaisyChainValue(int m_id,int chain_value);

	std::vector<int > getModuleParamsIds(int m_id,int mode_value);

	int getModuleModeValue(int m_id);
	void setModuleModeValue(int m_id,int mode_id);

	/////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	////!!!!!!!!!!!!!!!!!!!��XmlIO��!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	std::map<int,logic_Tree*> getTreeMap(); //��XmlIO��
	std::map <int ,logic_BasicModule* > getModuleMap(); //��XmlIO��
	std::vector<logic_TreeNode *> getAllTreeNode(int rootID); //�õ�����treenode list

	/////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//set & get
	int getID(); //ID�����޸�

	void setProgramName(const std::string name);       //program name
	std::string getName();

	//������ ModuleId
	int getMaxModuleId();

	std::vector<int> getAllTreeNodeId(int tree_id); //�õ�ָ���������к���id�б�


	///!!!!!!!!!!!!!!!!!!!!!!!!!!! \brief for if ģ�����
	/// �ѵ��� delete ��Ҫ���������tree
	bool insertModuleIntoFor(int m_id,int pre_id,int m_type,int for_id);
	bool insertModuleIntoIf(int m_id,int pre_id,int m_type,int if_id,int branch_id);

	int getForActiveTree(int for_id); //for
	int getIfActiveTree(int if_id,int branch_id); //if

	void setForActiveTree(int for_id,int tree_id); //for
	void setIfActiveTree(int if_id,int branch_id,int tree_id); //if

	/// get set ĳ�� branch ����
	int getIfBranchContentInt(int if_id,int branch_id); //get ָ�� branch��int content
	std::string getIfBranchContentStr(int if_id,int branch_id); //string

	///// \���ز�ͬ������룬��������0������
	int setIfBranchContent(int if_id,int branch_id,int con_int);
	int setIfBranchContent(int if_id,int branch_id,std::string con_str); //���� string

	//��ɾ if ��֧
	int addIfBranch(int if_id);
	int delIfBranch(int if_id,int branch_id); //�ѵ㣬��Ҫɾ����֧��������

	int delTreeThroughId(int id); //ͨ��һ����id��ɾ����

	/// \brief ģ���������
	int paraConnect(int out_m_id,int out_para_id,int in_m_id,int in_para_id);
	//ȡ������
	//��ͨ�� isOut ����outModule����inModuleɾ��
	void outParaDisconnect(int out_m_id,int out_para_id);
	void inParaDisconnect(int in_m_id,int in_para_id);

protected:

	std::map <_IdDataType,logic_Tree *> mvmu_TreeMap; // rootId �� ��ʵ��Ķ�Ӧ
	std::map <_IdDataType, logic_BasicModule *> mvmu_ModuleMap; //ά��һ��module��ӳ��
	std::map <int ,logic_Tree * > mvmu_ModuleId_TreeMap; //ά��ÿ�� moduleID �� tree ��ӳ��

	std::map <logic_Tree * ,int > mvmi_TreeId_For_IfIdMap; //!!!!!!!!!!!!ά�� treeId �� For If ģ�� Id ��ӳ���

	/////��������
	std::map<whPort, whPort > mvvu_Conn_From_ToMap; //ά�� ����ģ��Port---����ģ��Port ��ϣ��
	std::map<whPort, whPort > mvvu_Conn_To_FromMap; //ά�� ����ģ��Port---����ģ��Port������˫�����

	void Init();
	void prog_Destroy();

	void updateMId_TreeMap(logic_Tree *tree); //��һ����������module treeӳ���Ϊ��ǰtree
	void recurs_update(logic_Tree *tree,logic_TreeNode *some); //�� updateMId_TreeMap() ���ã��ݹ����

	void recurs_GetId(logic_TreeNode *some,std::vector<int> & L);
	void recurs_GetNode(logic_TreeNode *some,std::vector<logic_TreeNode *> & L);

	//��ȫɾ��һ�������нڵ�ģ���������Ϣ������ʵ��map��connection map��
	void recurs_DelTreeNodeModule(logic_TreeNode *some);

private:
	int mvs_ProgId; //һ��program��һ��ɭ�֣�project��ɭ�ֵĺϼ�
	std::string mvs_ProgName;

};


#endif
