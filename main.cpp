#include "mainwindow.h"
#include <QApplication>
#include "module.h"
#include"ports.h"
#include<QTreeWidget>
#include<QMenu>
#include<QMouseEvent>
#include<QDrag>
#include<QPainter>
#include<QBitmap>
#include"button.h"
#include "logic/logic_Tree.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#define new  new(_CLIENT_BLOCK, __FILE__, __LINE__)

//on_ff 为true 打印内存泄漏, 为false则不打印
void detect_memory_leaks( bool on_off )
{
	int flags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	if(!on_off)
		flags &= ~_CRTDBG_LEAK_CHECK_DF;
	else {
		flags |= _CRTDBG_LEAK_CHECK_DF;
		_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
		_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	}
	_CrtSetDbgFlag( flags );
}


void test() {

	std::map <logic_Tree * ,int > testMap;
	logic_Tree *tmpTree = new logic_Tree();

	testMap[]
}

int main(int argc, char *argv[])
{
	/*detect_memory_leaks(true);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();*/

	test();

	system("pause");
}
