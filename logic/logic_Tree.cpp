/* 
* 
* function: 逻辑层树组织结构
* 
* Date:2015-09-03
* 
*    Author: Bill Wang
*/

#include <iostream>
#include <assert.h>
#include <climits>
#include "logic_Tree.h"

using namespace std;
typedef logic_TreeNode tree_node;

//logic_Tree 构造、析构方法
logic_Tree::logic_Tree() //默认构建一棵root ID为0的节点
	:mvu_root(new logic_TreeNode(1))
{
	Init();
}

logic_Tree::logic_Tree(_IdDataType rootId)
{
	assert(rootId<INT_MAX);
	assert(rootId>INT_MIN);

	tree_node* node = new tree_node(rootId); //建立root节点
	this->mvu_root = node;
	Init();
}

logic_Tree::logic_Tree(tree_node *node)
	:mvu_root(node)
{
	assert(node);
	assert(node->mvi_NodeID<INT_MAX);
	assert(node->mvi_NodeID>INT_MIN);

	Init();
}

logic_Tree::~logic_Tree()
{
	cout<<"进入logic_Tree析构函数"<<endl;

	if( NULL != mvu_root )
		Destroy(mvu_root);
}

void logic_Tree::Init()
{
	this->mvi_TreeID = this->mvu_root->mvi_NodeID; //树ID用root ID标识
}

void logic_Tree::Destroy(tree_node *some)
{
	//后序删除
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++)
		Destroy(some->mvvu_Children[i]);
	SAFE_DELETE(some);
}

//迭代器
logic_Tree::iterator::iterator()
	:_node(0) //NULL
{

}

logic_Tree::iterator::iterator(tree_node *node)
	:_node(node)
{

}

logic_Tree::iterator::~iterator()
{

}

tree_node* logic_Tree::iterator::get_cur_node()
{
	return _node;
}//迭代器 END

tree_node* logic_Tree::getRoot()
{
	return this->mvu_root;
}

//有安全隐患，不建议使用
void logic_Tree::setRoot(tree_node *some) {
	this->mvu_root = some;
	this->mvi_TreeID = some->getID();
}

//将root的唯一孩子设置为root
bool logic_Tree::setFirstChildAsRoot() {

	logic_TreeNode * oldRoot = this->mvu_root;

	if( oldRoot->mvvu_Children.size() == 0 )
		return false;

	this->mvu_root = oldRoot->mvvu_Children.at(0);
	oldRoot->mvvu_Children.at(0)->mvu_Parent = NULL;
	this->mvi_TreeID = oldRoot->mvvu_Children.at(0)->getID();

	SAFE_DELETE(oldRoot);
	return true;
}

//增、删、查功能外部接口

bool logic_Tree::exchangeRoot(int ID) {

	iterator *temPos = search(ID);
	if ( NULL != temPos ) //如果已经存在，错误
	{
		SAFE_DELETE(temPos);
		return false;
	}

	tree_node *tmp = new tree_node(ID);
	tmp->mvvu_Children.push_back(this->mvu_root);
	this->mvu_root->mvu_Parent = tmp;
	this->mvu_root = tmp;
	this->mvi_TreeID = ID;

	return true;
}

bool logic_Tree::add_node(_IdDataType parent_ID,_IdDataType ID)
{
	iterator *temPos = search(ID);
	if ( NULL != temPos ) //如果已经存在，错误
	{
		SAFE_DELETE(temPos);
		return false;
	}

	tree_node *tmp = new tree_node(ID);
	iterator* position = search(parent_ID);

	if ( NULL == position) //父节点不存在，错误
	{
		SAFE_DELETE(position);
		return false;
	}

	position->_node->mvvu_Children.push_back(tmp);
	tmp->mvu_Parent = position->_node;
	SAFE_DELETE(position); //delete position

	return true;
}

//重载方法，支持直接贴上一个node
bool logic_Tree::add_node(_IdDataType parent_ID,logic_TreeNode *node)
{
	iterator *temPos = search(node->getID());
	if ( NULL != temPos ) //如果已经存在，错误
	{
		SAFE_DELETE(temPos);
		return false;
	}

	tree_node *tmp = node;
	iterator* position = search(parent_ID);

	if ( NULL == position) //父节点不存在，错误
	{
		SAFE_DELETE(position);
		return false;
	}

	position->_node->mvvu_Children.push_back(tmp);
	tmp->mvu_Parent = position->_node;
	SAFE_DELETE(position); //delete position

	return true;
}

//直接在新节点后面追加
bool logic_Tree::append_node(_IdDataType parent_ID,_IdDataType ID)
{
	iterator *temPos = search(ID);
	if ( NULL != temPos ) //如果已经存在，错误
	{
		SAFE_DELETE(temPos);
		return false;
	}

	tree_node *tmp = new tree_node(ID);
	iterator* position = search(parent_ID);

	if ( NULL == position) //父节点不存在，错误
	{
		SAFE_DELETE(position);
		return false;
	}

	//将父节点的所有儿子给tmp节点
	tree_node *parentNode = position->_node;
	for (int i=0;i<parentNode->mvvu_Children.size();++i)
	{
		tree_node * tmpChild = parentNode->mvvu_Children.at(i);
		tmpChild->mvu_Parent = tmp;
		tmp->mvvu_Children.push_back(tmpChild);
		parentNode->mvvu_Children.erase(parentNode->mvvu_Children.begin()+i);
		--i;
	}

	position->_node->mvvu_Children.push_back(tmp);
	tmp->mvu_Parent = position->_node;
	SAFE_DELETE(position); //delete position

	return true;
}

bool logic_Tree::insert_node(_IdDataType parent_ID,_IdDataType suc_ID,_IdDataType ID)
{
	iterator* positionA = search(parent_ID);
	iterator* positionB = search(suc_ID);

	if ( NULL == positionA || NULL == positionB)
	{
		//发现内存问题报错
		SAFE_DELETE(positionA);
		SAFE_DELETE(positionB);
		return false;
	}

	//如果suc_ID节点不是parent_ID节点直接孩子，错误
	int index = isChild(positionA,positionB);
	if (index == -1)
	{
		SAFE_DELETE(positionA);
		SAFE_DELETE(positionB);
		return false;
	}

	tree_node *tmp = new tree_node(ID);
	positionA->_node->mvvu_Children.erase(positionA->_node->mvvu_Children.begin()+index); //删除parent_ID节点中的suc_ID节点孩子
	positionA->_node->mvvu_Children.push_back(tmp);
	tmp->mvvu_Children.push_back(positionB->_node);
	tmp->mvu_Parent = positionA->_node;
	positionB->_node->mvu_Parent = tmp;

	SAFE_DELETE(positionA);
	SAFE_DELETE(positionB);

	return true;
}

int logic_Tree::isChild(iterator* p, iterator* c) const
{
	int Search_ID = c->_node->mvi_NodeID;
	for (int i=0;i<p->_node->mvvu_Children.size();++i)
	{
		if (Search_ID == p->_node->mvvu_Children[i]->mvi_NodeID)
		{
			return i;
		}
	}

	return -1;
}

bool logic_Tree::del_node(_IdDataType ID)
{
	iterator* position = search(ID);
	if (NULL == position)
	{
		SAFE_DELETE(position);
		return false;
	}

	tree_node *cur_node = position->_node;

	if(cur_node->mvvu_Children.size()>1) { //多个孩子在tree级别不做处理

		SAFE_DELETE(position);
		return false;
	}

	if( this->mvi_TreeID == ID ) {

		//如果待删除节点是Root，且只有一个孩子
		//直接将后一个节点置为根

		this->mvu_root = cur_node->mvvu_Children.at(0);
		this->mvi_TreeID = cur_node->mvvu_Children.at(0)->getID();
		cur_node->mvvu_Children.at(0)->mvu_Parent = NULL;

		SAFE_DELETE(cur_node);
		SAFE_DELETE(position);

		return true;
	}

	//将待删除节点的唯一儿子传给父亲，如果是叶子不用
	if( cur_node->mvvu_Children.size()>0 ) {
		cur_node->mvu_Parent->mvvu_Children.push_back(cur_node->mvvu_Children[0]);
		cur_node->mvvu_Children[0]->mvu_Parent = cur_node->mvu_Parent;
	}

	//将其父亲的此儿子删除
	for (int i=0;i<cur_node->mvu_Parent->mvvu_Children.size();++i)
	{
		if(cur_node->mvu_Parent->mvvu_Children[i]->mvi_NodeID == ID) {
			cur_node->mvu_Parent->mvvu_Children.erase(cur_node->mvu_Parent->mvvu_Children.begin()+i);
			break;
		}
	}

	SAFE_DELETE(cur_node);
	SAFE_DELETE(position);

	return true;
}

//端开ID节点连接，但不删除
bool logic_Tree::del_node_notConn(int ID) {

	iterator* position = search(ID);
	if (NULL == position) {
		SAFE_DELETE(position);
		return false;
	}

	if( this->mvi_TreeID == ID ) {
		//如果是树根，直接将root置空即可

		this->mvu_root = NULL; //这样在外部就可以轻松删除tree
		this->mvi_TreeID = -1;
		SAFE_DELETE(position);
		return true;
	}

	tree_node *cur_node = position->_node;

	//将其父亲的此儿子删除
	for (int i=0;i<cur_node->mvu_Parent->mvvu_Children.size();++i)
	{
		if(cur_node->mvu_Parent->mvvu_Children[i]->mvi_NodeID == ID) {
			cur_node->mvu_Parent->mvvu_Children.erase(cur_node->mvu_Parent->mvvu_Children.begin()+i);
			break;
		}
	}

	//SAFE_DELETE(cur_node);  //并不适合在此处删除，要删除应该在调用处删除，否则应该保留节点内存
	SAFE_DELETE(position);

	return true;
}

logic_Tree::iterator* logic_Tree::search(_IdDataType ID)
{
	//tree_node* some = mvu_root;
	tree_node* res = recurs_render(mvu_root,ID);

	if (res == NULL)
		return NULL;

	//会在调用search方法的地方释放
	iterator* tmp = new iterator(res);
	return tmp;
}

logic_TreeNode* logic_Tree::node_search(int id) {

	iterator *tmpPos = search(id);
	if( NULL == tmpPos ) {
		return NULL;
	}

	logic_TreeNode * tmpNode = tmpPos->_node;

	SAFE_DELETE(tmpPos);
	return tmpNode;
}

tree_node* logic_Tree::recurs_render(tree_node* some,const _IdDataType ID)
{
	if (ID == some->mvi_NodeID)
		return some;

	for (unsigned i = 0; i < some->mvvu_Children.size(); i++)
	{
		tree_node* r = recurs_render(some->mvvu_Children[i],ID);

		if(NULL != r)
			return r;
	}

	return NULL;
}

void logic_Tree::recurs_print(tree_node* some,int floor) const
{
	std::cout << "floor " << floor << ": ";
	++floor;
	std::cout << some->mvi_NodeID << std::endl;
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++)
		recurs_print(some->mvvu_Children[i],floor);
	--floor;
}

bool logic_Tree::kill_subtree(tree_node *some)
{
	if (mvi_TreeID == some->mvi_NodeID)
		return false;

	if ( NULL == some)
		return false;

	iterator* position = search(some->mvi_NodeID);
	if (NULL == position)
	{
		SAFE_DELETE(position);
		return false;
	}

	Destroy(some);

	return true;
}

//获得一个节点的前驱节点id
int logic_Tree::getPreId(int id) {

	iterator *pos = search(id);
	if ( NULL == pos ) { //如果不存在，报错
		return false;
	}

	if(id == this->mvi_TreeID)
		return 0;

	int resId = pos->_node->mvu_Parent->mvi_NodeID;
	SAFE_DELETE(pos);

	return resId;

}

//判断 nodeB_id 是否是 nodeA_id 的祖先
bool logic_Tree::isAncestor(int nodeA_id,int nodeB_id) {

	if( nodeA_id == nodeB_id )
		return false;

	iterator *posA = search(nodeA_id);
	iterator *posB = search(nodeB_id);
	if ( NULL == posA || NULL == posB ) { //如果不存在，报错
		return false;
	}

	logic_TreeNode * curNode = posA->_node;
	while ( NULL != curNode->mvu_Parent ) {

		if( curNode->getParentID() == nodeB_id ) { //发现 nodeB_id 是 nodeA_id 的祖先

			SAFE_DELETE(posA);
			SAFE_DELETE(posB);

			return true;
		}

		curNode = curNode->mvu_Parent;
	}

	SAFE_DELETE(posA);
	SAFE_DELETE(posB);

	return false;
}
