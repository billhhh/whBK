#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<cstring>
#include<Windows.h>
#include<atlstr.h>
#include<limits>
#include<iomanip>
#include<io.h>
#include"tinyXML\tinyxml.h"
#include"tinyXML\tinystr.h"
#include"logic_Project.h"
#include"logic_Controller.h"

#define MAX_INT 2147483647
#define MIN_INT -2147483648

class logic_Project;

struct TreeNode{
	int id;
	int parentId;
};


class logic_XmlIO
{
public:
	logic_XmlIO();

	bool IO_FillPrj(const std::string fileName, logic_Project &prj); //读取xml，填充满一个prj
	bool IO_SavePrj(const std::string fileName, logic_Project prj); //读取一个prj，写入一个xml文件
	bool IO_Initial(std::map <int, logic_BasicModule *> &InitModuleMap);
	bool I0_ExportProgram(const std::string fileName,logic_Program program); //项目属性中的导出文件
	bool IO_ImportProgram(const std::string fileName,logic_Project* project);//文件中导入program

//  bool IO_SaveProgram(const std::string fileName,TiXmlElement* rootElement);//将一个program文件单独存储为一个新的xml文件

//	void saveFrontEndPoint(std::map<int, std::map<int, std::map<int, Point>>>); //前端存储点坐标
//	std::map<int, std::map<int, std::map<int, Point>>> loadFrontEndPoint(); //迁都读取点坐标

	bool initialMyModule();

	//测试存储的Module Map,将所有信息打印出来
	void testAllModule(std::map <int, logic_BasicModule *> &InitModuleMap);
	
	bool initialBottom();

#pragma region unit_test
	void testConstruct()
	{
		logic_Project newProject(1,"oneNewProject");
	    logic_Program *testProgram = new logic_Program(1,"oneNewProgram");
		std::map <int, logic_BasicModule *> InitModuleMap;
		logic_VarModule* testVarmodule = new logic_VarModule(10,Text,"30");

		newProject.setPrjDescription("first_test_description");
		newProject.setPrjPhotoPath("no_path_now");
		newProject.newProgram(1,testProgram);
		newProject.newProgram(2,"anotherNewProgram");
		newProject.setPrjVariety(10,testVarmodule);
		
		//initial all the modules
		IO_Initial(InitModuleMap);
		testProgram->setModuleMap(InitModuleMap);

		//******************测试树**************************
		/////树最好建立在堆上，虽然树根建立在栈上不会报错，是因为安全删除的问题
		logic_Tree *tree1 = new logic_Tree(5);

	 	tree1->add_node(5,7);
		tree1->add_node(5,8);
		tree1->add_node(5,10);
 		tree1->insert_node(5,10,6);
 		tree1->add_node(6,11);

		testProgram->add_Tree(tree1);	
		
		testProgram->add_Module(5,1001);
		testProgram->add_Module(7,1001);
		testProgram->add_Module(8,1001);
		testProgram->add_Module(10,1001);
		testProgram->add_Module(6,1001);
		testProgram->add_Module(11,1001);

		logic_BasicModule* module1 = testProgram->searchModule(5);
		logic_BasicModule* module2 = testProgram->searchModule(7);
		logic_BasicModule* module3 = testProgram->searchModule(8);
		logic_BasicModule* module4 = testProgram->searchModule(10);
		logic_BasicModule* module5 = testProgram->searchModule(6);
		logic_BasicModule* module6 = testProgram->searchModule(11);

		module1->setModeValue(1);
		module2->setModeValue(1);
		module3->setModeValue(1);
		module4->setModeValue(1);
		module5->setModeValue(1);
		module6->setModeValue(1);

		////set paralist
		//logic_BasicPara* para1 = new logic_BasicPara();
		//para1->mvi_ParaID = 1;
		//para1->mvs_Value = "1";
		//para1->mvb_IsInport = 0;
		//std::vector <logic_BasicPara*> paraList;
		//paraList.push_back(para1);

		////set port
		//WinSwitcher* switcher = new WinSwitcher();
		//switcher->mve_WSType = WS_PORT_SINGLE;
		//switcher->mvs_WSValue = 1;
		//switcher->mvi_ChainLayer = 0;



		IO_SavePrj("testXml//testXml20160101.xml",newProject);
	};
	
	//bool testSaveOneElement(const char* fileName)
	//{
	//	try
	//	{
	//		TiXmlDocument* xmlFileName = new TiXmlDocument(fileName);
	//		xmlFileName->LoadFile();
	//		TiXmlElement* root = xmlFileName->RootElement();
	//		TiXmlElement* programs = root->FirstChild()->NextSiblingElement()->NextSiblingElement()->NextSiblingElement();
	//		IO_SaveProgram("testXml//testSaveOneElement.xml",programs);

	//	}
	//	catch(std::string& e)
	//	{
	//		std::cout<<"Happen some error in open the project "<<std::endl;
	//		return false;
	//	}

	//};
#pragma endregion unit_test

	//***********************end test******************************

	~logic_XmlIO(void);
protected:
	//判断该文件是否存在	
	int dump_attribs_to_stdout(TiXmlElement* pElement, unsigned int indent);

	const char* getIndent(unsigned int numIndents);
	const char * getIndentAlt(unsigned int numIndents);

	void dump_to_stdout(TiXmlNode* pParent, unsigned int);
	void dump_to_stdout(const char* pFilename);
private:
	//变量
	static const unsigned int NUM_INDENTS_PER_SPACE = 2;
	std::map <int, logic_BasicModule *> allModuleMap;


	//工具函数
	void traverSaveTree(logic_TreeNode* root,TiXmlElement* parent);

	//bool isFileExist()
	bool isFileExist(std::vector<const char*> allFilePaths);
	bool isFileExist(const char* filePath);

	#pragma region initial
	//*******************initial bottom***********************
	

	bool initial1001();
	bool initial1002();
	bool initial1003();
	bool initial1004();
	bool initial1005();
	bool initial1006();
	bool initial1007();

	bool initial2001();
	bool initial2002();
	bool initial2003();
	bool initial2004();
	bool initial2005();

	bool initial3001();
	bool initial3002();
	bool initial3003();
	bool initial3004();
	bool initial3005();
	bool initial3006();
	bool initial3007();
	bool initial3008();
	bool initial3009();
	bool initial3010();
	bool initial3011();

	bool initial4001();
	bool initial4002();
	//阵列运算去除
    //bool initial4003();
	bool initial4004();
	bool initial4005();
	bool initial4006();
	bool initial4007();
	bool initial4008();
	bool initial4009();
	bool initial4010();

	bool initial5001();
	//5002去除
	//bool initial5002();
	bool initial5003();
	bool initial5004();
	bool initial5005();
	bool initial5006();
	bool initial5007();
	bool initial5008();
	bool initial5009();

#pragma endregion initial

	//**********************virables***********************

	//***********************Tools**************************
	
	//第一个参数是xml文件名，第二个参数用来存储初始化值
	bool readInitial(const char* fileName,std::map <int, logic_BasicModule *> &InitModuleMap);

	//还原树
	bool rebuildTree(logic_Tree* treeRoot, std::vector<TreeNode*> allNode);

	//get current root path
	CString GetAppPath()
	{
		TCHAR modulePath[MAX_PATH];
		GetModuleFileName(NULL,modulePath,MAX_PATH);
		CString strModulePath(modulePath);
		strModulePath = strModulePath.Left(strModulePath.ReverseFind(_T('\\')));
		return strModulePath;
	}

	int charPtrToInt(const char* str)
	{
		int result;
		result = atoi(str);
		return result;
	}

	std::string intToString(int n){
    std::stringstream ss;
	ss<<n;
    return ss.str();
}

	int stringToInt(const std::string str)
	{
		std::stringstream ss;
		ss<<str;
		int result;
		ss>>result;
		return result;
	}


	std::vector<int> parseInputList(const std::string list)
{
	std::vector<int> result;
	for (auto index = list.begin(); index != list.end();++index)
	{
		int id = index - list.begin() + 1;
		if((*index)=='1')
		{
			result.push_back(id);
		}
	}
	return result;
}

	//用于初始化时的模块信息的存储
	void fillModule(logic_BasicModule* currentModule,const std::string name, std::string value);

	void fillMode(logic_ParaPointer* mode,const std::string name, std::string value);

	void fillPara(logic_BasicPara* para,const std::string name,const std::string value);

	//用于读取项目文件是的信息存储
	void fillProject(logic_Project &prj,const std::string name, std::string value);

	void fillProgram(std::map<int,logic_Program*> &prgMap,TiXmlElement* firstPrgChild);
	void fillProgram(logic_Program* prg, TiXmlElement* prgElement);
	bool saveProgram(std::map<int, logic_Program*> &programMap, TiXmlElement* parentElement);
	bool saveProgram(logic_Program* program, TiXmlDocument* parentElement);


	void fillVarModule(logic_Project &prj,TiXmlElement* varieties);

	////用于存储某个标签内的所有信息
	//void testAttribute(TiXmlElement* src,TiXmlElement* dst);
	void deepCopyPara(std::vector<logic_BasicPara*>,std::vector<logic_BasicPara*>&);

	bool parseRootToString(std::vector<int>,std::string&);

	bool parseRootToInt(std::vector<int>&,std::string);

	std::vector<const char*> allFilePaths;


	
};

