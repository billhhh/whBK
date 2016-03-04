/* 
* 
* function: 逻辑层全局变量
* 
* Date:2015-09-05
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_GLOBAL_H_
#define _LOGIC_GLOBAL_H_

#define _IdDataType int
#define SAFE_DELETE(p) { if(p) {delete p; p = NULL;} }
typedef struct frontEndPoint{
	int x;
	int y;
	frontEndPoint()
	{
		x = 0;
		y = 0;
	}
	frontEndPoint(int xPoint,int yPoint)
	{
		x = xPoint;
		y = yPoint;
	}



} point;




#endif
