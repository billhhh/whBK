/* 
* 
* function: “∫æß∆¡ÕºœÒ¿‡ µœ÷
* 
* Date:2016-01-23
* 
*    Author: Bill Wang
*/

#include "logic_Gragh.h"

int** logic_Gragh::getGragh() {

	return gragh;
}


void logic_Gragh::setGragh(int ** tmpGragh) {

	for (int i=0;i<GRAGH_LENGTH; ++i){

		for (int j=0;j<GRAGH_WIDTH; ++j) {

			if( tmpGragh[i][j] != 0 || tmpGragh[i][j] != 1 ) {

			}
		}
	}
}
