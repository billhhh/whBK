/* 
* 
* function: �߼������ڵ�
* 
* Date:2015-09-03
* 
*    Author: Bill Wang
*/

#include <assert.h>
#include <climits>
#include "logic_TreeNode.h"

logic_TreeNode::logic_TreeNode()
	:mvi_NodeID(-1),mvu_Parent(NULL)
{

}

//������½�����ʱ
logic_TreeNode::logic_TreeNode(const _IdDataType data)
	:mvu_Parent(0)
{
	assert(data<INT_MAX);
	assert(data>INT_MIN);

	mvi_NodeID = data;
}

logic_TreeNode::logic_TreeNode(logic_TreeNode *p,const _IdDataType data)
	:mvu_Parent(p)
{
	assert(data<INT_MAX);
	assert(data>INT_MIN);

	mvi_NodeID = data;
}

logic_TreeNode::~logic_TreeNode()
{

}

int logic_TreeNode::getID() {
	return mvi_NodeID;
}

int logic_TreeNode::getParentID() {

	if( NULL == this->mvu_Parent )
		return 0;

	return this->mvu_Parent->getID();
}
