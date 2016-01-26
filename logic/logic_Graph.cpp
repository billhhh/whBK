/* 
* 
* function: 液晶屏图像类实现
* 
* Date:2016-01-23
* 
*    Author: Bill Wang
*/

#include "logic_Graph.h"
#include <assert.h>

int* logic_Graph::getGraph() {

	return &graph[0][0];
}


int logic_Graph::setGraph(int * tmpGraph) {

	for (int i=0;i<GRAPH_WIDTH; ++i){
		for (int j=0;j<GRAPH_LENGTH; ++j) {

			if( tmpGraph[i*GRAPH_LENGTH+j] != 0 || tmpGraph[i*GRAPH_LENGTH+j] != 1 ) {
				assert(false);
				return -1; //严重的内部错误
			}

			this->graph[i][j] = tmpGraph[i*GRAPH_LENGTH+j];
		}
	}

	return 0;
}
