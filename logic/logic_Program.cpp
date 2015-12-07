/* 
* 
* function: �߼���ɭ����֯�ṹ
* 
* Date:2015-09-02
* 
*    Author: Bill Wang
*/

#include <iostream>  
#include <map>
#include <algorithm>
#include<stdlib.h>
#include "logic_Program.h"
#include "logic_Global.h"
#include "logic_Tree.h"
#include <assert.h>
#include "../TransStringNum.h"
#include "logic_ForModule.h"
#include "logic_IfModule.h"
#include "logic_WhData.h"

using namespace std;

//typedef logic_Tree tree_type;


logic_Program::logic_Program(int id,std::string prog_name)
	:mvs_ProgId(id),mvs_ProgName(prog_name)
{
	Init(); //��ʼ��program

}

logic_Program::~logic_Program()
{
	prog_Destroy();
}

//��ͨ��ʼ�����ɾ���program��
void logic_Program::Init()
{
	mvmu_TreeMap.clear();
	//mvmu_TreeMap[0] = NULL;
	mvmu_ModuleMap.clear();
	//mvmu_ModuleMap[0] = NULL;  //Module ��Ҫ getMax
	mvmu_ModuleId_TreeMap.clear();
	//mvmu_ModuleId_TreeMap[0] = NULL;

	mvvu_Conn_From_ToMap.clear();
	mvvu_Conn_To_FromMap.clear();

	mvmi_TreeId_For_IfIdMap.clear();
	//mvmi_TreeId_For_IfIdMap[0] = NULL;

	add_Tree(1);

	//����module�����һ����ʼģ��
	logic_BasicModule *bm = new logic_BasicModule();
	mvmu_ModuleMap.insert(pair<_IdDataType , logic_BasicModule *>(bm->mvi_ModuleID,bm));

	mvmu_ModuleId_TreeMap[1] = mvmu_TreeMap[1];
}

void logic_Program::prog_Destroy()
{
	cout<<"����prog_Destroy"<<endl;

	//���mvmu_ModuleMap
	for(map<_IdDataType , logic_BasicModule *>::iterator it = mvmu_ModuleMap.begin();it != mvmu_ModuleMap.end(); ++it)
		SAFE_DELETE(it->second);

	//���ɭ��
	for(map<_IdDataType , logic_Tree *>::iterator it = mvmu_TreeMap.begin();it != mvmu_TreeMap.end(); ++it)
	{
		logic_Tree *tmpT = it->second;
		//tmpT->Destroy(tmpT->getRoot()); //������������Σ��Ѵ���
		SAFE_DELETE(tmpT);
	}

	//���ӳ���
// 	for(map<int , logic_Tree *>::iterator it = mvmu_ModuleId_TreeMap.begin();it != mvmu_ModuleId_TreeMap.end(); ++it)
// 	{
// 		logic_Tree *tmpT = it->second;
// 		//tmpT->Destroy(tmpT->getRoot()); //������������Σ��Ѵ���
// 		SAFE_DELETE(tmpT);
// 	}
}

bool logic_Program::add_Tree(_IdDataType rootId)
{
	if (mvmu_TreeMap.count(rootId)>0) //�Ѵ��ڣ����󷵻�
		return false;

	logic_Tree* t = new logic_Tree(rootId);
	mvmu_TreeMap.insert(pair<_IdDataType , logic_Tree *>(t->mvi_TreeID,t));

	return true;
}

bool logic_Program::add_Tree(logic_Tree * t)
{
	if (mvmu_TreeMap.count(t->mvi_TreeID)>0) //�Ѵ��ڣ����󷵻�
		return false;

	//logic_Tree *tmpTree = new logic_Tree(*t);
	mvmu_TreeMap[t->mvi_TreeID]=t;

	return true;
}

bool logic_Program::del_Tree(_IdDataType rootId)
{
	if (mvmu_TreeMap.count(rootId)==0) //�����ڣ�ɾ������
		return false;

	logic_Tree *tmpT = mvmu_TreeMap[rootId];
	SAFE_DELETE(tmpT);

	mvmu_TreeMap.erase(rootId);
	return true;
}

logic_Tree* logic_Program::search_Tree(_IdDataType rootId)
{
	if (mvmu_TreeMap.count(rootId)>0)
	{
		return mvmu_TreeMap[rootId];
	}

	throw NULL;
}

//������ָ����ID���ҵ�����ID���Ҳ�������-1
_IdDataType logic_Program::search_Tree(logic_Tree* treePtr)
{
	if (mvmu_TreeMap.count(treePtr->mvi_TreeID)>0)
	{
		return treePtr->mvi_TreeID;
	}
	return -1;
}

//�������ͷ� modulePtr �ռ�
bool logic_Program::add_Module(_IdDataType moduleId , logic_BasicModule* modulePtr)
{
	if (mvmu_ModuleMap.count(moduleId)>0) //�Ѵ��ڣ����󷵻�
		return false;

	mvmu_ModuleMap[modulePtr->mvi_ModuleID] = modulePtr;

	return true;
}

bool logic_Program::add_Module(_IdDataType moduleId , int m_Type)
{
	if (mvmu_ModuleMap.count(moduleId)>0) //�Ѵ��ڣ����󷵻�
		return false;

	logic_BasicModule *bm = NULL;
	if( 2003 == m_Type ) {

		//for
		logic_ForModule* tmpForModule = new logic_ForModule(moduleId,mvmu_TreeMap,mvmu_ModuleMap,
			mvmu_ModuleId_TreeMap,mvmi_TreeId_For_IfIdMap,mvvu_Conn_From_ToMap,mvvu_Conn_To_FromMap);
		bm = tmpForModule;

		/// activeTree ��������forģ��
		//�õ�Ĭ��activeTree��ά��map
// 		logic_Tree * tmpActiveTree = tmpForModule->getCurActiveTree();
// 		mvmu_TreeMap[this->composeTreeId(moduleId)] = tmpActiveTree;

	}else if( 2004 == m_Type ) {

		//if
		logic_IfModule* tmpIfModule = new logic_IfModule(moduleId,mvmu_TreeMap,mvmu_ModuleMap,
			mvmu_ModuleId_TreeMap,mvmi_TreeId_For_IfIdMap,mvvu_Conn_From_ToMap,mvvu_Conn_To_FromMap);
		bm = tmpIfModule;

		/// activeTree ��������ifģ��
		//�õ�Ĭ�ϵ�����branch activeTree��ά��map
// 		logic_Tree * tmpActiveTree = tmpIfModule->getCurActiveTree(1);
// 		mvmu_TreeMap[this->composeTreeId(moduleId,1)] = tmpActiveTree;
// 		tmpActiveTree = tmpIfModule->getCurActiveTree(2);
// 		mvmu_TreeMap[this->composeTreeId(moduleId,2)] = tmpActiveTree;

	}else //��ͨģ��
		bm = new logic_BasicModule(moduleId,m_Type);

	mvmu_ModuleMap.insert(pair<_IdDataType , logic_BasicModule *>(bm->mvi_ModuleID,bm));

	return true;
}

bool logic_Program::del_Module(_IdDataType moduleId)
{
	if (mvmu_ModuleMap.count(moduleId)==0) {
		//�����ڣ�ɾ������
		assert(false);
		return false;
	}

	//ɾ��moduleʵ��
	logic_BasicModule * tmpModule = mvmu_ModuleMap[moduleId];
	mvmu_ModuleMap.erase(moduleId);

	//����virtual���������������Զ����� for��if
	SAFE_DELETE(tmpModule);

	//ɾ����������
	this->DelAllParaConnect(moduleId);

	return true;
}

//ɾ������ĳһģ�����������
void logic_Program::DelAllParaConnect(int id) {

	//��������
	for( map<whPort ,whPort >::iterator it = mvvu_Conn_From_ToMap.begin(); it != mvvu_Conn_From_ToMap.end(); ++it ) {

		if( id == it->first.moduleId ) {

			//��� from �Ǹ�ģ�飬������� outModule ��ؾ���Ҫɾ��
			whPort outPort = it->first;
			whPort inPort = mvvu_Conn_From_ToMap[outPort];
			mvvu_Conn_From_ToMap.erase(outPort);
			mvvu_Conn_To_FromMap.erase(inPort);

		}else if(id == it->second.moduleId) {

			//��� to �Ǹ�ģ��
			whPort outPort = it->first;   // �൱�� whPort inPort = it->second;
			whPort inPort = mvvu_Conn_From_ToMap[outPort];
			mvvu_Conn_From_ToMap.erase(outPort);
			mvvu_Conn_To_FromMap.erase(inPort);
		}
	}
}

logic_BasicModule* logic_Program::searchModule(_IdDataType moduleId)
{
	if (mvmu_ModuleMap.count(moduleId)>0)
	{
		return mvmu_ModuleMap[moduleId];
	}

	return NULL;
}

_IdDataType logic_Program::searchModule(logic_BasicModule* modulePtr)
{
	if (mvmu_ModuleMap.count(modulePtr->mvi_ModuleID)>0)
	{
		return modulePtr->mvi_ModuleID;
	}
	return -1;
}

void logic_Program::setProgramName(const string name)
{
	mvs_ProgName = name;
}

std::string logic_Program::getName()
{
	return mvs_ProgName;
}

int logic_Program::getID()
{
	return mvs_ProgId;
}

int logic_Program::getMaxModuleId() {

	if( mvmu_ModuleMap.size() == 0 )
		return 0;

	std::map<int, logic_BasicModule *>::const_iterator it = mvmu_ModuleMap.end();
	it--;
	return it->first;
}

//������ɭ�������id����ʵ������ module
bool logic_Program::appendModule(int m_id,int pre_id,int m_type) {

	assert( mvmu_ModuleMap.count(pre_id)>0 );

	// step1����ɭ���м������id

	if ( 0 == pre_id ) {   //��� pre_id Ϊ 0 ������Ҫ�½�һ����

		logic_Tree *tree = new logic_Tree(m_id);
		this->add_Tree(tree);
		mvmu_TreeMap[m_id] = tree;
		mvmu_ModuleId_TreeMap[m_id] = tree;

	}else {
		//��� pre_id ��Ϊ 0 ������ pre_id ����
		if ( m_type == 2001 ) {
			return false;
		}

		logic_Tree *tree = mvmu_ModuleId_TreeMap[pre_id];
		tree->append_node(pre_id,m_id);

		mvmu_ModuleId_TreeMap[m_id] = tree;
	}

	// step2�������������moduleʵ��
	this->add_Module(m_id,m_type);

	return true;
}

bool logic_Program::frontInsModule(int m_id,int post_id,int m_type) {

	assert( mvmu_ModuleMap.count(post_id)>0 );

	if ( 0 == post_id ) {
		return false;
	}

	// step1����ɭ���м������id

	//postģ���ǿ�ʼģ�飬���������
	if ( mvmu_ModuleMap[post_id]->getModuleType() == 2001 ) {
		return false;
	}

	logic_Tree *tree = mvmu_ModuleId_TreeMap[post_id];

	if ( post_id == tree->mvi_TreeID ) { //���ֺ�̽ڵ���root����Ҫ����
		tree->exchangeRoot(m_id);
		mvmu_ModuleId_TreeMap[m_id] = tree;

		//update treeMap
		mvmu_TreeMap.erase(post_id);
		mvmu_TreeMap[m_id] = tree;

	}else{ //�����̲���root�����뵽�������м�

		tree->insert_node(tree->getPreId(post_id),post_id,m_id);
		mvmu_ModuleId_TreeMap[m_id] = tree;
	}

	// step2�������������moduleʵ��
	this->add_Module(m_id,m_type);

	return true;
}

//ǰ��move
//cur_m_id �Ǵ�move�ڵ�
//post_m_id �ǽڵ���
int logic_Program::frontInsSingMove(int cur_m_id,int post_m_id) {

	///// ��һ�����ж� post_m_id �Ƿ�Ϊ 0

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(post_m_id)) ) {
		return -2; //û�ҵ������
	}

	//��� post_m_id ģ���ǿ�ʼ
	if ( mvmu_ModuleMap[post_m_id]->getModuleType() == 2001 ) {
			return -3; //ģ�����ʹ���
	}

	//ע�������½�module��ֻ�ô������ڵ㼴��

	///// step1�����������ڵ�
	logic_Tree *insTree = mvmu_ModuleId_TreeMap[post_m_id]; //��������
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //��ɾ����

	int oldRootId = insTree->mvi_TreeID;
	if( post_m_id == oldRootId ) {
		
		//������ڵ�Ҫ����ԭ��root֮ǰ
		mvmu_TreeMap.erase(post_m_id);
		insTree->exchangeRoot(cur_m_id);
	}else {

		//��������ط�
		insTree->insert_node(insTree->getPreId(post_m_id),post_m_id,cur_m_id);
	}

	mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

	///// step2��ɾ�������ڵ㣨ע���˴��������ж�����ӣ�
	if( cur_m_id != oldTree->mvi_TreeID ) {

		//��������
		oldTree->del_node(cur_m_id);
	}else if(cur_m_id == oldTree->mvi_TreeID 
		|| oldTree->getRoot()->mvvu_Children.size()==0 ) {

			//����Ψһģ�飬ɾ����
			SAFE_DELETE(oldTree);
			mvmu_TreeMap.erase(cur_m_id);
	}

	//ֻ�� post_m_id �Ǹ���������Ÿ���tree map
	if( post_m_id == oldRootId )
		mvmu_TreeMap[cur_m_id] = insTree;

	return 0; //��������

}

//��ģ����move
int logic_Program::backInsSingMove(int cur_m_id,int pre_m_id) {

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id)) ) {
		return -2; // ���� cur_m_id �� pre_m_id ��Ҫ��
	}

	//��� cur_id ģ���ǿ�ʼ
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
			return -3; //ģ�����ʹ���
	}

	//ע�������½�module��ֻ�ô������ڵ㼴��

	///// step1�����������ڵ�
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //��ɾ����������ҵ��������
	logic_Tree *insTree = NULL;
	if( 0 == pre_m_id ) {  ////////////�����������ǳ����������Σ��

		//���ǰ��һ�ÿ���

		if ( cur_m_id == oldTree->mvi_TreeID 
			&& oldTree->getRoot()->mvvu_Children.size()==0 
			) {

			///�����ǰ�������ͬʱ���� Ψһģ�� ����
			return -5;
		}

		logic_TreeNode tmpCurNode( *(oldTree->node_search(cur_m_id)) ) ; //������쵽ջ

		if ( tmpCurNode.mvvu_Children.size() > 1 ) {
			//������Ӳ���һ��������
			return -4;
		}

		tmpCurNode.mvu_Parent = 0;
		tmpCurNode.mvvu_Children.clear();

		logic_TreeNode *tmpPassNode = new logic_TreeNode(tmpCurNode); //������쵽��
		insTree = new logic_Tree(tmpPassNode); //�½�һ��������nodeҲ�����½������������delnode��

		mvmu_TreeMap[insTree->mvi_TreeID] = insTree;

	}else {

		////// pre_m_id ��Ϊ0

		/////����Ѵ��ڣ�ֱ���ҵ���������
		insTree = mvmu_ModuleId_TreeMap[pre_m_id];
		insTree->append_node(pre_m_id,cur_m_id);
	}

	///// step2��ɾ�������ڵ㣨ע���˴��������ж�����ӣ�

	if( cur_m_id != oldTree->mvi_TreeID ) {

		//��������
		oldTree->del_node(cur_m_id);
	}else if(cur_m_id == oldTree->mvi_TreeID ) {

		if ( oldTree->getRoot()->mvvu_Children.size()==0 ) {

			//����Ψһģ�飬ɾ������ ���������֧ pre_m_id ��Ȼ������0���������жϣ��������-5 ��

			SAFE_DELETE(oldTree);
			mvmu_TreeMap.erase(cur_m_id);

			// Step3���������ڴ˴�����Ȼ��return�ˣ�����
			mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

			return 0; //��������
		}else {
			//����Ψһģ��

			oldTree->setFirstChildAsRoot();
		}

	}

	// Step3������
	mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

	return 0; //��������
}

//������ǰ��move
////////////////ע����Ȼ�ǲ���һ��������ǰ��/////////////////
int logic_Program::frontInsMultiMove(int cur_m_id,int post_m_id) {

	///// ��һ�����ж� post_m_id �Ƿ�Ϊ 0

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(post_m_id)) ) {
		return -2; //û�ҵ������
	}

	//��� post_m_id ģ���ǿ�ʼ
	if ( mvmu_ModuleMap[post_m_id]->getModuleType() == 2001 ) {
			return -3; //ģ�����ʹ���
	}

	//ע�������½�module��ֻ�ô������ڵ㼴��

	///// step1�����������ڵ�
	/////!!!!!!!!!!!!�ر�ע���������� insTree �� oldtree ����������ת��Ϊ���!!!!!!!!!!!!!!
	logic_Tree *insTree = mvmu_ModuleId_TreeMap[cur_m_id]; //��������
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[post_m_id]; //��ɾ����

	//��� post_m_id ���Ǹ��ڵ㣬���󷵻�
	if( post_m_id!=oldTree->mvi_TreeID ) {
		return -4;
	}

	///////////////////////////////////////
	logic_TreeNode * insNode = oldTree->getRoot(); //������ڵ�
	insTree->add_node(cur_m_id,insNode);

	///// step2��ɾ�������ڵ�

	//��Ȼ��ROOT��ֱ��ɾ����
	oldTree->del_node_notConn(post_m_id); //�Ͽ� oldTree �˽ڵ�����������
	SAFE_DELETE(oldTree); //����ɾ����
	mvmu_TreeMap.erase(post_m_id);

	///// step3������ module treeӳ��

	recurs_update(insTree,insNode);


	return 0; //��������
}

//�����Ӻ��move
int logic_Program::backInsMultiMove(int cur_m_id,int pre_m_id) {

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id)) ) {
		return -2; // ���� cur_m_id �� pre_m_id ��Ҫ��
	}

	//��� cur_id ģ���ǿ�ʼ
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
			return -3; //ģ�����ʹ���
	}

	//ע�������½�module��ֻ�ô������ڵ㼴��

	/////////////��ʼ/////////////
	
	///// step1��ɾ�������ڵ�
	///// ע��ɾ�������ǵ�һ������Ȼ del_node_notConn ������ɾ������ parent �ĺ���

	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //��ɾ����
	logic_TreeNode * insNode = oldTree->node_search(cur_m_id); //������ڵ㣨�����ڴ˴�Ѱ�ң�

	if ( insNode->mvvu_Children.size() == 0 ) {
		//����ֻ��һ������
		return -4;
	}

	if( cur_m_id != oldTree->mvi_TreeID ) {

		//��������
		oldTree->del_node_notConn(cur_m_id); //�Ͽ� oldTree ��˽ڵ������

	}else if(cur_m_id == oldTree->mvi_TreeID ) {

		//ROOT��ɾ����
		oldTree->del_node_notConn(cur_m_id); //�����������ֱ�ӽ�����root�ÿ�
		SAFE_DELETE(oldTree); //����ɾ����
		mvmu_TreeMap.erase(cur_m_id);
	}

	///// step2�������½ڵ�
	logic_Tree *insTree = NULL;
	if( 0 == pre_m_id ) { 
		//���ǰ��һ�ÿ���

		insTree = new logic_Tree(insNode); //�½�һ����

		mvmu_TreeMap[insTree->mvi_TreeID] = insTree;
		mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

	}else {
		/////����Ѵ��ڣ�ֱ���ҵ���������
		insTree = mvmu_ModuleId_TreeMap[pre_m_id];

		logic_TreeNode * preNode = insTree->node_search(pre_m_id); //pre_m_id�ڵ�
		//��� pre_m_id ����Ҷ�ӽڵ㣬���󷵻�
		if(preNode->mvvu_Children.size()>0) {
			return -4;
		}

		insTree->add_node(pre_m_id,insNode);

	}

	///// step3������ module treeӳ��
	recurs_update(insTree,insNode);

	return 0; //��������
}

//��������move
int logic_Program::addLeafMove(int cur_m_id,int pre_m_id) {

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id)) ) {
		return -2; // ���� cur_m_id �� pre_m_id ��Ҫ��
	}

	//��� cur_id ģ���ǿ�ʼ
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
			return -3; //ģ�����ʹ���
	}

	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //��ɾ����
	//�ýڵ�����Ǹ����ĸ��ڵ�
	if( oldTree->mvi_TreeID != cur_m_id )
		assert(false);

	logic_Tree *insTree = mvmu_ModuleId_TreeMap[pre_m_id];
	logic_TreeNode * insNode = insTree->node_search(pre_m_id); //������ڵ�
	logic_TreeNode * curNode = oldTree->getRoot(); //��ǰ�ڵ�

	/// Step1�������½ڵ�
	insNode->mvvu_Children.push_back(curNode);

	/// Step2��ɾ������map��Ϣ
	mvmu_TreeMap.erase(cur_m_id);
	oldTree->setRoot(NULL);
	SAFE_DELETE(oldTree);

	/// Step3������ģ����map��Ϣ
	recurs_update(insTree,curNode);

	return 0;
}

//ͨ��һ��ģ��id���ҵ�������
logic_Tree* logic_Program::getTreeFromId(int m_id) {

	return mvmu_ModuleId_TreeMap[m_id];
}

std::map<int,logic_Tree*> logic_Program::getTreeMap() {
	return mvmu_TreeMap;
}

std::map <int ,logic_BasicModule* > logic_Program::getModuleMap() {
	return mvmu_ModuleMap;
}

bool logic_Program::delModule(int m_id) {

	if (mvmu_ModuleMap.count(m_id)==0) //�����ڣ�ɾ������
		return false;

	// step1����ɭ����ɾ�����id
	logic_Tree *tree = mvmu_ModuleId_TreeMap[m_id]; //�õ����ڵ���

	if (m_id != tree->mvi_TreeID ) {
		///!!!!!!!!!!!!!!!!!!!!����ROOT!!!!!!!!!!!!!!!!!!!!!!!!

		logic_TreeNode *delNode = tree->node_search(m_id);

		if(delNode->mvvu_Children.size() == 1) {

			//1����ROOT����ֻ��һ�����ӣ�����ɾ��
			tree->del_node(m_id);
			mvmu_ModuleId_TreeMap.erase(m_id);

		}else if(delNode->mvvu_Children.size() > 1) {

			//2����root���ж�����ӣ���ɶ����

			//����ĺ�����Ҫ����n����
			for (int i=0; i<delNode->mvvu_Children.size() ; ++i ) {

				delNode->mvvu_Children.at(i)->mvu_Parent = NULL;
				logic_Tree * tmpTree = new logic_Tree(delNode->mvvu_Children.at(i)); //�½���
				mvmu_TreeMap[tmpTree->mvi_TreeID] = tmpTree; //��map ����
				updateMId_TreeMap(tmpTree); //����ӳ���

				//���������root���� for �� if �У���Ҫ���⴦��
				if( mvmi_TreeId_For_IfIdMap.count(tree) > 0 ) {

					//�õ�����Module
					logic_BasicModule * tmpModule = mvmu_ModuleMap[mvmi_TreeId_For_IfIdMap[tree]];

					if( tmpModule->getModuleType() == 2003 ) {

						//for
						logic_ForModule * tmpForModule = (logic_ForModule *) tmpModule;
						//����ɾ��ԭ����ֱ�Ӽ�������
						tmpForModule->addTree(tmpTree);

					}else if( tmpModule->getModuleType() == 2004 ) {

						//if
						logic_IfModule * tmpIfModule = (logic_IfModule *) tmpModule;
						int tmpBranchId = tmpIfModule->getTreeBranch( mvmu_ModuleId_TreeMap[m_id] );
						tmpIfModule->addTree(tmpBranchId,tmpTree);
					}

					int for_if_id = mvmi_TreeId_For_IfIdMap[tree];
					mvmi_TreeId_For_IfIdMap[tmpTree] = for_if_id;

				}
			}

			//ԭ��������ֻ�뽫��ǰ�ڵ㸸�ڵ�����Ƴ�
			tree->del_node_notConn(m_id);
			SAFE_DELETE(delNode);  //��ʽɾ���˽ڵ�
			mvmu_ModuleId_TreeMap.erase(m_id);
		}

	}else {

		///!!!!!!!!!!!!!!!!!!!!!!!!!!!ROOT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		logic_TreeNode *oldRoot = tree->getRoot();

		if(oldRoot->mvvu_Children.size() == 1) {
			//1����ֻ��һ�����ӣ�����ɾ����treeû�иı䣬���ظ���ӳ���
			tree->del_node(m_id);
			mvmu_ModuleId_TreeMap.erase(m_id);

			/////// tree���䣬���ø��� mvmi_TreeId_For_IfIdMap

		}else if(oldRoot->mvvu_Children.size() > 1) {

			//2��root��n�����ӣ����n������ÿ����������

			//������Ҫ����n-1����
			for (int i=1; i<oldRoot->mvvu_Children.size() ; ++i ) {

				oldRoot->mvvu_Children.at(i)->mvu_Parent = NULL;
				logic_Tree * tmpTree = new logic_Tree(oldRoot->mvvu_Children.at(i)); //�½���
				mvmu_TreeMap[tmpTree->mvi_TreeID] = tmpTree; //��map ����
				updateMId_TreeMap(tmpTree); //����ӳ���


				//���������root���� for �� if �У���Ҫ���⴦��
				if( mvmi_TreeId_For_IfIdMap.count(tree) > 0 ) {

					logic_BasicModule * tmpModule = mvmu_ModuleMap[mvmi_TreeId_For_IfIdMap[tree]];

					if( tmpModule->getModuleType() == 2003 ) {

						//for
						logic_ForModule * tmpForModule = (logic_ForModule *) tmpModule;
						//����ɾ��ԭ����ֱ�Ӽ�������
						tmpForModule->addTree(tmpTree);

					}else if( tmpModule->getModuleType() == 2004 ) {

						//if
						logic_IfModule * tmpIfModule = (logic_IfModule *) tmpModule;
						int tmpBranchId = tmpIfModule->getTreeBranch( mvmu_ModuleId_TreeMap[m_id] );
						tmpIfModule->addTree(tmpBranchId,tmpTree);
					}

					int for_if_id = mvmi_TreeId_For_IfIdMap[tree];
					mvmi_TreeId_For_IfIdMap[tmpTree] = for_if_id;

				}

			}

			//ԭ��ֱ�����ú���Ϊroot��treeû�иı䣬���ظ���ӳ���
			tree->setFirstChildAsRoot(); //��root��Ψһ��������Ϊroot��ͬʱɾ��oldRoot
			mvmu_TreeMap.erase(m_id);
			mvmu_ModuleId_TreeMap.erase(m_id);

		}else if(oldRoot->mvvu_Children.size() == 0) {

			//����Ψһ��ģ�飬ɾ����
			SAFE_DELETE(mvmu_ModuleId_TreeMap[m_id]);
			mvmu_TreeMap.erase(m_id);
			mvmu_ModuleId_TreeMap.erase(m_id);

			//�����������root���� for �� if �У���Ҫ���⴦��
			if( mvmi_TreeId_For_IfIdMap.count(tree) > 0 ) {

				logic_BasicModule * tmpModule = mvmu_ModuleMap[mvmi_TreeId_For_IfIdMap[tree]];

				if( tmpModule->getModuleType() == 2003 ) {

					//for
					logic_ForModule * tmpForModule = (logic_ForModule *) tmpModule;
					tmpForModule->delTree( mvmu_ModuleId_TreeMap[m_id] );

				}else if( tmpModule->getModuleType() == 2004 ) {

					//if
					logic_IfModule * tmpIfModule = (logic_IfModule *) tmpModule;
					tmpIfModule->delTree( mvmu_ModuleId_TreeMap[m_id] );

				}

				mvmi_TreeId_For_IfIdMap.erase(tree); //��ȫɾ��

			}
		}
		
	}


	// step2����map��ɾ�����moduleʵ��
	this->del_Module(m_id);

	return true;
}

void logic_Program::updateMId_TreeMap(logic_Tree *tree) {
	//��һ����������module treeӳ���Ϊ��ǰtree
	this->recurs_update(tree,tree->getRoot());
}

void logic_Program::recurs_update(logic_Tree *tree,logic_TreeNode *some) {

	mvmu_ModuleId_TreeMap[some->getID()] = tree;

	//�� updateMId_TreeMap() ���ã��ݹ����
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++) {
		recurs_update(tree,some->mvvu_Children[i]);
	}
}

bool logic_Program::addLeafModule(int m_id,int pre_id,int m_type) {

	if ( 0 == pre_id ) {
		return false;
	}

	//��� pre_id ��Ϊ 0 ������ pre_id ����
	if ( m_type == 2001 ) {
		return false;
	}

	logic_Tree *tree = mvmu_ModuleId_TreeMap[pre_id];
	tree->add_node(pre_id,m_id);

	mvmu_ModuleId_TreeMap[m_id] = tree;

	// step2�������������moduleʵ��
	this->add_Module(m_id,m_type);

	return true;
}

int logic_Program::getModulePreId(int m_id) {

	if (mvmu_ModuleMap.count(m_id)==0) //�����ڣ�����
		return -1;

	int resid = mvmu_ModuleId_TreeMap[m_id]->getPreId(m_id);

	return resid;
}

std::vector<int > logic_Program::getModulePostId(int m_id) {

	std::vector<int > L;

	if (mvmu_ModuleMap.count(m_id) == 0) //�����ڣ�����
		return L;

	logic_TreeNode *tNode = mvmu_ModuleId_TreeMap[m_id]->node_search(m_id);

	if (tNode == NULL)
		return L;

	for (int i=0; i< tNode->mvvu_Children.size();++i ) {
		L.push_back(tNode->mvvu_Children.at(i)->getID());
	}

	return L;

}

std::vector<int> logic_Program::getAllTreeNodeId(int tree_id) {

	std::vector<int > L;

	if( mvmu_TreeMap.count(tree_id) <=0 ) {
		//���󣬷��ؿռ�
		return L;
	}

	logic_Tree *tree = mvmu_TreeMap[tree_id];
	this->recurs_GetId(tree->getRoot(),L);

	return L;
}

void logic_Program::recurs_GetId(logic_TreeNode *some,std::vector<int> & L) {

	L.push_back(some->getID());

	//�� getAllTreeNodeId() ���ã��ݹ�get id
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++) {
		recurs_GetId(some->mvvu_Children[i],L);
	}
}

std::string logic_Program::getModulePara(int type,int m_id,int p_id) {

	//MAX_VALUE = 0,//���ֵ
	//MIN_VALUE, //��Сֵ
	//INIT, //��ʼֵ
	//CUR //��ǰֵ

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return NULL; //����
	}

	logic_BasicPara *tPara = mvmu_ModuleMap[m_id]->getPara(p_id);
	std::string res;

	switch (type)
	{
	case 0: //max
		res = numToString<int > (tPara->mvd_Max);
		break;

	case 1: //min
		res = numToString<int > (tPara->mvd_Min);
		break;

	case 2: //init

		break;

	case 3: //cur
		res = tPara->mvs_Value;
		break;

	default:
		break;
	}

	return res;

}

void logic_Program::setModulePara(int m_id,int p_id,std::string p_value) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return ; //����
	}

	logic_BasicPara *tPara = mvmu_ModuleMap[m_id]->getPara(p_id);
	tPara->mvs_Value = p_value;
}

WinSwitcherType logic_Program::getModuleWinSwType(int m_id,int m_modeValue) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		//return ; //����
		assert(false);
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	return tModule->getWSType(m_modeValue);
}

std::string logic_Program::getModuleWinSwValue(int m_id) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return NULL; //����
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	return tModule->getWSValue();

}

void logic_Program::setModuleWinSwValue(int m_id,std::string ws_value) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return ; //����
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	tModule->setWSValue(ws_value);
}

int logic_Program::getModuleDaisyChainValue(int m_id) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return -1; //����
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	return tModule->getDaisyChainValue();
}

void logic_Program::setModuleDaisyChainValue(int m_id,int chain_value) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return ; //����
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	tModule->setDaisyChainValue(chain_value);
}

std::vector<int > logic_Program::getModuleParamsIds(int m_id,int mode_value) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		//return ; //����
		assert(false);
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	return tModule->getParamsIds(mode_value);
}

int logic_Program::getModuleModeValue(int m_id) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return -1; //����
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	return tModule->getModeValue();
}

void logic_Program::setModuleModeValue(int m_id,int mode_id) {

	if ( 0 == mvmu_ModuleMap.count(m_id) ) {
		return ; //����
	}

	logic_BasicModule *tModule = mvmu_ModuleMap[m_id];
	tModule->setModeValue(mode_id);
}

//�õ�����treenode
std::vector<logic_TreeNode *> logic_Program::getAllTreeNode(int rootID) {

	std::vector<logic_TreeNode *> L;

	if ( 0 == mvmu_ModuleMap.count(rootID) ) {
		return L; //����
	}

	logic_Tree *tree = mvmu_TreeMap[rootID];
	this->recurs_GetNode(tree->getRoot(),L);

	return L;

}

void logic_Program::recurs_GetNode(logic_TreeNode *some,std::vector<logic_TreeNode *> & L) {

	L.push_back(some);

	//�� getAllTreeNodeId() ���ã��ݹ�get id
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++) {
		recurs_GetNode(some->mvvu_Children[i],L);
	}
}

/// \brief for if

//insert into for
bool logic_Program::insertModuleIntoFor(int m_id,int pre_id,int m_type,int for_id) {

	/////�˴��ѱ�Ȼ�� append �ˣ��� pre_id ��Ȼ��0

	if( mvmu_ModuleMap.count(for_id) == 0 )
		return false;

	if( -1 == pre_id ) //��activeTree����ֱ�Ӳ���һ��ģ��
		return this->appendActiveTreeInsertFor(m_id,m_type,for_id);

	///// Step1�������Ѿ�д�õ� appendModule() ������pre_id ��Ȼ��0
	this->appendModule(m_id,0,m_type);

	///// Step2���� for ģ���м���
	logic_BasicModule * tmpModule = mvmu_ModuleMap[for_id];

	if( 2003 != tmpModule->getModuleType() ) //����forģ�飬����
		return false;

	/// type һ����2003
	logic_ForModule *tmpForModule = (logic_ForModule *)tmpModule; //ǿ��ת����for module
	
	if( tmpForModule->addTree(mvmu_ModuleId_TreeMap[m_id]) < 0 )
		return false;

	mvmi_TreeId_For_IfIdMap[mvmu_ModuleId_TreeMap[m_id]] = for_id;

	return true;
}

//insert into if
bool logic_Program::insertModuleIntoIf(int m_id,int pre_id,int m_type,int if_id,int branch_id) {

	/////�˴��ѱ�Ȼ�� append �ˣ��� pre_id ��Ȼ��0

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return false;

	///// Step1�������Ѿ�д�õ� appendModule() ����
	this->appendModule(m_id,pre_id,m_type);

	///// Step2���� for ģ���м���
	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //����ifģ�飬����
		return false;

	/// type һ����2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //ǿ��ת����if module
	
	if( tmpIfModule->addTree( branch_id,mvmu_ModuleId_TreeMap[m_id] ) < 0 )
		return false;

	mvmi_TreeId_For_IfIdMap[mvmu_ModuleId_TreeMap[m_id]] = if_id;

	return true;
}

// get for ��ǰactive��
int logic_Program::getForActiveTree(int for_id) {

	if( mvmu_ModuleMap.count(for_id) == 0 )
		return -3;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[for_id];

	if( 2003 != tmpModule->getModuleType() ) //����forģ�飬����
		return -4;

	/// type һ����2003
	logic_ForModule *tmpForModule = (logic_ForModule *)tmpModule; //ǿ��ת����for module

	logic_Tree * tree = tmpForModule->getCurActiveTree(); //����С��0

	return tree->mvi_TreeID;
}

//if ��ǰactive��
int logic_Program::getIfActiveTree(int if_id,int branch_id) {

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return -3;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //����ifģ�飬����
		return -4;

	/// type һ����2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //ǿ��ת����if module

	logic_Tree * tree = tmpIfModule->getCurActiveTree(branch_id); //����С��0

	return tree->mvi_TreeID;
}

// set for
void logic_Program::setForActiveTree(int for_id,int tree_id) {

	assert( mvmu_ModuleMap.count(for_id) > 0 ); //�ٶ� count ����0

	logic_BasicModule * tmpModule = mvmu_ModuleMap[for_id];

	assert( 2003 == tmpModule->getModuleType() ); //����forģ�飬����

	/// type һ����2003
	logic_ForModule *tmpForModule = (logic_ForModule *)tmpModule; //ǿ��ת����for module
	tmpForModule->setCurActiveTree( mvmu_ModuleId_TreeMap[tree_id] );

	return;
}

//if
void logic_Program::setIfActiveTree(int if_id,int branch_id,int tree_id) {

	assert( mvmu_ModuleMap.count(if_id) > 0 ); //�ٶ� count ����0

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	assert( 2004 == tmpModule->getModuleType() ); //����ifģ�飬����

	/// type һ����2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //ǿ��ת����if module
	tmpIfModule->setCurActiveTree( branch_id,mvmu_ModuleId_TreeMap[tree_id] ); //����С��0

	return;
}

//get ָ�� branch��int content
int logic_Program::getIfBranchContentInt(int if_id,int branch_id) {

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return -3;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //����ifģ�飬����
		return -4;

	/// type һ����2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //ǿ��ת����if module

	int content = tmpIfModule->getBranchContentInt(branch_id); //����С��0

	return content;
}

//string
std::string logic_Program::getIfBranchContentStr(int if_id,int branch_id) {

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return NULL;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //����ifģ�飬����
		return NULL;

	/// type һ����2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //ǿ��ת����if module

	std::string content = tmpIfModule->getBranchContentStr(branch_id);

	return content;
}

int logic_Program::setIfBranchContent(int if_id,int branch_id,int con_int) {

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return -3;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //����ifģ�飬����
		return -4;

	/// type һ����2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //ǿ��ת����if module

	int flag = tmpIfModule->setBranchContent(if_id,con_int);

	return flag;
}

//���� string
int logic_Program::setIfBranchContent(int if_id,int branch_id,std::string con_str) {

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return -3;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //����ifģ�飬����
		return -4;

	/// type һ����2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //ǿ��ת����if module

	int flag = tmpIfModule->setBranchContent(if_id,con_str);

	return flag;
}

//��ɾ if ��֧
int logic_Program::addIfBranch(int if_id) {

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return -3;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //����forģ�飬����
		return -4;

	/// type һ����2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //ǿ��ת����for module

	int newBranchId = tmpIfModule->addBranch();
	return newBranchId; //��������branch_id
}

//�ѵ㣬��Ҫɾ����֧��������
int logic_Program::delIfBranch(int if_id,int branch_id) {

	if( mvmu_ModuleMap.count(if_id) == 0 )
		return -3;

	logic_BasicModule * tmpModule = mvmu_ModuleMap[if_id];

	if( 2004 != tmpModule->getModuleType() ) //����ifģ�飬����
		return -4;

	/// type һ����2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //ǿ��ת����if module
	if( tmpIfModule->whDelBranch(branch_id) < 0 )
		return -1; //ɾ��ʧ��

	//�����²�������if�ڲ����
// 	std::vector<int > L = tmpIfModule->delBranch(branch_id);
// 
// 	//�ѻ�ô�ɾ��ģ����id�����ⲿɾ�����Լ����е�ģ��
// 	for (int i=0;i < L.size();++i) {
// 		
// 		if( this->delTreeThroughId(L[i]) < 0 )
// 			return -5;
// 	}

	return 0;
}

//ͨ��һ����id��ɾ����������ɾ�����г��ֵ�ģ�飬��Ҫɾ�����ߣ�
int logic_Program::delTreeThroughId(int id) {

	//�� id ����������
	if( mvmu_TreeMap.count(id) == 0 )
		return -1;

	logic_TreeNode * root = mvmu_TreeMap[id]->getRoot();
	recurs_DelTreeNodeModule(root); //����ģ��ʵ��

	mvmi_TreeId_For_IfIdMap.erase(mvmu_TreeMap[id]);
	SAFE_DELETE(mvmu_TreeMap[id]); //������
	//Ĩ�����ۼ�
	mvmu_TreeMap.erase(id);

	return 0;
}

//��ȫɾ��һ�������нڵ��������Ϣ������ʵ��map��connection map��
void logic_Program::recurs_DelTreeNodeModule(logic_TreeNode *some) {

	///// do sth here
	int tmpId = some->getID();
	if( mvmu_ModuleMap.count(tmpId) == 0 )
		assert(false);

	logic_BasicModule * tmpModule = mvmu_ModuleMap[tmpId];
	mvmu_ModuleMap.erase(tmpId);
	mvmu_ModuleId_TreeMap.erase(tmpId);
	SAFE_DELETE(tmpModule);

	//��������
	for( map<whPort ,whPort >::iterator it = mvvu_Conn_From_ToMap.begin(); it != mvvu_Conn_From_ToMap.end(); ++it ) {

		if( tmpId == it->first.moduleId ) {

			//��� from �Ǹ�ģ�飬������� outModule ��ؾ���Ҫɾ��
			whPort outPort = it->first;
			whPort inPort = mvvu_Conn_From_ToMap[outPort];
			mvvu_Conn_From_ToMap.erase(outPort);
			mvvu_Conn_To_FromMap.erase(inPort);

		}else if(tmpId == it->second.moduleId) {

			//��� to �Ǹ�ģ��
			whPort outPort = it->first;   // �൱�� whPort inPort = it->second;
			whPort inPort = mvvu_Conn_From_ToMap[outPort];
			mvvu_Conn_From_ToMap.erase(outPort);
			mvvu_Conn_To_FromMap.erase(inPort);
		}
	}

	//�� getAllTreeNodeId() ���ã��ݹ�get id
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++) {
		recurs_DelTreeNodeModule(some->mvvu_Children[i]);
	}
}

/// \brief ģ���������
int logic_Program::paraConnect(int out_m_id,int out_para_id,int in_m_id,int in_para_id) {

	assert( out_m_id != in_m_id );

	assert( mvmu_ModuleMap.count(out_m_id) * mvmu_ModuleMap.count(in_m_id) != 0 ); //����Ҳ�������

	logic_BasicPara * outPara = mvmu_ModuleMap[out_m_id]->getPara(out_m_id);
	logic_BasicPara * inPara = mvmu_ModuleMap[in_m_id]->getPara(in_m_id);

	if( NULL == outPara || NULL == inPara ) {

		//û����ô�������ֱ�Ӵ�
		//assert(false);
		return -1;
	}

	//����Ƿ��� in �� out
	if( outPara->getParaIOType() != PARA_OUT
		|| inPara->getParaIOType() != PARA_IN
		) {
		//assert(false);
		return -2;
	}

	//������� map
	whPort outPort;
	outPort.moduleId = out_m_id;
	outPort.paraId = out_para_id;

	whPort inPort;
	inPort.moduleId = in_m_id;
	inPort.paraId = in_para_id;

	if( mvvu_Conn_From_ToMap.count(outPort)
		* mvvu_Conn_To_FromMap.count(inPort) >0
		)
		return -3; //����Ѿ�����

	//��� inModule �Ƿ��� outModule ���ȣ�����������򲻿�������
	logic_Tree * out_m_tree = mvmu_ModuleId_TreeMap[out_m_id];
	bool flag = out_m_tree->isAncestor(out_m_id,in_m_id);

	//��� flag �� false���������
	if( NULL == flag ) {

		mvvu_Conn_From_ToMap[outPort] = inPort;
		mvvu_Conn_To_FromMap[inPort] = outPort;
		return 0;
	}else {
		return -4; //���� inModule �� outModule ���ȣ����ܹ�������
	}
}

//ȡ������
//��ͨ�� isOut ����outModule����inModuleɾ��
void logic_Program::outParaDisconnect(int out_m_id,int out_para_id) {

	assert( mvmu_ModuleMap.count(out_m_id) != 0 ); //����Ҳ�������

	logic_BasicPara * outPara = mvmu_ModuleMap[out_m_id]->getPara(out_m_id);

	if( NULL == outPara ) {

		//û����ô�������ֱ�Ӵ�
		assert(false);
	}

	//����Ƿ��� out
	if( outPara->getParaIOType() != PARA_OUT ) {

		assert(false);
	}

	//��� Port
	whPort outPort;
	outPort.moduleId = out_m_id;
	outPort.paraId = out_para_id;

	if( mvvu_Conn_From_ToMap.count(outPort) == 0 )
		assert(false);

	whPort inPort = mvvu_Conn_From_ToMap[outPort];

	//ɾ��map ��Ա
	mvvu_Conn_From_ToMap.erase(outPort);
	mvvu_Conn_To_FromMap.erase(inPort);

	return;
}

void logic_Program::inParaDisconnect(int in_m_id,int in_para_id) {

	assert( mvmu_ModuleMap.count(in_m_id) != 0 ); //����Ҳ�������

	logic_BasicPara * inPara = mvmu_ModuleMap[in_m_id]->getPara(in_m_id);

	if( NULL == inPara ) {

		//û����ô�������ֱ�Ӵ�
		assert(false);
	}

	//����Ƿ��� in
	if( inPara->getParaIOType() != PARA_IN ) {
			assert(false);
	}

	//������� map
	whPort inPort;
	inPort.moduleId = in_m_id;
	inPort.paraId = in_para_id;

	if( mvvu_Conn_To_FromMap.count(inPort) == 0 )
		assert(false);

	whPort outPort = mvvu_Conn_To_FromMap[inPort];

	//ɾ��map ��Ա
	mvvu_Conn_From_ToMap.erase(outPort);
	mvvu_Conn_To_FromMap.erase(inPort);

	return;
}

//for move��ͨ����
int logic_Program::backInsSingMoveFor(int cur_m_id,int pre_m_id,int for_id) {

	assert( pre_m_id >= 0 );

	//////pre_m_id������for��
	assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[pre_m_id] ) );

	logic_ForModule * tmpForModule = this->getForModuleById(for_id);

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id)) 
		*(mvmu_ModuleMap.count(for_id)) ) {
		return -2; // ���� cur_m_id �� pre_m_id ��Ҫ��
	}

	// cur_id �����ǿ�ʼģ��
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
		assert(false);
		return -3; //ģ�����ʹ���
	}

	//ע�������½�module��ֻ�ô������ڵ㼴��

	///// step1�����������ڵ�
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //��ɾ����������ҵ��������
	logic_Tree *insTree = NULL;
	if( 0 == pre_m_id ) {  ////////////�����������ǳ����������Σ��

		//���ǰ��һ�ÿ���

		///�����ǰ�������ͬʱ���ǡ�Ψһģ�顿�ǿ��Եģ���if����for�ƹ���

		logic_TreeNode tmpCurNode( *(oldTree->node_search(cur_m_id)) ) ; //������쵽ջ

		if ( tmpCurNode.mvvu_Children.size() > 1 ) {
			//������Ӳ���һ��������
			return -4;
		}

		tmpCurNode.mvu_Parent = 0;
		tmpCurNode.mvvu_Children.clear();

		logic_TreeNode *tmpPassNode = new logic_TreeNode(tmpCurNode); //������쵽��
		insTree = new logic_Tree(tmpPassNode); //�½�һ��������nodeҲ�����½������������delnode��

		mvmu_TreeMap[insTree->mvi_TreeID] = insTree;

		///////////////////////////////���⴦��for�ĵط�///////////////////////////////

		///
		/// \brief root����for
		///
		this->mvmi_TreeId_For_IfIdMap[mvmu_TreeMap[cur_m_id]] = for_id; //����forģ��ӳ��
		tmpForModule->addTree(mvmu_TreeMap[cur_m_id]); //add tree

		////////////////////////////////////////////////////////////////////////////////

	}else {

		////// pre_m_id ��Ϊ0

		//////pre_m_id������for��
		assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[pre_m_id] ) );

		/////����Ѵ��ڣ�ֱ���ҵ���������
		insTree = mvmu_ModuleId_TreeMap[pre_m_id];
		insTree->append_node(pre_m_id,cur_m_id);
	}

	///// step2��ɾ�������ڵ㣨ע���˴��������ж�����ӣ�

	if( cur_m_id != oldTree->mvi_TreeID ) {

		//��������
		oldTree->del_node(cur_m_id);
	}else if(cur_m_id == oldTree->mvi_TreeID ) {

		if ( oldTree->getRoot()->mvvu_Children.size()==0 ) {

			//����Ψһģ�飬ɾ������ ���������֧ pre_m_id Ҳ����Ϊ0 ��

			///////////////////////////////���⴦��if��for�ĵط�///////////////////////////////

			///
			/// \brief root�Ƴ�if��for
			///
			if( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ) {

				tmpForModule->delTree(oldTree);
				mvmi_TreeId_For_IfIdMap.erase(oldTree);
			}

			///////////////////////////////////////////////////////////////////////////////////

			SAFE_DELETE(oldTree);
			mvmu_TreeMap.erase(cur_m_id);

			// Step3���������ڴ˴�����Ȼ��return�ˣ�����
			mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

			return 0; //��������
		}else {
			//����Ψһģ��

			oldTree->setFirstChildAsRoot();
		}

	}

	// Step3������
	mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

	return 0; //��������

}

int logic_Program::frontInsSingMoveFor(int cur_m_id,int post_m_id,int for_id) {

	assert(post_m_id>0);

	//////post_m_id������for��
	assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[post_m_id] ) );

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(post_m_id))
		*(mvmu_ModuleMap.count(for_id)) ) {
		return -2; //û�ҵ������
	}

	//��� post_m_id �ǿ�ʼ
	if ( mvmu_ModuleMap[post_m_id]->getModuleType() == 2001 ) {
			return -3; //ģ�����ʹ���
	}

	//ע�������½�module��ֻ�ô������ڵ㼴��

	///// step1�����������ڵ�
	logic_Tree *insTree = mvmu_ModuleId_TreeMap[post_m_id]; //��������
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //��ɾ����

	int oldRootId = insTree->mvi_TreeID;
	if( post_m_id == oldRootId ) {

		//������ڵ�Ҫ����ԭ��root֮ǰ
		mvmu_TreeMap.erase(post_m_id);
		insTree->exchangeRoot(cur_m_id);
	}else {

		//��������ط�
		insTree->insert_node(insTree->getPreId(post_m_id),post_m_id,cur_m_id);
	}

	mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

	///// step2��ɾ�������ڵ㣨ע���˴��������ж�����ӣ�
	if( cur_m_id != oldTree->mvi_TreeID ) {

		//��������
		oldTree->del_node(cur_m_id);
	}else if(cur_m_id == oldTree->mvi_TreeID 
		|| oldTree->getRoot()->mvvu_Children.size()==0 ) {

			///////////////////////////////���⴦��if��for�ĵط�///////////////////////////////

			///
			/// \brief root�Ƴ�if��for
			///
			logic_ForModule * tmpForModule = this->getForModuleById(for_id);
			if( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ) {

				tmpForModule->delTree(oldTree);
				mvmi_TreeId_For_IfIdMap.erase(oldTree);
			}

			///////////////////////////////////////////////////////////////////////////////////

			//����Ψһģ�飬ɾ����
			SAFE_DELETE(oldTree);
			mvmu_TreeMap.erase(cur_m_id);
	}

	//ֻ�� post_m_id �Ǹ���������Ÿ���tree map
	if( post_m_id == oldRootId )
		mvmu_TreeMap[cur_m_id] = insTree;

	return 0; //��������
}

int logic_Program::backInsMultiMoveFor(int cur_m_id,int pre_m_id,int for_id) {

	//////pre_m_id������for��
	assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[pre_m_id] ) );

	//////cur_m_id �� pre_m_id ������һ��for��
	logic_Tree* cur_m_tree = mvmu_ModuleId_TreeMap[cur_m_id];
	logic_Tree* pre_m_tree = mvmu_ModuleId_TreeMap[pre_m_id];
	assert( mvmi_TreeId_For_IfIdMap[cur_m_tree] == mvmi_TreeId_For_IfIdMap[pre_m_tree] );

	/// �ظ� backInsMultiMove ����
	/// �ظ� addLeafMove ����
	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id))
		*(mvmu_ModuleMap.count(for_id)) ) {
		return -2; // ���� cur_m_id �� pre_m_id for_id ��Ҫ��
	}

	//��� cur_id ģ���ǿ�ʼ
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
		assert(false);
		return -3; //ģ�����ʹ���
	}

	//ע�������½�module��ֻ�ô������ڵ㼴��

	/////////////��ʼ/////////////

	///// step1��ɾ�������ڵ�
	///// ע��ɾ�������ǵ�һ������Ȼ del_node_notConn ������ɾ������ parent �ĺ���

	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //��ɾ����
	logic_TreeNode * insNode = oldTree->node_search(cur_m_id); //������ڵ㣨�����ڴ˴�Ѱ�ң�

	if ( insNode->mvvu_Children.size() == 0 ) {
		//����ֻ��һ������
		return -4;
	}

	if( cur_m_id != oldTree->mvi_TreeID ) {

		//��������
		oldTree->del_node_notConn(cur_m_id); //�Ͽ� oldTree ��˽ڵ������

	}else if(cur_m_id == oldTree->mvi_TreeID ) {

		//ROOT��ɾ����
		oldTree->del_node_notConn(cur_m_id); //�����������ֱ�ӽ�����root�ÿ�
		SAFE_DELETE(oldTree); //����ɾ����
		mvmu_TreeMap.erase(cur_m_id);

		///////////////////////////////���⴦��if��for�ĵط�///////////////////////////////

		///
		/// \brief root�Ƴ�if��for
		///
		logic_ForModule * tmpForModule = this->getForModuleById(for_id);
		assert( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ); //��Ȼ��ͬһ��for��

		tmpForModule->delTree(oldTree);
		mvmi_TreeId_For_IfIdMap.erase(oldTree);

		///////////////////////////////////////////////////////////////////////////////////
	}

	///// step2�������½ڵ�
	logic_Tree *insTree = NULL;
	if( 0 == pre_m_id ) { 
		//���ǰ��һ�ÿ���

		insTree = new logic_Tree(insNode); //�½�һ����

		mvmu_TreeMap[insTree->mvi_TreeID] = insTree;
		mvmu_ModuleId_TreeMap[cur_m_id] = insTree;

	}else {
		/////����Ѵ��ڣ�ֱ���ҵ���������
		insTree = mvmu_ModuleId_TreeMap[pre_m_id];

		logic_TreeNode * preNode = insTree->node_search(pre_m_id); //pre_m_id�ڵ�
		//��� pre_m_id ����Ҷ�ӽڵ㣬���󷵻�
		if(preNode->mvvu_Children.size()>0) {
			return -4;
		}

		insTree->add_node(pre_m_id,insNode);

	}

	///// step3������ module treeӳ��
	recurs_update(insTree,insNode);

	return 0; //��������
}

int logic_Program::frontInsMultiMoveFor(int cur_m_id,int post_m_id,int for_id) {

	//////post_m_id������for��
	assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[post_m_id] ) );

	//////cur_m_id �� post_m_id ������һ��for��
	logic_Tree* cur_m_tree = mvmu_ModuleId_TreeMap[cur_m_id];
	logic_Tree* pre_m_tree = mvmu_ModuleId_TreeMap[post_m_id];
	assert( mvmi_TreeId_For_IfIdMap[cur_m_tree] == mvmi_TreeId_For_IfIdMap[pre_m_tree] );

	/// �ظ� frontInsMultiMove ����
	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(post_m_id))
		*(mvmu_ModuleMap.count(for_id)) ) {
		return -2; //û�ҵ������
	}

	//��� post_m_id ģ���ǿ�ʼ
	if ( mvmu_ModuleMap[post_m_id]->getModuleType() == 2001 ) {
			return -3; //ģ�����ʹ���
	}

	//ע�������½�module��ֻ�ô������ڵ㼴��

	///// step1�����������ڵ�
	/////!!!!!!!!!!!!�ر�ע���������� insTree �� oldtree ����������ת��Ϊ���!!!!!!!!!!!!!!
	logic_Tree *insTree = mvmu_ModuleId_TreeMap[cur_m_id]; //��������
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[post_m_id]; //��ɾ����

	//��� post_m_id ���Ǹ��ڵ㣬���󷵻�
	if( post_m_id!=oldTree->mvi_TreeID ) {
		return -4;
	}

	///////////////////////////////////////
	logic_TreeNode * insNode = oldTree->getRoot(); //������ڵ�
	insTree->add_node(cur_m_id,insNode);

	///// step2��ɾ�������ڵ�

	//��Ȼ��ROOT��ֱ��ɾ����
	oldTree->del_node_notConn(post_m_id); //�Ͽ� oldTree �˽ڵ�����������
	SAFE_DELETE(oldTree); //����ɾ����
	mvmu_TreeMap.erase(post_m_id);

	///////////////////////////////���⴦��if��for�ĵط�///////////////////////////////

	///
	/// \brief root�Ƴ�if��for
	///
	logic_ForModule * tmpForModule = this->getForModuleById(for_id);
	assert( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ); //��Ȼ��ͬһ��for��

	tmpForModule->delTree(oldTree);
	mvmi_TreeId_For_IfIdMap.erase(oldTree);

	///////////////////////////////////////////////////////////////////////////////////

	///// step3������ module treeӳ��

	recurs_update(insTree,insNode);

	return 0; //��������
}

int logic_Program::addLeafMoveFor(int cur_m_id,int pre_m_id,int for_id) {

	//////pre_m_id������for��
	assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[pre_m_id] ) );

	//////cur_m_id �� pre_m_id ������һ��for��
	logic_Tree* cur_m_tree = mvmu_ModuleId_TreeMap[cur_m_id];
	logic_Tree* pre_m_tree = mvmu_ModuleId_TreeMap[pre_m_id];
	assert( mvmi_TreeId_For_IfIdMap[cur_m_tree] == mvmi_TreeId_For_IfIdMap[pre_m_tree] );

	/// �ظ� addLeafMove ����
	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id))
		*(mvmu_ModuleMap.count(for_id)) ) {
		return -2; // ���� cur_m_id �� pre_m_id for_id ��Ҫ��
	}

	//��� cur_id ģ���ǿ�ʼ
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
		return -3; //ģ�����ʹ���
	}

	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //��ɾ����
	//�ýڵ�����Ǹ����ĸ��ڵ�
	if( oldTree->mvi_TreeID != cur_m_id )
		assert(false);

	logic_Tree *insTree = mvmu_ModuleId_TreeMap[pre_m_id];
	logic_TreeNode * insNode = insTree->node_search(pre_m_id); //������ڵ�
	logic_TreeNode * curNode = oldTree->getRoot(); //��ǰ�ڵ�

	/// Step1�������½ڵ�
	insNode->mvvu_Children.push_back(curNode);

	/// Step2��ɾ������map��Ϣ
	mvmu_TreeMap.erase(cur_m_id);
	oldTree->setRoot(NULL);
	SAFE_DELETE(oldTree);

	///////////////////////////////���⴦��if��for�ĵط�///////////////////////////////

	///
	/// \brief root�Ƴ�if��for
	///
	logic_ForModule * tmpForModule = this->getForModuleById(for_id);
	assert( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ); //��Ȼ��һ��for��

	tmpForModule->delTree(oldTree);
	mvmi_TreeId_For_IfIdMap.erase(oldTree);

	///////////////////////////////////////////////////////////////////////////////////

	/// Step3������ģ����map��Ϣ
	recurs_update(insTree,curNode);

	return 0;

}

//ͨ��id�õ�ģ��
logic_ForModule* logic_Program::getForModuleById(int id) {

	assert( mvmu_ModuleMap.count(id) > 0 ); //�ٶ� count ����0

	logic_BasicModule * tmpModule = mvmu_ModuleMap[id];
	assert( 2003 == tmpModule->getModuleType() ); //����forģ�飬����

	/// type һ����2003
	logic_ForModule *tmpForModule = (logic_ForModule *)tmpModule; //ǿ��ת����for module

	return tmpForModule;
}

logic_IfModule* logic_Program::getIfModuleById(int id) {

	assert( mvmu_ModuleMap.count(id) > 0 ); //�ٶ� count ����0

	logic_BasicModule * tmpModule = mvmu_ModuleMap[id];

	assert( 2004 == tmpModule->getModuleType() ); //����ifģ�飬����

	/// type һ����2004
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //ǿ��ת����if module

	return tmpIfModule;
}

//rootId = moduleId*100000
//�ϳ�for��if����tree map�е�id
inline int logic_Program::composeTreeId(int for_id) {

	return for_id * ACTIVE_TREE_MAP_FACTOR;
}

//rootId = moduleId*100000+branchId
inline int logic_Program::composeTreeId(int if_id,int branch_id) {

	return if_id * ACTIVE_TREE_MAP_FACTOR + branch_id;
}

//ֻ�ڽӵ�activeTree���ڵ��ʱ�����
int logic_Program::appendActiveTreeMoveFor(int cur_m_id,int for_id) {

	//��ĳһģ��ӵ� for_id activeTree����

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(for_id)) ) {
		assert(false);
		return -2; // ���� cur_m_id �� for_id ��Ҫ��
	}

	//��� cur_id ģ���ǿ�ʼ
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
		assert(false);
		return -3; //ģ�����ʹ���
	}

	//�õ� activeTree
	logic_Tree * curActiveTree = this->getForModuleById(for_id)->getCurActiveTree();
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id];

	///// Step1������ڵ�
	curActiveTree->append_node(-1,cur_m_id);


	///// step2��ɾ�������ڵ㣨ע���˴��������ж�����ӣ�
	if( cur_m_id != oldTree->mvi_TreeID ) {

		//��������
		oldTree->del_node(cur_m_id);
	}else if(cur_m_id == oldTree->mvi_TreeID ) {

		if ( oldTree->getRoot()->mvvu_Children.size()==0 ) {

			//����Ψһģ�飬ɾ������ ���������֧ pre_m_id Ҳ����Ϊ0 ��

			///////////////////////////////���⴦��if��for�ĵط�///////////////////////////////

			///
			/// \brief root�Ƴ�if��for
			///
			if( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ) {
				logic_ForModule * tmpForModule = this->getForModuleById(for_id);
				tmpForModule->delTree(oldTree);
				mvmi_TreeId_For_IfIdMap.erase(oldTree);
			}

			///////////////////////////////////////////////////////////////////////////////////

			SAFE_DELETE(oldTree);
			mvmu_TreeMap.erase(cur_m_id);

			// Step3���������ڴ˴�����Ȼ��return�ˣ�����
			mvmu_ModuleId_TreeMap[cur_m_id] = curActiveTree;

			return 0; //��������
		}else {
			//����Ψһģ��

			oldTree->setFirstChildAsRoot();
		}

	}

	// Step3������
	mvmu_ModuleId_TreeMap[cur_m_id] = curActiveTree;

	return 0;
}

//activeTreeֱ�����Ҷ��
int logic_Program::addLeafActiveTreeMoveFor(int cur_m_id,int for_id) {

	//////cur_m_id �� activeTree ������ͬһ��for��
	logic_Tree* cur_m_tree = mvmu_ModuleId_TreeMap[cur_m_id];
	assert( mvmi_TreeId_For_IfIdMap[cur_m_tree] == for_id );

	/// �ظ� addLeafMove ����
	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(for_id)) ) {
			return -2; // ���� cur_m_id �� for_id ��Ҫ��
	}

	//��� cur_id ģ���ǿ�ʼ
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
		return -3; //ģ�����ʹ���
	}

	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //��ɾ����
	//�ýڵ�����Ǹ����ĸ��ڵ�
	if( oldTree->mvi_TreeID != cur_m_id )
		assert(false);

	logic_ForModule * tmpForModule = this->getForModuleById(for_id);

	logic_Tree *insTree = tmpForModule->getCurActiveTree();
	logic_TreeNode * insNode = insTree->getRoot(); //������ڵ�
	logic_TreeNode * curNode = oldTree->getRoot(); //��ǰ�ڵ�

	/// Step1�������½ڵ�
	insNode->mvvu_Children.push_back(curNode);

	/// Step2��ɾ������map��Ϣ
	mvmu_TreeMap.erase(cur_m_id);
	oldTree->setRoot(NULL);
	SAFE_DELETE(oldTree);

	///////////////////////////////���⴦��if��for�ĵط�///////////////////////////////

	///
	/// \brief root�Ƴ�if��for
	///
	assert( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ); //��Ȼ��һ��for��

	tmpForModule->delTree(oldTree);
	mvmi_TreeId_For_IfIdMap.erase(oldTree);

	///////////////////////////////////////////////////////////////////////////////////

	/// Step3������ģ����map��Ϣ
	recurs_update(insTree,curNode);

	return 0;
}

//��ģ���²���activeTree
int logic_Program::appendActiveTreeInsertFor(int m_id,int m_type,int for_id) {

	assert( mvmu_ModuleMap.count(for_id)>0 );

	// step1����ɭ���м������id

	if ( m_type == 2001 ) {
		return false;
	}

	logic_ForModule * tmpForModule = this->getForModuleById(for_id);
	logic_Tree *tree = tmpForModule->getCurActiveTree();
	tree->append_node(-1,m_id);


	// step2�������������moduleʵ��
	this->add_Module(m_id,m_type);

	return 0;
}
