#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "module.h"
#include"ports.h"
#include<QTreeWidget>
#include<QMenu>
#include<QMouseEvent>
#include<QDrag>
#include<QPainter>
#include<QBitmap>
#include"button.h"
#include"menuitem.h"
#include<QWidgetAction>
#include"view.h"
#include"mode_select.h"
#include "msgInterface.h"
#include <iostream>
#include <windows.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
   ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	ui->modules->setCurrentIndex(0);

	whWork();
	
}

MainWindow::~MainWindow()
{
	qDebug()<<"run ~MainWindow()";
    delete ui;
}

void MainWindow::whWork() {

	//���½�һ������Ŀ
	msginterface.newPrj();

	//�ٽ�һ����program
	msginterface.newProg();

	//����һ��module�����
	msginterface.insertModule(1,false,1002); //2
	msginterface.insertModule(0,false,1003); //3
	msginterface.insertModule(3,false,1004); //4

	//ǰ��
	msginterface.insertModule(4,true,1005); //5
	msginterface.insertModule(3,true,1006); //6

	//ɾ��module����
	msginterface.addLeafModule(5,1007); //7
	msginterface.addLeafModule(5,1008); //8
	msginterface.addLeafModule(7,1009); //9
// 	msginterface.deleteModule(3);
// 	msginterface.deleteModule(5);

	msginterface.addLeafModule(6,1010); //10
	msginterface.addLeafModule(6,1011); //11
//	msginterface.deleteModule(6);

	msginterface.insertModule(2,false,1012); //12
	msginterface.insertModule(12,false,1013); //13

	//////////move test
//	msginterface.moveModule(2,5,BACK_SINGLE); //��ģ���� OK
//	msginterface.moveModule(2,0,BACK_SINGLE); //��ģ���� �ſ�

//	msginterface.moveModule(12,4,FRONT_SINGLE); //��ģ��ǰ�� OK
//	msginterface.moveModule(2,4,BACK_MULTI); //��ģ���� OK

//	msginterface.moveModule(13,6,FRONT_MULTI); //��ģ��ǰ�� OK
	msginterface.moveModule(5,0,BACK_MULTI); //��ģ���� �ſ�

}


////////////////////////////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



void MainWindow::addProgram(QWidget * parent)
{
	   int a=ui->projects->currentIndex();
	   QString programName;
	   QTabWidget* tab=new QTabWidget(parent);
	   QWidget* program = new QWidget();
       QVBoxLayout* verticalLayout = new QVBoxLayout(program);
       verticalLayout->setSpacing(0);
       verticalLayout->setContentsMargins(0, 0, 0, 0);
       QGraphicsView*  view = new QGraphicsView(program);
       verticalLayout->addWidget(view);
	   tab->addTab(program,QString());
	   QWidget * buttons =new QWidget(program);
	   QGridLayout * layout =new QGridLayout(buttons);
	   buttons->setGeometry(800,50,200,100);

}

void MainWindow::addProject()
{
	QWidget* tab = new QWidget();   
    QHBoxLayout* horizontalLayout = new QHBoxLayout(tab);
    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
	ui->projects->addTab(tab, QString());
	QString projectName;
	project a ;
	a.setName(projectName);
	projectList.append(a);
	addProgram(tab);
}

void MainWindow::save()
{
	int a=ui->modules->count();
	for(int i=0;i<a;i++)
	{
		QWidget* wid =ui->modules->widget(i);
		QTabWidget* tab=(QTabWidget*)wid->children().at(0);
		int b=tab->count();
		for(int j=0;j<b;j++)
		{
			QGraphicsView* wid =(QGraphicsView*) tab->widget(j);
			QGraphicsScene scene= wid->scene();
			
		}
	}
}

bottom_label* MainWindow::GetLabelPtr(int id)
{
	QObjectList bottomLabelList = ui->green->children();
	int len = bottomLabelList.length();

	for(int i=0;i<len;i++)
	{
		bottom_label* p = (bottom_label*)bottomLabelList.at(i);
		if (p->GetID() == id)
		{
			return p;
		}
	}

	return NULL;
}
