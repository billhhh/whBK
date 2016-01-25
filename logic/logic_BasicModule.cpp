#include "logic_BasicModule.h"
#include "logic_Global.h"
#include <iostream>

using namespace std;

logic_BasicModule::logic_BasicModule()
	:mvi_ModuleID(1),mvb_IsRun(0),mvs_ModuleType(2001)
{
	//默认生成start
	Init();
}

logic_BasicModule::logic_BasicModule(int id)
	:mvi_ModuleID(id),mvb_IsRun(0),mvs_ModuleType(2001)
{
	//默认生成start
	Init();
}

logic_BasicModule::logic_BasicModule(int id,int moduleType)
	:mvi_ModuleID(id),mvb_IsRun(0),mvs_ModuleType(moduleType)
{
	Init();
}

////深拷贝构造函数
logic_BasicModule::logic_BasicModule(int id,int moduleType,const logic_BasicModule &bm)
	:mvi_ModuleID(id),mvb_IsRun(0),mvs_ModuleType(moduleType)
{
	////mvvu_ModeMenu

	
	////mvvu_ParaList 和 mvvu_InitParaList

	////mve_CurWinSwitcher

	Init();
}

logic_BasicModule::~logic_BasicModule()
{
	/////释放所有modemenu和para_list
	cout<<"进入logic_BasicModule析构函数"<<endl;

	Destroy();
}

void logic_BasicModule::Init() {

	//!!!!!!!!!临时写死30个参数，用不完
// 	for (int i=0 ; i<30 ; ++i) {
// 		logic_BasicPara * tmpPara = new logic_BasicPara();
// 		mvvu_ParaList.push_back(tmpPara);
// 	}
}

void logic_BasicModule::Destroy() {

	/////释放modemenu
	for ( int i=0;i<mvvu_ModeMenu.size();++i ) {
		SAFE_DELETE(mvvu_ModeMenu.at(i));
	}

	/////释放para_list
	for ( int i=0;i<mvvu_ParaList.size();++i ) {
		SAFE_DELETE(mvvu_ParaList.at(i));
	}

}

/*/////
* brief 修改模式，获取特定模式的参数列表，供调用接口
* param modeID 传入模式选择ID
* param para_return_list 返回参数引用列表
* return 正确完成返回0 非正常完成返回-1
*/
bool logic_BasicModule::changeMode(int modeID,std::vector<logic_BasicPara *> & ParaReturnList)
{
	return true;
}

bool logic_BasicModule::changeParaValue(int paraID,std::string value)
{
	return true;
}

bool logic_BasicModule::changeWinSwicher() {

	return true;
}

logic_BasicPara * logic_BasicModule::getPara(int p_id) {

	if( mvvu_ParaList.size() < p_id )
		return NULL;

	return mvvu_ParaList.at(p_id);
}

int logic_BasicModule::getModuleType() {
	return mvs_ModuleType;
}

WinSwitcherType logic_BasicModule::getWSType(int m_modeValue) {

	return mvvu_ModeMenu.at(m_modeValue-1)->mve_WS.mve_WSType;
}

std::string logic_BasicModule::getWSValue() {

	return this->mve_CurWinSwitcher.mvs_WSValue;
}

void logic_BasicModule::setWSValue(std::string ws_value) {

	this->mve_CurWinSwitcher.mvs_WSValue = ws_value;
}

int logic_BasicModule::getDaisyChainValue() {

	return this->mve_CurWinSwitcher.mvi_ChainLayer;
}

void logic_BasicModule::setDaisyChainValue(int chain_value) {

	this->mve_CurWinSwitcher.mvi_ChainLayer = chain_value;
}

std::vector<int > logic_BasicModule::getParamsIds(int mode_value) {

	logic_ParaPointer * tp = mvvu_ModeMenu.at(mode_value-1);

	return tp->mvvi_ParaIDList;
}

int logic_BasicModule::getModeValue() {

	return mvi_CurModeID;
}

void logic_BasicModule::setModeValue(int mode_id) {

	mvi_CurModeID = mode_id;
}

WinSwitcherType logic_BasicModule::getCurWSType() {

	return getWSType(this->mvi_CurModeID);
}

std::vector <logic_BasicPara*> logic_BasicModule::getCurParaList() {

	logic_ParaPointer * tCurMode = mvvu_ModeMenu.at(this->mvi_CurModeID-1);
	std::vector <int > tAllParaIds = tCurMode->mvvi_ParaIDList;

	std::vector <logic_BasicPara*> resL;

	for (int i=0;i<tAllParaIds.size();++i) {
		int p_id = tAllParaIds.at(i);
		resL.push_back(mvvu_ParaList.at(p_id));
	}

	return resL;
}
