/* 
* 
* function: 逻辑层树组织结构
* 
* Date:2015-09-03
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_TREE_H_
#define _LOGIC_TREE_H_

#include "logic_TreeNode.h"
#include "logic_Global.h"

class logic_Tree
{

	//friend class logic_XmlIO;

protected:
	typedef logic_TreeNode tree_node;
public:
	_IdDataType mvi_TreeID; //TreeID即rootID

	explicit logic_Tree();
	explicit logic_Tree(_IdDataType rootId);
	explicit logic_Tree(tree_node *node);
	~logic_Tree();

	//迭代器嵌套类
	class iterator{
	public:
		//构造与析构
		iterator();
		explicit iterator(tree_node *node);
		~iterator();

		tree_node *_node;

		tree_node* get_cur_node(); //获取当前节点
		// 		iterator begin() const; //开始位置
		// 		iterator end() const; //结束位置

	protected:

	private:
		//tree_node* _find_end(tree_node* current) const;
	};

public:
	tree_node * getRoot();
	void setRoot(tree_node *some);
	bool setFirstChildAsRoot(); //将root的唯一孩子设置为root

	//增、删、查功能外部接口
	bool exchangeRoot(int id); //将root换成新的id节点，相当于在root前前插
	bool add_node(_IdDataType parent_ID,_IdDataType ID); //直接在parent后添上一个叶子节点
	bool add_node(_IdDataType parent_ID,logic_TreeNode *node); //重载方法，支持直接贴上一个node
	bool append_node(_IdDataType parent_ID,_IdDataType ID);//直接追加节点，父节点孩子直接赋值给追加节点
	bool insert_node(_IdDataType parent_ID,_IdDataType suc_ID,_IdDataType ID); //插在两个节点中间
	bool del_node(_IdDataType ID);
	bool del_node_notConn(int id); //删除一个节点，并把其孩子从树中断掉
	iterator* search(_IdDataType ID); //遍历搜索
	tree_node* node_search(int id); //返回node指针
	void recurs_print(tree_node* some,int floor=0) const; //DFS打印测试
	bool kill_subtree(tree_node *some); //将非根节点的某个节点极其子树销毁

	int getPreId(int id); //获得一个节点的前驱节点id

	//判断 nodeB_id 是否是 nodeA_id 的祖先
	bool isAncestor(int nodeA_id,int nodeB_id);

	//重载小于号操作符，方便 map 作为 key 排序
	bool operator < (const logic_Tree &t) const
	{
		if( mvi_TreeID < t.mvi_TreeID ) { //小于直接返回true
			return true;
		}else if( mvi_TreeID > t.mvi_TreeID ) { //大于返回false
			return false;
		}else {

			//不可能一样
			assert(false);
		}
	}

protected:

private:
	tree_node *mvu_root;

	void Init();
	void Destroy(tree_node *some); /////销毁some节点及其所有后代，销毁整棵树
	int isChild(iterator* p, iterator* c) const; //判断c是不是p的直接孩子，如果找到返回i，没找到-1
	tree_node* recurs_render(tree_node* some,const _IdDataType ID); //递归DFS

};

#endif
