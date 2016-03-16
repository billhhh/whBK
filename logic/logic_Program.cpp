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

logic_Program::logic_Program(int id, std::string prog_name,std::map <int, logic_BasicModule *> imap)
	:mvs_ProgId(id),mvs_ProgName(prog_name),initModuleMap(imap)
{
	Init();
}

logic_Program::~logic_Program()
{
	prog_Destroy();
}

//����id,prgname,�������ݶ�����
logic_Program* logic_Program::copyPrg(logic_Program* newProgram)
{
	auto treeMap = getTreeMap();
	auto moduleMap = getModuleMap();
	auto moduleId_TreeMap = getModuleTreeMap();
	auto treeIn_IFFOR_Map = getForIfMap();
	auto fromToMap = getFromMap();
	auto toMap = getToMap();
	auto initModuleMap = getInit_m_map();
	auto varietyMap = getVarMap();

	newProgram->setTreeMap(treeMap);
	newProgram->setModuleMap(moduleMap);
	newProgram->setModuleTreeMap(mvmu_ModuleId_TreeMap);
	newProgram->setForIfMap(treeIn_IFFOR_Map);
	newProgram->setFromToMap(fromToMap);
	newProgram->setToFromMap(toMap);
	newProgram->setInitModuleMap(initModuleMap);
	newProgram->setInitVarMap(*varietyMap);

	return newProgram;

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

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!��̨��Ҫ�Լ�����2001����ǰ������
	//add_Tree(1);

	////����module�����һ����ʼģ��
	//logic_BasicModule *bm = new logic_BasicModule();
	//mvmu_ModuleMap.insert(pair<_IdDataType , logic_BasicModule *>(bm->mvi_ModuleID,bm));

	//mvmu_ModuleId_TreeMap[1] = mvmu_TreeMap[1];
}

void logic_Program::prog_Destroy()
{
	cout<<"����prog_Destroy"<<endl;


		//���ɭ��
	for(map<_IdDataType , logic_Tree *>::iterator it = mvmu_TreeMap.begin();it != mvmu_TreeMap.end(); ++it)
	{
		logic_Tree *tmpT = it->second;
		//tmpT->Destroy(tmpT->getRoot()); //������������Σ��Ѵ���
		SAFE_DELETE(tmpT);
	}

	//���mvmu_ModuleMap
	for(map<_IdDataType , logic_BasicModule *>::iterator it = mvmu_ModuleMap.begin();it != mvmu_ModuleMap.end(); ++it)
		SAFE_DELETE(it->second);



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
			mvmu_ModuleId_TreeMap,mvmi_TreeId_For_IfIdMap,mvvu_Conn_From_ToMap,mvvu_Conn_To_FromMap,
			*(this->initModuleMap[2003]));
		bm = tmpForModule;

		/// activeTree ��������forģ��
		//�õ�Ĭ��activeTree��ά��map
// 		logic_Tree * tmpActiveTree = tmpForModule->getCurActiveTree();
// 		mvmu_TreeMap[this->composeTreeId(moduleId)] = tmpActiveTree;

	}else if( 2004 == m_Type ) {

		//if
		logic_IfModule* tmpIfModule = new logic_IfModule(moduleId,mvmu_TreeMap,mvmu_ModuleMap,
			mvmu_ModuleId_TreeMap,mvmi_TreeId_For_IfIdMap,mvvu_Conn_From_ToMap,mvvu_Conn_To_FromMap,
			*(this->initModuleMap[2004]));
		bm = tmpIfModule;

		/// activeTree ��������ifģ��
		//�õ�Ĭ�ϵ�����branch activeTree��ά��map
// 		logic_Tree * tmpActiveTree = tmpIfModule->getCurActiveTree(1);
// 		mvmu_TreeMap[this->composeTreeId(moduleId,1)] = tmpActiveTree;
// 		tmpActiveTree = tmpIfModule->getCurActiveTree(2);
// 		mvmu_TreeMap[this->composeTreeId(moduleId,2)] = tmpActiveTree;

	}else //��ͨģ��
	{
		//bm = new logic_BasicModule(moduleId,m_Type);
		bm = new logic_BasicModule(moduleId,m_Type,*(this->initModuleMap[m_Type]));
	}

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

void logic_Program::setID(int id)
{
	mvs_ProgId = id;
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

	assert( mvmu_ModuleMap.count(pre_id)>=0 );

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

//��ģ����move
int logic_Program::backInsSingMove(int cur_m_id,int pre_m_id) {

	if ( pre_m_id != 0 && 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id)) ) {
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

		if( insTree->mvi_TreeID == oldTree->mvi_TreeID ) {

			//����Ǳ���ֱ��move
			if ( insTree->innerTreeBackInsSingMove(pre_m_id,cur_m_id) < 0 )
				return -6; //����move����
			else
				return 0; //��move��ֱ�ӷ���

		}else {
			//�����ƶ�
			insTree->append_node(pre_m_id,cur_m_id);
		}
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
	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id];  //��ɾ����

	int oldRootId = insTree->mvi_TreeID;
	if( post_m_id == oldRootId ) {

		//������ڵ�Ҫ����ԭ��root֮ǰ
		if ( insTree->mvi_TreeID != oldTree->mvi_TreeID ) { //���������ڵ���������

			if( insTree->exchangeRoot(cur_m_id) == false )
				return -5;

			//ֻ�� post_m_id �Ǹ���������Ÿ���tree map
			mvmu_TreeMap.erase(post_m_id);
			mvmu_TreeMap[cur_m_id] = insTree;
		} else {

			//���ڽ���������ɾ�������ڵ㣬��ǰ��ֹ
			if( insTree->innerTreeExchangeRoot(cur_m_id) >= 0 ) {

				//ֻ�� post_m_id �Ǹ���������Ÿ���tree map
				mvmu_TreeMap.erase(post_m_id);
				mvmu_TreeMap[cur_m_id] = insTree;

				return 0;
			} else {
				return -4; //���ڽ���ʧ��
			}
		}

	}else {

		if ( insTree->mvi_TreeID == oldTree->mvi_TreeID ) { //��������

			if( insTree->innerTreeFrontInsSingMove(cur_m_id,post_m_id) >=0 ) {

				//����������������ǰ��ֹ
				return 0;
			}else {
				return -6;
			}

		}
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

	return 0; //��������

}

//�����Ӻ��move
int logic_Program::backInsMultiMove(int cur_m_id,int pre_m_id) {

	if ( 0 != pre_m_id && 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id)) ) {
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

//������ǰ��move
////////////////ע����Ȼ�ǲ���һ��������ǰ��/////////////////
int logic_Program::frontInsMultiMove(int cur_m_id,int post_m_id) {

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id)) ) {
		return -2; //û�ҵ������
	}

	//��� post_m_id ģ���ǿ�ʼ
	if ( post_m_id != 0 && mvmu_ModuleMap[post_m_id]->getModuleType() == 2001 ) {
			return -3; //ģ�����ʹ���
	}

	//ע�������½�module��ֻ�ô������ڵ㼴��

	if( 0 == post_m_id ) {

		//�ղ�
		//�൱�� backInsMultiMove ������

		logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id];

		///// step1��ɾ�������ڵ㣬ͬʱ���Ͽ�������������
		logic_TreeNode * curNode = oldTree->node_search(cur_m_id);
		if( curNode->mvvu_Children.size() == 1 ) {

			logic_TreeNode * breakNode = curNode->mvvu_Children[0];
			oldTree->del_node_notConn(breakNode->getID());
			logic_Tree * newTree = new logic_Tree(breakNode);

			mvmu_TreeMap[newTree->getRoot()->getID()] = newTree;
			///// ���� module treeӳ�� insNode��֧
			recurs_update(newTree,newTree->getRoot());
		}else if( curNode->mvvu_Children.size() > 1 ) {
			assert(false);
		}

	} else {

		logic_Tree *insTree = mvmu_ModuleId_TreeMap[post_m_id]; //�²�����
		logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id];

		//��� post_m_id ���Ǹ��ڵ㣬���󷵻�
		if( post_m_id!=insTree->mvi_TreeID ) {
			return -4;
		}

		///// step1��ɾ�������ڵ㣬ͬʱ���Ͽ�������������
		logic_TreeNode * curNode = oldTree->node_search(cur_m_id);
		if( curNode->mvvu_Children.size() == 1 ) {

			logic_TreeNode * breakNode = curNode->mvvu_Children[0];
			oldTree->del_node_notConn(breakNode->getID());
			logic_Tree * newTree = new logic_Tree(breakNode);

			mvmu_TreeMap[newTree->getRoot()->getID()] = newTree;
			///// ���� module treeӳ�� insNode��֧
			recurs_update(newTree,newTree->getRoot());
		}else if( curNode->mvvu_Children.size() > 1 ) {
			assert(false);
		}
		
		///// step2�����������ڵ�

		logic_TreeNode * insNode = insTree->getRoot(); //������ڵ�
		oldTree->add_node(cur_m_id,insNode); //insTree�ӵ�oldTree��

		//��Ȼ��ROOT��ֱ��ɾ��ԭinsTree
		insTree->del_node_notConn(post_m_id); //��root��ֱ���ÿ�
		SAFE_DELETE(insTree); //����ɾ����
		mvmu_TreeMap.erase(post_m_id);

		///// ���� module treeӳ�� insNode��֧
		recurs_update(oldTree,insNode);

	}

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

	if ( addLeafCheckPre(cur_m_id,pre_m_id) < 0 ) {
		return -4;
	}

	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //��ɾ����
	//�ýڵ�����Ǹ����ĸ��ڵ�
	if( oldTree->mvi_TreeID != cur_m_id )
		assert(false);

	logic_Tree *insTree = mvmu_ModuleId_TreeMap[pre_m_id];
	logic_TreeNode * insNode = insTree->node_search(pre_m_id); //������ڵ�
	logic_TreeNode * curNode = oldTree->getRoot(); //��ǰ�ڵ�

	curNode->mvu_Parent = insNode;

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

std::map <int ,logic_Tree * > logic_Program::getModuleTreeMap()
{
	return mvmu_ModuleId_TreeMap;
}

void logic_Program::setModuleTreeMap(std::map <int, logic_Tree * > moduleTreeMap)
{
	mvmu_ModuleId_TreeMap = moduleTreeMap;
}

std::map <logic_Tree * ,int > logic_Program::getForIfMap()
{
	return mvmi_TreeId_For_IfIdMap;
}

void logic_Program::setForIfMap(std::map <logic_Tree *, int > forIfMap)
{
	mvmi_TreeId_For_IfIdMap = forIfMap;
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

bool logic_Program::addLeafModule(int pre_id,int m_id) {

	if ( 0 == pre_id ) {
		return false;
	}

	assert(mvmu_ModuleMap.count(pre_id)!=0); //������pre������

	

	return true;
}

int logic_Program::getModulePreId(int m_id) {

	if (mvmu_ModuleMap.count(m_id)==0) //�����ڣ�����
		return 0;

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

//�õ���ģ���������ĸ��ڵ��ģ��id
int logic_Program::getRootModuleId(int m_id)
{
	int rootModuleId = 0;

	if (mvmu_ModuleMap.count(m_id) == 0) //�����ڣ�����
		return rootModuleId;

	logic_Tree* theTree = getTreeFromId(m_id);
	logic_TreeNode* rootNode = theTree->getRoot();

	rootModuleId = rootNode->getID();
	return rootModuleId;
}

//��ѯ����module�Ƿ���ͬһ������
bool logic_Program::IsInSameTree(int cur_m_id, int other_m_id)
{
	assert(mvmu_ModuleMap.count(cur_m_id) != 0 && mvmu_ModuleMap.count(other_m_id)); //�ж��Ƿ����

	logic_Tree* oneTree = getTreeFromId(cur_m_id);
	logic_Tree* otherTree = getTreeFromId(other_m_id);
	
	if (oneTree == otherTree)
		return true;
	else
		return false;
}


std::vector<int > logic_Program::getForModuleRootPostId(int for_Id){
	std::vector<int > L;

	if (mvmu_ModuleMap.count(for_Id) == 0) //�����ڣ�����
		return L;

	auto forModule = (logic_ForModule*)mvmu_ModuleMap[for_Id];
	auto activeTree = forModule->getCurActiveTree();
	auto rootNode = activeTree->getRoot();
	for(int i = 0; i < rootNode->mvvu_Children.size();++i){
		L.push_back(rootNode->mvvu_Children.at(i)->getID());
	}

	return L;
}


std::vector<int > logic_Program::getIfModuleBranchPostId(int if_id, int local_branch_id)
{
	std::vector<int > L;

	if (mvmu_ModuleMap.count(if_id) == 0) //�����ڣ�����
		return L;

	auto IfModule = (logic_IfModule*)mvmu_ModuleMap[if_id];
	if (!IfModule->isBranchExist(local_branch_id))
		return L; 

	auto activeTree = IfModule->getCurActiveTree(local_branch_id);
	auto rootNode = activeTree->getRoot();
	for (int i = 0; i < rootNode->mvvu_Children.size(); ++i){
		L.push_back(rootNode->mvvu_Children.at(i)->getID());
	}

	return L;
}

int logic_Program::getForModuleEndPreId(int for_id)
{
	if (mvmu_ModuleMap.count(for_id) == 0) //�����ڣ�����
		return 0;

	auto forModule = (logic_ForModule*)mvmu_ModuleMap[for_id];
	auto activeTree = forModule->getCurActiveTree();
	auto preId = activeTree->getPreId(-2);
	
	return preId;
}

int	logic_Program::getIfModuleEndPreId(int if_id, int local_branch_id)
{
	if (mvmu_ModuleMap.count(if_id) == 0) //�����ڣ�����
		return 0;

	auto IfModule = (logic_IfModule*)mvmu_ModuleMap[if_id];
	if (!IfModule->isBranchExist(local_branch_id))
		return 0;

	auto activeTree = IfModule->getCurActiveTree(local_branch_id);
	auto preId = activeTree->getPreId(-2);

	return preId;
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
		{
			logic_BasicPara *tInitPara = mvmu_ModuleMap[m_id]->getInitPara(p_id);
			res = tInitPara->mvs_Value;
			break;
		}

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

std::map<whPort, whPort > logic_Program::getFromMap()
{
	return mvvu_Conn_From_ToMap;
}

std::map<whPort, whPort> logic_Program::getToMap()
{
	return mvvu_Conn_To_FromMap;
}


void logic_Program::setFromToMap(std::map<whPort, whPort > fromToMap)
{
	mvvu_Conn_From_ToMap = fromToMap;
}

void logic_Program::setToFromMap(std::map<whPort, whPort > toFromMap)
{
	mvvu_Conn_To_FromMap = toFromMap;
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

	if( -1 == pre_id ) //��activeTree����ֱ�Ӳ���һ��ģ��
		return this->appendActiveTreeInsertIf(m_id,m_type,if_id,branch_id);

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
	logic_IfModule *tmpIfModule = (logic_IfModule *)tmpModule; //ǿ��ת����if module

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

	if (pre_m_id > 0)
	{
		//////���pre_m_id != 0 ��pre_m_id������for��
		assert(mvmi_TreeId_For_IfIdMap.count(mvmu_ModuleId_TreeMap[pre_m_id]));

		if (0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id))
			*(mvmu_ModuleMap.count(for_id))) {
			return -2; // ���� cur_m_id �� pre_m_id ��Ҫ��
		}

		// cur_id �����ǿ�ʼģ��
		if (mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001) {
			assert(false);
			return -3; //ģ�����ʹ���
		}
	}
	logic_ForModule * tmpForModule = this->getForModuleById(for_id);

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

		if( insTree->mvi_TreeID == oldTree->mvi_TreeID ) {

			//����Ǳ���ֱ��move
			if ( insTree->innerTreeBackInsSingMove(pre_m_id,cur_m_id) < 0 )
				return -6; //����move����
			else
				return 0; //��move��ֱ�ӷ���

		}else {
			//�����ƶ�
			insTree->append_node(pre_m_id,cur_m_id);
		}
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
		if ( insTree->mvi_TreeID != oldTree->mvi_TreeID ) { //���������ڵ���������

			if( insTree->exchangeRoot(cur_m_id) == false )
				return -5;

			//ֻ�� post_m_id �Ǹ���������Ÿ���tree map
			mvmu_TreeMap.erase(post_m_id);
			mvmu_TreeMap[cur_m_id] = insTree;
		} else {

			//���ڽ���������ɾ�������ڵ㣬��ǰ��ֹ
			if( insTree->innerTreeExchangeRoot(cur_m_id) >= 0 ) {

				//ֻ�� post_m_id �Ǹ���������Ÿ���tree map
				mvmu_TreeMap.erase(post_m_id);
				mvmu_TreeMap[cur_m_id] = insTree;

				return 0;
			} else {
				return -4; //���ڽ���ʧ��
			}
		}

	}else {

		if ( insTree->mvi_TreeID == oldTree->mvi_TreeID ) { //��������

			if( insTree->innerTreeFrontInsSingMove(cur_m_id,post_m_id) >=0 ) {

				//����������������ǰ��ֹ
				return 0;
			}else {
				return -6;
			}

		}
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

	logic_ForModule * tmpForModule = this->getForModuleById(for_id);

	/// �ظ� frontInsMultiMove ����
	if( 0 == post_m_id ) {

		//�ղ�
		//�൱�� backInsMultiMove ������

		logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id];

		///// step1��ɾ�������ڵ㣬ͬʱ���Ͽ�������������
		logic_TreeNode * curNode = oldTree->node_search(cur_m_id);
		if( curNode->mvvu_Children.size() == 1 ) {

			logic_TreeNode * breakNode = curNode->mvvu_Children[0];
			oldTree->del_node_notConn(breakNode->getID());
			logic_Tree * newTree = new logic_Tree(breakNode);

			mvmu_TreeMap[newTree->getRoot()->getID()] = newTree;

			/////////////��for�м�����///////////
			mvmi_TreeId_For_IfIdMap[newTree] = for_id;
			tmpForModule->addTree(newTree);

			///// ���� module treeӳ�� insNode��֧
			recurs_update(newTree,newTree->getRoot());
		}else if( curNode->mvvu_Children.size() > 1 ) {
			assert(false);
		}

	} else {

		logic_Tree *insTree = mvmu_ModuleId_TreeMap[post_m_id]; //�²�����
		logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id];

		//��� post_m_id ���Ǹ��ڵ㣬���󷵻�
		if( post_m_id!=insTree->mvi_TreeID ) {
			return -4;
		}

		///// step1��ɾ�������ڵ㣬ͬʱ���Ͽ�������������
		logic_TreeNode * curNode = oldTree->node_search(cur_m_id);
		if( curNode->mvvu_Children.size() == 1 ) {

			logic_TreeNode * breakNode = curNode->mvvu_Children[0];
			oldTree->del_node_notConn(breakNode->getID());
			logic_Tree * newTree = new logic_Tree(breakNode);

			mvmu_TreeMap[newTree->getRoot()->getID()] = newTree;

			/////////////��for�м�����///////////
			mvmi_TreeId_For_IfIdMap[newTree] = for_id;
			tmpForModule->addTree(newTree);

			///// ���� module treeӳ�� insNode��֧
			recurs_update(newTree,newTree->getRoot());
		}else if( curNode->mvvu_Children.size() > 1 ) {
			assert(false);
		}

		///// step2�����������ڵ�

		logic_TreeNode * insNode = insTree->getRoot(); //������ڵ�
		oldTree->add_node(cur_m_id,insNode); //insTree�ӵ�oldTree��

		//��Ȼ��ROOT��ֱ��ɾ��ԭinsTree
		insTree->del_node_notConn(post_m_id); //��root��ֱ���ÿ�
		SAFE_DELETE(insTree); //����ɾ����
		mvmu_TreeMap.erase(post_m_id);

		///////////////////////////////���⴦��if��for�ĵط�///////////////////////////////

		///
		/// \brief ��for��ɾ����
		///
		assert( mvmi_TreeId_For_IfIdMap.count(insTree) >0 ); //��Ȼ��ͬһ��for��

		tmpForModule->delTree(insTree);
		mvmi_TreeId_For_IfIdMap.erase(insTree);

		///////////////////////////////////////////////////////////////////////////////////

		///// ���� module treeӳ�� insNode��֧
		recurs_update(oldTree,insNode);

	}

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

	if ( addLeafCheckPre(cur_m_id,pre_m_id) < 0 ) {
		return -4;
	}

	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //��ɾ����
	//�ýڵ�����Ǹ����ĸ��ڵ�
	if( oldTree->mvi_TreeID != cur_m_id )
		assert(false);

	logic_Tree *insTree = mvmu_ModuleId_TreeMap[pre_m_id];
	logic_TreeNode * insNode = insTree->node_search(pre_m_id); //������ڵ�
	logic_TreeNode * curNode = oldTree->getRoot(); //��ǰ�ڵ�

	curNode->mvu_Parent = insNode;

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

	curNode->mvu_Parent = insNode;

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

///
/// \brief ���⴦��if��move����
///
int logic_Program::backInsSingMoveIf(int cur_m_id,int pre_m_id,int if_id,int branch_id) {


	assert( pre_m_id >= 0 );

	//////pre_m_id������if��
	assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[pre_m_id] ) );

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id)) 
		*(mvmu_ModuleMap.count(if_id)) ) {
			return -2; // ���� cur_m_id �� pre_m_id ��Ҫ��
	}

	logic_IfModule * tmpIfModule = this->getIfModuleById(if_id); //�ж�branch��֧�Ƿ����
	assert( tmpIfModule->isBranchExist(branch_id) == true );

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

		///////////////////////////////���⴦��if�ĵط�///////////////////////////////

		///
		/// \brief root����if
		///
		this->mvmi_TreeId_For_IfIdMap[mvmu_TreeMap[cur_m_id]] = if_id; //����ģ��ӳ��
		tmpIfModule->addTree(branch_id,mvmu_TreeMap[cur_m_id]); //add tree

		////////////////////////////////////////////////////////////////////////////////

	}else {

		////// pre_m_id ��Ϊ0

		//////pre_m_id������if��
		assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[pre_m_id] ) );

		/////����Ѵ��ڣ�ֱ���ҵ���������
		insTree = mvmu_ModuleId_TreeMap[pre_m_id];

		if( insTree->mvi_TreeID == oldTree->mvi_TreeID ) {

			//����Ǳ���ֱ��move
			if ( insTree->innerTreeBackInsSingMove(pre_m_id,cur_m_id) < 0 )
				return -6; //����move����
			else
				return 0; //��move��ֱ�ӷ���

		}else {
			//�����ƶ�
			insTree->append_node(pre_m_id,cur_m_id);
		}
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

				tmpIfModule->delTree(oldTree);
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

int logic_Program::frontInsSingMoveIf(int cur_m_id,int post_m_id,int if_id,int branch_id) {

	assert(post_m_id>0);

	//////post_m_id������if��
	assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[post_m_id] ) );

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(post_m_id))
		*(mvmu_ModuleMap.count(if_id)) ) {
			return -2; //û�ҵ������
	}

	logic_IfModule * tmpIfModule = this->getIfModuleById(if_id); //�ж�branch��֧�Ƿ����
	assert( tmpIfModule->isBranchExist(branch_id) == true );

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
		if ( insTree->mvi_TreeID != oldTree->mvi_TreeID ) { //���������ڵ���������

			if( insTree->exchangeRoot(cur_m_id) == false )
				return -5;

			//ֻ�� post_m_id �Ǹ���������Ÿ���tree map
			mvmu_TreeMap.erase(post_m_id);
			mvmu_TreeMap[cur_m_id] = insTree;
		} else {

			//���ڽ���������ɾ�������ڵ㣬��ǰ��ֹ
			if( insTree->innerTreeExchangeRoot(cur_m_id) >= 0 ) {

				//ֻ�� post_m_id �Ǹ���������Ÿ���tree map
				mvmu_TreeMap.erase(post_m_id);
				mvmu_TreeMap[cur_m_id] = insTree;

				return 0;
			} else {
				return -4; //���ڽ���ʧ��
			}
		}

	}else {

		if ( insTree->mvi_TreeID == oldTree->mvi_TreeID ) { //��������

			if( insTree->innerTreeFrontInsSingMove(cur_m_id,post_m_id) >=0 ) {

				//����������������ǰ��ֹ
				return 0;
			}else {
				return -6;
			}

		}
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
			if( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ) {

				tmpIfModule->delTree(oldTree);
				mvmi_TreeId_For_IfIdMap.erase(oldTree);
			}

			///////////////////////////////////////////////////////////////////////////////////

			//����Ψһģ�飬ɾ����
			SAFE_DELETE(oldTree);
			mvmu_TreeMap.erase(cur_m_id);
	}

	return 0; //��������
}

int logic_Program::backInsMultiMoveIf(int cur_m_id,int pre_m_id,int if_id,int branch_id) {

	//////pre_m_id������if��
	assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[pre_m_id] ) );

	//////cur_m_id �� pre_m_id ������һ��if��
	logic_Tree* cur_m_tree = mvmu_ModuleId_TreeMap[cur_m_id];
	logic_Tree* pre_m_tree = mvmu_ModuleId_TreeMap[pre_m_id];
	assert( mvmi_TreeId_For_IfIdMap[cur_m_tree] == mvmi_TreeId_For_IfIdMap[pre_m_tree] );

	/// �ظ� backInsMultiMove ����
	/// �ظ� addLeafMove ����
	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id))
		*(mvmu_ModuleMap.count(if_id)) ) {
			return -2; // ���� cur_m_id �� pre_m_id for_id ��Ҫ��
	}

	logic_IfModule * tmpIfModule = this->getIfModuleById(if_id); //�ж�branch��֧�Ƿ����
	assert( tmpIfModule->isBranchExist(branch_id) == true );

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
		assert( mvmi_TreeId_For_IfIdMap.count(oldTree) >0 ); //��Ȼ��ͬһ��for��

		tmpIfModule->delTree(oldTree);
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

int logic_Program::frontInsMultiMoveIf(int cur_m_id,int post_m_id,int if_id,int branch_id) {

	//////post_m_id������if��
	assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[post_m_id] ) );

	//////cur_m_id �� post_m_id ������һ��if��
	logic_Tree* cur_m_tree = mvmu_ModuleId_TreeMap[cur_m_id];
	logic_Tree* pre_m_tree = mvmu_ModuleId_TreeMap[post_m_id];
	assert( mvmi_TreeId_For_IfIdMap[cur_m_tree] == mvmi_TreeId_For_IfIdMap[pre_m_tree] );

	/// �ظ� frontInsMultiMove ����
	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(post_m_id))
		*(mvmu_ModuleMap.count(if_id)) ) {
			return -2; //û�ҵ������
	}

	logic_IfModule * tmpIfModule = this->getIfModuleById(if_id); //�ж�branch��֧�Ƿ����
	assert( tmpIfModule->isBranchExist(branch_id) == true );

	//��� post_m_id ģ���ǿ�ʼ
	if ( mvmu_ModuleMap[post_m_id]->getModuleType() == 2001 ) {
		return -3; //ģ�����ʹ���
	}

	//ע�������½�module��ֻ�ô������ڵ㼴��

	/// �ظ� frontInsMultiMove ����
	if( 0 == post_m_id ) {

		//�ղ�
		//�൱�� backInsMultiMove ������

		logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id];

		///// step1��ɾ�������ڵ㣬ͬʱ���Ͽ�������������
		logic_TreeNode * curNode = oldTree->node_search(cur_m_id);
		if( curNode->mvvu_Children.size() == 1 ) {

			logic_TreeNode * breakNode = curNode->mvvu_Children[0];
			oldTree->del_node_notConn(breakNode->getID());
			logic_Tree * newTree = new logic_Tree(breakNode);

			mvmu_TreeMap[newTree->getRoot()->getID()] = newTree;

			/////////////��if�м�����///////////
			mvmi_TreeId_For_IfIdMap[newTree] = if_id;
			tmpIfModule->addTree(branch_id,newTree);

			///// ���� module treeӳ�� insNode��֧
			recurs_update(newTree,newTree->getRoot());
		}else if( curNode->mvvu_Children.size() > 1 ) {
			assert(false);
		}

	} else {

		logic_Tree *insTree = mvmu_ModuleId_TreeMap[post_m_id]; //�²�����
		logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id];

		//��� post_m_id ���Ǹ��ڵ㣬���󷵻�
		if( post_m_id!=insTree->mvi_TreeID ) {
			return -4;
		}

		///// step1��ɾ�������ڵ㣬ͬʱ���Ͽ�������������
		logic_TreeNode * curNode = oldTree->node_search(cur_m_id);
		if( curNode->mvvu_Children.size() == 1 ) {

			logic_TreeNode * breakNode = curNode->mvvu_Children[0];
			oldTree->del_node_notConn(breakNode->getID());
			logic_Tree * newTree = new logic_Tree(breakNode);

			mvmu_TreeMap[newTree->getRoot()->getID()] = newTree;

			/////////////��for�м�����///////////
			mvmi_TreeId_For_IfIdMap[newTree] = if_id;
			tmpIfModule->addTree(branch_id,newTree);

			///// ���� module treeӳ�� insNode��֧
			recurs_update(newTree,newTree->getRoot());
		}else if( curNode->mvvu_Children.size() > 1 ) {
			assert(false);
		}

		///// step2�����������ڵ�

		logic_TreeNode * insNode = insTree->getRoot(); //������ڵ�
		oldTree->add_node(cur_m_id,insNode); //insTree�ӵ�oldTree��

		//��Ȼ��ROOT��ֱ��ɾ��ԭinsTree
		insTree->del_node_notConn(post_m_id); //��root��ֱ���ÿ�
		SAFE_DELETE(insTree); //����ɾ����
		mvmu_TreeMap.erase(post_m_id);

		///////////////////////////////���⴦��if��for�ĵط�///////////////////////////////

		///
		/// \brief ��if��ɾ����
		///
		assert( mvmi_TreeId_For_IfIdMap.count(insTree) >0 ); //��Ȼ��ͬһ��for��

		tmpIfModule->delTree(insTree);
		mvmi_TreeId_For_IfIdMap.erase(insTree);

		///////////////////////////////////////////////////////////////////////////////////

		///// ���� module treeӳ�� insNode��֧
		recurs_update(oldTree,insNode);

	}

	return 0; //��������
}

int logic_Program::addLeafMoveIf(int cur_m_id,int pre_m_id,int if_id,int branch_id) {

	//////pre_m_id������if��
	assert( mvmi_TreeId_For_IfIdMap.count( mvmu_ModuleId_TreeMap[pre_m_id] ) );

	//////cur_m_id �� pre_m_id ������һ��if��
	logic_Tree* cur_m_tree = mvmu_ModuleId_TreeMap[cur_m_id];
	logic_Tree* pre_m_tree = mvmu_ModuleId_TreeMap[pre_m_id];
	assert( mvmi_TreeId_For_IfIdMap[cur_m_tree] == mvmi_TreeId_For_IfIdMap[pre_m_tree] );

	/// �ظ� addLeafMove ����
	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(pre_m_id))
		*(mvmu_ModuleMap.count(if_id)) ) {
			return -2; // ���� cur_m_id �� pre_m_id if_id ��Ҫ��
	}

	logic_IfModule * tmpIfModule = this->getIfModuleById(if_id); //�ж�branch��֧�Ƿ����
	assert( tmpIfModule->isBranchExist(branch_id) == true );

	//��� cur_id ģ���ǿ�ʼ
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
		return -3; //ģ�����ʹ���
	}

	if ( addLeafCheckPre(cur_m_id,pre_m_id) < 0 ) {
		return -4;
	}

	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //��ɾ����
	//�ýڵ�����Ǹ����ĸ��ڵ�
	if( oldTree->mvi_TreeID != cur_m_id )
		assert(false);

	logic_Tree *insTree = mvmu_ModuleId_TreeMap[pre_m_id];
	logic_TreeNode * insNode = insTree->node_search(pre_m_id); //������ڵ�
	logic_TreeNode * curNode = oldTree->getRoot(); //��ǰ�ڵ�

	curNode->mvu_Parent = insNode;

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

	tmpIfModule->delTree(oldTree);
	mvmi_TreeId_For_IfIdMap.erase(oldTree);

	///////////////////////////////////////////////////////////////////////////////////

	/// Step3������ģ����map��Ϣ
	recurs_update(insTree,curNode);

	return 0;
}

//ֻ�ڽӵ�activeTree���ڵ��ʱ�����

//��ģ�����activeTree
int logic_Program::appendActiveTreeMoveIf(int cur_m_id,int if_id,int branch_id) {

	//��ĳһģ��ӵ� branch activeTree����

	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(if_id)) ) {
		assert(false);
		return -2; // ���� cur_m_id �� if_id ��Ҫ��
	}

	logic_IfModule * tmpIfModule = this->getIfModuleById(if_id); //�ж�branch��֧�Ƿ����
	assert( tmpIfModule->isBranchExist(branch_id) == true );

	//��� cur_id ģ���ǿ�ʼ
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
		assert(false);
		return -3; //ģ�����ʹ���
	}

	//�õ� activeTree
	logic_Tree * curActiveTree = tmpIfModule->getCurActiveTree(branch_id);
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
				tmpIfModule->delTree(oldTree);
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
int logic_Program::addLeafActiveTreeMoveIf(int cur_m_id,int if_id,int branch_id) {

	//////cur_m_id �� activeTree ������ͬһ��if��
	logic_Tree* cur_m_tree = mvmu_ModuleId_TreeMap[cur_m_id];
	assert( mvmi_TreeId_For_IfIdMap[cur_m_tree] == if_id );

	/// �ظ� addLeafMove ����
	if ( 0 >= (mvmu_ModuleMap.count(cur_m_id))*(mvmu_ModuleMap.count(if_id)) ) {
		return -2; // ���� cur_m_id �� for_id ��Ҫ��
	}

	logic_IfModule * tmpIfModule = this->getIfModuleById(if_id); //�ж�branch��֧�Ƿ����
	assert( tmpIfModule->isBranchExist(branch_id) == true );

	//��� cur_id ģ���ǿ�ʼ
	if ( mvmu_ModuleMap[cur_m_id]->getModuleType() == 2001 ) {
		return -3; //ģ�����ʹ���
	}

	logic_Tree *oldTree = mvmu_ModuleId_TreeMap[cur_m_id]; //��ɾ����
	//�ýڵ�����Ǹ����ĸ��ڵ�
	if( oldTree->mvi_TreeID != cur_m_id )
		assert(false);

	logic_Tree *insTree = tmpIfModule->getCurActiveTree(branch_id);
	logic_TreeNode * insNode = insTree->getRoot(); //������ڵ�
	logic_TreeNode * curNode = oldTree->getRoot(); //��ǰ�ڵ�

	curNode->mvu_Parent = insNode;

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

	tmpIfModule->delTree(oldTree);
	mvmi_TreeId_For_IfIdMap.erase(oldTree);

	///////////////////////////////////////////////////////////////////////////////////

	/// Step3������ģ����map��Ϣ
	recurs_update(insTree,curNode);

	return 0;
}

//��ģ���²���activeTree
int logic_Program::appendActiveTreeInsertIf(int m_id,int m_type,int if_id,int branch_id) {

	assert( mvmu_ModuleMap.count(if_id)>0 );

	logic_IfModule * tmpIfModule = this->getIfModuleById(if_id); //�ж�branch��֧�Ƿ����
	assert( tmpIfModule->isBranchExist(branch_id) == true );

	// step1����ɭ���м������id

	if ( m_type == 2001 ) {
		return false;
	}

	logic_Tree *tree = tmpIfModule->getCurActiveTree(branch_id);
	tree->append_node(-1,m_id);


	// step2�������������moduleʵ��
	this->add_Module(m_id,m_type);

	return 0;
}

//��prj��ʼ��prog
//��ʼ�� ��������map��v_map������
void logic_Program::setInitVarMap(std::map<int  ,logic_VarModule*> &v_map) {

	this->prjVariety = &v_map; //��ʼ��prj ���� map
}


std::map<int, logic_VarModule*>* logic_Program::getVarMap()
{
	return prjVariety;
}


//��ʼ�� initModule��init_m_map�Ǹ���
void logic_Program::setInitModuleMap(std::map <int, logic_BasicModule *> init_m_map) {

	this->initModuleMap = init_m_map; //��ʼ�� ����init module����
}

std::map <int, logic_BasicModule *> logic_Program::getInit_m_map()
{
	return initModuleMap;
}

///
/// \brief ��ȡ���ڵ�
/// \para ������ţ������0����ȡ�����root����
/// \return ���ڵ㼯��
///

//��ȡprogram�󻭲�rootsId
std::vector<int > logic_Program::findRootsInContainer() {

	vector<int > L;
	map<int , logic_Tree * > map = mvmu_TreeMap;

	//�޳����в��õ�root
	for( std::map<logic_Tree * ,int >::iterator it = mvmi_TreeId_For_IfIdMap.begin();it != mvmi_TreeId_For_IfIdMap.end() ; ++it) {

		map.erase(it->first->mvi_TreeID);
	}

	for( std::map<int ,logic_Tree * >::iterator it = map.begin();it != map.end() ; ++it) {

		if( it->first >= ACTIVE_TREE_MAP_FACTOR )
			continue;

		L.push_back(it->first);
	}

	return L;
}

//���أ���ȡָ�� for �� rootsId
std::vector<int > logic_Program::findRootsInContainer(int for_id) {

	assert( mvmu_ModuleMap.count(for_id)>0 );
	logic_ForModule * tmpForModule = this->getForModuleById(for_id);

	return tmpForModule->findAllRoots();
}

//���أ���ȡָ�� if �� rootsId
std::vector<int > logic_Program::findRootsInContainer(int if_id,int branch_id) {

	assert( mvmu_ModuleMap.count(if_id)>0 );
	logic_IfModule * tmpIfModule = this->getIfModuleById(if_id);

	return tmpIfModule->findBranchAllRoots(branch_id);
}

//����ʱ��⣺ֻ��һ����������⣬�������Լ�������
//����ʵ�ж�������ģ�������һ�����������⣩
//para�� cur_id�����߳���ģ�飬another_id�Ǳ�����ģ��
//
int logic_Program::addLeafCheckPre(int cur_id,int another_id) {

	if ( mvmu_ModuleId_TreeMap[cur_id]->mvi_TreeID 
		== mvmu_ModuleId_TreeMap[another_id]->mvi_TreeID ) {

		return -1;
	}

	return 0;
}

void logic_Program::setModuleMap(std::map <int ,logic_BasicModule* > moduleMap)
{
	mvmu_ModuleMap = moduleMap;
}

void logic_Program::setTreeMap(std::map<int,logic_Tree*> treeMap)
{
	mvmu_TreeMap = treeMap;
}


//!!!!!!!!!!!!!!!!!!!!����!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
whPort logic_Program::getLinkstartwhport(whPort in)
{
	assert(mvvu_Conn_To_FromMap.find(in) != mvvu_Conn_To_FromMap.end());
	return mvvu_Conn_To_FromMap[in];
	
}

std::map<logic_Tree* ,int> logic_Program::getIfforidmaptree()
{
	return mvmi_TreeId_For_IfIdMap;
}
//!!!!!!!!!!!!!!!!!!!!����!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//

///
/// \brief �����ҵ�ģ��
///

//session1���Ƿ���Դ����ҵ�ģ�飬ǰ��˵�һ�λỰ
//�ӿڴ�id�б������Ƿ�ɴ���

///1���ж�����ģ����붼��ͨ���������ֱͨ��pass��
///������Ϣ����ȷ������ģ�鶼�����ӣ����ҹ���ͬһ����ʼģ��
///2��DFS����������еķ�֧û�и��ǵ��������
///������Ϣ������ѡ�������а������в���ģ�顣

///
/// \return -1 ���������ʼģ��
///         -2 ��ʾ����һ����
///         -3 ��ʾ��֤����֧����
///          0 ��ʾ������������
///         -4 ��ʾĳ�ڵ㲢�����к��Ӷ���ѡ��
///         -5 ��ʾ�ж����ͨ��
///
int logic_Program::canMyBlocks(std::vector<int > ids) {

	assert( mvmu_ModuleMap.count(ids[0])>0 ); //������ģ��

	int vsize = ids.size();
	logic_Tree * tree = mvmu_ModuleId_TreeMap[ids[0]];
	std::map <int , int > idsMap;

	//���flagMap
	for (int i=0;i<vsize;i++) {

		assert( mvmu_ModuleMap.count(ids[i])>0 ); //������ģ��

		if ( mvmu_ModuleMap[ids[0]]->getModuleType() )
			return -1;

		if ( mvmu_ModuleId_TreeMap[ids[0]]->mvi_TreeID != tree->mvi_TreeID )
			return -2;

		idsMap[ids[i]] = 1; //�����ֵ
	}

	//����BFSɨ����һ���ڵ㣬�˽ڵ�һ���ǲ�����͵Ľڵ㣨֮һ��
	std::queue<logic_TreeNode *> q;
	q.push(tree->getRoot());
	logic_TreeNode * n = NULL;
	MyBlockS1_bfsFindStartNode(q,idsMap,n);

	if( NULL == n )
		assert(false);

	//������֧���
	///
	/// \return 0 ��ʾ������ϣ�>0 ��ʾ��ֹһ����֧��<0 ����
	///
	int res = MyBlockS1_SingleBranchProc(n,idsMap);
	if( res < 0 )
		return -3;
	else if( 0 == res )
		return 0;

	//��tree����DFS
	res = 0;
	MyBlockS1_DFSJudge(n,res,idsMap);
	if( res < 0 )
		return -4;

	//��ʱ��ͨ���ѱ�����
	if( idsMap.empty() == false )
		return -5;

	return 0; //���Դ���
}

///
/// \brief ������������ж��Ƿ���Խ����ҵ�ģ�飬��֧������Ȼ����1
/// \para res ��ʾ��� ������ʾ���ɽ�����idsMap ��ʶ�Ƿ���id����findʱ��������O(1)��
///
void logic_Program::MyBlockS1_DFSJudge( logic_TreeNode *some, int res, std::map <int , int > &idsMap ) {

	//�жϱ�׼����start��,branchCnt>1ʱ����֤��ǰ�ڵ��������нڵ㶼������

	if( res < 0 )
		return;

	int curId = some->getID();
	if( idsMap.count(curId) > 0 ) {
		idsMap.erase(curId);
	}

	//��Ѱ�Լ������к����Ƿ���IDSMap��
	//�ѽ��м�֦
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++) {

		if( idsMap.count(some->mvvu_Children[i]->getID()) == 0 )
			res = -1;
		else
			MyBlockS1_DFSJudge(some->mvvu_Children[i],res,idsMap);
	}

	//���Լ����ֵ��Ƿ���ڣ�������ڿ��Լ���
	logic_TreeNode *pa = some->mvu_Parent;
	for (int i=0;i<pa->mvvu_Children.size();i++) {
		if( idsMap.count(pa->mvvu_Children[i]->getID()) == 0 )
			MyBlockS1_DFSJudge(some->mvvu_Children[i],res,idsMap);
	}

}

//��bfs�ҳ��ж���ʼ�ڵ�
void logic_Program::MyBlockS1_bfsFindStartNode(std::queue<logic_TreeNode *> &q,std::map <int , int > idsMap, logic_TreeNode * &findNode) {

	if( findNode != NULL ) //�ҵ���
		return;

	if ( q.empty() == true )
		return;

	logic_TreeNode *node = q.front();
	q.pop();
	if( idsMap.count(node->getID()) > 0 ) {
		findNode = node;
		return;
	}

	//���������Ů
	for(int i=0;i<node->mvvu_Children.size();++i)
		q.push(node->mvvu_Children[i]);

	MyBlockS1_bfsFindStartNode(q,idsMap,findNode);
}

///
/// \brief ������֧���
/// \return 0 ��ʾ������ϣ�>0 ��ʾ��ֹһ����֧��<0 ����
///
int logic_Program::MyBlockS1_SingleBranchProc(logic_TreeNode * curNode, std::map <int , int > idsMap) {

	//ֱ����Ϊ����֧�������
	while ( idsMap.empty() == false ) {

		if( idsMap.count(curNode->getID()) > 0 ) {
			idsMap.erase(curNode->getID());
		} else {
			//���յ���IDSMap��û������ڵ㣬֤�����ǵ���֧���������֧û��������������
			return -1;
		}

		if ( curNode->mvvu_Children.size() == 0 && idsMap.empty() == false ) {
			//�ѵ�Ҷ�ӽڵ㣬���Ǵ˴�idsMap��û�п�
			return 1; //����һ����֧
		}

		curNode = curNode->mvvu_Children[0];

	}
	
	return 0;
}
