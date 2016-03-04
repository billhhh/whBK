/* 
* 
* function: �߼��� project ��
* 
* Date:2015-09-04
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_PROJECT_H_
#define _LOGIC_PROJECT_H_

#include <map>
#include <string>
#include <stdlib.h>
#include "logic_Program.h"
#include "logic_VarModule.h"
#include "logic_BasicModule.h"
#include "logic_Gragh.h"
#include "logic_PrjPropertyGlobal.h"

class logic_Project
{
public:
	logic_Project(int id,std::string name);
	logic_Project(int id,std::string name,std::map <int, logic_BasicModule *> imap);
	~logic_Project();


	//set and get
	int getPrjId();//project id ���ɾ��޷��ı�
	void setPrjId(int id);

	std::string getPrjFilePath();//��Ŀ�ĳ־û��ļ��ĵ�ַ
	void setPrjFilePath(std::string filePath);//������Ŀ�־û��ļ��ĵ�ַ

	void setPrjName(const std::string name);
	std::string getPrjName();

	void setPrjDescription(const std::string description);
	std::string getPrjDescription();

	void setPrjPhotoPath(const std::string path);
	std::string getPrjPhotoPath();

	void setPrjVariety(const _IdDataType, logic_VarModule*);
	void setPrjVarietyMap(std::map<_IdDataType ,logic_VarModule*> PrjVariety);
	std::map<_IdDataType ,logic_VarModule*> getPrjVariety();

	//����program
	int newProgram(); //�����½�program����ȫ�Զ����½�program�������½�program ID
	void newProgram(int id,std::string name); //�����½�program��ֻ�ô���program ID �� name
	void newProgram(int id,logic_Program* program);
	void setProgram(std::map <int ,logic_Program* > programMap);
	logic_Program* getProgram(int id);
	std::string copyProgram(const std::string progName);
	bool deleteProgram(const std::string progName);//����progNameɾ����program
	void addProgram(logic_Program* prg);//importһ��program�ļ�

	//������ ProgID�������ۼ�
	int getMaxProgId();
	int getProgMaxModuleId(int prog_id);

	std::string getPrjPhotoDscrpt(); // ��XmlIO��
	std::map <int ,logic_Program* > getAllProgram();  //��XmlIO��
	bool importProgram(std::string progPath);//��XmlIO�� ����·��������һ��program

	//��ʼ�� initModule��init_m_map�Ǹ���
	void setInitModuleMap(std::map <int, logic_BasicModule *> init_m_map);

private:
	/**************�������Ʊ��ѭ�����Ʊ�*****************/
	int mvstr_PrjId;              // project ID
	std::string mvstr_PrjName;    // project name
	std::string mvstr_PrjDescription;
	std::string mvstr_PhotoPath;

	//program map
	std::map <int, logic_Program *> mvvu_ProgMap;
	//����������prjͨ�ã� my virable and its type
	std::map<_IdDataType ,logic_VarModule*> mvmu_PrjVariety;

	//!!!!!!!init module map���������еĳ�ʼ�� Module ָ�� map ����!!!!!!!
	///
	/// \brief load from xml which is on the disk
	///
	std::map <int, logic_BasicModule *> initModuleMap;

	std::map<int, logic_Gragh *> graghMap;

//����private����
private:
	void Init();
	void prj_Destroy();

	std::string whIntToString(int i);
	std::string genNewProgName(int id); //������ prj ������
	int getProgId(std::string progName); //����progname���õ�programID

	std::string projectFilePath;
};

#endif
