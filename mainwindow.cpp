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

	//先新建一个空项目
	msginterface.newPrj();

	//再建一个空program
	msginterface.newProg();

	msginterface.insertModule(0,false,1002);
	msginterface.insertModule(0,false,1002);
	msginterface.insertModule(2,false,1002);
	msginterface.moveModule(2,1,ADD_LEAF);

	msginterface.moveModule(2,0,FRONT_MULTI);

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
