/* 
* 
* function: 液晶屏图像类实现
* 
* Date:2016-01-23
* 
*    Author: Bill Wang
*/

#include "logic_Gragh.h"
#include <assert.h>

int* logic_Gragh::getGragh() {

	return &gragh[0][0];
}


int logic_Gragh::setGragh(int * tmpGragh) {

	for (int i=0;i<GRAGH_WIDTH; ++i){
		for (int j=0;j<GRAGH_LENGTH; ++j) {

			if( tmpGragh[i*GRAGH_LENGTH+j] != 0 || tmpGragh[i*GRAGH_LENGTH+j] != 1 ) {
				assert(false);
				return -1; //严重的内部错误
			}

			this->gragh[i][j] = tmpGragh[i*GRAGH_LENGTH+j];
		}
	}

	return 0;
}
