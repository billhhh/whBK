/**
 * ��ȡxml�Ĺ�����
 * 
 * @author Bill Wang
 * 
 */
#ifndef _XML_IO_H_
#define _XML_IO_H_

#include <string>
#include <map>
#include "logic_Project.h"
#include "logic_BasicModule.h"

class logic_XmlIO
{
public:
	std::map <int, logic_BasicModule *> initAllModule(); //��ʼ��ģ��

	int SavePrj(std::string path,logic_Project prj); //д��xml
	int FillPrj(std::string path,logic_Project &prj); //��ȡxml�������һ��prj

private:
	
};

#endif