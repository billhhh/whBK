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


class logic_Project
{
public:
	explicit logic_Project(int id,std::string name);
	~logic_Project();


	//set and get
	int getPrjId();//project id ���ɾ��޷��ı�

	void setPrjName(const std::string name);
	std::string getPrjName();

	void setPrjDescription(const std::string description);
	std::string getPrjDescription();

	void setPrjPhotoPath(const std::string path);
	std::string getPrjPhotoPath();

	void setPrjVariety(const _IdDataType, logic_VarModule*);
	std::map<_IdDataType ,logic_VarModule*> getPrjVariety();

	//����program
	int newProgram(); //�����½�program����ȫ�Զ����½�program�������½�program ID
	void newProgram(int id,std::string name); //�����½�program��ֻ�ô���program ID �� name
	void newProgram(int id,logic_Program* program);
	logic_Program* getProgram(int id);

	//������ ProgID�������ۼ�
	int getMaxProgId();
	int getProgMaxModuleId(int prog_id);

	std::string getPrjPhotoDscrpt(); // ��XmlIO��
	std::map <int ,logic_Program* > getAllProgram();  //��XmlIO��

protected:

	void Init();
	void prj_Destroy();

private:
	/**************�������Ʊ���ѭ�����Ʊ�*****************/
	int mvstr_PrjId;              // project ID
	std::string mvstr_PrjName;    // project name
	std::string mvstr_PrjDescription;
	std::string mvstr_PhotoPath;

	//program map
	std::map <int, logic_Program *> mvvu_ProgMap;
	//�ҵı���my virable and its type
	std::map<_IdDataType ,logic_VarModule*> mvmu_PrjVariety;

	std::string genNewProgName(int id); //������ prj ������

//����private����
private:
	std::string whIntToString(int i);

};

#endif