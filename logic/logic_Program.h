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
#include "logic_Tree.h"
#include "logic_BasicModule.h"
#include "logic_Global.h"
#include "logic_ModulePortLine.h"

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

	bool delModule(int m_id);
	int getModulePreId(int m_id); //�õ�ĳһģ���ǰ��id
	std::vector<int > getModulePostId(int m_id);

	//////move ����
	int frontInsSingMove(int cur_m_id,int post_m_id); //ǰ��move
	int backInsSingMove(int cur_m_id,int pre_m_id); //���move
	int frontInsMultiMove(int cur_m_id,int post_m_id); //������ǰ��move
	int backInsMultiMove(int cur_m_id,int pre_m_id); //�����Ӻ��move

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

protected:
	///////map[0] == NULL ��ֹ getMaxXXXId() �����Ҳ��������е� map ����������취
	std::map <_IdDataType,logic_Tree *> mvmu_TreeMap;
	std::map <_IdDataType, logic_BasicModule *> mvmu_ModuleMap; //ά��һ��module��ӳ��
	std::map <int ,logic_Tree * > mvmu_ModuleId_TreeMap; //ά��ÿ�� moduleID �� tree ��ӳ��

	std::vector<logic_ModulePortLine *> mvvu_ModulePortLineList; //���߱�
	std::map <int ,int > mvmi_TreeId_For_IfIdMap; //!!!!!!!!!!!!ά�� treeId �� For If ģ�� Id ��ӳ���

	void Init();
	void prog_Destroy();

	void updateMId_TreeMap(logic_Tree *tree); //��һ����������module treeӳ���Ϊ��ǰtree
	void recurs_update(logic_Tree *tree,logic_TreeNode *some); //�� updateMId_TreeMap() ���ã��ݹ����

	void recurs_GetId(logic_TreeNode *some,std::vector<int> & L);
	void recurs_GetNode(logic_TreeNode *some,std::vector<logic_TreeNode *> & L);

	//רע��� for ģ�����Ӻ�ɾ��
	void handleForAdd();
	void handleForDel();

private:
	int mvs_ProgId; //һ��program��һ��ɭ�֣�project��ɭ�ֵĺϼ�
	std::string mvs_ProgName;

};


#endif
