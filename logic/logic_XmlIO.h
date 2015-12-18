/**
 * 读取xml的工具类
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
	std::map <int, logic_BasicModule *> initAllModule(); //初始化模块

	int SavePrj(std::string path,logic_Project prj); //写入xml
	int FillPrj(std::string path,logic_Project &prj); //读取xml，填充满一个prj

private:
	
};

#endif