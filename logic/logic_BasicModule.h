/* 
* 
* function: �߼������ Module ʵ����
* 
* Date:2015-09-01
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_BASIC_MODULE_H_
#define _LOGIC_BASIC_MODULE_H_

#include <string>
#include <vector>
#include "logic_BasicPara.h"
#include "logic_WinSwitcher.h"
#include "logic_ParaPointer.h"

class logic_BasicModule
{
public:
	int mvi_ModuleID;

	/////���캯������������
	explicit logic_BasicModule();//Ĭ������start
	explicit logic_BasicModule(int id);//Ĭ������start
	explicit logic_BasicModule(int id,int moduleType); //������Ϣ���Զ����������Ϣ
	////������캯��
	explicit logic_BasicModule(int id,int moduleType,const logic_BasicModule &bm);
	virtual ~logic_BasicModule();

	/////!!! useless !!!!!!!!!!!!
	bool changeMode(int modeID,std::vector <logic_BasicPara *> & ParaReturnList); //�޸�ģʽ����ȡ�ض�ģʽ�Ĳ����б�
	bool changeParaValue(int paraID,std::string value); //�޸Ĳ���ֵ����Ҫ�޸ĵ�ǰ����Ƭ
	bool changeWinSwicher();
	////////////////////////////////

	logic_BasicPara* getPara(int p_id); //����ĳһ����������
	logic_BasicPara* getInitPara(int p_id); //����ĳһinit����������

	int getModuleType();

	WinSwitcherType getWSType(int m_modeValue);
	std::string getWSValue();
	void setWSValue(std::string ws_value);

	int getDaisyChainValue();
	void setDaisyChainValue(int chain_value);

	std::vector<int > getParamsIds(int mode_value);

	int getModeValue(); //IO �� ǰ̨����Ҫ
	void setModeValue(int mode_id); //����ģʽѡ����

	////!!!!!!!!!!!!!!!!!!!��XmlIO��!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	std::vector <logic_BasicPara*> getCurParaList(); //get ��ǰģʽ �����в���
	WinSwitcherType getCurWSType(); //�õ���ǰ �˿�ѡ���� type

	void setCurParaList(std::vector <logic_BasicPara*> paraList);

	/////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/////�ϳɴ���
	bool generateCodeBlocks();

//protected:
	int mvi_CurModeID; //��ǰģʽ
	int mvs_ModuleType; //ģ������ ����ȥxml load
	std::string mvs_CurCodeBlocks; //����Ƭ

	bool mvb_IsRun; //�Ƿ���������
	//bool mvb_IsConnectStart; //��û�и���ʼģ������

	//ģʽѡ�����ܱ���ʼ��load����
	std::vector <logic_ParaPointer *> mvvu_ModeMenu;
	std::vector <logic_BasicPara *> mvvu_ParaList; //�����б�
	std::vector <std::string > mvvu_CodeBlocksList; //����Ƭ�б�---��Ӧ��ͬģʽ

	std::vector <logic_BasicPara *> mvvu_InitParaList; //init�����б�

	//��ǰ�˿�ѡ�����������������
	WinSwitcher mve_CurWinSwitcher;

private:
	void Init(); //�����ʼ������
	void Destroy(); //������ʱ����

};

#endif // !_BASIC_MODULE_H_

