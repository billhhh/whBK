/**
 * 读取xml的工具类
 * 
 * @author Bill Wang
 * 
 */
#ifndef _XML_IO_H_
#define _XML_IO_H_

#include <string>
#include "logic_Project.h"

class logic_XmlIO
{
public:
	bool FillPrj(std::string path,logic_Project &prj); //读取xml，填充满一个prj

private:
	
};

#endif