#include <iostream>
#include <string>
#include <stdlib.h>
#include "logic_Global.h"
#include "logic_Test.h"
#include "logic_Tree.h"
#include "logic_TreeNode.h"
#include "logic_Program.h"
#include "../logger.h"
// #include "../mutex.h"
// #include "../mymutex.h"

using namespace std;

void logic_Test::MainTest()
{
	//cout<<"进入test主线程"<<endl;

	//testTree();
	//testProgram();
	//testProject();
	testLogger();
	//testMutex();
}

void logic_Test::testTree()
{
	typedef logic_TreeNode node_type;
	typedef logic_Tree tree_type;

	/////树最好建立在堆上，虽然树根建立在栈上不会报错，是因为安全删除的问题
	tree_type *tree1 = new tree_type(5);
	//tree_type tree1(5);

 	tree1->add_node(5,7);
 	tree1->add_node(5,8);
 	tree1->add_node(5,10);
 	tree1->insert_node(5,10,6);
 	tree1->add_node(6,11);
 	tree1->recurs_print(tree1->getRoot());

 	cout<<"\n删除后："<<endl;
 	tree1->del_node(5);
	tree1->recurs_print(tree1->getRoot());
		delete tree1;

	//tree_type *pObj = new tree_type(-2147483649);
// 	pObj->add_node(-3, 3);
// 	pObj->add_node(-3, 5);

// 	logic_TreeNode *node = NULL;
// 	tree_type *pObj = new logic_Tree(node);
// 	pObj->recurs_print(pObj->getRoot());
	//pObj->recurs_print(pObj->getRoot(),1);
	//delete pObj;
}

void logic_Test::testProgram()
{
// 	cout<<"进入 ProgramTest"<<endl;
// 	logic_Program p1("car2");
// 
// 	typedef logic_Tree tree_type;
// 	tree_type *tree1 = new tree_type(5);
// 
// 	tree1->add_node(5,7);
// 	tree1->add_node(5,8);
// 	tree1->add_node(5,10);
// 	tree1->insert_node(5,10,6);
// 	tree1->add_node(6,11);
// 
// 	p1.add_Tree(tree1);
// 	tree_type * t = p1.search_Tree(5);
// 	t->recurs_print(t->getRoot());
// 
// 	cout<<"search_Tree_ID == "<<p1.search_Tree(t)<<endl;
// 
// 	p1.del_Tree(5);

	//delete tree1;

	return;
}

void logic_Test::testProject()
{
	//完全新建Project测试

}

void logic_Test::testLogger()
{
	initLogger("hahaha","warnlog.txt","errolog.txt");
	//LOG(_INFO);
	//LOG(_WARNING);
	//LOG(_FATAL);
	//LOG(_ERROR);
	LOG2(_INFO,"国庆快乐");
	//LOG2(_WARNING,"just for fun");

	//CHECK(0);
}

void logic_Test::testMutex()
{
	initLogger("infolog.txt","warnlog.txt","errolog.txt");
	//Mutex loggerLock;
	//MyMutex loggerLock;

	LOG(_INFO);
	LOG2(_WARNING,"just for fun");
	LOG2(_ERROR,"warning reason 2015.9.23");

}
