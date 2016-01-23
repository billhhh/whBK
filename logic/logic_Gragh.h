/* 
* 
* function: “∫æß∆¡ÕºœÒ¿‡
* 
* Date:2016-01-23
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_GRAGH_H_
#define _LOGIC_GRAGH_H_

#define GRAGH_LENGTH 180
#define GRAGH_WIDTH 128

#include <string>

class logic_Gragh
{
public:

	int id;
	std::string name;

	int* getGragh();
	int setGragh(int *tmpGragh);

protected:


private:
	int gragh[GRAGH_LENGTH][GRAGH_WIDTH];

};

#endif
