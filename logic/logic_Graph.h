/* 
* 
* function: “∫æß∆¡ÕºœÒ¿‡
* 
* Date:2016-01-23
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_GRAPH_H_
#define _LOGIC_GRAPH_H_

#define GRAPH_LENGTH 180
#define GRAPH_WIDTH 128

#include <string>

class logic_Graph
{
public:

	int id;
	std::string name;

	int* getGraph();
	int setGraph(int *tmpGraph);

protected:


private:
	int graph[GRAPH_LENGTH][GRAPH_WIDTH];

};

#endif
