#include "logic_XmlIO.h"


logic_XmlIO::logic_XmlIO()
{
	if (isFileExist("logicXmls//1001.xml"))
		allFilePaths.push_back("logicXmls//1001.xml");
	if (isFileExist("logicXmls//1002.xml"))
		allFilePaths.push_back("logicXmls//1002.xml");
	if (isFileExist("logicXmls//1003.xml"))
		allFilePaths.push_back("logicXmls//1003.xml");
	if (isFileExist("logicXmls//1004.xml"))
		allFilePaths.push_back("logicXmls//1004.xml");
	if (isFileExist("logicXmls//1005.xml"))
		allFilePaths.push_back("logicXmls//1005.xml");
	if (isFileExist("logicXmls//1006.xml"))
		allFilePaths.push_back("logicXmls//1006.xml");
	if (isFileExist("logicXmls//1007.xml"))
		allFilePaths.push_back("logicXmls//1007.xml");
	if (isFileExist("logicXmls//2001.xml"))
		allFilePaths.push_back("logicXmls//2001.xml");
	if (isFileExist("logicXmls//2002.xml"))
		allFilePaths.push_back("logicXmls//2002.xml");
	if (isFileExist("logicXmls//2003.xml"))
		allFilePaths.push_back("logicXmls//2003.xml");
	if (isFileExist("logicXmls//2004.xml"))
		allFilePaths.push_back("logicXmls//2004.xml");
	if (isFileExist("logicXmls//2005.xml"))
		allFilePaths.push_back("logicXmls//2005.xml");
	if (isFileExist("logicXmls//3001.xml"))
		allFilePaths.push_back("logicXmls//3001.xml");
	if (isFileExist("logicXmls//3002.xml"))
		allFilePaths.push_back("logicXmls//3002.xml");
	if (isFileExist("logicXmls//3003.xml"))
		allFilePaths.push_back("logicXmls//3003.xml");
	if (isFileExist("logicXmls//3004.xml"))
		allFilePaths.push_back("logicXmls//3004.xml");
	if (isFileExist("logicXmls//3005.xml"))
		allFilePaths.push_back("logicXmls//3005.xml");
	if (isFileExist("logicXmls//3006.xml"))
		allFilePaths.push_back("logicXmls//3006.xml");
	if (isFileExist("logicXmls//3007.xml"))
		allFilePaths.push_back("logicXmls//3007.xml");
	if (isFileExist("logicXmls//3008.xml"))
		allFilePaths.push_back("logicXmls//3008.xml");
	if (isFileExist("logicXmls//3009.xml"))
		allFilePaths.push_back("logicXmls//3009.xml");
	if (isFileExist("logicXmls//3010.xml"))
		allFilePaths.push_back("logicXmls//3010.xml");
	if (isFileExist("logicXmls//3011.xml"))
		allFilePaths.push_back("logicXmls//3011.xml");
	if (isFileExist("logicXmls//4001.xml"))
		allFilePaths.push_back("logicXmls//4001.xml");
	if (isFileExist("logicXmls//4002.xml"))
		allFilePaths.push_back("logicXmls//4002.xml");
	if (isFileExist("logicXmls//4004.xml"))
		allFilePaths.push_back("logicXmls//4004.xml");
	if (isFileExist("logicXmls//4005.xml"))
		allFilePaths.push_back("logicXmls//4005.xml");
	if (isFileExist("logicXmls//4006.xml"))
		allFilePaths.push_back("logicXmls//4006.xml");
	if (isFileExist("logicXmls//4007.xml"))
		allFilePaths.push_back("logicXmls//4007.xml");
	if (isFileExist("logicXmls//4008.xml"))
		allFilePaths.push_back("logicXmls//4008.xml");
	if (isFileExist("logicXmls//4009.xml"))
		allFilePaths.push_back("logicXmls//4009.xml");
	if (isFileExist("logicXmls//4010.xml"))
		allFilePaths.push_back("logicXmls//4010.xml");
	if (isFileExist("logicXmls//5001.xml"))
		allFilePaths.push_back("logicXmls//5001.xml");
	if (isFileExist("logicXmls//5003.xml"))
		allFilePaths.push_back("logicXmls//5003.xml");
	if (isFileExist("logicXmls//5004.xml"))
		allFilePaths.push_back("logicXmls//5004.xml");
	if (isFileExist("logicXmls//5005.xml"))
		allFilePaths.push_back("logicXmls//5005.xml");
	if (isFileExist("logicXmls//5006.xml"))
		allFilePaths.push_back("logicXmls//5006.xml");
	if (isFileExist("logicXmls//5007.xml"))
		allFilePaths.push_back("logicXmls//5007.xml");
	if (isFileExist("logicXmls//5008.xml"))
		allFilePaths.push_back("logicXmls//5008.xml");
	if (isFileExist("logicXmls//5009.xml"))
		allFilePaths.push_back("logicXmls//5009.xml");

}

const char * logic_XmlIO::getIndent(unsigned int numIndents)
{
	static const char * pINDENT = "                                      + ";
	static const unsigned int LENGTH = strlen(pINDENT);
	unsigned int n = numIndents*NUM_INDENTS_PER_SPACE;
	if (n > LENGTH) n = LENGTH;

	return &pINDENT[LENGTH - n];
}

// same as getIndent but no "+" at the end
const char * logic_XmlIO::getIndentAlt(unsigned int numIndents)
{
	static const char * pINDENT = "                                        ";
	static const unsigned int LENGTH = strlen(pINDENT);
	unsigned int n = numIndents*NUM_INDENTS_PER_SPACE;
	if (n > LENGTH) n = LENGTH;

	return &pINDENT[LENGTH - n];
}

int logic_XmlIO::dump_attribs_to_stdout(TiXmlElement* pElement, unsigned int indent)
{
	if (!pElement) return 0;

	TiXmlAttribute* pAttrib = pElement->FirstAttribute();
	int i = 0;
	int ival;          //int value
	double dval;       //double value
	const char* pIndent = getIndent(indent);
	printf("\n");
	while (pAttrib)
	{
		printf("%s%s: value=[%s]", pIndent, pAttrib->Name(), pAttrib->Value());

		if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS)    printf(" int=%d", ival);
		if (pAttrib->QueryDoubleValue(&dval) == TIXML_SUCCESS) printf(" d=%1.1f", dval);
		printf("\n");
		i++;
		pAttrib = pAttrib->Next();
	}
	return i;
}

void logic_XmlIO::dump_to_stdout(TiXmlNode* pParent, unsigned int indent = 0)
{
	if (!pParent) return;

	TiXmlNode* pChild;
	TiXmlText* pText;
	int t = pParent->Type();
	printf("%s", getIndent(indent));
	int num;

	switch (t)
	{
	case TiXmlNode::TINYXML_DOCUMENT:
		printf("Document");
		break;

	case TiXmlNode::TINYXML_ELEMENT:
		printf("Element [%s]", pParent->Value());
		num = dump_attribs_to_stdout(pParent->ToElement(), indent + 1);
		switch (num)
		{
		case 0:  printf(" (No attributes)"); break;
		case 1:  printf("%s1 attribute", getIndentAlt(indent)); break;
		default: printf("%s%d attributes", getIndentAlt(indent), num); break;
		}
		break;

	case TiXmlNode::TINYXML_COMMENT:
		printf("Comment: [%s]", pParent->Value());
		break;

	case TiXmlNode::TINYXML_UNKNOWN:
		printf("Unknown");
		break;

	case TiXmlNode::TINYXML_TEXT:
		pText = pParent->ToText();
		printf("Text: [%s]", pText->Value());
		break;

	case TiXmlNode::TINYXML_DECLARATION:
		printf("Declaration");
		break;
	default:
		break;
	}
	printf("\n");
	for (pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		dump_to_stdout(pChild, indent + 1);
	}
}

// load the named file and dump its structure to STDOUT
void logic_XmlIO::dump_to_stdout(const char* pFilename)
{
	TiXmlDocument doc(pFilename);
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
		printf("\n%s:\n", pFilename);
		dump_to_stdout(&doc); // defined later in the tutorial
	}
	else
	{
		printf("Failed to load file \"%s\"\n", pFilename);
	}
}



bool logic_XmlIO::IO_FillPrj(const std::string fileName, logic_Project &prj)
{
	try
	{
		//所有的模块Map
		logic_Controller control;
		allModuleMap = control.ctrlGetInitMap();
		
		//打开文件
		const char* file= fileName.c_str();
		TiXmlDocument* xmlFileName = new TiXmlDocument(file);
		xmlFileName->LoadFile();

		TiXmlElement* root = xmlFileName->RootElement();
		auto prjName = root->Value();
		prj.setPrjName(prjName);
		auto prjId = root->FirstAttribute()->Value();
		prj.setPrjId(stringToInt(prjId));

		//对第一层遍历，即project的信息
		if(root->FirstChild())
		{
			TiXmlNode* child = root->FirstChild()->ToElement();
			for(child; child != NULL; child = child->NextSibling())
			{
				std::string prjInfoName = child->Value();
				if(auto value = child->ToElement()->GetText())
				{
					fillProject(prj,prjInfoName,value);
				}
				else if(prjInfoName == "Programs")  //program list 
				{
					if(child->FirstChildElement())
					{
						TiXmlElement* program = child->FirstChildElement();
						std::map <int ,logic_Program* > programMap;
						fillProgram(programMap,program);
						prj.setProgram(programMap);
					}
				}
				else if(prjInfoName == "Varieties")   //Variet
				{
					if(child->FirstChildElement())
					{
						TiXmlElement* varieties = child->FirstChildElement();
						fillVarModule(prj,varieties);

					}

				}

			}
		}
		return true;
	}
	catch(std::string& e)
	{
		std::cout<<"Happen some error in Fill the project "<<std::endl;
		return false;
	}
}

bool logic_XmlIO::IO_SavePrj(const std::string fileName, logic_Project prj)
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "", ""); 
	TiXmlElement* project = new TiXmlElement("Project");
	TiXmlElement* prjName = new TiXmlElement("Name");
	TiXmlElement* prjDescription = new TiXmlElement("Project_Description");
	TiXmlElement* prjPhotoPath = new TiXmlElement("Photo_Path"); 
	TiXmlElement* prjMyvariety = new TiXmlElement("Varieties"); 
	TiXmlElement* ProgramList = new TiXmlElement("Programs");
	TiXmlText *nameContent = new TiXmlText(prj.getPrjName().c_str());
	TiXmlText *descriptionContent = new TiXmlText(prj.getPrjDescription().c_str());
	TiXmlText *photoPath = new TiXmlText(prj.getPrjPhotoPath().c_str());

	//set attribute
	project->SetAttribute("id",prj.getPrjId());
	
	//link child
	doc.LinkEndChild(dec);
	doc.LinkEndChild(project);
	project->LinkEndChild(prjName);
	project->LinkEndChild(prjPhotoPath);
	project->LinkEndChild(prjDescription);
	project->LinkEndChild(ProgramList);
	project->LinkEndChild(prjMyvariety);
	prjName->LinkEndChild(nameContent);
	prjDescription->LinkEndChild(descriptionContent);
	prjPhotoPath->LinkEndChild(photoPath);
	
	//all program map  
	std::map<int,logic_Program*> programMap = prj.getAllProgram();           
	auto isPrgSaveRight = saveProgram(programMap,ProgramList);
	
	//all varieties map
	auto varietiesMap = prj.getPrjVariety();
	for(auto index = varietiesMap.begin();index!=varietiesMap.end();++index)
	{
		TiXmlElement* variety = new TiXmlElement("variety");
		int id = index->first;
		auto varModule = index->second;
		auto varType = varModule->getType();
		auto varValue = varModule->getValue();
		variety->SetAttribute("id",id);
		variety->SetAttribute("type",varType.c_str());
		variety->SetAttribute("value",varValue.c_str());
		prjMyvariety->LinkEndChild(variety);
	}

	dump_to_stdout(&doc);

	if(doc.SaveFile(fileName.c_str()))
		return true;
	else 
		return false;
}

//DFS遍历保存树
void logic_XmlIO::traverSaveTree(logic_TreeNode * root,TiXmlElement* parent)
{
	if(root == NULL) return ;
	TiXmlElement* childID = new TiXmlElement(intToString(root->getID()).c_str());
	parent->LinkEndChild(childID);
	std::vector<logic_TreeNode *> child = root->mvvu_Children;	

	for(auto index = child.begin();index!=child.end();++index)
	{
		traverSaveTree(*index,childID);
	}
	
}

logic_XmlIO::~logic_XmlIO()
{
}

bool logic_XmlIO::initialBottom()
{
	if(initial5004())
		return true;
	else
		return false;
}

bool logic_XmlIO::initial1001()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");
	//mode
	TiXmlElement* mode = new TiXmlElement("Mode");
	TiXmlElement* close = new TiXmlElement("close");
	TiXmlElement* open = new TiXmlElement("open");
	TiXmlElement* openSecond = new TiXmlElement("openSecond");
	TiXmlElement* openDegree = new TiXmlElement("openDegree");
	TiXmlElement* openRound = new TiXmlElement("openRound");
	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* power = new TiXmlElement("power");
	TiXmlElement* round = new TiXmlElement("Round");
	TiXmlElement* brake = new TiXmlElement("brake");
	TiXmlElement* second = new TiXmlElement("second");
	TiXmlElement* degree = new TiXmlElement("degree");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",1001);
	module->SetAttribute("Mode",4);
	module->SetAttribute("WinSwitcherValue","A");
	module->SetAttribute("WinSwitcherType",2);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	close->SetAttribute("id",1); 
	close->SetAttribute("include","01000");
	close->SetAttribute("WinSwitcherType",2);
	close->SetAttribute("WinSwitcherValue","A");
	close->SetAttribute("ChainLayer",0);

	open->SetAttribute("id",2);
	open->SetAttribute("include","10000");
	open->SetAttribute("WinSwitcherType",2);
	open->SetAttribute("WinSwitcherValue","A");
	open->SetAttribute("ChainLayer",0);

	openSecond->SetAttribute("id",3);
	openSecond->SetAttribute("include","11100");
	openSecond->SetAttribute("WinSwitcherType",2);
	openSecond->SetAttribute("WinSwitcherValue","A");
	openSecond->SetAttribute("ChainLayer",0);

	openDegree->SetAttribute("id",4);
	openDegree->SetAttribute("include","11010");
	openDegree->SetAttribute("WinSwitcherType",2);
	openDegree->SetAttribute("WinSwitcherValue","A");
	openDegree->SetAttribute("ChainLayer",0);
	
	openRound->SetAttribute("id",5);
	openRound ->SetAttribute("include","11001");
	openRound->SetAttribute("WinSwitcherType",2);
	openRound->SetAttribute("WinSwitcherValue","A");
	openRound->SetAttribute("ChainLayer",0);

	//input attribute
	power->SetAttribute("id",1);
	power->SetAttribute("default",50);
	power->SetAttribute("type","PARA_NUM");
	power->SetAttribute("max",100);
	power->SetAttribute("min",-100);
	power->SetAttribute("InOrOut","PARA_IN");
	power->SetAttribute("IsPort",0);

	round->SetAttribute("id",2);
	round->SetAttribute("default",1);
	round->SetAttribute("type","PARA_NUM");
	round->SetAttribute("max",MAX_INT);
	round->SetAttribute("min",MIN_INT);
	round->SetAttribute("InOrOut","PARA_IN");
	round->SetAttribute("IsPort",0);

	brake->SetAttribute("id",3);
	brake->SetAttribute("default",1);
	brake->SetAttribute("type","PARA_LOGIC");
	brake->SetAttribute("max",1);
	brake->SetAttribute("min",0);
	brake->SetAttribute("InOrOut","PARA_IN");
	brake->SetAttribute("IsPort",0);

	second->SetAttribute("id",4);
	second->SetAttribute("default",1);
	second->SetAttribute("type","PARA_NUM");
	second->SetAttribute("max",MAX_INT);
	second->SetAttribute("min",0);
	second->SetAttribute("InOrOut","PARA_IN");
	second->SetAttribute("IsPort",0);

	degree->SetAttribute("id",5);
	degree->SetAttribute("default",1);
	degree->SetAttribute("type","PARA_NUM");
	degree->SetAttribute("max",MAX_INT);
	degree->SetAttribute("min",MIN_INT);
	degree->SetAttribute("InOrOut","PARA_IN");
	degree->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(close);
	mode->LinkEndChild(open);
	mode->LinkEndChild(openSecond);
	mode->LinkEndChild(openDegree);
	mode->LinkEndChild(openRound);

	inputList->LinkEndChild(power);
	inputList->LinkEndChild(round);
	inputList->LinkEndChild(brake);
	inputList->LinkEndChild(second);
	inputList->LinkEndChild(degree);

	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//1001.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial1002()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");
	//mode
	TiXmlElement* mode = new TiXmlElement("Mode");
	TiXmlElement* close = new TiXmlElement("close");
	TiXmlElement* open = new TiXmlElement("open");
	TiXmlElement* openSecond = new TiXmlElement("openSecond");
	TiXmlElement* openDegree = new TiXmlElement("openDegree");
	TiXmlElement* openRound = new TiXmlElement("openRound");
	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* power = new TiXmlElement("power");
	TiXmlElement* brake = new TiXmlElement("brake");
	TiXmlElement* second = new TiXmlElement("second");
	TiXmlElement* degree = new TiXmlElement("degree");
	TiXmlElement* round = new TiXmlElement("Round");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",1002);
	module->SetAttribute("Mode",5);
	module->SetAttribute("WinSwitcherValue","D");
	module->SetAttribute("WinSwitcherType",2);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	close->SetAttribute("id",1); 
	close->SetAttribute("include","01000");
	close->SetAttribute("WinSwitcherType",2);
	close->SetAttribute("WinSwitcherValue","A");
	close->SetAttribute("ChainLayer",0);

	open->SetAttribute("id",2);
	open->SetAttribute("include","10000");
	open->SetAttribute("WinSwitcherType",2);
	open->SetAttribute("WinSwitcherValue","A");
	open->SetAttribute("ChainLayer",0);

	openSecond->SetAttribute("id",3);
	openSecond->SetAttribute("include","11100");
	openSecond->SetAttribute("WinSwitcherType",2);
	openSecond->SetAttribute("WinSwitcherValue","A");
	openSecond->SetAttribute("ChainLayer",0);

	openDegree->SetAttribute("id",4);
	openDegree->SetAttribute("include","11010");
	openDegree->SetAttribute("WinSwitcherType",2);
	openDegree->SetAttribute("WinSwitcherValue","A");
	openDegree->SetAttribute("ChainLayer",0);
	
	openRound->SetAttribute("id",5);
	openRound ->SetAttribute("include","11001");
	openRound->SetAttribute("WinSwitcherType",2);
	openRound->SetAttribute("WinSwitcherValue","A");
	openRound->SetAttribute("ChainLayer",0);

	//input attribute
	power->SetAttribute("id",1);
	power->SetAttribute("default",50);
	power->SetAttribute("type","PARA_NUM");
	power->SetAttribute("max",100);
	power->SetAttribute("min",-100);
	power->SetAttribute("InOrOut","PARA_IN");
	power->SetAttribute("IsPort",0);

	round->SetAttribute("id",2);
	round->SetAttribute("default",1);
	round->SetAttribute("type","PARA_NUM");
	round->SetAttribute("max",MAX_INT);
	round->SetAttribute("min",MIN_INT);
	round->SetAttribute("InOrOut","PARA_IN");
	round->SetAttribute("IsPort",0);

	brake->SetAttribute("id",3);
	brake->SetAttribute("default",1);
	brake->SetAttribute("type","PARA_LOGIC");
	brake->SetAttribute("max",1);
	brake->SetAttribute("min",0);
	brake->SetAttribute("InOrOut","PARA_IN");
	brake->SetAttribute("IsPort",0);

	second->SetAttribute("id",4);
	second->SetAttribute("default",1);
	second->SetAttribute("type","PARA_NUM");
	second->SetAttribute("max",MAX_INT);
	second->SetAttribute("min",0);
	second->SetAttribute("InOrOut","PARA_IN");
	second->SetAttribute("IsPort",0);

	degree->SetAttribute("id",5);
	degree->SetAttribute("default",1);
	degree->SetAttribute("type","PARA_NUM");
	degree->SetAttribute("max",MAX_INT);
	degree->SetAttribute("min",MIN_INT);
	degree->SetAttribute("InOrOut","PARA_IN");
	degree->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(close);
	mode->LinkEndChild(open);
	mode->LinkEndChild(openSecond);
	mode->LinkEndChild(openDegree);
	mode->LinkEndChild(openRound);

	inputList->LinkEndChild(power);
	inputList->LinkEndChild(round);
	inputList->LinkEndChild(brake);
	inputList->LinkEndChild(second);
	inputList->LinkEndChild(degree);

	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//1002.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial1003()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");
	//mode
	TiXmlElement* mode = new TiXmlElement("Mode");
	TiXmlElement* close = new TiXmlElement("close");
	TiXmlElement* open = new TiXmlElement("open");
	TiXmlElement* openSecond = new TiXmlElement("openSecond");
	TiXmlElement* openDegree = new TiXmlElement("openDegree");
	TiXmlElement* openRound = new TiXmlElement("openRound");
	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* power = new TiXmlElement("power");
	TiXmlElement* direction = new TiXmlElement("direction");
	TiXmlElement* brake = new TiXmlElement("brake");
	TiXmlElement* second = new TiXmlElement("second");
	TiXmlElement* degree = new TiXmlElement("degree");
	TiXmlElement* round = new TiXmlElement("Round");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",1003);
	module->SetAttribute("Mode",5);
	module->SetAttribute("WinSwitcherValue","B+C");
	module->SetAttribute("WinSwitcherType",3);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	close->SetAttribute("id",1); 
	close->SetAttribute("include","001000");
	close->SetAttribute("WinSwitcherType",2);
	close->SetAttribute("WinSwitcherValue","A");
	close->SetAttribute("ChainLayer",0);

	open->SetAttribute("id",2);
	open->SetAttribute("include","110000");
	open->SetAttribute("WinSwitcherType",2);
	open->SetAttribute("WinSwitcherValue","A");
	open->SetAttribute("ChainLayer",0);

	openSecond->SetAttribute("id",3);
	openSecond->SetAttribute("include","111100");
	openSecond->SetAttribute("WinSwitcherType",2);
	openSecond->SetAttribute("WinSwitcherValue","A");
	openSecond->SetAttribute("ChainLayer",0);

	openDegree->SetAttribute("id",4);
	openDegree->SetAttribute("include","111010");
	openDegree->SetAttribute("WinSwitcherType",2);
	openDegree->SetAttribute("WinSwitcherValue","A");
	openDegree->SetAttribute("ChainLayer",0);
	
	openRound->SetAttribute("id",5);
	openRound ->SetAttribute("include","111001");
	openRound->SetAttribute("WinSwitcherType",2);
	openRound->SetAttribute("WinSwitcherValue","A");
	openRound->SetAttribute("ChainLayer",0);

	//input attribute
	power->SetAttribute("id",1);
	power->SetAttribute("default",50);
	power->SetAttribute("type","PARA_NUM");
	power->SetAttribute("max",100);
	power->SetAttribute("min",-100);
	power->SetAttribute("InOrOut","PARA_IN");
	power->SetAttribute("IsPort",0);

	direction->SetAttribute("id",2);
	direction->SetAttribute("default",0);
	direction->SetAttribute("type","PARA_NUM");
	direction->SetAttribute("max",100);
	direction->SetAttribute("min",-100);
	direction->SetAttribute("InOrOut","PARA_IN");
	direction->SetAttribute("IsPort",0);

	round->SetAttribute("id",3);
	round->SetAttribute("default",1);
	round->SetAttribute("type","PARA_NUM");
	round->SetAttribute("max",MAX_INT);
	round->SetAttribute("min",MIN_INT);
	round->SetAttribute("InOrOut","PARA_IN");
	round->SetAttribute("IsPort",0);

	brake->SetAttribute("id",4);
	brake->SetAttribute("default",1);
	brake->SetAttribute("type","PARA_LOGIC");
	brake->SetAttribute("max",1);
	brake->SetAttribute("min",0);
	brake->SetAttribute("InOrOut","PARA_IN");
	brake->SetAttribute("IsPort",0);

	second->SetAttribute("id",5);
	second->SetAttribute("default",1);
	second->SetAttribute("type","PARA_NUM");
	second->SetAttribute("max",MAX_INT);
	second->SetAttribute("min",0);
	second->SetAttribute("InOrOut","PARA_IN");
	second->SetAttribute("IsPort",0);

	degree->SetAttribute("id",6);
	degree->SetAttribute("default",1);
	degree->SetAttribute("type","PARA_NUM");
	degree->SetAttribute("max",MAX_INT);
	degree->SetAttribute("min",MIN_INT);
	degree->SetAttribute("InOrOut","PARA_IN");
	degree->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(close);
	mode->LinkEndChild(open);
	mode->LinkEndChild(openSecond);
	mode->LinkEndChild(openDegree);
	mode->LinkEndChild(openRound);

	inputList->LinkEndChild(power);
	inputList->LinkEndChild(direction);
	inputList->LinkEndChild(round);
	inputList->LinkEndChild(brake);
	inputList->LinkEndChild(second);
	inputList->LinkEndChild(degree);

	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//1003.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial1004()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");
	//mode
	TiXmlElement* mode = new TiXmlElement("Mode");
	TiXmlElement* close = new TiXmlElement("close");
	TiXmlElement* open = new TiXmlElement("open");
	TiXmlElement* openSecond = new TiXmlElement("openSecond");
	TiXmlElement* openDegree = new TiXmlElement("openDegree");
	TiXmlElement* openRound = new TiXmlElement("openRound");
	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* leftPower = new TiXmlElement("leftPower");
	TiXmlElement* rightPower = new TiXmlElement("rightPower");
	TiXmlElement* brake = new TiXmlElement("brake");
	TiXmlElement* second = new TiXmlElement("second");
	TiXmlElement* degree = new TiXmlElement("degree");
	TiXmlElement* round = new TiXmlElement("Round");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",1004);
	module->SetAttribute("Mode",5);
	module->SetAttribute("WinSwitcherValue","B+C");
	module->SetAttribute("WinSwitcherType",3);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	close->SetAttribute("id",1); 
	close->SetAttribute("include","001000");
	close->SetAttribute("WinSwitcherType",2);
	close->SetAttribute("WinSwitcherValue","A");
	close->SetAttribute("ChainLayer",0);

	open->SetAttribute("id",2);
	open->SetAttribute("include","110000");
	open->SetAttribute("WinSwitcherType",2);
	open->SetAttribute("WinSwitcherValue","A");
	open->SetAttribute("ChainLayer",0);

	openSecond->SetAttribute("id",3);
	openSecond->SetAttribute("include","111100");
	openSecond->SetAttribute("WinSwitcherType",2);
	openSecond->SetAttribute("WinSwitcherValue","A");
	openSecond->SetAttribute("ChainLayer",0);

	openDegree->SetAttribute("id",4);
	openDegree->SetAttribute("include","111010");
	openDegree->SetAttribute("WinSwitcherType",2);
	openDegree->SetAttribute("WinSwitcherValue","A");
	openDegree->SetAttribute("ChainLayer",0);
	
	openRound->SetAttribute("id",5);
	openRound ->SetAttribute("include","111001");
	openRound->SetAttribute("WinSwitcherType",2);
	openRound->SetAttribute("WinSwitcherValue","A");
	openRound->SetAttribute("ChainLayer",0);

	//input attribute
	leftPower->SetAttribute("id",1);
	leftPower->SetAttribute("default",50);
	leftPower->SetAttribute("type","PARA_NUM");
	leftPower->SetAttribute("max",100);
	leftPower->SetAttribute("min",-100);
	leftPower->SetAttribute("InOrOut","PARA_IN");
	leftPower->SetAttribute("IsPort",0);

	rightPower->SetAttribute("id",2);
	rightPower->SetAttribute("default",50);
	rightPower->SetAttribute("type","PARA_NUM");
	rightPower->SetAttribute("max",100);
	rightPower->SetAttribute("min",-100);
	rightPower->SetAttribute("InOrOut","PARA_IN");
	rightPower->SetAttribute("IsPort",0);

	round->SetAttribute("id",3);
	round->SetAttribute("default",1);
	round->SetAttribute("type","PARA_NUM");
	round->SetAttribute("max",MAX_INT);
	round->SetAttribute("min",MIN_INT);
	round->SetAttribute("InOrOut","PARA_IN");
	round->SetAttribute("IsPort",0);

	brake->SetAttribute("id",4);
	brake->SetAttribute("default",1);
	brake->SetAttribute("type","PARA_LOGIC");
	brake->SetAttribute("max",1);
	brake->SetAttribute("min",0);
	brake->SetAttribute("InOrOut","PARA_IN");
	brake->SetAttribute("IsPort",0);

	second->SetAttribute("id",5);
	second->SetAttribute("default",1);
	second->SetAttribute("type","PARA_NUM");
	second->SetAttribute("max",MAX_INT);
	second->SetAttribute("min",0);
	second->SetAttribute("InOrOut","PARA_IN");
	second->SetAttribute("IsPort",0);

	degree->SetAttribute("id",6);
	degree->SetAttribute("default",1);
	degree->SetAttribute("type","PARA_NUM");
	degree->SetAttribute("max",MAX_INT);
	degree->SetAttribute("min",MIN_INT);
	degree->SetAttribute("InOrOut","PARA_IN");
	degree->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(close);
	mode->LinkEndChild(open);
	mode->LinkEndChild(openSecond);
	mode->LinkEndChild(openDegree);
	mode->LinkEndChild(openRound);

	inputList->LinkEndChild(leftPower);
	inputList->LinkEndChild(rightPower);
	inputList->LinkEndChild(round);
	inputList->LinkEndChild(brake);
	inputList->LinkEndChild(second);
	inputList->LinkEndChild(degree);

	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//1004.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial1005()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");
	//mode
	TiXmlElement* mode = new TiXmlElement("Mode");
	TiXmlElement* pixel = new TiXmlElement("pixel");
	TiXmlElement* grid = new TiXmlElement("grid");
	TiXmlElement* line = new TiXmlElement("line");
	TiXmlElement* circle = new TiXmlElement("circle");
	TiXmlElement* rectangle = new TiXmlElement("rectangle");
	TiXmlElement* dot = new TiXmlElement("dot");
	TiXmlElement* photo = new TiXmlElement("photo");
	TiXmlElement* reset = new TiXmlElement("reset");

	//input list
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* clear = new TiXmlElement("clear");
	TiXmlElement* fileName = new TiXmlElement("fileName");
	TiXmlElement* context = new TiXmlElement("context");
	TiXmlElement* columns = new TiXmlElement("columns");
	TiXmlElement* rows = new TiXmlElement("rows");
	TiXmlElement* X = new TiXmlElement("X");
	TiXmlElement* Y = new TiXmlElement("Y");
	TiXmlElement* X1 = new TiXmlElement("X1");
	TiXmlElement* Y1 = new TiXmlElement("Y1");
	TiXmlElement* X2 = new TiXmlElement("X2");
	TiXmlElement* Y2 = new TiXmlElement("Y2");
	TiXmlElement* radius = new TiXmlElement("radius");
	TiXmlElement* width = new TiXmlElement("width");
	TiXmlElement* height = new TiXmlElement("height");
	TiXmlElement* isFull = new TiXmlElement("isFull");
	TiXmlElement* color = new TiXmlElement("color");
	TiXmlElement* font = new TiXmlElement("font");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",1005);
	module->SetAttribute("Mode",7);
	module->SetAttribute("WinSwitcherValue","");
	module->SetAttribute("WinSwitcherType",8);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	pixel->SetAttribute("id",1); 
	pixel->SetAttribute("include","11000110000000011");
	pixel->SetAttribute("WinSwitcherType",4);
	pixel->SetAttribute("WinSwitcherValue","IAISROBOT");
	pixel->SetAttribute("ChainLayer",0);

	grid->SetAttribute("id",2);
	grid->SetAttribute("include","11011000000000011");
	grid->SetAttribute("WinSwitcherType",4);
	grid->SetAttribute("WinSwitcherValue","IAISROBOT");
	grid->SetAttribute("ChainLayer",0);

	line->SetAttribute("id",3);
	line->SetAttribute("include","10000001111000010");
	line->SetAttribute("WinSwitcherType",0);
	line->SetAttribute("WinSwitcherValue","");
	line->SetAttribute("ChainLayer",0);

	circle->SetAttribute("id",4);
	circle->SetAttribute("include","10000110000100110");
	circle->SetAttribute("WinSwitcherType",0);
	circle->SetAttribute("WinSwitcherValue","");
	circle->SetAttribute("ChainLayer",0);
	
	rectangle->SetAttribute("id",5);
	rectangle ->SetAttribute("include","10000110000011110");
	rectangle->SetAttribute("WinSwitcherType",0);
	rectangle->SetAttribute("WinSwitcherValue","");
	rectangle->SetAttribute("ChainLayer",0);

	dot->SetAttribute("id",6);
	dot ->SetAttribute("include","10000110000000010");
	dot->SetAttribute("WinSwitcherType",0);
	dot->SetAttribute("WinSwitcherValue","");
	dot->SetAttribute("ChainLayer",0);

	photo->SetAttribute("id",7);
	photo ->SetAttribute("include","11000110000000000");
	photo->SetAttribute("WinSwitcherType",8);
	photo->SetAttribute("WinSwitcherValue","");
	photo->SetAttribute("ChainLayer",0);

	reset->SetAttribute("id",8);
	reset ->SetAttribute("include","00000000000000000");
	reset->SetAttribute("WinSwitcherType",0);
	reset->SetAttribute("WinSwitcherValue","");
	reset->SetAttribute("ChainLayer",0);

	//input attribute
	clear->SetAttribute("id",1);
	clear->SetAttribute("default",1);
	clear->SetAttribute("type","PARA_LOGIC");
	clear->SetAttribute("max",1);
	clear->SetAttribute("min",0);
	clear->SetAttribute("InOrOut","PARA_IN");
	clear->SetAttribute("IsPort",0);

	fileName->SetAttribute("id",2);
	fileName->SetAttribute("default","");
	fileName->SetAttribute("type","PARA_TEXT");
	fileName->SetAttribute("max",0);
	fileName->SetAttribute("min",0);
	fileName->SetAttribute("InOrOut","PARA_IN");
	fileName->SetAttribute("IsPort",0);

	context->SetAttribute("id",3);
	context->SetAttribute("default","");
	context->SetAttribute("type","PARA_TEXT");
	context->SetAttribute("max",0);
	context->SetAttribute("min",0);
	context->SetAttribute("InOrOut","PARA_IN");
	context->SetAttribute("IsPort",0);

	columns->SetAttribute("id",4);
	columns->SetAttribute("default",0);
	columns->SetAttribute("type","PARA_NUM");
	columns->SetAttribute("max",21);
	columns->SetAttribute("min",0);
	columns->SetAttribute("InOrOut","PARA_IN");
	columns->SetAttribute("IsPort",0);

	rows->SetAttribute("id",5);
	rows->SetAttribute("default",0);
	rows->SetAttribute("type","PARA_NUM");
	rows->SetAttribute("max",11);
	rows->SetAttribute("min",0);
	rows->SetAttribute("InOrOut","PARA_IN");
	rows->SetAttribute("IsPort",0);

	X->SetAttribute("id",6);
	X->SetAttribute("default",0);
	X->SetAttribute("type","PARA_NUM");
	X->SetAttribute("max",177);
	X->SetAttribute("min",0);
	X->SetAttribute("InOrOut","PARA_IN");
	X->SetAttribute("IsPort",0);

	Y->SetAttribute("id",7);
	Y->SetAttribute("default",0);
	Y->SetAttribute("type","PARA_NUM");
	Y->SetAttribute("max",127);
	Y->SetAttribute("min",0);
	Y->SetAttribute("InOrOut","PARA_IN");
	Y->SetAttribute("IsPort",0);

	X1->SetAttribute("id",8);
	X1->SetAttribute("default",0);
	X1->SetAttribute("type","PARA_NUM");
	X1->SetAttribute("max",177);
	X1->SetAttribute("min",0);
	X1->SetAttribute("InOrOut","PARA_IN");
	X1->SetAttribute("IsPort",0);

	Y1->SetAttribute("id",9);
	Y1->SetAttribute("default",0);
	Y1->SetAttribute("type","PARA_NUM");
	Y1->SetAttribute("max",127);
	Y1->SetAttribute("min",0);
	Y1->SetAttribute("InOrOut","PARA_IN");
	Y1->SetAttribute("IsPort",0);

	X2->SetAttribute("id",10);
	X2->SetAttribute("default",0);
	X2->SetAttribute("type","PARA_NUM");
	X2->SetAttribute("max",177);
	X2->SetAttribute("min",0);
	X2->SetAttribute("InOrOut","PARA_IN");
	X2->SetAttribute("IsPort",0);

	Y2->SetAttribute("id",11);
	Y2->SetAttribute("default",0);
	Y2->SetAttribute("type","PARA_NUM");
	Y2->SetAttribute("max",127);
	Y2->SetAttribute("min",0);
	Y2->SetAttribute("InOrOut","PARA_IN");
	Y2->SetAttribute("IsPort",0);

	radius->SetAttribute("id",12);
	radius->SetAttribute("default",40);
	radius->SetAttribute("type","PARA_NUM");
	radius->SetAttribute("max",MAX_INT);
	radius->SetAttribute("min",0);
	radius->SetAttribute("InOrOut","PARA_IN");
	radius->SetAttribute("IsPort",0);

	width->SetAttribute("id",13);
	width->SetAttribute("default",80);
	width->SetAttribute("type","PARA_NUM");
	width->SetAttribute("max",MAX_INT);
	width->SetAttribute("min",0);
	width->SetAttribute("InOrOut","PARA_IN");
	width->SetAttribute("IsPort",0);

	height->SetAttribute("id",14);
	height->SetAttribute("default",80);
	height->SetAttribute("type","PARA_NUM");
	height->SetAttribute("max",MAX_INT);
	height->SetAttribute("min",0);
	height->SetAttribute("InOrOut","PARA_IN");
	height->SetAttribute("IsPort",0);

	isFull->SetAttribute("id",15);
	isFull->SetAttribute("default",0);
	isFull->SetAttribute("type","PARA_LOGIC");
	isFull->SetAttribute("max",1);
	isFull->SetAttribute("min",0);
	isFull->SetAttribute("InOrOut","PARA_IN");
	isFull->SetAttribute("IsPort",0);

	color->SetAttribute("id",16);
	color->SetAttribute("default",0);
	color->SetAttribute("type","PARA_LOGIC");
	color->SetAttribute("max",1);
	color->SetAttribute("min",0);
	color->SetAttribute("InOrOut","PARA_IN");
	color->SetAttribute("IsPort",0);

	font->SetAttribute("id",17);
	font->SetAttribute("default",2);
	font->SetAttribute("type","PARA_NUM");
	font->SetAttribute("max",2);
	font->SetAttribute("min",0);
	font->SetAttribute("InOrOut","PARA_IN");
	font->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(pixel);
	mode->LinkEndChild(grid);
	mode->LinkEndChild(line);
	mode->LinkEndChild(circle);
	mode->LinkEndChild(rectangle);
	mode->LinkEndChild(dot);
	mode->LinkEndChild(photo);
	mode->LinkEndChild(reset);

	inputList->LinkEndChild(clear);
	inputList->LinkEndChild(fileName);
	inputList->LinkEndChild(context);
	inputList->LinkEndChild(columns);
	inputList->LinkEndChild(rows);
	inputList->LinkEndChild(X);
	inputList->LinkEndChild(Y);
	inputList->LinkEndChild(X1);
	inputList->LinkEndChild(Y1);
	inputList->LinkEndChild(X2);
	inputList->LinkEndChild(Y2);
	inputList->LinkEndChild(radius);
	inputList->LinkEndChild(width);
	inputList->LinkEndChild(height);
	inputList->LinkEndChild(isFull);
	inputList->LinkEndChild(color);
	inputList->LinkEndChild(font);

	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//1005.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial1006()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");
	//mode
	TiXmlElement* mode = new TiXmlElement("Mode");
	TiXmlElement* stop = new TiXmlElement("stop");
	TiXmlElement* openFile = new TiXmlElement("openFile");
	TiXmlElement* openFrequency = new TiXmlElement("openFrequency");
	TiXmlElement* openNotes = new TiXmlElement("openNotes");
	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* fileName = new TiXmlElement("fileName");
	TiXmlElement* notes = new TiXmlElement("notes");
	TiXmlElement* frequency = new TiXmlElement("frequency");
	TiXmlElement* lastTime = new TiXmlElement("lastTime");
	TiXmlElement* volume = new TiXmlElement("volume");
	TiXmlElement* type = new TiXmlElement("type");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",1006);
	module->SetAttribute("Mode",2);
	module->SetAttribute("WinSwitcherValue","");
	module->SetAttribute("WinSwitcherType",8);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	stop->SetAttribute("id",1); 
	stop->SetAttribute("include","000000");
	stop->SetAttribute("WinSwitcherType",0);
	stop->SetAttribute("WinSwitcherValue","");
	stop->SetAttribute("ChainLayer",0);

	openFile->SetAttribute("id",2);
	openFile->SetAttribute("include","100011");
	openFile->SetAttribute("WinSwitcherType",0);
	openFile->SetAttribute("WinSwitcherValue","");
	openFile->SetAttribute("ChainLayer",0);

	openFrequency->SetAttribute("id",3);
	openFrequency->SetAttribute("include","001111");
	openFrequency->SetAttribute("WinSwitcherType",0);
	openFrequency->SetAttribute("WinSwitcherValue","");
	openFrequency->SetAttribute("ChainLayer",0);

	openNotes->SetAttribute("id",4);
	openNotes->SetAttribute("include","010111");
	openNotes->SetAttribute("WinSwitcherType",0);
	openNotes->SetAttribute("WinSwitcherValue","");
	openNotes->SetAttribute("ChainLayer",0);


	//input attribute
	fileName->SetAttribute("id",1);
	fileName->SetAttribute("default","");
	fileName->SetAttribute("type","PARA_TEXT");
	fileName->SetAttribute("max",0);
	fileName->SetAttribute("min",0);
	fileName->SetAttribute("InOrOut","PARA_IN");
	fileName->SetAttribute("IsPort",0);

	notes->SetAttribute("id",2);
	notes->SetAttribute("default","A5");
	notes->SetAttribute("type","PARA_TEXT");
	notes->SetAttribute("max",0);
	notes->SetAttribute("min",0);
	notes->SetAttribute("InOrOut","PARA_IN");
	notes->SetAttribute("IsPort",0);

	frequency->SetAttribute("id",3);
	frequency->SetAttribute("default",440);
	frequency->SetAttribute("type","PARA_NUM");
	frequency->SetAttribute("max",10000);
	frequency->SetAttribute("min",300);
	frequency->SetAttribute("InOrOut","PARA_IN");
	frequency->SetAttribute("IsPort",0);

	lastTime->SetAttribute("id",4);
	lastTime->SetAttribute("default",1);
	lastTime->SetAttribute("type","PARA_NUM");
	lastTime->SetAttribute("max",MAX_INT);
	lastTime->SetAttribute("min",0);
	lastTime->SetAttribute("InOrOut","PARA_IN");
	lastTime->SetAttribute("IsPort",0);

	volume->SetAttribute("id",5);
	volume->SetAttribute("default",100);
	volume->SetAttribute("type","PARA_NUM");
	volume->SetAttribute("max",100);
	volume->SetAttribute("min",0);
	volume->SetAttribute("InOrOut","PARA_IN");
	volume->SetAttribute("IsPort",0);

	type->SetAttribute("id",6);
	type->SetAttribute("default",0);
	type->SetAttribute("type","PARA_NUM");
	type->SetAttribute("max",2);
	type->SetAttribute("min",0);
	type->SetAttribute("InOrOut","PARA_IN");
	type->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(stop);
	mode->LinkEndChild(openFile);
	mode->LinkEndChild(openFrequency);
	mode->LinkEndChild(openNotes);

	inputList->LinkEndChild(fileName);
	inputList->LinkEndChild(notes);
	inputList->LinkEndChild(frequency);
	inputList->LinkEndChild(lastTime);
	inputList->LinkEndChild(volume); 
	inputList->LinkEndChild(type);

	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//1006.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial1007()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");
	//mode
	TiXmlElement* mode = new TiXmlElement("Mode");
	TiXmlElement* close = new TiXmlElement("close");
	TiXmlElement* open = new TiXmlElement("open");
	TiXmlElement* reset = new TiXmlElement("reset");
	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* color = new TiXmlElement("color");
	TiXmlElement* blink = new TiXmlElement("blink");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",1007);
	module->SetAttribute("Mode",2);
	module->SetAttribute("WinSwitcherValue","");
	module->SetAttribute("WinSwitcherType",0);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	close->SetAttribute("id",1); 
	close->SetAttribute("include","000000");
	close->SetAttribute("WinSwitcherType",0);
	close->SetAttribute("WinSwitcherValue","");
	close->SetAttribute("ChainLayer",0);

	open->SetAttribute("id",2);
	open->SetAttribute("include","11");
	open->SetAttribute("WinSwitcherType",0);
	open->SetAttribute("WinSwitcherValue","");
	open->SetAttribute("ChainLayer",0);

	reset->SetAttribute("id",3);
	reset->SetAttribute("include","00");
	reset->SetAttribute("WinSwitcherType",0);
	reset->SetAttribute("WinSwitcherValue","");
	reset->SetAttribute("ChainLayer",0);

	//input attribute
	color->SetAttribute("id",1);
	color->SetAttribute("default","1");
	color->SetAttribute("type","PARA_NUM");
	color->SetAttribute("max",2);
	color->SetAttribute("min",0);
	color->SetAttribute("InOrOut","PARA_IN");
	color->SetAttribute("IsPort",0);

	blink->SetAttribute("id",2);
	blink->SetAttribute("default","1");
	blink->SetAttribute("type","PARA_LOGIC");
	blink->SetAttribute("max",1);
	blink->SetAttribute("min",0);
	blink->SetAttribute("InOrOut","PARA_IN");
	blink->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(close);
	mode->LinkEndChild(open);
	mode->LinkEndChild(reset);

	inputList->LinkEndChild(color);
	inputList->LinkEndChild(blink);

	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//1007.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial2001()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");
	//mode
	TiXmlElement* mode = new TiXmlElement("Mode");
	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",2001);
	module->SetAttribute("Mode",0);
	module->SetAttribute("WinSwitcherValue","");
	module->SetAttribute("WinSwitcherType",0);
	module->SetAttribute("ChainLayer",0);


	//input attribute

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	

	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//2001.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial2002()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");
	//mode
	TiXmlElement* mode = new TiXmlElement("mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");
	TiXmlElement* mode2  = new TiXmlElement("mode2");
	TiXmlElement* mode3  = new TiXmlElement("mode3");
	TiXmlElement* mode4  = new TiXmlElement("mode4");
	TiXmlElement* mode5  = new TiXmlElement("mode5");
	TiXmlElement* mode6  = new TiXmlElement("mode6");
	TiXmlElement* mode7  = new TiXmlElement("mode7");
	TiXmlElement* mode8  = new TiXmlElement("mode8");
	TiXmlElement* mode9  = new TiXmlElement("mode9");
	TiXmlElement* mode10 = new TiXmlElement("mode10");
	TiXmlElement* mode11 = new TiXmlElement("mode11");
	TiXmlElement* mode12 = new TiXmlElement("mode12");
	TiXmlElement* mode13 = new TiXmlElement("mode13");
	TiXmlElement* mode14 = new TiXmlElement("mode14");
	TiXmlElement* mode15 = new TiXmlElement("mode15");
	TiXmlElement* mode16 = new TiXmlElement("mode16");
	TiXmlElement* mode17 = new TiXmlElement("mode17");
	TiXmlElement* mode18 = new TiXmlElement("mode18");
	TiXmlElement* mode19 = new TiXmlElement("mode19");
	TiXmlElement* mode20 = new TiXmlElement("mode20");
	TiXmlElement* mode21 = new TiXmlElement("mode21");
	TiXmlElement* mode22 = new TiXmlElement("mode22");
	TiXmlElement* mode23 = new TiXmlElement("mode23");
	TiXmlElement* mode24 = new TiXmlElement("mode24");
	TiXmlElement* mode25 = new TiXmlElement("mode25");
	TiXmlElement* mode26 = new TiXmlElement("mode26");
	TiXmlElement* mode27 = new TiXmlElement("mode27");
	TiXmlElement* mode28 = new TiXmlElement("mode28");
	TiXmlElement* mode29 = new TiXmlElement("mode29");
	TiXmlElement* mode30 = new TiXmlElement("mode30");
	TiXmlElement* mode31 = new TiXmlElement("mode31");
	TiXmlElement* mode32 = new TiXmlElement("mode32");
	TiXmlElement* mode33 = new TiXmlElement("mode33");
	TiXmlElement* mode34 = new TiXmlElement("mode34");
	TiXmlElement* mode35 = new TiXmlElement("mode35");
	TiXmlElement* mode36 = new TiXmlElement("mode36");
	TiXmlElement* mode37 = new TiXmlElement("mode37");
	TiXmlElement* mode38 = new TiXmlElement("mode38");
	TiXmlElement* mode39 = new TiXmlElement("mode39");
	TiXmlElement* mode40 = new TiXmlElement("mode40");
	TiXmlElement* mode41 = new TiXmlElement("mode41");
	TiXmlElement* mode42 = new TiXmlElement("mode42");
	TiXmlElement* mode43 = new TiXmlElement("mode43");
	TiXmlElement* mode44 = new TiXmlElement("mode44");
	TiXmlElement* mode45 = new TiXmlElement("mode45");
	TiXmlElement* mode46 = new TiXmlElement("mode46");
	TiXmlElement* mode47 = new TiXmlElement("mode47");
	TiXmlElement* mode48 = new TiXmlElement("mode48");
	TiXmlElement* mode49 = new TiXmlElement("mode49");
	TiXmlElement* mode50 = new TiXmlElement("mode50");
	TiXmlElement* mode51 = new TiXmlElement("mode51");
	TiXmlElement* mode52 = new TiXmlElement("mode52");
	TiXmlElement* mode53 = new TiXmlElement("mode53");
	TiXmlElement* mode54 = new TiXmlElement("mode54");
	TiXmlElement* mode55 = new TiXmlElement("mode55");
	TiXmlElement* mode56 = new TiXmlElement("mode56");
	TiXmlElement* mode57 = new TiXmlElement("mode57");
	TiXmlElement* mode58 = new TiXmlElement("mode58");
	TiXmlElement* mode59 = new TiXmlElement("mode59");
	TiXmlElement* mode60 = new TiXmlElement("mode60");
	TiXmlElement* mode61 = new TiXmlElement("mode61");
	TiXmlElement* mode62 = new TiXmlElement("mode62");
	TiXmlElement* mode63 = new TiXmlElement("mode63");
	TiXmlElement* mode64 = new TiXmlElement("mode64");
	TiXmlElement* mode65 = new TiXmlElement("mode65");
	TiXmlElement* mode66 = new TiXmlElement("mode66");
	TiXmlElement* mode67 = new TiXmlElement("mode67");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");
	TiXmlElement* input2 = new TiXmlElement("input2");
	TiXmlElement* input3 = new TiXmlElement("input3");
	TiXmlElement* input4 = new TiXmlElement("input4");
	TiXmlElement* input5 = new TiXmlElement("input5");
	TiXmlElement* input6 = new TiXmlElement("input6");
	TiXmlElement* input7 = new TiXmlElement("input7");
	TiXmlElement* input8 = new TiXmlElement("input8");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",2002);
	module->SetAttribute("Mode",67);
	module->SetAttribute("WinSwitcherValue","");
	module->SetAttribute("WinSwitcherType",0);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","00001110");
	mode1->SetAttribute("WinSwitcherType",0);
	mode1->SetAttribute("WinSwitcherValue","");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2); 
	mode2->SetAttribute("include","00000010");
	mode2->SetAttribute("WinSwitcherType",0);
	mode2->SetAttribute("WinSwitcherValue","");
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3); 
	mode3->SetAttribute("include","00000110");
	mode3->SetAttribute("WinSwitcherType",2);
	mode3->SetAttribute("WinSwitcherValue","3");
	mode3->SetAttribute("ChainLayer",0);

	mode4->SetAttribute("id",4); 
	mode4->SetAttribute("include","01100010");
	mode4->SetAttribute("WinSwitcherType",2);
	mode4->SetAttribute("WinSwitcherValue","3");
	mode4->SetAttribute("ChainLayer",0);

	mode5->SetAttribute("id",5); 
	mode5->SetAttribute("include","01100010");
	mode5->SetAttribute("WinSwitcherType",2);
	mode5->SetAttribute("WinSwitcherValue","3");
	mode5->SetAttribute("ChainLayer",0);

	mode6->SetAttribute("id",6); 
	mode6->SetAttribute("include","00000010");
	mode6->SetAttribute("WinSwitcherType",2);
	mode6->SetAttribute("WinSwitcherValue","3");
	mode6->SetAttribute("ChainLayer",0);

	mode7->SetAttribute("id",7); 
	mode7->SetAttribute("include","00011010");
	mode7->SetAttribute("WinSwitcherType",2);
	mode7->SetAttribute("WinSwitcherValue","3");
	mode7->SetAttribute("ChainLayer",0);

	mode8->SetAttribute("id",8); 
	mode8->SetAttribute("include","00011010");
	mode8->SetAttribute("WinSwitcherType",2);
	mode8->SetAttribute("WinSwitcherValue","3");
	mode8->SetAttribute("ChainLayer",0);

	mode9->SetAttribute("id",9); 
	mode9->SetAttribute("include","01100010");
	mode9->SetAttribute("WinSwitcherType",2);
	mode9->SetAttribute("WinSwitcherValue","2");
	mode9->SetAttribute("ChainLayer",0);

	mode10->SetAttribute("id",10); 
	mode10->SetAttribute("include","01100010");
	mode10->SetAttribute("WinSwitcherType",2);
	mode10->SetAttribute("WinSwitcherValue","2");
	mode10->SetAttribute("ChainLayer",0);

	mode11->SetAttribute("id",11); 
	mode11->SetAttribute("include","00011010");
	mode11->SetAttribute("WinSwitcherType",2);
	mode11->SetAttribute("WinSwitcherValue","2");
	mode11->SetAttribute("ChainLayer",0);

	mode12->SetAttribute("id",12); 
	mode12->SetAttribute("include","00011010");
	mode12->SetAttribute("WinSwitcherType",2);
	mode12->SetAttribute("WinSwitcherValue","2");
	mode12->SetAttribute("ChainLayer",0);

	mode13->SetAttribute("id",13); 
	mode13->SetAttribute("include","01100010");
	mode13->SetAttribute("WinSwitcherType",2);
	mode13->SetAttribute("WinSwitcherValue","4");
	mode13->SetAttribute("ChainLayer",0);

	mode14->SetAttribute("id",14); 
	mode14->SetAttribute("include","01100110");
	mode14->SetAttribute("WinSwitcherType",2);
	mode14->SetAttribute("WinSwitcherValue","4");
	mode14->SetAttribute("ChainLayer",0);

	mode15->SetAttribute("id",15); 
	mode15->SetAttribute("include","01101010");
	mode15->SetAttribute("WinSwitcherType",2);
	mode15->SetAttribute("WinSwitcherValue","4");
	mode15->SetAttribute("ChainLayer",0);

	mode16->SetAttribute("id",16); 
	mode16->SetAttribute("include","00001110");
	mode16->SetAttribute("WinSwitcherType",2);
	mode16->SetAttribute("WinSwitcherValue","4");
	mode16->SetAttribute("ChainLayer",0);

	mode17->SetAttribute("id",17); 
	mode17->SetAttribute("include","01100010");
	mode17->SetAttribute("WinSwitcherType",2);
	mode17->SetAttribute("WinSwitcherValue","4");
	mode17->SetAttribute("ChainLayer",0);

	mode18->SetAttribute("id",18); 
	mode18->SetAttribute("include","01100110");
	mode18->SetAttribute("WinSwitcherType",2);
	mode18->SetAttribute("WinSwitcherValue","4");
	mode18->SetAttribute("ChainLayer",0);

	mode19->SetAttribute("id",19); 
	mode19->SetAttribute("include","01101010");
	mode19->SetAttribute("WinSwitcherType",2);
	mode19->SetAttribute("WinSwitcherValue","4");
	mode19->SetAttribute("ChainLayer",0);

	mode20->SetAttribute("id",20); 
	mode20->SetAttribute("include","00001110");
	mode20->SetAttribute("WinSwitcherType",2);
	mode20->SetAttribute("WinSwitcherValue","4");
	mode20->SetAttribute("ChainLayer",0);

	mode21->SetAttribute("id",21); 
	mode21->SetAttribute("include","01100010");
	mode21->SetAttribute("WinSwitcherType",2);
	mode21->SetAttribute("WinSwitcherValue","A");
	mode21->SetAttribute("ChainLayer",0);

	mode22->SetAttribute("id",22); 
	mode22->SetAttribute("include","01100010");
	mode22->SetAttribute("WinSwitcherType",2);
	mode22->SetAttribute("WinSwitcherValue","A");
	mode22->SetAttribute("ChainLayer",0);

	mode23->SetAttribute("id",23); 
	mode23->SetAttribute("include","01100010");
	mode23->SetAttribute("WinSwitcherType",2);
	mode23->SetAttribute("WinSwitcherValue","A");
	mode23->SetAttribute("ChainLayer",0);

	mode24->SetAttribute("id",24); 
	mode24->SetAttribute("include","01100010");
	mode24->SetAttribute("WinSwitcherType",2);
	mode24->SetAttribute("WinSwitcherValue","A");
	mode24->SetAttribute("ChainLayer",0);

	mode25->SetAttribute("id",25); 
	mode25->SetAttribute("include","01100010");
	mode25->SetAttribute("WinSwitcherType",2);
	mode25->SetAttribute("WinSwitcherValue","A");
	mode25->SetAttribute("ChainLayer",0);

	mode26->SetAttribute("id",26); 
	mode26->SetAttribute("include","01100010");
	mode26->SetAttribute("WinSwitcherType",2);
	mode26->SetAttribute("WinSwitcherValue","A");
	mode26->SetAttribute("ChainLayer",0);

	mode27->SetAttribute("id",27); 
	mode27->SetAttribute("include","01100010");
	mode27->SetAttribute("WinSwitcherType",2);
	mode27->SetAttribute("WinSwitcherValue","1");
	mode27->SetAttribute("ChainLayer",0);

	mode28->SetAttribute("id",28); 
	mode28->SetAttribute("include","01100010");
	mode28->SetAttribute("WinSwitcherType",2);
	mode28->SetAttribute("WinSwitcherValue","1");
	mode28->SetAttribute("ChainLayer",0);

	mode29->SetAttribute("id",29); 
	mode29->SetAttribute("include","01100010");
	mode29->SetAttribute("WinSwitcherType",2);
	mode29->SetAttribute("WinSwitcherValue","1");
	mode29->SetAttribute("ChainLayer",0);

	mode30->SetAttribute("id",30); 
	mode30->SetAttribute("include","01100010");
	mode30->SetAttribute("WinSwitcherType",2);
	mode30->SetAttribute("WinSwitcherValue","1");
	mode30->SetAttribute("ChainLayer",0);

	mode31->SetAttribute("id",31); 
	mode31->SetAttribute("include","01100110");
	mode31->SetAttribute("WinSwitcherType",0);
	mode31->SetAttribute("WinSwitcherValue","");
	mode31->SetAttribute("ChainLayer",0);

	mode32->SetAttribute("id",32); 
	mode32->SetAttribute("include","00001110");
	mode32->SetAttribute("WinSwitcherType",0);
	mode32->SetAttribute("WinSwitcherValue","");
	mode32->SetAttribute("ChainLayer",0);

	mode33->SetAttribute("id",33); 
	mode33->SetAttribute("include","00001001");
	mode33->SetAttribute("WinSwitcherType",2);
	mode33->SetAttribute("WinSwitcherValue","1");
	mode33->SetAttribute("ChainLayer",0);

	mode34->SetAttribute("id",34); 
	mode34->SetAttribute("include","00000001");
	mode34->SetAttribute("WinSwitcherType",2);
	mode34->SetAttribute("WinSwitcherValue","1");
	mode34->SetAttribute("ChainLayer",0);

	mode35->SetAttribute("id",35); 
	mode35->SetAttribute("include","01100010");
	mode35->SetAttribute("WinSwitcherType",2);
	mode35->SetAttribute("WinSwitcherValue","4");
	mode35->SetAttribute("ChainLayer",0);

	mode36->SetAttribute("id",36); 
	mode36->SetAttribute("include","01100010");
	mode36->SetAttribute("WinSwitcherType",2);
	mode36->SetAttribute("WinSwitcherValue","4");
	mode36->SetAttribute("ChainLayer",0);

	mode37->SetAttribute("id",37); 
	mode37->SetAttribute("include","01100010");
	mode37->SetAttribute("WinSwitcherType",2);
	mode37->SetAttribute("WinSwitcherValue","A");
	mode37->SetAttribute("ChainLayer",0);

	mode38->SetAttribute("id",38); 
	mode38->SetAttribute("include","00000000");
	mode38->SetAttribute("WinSwitcherType",2);
	mode38->SetAttribute("WinSwitcherValue","4");
	mode38->SetAttribute("ChainLayer",0);

	mode39->SetAttribute("id",39); 
	mode39->SetAttribute("include","00011010");
	mode39->SetAttribute("WinSwitcherType",2);
	mode39->SetAttribute("WinSwitcherValue","4");
	mode39->SetAttribute("ChainLayer",0);

	mode40->SetAttribute("id",40); 
	mode40->SetAttribute("include","00011010");
	mode40->SetAttribute("WinSwitcherType",2);
	mode40->SetAttribute("WinSwitcherValue","4");
	mode40->SetAttribute("ChainLayer",0);

	mode41->SetAttribute("id",41); 
	mode41->SetAttribute("include","01100001");
	mode41->SetAttribute("WinSwitcherType",2);
	mode41->SetAttribute("WinSwitcherValue","3");
	mode41->SetAttribute("ChainLayer",0);

	mode42->SetAttribute("id",42); 
	mode42->SetAttribute("include","01100001");
	mode42->SetAttribute("WinSwitcherType",2);
	mode42->SetAttribute("WinSwitcherValue","3");
	mode42->SetAttribute("ChainLayer",0);

	mode43->SetAttribute("id",43); 
	mode43->SetAttribute("include","01100001");
	mode43->SetAttribute("WinSwitcherType",2);
	mode43->SetAttribute("WinSwitcherValue","3");
	mode43->SetAttribute("ChainLayer",0);

	mode44->SetAttribute("id",44); 
	mode44->SetAttribute("include","01100001");
	mode44->SetAttribute("WinSwitcherType",2);
	mode44->SetAttribute("WinSwitcherValue","3");
	mode44->SetAttribute("ChainLayer",0);

	mode45->SetAttribute("id",45); 
	mode45->SetAttribute("include","01100001");
	mode45->SetAttribute("WinSwitcherType",2);
	mode45->SetAttribute("WinSwitcherValue","3");
	mode45->SetAttribute("ChainLayer",0);

	mode46->SetAttribute("id",46); 
	mode46->SetAttribute("include","01100001");
	mode46->SetAttribute("WinSwitcherType",2);
	mode46->SetAttribute("WinSwitcherValue","3");
	mode46->SetAttribute("ChainLayer",0);

	mode47->SetAttribute("id",47); 
	mode47->SetAttribute("include","00011001");
	mode47->SetAttribute("WinSwitcherType",2);
	mode47->SetAttribute("WinSwitcherValue","3");
	mode47->SetAttribute("ChainLayer",0);

	mode48->SetAttribute("id",48); 
	mode48->SetAttribute("include","00011001");
	mode48->SetAttribute("WinSwitcherType",2);
	mode48->SetAttribute("WinSwitcherValue","3");
	mode48->SetAttribute("ChainLayer",0);

	mode49->SetAttribute("id",49); 
	mode49->SetAttribute("include","00011001");
	mode49->SetAttribute("WinSwitcherType",2);
	mode49->SetAttribute("WinSwitcherValue","3");
	mode49->SetAttribute("ChainLayer",0);

	mode50->SetAttribute("id",50); 
	mode50->SetAttribute("include","00011001");
	mode50->SetAttribute("WinSwitcherType",2);
	mode50->SetAttribute("WinSwitcherValue","3");
	mode50->SetAttribute("ChainLayer",0);

	mode51->SetAttribute("id",51); 
	mode51->SetAttribute("include","00011001");
	mode51->SetAttribute("WinSwitcherType",2);
	mode51->SetAttribute("WinSwitcherValue","3");
	mode51->SetAttribute("ChainLayer",0);

	mode52->SetAttribute("id",52); 
	mode52->SetAttribute("include","00011001");
	mode52->SetAttribute("WinSwitcherType",2);
	mode52->SetAttribute("WinSwitcherValue","3");
	mode52->SetAttribute("ChainLayer",0);

	mode53->SetAttribute("id",53); 
	mode53->SetAttribute("include","00011001");
	mode53->SetAttribute("WinSwitcherType",2);
	mode53->SetAttribute("WinSwitcherValue","3");
	mode53->SetAttribute("ChainLayer",0);

	mode54->SetAttribute("id",54); 
	mode54->SetAttribute("include","01100010");
	mode54->SetAttribute("WinSwitcherType",2);
	mode54->SetAttribute("WinSwitcherValue","2");
	mode54->SetAttribute("ChainLayer",0);

	mode55->SetAttribute("id",55); 
	mode55->SetAttribute("include","01100010");
	mode55->SetAttribute("WinSwitcherType",2);
	mode55->SetAttribute("WinSwitcherValue","2");
	mode55->SetAttribute("ChainLayer",0);

	mode56->SetAttribute("id",56); 
	mode56->SetAttribute("include","00011010");
	mode56->SetAttribute("WinSwitcherType",2);
	mode56->SetAttribute("WinSwitcherValue","2");
	mode56->SetAttribute("ChainLayer",0);

	mode57->SetAttribute("id",57); 
	mode57->SetAttribute("include","00011010");
	mode57->SetAttribute("WinSwitcherType",2);
	mode57->SetAttribute("WinSwitcherValue","2");
	mode57->SetAttribute("ChainLayer",0);

	mode58->SetAttribute("id",58); 
	mode58->SetAttribute("include","01000110");
	mode58->SetAttribute("WinSwitcherType",4);
	mode58->SetAttribute("WinSwitcherValue","abc");
	mode58->SetAttribute("ChainLayer",0);

	mode59->SetAttribute("id",59); 
	mode59->SetAttribute("include","01100010");
	mode59->SetAttribute("WinSwitcherType",4);
	mode59->SetAttribute("WinSwitcherValue","abc");
	mode59->SetAttribute("ChainLayer",0);

	mode60->SetAttribute("id",60); 
	mode60->SetAttribute("include","00000010");
	mode60->SetAttribute("WinSwitcherType",4);
	mode60->SetAttribute("WinSwitcherValue","abc");
	mode60->SetAttribute("ChainLayer",0);

	mode61->SetAttribute("id",61); 
	mode61->SetAttribute("include","00000010");
	mode61->SetAttribute("WinSwitcherType",4);
	mode61->SetAttribute("WinSwitcherValue","abc");
	mode61->SetAttribute("ChainLayer",0);

	mode62->SetAttribute("id",62); 
	mode62->SetAttribute("include","00000010");
	mode62->SetAttribute("WinSwitcherType",4);
	mode62->SetAttribute("WinSwitcherValue","abc");
	mode62->SetAttribute("ChainLayer",0);

	mode63->SetAttribute("id",63); 
	mode63->SetAttribute("include","00000010");
	mode63->SetAttribute("WinSwitcherType",4);
	mode63->SetAttribute("WinSwitcherValue","abc");
	mode63->SetAttribute("ChainLayer",0);

	mode64->SetAttribute("id",64); 
	mode64->SetAttribute("include","00000010");
	mode64->SetAttribute("WinSwitcherType",4);
	mode64->SetAttribute("WinSwitcherValue","abc");
	mode64->SetAttribute("ChainLayer",0);

	mode65->SetAttribute("id",65); 
	mode65->SetAttribute("include","00011010");
	mode65->SetAttribute("WinSwitcherType",4);
	mode65->SetAttribute("WinSwitcherValue","abc");
	mode65->SetAttribute("ChainLayer",0);

	mode66->SetAttribute("id",66); 
	mode66->SetAttribute("include","00000010");
	mode66->SetAttribute("WinSwitcherType",4);
	mode66->SetAttribute("WinSwitcherValue","abc");
	mode66->SetAttribute("ChainLayer",0);

	mode67->SetAttribute("id",67); 
	mode67->SetAttribute("include","10000000");
	mode67->SetAttribute("WinSwitcherType",0);
	mode67->SetAttribute("WinSwitcherValue","");
	mode67->SetAttribute("ChainLayer",0);
	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","1");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",MAX_INT);
	input1->SetAttribute("min",MIN_INT);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","1");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",5);
	input2->SetAttribute("min",0);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default","1");
	input3->SetAttribute("type","PARA_NUM");
	input3->SetAttribute("max",MAX_INT);
	input3->SetAttribute("min",MIN_INT);
	input3->SetAttribute("InOrOut","PARA_IN");
	input3->SetAttribute("IsPort",0);

	input4->SetAttribute("id",4);
	input4->SetAttribute("default","1");
	input4->SetAttribute("type","PARA_NUM");
	input4->SetAttribute("max",2);
	input4->SetAttribute("min",0);
	input4->SetAttribute("InOrOut","PARA_IN");
	input4->SetAttribute("IsPort",0);

	input5->SetAttribute("id",5);
	input5->SetAttribute("default","1");
	input5->SetAttribute("type","PARA_NUM");
	input5->SetAttribute("max",MAX_INT);
	input5->SetAttribute("min",MIN_INT);
	input5->SetAttribute("InOrOut","PARA_IN");
	input5->SetAttribute("IsPort",0);

	input6->SetAttribute("id",6);
	input6->SetAttribute("default","1");
	input6->SetAttribute("type","PARA_TEXT");
	input6->SetAttribute("max",0);
	input6->SetAttribute("min",0);
	input6->SetAttribute("InOrOut","PARA_IN");
	input6->SetAttribute("IsPort",0);

	input7->SetAttribute("id",7);
	input7->SetAttribute("default","1");
	input7->SetAttribute("type","PARA_TEXT");
	input7->SetAttribute("max",0);
	input7->SetAttribute("min",0);
	input7->SetAttribute("InOrOut","PARA_OUT");
	input7->SetAttribute("IsPort",0);

	input8->SetAttribute("id",8);
	input8->SetAttribute("default","1");
	input8->SetAttribute("type","PARA_NUM");
	input8->SetAttribute("max",MAX_INT);
	input8->SetAttribute("min",MIN_INT);
	input8->SetAttribute("InOrOut","PARA_OUT");
	input8->SetAttribute("IsPort",0);


    //***************link all the element*************
	doc.LinkEndChild(module);
	//link mode and inputlist
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	//link all mode
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);
	mode->LinkEndChild(mode4);
	mode->LinkEndChild(mode5);
	mode->LinkEndChild(mode6);
	mode->LinkEndChild(mode7);
	mode->LinkEndChild(mode8);
	mode->LinkEndChild(mode9);
	mode->LinkEndChild(mode10);
	mode->LinkEndChild(mode11);
	mode->LinkEndChild(mode12);
	mode->LinkEndChild(mode13);
	mode->LinkEndChild(mode14);
	mode->LinkEndChild(mode15);
	mode->LinkEndChild(mode16);
	mode->LinkEndChild(mode17);
	mode->LinkEndChild(mode18);
	mode->LinkEndChild(mode19);
	mode->LinkEndChild(mode20);
	mode->LinkEndChild(mode21);
	mode->LinkEndChild(mode22);
	mode->LinkEndChild(mode23);
	mode->LinkEndChild(mode24);
	mode->LinkEndChild(mode25);
	mode->LinkEndChild(mode26);
	mode->LinkEndChild(mode27);
	mode->LinkEndChild(mode28);
	mode->LinkEndChild(mode29);
	mode->LinkEndChild(mode30);
	mode->LinkEndChild(mode31);
	mode->LinkEndChild(mode32);
	mode->LinkEndChild(mode33);
	mode->LinkEndChild(mode34);
	mode->LinkEndChild(mode35);
	mode->LinkEndChild(mode36);
	mode->LinkEndChild(mode37);
	mode->LinkEndChild(mode38);
	mode->LinkEndChild(mode39);
	mode->LinkEndChild(mode40);
	mode->LinkEndChild(mode41);
	mode->LinkEndChild(mode42);
	mode->LinkEndChild(mode43);
	mode->LinkEndChild(mode44);
	mode->LinkEndChild(mode45);
	mode->LinkEndChild(mode46);
	mode->LinkEndChild(mode47);
	mode->LinkEndChild(mode48);
	mode->LinkEndChild(mode49);
	mode->LinkEndChild(mode50);
	mode->LinkEndChild(mode51);
	mode->LinkEndChild(mode52);
	mode->LinkEndChild(mode53);
	mode->LinkEndChild(mode54);
	mode->LinkEndChild(mode55);
	mode->LinkEndChild(mode56);
	mode->LinkEndChild(mode57);
	mode->LinkEndChild(mode58);
	mode->LinkEndChild(mode59);
	mode->LinkEndChild(mode60);
	mode->LinkEndChild(mode61);
	mode->LinkEndChild(mode62);
	mode->LinkEndChild(mode63);
	mode->LinkEndChild(mode64);
	mode->LinkEndChild(mode65);
	mode->LinkEndChild(mode66);
	mode->LinkEndChild(mode67);
	//link input list				   
	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);
	inputList->LinkEndChild(input5);
	inputList->LinkEndChild(input6);
	inputList->LinkEndChild(input7);
	inputList->LinkEndChild(input8);

	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//2002.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial2003()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");
	//mode
	TiXmlElement* mode = new TiXmlElement("mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");
	TiXmlElement* mode2  = new TiXmlElement("mode2");
	TiXmlElement* mode3  = new TiXmlElement("mode3");
	TiXmlElement* mode4  = new TiXmlElement("mode4");
	TiXmlElement* mode5  = new TiXmlElement("mode5");
	TiXmlElement* mode6  = new TiXmlElement("mode6");
	TiXmlElement* mode7  = new TiXmlElement("mode7");
	TiXmlElement* mode8  = new TiXmlElement("mode8");
	TiXmlElement* mode9  = new TiXmlElement("mode9");
	TiXmlElement* mode10 = new TiXmlElement("mode10");
	TiXmlElement* mode11 = new TiXmlElement("mode11");
	TiXmlElement* mode12 = new TiXmlElement("mode12");
	TiXmlElement* mode13 = new TiXmlElement("mode13");
	TiXmlElement* mode14 = new TiXmlElement("mode14");
	TiXmlElement* mode15 = new TiXmlElement("mode15");
	TiXmlElement* mode16 = new TiXmlElement("mode16");
	TiXmlElement* mode17 = new TiXmlElement("mode17");
	TiXmlElement* mode18 = new TiXmlElement("mode18");
	TiXmlElement* mode19 = new TiXmlElement("mode19");
	TiXmlElement* mode20 = new TiXmlElement("mode20");
	TiXmlElement* mode21 = new TiXmlElement("mode21");
	TiXmlElement* mode22 = new TiXmlElement("mode22");
	TiXmlElement* mode23 = new TiXmlElement("mode23");
	TiXmlElement* mode24 = new TiXmlElement("mode24");
	TiXmlElement* mode25 = new TiXmlElement("mode25");
	TiXmlElement* mode26 = new TiXmlElement("mode26");
	TiXmlElement* mode27 = new TiXmlElement("mode27");
	TiXmlElement* mode28 = new TiXmlElement("mode28");
	TiXmlElement* mode29 = new TiXmlElement("mode29");
	TiXmlElement* mode30 = new TiXmlElement("mode30");
	TiXmlElement* mode31 = new TiXmlElement("mode31");
	TiXmlElement* mode32 = new TiXmlElement("mode32");
	TiXmlElement* mode33 = new TiXmlElement("mode33");
	TiXmlElement* mode34 = new TiXmlElement("mode34");
	TiXmlElement* mode35 = new TiXmlElement("mode35");
	TiXmlElement* mode36 = new TiXmlElement("mode36");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");
	TiXmlElement* input2 = new TiXmlElement("input2");
	TiXmlElement* input3 = new TiXmlElement("input3");
	TiXmlElement* input4 = new TiXmlElement("input4");
	TiXmlElement* input5 = new TiXmlElement("input5");
	TiXmlElement* input6 = new TiXmlElement("input6");
	TiXmlElement* input7 = new TiXmlElement("input7");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",2003);
	module->SetAttribute("Mode",34);
	module->SetAttribute("WinSwitcherValue","");
	module->SetAttribute("WinSwitcherType",0);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","0000110");
	mode1->SetAttribute("WinSwitcherType",0);
	mode1->SetAttribute("WinSwitcherValue","");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2); 
	mode2->SetAttribute("include","0000010");
	mode2->SetAttribute("WinSwitcherType",0);
	mode2->SetAttribute("WinSwitcherValue","");
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3); 
	mode3->SetAttribute("include","0001100");
	mode3->SetAttribute("WinSwitcherType",2);
	mode3->SetAttribute("WinSwitcherValue","3");
	mode3->SetAttribute("ChainLayer",0);

	mode4->SetAttribute("id",4); 
	mode4->SetAttribute("include","0001100");
	mode4->SetAttribute("WinSwitcherType",2);
	mode4->SetAttribute("WinSwitcherValue","3");
	mode4->SetAttribute("ChainLayer",0);

	mode5->SetAttribute("id",5); 
	mode5->SetAttribute("include","0001100");
	mode5->SetAttribute("WinSwitcherType",2);
	mode5->SetAttribute("WinSwitcherValue","3");
	mode5->SetAttribute("ChainLayer",0);

	mode6->SetAttribute("id",6); 
	mode6->SetAttribute("include","0001100");
	mode6->SetAttribute("WinSwitcherType",2);
	mode6->SetAttribute("WinSwitcherValue","3");
	mode6->SetAttribute("ChainLayer",0);

	mode7->SetAttribute("id",7); 
	mode7->SetAttribute("include","0001100");
	mode7->SetAttribute("WinSwitcherType",2);
	mode7->SetAttribute("WinSwitcherValue","3");
	mode7->SetAttribute("ChainLayer",0);

	mode8->SetAttribute("id",8); 
	mode8->SetAttribute("include","0001110");
	mode8->SetAttribute("WinSwitcherType",2);
	mode8->SetAttribute("WinSwitcherValue","4");
	mode8->SetAttribute("ChainLayer",0);

	mode9->SetAttribute("id",9); 
	mode9->SetAttribute("include","0001110");
	mode9->SetAttribute("WinSwitcherType",2);
	mode9->SetAttribute("WinSwitcherValue","4");
	mode9->SetAttribute("ChainLayer",0);

	mode10->SetAttribute("id",10); 
	mode10->SetAttribute("include","0000110");
	mode10->SetAttribute("WinSwitcherType",2);
	mode10->SetAttribute("WinSwitcherValue","4");
	mode10->SetAttribute("ChainLayer",0);

	mode11->SetAttribute("id",11); 
	mode11->SetAttribute("include","0001100");
	mode11->SetAttribute("WinSwitcherType",2);
	mode11->SetAttribute("WinSwitcherValue","A");
	mode11->SetAttribute("ChainLayer",0);

	mode12->SetAttribute("id",12); 
	mode12->SetAttribute("include","0001100");
	mode12->SetAttribute("WinSwitcherType",2);
	mode12->SetAttribute("WinSwitcherValue","A");
	mode12->SetAttribute("ChainLayer",0);

	mode13->SetAttribute("id",13); 
	mode13->SetAttribute("include","0001100");
	mode13->SetAttribute("WinSwitcherType",2);
	mode13->SetAttribute("WinSwitcherValue","A");
	mode13->SetAttribute("ChainLayer",0);

	mode14->SetAttribute("id",14); 
	mode14->SetAttribute("include","0001100");
	mode14->SetAttribute("WinSwitcherType",2);
	mode14->SetAttribute("WinSwitcherValue","1");
	mode14->SetAttribute("ChainLayer",0);

	mode15->SetAttribute("id",15); 
	mode15->SetAttribute("include","0001100");
	mode15->SetAttribute("WinSwitcherType",2);
	mode15->SetAttribute("WinSwitcherValue","1");
	mode15->SetAttribute("ChainLayer",0);

	mode16->SetAttribute("id",16); 
	mode16->SetAttribute("include","0001110");
	mode16->SetAttribute("WinSwitcherType",0);
	mode16->SetAttribute("WinSwitcherValue","");
	mode16->SetAttribute("ChainLayer",0);

	mode17->SetAttribute("id",17); 
	mode17->SetAttribute("include","0000100");
	mode17->SetAttribute("WinSwitcherType",2);
	mode17->SetAttribute("WinSwitcherValue","1");
	mode17->SetAttribute("ChainLayer",0);

	mode18->SetAttribute("id",18); 
	mode18->SetAttribute("include","0001100");
	mode18->SetAttribute("WinSwitcherType",2);
	mode18->SetAttribute("WinSwitcherValue","4");
	mode18->SetAttribute("ChainLayer",0);

	mode19->SetAttribute("id",19); 
	mode19->SetAttribute("include","0001100");
	mode19->SetAttribute("WinSwitcherType",2);
	mode19->SetAttribute("WinSwitcherValue","4");
	mode19->SetAttribute("ChainLayer",0);

	mode20->SetAttribute("id",20); 
	mode20->SetAttribute("include","0000000");
	mode20->SetAttribute("WinSwitcherType",2);
	mode20->SetAttribute("WinSwitcherValue","4");
	mode20->SetAttribute("ChainLayer",0);

	mode21->SetAttribute("id",21); 
	mode21->SetAttribute("include","0001100");
	mode21->SetAttribute("WinSwitcherType",2);
	mode21->SetAttribute("WinSwitcherValue","3");
	mode21->SetAttribute("ChainLayer",0);

	mode22->SetAttribute("id",22); 
	mode22->SetAttribute("include","0001100");
	mode22->SetAttribute("WinSwitcherType",2);
	mode22->SetAttribute("WinSwitcherValue","3");
	mode22->SetAttribute("ChainLayer",0);

	mode23->SetAttribute("id",23); 
	mode23->SetAttribute("include","0001100");
	mode23->SetAttribute("WinSwitcherType",2);
	mode23->SetAttribute("WinSwitcherValue","3");
	mode23->SetAttribute("ChainLayer",0);

	mode24->SetAttribute("id",24); 
	mode24->SetAttribute("include","0001100");
	mode24->SetAttribute("WinSwitcherType",2);
	mode24->SetAttribute("WinSwitcherValue","3");
	mode24->SetAttribute("ChainLayer",0);

	mode25->SetAttribute("id",25); 
	mode25->SetAttribute("include","0001100");
	mode25->SetAttribute("WinSwitcherType",2);
	mode25->SetAttribute("WinSwitcherValue","3");
	mode25->SetAttribute("ChainLayer",0);

	mode26->SetAttribute("id",26); 
	mode26->SetAttribute("include","0001100");
	mode26->SetAttribute("WinSwitcherType",2);
	mode26->SetAttribute("WinSwitcherValue","3");
	mode26->SetAttribute("ChainLayer",0);

	mode27->SetAttribute("id",27); 
	mode27->SetAttribute("include","0001100");
	mode27->SetAttribute("WinSwitcherType",2);
	mode27->SetAttribute("WinSwitcherValue","3");
	mode27->SetAttribute("ChainLayer",0);

	mode28->SetAttribute("id",28); 
	mode28->SetAttribute("include","0001100");
	mode28->SetAttribute("WinSwitcherType",2);
	mode28->SetAttribute("WinSwitcherValue","2");
	mode28->SetAttribute("ChainLayer",0);

	mode29->SetAttribute("id",29); 
	mode29->SetAttribute("include","0001100");
	mode29->SetAttribute("WinSwitcherType",2);
	mode29->SetAttribute("WinSwitcherValue","2");
	mode29->SetAttribute("ChainLayer",0);

	mode30->SetAttribute("id",30); 
	mode30->SetAttribute("include","0001010");
	mode30->SetAttribute("WinSwitcherType",5);
	mode30->SetAttribute("WinSwitcherValue","abc");
	mode30->SetAttribute("ChainLayer",0);

	mode31->SetAttribute("id",31); 
	mode31->SetAttribute("include","0001100");
	mode31->SetAttribute("WinSwitcherType",5);
	mode31->SetAttribute("WinSwitcherValue","abc");
	mode31->SetAttribute("ChainLayer",0);

	mode32->SetAttribute("id",32); 
	mode32->SetAttribute("include","0000000");
	mode32->SetAttribute("WinSwitcherType",5);
	mode32->SetAttribute("WinSwitcherValue","abc");
	mode32->SetAttribute("ChainLayer",0);

	mode33->SetAttribute("id",33); 
	mode33->SetAttribute("include","0000000");
	mode33->SetAttribute("WinSwitcherType",0);
	mode33->SetAttribute("WinSwitcherValue","");
	mode33->SetAttribute("ChainLayer",0);

	mode34->SetAttribute("id",34); 
	mode34->SetAttribute("include","1000000");
	mode34->SetAttribute("WinSwitcherType",0);
	mode34->SetAttribute("WinSwitcherValue","");
	mode34->SetAttribute("ChainLayer",0);

	mode35->SetAttribute("id",35); 
	mode35->SetAttribute("include","0010000");
	mode35->SetAttribute("WinSwitcherType",0);
	mode35->SetAttribute("WinSwitcherValue","");
	mode35->SetAttribute("ChainLayer",0);

	mode36->SetAttribute("id",36); 
	mode36->SetAttribute("include","0100000");
	mode36->SetAttribute("WinSwitcherType",0);
	mode36->SetAttribute("WinSwitcherValue","");
	mode36->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","1");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",MAX_INT);
	input1->SetAttribute("min",MIN_INT);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","1");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",MAX_INT);
	input2->SetAttribute("min",MIN_INT);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default","1");
	input3->SetAttribute("type","PARA_LOGIC");
	input3->SetAttribute("max",1);
	input3->SetAttribute("min",0);
	input3->SetAttribute("InOrOut","PARA_IN");
	input3->SetAttribute("IsPort",0);

	input4->SetAttribute("id",4);
	input4->SetAttribute("default","1");
	input4->SetAttribute("type","PARA_NUM");
	input4->SetAttribute("max",5);
	input4->SetAttribute("min",0);
	input4->SetAttribute("InOrOut","PARA_IN");
	input4->SetAttribute("IsPort",0);

	input5->SetAttribute("id",5);
	input5->SetAttribute("default","1");
	input5->SetAttribute("type","PARA_NUM");
	input5->SetAttribute("max",MAX_INT);
	input5->SetAttribute("min",MIN_INT);
	input5->SetAttribute("InOrOut","PARA_IN");
	input5->SetAttribute("IsPort",0);

	input6->SetAttribute("id",6);
	input6->SetAttribute("default","");
	input6->SetAttribute("type","PARA_TEXT");
	input6->SetAttribute("max",0);
	input6->SetAttribute("min",0);
	input6->SetAttribute("InOrOut","PARA_IN");
	input6->SetAttribute("IsPort",0);

	input7->SetAttribute("id",7);
	input7->SetAttribute("default","0");
	input7->SetAttribute("type","PARA_NUM");
	input7->SetAttribute("max",MAX_INT);
	input7->SetAttribute("min",MIN_INT);
	input7->SetAttribute("InOrOut","PARA_OUT");
	input7->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	//link mode and inputlist
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	//link all mode
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);
	mode->LinkEndChild(mode4);
	mode->LinkEndChild(mode5);
	mode->LinkEndChild(mode6);
	mode->LinkEndChild(mode7);
	mode->LinkEndChild(mode8);
	mode->LinkEndChild(mode9);
	mode->LinkEndChild(mode10);
	mode->LinkEndChild(mode11);
	mode->LinkEndChild(mode12);
	mode->LinkEndChild(mode13);
	mode->LinkEndChild(mode14);
	mode->LinkEndChild(mode15);
	mode->LinkEndChild(mode16);
	mode->LinkEndChild(mode17);
	mode->LinkEndChild(mode18);
	mode->LinkEndChild(mode19);
	mode->LinkEndChild(mode20);
	mode->LinkEndChild(mode21);
	mode->LinkEndChild(mode22);
	mode->LinkEndChild(mode23);
	mode->LinkEndChild(mode24);
	mode->LinkEndChild(mode25);
	mode->LinkEndChild(mode26);
	mode->LinkEndChild(mode27);
	mode->LinkEndChild(mode28);
	mode->LinkEndChild(mode29);
	mode->LinkEndChild(mode30);
	mode->LinkEndChild(mode31);
	mode->LinkEndChild(mode32);
	mode->LinkEndChild(mode33);
	mode->LinkEndChild(mode34);
	mode->LinkEndChild(mode35);
	mode->LinkEndChild(mode36);
	
	//link input list				   
	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);
	inputList->LinkEndChild(input5);
	inputList->LinkEndChild(input6);
	inputList->LinkEndChild(input7);

	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//2003.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial2004()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");
	//mode
	TiXmlElement* mode = new TiXmlElement("mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");
	TiXmlElement* mode2  = new TiXmlElement("mode2");
	TiXmlElement* mode3  = new TiXmlElement("mode3");
	TiXmlElement* mode4  = new TiXmlElement("mode4");
	TiXmlElement* mode5  = new TiXmlElement("mode5");
	TiXmlElement* mode6  = new TiXmlElement("mode6");
	TiXmlElement* mode7  = new TiXmlElement("mode7");
	TiXmlElement* mode8  = new TiXmlElement("mode8");
	TiXmlElement* mode9  = new TiXmlElement("mode9");
	TiXmlElement* mode10 = new TiXmlElement("mode10");
	TiXmlElement* mode11 = new TiXmlElement("mode11");
	TiXmlElement* mode12 = new TiXmlElement("mode12");
	TiXmlElement* mode13 = new TiXmlElement("mode13");
	TiXmlElement* mode14 = new TiXmlElement("mode14");
	TiXmlElement* mode15 = new TiXmlElement("mode15");
	TiXmlElement* mode16 = new TiXmlElement("mode16");
	TiXmlElement* mode17 = new TiXmlElement("mode17");
	TiXmlElement* mode18 = new TiXmlElement("mode18");
	TiXmlElement* mode19 = new TiXmlElement("mode19");
	TiXmlElement* mode20 = new TiXmlElement("mode20");
	TiXmlElement* mode21 = new TiXmlElement("mode21");
	TiXmlElement* mode22 = new TiXmlElement("mode22");
	TiXmlElement* mode23 = new TiXmlElement("mode23");
	TiXmlElement* mode24 = new TiXmlElement("mode24");
	TiXmlElement* mode25 = new TiXmlElement("mode25");
	TiXmlElement* mode26 = new TiXmlElement("mode26");
	TiXmlElement* mode27 = new TiXmlElement("mode27");
	TiXmlElement* mode28 = new TiXmlElement("mode28");
	TiXmlElement* mode29 = new TiXmlElement("mode29");
	TiXmlElement* mode30 = new TiXmlElement("mode30");
	TiXmlElement* mode31 = new TiXmlElement("mode31");
	TiXmlElement* mode32 = new TiXmlElement("mode32");
	TiXmlElement* mode33 = new TiXmlElement("mode33");
	TiXmlElement* mode34 = new TiXmlElement("mode34");
	TiXmlElement* mode35 = new TiXmlElement("mode35");
	TiXmlElement* mode36 = new TiXmlElement("mode36");
	TiXmlElement* mode37 = new TiXmlElement("mode37");
	TiXmlElement* mode38 = new TiXmlElement("mode38");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");
	TiXmlElement* input2 = new TiXmlElement("input2");
	TiXmlElement* input3 = new TiXmlElement("input3");
	TiXmlElement* input4 = new TiXmlElement("input4");
	TiXmlElement* input5 = new TiXmlElement("input5");
	TiXmlElement* input6 = new TiXmlElement("input6");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",2004);
	module->SetAttribute("Mode",20);
	module->SetAttribute("WinSwitcherValue","1");
	module->SetAttribute("WinSwitcherType",2);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","000000");
	mode1->SetAttribute("WinSwitcherType",0);
	mode1->SetAttribute("WinSwitcherValue","");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2); 
	mode2->SetAttribute("include","000011");
	mode2->SetAttribute("WinSwitcherType",0);
	mode2->SetAttribute("WinSwitcherValue","");
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3); 
	mode3->SetAttribute("include","000000");
	mode3->SetAttribute("WinSwitcherType",2);
	mode3->SetAttribute("WinSwitcherValue","3");
	mode3->SetAttribute("ChainLayer",0);

	mode4->SetAttribute("id",4); 
	mode4->SetAttribute("include","000001");
	mode4->SetAttribute("WinSwitcherType",2);
	mode4->SetAttribute("WinSwitcherValue","3");
	mode4->SetAttribute("ChainLayer",0);

	mode5->SetAttribute("id",5); 
	mode5->SetAttribute("include","000110");
	mode5->SetAttribute("WinSwitcherType",2);
	mode5->SetAttribute("WinSwitcherValue","3");
	mode5->SetAttribute("ChainLayer",0);

	mode6->SetAttribute("id",6); 
	mode6->SetAttribute("include","000110");
	mode6->SetAttribute("WinSwitcherType",2);
	mode6->SetAttribute("WinSwitcherValue","3");
	mode6->SetAttribute("ChainLayer",0);

	mode7->SetAttribute("id",7); 
	mode7->SetAttribute("include","000110");
	mode7->SetAttribute("WinSwitcherType",2);
	mode7->SetAttribute("WinSwitcherValue","2");
	mode7->SetAttribute("ChainLayer",0);

	mode8->SetAttribute("id",8); 
	mode8->SetAttribute("include","000110");
	mode8->SetAttribute("WinSwitcherType",2);
	mode8->SetAttribute("WinSwitcherValue","2");
	mode8->SetAttribute("ChainLayer",0);

	mode9->SetAttribute("id",9); 
	mode9->SetAttribute("include","000010");
	mode9->SetAttribute("WinSwitcherType",2);
	mode9->SetAttribute("WinSwitcherValue","4");
	mode9->SetAttribute("ChainLayer",0);

	mode10->SetAttribute("id",10); 
	mode10->SetAttribute("include","000110");
	mode10->SetAttribute("WinSwitcherType",2);
	mode10->SetAttribute("WinSwitcherValue","4");
	mode10->SetAttribute("ChainLayer",0);

	mode11->SetAttribute("id",11); 
	mode11->SetAttribute("include","000111");
	mode11->SetAttribute("WinSwitcherType",2);
	mode11->SetAttribute("WinSwitcherValue","4");
	mode11->SetAttribute("ChainLayer",0);

	mode12->SetAttribute("id",12); 
	mode12->SetAttribute("include","000111");
	mode12->SetAttribute("WinSwitcherType",2);
	mode12->SetAttribute("WinSwitcherValue","4");
	mode12->SetAttribute("ChainLayer",0);

	mode13->SetAttribute("id",13); 
	mode13->SetAttribute("include","000011");
	mode13->SetAttribute("WinSwitcherType",2);
	mode13->SetAttribute("WinSwitcherValue","4");
	mode13->SetAttribute("ChainLayer",0);

	mode14->SetAttribute("id",14); 
	mode14->SetAttribute("include","000110");
	mode14->SetAttribute("WinSwitcherType",2);
	mode14->SetAttribute("WinSwitcherValue","4");
	mode14->SetAttribute("ChainLayer",0);

	mode15->SetAttribute("id",15); 
	mode15->SetAttribute("include","000110");
	mode15->SetAttribute("WinSwitcherType",2);
	mode15->SetAttribute("WinSwitcherValue","A");
	mode15->SetAttribute("ChainLayer",0);

	mode16->SetAttribute("id",16); 
	mode16->SetAttribute("include","000110");
	mode16->SetAttribute("WinSwitcherType",2);
	mode16->SetAttribute("WinSwitcherValue","A");
	mode16->SetAttribute("ChainLayer",0);

	mode17->SetAttribute("id",17); 
	mode17->SetAttribute("include","000110");
	mode17->SetAttribute("WinSwitcherType",2);
	mode17->SetAttribute("WinSwitcherValue","1");
	mode17->SetAttribute("ChainLayer",0);

	mode18->SetAttribute("id",18); 
	mode18->SetAttribute("include","000110");
	mode18->SetAttribute("WinSwitcherType",2);
	mode18->SetAttribute("WinSwitcherValue","1");
	mode18->SetAttribute("ChainLayer",0);

	mode19->SetAttribute("id",19); 
	mode19->SetAttribute("include","000111");
	mode19->SetAttribute("WinSwitcherType",0);
	mode19->SetAttribute("WinSwitcherValue","");
	mode19->SetAttribute("ChainLayer",0);

	mode20->SetAttribute("id",20); 
	mode20->SetAttribute("include","000010");
	mode20->SetAttribute("WinSwitcherType",2);
	mode20->SetAttribute("WinSwitcherValue","1");
	mode20->SetAttribute("ChainLayer",0);

	mode21->SetAttribute("id",21); 
	mode21->SetAttribute("include","000110");
	mode21->SetAttribute("WinSwitcherType",2);
	mode21->SetAttribute("WinSwitcherValue","4");
	mode21->SetAttribute("ChainLayer",0);

	mode22->SetAttribute("id",22); 
	mode22->SetAttribute("include","000110");
	mode22->SetAttribute("WinSwitcherType",2);
	mode22->SetAttribute("WinSwitcherValue","4");
	mode22->SetAttribute("ChainLayer",0);

	mode23->SetAttribute("id",23); 
	mode23->SetAttribute("include","000000");
	mode23->SetAttribute("WinSwitcherType",2);
	mode23->SetAttribute("WinSwitcherValue","4");
	mode23->SetAttribute("ChainLayer",0);

	mode24->SetAttribute("id",24); 
	mode24->SetAttribute("include","000110");
	mode24->SetAttribute("WinSwitcherType",2);
	mode24->SetAttribute("WinSwitcherValue","3");
	mode24->SetAttribute("ChainLayer",0);

	mode25->SetAttribute("id",25); 
	mode25->SetAttribute("include","000110");
	mode25->SetAttribute("WinSwitcherType",2);
	mode25->SetAttribute("WinSwitcherValue","3");
	mode25->SetAttribute("ChainLayer",0);

	mode26->SetAttribute("id",26); 
	mode26->SetAttribute("include","000110");
	mode26->SetAttribute("WinSwitcherType",2);
	mode26->SetAttribute("WinSwitcherValue","3");
	mode26->SetAttribute("ChainLayer",0);

	mode27->SetAttribute("id",27); 
	mode27->SetAttribute("include","000110");
	mode27->SetAttribute("WinSwitcherType",2);
	mode27->SetAttribute("WinSwitcherValue","3");
	mode27->SetAttribute("ChainLayer",0);

	mode28->SetAttribute("id",28); 
	mode28->SetAttribute("include","000110");
	mode28->SetAttribute("WinSwitcherType",2);
	mode28->SetAttribute("WinSwitcherValue","3");
	mode28->SetAttribute("ChainLayer",0);

	mode29->SetAttribute("id",29); 
	mode29->SetAttribute("include","000110");
	mode29->SetAttribute("WinSwitcherType",2);
	mode29->SetAttribute("WinSwitcherValue","3");
	mode29->SetAttribute("ChainLayer",0);

	mode30->SetAttribute("id",30); 
	mode30->SetAttribute("include","000110");
	mode30->SetAttribute("WinSwitcherType",2);
	mode30->SetAttribute("WinSwitcherValue","3");
	mode30->SetAttribute("ChainLayer",0);

	mode31->SetAttribute("id",31); 
	mode31->SetAttribute("include","000110");
	mode31->SetAttribute("WinSwitcherType",2);
	mode31->SetAttribute("WinSwitcherValue","2");
	mode31->SetAttribute("ChainLayer",0);

	mode32->SetAttribute("id",32); 
	mode32->SetAttribute("include","000110");
	mode32->SetAttribute("WinSwitcherType",2);
	mode32->SetAttribute("WinSwitcherValue","2");
	mode32->SetAttribute("ChainLayer",0);

	mode33->SetAttribute("id",33); 
	mode33->SetAttribute("include","001100");
	mode33->SetAttribute("WinSwitcherType",4);
	mode33->SetAttribute("WinSwitcherValue","abc");
	mode33->SetAttribute("ChainLayer",0);

	mode34->SetAttribute("id",34); 
	mode34->SetAttribute("include","000110");
	mode34->SetAttribute("WinSwitcherType",4);
	mode34->SetAttribute("WinSwitcherValue","abc");
	mode34->SetAttribute("ChainLayer",0);

	mode35->SetAttribute("id",35); 
	mode35->SetAttribute("include","000000");
	mode35->SetAttribute("WinSwitcherType",4);
	mode35->SetAttribute("WinSwitcherValue","abc");
	mode35->SetAttribute("ChainLayer",0);

	mode36->SetAttribute("id",36); 
	mode36->SetAttribute("include","001000");
	mode36->SetAttribute("WinSwitcherType",0);
	mode36->SetAttribute("WinSwitcherValue","");
	mode36->SetAttribute("ChainLayer",0);

	mode37->SetAttribute("id",37); 
	mode37->SetAttribute("include","100000");
	mode37->SetAttribute("WinSwitcherType",0);
	mode37->SetAttribute("WinSwitcherValue","");
	mode37->SetAttribute("ChainLayer",0);

	mode38->SetAttribute("id",38); 
	mode38->SetAttribute("include","010000");
	mode38->SetAttribute("WinSwitcherType",0);
	mode38->SetAttribute("WinSwitcherValue","");
	mode38->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","1");
	input1->SetAttribute("type","PARA_LOGIC");
	input1->SetAttribute("max",1);
	input1->SetAttribute("min",0);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","1");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",MAX_INT);
	input2->SetAttribute("min",MIN_INT);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default","");
	input3->SetAttribute("type","PARA_TEXT");
	input3->SetAttribute("max",0);
	input3->SetAttribute("min",0);
	input3->SetAttribute("InOrOut","PARA_IN");
	input3->SetAttribute("IsPort",0);

	input4->SetAttribute("id",4);
	input4->SetAttribute("default","1");
	input4->SetAttribute("type","PARA_NUM");
	input4->SetAttribute("max",5);
	input4->SetAttribute("min",0);
	input4->SetAttribute("InOrOut","PARA_IN");
	input4->SetAttribute("IsPort",0);

	input5->SetAttribute("id",5);
	input5->SetAttribute("default","1");
	input5->SetAttribute("type","PARA_NUM");
	input5->SetAttribute("max",MAX_INT);
	input5->SetAttribute("min",MIN_INT);
	input5->SetAttribute("InOrOut","PARA_IN");
	input5->SetAttribute("IsPort",0);

	input6->SetAttribute("id",6);
	input6->SetAttribute("default","1");
	input6->SetAttribute("type","PARA_TEXT");
	input6->SetAttribute("max",0);
	input6->SetAttribute("min",0);
	input6->SetAttribute("InOrOut","PARA_IN");
	input6->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	//link mode and inputlist
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	//link all mode
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);
	mode->LinkEndChild(mode4);
	mode->LinkEndChild(mode5);
	mode->LinkEndChild(mode6);
	mode->LinkEndChild(mode7);
	mode->LinkEndChild(mode8);
	mode->LinkEndChild(mode9);
	mode->LinkEndChild(mode10);
	mode->LinkEndChild(mode11);
	mode->LinkEndChild(mode12);
	mode->LinkEndChild(mode13);
	mode->LinkEndChild(mode14);
	mode->LinkEndChild(mode15);
	mode->LinkEndChild(mode16);
	mode->LinkEndChild(mode17);
	mode->LinkEndChild(mode18);
	mode->LinkEndChild(mode19);
	mode->LinkEndChild(mode20);
	mode->LinkEndChild(mode21);
	mode->LinkEndChild(mode22);
	mode->LinkEndChild(mode23);
	mode->LinkEndChild(mode24);
	mode->LinkEndChild(mode25);
	mode->LinkEndChild(mode26);
	mode->LinkEndChild(mode27);
	mode->LinkEndChild(mode28);
	mode->LinkEndChild(mode29);
	mode->LinkEndChild(mode30);
	mode->LinkEndChild(mode31);
	mode->LinkEndChild(mode32);
	mode->LinkEndChild(mode33);
	mode->LinkEndChild(mode34);
	mode->LinkEndChild(mode35);
	mode->LinkEndChild(mode36);
	mode->LinkEndChild(mode37);
	mode->LinkEndChild(mode38);
	
	//link input list				   
	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);
	inputList->LinkEndChild(input5);
	inputList->LinkEndChild(input6);

	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//2004.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial2005()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");
	//mode
	TiXmlElement* mode = new TiXmlElement("Mode");
	TiXmlElement* stop = new TiXmlElement("stop");
	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",2005);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","01");
	module->SetAttribute("WinSwitcherType",4);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	stop->SetAttribute("id",1); 
	stop->SetAttribute("include","");
	stop->SetAttribute("WinSwitcherType",4);
	stop->SetAttribute("WinSwitcherValue","01");
	stop->SetAttribute("ChainLayer",0);

	//input attribute

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(stop);

	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//2005.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial3001()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode = new TiXmlElement("Mode");
	TiXmlElement* mode1 = new TiXmlElement("mode1");
	TiXmlElement* mode2 = new TiXmlElement("mode2");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");
	TiXmlElement* input2 = new TiXmlElement("input2");
	TiXmlElement* input3 = new TiXmlElement("input3");
	TiXmlElement* input4 = new TiXmlElement("input4");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",3001);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","");
	module->SetAttribute("WinSwitcherType",0);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","0010");
	mode1->SetAttribute("WinSwitcherType",0);
	mode1->SetAttribute("WinSwitcherValue","");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2);
	mode2->SetAttribute("include","1111");
	mode2->SetAttribute("WinSwitcherType",0);
	mode2->SetAttribute("WinSwitcherValue","0");
	mode2->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","2");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",5);
	input1->SetAttribute("min",0);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","1");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",2);
	input2->SetAttribute("min",0);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default",0);
	input3->SetAttribute("type","PARA_NUM");
	input3->SetAttribute("max",0);
	input3->SetAttribute("min",0);
	input3->SetAttribute("InOrOut","PARA_OUT");
	input3->SetAttribute("IsPort",0);

	input4->SetAttribute("id",4);
	input4->SetAttribute("default",0);
	input4->SetAttribute("type","PARA_LOGIC");
	input4->SetAttribute("max",0);
	input4->SetAttribute("min",0);
	input4->SetAttribute("InOrOut","PARA_OUT");
	input4->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);


	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//3001.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial3002()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode = new TiXmlElement("Mode");
	TiXmlElement* mode1 = new TiXmlElement("mode1");
	TiXmlElement* mode2 = new TiXmlElement("mode2");
	TiXmlElement* mode3 = new TiXmlElement("mode3");
	TiXmlElement* mode4 = new TiXmlElement("mode4");
	TiXmlElement* mode5 = new TiXmlElement("mode5");
	TiXmlElement* mode6 = new TiXmlElement("mode6");
	TiXmlElement* mode7 = new TiXmlElement("mode7");
	TiXmlElement* mode8 = new TiXmlElement("mode8");
	TiXmlElement* mode9 = new TiXmlElement("mode9");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");
	TiXmlElement* input2 = new TiXmlElement("input2");
	TiXmlElement* input3 = new TiXmlElement("input3");
	TiXmlElement* input4 = new TiXmlElement("input4");
	TiXmlElement* input5 = new TiXmlElement("input5");
	TiXmlElement* input6 = new TiXmlElement("input6");
	TiXmlElement* input7 = new TiXmlElement("input7");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",3002);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","3");
	module->SetAttribute("WinSwitcherType",2);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","0000100");
	mode1->SetAttribute("WinSwitcherType",2);
	mode1->SetAttribute("WinSwitcherValue","3");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2);
	mode2->SetAttribute("include","0000001");
	mode2->SetAttribute("WinSwitcherType",2);
	mode2->SetAttribute("WinSwitcherValue","3");
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3);
	mode3->SetAttribute("include","0000001");
	mode3->SetAttribute("WinSwitcherType",2);
	mode3->SetAttribute("WinSwitcherValue","3");
	mode3->SetAttribute("ChainLayer",0);

	mode4->SetAttribute("id",4);
	mode4->SetAttribute("include","1000110");
	mode4->SetAttribute("WinSwitcherType",2);
	mode4->SetAttribute("WinSwitcherValue","3");
	mode4->SetAttribute("ChainLayer",0);

	mode5->SetAttribute("id",5);
	mode5->SetAttribute("include","0110011");
	mode5->SetAttribute("WinSwitcherType",2);
	mode5->SetAttribute("WinSwitcherValue","3");
	mode5->SetAttribute("ChainLayer",0);

	mode6->SetAttribute("id",6);
	mode6->SetAttribute("include","0110011");
	mode6->SetAttribute("WinSwitcherType",2);
	mode6->SetAttribute("WinSwitcherValue","3");
	mode6->SetAttribute("ChainLayer",0);

	mode7->SetAttribute("id",7);
	mode7->SetAttribute("include","0001000");
	mode7->SetAttribute("WinSwitcherType",0);
	mode7->SetAttribute("WinSwitcherValue","0");
	mode7->SetAttribute("ChainLayer",0);

	mode8->SetAttribute("id",8);
	mode8->SetAttribute("include","0001000");
	mode8->SetAttribute("WinSwitcherType",2);
	mode8->SetAttribute("WinSwitcherValue","3");
	mode8->SetAttribute("ChainLayer",0);

	mode9->SetAttribute("id",9);
	mode9->SetAttribute("include","0001000");
	mode9->SetAttribute("WinSwitcherType",2);
	mode9->SetAttribute("WinSwitcherValue","3");
	mode9->SetAttribute("ChainLayer",0);


	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","5");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",7);
	input1->SetAttribute("min",0);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","4");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",5);
	input2->SetAttribute("min",0);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default",0);
	input3->SetAttribute("type","PARA_NUM");
	input3->SetAttribute("max",MAX_INT);
	input3->SetAttribute("min",MIN_INT);
	input3->SetAttribute("InOrOut","PARA_IN");
	input3->SetAttribute("IsPort",0);

	input4->SetAttribute("id",4);
	input4->SetAttribute("default",50);
	input4->SetAttribute("type","PARA_NUM");
	input4->SetAttribute("max",100);
	input4->SetAttribute("min",0);
	input4->SetAttribute("InOrOut","PARA_IN");
	input4->SetAttribute("IsPort",0);

	input5->SetAttribute("id",5);
	input5->SetAttribute("default",0);
	input5->SetAttribute("type","PARA_NUM");
	input5->SetAttribute("max",7);
	input5->SetAttribute("min",1);
	input5->SetAttribute("InOrOut","PARA_OUT");
	input5->SetAttribute("IsPort",0);

	input6->SetAttribute("id",6);
	input6->SetAttribute("default",0);
	input6->SetAttribute("type","PARA_LOGIC");
	input6->SetAttribute("max",0);
	input6->SetAttribute("min",0);
	input6->SetAttribute("InOrOut","PARA_OUT");
	input6->SetAttribute("IsPort",0);

	input7->SetAttribute("id",7);
	input7->SetAttribute("default",0);
	input7->SetAttribute("type","PARA_NUM");
	input7->SetAttribute("max",0);
	input7->SetAttribute("min",0);
	input7->SetAttribute("InOrOut","PARA_OUT");
	input7->SetAttribute("IsPort",0);


    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);
	mode->LinkEndChild(mode4);
	mode->LinkEndChild(mode5);
	mode->LinkEndChild(mode6);
	mode->LinkEndChild(mode7);
	mode->LinkEndChild(mode8);
	mode->LinkEndChild(mode9);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);
	inputList->LinkEndChild(input5);
	inputList->LinkEndChild(input6);
	inputList->LinkEndChild(input7);


	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//3002.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial3003()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");
	//mode
	TiXmlElement* mode = new TiXmlElement("Mode");
	TiXmlElement* mode11 = new TiXmlElement("mode11");
	TiXmlElement* mode12 = new TiXmlElement("mode12");
	TiXmlElement* mode13 = new TiXmlElement("mode13");
	TiXmlElement* mode21 = new TiXmlElement("mode21");
	TiXmlElement* mode22 = new TiXmlElement("mode22");
	TiXmlElement* mode31 = new TiXmlElement("mode31");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");
	TiXmlElement* input2 = new TiXmlElement("input2");
	TiXmlElement* input3 = new TiXmlElement("input3");
	TiXmlElement* input4 = new TiXmlElement("input4");
	TiXmlElement* input5 = new TiXmlElement("input5");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",3003);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","2");
	module->SetAttribute("WinSwitcherType",2);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode11->SetAttribute("id",1); 
	mode11->SetAttribute("include","00100");
	mode11->SetAttribute("WinSwitcherType",2);
	mode11->SetAttribute("WinSwitcherValue","2");
	mode11->SetAttribute("ChainLayer",0);

	mode12->SetAttribute("id",2);
	mode12->SetAttribute("include","00010");
	mode12->SetAttribute("WinSwitcherType",2);
	mode12->SetAttribute("WinSwitcherValue","2");
	mode12->SetAttribute("ChainLayer",0);

	mode13->SetAttribute("id",3);
	mode13->SetAttribute("include","00110");
	mode13->SetAttribute("WinSwitcherType",2);
	mode13->SetAttribute("WinSwitcherValue","2");
	mode13->SetAttribute("ChainLayer",0);

	mode21->SetAttribute("id",4);
	mode21->SetAttribute("include","11101");
	mode21->SetAttribute("WinSwitcherType",2);
	mode21->SetAttribute("WinSwitcherValue","2");
	mode21->SetAttribute("ChainLayer",0);

	mode22->SetAttribute("id",5);
	mode22->SetAttribute("include","11011");
	mode22->SetAttribute("WinSwitcherType",2);
	mode22->SetAttribute("WinSwitcherValue","2");
	mode22->SetAttribute("ChainLayer",0);

	mode31->SetAttribute("id",6);
	mode31->SetAttribute("include","00000");
	mode31->SetAttribute("WinSwitcherType",2);
	mode31->SetAttribute("WinSwitcherValue","2");
	mode31->SetAttribute("ChainLayer",0);



	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","4");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",5);
	input1->SetAttribute("min",0);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","90");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",MAX_INT);
	input2->SetAttribute("min",MIN_INT);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default",0);
	input3->SetAttribute("type","PARA_NUM");
	input3->SetAttribute("max",0);
	input3->SetAttribute("min",0);
	input3->SetAttribute("InOrOut","PARA_OUT");
	input3->SetAttribute("IsPort",0);

	input4->SetAttribute("id",4);
	input4->SetAttribute("default",0);
	input4->SetAttribute("type","PARA_NUM");
	input4->SetAttribute("max",0);
	input4->SetAttribute("min",0);
	input4->SetAttribute("InOrOut","PARA_OUT");
	input4->SetAttribute("IsPort",0);

	input5->SetAttribute("id",5);
	input5->SetAttribute("default",0);
	input5->SetAttribute("type","PARA_LOGIC");
	input5->SetAttribute("max",0);
	input5->SetAttribute("min",0);
	input5->SetAttribute("InOrOut","PARA_OUT");
	input5->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode11);
	mode->LinkEndChild(mode12);
	mode->LinkEndChild(mode13);
	mode->LinkEndChild(mode21);
	mode->LinkEndChild(mode22);
	mode->LinkEndChild(mode31);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);
	inputList->LinkEndChild(input5);


	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//3003.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial3004()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode = new TiXmlElement("Mode");
	TiXmlElement* mode1 = new TiXmlElement("mode1");
	TiXmlElement* mode2 = new TiXmlElement("mode2");
	TiXmlElement* mode3 = new TiXmlElement("mode3");
	TiXmlElement* mode4 = new TiXmlElement("mode4");
	TiXmlElement* mode5 = new TiXmlElement("mode5");
	TiXmlElement* mode6 = new TiXmlElement("mode6");
	TiXmlElement* mode7 = new TiXmlElement("mode7");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");
	TiXmlElement* input2 = new TiXmlElement("input2");
	TiXmlElement* input3 = new TiXmlElement("input3");
	TiXmlElement* input4 = new TiXmlElement("input4");
	TiXmlElement* input5 = new TiXmlElement("input5");
	TiXmlElement* input6 = new TiXmlElement("input6");
	TiXmlElement* input7 = new TiXmlElement("input7");
	TiXmlElement* input8 = new TiXmlElement("input8");
	TiXmlElement* input9 = new TiXmlElement("input9");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",3004);
	module->SetAttribute("Mode",2);
	module->SetAttribute("WinSwitcherValue","4");
	module->SetAttribute("WinSwitcherType",2);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","000010000");
	mode1->SetAttribute("WinSwitcherType",2);
	mode1->SetAttribute("WinSwitcherValue","4");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2);
	mode2->SetAttribute("include","100011100");
	mode2->SetAttribute("WinSwitcherType",2);
	mode2->SetAttribute("WinSwitcherValue","4");
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3);
	mode3->SetAttribute("include","100000010");
	mode3->SetAttribute("WinSwitcherType",2);
	mode3->SetAttribute("WinSwitcherValue","4");
	mode3->SetAttribute("ChainLayer",0);

	mode4->SetAttribute("id",4);
	mode4->SetAttribute("include","011010001");
	mode4->SetAttribute("WinSwitcherType",2);
	mode4->SetAttribute("WinSwitcherValue","3");
	mode4->SetAttribute("ChainLayer",0);

	mode5->SetAttribute("id",5);
	mode5->SetAttribute("include","111000101");
	mode5->SetAttribute("WinSwitcherType",2);
	mode5->SetAttribute("WinSwitcherValue","3");
	mode5->SetAttribute("ChainLayer",0);

	mode6->SetAttribute("id",6);
	mode6->SetAttribute("include","111010001");
	mode6->SetAttribute("WinSwitcherType",2);
	mode6->SetAttribute("WinSwitcherValue","3");
	mode6->SetAttribute("ChainLayer",0);

	mode7->SetAttribute("id",7);
	mode7->SetAttribute("include","100100011");
	mode7->SetAttribute("WinSwitcherType",0);
	mode7->SetAttribute("WinSwitcherValue","0");
	mode7->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","1");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",4);
	input1->SetAttribute("min",1);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","4");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",5);
	input2->SetAttribute("min",0);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default",50);
	input3->SetAttribute("type","PARA_NUM");
	input3->SetAttribute("max",MAX_INT);
	input3->SetAttribute("min",MIN_INT);
	input3->SetAttribute("InOrOut","PARA_IN");
	input3->SetAttribute("IsPort",0);

	input4->SetAttribute("id",4);
	input4->SetAttribute("default",1);
	input4->SetAttribute("type","PARA_NUM");
	input4->SetAttribute("max",11);
	input4->SetAttribute("min",0);
	input4->SetAttribute("InOrOut","PARA_IN");
	input4->SetAttribute("IsPort",0);

	input5->SetAttribute("id",5);
	input5->SetAttribute("default",0);
	input5->SetAttribute("type","PARA_NUM");
	input5->SetAttribute("max",100);
	input5->SetAttribute("min",0);
	input5->SetAttribute("InOrOut","PARA_OUT");
	input5->SetAttribute("IsPort",0);

	input6->SetAttribute("id",6);
	input6->SetAttribute("default",0);
	input6->SetAttribute("type","PARA_LOGIC");
	input6->SetAttribute("max",1);
	input6->SetAttribute("min",0);
	input6->SetAttribute("InOrOut","PARA_OUT");
	input6->SetAttribute("IsPort",0);

	input7->SetAttribute("id",7);
	input7->SetAttribute("default",0);
	input7->SetAttribute("type","PARA_NUM");
	input7->SetAttribute("max",25);
	input7->SetAttribute("min",-25);
	input7->SetAttribute("InOrOut","PARA_OUT");
	input7->SetAttribute("IsPort",0);

	input8->SetAttribute("id",8);
	input8->SetAttribute("default",0);
	input8->SetAttribute("type","PARA_NUM");
	input8->SetAttribute("max",11);
	input8->SetAttribute("min",0);
	input8->SetAttribute("InOrOut","PARA_OUT");
	input8->SetAttribute("IsPort",0);

	input9->SetAttribute("id",9);
	input9->SetAttribute("default",0);
	input9->SetAttribute("type","PARA_LOGIC");
	input9->SetAttribute("max",1);
	input9->SetAttribute("min",0);
	input9->SetAttribute("InOrOut","PARA_OUT");
	input9->SetAttribute("IsPort",0);
    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);
	mode->LinkEndChild(mode4);
	mode->LinkEndChild(mode5);
	mode->LinkEndChild(mode6);
	mode->LinkEndChild(mode7);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);
	inputList->LinkEndChild(input5);
	inputList->LinkEndChild(input6);
	inputList->LinkEndChild(input7);
	inputList->LinkEndChild(input8);
	inputList->LinkEndChild(input9);


	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//3004.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial3005()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode = new TiXmlElement("Mode");
	TiXmlElement* mode1 = new TiXmlElement("mode1");
	TiXmlElement* mode2 = new TiXmlElement("mode2");
	TiXmlElement* mode3 = new TiXmlElement("mode3");
	TiXmlElement* mode4 = new TiXmlElement("mode4");
	TiXmlElement* mode5 = new TiXmlElement("mode5");
	TiXmlElement* mode6 = new TiXmlElement("mode6");
	TiXmlElement* mode7 = new TiXmlElement("mode7");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");
	TiXmlElement* input2 = new TiXmlElement("input2");
	TiXmlElement* input3 = new TiXmlElement("input3");
	TiXmlElement* input4 = new TiXmlElement("input4");
	TiXmlElement* input5 = new TiXmlElement("input5");
	TiXmlElement* input6 = new TiXmlElement("input6");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",3005);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","A");
	module->SetAttribute("WinSwitcherType",2);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","001000");
	mode1->SetAttribute("WinSwitcherType",2);
	mode1->SetAttribute("WinSwitcherValue","A");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2);
	mode2->SetAttribute("include","000100");
	mode2->SetAttribute("WinSwitcherType",2);
	mode2->SetAttribute("WinSwitcherValue","A");
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3);
	mode3->SetAttribute("include","000010");
	mode3->SetAttribute("WinSwitcherType",2);
	mode3->SetAttribute("WinSwitcherValue","A");
	mode3->SetAttribute("ChainLayer",0);

	mode4->SetAttribute("id",4);
	mode4->SetAttribute("include","111001");
	mode4->SetAttribute("WinSwitcherType",2);
	mode4->SetAttribute("WinSwitcherValue","A");
	mode4->SetAttribute("ChainLayer",0);

	mode5->SetAttribute("id",5);
	mode5->SetAttribute("include","110101");
	mode5->SetAttribute("WinSwitcherType",2);
	mode5->SetAttribute("WinSwitcherValue","A");
	mode5->SetAttribute("ChainLayer",0);

	mode6->SetAttribute("id",6);
	mode6->SetAttribute("include","110011");
	mode6->SetAttribute("WinSwitcherType",2);
	mode6->SetAttribute("WinSwitcherValue","A");
	mode6->SetAttribute("ChainLayer",0);

	mode7->SetAttribute("id",7);
	mode7->SetAttribute("include","000000");
	mode7->SetAttribute("WinSwitcherType",2);
	mode7->SetAttribute("WinSwitcherValue","A");
	mode7->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","2");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",5);
	input1->SetAttribute("min",0);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","90");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",MAX_INT);
	input2->SetAttribute("min",MIN_INT);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default",0);
	input3->SetAttribute("type","PARA_NUM");
	input3->SetAttribute("max",MAX_INT);
	input3->SetAttribute("min",MIN_INT);
	input3->SetAttribute("InOrOut","PARA_OUT");
	input3->SetAttribute("IsPort",0);

	input4->SetAttribute("id",4);
	input4->SetAttribute("default",1);
	input4->SetAttribute("type","PARA_NUM");
	input4->SetAttribute("max",MAX_INT);
	input4->SetAttribute("min",MIN_INT);
	input4->SetAttribute("InOrOut","PARA_OUT");
	input4->SetAttribute("IsPort",0);

	input5->SetAttribute("id",5);
	input5->SetAttribute("default",0);
	input5->SetAttribute("type","PARA_NUM");
	input5->SetAttribute("max",100);
	input5->SetAttribute("min",-100);
	input5->SetAttribute("InOrOut","PARA_OUT");
	input5->SetAttribute("IsPort",0);

	input6->SetAttribute("id",6);
	input6->SetAttribute("default",0);
	input6->SetAttribute("type","PARA_LOGIC");
	input6->SetAttribute("max",1);
	input6->SetAttribute("min",0);
	input6->SetAttribute("InOrOut","PARA_OUT");
	input6->SetAttribute("IsPort",0);


    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);
	mode->LinkEndChild(mode4);
	mode->LinkEndChild(mode5);
	mode->LinkEndChild(mode6);
	mode->LinkEndChild(mode7);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);
	inputList->LinkEndChild(input5);
	inputList->LinkEndChild(input6);


	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//3005.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial3006()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode = new TiXmlElement("Mode");
	TiXmlElement* mode1 = new TiXmlElement("mode1");
	TiXmlElement* mode2 = new TiXmlElement("mode2");
	TiXmlElement* mode3 = new TiXmlElement("mode3");
	TiXmlElement* mode4 = new TiXmlElement("mode4");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");
	TiXmlElement* input2 = new TiXmlElement("input2");
	TiXmlElement* input3 = new TiXmlElement("input3");
	TiXmlElement* input4 = new TiXmlElement("input4");
	TiXmlElement* input5 = new TiXmlElement("input5");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",3006);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","1");
	module->SetAttribute("WinSwitcherType",2);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","00100");
	mode1->SetAttribute("WinSwitcherType",2);
	mode1->SetAttribute("WinSwitcherValue","1");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2);
	mode2->SetAttribute("include","00010");
	mode2->SetAttribute("WinSwitcherType",2);
	mode2->SetAttribute("WinSwitcherValue","1");
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3);
	mode3->SetAttribute("include","11101");
	mode3->SetAttribute("WinSwitcherType",2);
	mode3->SetAttribute("WinSwitcherValue","1");
	mode3->SetAttribute("ChainLayer",0);

	mode4->SetAttribute("id",4);
	mode4->SetAttribute("include","11010");
	mode4->SetAttribute("WinSwitcherType",2);
	mode4->SetAttribute("WinSwitcherValue","1");
	mode4->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","2");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",5);
	input1->SetAttribute("min",0);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","25");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",MAX_INT);
	input2->SetAttribute("min",MIN_INT);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default",0);
	input3->SetAttribute("type","PARA_NUM");
	input3->SetAttribute("max",120);
	input3->SetAttribute("min",-20);
	input3->SetAttribute("InOrOut","PARA_OUT");
	input3->SetAttribute("IsPort",0);

	input4->SetAttribute("id",4);
	input4->SetAttribute("default",0);
	input4->SetAttribute("type","PARA_NUM");
	input4->SetAttribute("max",248);
	input4->SetAttribute("min",-4);
	input4->SetAttribute("InOrOut","PARA_OUT");
	input4->SetAttribute("IsPort",0);

	input5->SetAttribute("id",5);
	input5->SetAttribute("default",0);
	input5->SetAttribute("type","PARA_NUM");
	input5->SetAttribute("max",1);
	input5->SetAttribute("min",0);
	input5->SetAttribute("InOrOut","PARA_OUT");
	input5->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);
	mode->LinkEndChild(mode4);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);
	inputList->LinkEndChild(input5);



	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//3006.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial3007()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode = new TiXmlElement("Mode");
	TiXmlElement* mode1 = new TiXmlElement("mode1");
	TiXmlElement* mode2 = new TiXmlElement("mode2");
	TiXmlElement* mode3 = new TiXmlElement("mode3");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");
	TiXmlElement* input2 = new TiXmlElement("input2");
	TiXmlElement* input3 = new TiXmlElement("input3");
	TiXmlElement* input4 = new TiXmlElement("input4");
	TiXmlElement* input5 = new TiXmlElement("input5");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",3007);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","1");
	module->SetAttribute("WinSwitcherType",2);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","10010");
	mode1->SetAttribute("WinSwitcherType",0);
	mode1->SetAttribute("WinSwitcherValue","0");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2);
	mode2->SetAttribute("include","11111");
	mode2->SetAttribute("WinSwitcherType",0);
	mode2->SetAttribute("WinSwitcherValue","0");
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3);
	mode3->SetAttribute("include","10000");
	mode3->SetAttribute("WinSwitcherType",0);
	mode3->SetAttribute("WinSwitcherValue","0");
	mode3->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","1");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",8);
	input1->SetAttribute("min",1);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","2");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",5);
	input2->SetAttribute("min",0);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default",5);
	input3->SetAttribute("type","PARA_NUM");
	input3->SetAttribute("max",MAX_INT);
	input3->SetAttribute("min",MIN_INT);
	input3->SetAttribute("InOrOut","PARA_IN");
	input3->SetAttribute("IsPort",0);

	input4->SetAttribute("id",4);
	input4->SetAttribute("default",0);
	input4->SetAttribute("type","PARA_NUM");
	input4->SetAttribute("max",MAX_INT);
	input4->SetAttribute("min",MIN_INT);
	input4->SetAttribute("InOrOut","PARA_OUT");
	input4->SetAttribute("IsPort",0);

	input5->SetAttribute("id",5);
	input5->SetAttribute("default",0);
	input5->SetAttribute("type","PARA_LOGIC");
	input5->SetAttribute("max",1);
	input5->SetAttribute("min",0);
	input5->SetAttribute("InOrOut","PARA_OUT");
	input5->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);
	inputList->LinkEndChild(input5);



	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//3007.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial3008()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode = new TiXmlElement("Mode");
	TiXmlElement* mode1 = new TiXmlElement("mode1");
	TiXmlElement* mode2 = new TiXmlElement("mode2");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");
	TiXmlElement* input2 = new TiXmlElement("input2");
	TiXmlElement* input3 = new TiXmlElement("input3");
	TiXmlElement* input4 = new TiXmlElement("input4");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",3008);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","1");
	module->SetAttribute("WinSwitcherType",2);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","0100");
	mode1->SetAttribute("WinSwitcherType",2);
	mode1->SetAttribute("WinSwitcherValue","1");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2);
	mode2->SetAttribute("include","1011");
	mode2->SetAttribute("WinSwitcherType",2);
	mode2->SetAttribute("WinSwitcherValue","1");
	mode2->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","1");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",2);
	input1->SetAttribute("min",0);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","0");
	input2->SetAttribute("type","PARA_LOGIC");
	input2->SetAttribute("max",1);
	input2->SetAttribute("min",0);
	input2->SetAttribute("InOrOut","PARA_OUT");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default",0);
	input3->SetAttribute("type","PARA_LOGIC");
	input3->SetAttribute("max",1);
	input3->SetAttribute("min",0);
	input3->SetAttribute("InOrOut","PARA_OUT");
	input3->SetAttribute("IsPort",0);

	input4->SetAttribute("id",4);
	input4->SetAttribute("default",0);
	input4->SetAttribute("type","PARA_NUM");
	input4->SetAttribute("max",2);
	input4->SetAttribute("min",0);
	input4->SetAttribute("InOrOut","PARA_OUT");
	input4->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);
	
	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//3008.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial3009()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode = new TiXmlElement("Mode");
	TiXmlElement* mode1 = new TiXmlElement("mode1");
	TiXmlElement* mode2 = new TiXmlElement("mode2");
	TiXmlElement* mode3 = new TiXmlElement("mode3");
	TiXmlElement* mode4 = new TiXmlElement("mode4");
	TiXmlElement* mode5 = new TiXmlElement("mode5");
	TiXmlElement* mode6 = new TiXmlElement("mode6");
	TiXmlElement* mode7 = new TiXmlElement("mode7");
	TiXmlElement* mode8 = new TiXmlElement("mode8");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");
	TiXmlElement* input2 = new TiXmlElement("input2");
	TiXmlElement* input3 = new TiXmlElement("input3");
	TiXmlElement* input4 = new TiXmlElement("input4");
	TiXmlElement* input5 = new TiXmlElement("input5");
	TiXmlElement* input6 = new TiXmlElement("input6");
	TiXmlElement* input7 = new TiXmlElement("input7");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",3009);
	module->SetAttribute("Mode",3);
	module->SetAttribute("WinSwitcherValue","4");
	module->SetAttribute("WinSwitcherType",2);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","0011000");
	mode1->SetAttribute("WinSwitcherType",2);
	mode1->SetAttribute("WinSwitcherValue","4");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2);
	mode2->SetAttribute("include","0010100");
	mode2->SetAttribute("WinSwitcherType",2);
	mode2->SetAttribute("WinSwitcherValue","4");
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3);
	mode3->SetAttribute("include","0001000");
	mode3->SetAttribute("WinSwitcherType",2);
	mode3->SetAttribute("WinSwitcherValue","4");
	mode3->SetAttribute("ChainLayer",0);

	mode4->SetAttribute("id",4);
	mode4->SetAttribute("include","0000100");
	mode4->SetAttribute("WinSwitcherType",2);
	mode4->SetAttribute("WinSwitcherValue","4");
	mode4->SetAttribute("ChainLayer",0);

	mode5->SetAttribute("id",5);
	mode5->SetAttribute("include","0000010");
	mode5->SetAttribute("WinSwitcherType",2);
	mode5->SetAttribute("WinSwitcherValue","4");
	mode5->SetAttribute("ChainLayer",0);

	mode6->SetAttribute("id",6);
	mode6->SetAttribute("include","1101001");
	mode6->SetAttribute("WinSwitcherType",2);
	mode6->SetAttribute("WinSwitcherValue","4");
	mode6->SetAttribute("ChainLayer",0);

	mode7->SetAttribute("id",7);
	mode7->SetAttribute("include","1100101");
	mode7->SetAttribute("WinSwitcherType",2);
	mode7->SetAttribute("WinSwitcherValue","4");
	mode7->SetAttribute("ChainLayer",0);

	mode8->SetAttribute("id",8);
	mode8->SetAttribute("include","0000010");
	mode8->SetAttribute("WinSwitcherType",2);
	mode8->SetAttribute("WinSwitcherValue","4");
	mode8->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","4");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",5);
	input1->SetAttribute("min",0);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","50");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",MAX_INT);
	input2->SetAttribute("min",MIN_INT);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default",0);
	input3->SetAttribute("type","PARA_NUM");
	input3->SetAttribute("max",1);
	input3->SetAttribute("min",0);
	input3->SetAttribute("InOrOut","PARA_IN");
	input3->SetAttribute("IsPort",0);

	input4->SetAttribute("id",4);
	input4->SetAttribute("default",0);
	input4->SetAttribute("type","PARA_NUM");
	input4->SetAttribute("max",255);
	input4->SetAttribute("min",0);
	input4->SetAttribute("InOrOut","PARA_OUT");
	input4->SetAttribute("IsPort",0);

	input5->SetAttribute("id",5);
	input5->SetAttribute("default",0);
	input5->SetAttribute("type","PARA_NUM");
	input5->SetAttribute("max",100);
	input5->SetAttribute("min",0);
	input5->SetAttribute("InOrOut","PARA_OUT");
	input5->SetAttribute("IsPort",0);

	input6->SetAttribute("id",6);
	input6->SetAttribute("default",0);
	input6->SetAttribute("type","PARA_LOGIC");
	input6->SetAttribute("max",1);
	input6->SetAttribute("min",0);
	input6->SetAttribute("InOrOut","PARA_OUT");
	input6->SetAttribute("IsPort",0);

	input7->SetAttribute("id",7);
	input7->SetAttribute("default",0);
	input7->SetAttribute("type","PARA_LOGIC");
	input7->SetAttribute("max",1);
	input7->SetAttribute("min",0);
	input7->SetAttribute("InOrOut","PARA_OUT");
	input7->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);
	mode->LinkEndChild(mode4);
	mode->LinkEndChild(mode5);
	mode->LinkEndChild(mode6);
	mode->LinkEndChild(mode7);
	mode->LinkEndChild(mode8);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);
	inputList->LinkEndChild(input5);
	inputList->LinkEndChild(input6);
	inputList->LinkEndChild(input7);
	
	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//3009.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial3010()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode   = new TiXmlElement("Mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");
	TiXmlElement* mode2  = new TiXmlElement("mode2");
	TiXmlElement* mode3  = new TiXmlElement("mode3");
	TiXmlElement* mode4  = new TiXmlElement("mode4");
	TiXmlElement* mode5  = new TiXmlElement("mode5");
	TiXmlElement* mode6  = new TiXmlElement("mode6");
	TiXmlElement* mode7  = new TiXmlElement("mode7");
	TiXmlElement* mode8  = new TiXmlElement("mode8");
	TiXmlElement* mode9  = new TiXmlElement("mode9");
	TiXmlElement* mode10 = new TiXmlElement("mode10");
	TiXmlElement* mode11 = new TiXmlElement("mode11");
	TiXmlElement* mode12 = new TiXmlElement("mode12");
	TiXmlElement* mode13 = new TiXmlElement("mode13");
	TiXmlElement* mode14 = new TiXmlElement("mode14");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");
	TiXmlElement* input2 = new TiXmlElement("input2");
	TiXmlElement* input3 = new TiXmlElement("input3");
	TiXmlElement* input4 = new TiXmlElement("input4");
	TiXmlElement* input5 = new TiXmlElement("input5");
	TiXmlElement* input6 = new TiXmlElement("input6");
	TiXmlElement* input7 = new TiXmlElement("input7");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",3010);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","3");
	module->SetAttribute("WinSwitcherType",2);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","0010000");
	mode1->SetAttribute("WinSwitcherType",2);
	mode1->SetAttribute("WinSwitcherValue","3");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2);
	mode2->SetAttribute("include","0100000");
	mode2->SetAttribute("WinSwitcherType",2);
	mode2->SetAttribute("WinSwitcherValue","3");
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3);
	mode3->SetAttribute("include","0001000");
	mode3->SetAttribute("WinSwitcherType",2);
	mode3->SetAttribute("WinSwitcherValue","3");
	mode3->SetAttribute("ChainLayer",0);

	mode4->SetAttribute("id",4);
	mode4->SetAttribute("include","0010000");
	mode4->SetAttribute("WinSwitcherType",2);
	mode4->SetAttribute("WinSwitcherValue","3");
	mode4->SetAttribute("ChainLayer",0);

	mode5->SetAttribute("id",5);
	mode5->SetAttribute("include","0100000");
	mode5->SetAttribute("WinSwitcherType",2);
	mode5->SetAttribute("WinSwitcherValue","3");
	mode5->SetAttribute("ChainLayer",0);

	mode6->SetAttribute("id",6);
	mode6->SetAttribute("include","0001000");
	mode6->SetAttribute("WinSwitcherType",2);
	mode6->SetAttribute("WinSwitcherValue","3");
	mode6->SetAttribute("ChainLayer",0);

	mode7->SetAttribute("id",7);
	mode7->SetAttribute("include","0000100");
	mode7->SetAttribute("WinSwitcherType",2);
	mode7->SetAttribute("WinSwitcherValue","3");
	mode7->SetAttribute("ChainLayer",0);

	mode8->SetAttribute("id",8);
	mode8->SetAttribute("include","1010011");
	mode8->SetAttribute("WinSwitcherType",2);
	mode8->SetAttribute("WinSwitcherValue","3");
	mode8->SetAttribute("ChainLayer",0);

	mode9->SetAttribute("id",9);
	mode9->SetAttribute("include","1100011");
	mode9->SetAttribute("WinSwitcherType",2);
	mode9->SetAttribute("WinSwitcherValue","3");
	mode9->SetAttribute("ChainLayer",0);

	mode10->SetAttribute("id",10);
	mode10->SetAttribute("include","1000111");
	mode10->SetAttribute("WinSwitcherType",2);
	mode10->SetAttribute("WinSwitcherValue","3");
	mode10->SetAttribute("ChainLayer",0);

	mode11->SetAttribute("id",11);
	mode11->SetAttribute("include","1010011");
	mode11->SetAttribute("WinSwitcherType",2);
	mode11->SetAttribute("WinSwitcherValue","3");
	mode11->SetAttribute("ChainLayer",0);

	mode12->SetAttribute("id",12);
	mode12->SetAttribute("include","1100011");
	mode12->SetAttribute("WinSwitcherType",2);
	mode12->SetAttribute("WinSwitcherValue","3");
	mode12->SetAttribute("ChainLayer",0);

	mode13->SetAttribute("id",13);
	mode13->SetAttribute("include","1001011");
	mode13->SetAttribute("WinSwitcherType",2);
	mode13->SetAttribute("WinSwitcherValue","3");
	mode13->SetAttribute("ChainLayer",0);

	mode14->SetAttribute("id",14);
	mode14->SetAttribute("include","1000111");
	mode14->SetAttribute("WinSwitcherType",2);
	mode14->SetAttribute("WinSwitcherValue","3");
	mode14->SetAttribute("ChainLayer",0);

	//input attribute
	//比较类型
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","2");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",5);
	input1->SetAttribute("min",0);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	//A
	input2->SetAttribute("id",2);
	input2->SetAttribute("default","0");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",MAX_INT);
	input2->SetAttribute("min",MIN_INT);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	//V
	input3->SetAttribute("id",3);
	input3->SetAttribute("default",0);
	input3->SetAttribute("type","PARA_NUM");
	input3->SetAttribute("max",MAX_INT);
	input3->SetAttribute("min",MIN_INT);
	input3->SetAttribute("InOrOut","PARA_OUT");
	input3->SetAttribute("IsPort",0);

	//W
	input4->SetAttribute("id",4);
	input4->SetAttribute("default",0);
	input4->SetAttribute("type","PARA_NUM");
	input4->SetAttribute("max",MAX_INT);
	input4->SetAttribute("min",MIN_INT);
	input4->SetAttribute("InOrOut","PARA_OUT");
	input4->SetAttribute("IsPort",0);

	//J
	input5->SetAttribute("id",5);
	input5->SetAttribute("default",0);
	input5->SetAttribute("type","PARA_NUM");
	input5->SetAttribute("max",MAX_INT);
	input5->SetAttribute("min",MIN_INT);
	input5->SetAttribute("InOrOut","PARA_OUT");
	input5->SetAttribute("IsPort",0);

	//阈值
	input6->SetAttribute("id",6);
	input6->SetAttribute("default",0);
	input6->SetAttribute("type","PARA_NUM");
	input6->SetAttribute("max",MAX_INT);
	input6->SetAttribute("min",MIN_INT);
	input6->SetAttribute("InOrOut","PARA_OUT");
	input6->SetAttribute("IsPort",0);

	//比较结果
	input7->SetAttribute("id",7);
	input7->SetAttribute("default",0);
	input7->SetAttribute("type","PARA_LOGIC");
	input7->SetAttribute("max",1);
	input7->SetAttribute("min",0);
	input7->SetAttribute("InOrOut","PARA_OUT");
	input7->SetAttribute("IsPort",0);


    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);
	mode->LinkEndChild(mode4);
	mode->LinkEndChild(mode5);
	mode->LinkEndChild(mode6);
	mode->LinkEndChild(mode7);
	mode->LinkEndChild(mode8);
	mode->LinkEndChild(mode9);
	mode->LinkEndChild(mode10);
	mode->LinkEndChild(mode11);
	mode->LinkEndChild(mode12);
	mode->LinkEndChild(mode13);
	mode->LinkEndChild(mode14);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);
	inputList->LinkEndChild(input5);
	inputList->LinkEndChild(input6);
	inputList->LinkEndChild(input7);
	
	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//3010.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial3011()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode   = new TiXmlElement("Mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");
	TiXmlElement* mode2  = new TiXmlElement("mode2");
	TiXmlElement* mode3  = new TiXmlElement("mode3");
	TiXmlElement* mode4  = new TiXmlElement("mode4");
	TiXmlElement* mode5  = new TiXmlElement("mode5");
	TiXmlElement* mode6  = new TiXmlElement("mode6");
	TiXmlElement* mode7  = new TiXmlElement("mode7");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");
	TiXmlElement* input2 = new TiXmlElement("input2");
	TiXmlElement* input3 = new TiXmlElement("input3");
	TiXmlElement* input4 = new TiXmlElement("input4");
	TiXmlElement* input5 = new TiXmlElement("input5");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",3011);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","2");
	module->SetAttribute("WinSwitcherType",2);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","00010");
	mode1->SetAttribute("WinSwitcherType",2);
	mode1->SetAttribute("WinSwitcherValue","2");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2);
	mode2->SetAttribute("include","00010");
	mode2->SetAttribute("WinSwitcherType",2);
	mode2->SetAttribute("WinSwitcherValue","2");
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3);
	mode3->SetAttribute("include","11011");
	mode3->SetAttribute("WinSwitcherType",2);
	mode3->SetAttribute("WinSwitcherValue","2");
	mode3->SetAttribute("ChainLayer",0);

	mode4->SetAttribute("id",4);
	mode4->SetAttribute("include","11011");
	mode4->SetAttribute("WinSwitcherType",2);
	mode4->SetAttribute("WinSwitcherValue","2");
	mode4->SetAttribute("ChainLayer",0);

	mode5->SetAttribute("id",5);
	mode5->SetAttribute("include","00100");
	mode5->SetAttribute("WinSwitcherType",0);
	mode5->SetAttribute("WinSwitcherValue","0");
	mode5->SetAttribute("ChainLayer",0);

	mode6->SetAttribute("id",6);
	mode6->SetAttribute("include","00100");
	mode6->SetAttribute("WinSwitcherType",0);
	mode6->SetAttribute("WinSwitcherValue","0");
	mode6->SetAttribute("ChainLayer",0);

	mode7->SetAttribute("id",7);
	mode7->SetAttribute("include","00000");
	mode7->SetAttribute("WinSwitcherType",0);
	mode7->SetAttribute("WinSwitcherValue","0");
	mode7->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","2");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",5);
	input1->SetAttribute("min",0);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","0");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",MAX_INT);
	input2->SetAttribute("min",MIN_INT);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default",0);
	input3->SetAttribute("type","PARA_NUM");
	input3->SetAttribute("max",100);
	input3->SetAttribute("min",0);
	input3->SetAttribute("InOrOut","PARA_IN");
	input3->SetAttribute("IsPort",0);

	input4->SetAttribute("id",4);
	input4->SetAttribute("default",0);
	input4->SetAttribute("type","PARA_NUM");
	input4->SetAttribute("max",100);
	input4->SetAttribute("min",0);
	input4->SetAttribute("InOrOut","PARA_OUT");
	input4->SetAttribute("IsPort",0);

	input5->SetAttribute("id",5);
	input5->SetAttribute("default",0);
	input5->SetAttribute("type","PARA_LOGIC");
	input5->SetAttribute("max",1);
	input5->SetAttribute("min",0);
	input5->SetAttribute("InOrOut","PARA_OUT");
	input5->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);
	mode->LinkEndChild(mode4);
	mode->LinkEndChild(mode5);
	mode->LinkEndChild(mode6);
	mode->LinkEndChild(mode7);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);
	inputList->LinkEndChild(input5);
	
	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//3011.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial4001()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode   = new TiXmlElement("Mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");
	TiXmlElement* mode2  = new TiXmlElement("mode2");
	TiXmlElement* mode3  = new TiXmlElement("mode3");
	TiXmlElement* mode4  = new TiXmlElement("mode4");
	TiXmlElement* mode5  = new TiXmlElement("mode5");
	TiXmlElement* mode6  = new TiXmlElement("mode6");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");
	TiXmlElement* input2 = new TiXmlElement("input2");
	TiXmlElement* input3 = new TiXmlElement("input3");
	TiXmlElement* input4 = new TiXmlElement("input4");
	TiXmlElement* input5 = new TiXmlElement("input5");
	TiXmlElement* input6 = new TiXmlElement("input6");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",4001);
	module->SetAttribute("Mode",5);
	module->SetAttribute("WinSwitcherValue","0");
	module->SetAttribute("WinSwitcherType",0);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","000100");
	mode1->SetAttribute("WinSwitcherType",0);
	mode1->SetAttribute("WinSwitcherValue","0");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2);
	mode2->SetAttribute("include","000010");
	mode2->SetAttribute("WinSwitcherType",0);
	mode2->SetAttribute("WinSwitcherValue","0");
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3);
	mode3->SetAttribute("include","000001");
	mode3->SetAttribute("WinSwitcherType",0);
	mode3->SetAttribute("WinSwitcherValue","0");
	mode3->SetAttribute("ChainLayer",0);

	mode4->SetAttribute("id",4);
	mode4->SetAttribute("include","100000");
	mode4->SetAttribute("WinSwitcherType",0);
	mode4->SetAttribute("WinSwitcherValue","0");
	mode4->SetAttribute("ChainLayer",0);

	mode5->SetAttribute("id",5);
	mode5->SetAttribute("include","010000");
	mode5->SetAttribute("WinSwitcherType",0);
	mode5->SetAttribute("WinSwitcherValue","0");
	mode5->SetAttribute("ChainLayer",0);

	mode6->SetAttribute("id",6);
	mode6->SetAttribute("include","001000");
	mode6->SetAttribute("WinSwitcherType",0);
	mode6->SetAttribute("WinSwitcherValue","0");
	mode6->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","2");
	input1->SetAttribute("type","PARA_TEXT");
	input1->SetAttribute("max",0);
	input1->SetAttribute("min",0);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","0");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",MAX_INT);
	input2->SetAttribute("min",MIN_INT);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default",0);
	input3->SetAttribute("type","PARA_LOGIC");
	input3->SetAttribute("max",1);
	input3->SetAttribute("min",0);
	input3->SetAttribute("InOrOut","PARA_IN");
	input3->SetAttribute("IsPort",0);

	input4->SetAttribute("id",4);
	input4->SetAttribute("default",0);
	input4->SetAttribute("type","PARA_TEXT");
	input4->SetAttribute("max",0);
	input4->SetAttribute("min",0);
	input4->SetAttribute("InOrOut","PARA_OUT");
	input4->SetAttribute("IsPort",0);

	input5->SetAttribute("id",5);
	input5->SetAttribute("default",0);
	input5->SetAttribute("type","PARA_NUM");
	input5->SetAttribute("max",MAX_INT);
	input5->SetAttribute("min",MIN_INT);
	input5->SetAttribute("InOrOut","PARA_OUT");
	input5->SetAttribute("IsPort",0);

	input6->SetAttribute("id",6);
	input6->SetAttribute("default",0);
	input6->SetAttribute("type","PARA_LOGIC");
	input6->SetAttribute("max",1);
	input6->SetAttribute("min",0);
	input6->SetAttribute("InOrOut","PARA_OUT");
	input6->SetAttribute("IsPort",0);


    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);
	mode->LinkEndChild(mode4);
	mode->LinkEndChild(mode5);
	mode->LinkEndChild(mode6);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);
	inputList->LinkEndChild(input5);
	inputList->LinkEndChild(input6);
	
	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//4001.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial4002()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode   = new TiXmlElement("Mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");
	TiXmlElement* mode2  = new TiXmlElement("mode2");
	TiXmlElement* mode3  = new TiXmlElement("mode3");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");
	TiXmlElement* input2 = new TiXmlElement("input2");
	TiXmlElement* input3 = new TiXmlElement("input3");
	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",4002);
	module->SetAttribute("Mode",2);
	module->SetAttribute("WinSwitcherValue","0");
	module->SetAttribute("WinSwitcherType",0);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","100");
	mode1->SetAttribute("WinSwitcherType",0);
	mode1->SetAttribute("WinSwitcherValue","0");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2);
	mode2->SetAttribute("include","010");
	mode2->SetAttribute("WinSwitcherType",0);
	mode2->SetAttribute("WinSwitcherValue","0");
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3);
	mode3->SetAttribute("include","001");
	mode3->SetAttribute("WinSwitcherType",0);
	mode3->SetAttribute("WinSwitcherValue","0");
	mode3->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","0");
	input1->SetAttribute("type","PARA_TEXT");
	input1->SetAttribute("max",0);
	input1->SetAttribute("min",0);
	input1->SetAttribute("InOrOut","PARA_OUT");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","0");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",MAX_INT);
	input2->SetAttribute("min",MIN_INT);
	input2->SetAttribute("InOrOut","PARA_OUT");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default",0);
	input3->SetAttribute("type","PARA_LOGIC");
	input3->SetAttribute("max",1);
	input3->SetAttribute("min",0);
	input3->SetAttribute("InOrOut","PARA_OUT");
	input3->SetAttribute("IsPort",0);


    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//4002.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial4004()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode   = new TiXmlElement("Mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");
	TiXmlElement* mode2  = new TiXmlElement("mode2");
	TiXmlElement* mode3  = new TiXmlElement("mode3");
	TiXmlElement* mode4  = new TiXmlElement("mode4");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1    = new TiXmlElement("input1");
	TiXmlElement* input2    = new TiXmlElement("input2");
	TiXmlElement* input3    = new TiXmlElement("input3");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",4004);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","0");
	module->SetAttribute("WinSwitcherType",0);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","111");
	mode1->SetAttribute("WinSwitcherType",0);
	mode1->SetAttribute("WinSwitcherValue","0");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2);
	mode2->SetAttribute("include","111");
	mode2->SetAttribute("WinSwitcherType",0);
	mode2->SetAttribute("WinSwitcherValue","0");
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3);
	mode3->SetAttribute("include","111");
	mode3->SetAttribute("WinSwitcherType",0);
	mode3->SetAttribute("WinSwitcherValue","0");
	mode3->SetAttribute("ChainLayer",0);

	mode4->SetAttribute("id",4);
	mode4->SetAttribute("include","101");
	mode4->SetAttribute("WinSwitcherType",0);
	mode4->SetAttribute("WinSwitcherValue","0");
	mode4->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","0");
	input1->SetAttribute("type","PARA_LOGIC");
	input1->SetAttribute("max",1);
	input1->SetAttribute("min",0);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","0");
	input2->SetAttribute("type","PARA_LOGIC");
	input2->SetAttribute("max",1);
	input2->SetAttribute("min",0);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default",0);
	input3->SetAttribute("type","PARA_LOGIC");
	input3->SetAttribute("max",1);
	input3->SetAttribute("min",0);
	input3->SetAttribute("InOrOut","PARA_OUT");
	input3->SetAttribute("IsPort",0);


    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);
	mode->LinkEndChild(mode4);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//4004.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial4005()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode   = new TiXmlElement("Mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");
	TiXmlElement* mode2  = new TiXmlElement("mode2");
	TiXmlElement* mode3  = new TiXmlElement("mode3");
	TiXmlElement* mode4  = new TiXmlElement("mode4");
	TiXmlElement* mode5  = new TiXmlElement("mode5");
	TiXmlElement* mode6  = new TiXmlElement("mode6");
	TiXmlElement* mode7  = new TiXmlElement("mode7");
	TiXmlElement* mode8  = new TiXmlElement("mode8");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1    = new TiXmlElement("input1");
	TiXmlElement* input2    = new TiXmlElement("input2");
	TiXmlElement* input3    = new TiXmlElement("input3");
	TiXmlElement* input4    = new TiXmlElement("input4");
	TiXmlElement* input5    = new TiXmlElement("input5");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",4005);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","0");
	module->SetAttribute("WinSwitcherType",0);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","11001");
	mode1->SetAttribute("WinSwitcherType",0);
	mode1->SetAttribute("WinSwitcherValue","0");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2);
	mode2->SetAttribute("include","11001");
	mode2->SetAttribute("WinSwitcherType",0);
	mode2->SetAttribute("WinSwitcherValue","0");
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3);
	mode3->SetAttribute("include","11001");
	mode3->SetAttribute("WinSwitcherType",0);
	mode3->SetAttribute("WinSwitcherValue","0");
	mode3->SetAttribute("ChainLayer",0);

	mode4->SetAttribute("id",4);
	mode4->SetAttribute("include","11001");
	mode4->SetAttribute("WinSwitcherType",0);
	mode4->SetAttribute("WinSwitcherValue","0");
	mode4->SetAttribute("ChainLayer",0);

	mode5->SetAttribute("id",5);
	mode5->SetAttribute("include","11001");
	mode5->SetAttribute("WinSwitcherType",0);
	mode5->SetAttribute("WinSwitcherValue","0");
	mode5->SetAttribute("ChainLayer",0);

	mode6->SetAttribute("id",6);
	mode6->SetAttribute("include","11001");
	mode6->SetAttribute("WinSwitcherType",0);
	mode6->SetAttribute("WinSwitcherValue","0");
	mode6->SetAttribute("ChainLayer",0);

	mode7->SetAttribute("id",7);
	mode7->SetAttribute("include","11001");
	mode7->SetAttribute("WinSwitcherType",0);
	mode7->SetAttribute("WinSwitcherValue","0");
	mode7->SetAttribute("ChainLayer",0);

	mode8->SetAttribute("id",8);
	mode8->SetAttribute("include","11111");
	mode8->SetAttribute("WinSwitcherType",0);
	mode8->SetAttribute("WinSwitcherValue","0");
	mode8->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","1");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",MAX_INT);
	input1->SetAttribute("min",MIN_INT);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","1");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",MAX_INT);
	input2->SetAttribute("min",MIN_INT);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default",1);
	input3->SetAttribute("type","PARA_NUM");
	input3->SetAttribute("max",MAX_INT);
	input3->SetAttribute("min",MIN_INT);
	input3->SetAttribute("InOrOut","PARA_IN");
	input3->SetAttribute("IsPort",0);

	input4->SetAttribute("id",4);
	input4->SetAttribute("default",1);
	input4->SetAttribute("type","PARA_NUM");
	input4->SetAttribute("max",MAX_INT);
	input4->SetAttribute("min",MIN_INT);
	input4->SetAttribute("InOrOut","PARA_IN");
	input4->SetAttribute("IsPort",0);

	input5->SetAttribute("id",5);
	input5->SetAttribute("default",0);
	input5->SetAttribute("type","PARA_NUM");
	input5->SetAttribute("max",MAX_INT);
	input5->SetAttribute("min",MIN_INT);
	input5->SetAttribute("InOrOut","PARA_OUT");
	input5->SetAttribute("IsPort",0);


    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);
	mode->LinkEndChild(mode4);
	mode->LinkEndChild(mode5);
	mode->LinkEndChild(mode6);
	mode->LinkEndChild(mode7);
	mode->LinkEndChild(mode8);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);
	inputList->LinkEndChild(input5);
	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//4005.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial4006()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode   = new TiXmlElement("Mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");
	TiXmlElement* mode2  = new TiXmlElement("mode2");
	TiXmlElement* mode3  = new TiXmlElement("mode3");
	TiXmlElement* mode4  = new TiXmlElement("mode4");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1    = new TiXmlElement("input1");
	TiXmlElement* input2    = new TiXmlElement("input2");
	TiXmlElement* input3    = new TiXmlElement("input3");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",4006);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","0");
	module->SetAttribute("WinSwitcherType",0);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","101");
	mode1->SetAttribute("WinSwitcherType",0);
	mode1->SetAttribute("WinSwitcherValue","0");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2);
	mode2->SetAttribute("include","101");
	mode2->SetAttribute("WinSwitcherType",0);
	mode2->SetAttribute("WinSwitcherValue","0");
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3);
	mode3->SetAttribute("include","101");
	mode3->SetAttribute("WinSwitcherType",0);
	mode3->SetAttribute("WinSwitcherValue","0");
	mode3->SetAttribute("ChainLayer",0);

	mode4->SetAttribute("id",4);
	mode4->SetAttribute("include","111");
	mode4->SetAttribute("WinSwitcherType",0);
	mode4->SetAttribute("WinSwitcherValue","0");
	mode4->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","4.75");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",MAX_INT);
	input1->SetAttribute("min",MIN_INT);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","1");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",MAX_INT);
	input2->SetAttribute("min",MIN_INT);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default",0);
	input3->SetAttribute("type","PARA_NUM");
	input3->SetAttribute("max",MAX_INT);
	input3->SetAttribute("min",MIN_INT);
	input3->SetAttribute("InOrOut","PARA_OUT");
	input3->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);
	mode->LinkEndChild(mode4);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//4006.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial4007()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode   = new TiXmlElement("Mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");
	TiXmlElement* mode2  = new TiXmlElement("mode2");
	TiXmlElement* mode3  = new TiXmlElement("mode3");
	TiXmlElement* mode4  = new TiXmlElement("mode4");
	TiXmlElement* mode5  = new TiXmlElement("mode5");
	TiXmlElement* mode6  = new TiXmlElement("mode6");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1    = new TiXmlElement("input1");
	TiXmlElement* input2    = new TiXmlElement("input2");
	TiXmlElement* input3    = new TiXmlElement("input3");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",4007);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","0");
	module->SetAttribute("WinSwitcherType",0);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","111");
	mode1->SetAttribute("WinSwitcherType",0);
	mode1->SetAttribute("WinSwitcherValue","0");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2);
	mode2->SetAttribute("include","111");
	mode2->SetAttribute("WinSwitcherType",0);
	mode2->SetAttribute("WinSwitcherValue","0");
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3);
	mode3->SetAttribute("include","111");
	mode3->SetAttribute("WinSwitcherType",0);
	mode3->SetAttribute("WinSwitcherValue","0");
	mode3->SetAttribute("ChainLayer",0);

	mode4->SetAttribute("id",4);
	mode4->SetAttribute("include","111");
	mode4->SetAttribute("WinSwitcherType",0);
	mode4->SetAttribute("WinSwitcherValue","0");
	mode4->SetAttribute("ChainLayer",0);

	mode5->SetAttribute("id",5);
	mode5->SetAttribute("include","111");
	mode5->SetAttribute("WinSwitcherType",0);
	mode5->SetAttribute("WinSwitcherValue","0");
	mode5->SetAttribute("ChainLayer",0);

	mode6->SetAttribute("id",6);
	mode6->SetAttribute("include","111");
	mode6->SetAttribute("WinSwitcherType",0);
	mode6->SetAttribute("WinSwitcherValue","0");
	mode6->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","1");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",MAX_INT);
	input1->SetAttribute("min",MIN_INT);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","1");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",MAX_INT);
	input2->SetAttribute("min",MIN_INT);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default",0);
	input3->SetAttribute("type","PARA_LOGIC");
	input3->SetAttribute("max",1);
	input3->SetAttribute("min",0);
	input3->SetAttribute("InOrOut","PARA_OUT");
	input3->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);
	mode->LinkEndChild(mode4);
	mode->LinkEndChild(mode5);
	mode->LinkEndChild(mode6);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//4007.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial4008()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode   = new TiXmlElement("Mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");
	TiXmlElement* mode2  = new TiXmlElement("mode2");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1    = new TiXmlElement("input1");
	TiXmlElement* input2    = new TiXmlElement("input2");
	TiXmlElement* input3    = new TiXmlElement("input3");
	TiXmlElement* input4    = new TiXmlElement("input4");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",4008);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","0");
	module->SetAttribute("WinSwitcherType",0);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","1111");
	mode1->SetAttribute("WinSwitcherType",0);
	mode1->SetAttribute("WinSwitcherValue","0");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2);
	mode2->SetAttribute("include","1111");
	mode2->SetAttribute("WinSwitcherType",0);
	mode2->SetAttribute("WinSwitcherValue","0");
	mode2->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","50");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",MAX_INT);
	input1->SetAttribute("min",MIN_INT);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","25");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",MAX_INT);
	input2->SetAttribute("min",MIN_INT);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default","75");
	input3->SetAttribute("type","PARA_NUM");
	input3->SetAttribute("max",MAX_INT);
	input3->SetAttribute("min",MIN_INT);
	input3->SetAttribute("InOrOut","PARA_OUT");
	input3->SetAttribute("IsPort",0);

	input4->SetAttribute("id",4);
	input4->SetAttribute("default",0);
	input4->SetAttribute("type","PARA_LOGIC");
	input4->SetAttribute("max",1);
	input4->SetAttribute("min",0);
	input4->SetAttribute("InOrOut","PARA_OUT");
	input4->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);
	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//4008.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial4009()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode   = new TiXmlElement("Mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1    = new TiXmlElement("input1");
	TiXmlElement* input2    = new TiXmlElement("input2");
	TiXmlElement* input3    = new TiXmlElement("input3");
	TiXmlElement* input4    = new TiXmlElement("input4");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",4009);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","0");
	module->SetAttribute("WinSwitcherType",0);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","1111");
	mode1->SetAttribute("WinSwitcherType",0);
	mode1->SetAttribute("WinSwitcherValue","0");
	mode1->SetAttribute("ChainLayer",0);


	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","");
	input1->SetAttribute("type","PARA_TEXT");
	input1->SetAttribute("max",0);
	input1->SetAttribute("min",0);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","");
	input2->SetAttribute("type","PARA_TEXT");
	input2->SetAttribute("max",0);
	input2->SetAttribute("min",0);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default","");
	input3->SetAttribute("type","PARA_TEXT");
	input3->SetAttribute("max",0);
	input3->SetAttribute("min",0);
	input3->SetAttribute("InOrOut","PARA_IN");
	input3->SetAttribute("IsPort",0);

	input4->SetAttribute("id",4);
	input4->SetAttribute("default",0);
	input4->SetAttribute("type","PARA_TEXT");
	input4->SetAttribute("max",0);
	input4->SetAttribute("min",0);
	input4->SetAttribute("InOrOut","PARA_OUT");
	input4->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);
	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//4009.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial4010()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode   = new TiXmlElement("Mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");
	TiXmlElement* mode2  = new TiXmlElement("mode2");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1    = new TiXmlElement("input1");
	TiXmlElement* input2    = new TiXmlElement("input2");
	TiXmlElement* input3    = new TiXmlElement("input3");
	TiXmlElement* input4    = new TiXmlElement("input4");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",4010);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","0");
	module->SetAttribute("WinSwitcherType",0);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","1101");
	mode1->SetAttribute("WinSwitcherType",0);
	mode1->SetAttribute("WinSwitcherValue","0");
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2); 
	mode2->SetAttribute("include","0011");
	mode2->SetAttribute("WinSwitcherType",0);
	mode2->SetAttribute("WinSwitcherValue","0");
	mode2->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","1");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",MAX_INT);
	input1->SetAttribute("min",MIN_INT);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","10");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",MAX_INT);
	input2->SetAttribute("min",MIN_INT);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default","50");
	input3->SetAttribute("type","PARA_NUM");
	input3->SetAttribute("max",MAX_INT);
	input3->SetAttribute("min",MIN_INT);
	input3->SetAttribute("InOrOut","PARA_IN");
	input3->SetAttribute("IsPort",0);

	input4->SetAttribute("id",4);
	input4->SetAttribute("default",0);
	input4->SetAttribute("type","PARA_NUM");
	input4->SetAttribute("max",MAX_INT);
	input4->SetAttribute("min",MIN_INT);
	input4->SetAttribute("InOrOut","PARA_OUT");
	input4->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);
	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//4010.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial5001()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode   = new TiXmlElement("Mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");
	TiXmlElement* mode2  = new TiXmlElement("mode2");
	TiXmlElement* mode3  = new TiXmlElement("mode3");
	TiXmlElement* mode4  = new TiXmlElement("mode4");
	TiXmlElement* mode5  = new TiXmlElement("mode5");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1    = new TiXmlElement("input1");
	TiXmlElement* input2    = new TiXmlElement("input2");
	TiXmlElement* input3    = new TiXmlElement("input3");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",5001);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","abc");
	module->SetAttribute("WinSwitcherType",8);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","001");
	mode1->SetAttribute("WinSwitcherValue","abc");
	mode1->SetAttribute("WinSwitcherType",8);
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2); 
	mode2->SetAttribute("include","010");
	mode2->SetAttribute("WinSwitcherValue","abc");
	mode2->SetAttribute("WinSwitcherType",8);
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3); 
	mode3->SetAttribute("include","100");
	mode3->SetAttribute("WinSwitcherValue","abc");
	mode3->SetAttribute("WinSwitcherType",8);
	mode3->SetAttribute("ChainLayer",0);

	mode4->SetAttribute("id",4); 
	mode4->SetAttribute("include","000");
	mode4->SetAttribute("WinSwitcherValue","abc");
	mode4->SetAttribute("WinSwitcherType",8);
	mode4->SetAttribute("ChainLayer",0);

	mode5->SetAttribute("id",5); 
	mode5->SetAttribute("include","000");
	mode5->SetAttribute("WinSwitcherValue","abc");
	mode5->SetAttribute("WinSwitcherType",8);
	mode5->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","");
	input1->SetAttribute("type","PARA_TEXT");
	input1->SetAttribute("max",0);
	input1->SetAttribute("min",0);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","0");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",MAX_INT);
	input2->SetAttribute("min",MIN_INT);
	input2->SetAttribute("InOrOut","PARA_OUT");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default","");
	input3->SetAttribute("type","PARA_TEXT");
	input3->SetAttribute("max",0);
	input3->SetAttribute("min",0);
	input3->SetAttribute("InOrOut","PARA_OUT");
	input3->SetAttribute("IsPort",0);


    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);
	mode->LinkEndChild(mode4);
	mode->LinkEndChild(mode5);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//5001.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial5003()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode   = new TiXmlElement("Mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");
	TiXmlElement* mode2  = new TiXmlElement("mode2");
	TiXmlElement* mode3  = new TiXmlElement("mode3");
	TiXmlElement* mode4  = new TiXmlElement("mode4");
	TiXmlElement* mode5  = new TiXmlElement("mode5");
	TiXmlElement* mode6  = new TiXmlElement("mode6");
	TiXmlElement* mode7  = new TiXmlElement("mode7");
	TiXmlElement* mode8  = new TiXmlElement("mode8");
	TiXmlElement* mode9  = new TiXmlElement("mode9");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1    = new TiXmlElement("input1");
	TiXmlElement* input2    = new TiXmlElement("input2");
	TiXmlElement* input3    = new TiXmlElement("input3");
	TiXmlElement* input4    = new TiXmlElement("input4");
	TiXmlElement* input5    = new TiXmlElement("input5");
	TiXmlElement* input6    = new TiXmlElement("input6");
	TiXmlElement* input7    = new TiXmlElement("input7");
	TiXmlElement* input8    = new TiXmlElement("input8");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",5003);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","abc");
	module->SetAttribute("WinSwitcherType",4);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","11100000");
	mode1->SetAttribute("WinSwitcherValue","abc");
	mode1->SetAttribute("WinSwitcherType",4);
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2); 
	mode2->SetAttribute("include","11100000");
	mode2->SetAttribute("WinSwitcherValue","abc");
	mode2->SetAttribute("WinSwitcherType",4);
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3); 
	mode3->SetAttribute("include","11100000");
	mode3->SetAttribute("WinSwitcherValue","abc");
	mode3->SetAttribute("WinSwitcherType",4);
	mode3->SetAttribute("ChainLayer",0);

	mode4->SetAttribute("id",4); 
	mode4->SetAttribute("include","10000010");
	mode4->SetAttribute("WinSwitcherValue","abc");
	mode4->SetAttribute("WinSwitcherType",4);
	mode4->SetAttribute("ChainLayer",0);

	mode5->SetAttribute("id",5); 
	mode5->SetAttribute("include","10000010");
	mode5->SetAttribute("WinSwitcherValue","abc");
	mode5->SetAttribute("WinSwitcherType",4);
	mode5->SetAttribute("ChainLayer",0);

	mode6->SetAttribute("id",6); 
	mode6->SetAttribute("include","10000010");
	mode6->SetAttribute("WinSwitcherValue","abc");
	mode6->SetAttribute("WinSwitcherType",4);
	mode6->SetAttribute("ChainLayer",0);

	mode7->SetAttribute("id",7); 
	mode7->SetAttribute("include","10010111");
	mode7->SetAttribute("WinSwitcherValue","abc");
	mode7->SetAttribute("WinSwitcherType",4);
	mode7->SetAttribute("ChainLayer",0);

	mode8->SetAttribute("id",8); 
	mode8->SetAttribute("include","10011011");
	mode8->SetAttribute("WinSwitcherValue","abc");
	mode8->SetAttribute("WinSwitcherType",4);
	mode8->SetAttribute("ChainLayer",0);

	mode9->SetAttribute("id",9); 
	mode9->SetAttribute("include","10000011");
	mode9->SetAttribute("WinSwitcherValue","abc");
	mode9->SetAttribute("WinSwitcherType",4);
	mode9->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","abc");
	input1->SetAttribute("type","PARA_TEXT");
	input1->SetAttribute("max",0);
	input1->SetAttribute("min",0);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","0");
	input2->SetAttribute("type","PARA_TEXT");
	input2->SetAttribute("max",MAX_INT);
	input2->SetAttribute("min",MIN_INT);
	input2->SetAttribute("InOrOut","PARA_IN");
	input2->SetAttribute("IsPort",0);

	input3->SetAttribute("id",3);
	input3->SetAttribute("default","0");
	input3->SetAttribute("type","PARA_TEXT");
	input3->SetAttribute("max",0);
	input3->SetAttribute("min",0);
	input3->SetAttribute("InOrOut","PARA_IN");
	input3->SetAttribute("IsPort",0);

	input4->SetAttribute("id",4);
	input4->SetAttribute("default","4");
	input4->SetAttribute("type","PARA_NUM");
	input4->SetAttribute("max",0);
	input4->SetAttribute("min",0);
	input4->SetAttribute("InOrOut","PARA_IN");
	input4->SetAttribute("IsPort",0);

	input5->SetAttribute("id",5);
	input5->SetAttribute("default","50");
	input5->SetAttribute("type","PARA_NUM");
	input5->SetAttribute("max",0);
	input5->SetAttribute("min",0);
	input5->SetAttribute("InOrOut","PARA_IN");
	input5->SetAttribute("IsPort",0);

	input6->SetAttribute("id",6);
	input6->SetAttribute("default","");
	input6->SetAttribute("type","PARA_TEXT");
	input6->SetAttribute("max",0);
	input6->SetAttribute("min",0);
	input6->SetAttribute("InOrOut","PARA_IN");
	input6->SetAttribute("IsPort",0);

	input7->SetAttribute("id",7);
	input7->SetAttribute("default","");
	input7->SetAttribute("type","PARA_TEXT");
	input7->SetAttribute("max",0);
	input7->SetAttribute("min",0);
	input7->SetAttribute("InOrOut","PARA_OUT");
	input7->SetAttribute("IsPort",0);

	input8->SetAttribute("id",8);
	input8->SetAttribute("default","");
	input8->SetAttribute("type","PARA_TEXT");
	input8->SetAttribute("max",0);
	input8->SetAttribute("min",0);
	input8->SetAttribute("InOrOut","PARA_OUT");
	input8->SetAttribute("IsPort",0);


    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);
	mode->LinkEndChild(mode4);
	mode->LinkEndChild(mode5);
	mode->LinkEndChild(mode6);
	mode->LinkEndChild(mode7);
	mode->LinkEndChild(mode8);
	mode->LinkEndChild(mode9);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);
	inputList->LinkEndChild(input3);
	inputList->LinkEndChild(input4);
	inputList->LinkEndChild(input5);
	inputList->LinkEndChild(input6);
	inputList->LinkEndChild(input7);
	inputList->LinkEndChild(input8);
	
	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//5003.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial5004()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode   = new TiXmlElement("Mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");
	TiXmlElement* mode2  = new TiXmlElement("mode2");
	TiXmlElement* mode3  = new TiXmlElement("mode3");
	TiXmlElement* mode4  = new TiXmlElement("mode4");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");
 	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",5004);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","");
	module->SetAttribute("WinSwitcherType",0);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","0");
	mode1->SetAttribute("WinSwitcherValue","");
	mode1->SetAttribute("WinSwitcherType",0);
	mode1->SetAttribute("ChainLayer",0);

	mode2->SetAttribute("id",2); 
	mode2->SetAttribute("include","0");
	mode2->SetAttribute("WinSwitcherValue","");
	mode2->SetAttribute("WinSwitcherType",0);
	mode2->SetAttribute("ChainLayer",0);

	mode3->SetAttribute("id",3); 
	mode3->SetAttribute("include","1");
	mode3->SetAttribute("WinSwitcherValue","");
	mode3->SetAttribute("WinSwitcherType",0);
	mode3->SetAttribute("ChainLayer",0);

	mode4->SetAttribute("id",4); 
	mode4->SetAttribute("include","1");
	mode4->SetAttribute("WinSwitcherValue","");
	mode4->SetAttribute("WinSwitcherType",0);
	mode4->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","");
	input1->SetAttribute("type","PARA_TEXT");
	input1->SetAttribute("max",0);
	input1->SetAttribute("min",0);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);
    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);
	mode->LinkEndChild(mode2);
	mode->LinkEndChild(mode3);
	mode->LinkEndChild(mode4);

	inputList->LinkEndChild(input1);
	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//5004.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial5005()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode   = new TiXmlElement("Mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",5005);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","");
	module->SetAttribute("WinSwitcherType",0);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","1");
	mode1->SetAttribute("WinSwitcherValue","");
	mode1->SetAttribute("WinSwitcherType",0);
	mode1->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","0");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",MAX_INT);
	input1->SetAttribute("min",MIN_INT);
	input1->SetAttribute("InOrOut","PARA_OUT");
	input1->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);

	inputList->LinkEndChild(input1);

	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//5005.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial5006()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode   = new TiXmlElement("Mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");
	TiXmlElement* input2 = new TiXmlElement("input2");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",5006);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","");
	module->SetAttribute("WinSwitcherType",0);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","1");
	mode1->SetAttribute("WinSwitcherValue","");
	mode1->SetAttribute("WinSwitcherType",0);
	mode1->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","1");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",MAX_INT);
	input1->SetAttribute("min",MIN_INT);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

	input2->SetAttribute("id",2);
	input2->SetAttribute("default","0");
	input2->SetAttribute("type","PARA_NUM");
	input2->SetAttribute("max",MAX_INT);
	input2->SetAttribute("min",MIN_INT);
	input2->SetAttribute("InOrOut","PARA_OUT");
	input2->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);

	inputList->LinkEndChild(input1);
	inputList->LinkEndChild(input2);

	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//5006.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial5007()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode   = new TiXmlElement("Mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",5007);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","A");
	module->SetAttribute("WinSwitcherType",2);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","1");
	mode1->SetAttribute("WinSwitcherValue","A");
	mode1->SetAttribute("WinSwitcherType",2);
	mode1->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","50");
	input1->SetAttribute("type","PARA_NUM");
	input1->SetAttribute("max",MAX_INT);
	input1->SetAttribute("min",MIN_INT);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);

	inputList->LinkEndChild(input1);

	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//5007.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial5008()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode   = new TiXmlElement("Mode");
	TiXmlElement* mode1  = new TiXmlElement("mode1");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");
	TiXmlElement* input1 = new TiXmlElement("input1");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",5008);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","A");
	module->SetAttribute("WinSwitcherType",2);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute
	mode1->SetAttribute("id",1); 
	mode1->SetAttribute("include","1");
	mode1->SetAttribute("WinSwitcherValue","A");
	mode1->SetAttribute("WinSwitcherType",2);
	mode1->SetAttribute("ChainLayer",0);

	//input attribute
	input1->SetAttribute("id",1);
	input1->SetAttribute("default","1");
	input1->SetAttribute("type","PARA_LOGIC");
	input1->SetAttribute("max",1);
	input1->SetAttribute("min",0);
	input1->SetAttribute("InOrOut","PARA_IN");
	input1->SetAttribute("IsPort",0);

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	
	mode->LinkEndChild(mode1);

	inputList->LinkEndChild(input1);

	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//5008.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::initial5009()
{
	TiXmlDocument doc;
	//declare
	TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");                    
	doc.LinkEndChild(dec);    

	//***************generate Xml element*************
	//module
	TiXmlElement* module = new TiXmlElement("Moudule");

	//mode
	TiXmlElement* mode   = new TiXmlElement("Mode");

	//input
	TiXmlElement* inputList = new TiXmlElement("InputList");

	//***************set attribute********************
	//current attribute
	module->SetAttribute("typeid",5009);
	module->SetAttribute("Mode",1);
	module->SetAttribute("WinSwitcherValue","");
	module->SetAttribute("WinSwitcherType",0);
	module->SetAttribute("ChainLayer",0);

	//Mode attribute

	//input attribute

    //***************link all the element*************
	doc.LinkEndChild(module);
	
	module->LinkEndChild(mode);
	module->LinkEndChild(inputList);
	

	//控制台输出调试
	dump_to_stdout(&doc);
    if(doc.SaveFile(".//logicXmls//5009.xml"))
		return true;
	else 
		return false;
}

bool logic_XmlIO::readInitial(const char* fileName,std::map <int, logic_BasicModule *> &InitModuleMap)
{
	//initial this map
	logic_BasicModule* currentModule = new logic_BasicModule;
	std::vector<logic_ParaPointer*> modeMenu;
	std::vector<logic_BasicPara*> paraList;

	try
	{
		TiXmlDocument* InitialXml = new TiXmlDocument(fileName);
		
		InitialXml->LoadFile();
		TiXmlElement* root = InitialXml->RootElement();
		//Initial Module Attributes
		if(root->FirstAttribute())
		{
			for(TiXmlAttribute* rootAttribute = root->FirstAttribute();rootAttribute;rootAttribute = rootAttribute = rootAttribute->Next())
			{
				fillModule(currentModule,rootAttribute->Name(),rootAttribute->Value());
			}
		}

		TiXmlHandle docHandle(root);
		TiXmlElement* child = docHandle.FirstChildElement().ToElement();

		//test if is ok
		for(child;child!=NULL;child=child->NextSiblingElement())
		{
			//mode layer
			if(child->FirstChildElement())
			{
				for(TiXmlElement* leave = child->FirstChildElement()->ToElement();leave;leave = leave->NextSiblingElement())
				{
					//traverse every mode
					logic_ParaPointer* modeTmp = new logic_ParaPointer;
					if(leave->FirstAttribute())
					{
						//travers every attributes
						for(TiXmlAttribute* currentAttribute = leave->FirstAttribute();currentAttribute;currentAttribute = currentAttribute->Next())
						{
							fillMode(modeTmp,currentAttribute->Name(),currentAttribute->Value());
						}
					}
					modeMenu.push_back(modeTmp);
				}
			}
			
			//InputList layer
			if(child->NextSiblingElement())
			{
				child = child->NextSiblingElement();
				//traverse InputList leaves
				if(child->FirstChildElement())
				{
					for(TiXmlElement* leave = child->FirstChildElement()->ToElement();leave;leave = leave->NextSiblingElement())
					{
						logic_BasicPara* paraTmp = new logic_BasicPara;
						if(leave->FirstAttribute())
						{
							for(TiXmlAttribute* attributeTmp = leave->FirstAttribute();attributeTmp;attributeTmp = attributeTmp->Next())
							{
								fillPara(paraTmp,attributeTmp->Name(),attributeTmp->Value());
							}
						}
						paraList.push_back(paraTmp);
					}
				}
			}
		}
		
		currentModule->mvvu_ModeMenu = modeMenu;
		currentModule->mvvu_ParaList = paraList;
		
		int id = currentModule->mvs_ModuleType;
		InitModuleMap[id] = currentModule;
	}
	catch(std::string& e)
	{
		return false;
	}
	return true;
}

void logic_XmlIO::testAllModule(std::map <int, logic_BasicModule *> &InitModuleMap)
{
	//test if initial has problem
	if(!InitModuleMap.empty())
	{
		std::ofstream fileOut;
		fileOut.open("testXml//testAllModules.txt");
		for(auto index = InitModuleMap.begin();index!=InitModuleMap.end();++index)
		{
			auto moduleId = index->first;
			logic_BasicModule* modulePtr = index->second;
			fileOut<<"Module's id is "<<moduleId<<std::endl;
			fileOut<<"Current mode id is "<<modulePtr->mvi_CurModeID<<std::endl;
			auto swithcer = modulePtr->mve_CurWinSwitcher.mve_WSType;
			fileOut<<"Current switcher type is "<<swithcer<<std::endl;
			auto swiValue = modulePtr->mve_CurWinSwitcher.mvs_WSValue;
			fileOut<<"switcher value is "<<swiValue<<std::endl;
			auto swiChain = modulePtr->mve_CurWinSwitcher.mvi_ChainLayer;
			fileOut<<"chainlayer"<<swiChain<<std::endl;
			
			std::vector <logic_ParaPointer *> ModeMenu = modulePtr->mvvu_ModeMenu; 
			std::vector <logic_BasicPara *> ParaList = modulePtr->mvvu_ParaList;
	
			for(auto everyParaPtr:ModeMenu)
			{
				fileOut<<"The mode id is "<<everyParaPtr->mvi_ParaPtrID<<"\t";
				fileOut<<"ID List : "<<std::endl;
				for(auto indexList:everyParaPtr->mvvi_ParaIDList)
				{
					fileOut<<indexList<<"\t";
				}
				auto winSwitcher = everyParaPtr->mve_WS;
				auto type = winSwitcher.mve_WSType;
				auto value = winSwitcher.mvs_WSValue;
				auto chainLayer = winSwitcher.mvi_ChainLayer;
				
				fileOut<<"type is "<< type <<" value is "<<value<<" chainLayer is "<< chainLayer<<std::endl;
			}
	
			for(auto everyBasicParaPtr:ParaList)
			{
				auto paraID = everyBasicParaPtr->mvi_ParaID;
				auto paraIOType = everyBasicParaPtr->mve_IOType;
				auto paraType = everyBasicParaPtr->mve_ParaType;
				auto paraValue = everyBasicParaPtr->mvs_Value;
				auto min = everyBasicParaPtr->mvd_Min;
				auto max = everyBasicParaPtr->mvd_Max;
				auto isInPort = everyBasicParaPtr->mvb_IsInport;
	
				fileOut<<"para id is "<<paraID<<std::endl;
				fileOut<<"ID IO type is "<<paraIOType<<"\t";
				fileOut<<"para type is "<<paraType<<"\t";
				fileOut<<"para value is "<<paraValue<<"\t";
				fileOut<<"max value is "<<max<<"\t";
				fileOut<<"min value is "<<min<<"\t";
				fileOut<<"Is In port "<<isInPort<<std::endl;
			}
		}
		fileOut.close();
	}
	else
	{
		std::cout<<"The map is empty"<<std::endl;
	}
}

void logic_XmlIO::fillMode(logic_ParaPointer* mode,const std::string name, std::string value)
	{
		if(name == "id")
		{
			mode->mvi_ParaPtrID = stringToInt(value);
		}
		else if(name == "include")
		{
			mode->mvvi_ParaIDList = parseInputList(value);
		}
		else if(name == "WinSwitcherType")
		{
			int selector = stringToInt(value);
			switch(selector)
			{
			case 0:
				mode->mve_WS.mve_WSType = WS_NONE;
				break;
			case 1:
				mode->mve_WS.mve_WSType = WS_NAME;
				break;
			case 2:
				mode->mve_WS.mve_WSType = WS_PORT_SINGLE;
				break;
			case 3:
				mode->mve_WS.mve_WSType = WS_PORT_DOUBLE;
				break;		
			case 4:
				mode->mve_WS.mve_WSType = WS_VALUE_TEXT;
				break;
			case 5:
				mode->mve_WS.mve_WSType = WS_VALUE_INT;
				break;
			case 6:
				mode->mve_WS.mve_WSType = WS_VALUE_DOUBLE;
				break;
			case 7:
				mode->mve_WS.mve_WSType = WS_VALUE_BOOL;
				break;
			case 8:
				mode->mve_WS.mve_WSType = WS_FILE_PATH;
				break;
			case 9:
				mode->mve_WS.mve_WSType = WS_INPORT;
				break;
			default:
				std::cout<<"save WinSwitcherType finds error!!!"<<std::endl;
				break;
			}
		}
		else if(name == "WinSwitcherValue")
		{
			mode->mve_WS.mvs_WSValue = value;
		}
		else if(name == "ChainLayer")
		{
			mode->mve_WS.mvi_ChainLayer = stringToInt(value);
		}
		else
		{
			std::cout<<"saveMode finds errors!!!"<<std::endl;
		}
	}

void logic_XmlIO::fillModule(logic_BasicModule* currentModule,const std::string name, std::string value)
	{
		if(name == "typeid")
		{
			currentModule->mvs_ModuleType = stringToInt(value);
		}
		else if(name == "WinSwitcherValue")
		{
			currentModule->mve_CurWinSwitcher.mvs_WSValue = value;
		}
		else if(name == "Mode")
		{
			currentModule->mvi_CurModeID = stringToInt(value);
		}
		else if(name == "WinSwitcherType")
		{
			int selector = stringToInt(value);
			switch(selector)
			{
			case 0:
				currentModule->mve_CurWinSwitcher.mve_WSType = WS_NONE;
				break;
			case 1:
				currentModule->mve_CurWinSwitcher.mve_WSType = WS_NAME;
				break;
			case 2:
				currentModule->mve_CurWinSwitcher.mve_WSType = WS_PORT_SINGLE;
				break;
			case 3:
				currentModule->mve_CurWinSwitcher.mve_WSType = WS_PORT_DOUBLE;
				break;		
			case 4:
				currentModule->mve_CurWinSwitcher.mve_WSType = WS_VALUE_TEXT;
				break;
			case 5:
				currentModule->mve_CurWinSwitcher.mve_WSType = WS_VALUE_INT;
				break;
			case 6:
				currentModule->mve_CurWinSwitcher.mve_WSType = WS_VALUE_DOUBLE;
				break;
			case 7:
				currentModule->mve_CurWinSwitcher.mve_WSType = WS_VALUE_BOOL;
				break;
			case 8:
				currentModule->mve_CurWinSwitcher.mve_WSType = WS_FILE_PATH;
				break;
			case 9:
				currentModule->mve_CurWinSwitcher.mve_WSType = WS_INPORT;
				break;
			default:
				std::cout<<"save WinSwitcherType finds error!!!"<<std::endl;
				break;
			}
		}
		else if(name =="ChainLayer")
		{
			currentModule->mve_CurWinSwitcher.mvi_ChainLayer = stringToInt(value);
		}
		else 
		{
			std::cout<<"saveModule finds errors!!!"<<std::endl;
		}
	}

void logic_XmlIO::fillPara(logic_BasicPara* para,const std::string name,const std::string value)
	{
		if(name == "id")
		{
			para->mvi_ParaID = stringToInt(value);
		}
		else if(name == "default")
		{
			para->mvs_Value = value;
		}
		else if(name == "type")
		{
			if(value == "PARA_LOGIC")
				para->mve_ParaType = PARA_LOGIC;
			else if(value == "PARA_NUM")
				para->mve_ParaType = PARA_NUM;
			else if(value == "PARA_TEXT")
				para->mve_ParaType  = PARA_TEXT;
			else
			{
				std::cout<<"find error in save type"<<std::endl;
			}
		}
		else if(name == "max")
		{
			para->mvd_Max = stringToInt(value);
		}
		else if(name == "min")
		{
			para->mvd_Min = stringToInt(value);
		}
		else if(name == "InOrOut")
		{
			if(value == "PARA_IN")
			para->mve_IOType = PARA_IN;
			else if(value == "PARA_OUT")
				para->mve_IOType = PARA_OUT;
			else 
			{
				std::cout<<"find error in save InOrOut"<<std::endl;
			}
		}
		else if(name == "IsPort")
		{
			if(value == "0")
				para->mvb_IsInport = false;
			else if(value == "1")
				para->mvb_IsInport = true;
			else 
			{
				std::cout<<"find error in save IsInPort"<<std::endl;
			}
		}
		else
		{
			std::cout<<"save Para finds problem!!"<<std::endl;
		}

	}

void logic_XmlIO::fillProject(logic_Project &prj,const std::string name, std::string value)
	{
		if(name == "Name")
		{
			prj.setPrjName(value);
		}
		else if(name == "Photo_Path")
		{
			prj.setPrjPhotoPath(value);
		}
		else if(name == "Project_Description")
		{
			prj.setPrjDescription(value);
		}
		else
		{
			std::cout<<"Something wrong in saveProject "<<std::endl;
		}
	}

void logic_XmlIO::fillProgram(std::map<int,logic_Program*> &prgMap,TiXmlElement* firstPrgChild)
{
	for(firstPrgChild;firstPrgChild;firstPrgChild = firstPrgChild->NextSiblingElement())
	{
		int prgId = firstPrgChild->FirstAttribute()->IntValue();                          //program id
		std::string name = firstPrgChild->FirstAttribute()->Next()->Value();      //program name
		logic_Program* program = new logic_Program(prgId,name);
		std::map<whPort, whPort > fromToMap;     //连线map
		std::map<whPort, whPort > toFromMap;     //连线map

		//traverse all the tree to initial treeMap
		if(firstPrgChild->FirstChildElement()) 
		{   
			for(auto treeRoot = firstPrgChild->FirstChildElement();treeRoot;treeRoot = treeRoot->NextSiblingElement())                       //TreeRoot层
			{
				std::string name = treeRoot->Value();

				if(name == "TreeRoot")
				{
					int rootId = treeRoot->FirstAttribute()->IntValue();
					logic_Tree* tree = new logic_Tree(rootId);
					program->add_Tree(tree);

					//initial the tree node
					//std::vector<logic_TreeNode*> nodeMap;
					
					if(treeRoot->FirstChild())
					{
						std::vector<TreeNode*> allNode;
						for(TiXmlElement* treeNode = treeRoot->FirstChild()->ToElement();treeNode;treeNode = treeNode->NextSiblingElement())          //treenode层
						{
							auto nodeIdAttribute = treeNode->FirstAttribute();
							auto fatherIdAttribute = nodeIdAttribute->Next();
							auto moduleTypeAttribute = fatherIdAttribute->Next();
							auto currentModeTypeAttribute = moduleTypeAttribute->Next();
							TiXmlAttribute* forNameAttribute = new TiXmlAttribute();
							TiXmlAttribute* forAllRootStringAttribute = new TiXmlAttribute();
							std::string forName;
							std::string forAllRootString;
							if(currentModeTypeAttribute->Next())    //如果是for或者if模块
							{
								forNameAttribute = currentModeTypeAttribute->Next();
								forAllRootStringAttribute = forNameAttribute->Next();
								forName = forNameAttribute->Value();                     //for的名称
								forAllRootString = forAllRootStringAttribute->Value();   //for中包含的所有的tree根节点key
							}
							else                                    //不是的话就析构
							{
								delete forNameAttribute;
								delete forAllRootStringAttribute;
							}



							//模块信息
							int nodeID = nodeIdAttribute->IntValue();                     //模块ID
							int fatherID = fatherIdAttribute->IntValue();                 //父亲节点ID
							int moduleType = moduleTypeAttribute->IntValue();			  //模块类型
							int currentModeType = currentModeTypeAttribute->IntValue();	  //模块当前模式

							//还原模块信息,注意要深拷贝
							logic_BasicModule* moduleNode = new logic_BasicModule();
							//深拷贝
							moduleNode->mvi_CurModeID = allModuleMap[moduleType]->mvi_CurModeID;
							moduleNode->mvs_ModuleType = allModuleMap[moduleType]->mvs_ModuleType;
							moduleNode->mvvu_ModeMenu = allModuleMap[moduleType]->mvvu_ModeMenu;
							deepCopyPara(allModuleMap[moduleType]->mvvu_ParaList,moduleNode->mvvu_ParaList);    
							moduleNode->mvvu_InitParaList = allModuleMap[moduleType]->mvvu_InitParaList;
							moduleNode->mve_CurWinSwitcher = allModuleMap[moduleType]->mve_CurWinSwitcher;
							//当前值
							moduleNode->mvi_ModuleID = nodeID;
							moduleNode->mvi_CurModeID = currentModeType;                  

							//用来还原树
							TreeNode* node = new TreeNode();
							node->id = nodeID;
							node->parentId = fatherID;
							allNode.push_back(node);

							//模块中当前模式下的参数列表与端口菊链
							std::vector <logic_BasicPara*> paraList = moduleNode->mvvu_ParaList;
							WinSwitcher* switcher = &(moduleNode->mve_CurWinSwitcher);

							//遍历参数列表
							if(treeNode->FirstChildElement())
							{
								auto paraInfo = treeNode->FirstChildElement();
								if(paraInfo->FirstChild())                               //paraInfo        
								{
									//遍历para
									for(auto paraNode = paraInfo->FirstChildElement();paraNode;paraNode = paraNode->NextSiblingElement())                     //paraInfo层
									{
										std::string name = paraNode->Value();
										if(name == "para")
										{
											if(paraNode->FirstAttribute())			             //para attribute
											{	
												int id,isInPort;
												std::string value;
												for(auto paraNodeAttribute = paraNode->FirstAttribute();paraNodeAttribute;paraNodeAttribute = paraNodeAttribute->Next())          //para层
												{
													std::string name = paraNodeAttribute->Name();
													if(name == "ID")
													{
														id = paraNodeAttribute->IntValue();
													}
													else if(name == "value")
													{
														value = paraNodeAttribute->Value();
													}
													else if(name == "isInPort")
													{
														isInPort = paraNodeAttribute->IntValue();
													}

												}					
												paraList[id-1]->mvs_Value = value;
												paraList[id-1]->mvb_IsInport = isInPort;
 											}
										}
										else if(name == "switcher")
										{
											if(paraNode->FirstAttribute())			             //switcher attribute
											{
												std::string value;
												int chainLayer;	
												for(auto paraNodeAttribute = paraNode->FirstAttribute();paraNodeAttribute;paraNodeAttribute = paraNodeAttribute->Next())          //para层
												{
													std::string name = paraNodeAttribute->Name();
													if(name == "value")
													{
														value = paraNodeAttribute->Value();
													}
													else if(name == "chainLayer")
													{
														chainLayer = paraNodeAttribute->IntValue();
													}
												}						
												switcher->mvs_WSValue = value;
												switcher->mvi_ChainLayer = chainLayer;
 											}
										}

									}																																														//paraInfo层结束
									//list填充完毕，将list写入module
									moduleNode->mvvu_ParaList = paraList;
									moduleNode->mve_CurWinSwitcher = *switcher;
									if(moduleType == 2003)  //还原for模块
									{
										std::map <int,logic_Tree *> tree_map = program->getTreeMap();
										std::map <int, logic_BasicModule *> module_map = program->getModuleMap();
										std::map <int ,logic_Tree * > m_tree_map = program->getModuleTreeMap();
										std::map <logic_Tree * ,int > tree_forif_map = program->getForIfMap();
										std::map<whPort, whPort > conn_fromto_map = program->getFromMap();
										std::map<whPort, whPort > conn_tofrom_map = program->getToMap();
										

										logic_ForModule* forModule = new logic_ForModule(nodeID,
											                                             tree_map,
																						 module_map,
																						 m_tree_map,
																						 tree_forif_map,
																						 conn_fromto_map,
																						 conn_tofrom_map,
																						 *moduleNode
											);
										forModule->forName = forName;

									}
									else if(moduleType == 2004)
									{

									}
								}
							}
							//将还原的模块放入program
							program->add_Module(nodeID,moduleNode);
						}																																								//Tree层结束
						rebuildTree(tree,allNode);
					}
				}
				else if(name == "From_To")
				{
					if(treeRoot->FirstAttribute())
					{
						int module1,paraId1,module2,paraId2;
						for(auto From_To_Attribute = treeRoot->FirstAttribute();From_To_Attribute;From_To_Attribute = From_To_Attribute->Next())
						{
							std::string name = From_To_Attribute->Name();
							if(name == "moduleId1")
							{
								module1 = From_To_Attribute->IntValue();
							}
							else if(name == "paraId1")
							{
								paraId1 = From_To_Attribute->IntValue();
							}
							else if(name == "moduleId2")
							{
								module2 = From_To_Attribute->IntValue();
							}
							else if(name == "paraId2")
							{
								paraId2 = From_To_Attribute->IntValue();
							}
						}
						whPort from,to;
						from.moduleId = module1;
						from.paraId = paraId1;
						to.moduleId = module2;
						to.paraId = paraId2;
						fromToMap[from] = to;
						toFromMap[to] = from;
					}

				}

			}  //TreeRoot层结束
			//将连线的两个表放入program
			program->setFromToMap(fromToMap);
			program->setToFromMap(toFromMap);
		}
		//将program放入project
		prgMap[prgId] = program;
	}
}

bool logic_XmlIO::saveProgram(std::map<int, logic_Program*> &programMap, TiXmlElement* ProgramList)
{
	for (auto index = programMap.begin(); index != programMap.end(); ++index){
		//program指针
		auto prg = index->second;
		//program id
		TiXmlElement* program = new TiXmlElement("Program");

		//set attribute
		program->SetAttribute("id", intToString(index->first).c_str());
		program->SetAttribute("name", index->second->getName().c_str());

		//link them
		ProgramList->LinkEndChild(program);

		//tree map
		auto allTreeMap = prg->getTreeMap();
		for (auto indexOfRoot = allTreeMap.begin(); indexOfRoot != allTreeMap.end(); ++indexOfRoot){               //TreeNode层

			TiXmlElement* treeRoot = new TiXmlElement("TreeRoot");
			program->LinkEndChild(treeRoot);
			treeRoot->SetAttribute("id", indexOfRoot->first);

			//遍历树，存每个节点信息---------ID和父节点ID
			auto allNode = prg->getAllTreeNode(indexOfRoot->first);
			for (auto index = allNode.begin(); index != allNode.end(); ++index){
				TiXmlElement* node = new TiXmlElement("TreeNode");
				treeRoot->LinkEndChild(node);
				node->SetAttribute("ID", (*index)->getID());
				node->SetAttribute("fatherID", (*index)->getParentID());
				//模块信息
				auto moduleID = (*index)->getID();
				auto moduleMap = prg->getModuleMap();
				auto module = moduleMap[moduleID];
				//当前信息
				auto type = module->getModuleType();
				auto mode = module->getModeValue();
				auto paraList = module->getCurParaList();
				auto port = module->mve_CurWinSwitcher;        //当前端口选择器
				if (2003 == type)        //如果是for模块
				{
					logic_ForModule* forModule = prg->getForModuleById(moduleID);
					std::string allTreeRoot;
					std::vector<int> allRootInt = forModule->findAllRoots();
					parseRootToString(allRootInt, allTreeRoot);

					node->SetAttribute("ModuleType", type);
					node->SetAttribute("CurrentModeType", mode);
					node->SetAttribute("ForName", forModule->forName.c_str());
					node->SetAttribute("AllRoot", allTreeRoot.c_str());
				}
				else if (2004 == type)   //如果是if模块
				{
					logic_IfModule* ifModule = prg->getIfModuleById(moduleID);
					node->SetAttribute("ModuleType", type);
					node->SetAttribute("CurrentModeType", mode);
					node->SetAttribute("IfName", ifModule->IfName.c_str());
				}
				else                    //如果是非for和if模块
				{
					node->SetAttribute("ModuleType", type);
					node->SetAttribute("CurrentModeType", mode);
				}



				TiXmlElement* paraInfo = new TiXmlElement("paraInfo");
				if (!paraList.empty())
				{												//当前参数列表
					for (auto paraIndex = paraList.begin(); paraIndex != paraList.end(); ++paraIndex)
					{
						TiXmlElement* para = new TiXmlElement("para");
						para->SetAttribute("ID", (*paraIndex)->mvi_ParaID);
						para->SetAttribute("value", (*paraIndex)->mvs_Value.c_str());
						para->SetAttribute("isInPort", (*paraIndex)->mvb_IsInport);
						paraInfo->LinkEndChild(para);
					}
				}
				//当前端口
				TiXmlElement* switcher = new TiXmlElement("switcher");
				switcher->SetAttribute("value", port.mvs_WSValue.c_str());
				switcher->SetAttribute("chainLayer", port.mvi_ChainLayer);
				paraInfo->LinkEndChild(switcher);
				node->LinkEndChild(paraInfo);

			}
		} //TreeNode层结束

		//From_To层
		auto Conn_From_ToMap = prg->getFromMap();
		if (Conn_From_ToMap.size() != 0)
		{
			TiXmlElement* From_To = new TiXmlElement("From_To");
			for (auto index = Conn_From_ToMap.begin(); index != Conn_From_ToMap.end(); index++)
			{
				auto from = index->first;
				auto to = index->second;
				From_To->SetAttribute("moduleId1", from.moduleId);
				From_To->SetAttribute("paraId1", from.paraId);
				From_To->SetAttribute("moduleId2", to.moduleId);
				From_To->SetAttribute("paraId2", to.paraId);
			}
			program->LinkEndChild(From_To);
		}

	}
	return true;
}

//
//bool logic_XmlIO::IO_SaveProgram(const std::string fileName,TiXmlElement* rootElement)
//{
//	try
//	{
//		TiXmlDocument doc;
//		TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "", "");
//		doc.LinkEndChild(dec);
//		TiXmlElement* root = new TiXmlElement(rootElement->Value());       //深拷贝根元素
//		doc.LinkEndChild(root);
//		if(rootElement->FirstChild())
//		{
//			auto program = rootElement->FirstChildElement();
//			//深拷贝所有的program
//			while (program)
//			{
//				std::cout<<"The child is "<<rootElement->FirstChild()->Value()<<std::endl;
//				auto programName = rootElement->FirstChild()->Value();
//				TiXmlElement* programCopy = new TiXmlElement(programName);
//				root->LinkEndChild(programCopy);
//				//深拷贝所有的attribute
//				if(program->FirstAttribute())
//				{
//					auto attribute = program->FirstAttribute();
//					while(attribute)
//					{
//						programCopy->SetAttribute(attribute->Name(),attribute->Value());
//						attribute = attribute->Next();
//					}
//				}
//				//深拷贝所有树的子节点
//				if(program->FirstChildElement())
//				{
//					auto treeRoot = program->FirstChildElement();
//					while(treeRoot)
//					{
//						TiXmlElement* treeRootCopy = new TiXmlElement(treeRoot->Value());
//						//深拷贝所有的树根节点的属性值
//						if(treeRoot->FirstAttribute())
//						{
//							auto attribute = treeRoot->FirstAttribute();
//							while(attribute)
//							{
//								treeRootCopy->SetAttribute(attribute->Name(),attribute->Value());
//								attribute = attribute->Next();
//							}
//						}
//						//深拷贝所有树的子节点
//						if(treeRoot->FirstChildElement())
//						{
//							auto treeNode = treeRoot->FirstChildElement();
//							while(treeNode)
//							{
//								TiXmlElement* treeNodeCopy = new TiXmlElement(treeNode->Value());
//								//深拷贝所有的子根节点的属性值
//								if(treeNode->FirstAttribute())
//								{
//									auto attribute = treeNode->FirstAttribute();
//									while(attribute)
//									{
//										treeNodeCopy->SetAttribute(attribute->Name(),attribute->Value());
//										attribute = attribute->Next();
//									}
//								}
//								treeRootCopy->LinkEndChild(treeNodeCopy);
//								treeNode = treeNode->NextSiblingElement();
//							}
//
//						}
//						programCopy->LinkEndChild(treeRootCopy);
//						treeRoot = treeRoot->NextSiblingElement();
//					}
//
//				}
//
//
//
//				program = program->NextSiblingElement();
//			}
//		}
//
//
//		std::cout<<"****************************************"<<std::endl;
//		dump_to_stdout(&doc);
//		if(doc.SaveFile(fileName.c_str()))
//			return true;
//		else 
//			return false;
//	}
//	catch(std::string& e)
//	{
//		std::cout<<"Happen some error in save the program "<<std::endl;
//		return false;
//	}
//
//
//}

void logic_XmlIO::fillVarModule(logic_Project &prj,TiXmlElement* varietiesElement)
{
	int id = varietiesElement->FirstAttribute()->IntValue();
	int typeInt = varietiesElement->FirstAttribute()->Next()->IntValue();
	std::string value = varietiesElement->FirstAttribute()->Next()->Next()->Value();

	VarietyType type;
	switch (typeInt)
	{
		case 0:
			type = Text;
			break;
		case 1:
			type = Numeric;
			break;
		case 2:
			type = Boolean;
			break;
		default:
			std::cout<<"find error in variety type"<<std::endl;
			return;
			break;
	}
	logic_VarModule* variety = new logic_VarModule(id,type,value);
	prj.setPrjVariety(id,variety);

	if(varietiesElement->NextSiblingElement())
	{
		for(auto firstVar = varietiesElement->NextSiblingElement();firstVar;firstVar = firstVar->NextSiblingElement())
		{
			int id = varietiesElement->FirstAttribute()->IntValue();
			int typeInt = varietiesElement->FirstAttribute()->Next()->IntValue();
			std::string value = varietiesElement->FirstAttribute()->Next()->Next()->Value();
		
			VarietyType type;
			switch (typeInt)
			{
			case 0:
				type = Text;
				break;
			case 1:
				type = Numeric;
				break;
			case 2:
				type = Boolean;
				break;
			default:
				std::cout<<"find error in variety type"<<std::endl;
				return;
				break;
			}
			logic_VarModule* variety = new logic_VarModule(id,type,value);
			prj.setPrjVariety(id,variety);
		}

	}

}

bool logic_XmlIO::IO_Initial(std::map <int, logic_BasicModule *> &InitModuleMap)
{
	//检测文件是否存在
	if (isFileExist(allFilePaths))
	{
		for (auto index : allFilePaths)
		{
			readInitial(index, InitModuleMap);
		}
		return true;
	}
	else
	{
		return false;
	}
	
}

//项目属性中的导出文件
bool logic_XmlIO::I0_ExportProgram(const std::string fileName, logic_Program program)
{
	if (isFileExist(fileName.c_str()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//文件中导入program
bool logic_XmlIO::IO_ImportProgram(const std::string fileName, logic_Project* project)
{
	if (isFileExist(fileName.c_str()))
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool logic_XmlIO::rebuildTree(logic_Tree* treeRoot, std::vector<TreeNode*> allNode)
{
	if(allNode.empty())
	{
		return false;
	}
	else
	{
		std::map<int,logic_TreeNode*> treeNodeMap;
		for(auto index: allNode)
		{
			logic_TreeNode* node = new logic_TreeNode(index->id);
			treeNodeMap[index->id] = node;
		}
		for(auto child:allNode)
		{
			for(auto parent:allNode)
			{
				if(child->parentId == parent->id)
				{
					auto childNode = treeNodeMap[child->id];
					auto parentNode = treeNodeMap[parent->id];
					childNode->mvu_Parent = parentNode;
					parentNode->mvvu_Children.push_back(childNode);
				}
			}

		}
		treeRoot->setRoot(treeNodeMap.begin()->second);
	}

}

void logic_XmlIO::deepCopyPara(std::vector<logic_BasicPara*> copy,std::vector<logic_BasicPara*> &copyTo)
{
	for(auto index : copy)
	{
		logic_BasicPara* para = new logic_BasicPara();
		para->mvi_ParaID = index->mvi_ParaID;
		para->mve_IOType = index->mve_IOType;
		para->mve_ParaType = index->mve_ParaType;
		para->mvs_Value = index->mvs_Value;
		para->mvd_Min = index->mvd_Min;
		para->mvd_Max = index->mvd_Max;
		para->mvb_IsInport = index->mvb_IsInport;
		copyTo.push_back(para);
	}
}

bool logic_XmlIO::parseRootToString(std::vector<int> allRoot,std::string &allRootString)
{
	if(allRoot.size()!= 0)
	{
		allRootString.clear();
		for(auto rootID:allRoot)
		{
			std::string idNode = intToString(rootID);
			allRootString += idNode + "#"; 
		}

		return true;
	}
	else
		return false;
}

bool logic_XmlIO::parseRootToInt(std::vector<int>& allRoot,std::string allRootString)
{
	if(allRootString.size()!=0)
	{
		allRoot.clear();
		std::string rootInt;
		for(auto index:allRootString)
		{ 
			if (index != '#')
			{
				rootInt += index;
			}
			else
			{
				int rootId = atoi(rootInt.c_str());
				allRoot.push_back(rootId);
				rootInt.clear();
			}
		}
		return true;
	}
	else
		return false;
}

//bool isFileExist()
bool logic_XmlIO::isFileExist(std::vector<const char*> allFilePaths)
{
	bool isExisted = true;
	for (auto index : allFilePaths)
	{
		auto flag = access(index,0);
		if (flag == -1)
		{
			isExisted = false;
			std::cout << index << "is not exist!" << std::endl;
			return isExisted;
		}
	}
	return isExisted;
}

bool logic_XmlIO::isFileExist(const char* filePath)
{
	bool isExisted = true;
	auto flag = access(filePath, 0);
	if (flag == -1)
	{
		isExisted = false;
		std::cout <<"file " << filePath << " is not exist!" << std::endl;
		return isExisted;
	}

	return isExisted;
}