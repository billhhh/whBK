#include "mode_select.h"
#include<QMenu>
#include<QAction>
#include "module.h"
#include"ports.h"
#include<QTreeWidget>
#include<QMouseEvent>
#include<QDrag>
#include<QPainter>
#include<QBitmap>
#include"button.h"
#include"menuitem.h"
#include<QWidgetAction>
#include<QMouseEvent>
mode_select::mode_select(QWidget * parent):QPushButton(parent)
{
	setFixedSize(61,34);
	menu = new QMenu(this);
	QFile file("menus.xml");  
	if (!file.open(QFile::ReadOnly | QFile::Text)) {  
		return ;  
	}  
	QDomDocument domDocument;  
	if (!domDocument.setContent(&file, true)) {  
		file.close();  
		return ;  
	}  	
	//QTreeWidget* treewidget=new QTreeWidget(this);

	QDomElement tree = domDocument.documentElement(); 
	QDomElement children=tree.childNodes().at(0).toElement();
	QDomNodeList actions = children.childNodes();

	int n=actions.length();
	for(int i=0;i<n;i++)
	{
		QDomNode ac =actions.at(i);		
		QString img =ac.toElement().attribute("image");	
		QAction * action =new QAction(this);
		action->setText(img);
		/*
		menuItem * menulist=new menuItem(this);
		QPixmap pixmap(img);
		menulist->setBackgroundImage(pixmap);
		menulist->resize(pixmap.size().width(),pixmap.size().height());		
		QWidgetAction *  action = new QWidgetAction(menu);
		action->setDefaultWidget(menulist);  */
        menu->addAction(action);
		if(ac.hasChildNodes())
		{
			QMenu* menu1=new QMenu(this);
			action->setMenu(menu1);
			QDomElement submenu_2=ac.firstChildElement();
			QDomNodeList actions_2 = submenu_2.childNodes();
			int m=actions_2.length();
			for(int j=0;j<m;j++)
			{
				QDomNode ac_2 =actions_2.at(j);	       
			    QString img2 =ac_2.toElement().attribute("image");
				QAction * add_2 =new QAction(this);
		        add_2->setText(img2);
				/*
	            menuItem * menulist1=new menuItem(this);
				pixmap.load(img2);
				menulist1->setBackgroundImage(pixmap);
				menulist1->resize(pixmap.size().width(),pixmap.size().height());
                QWidgetAction *  add_2 = new QWidgetAction(menu1); 
				add_2->setDefaultWidget(menulist1); */
				menu1->addAction(add_2);
				if(ac_2.hasChildNodes())
				{
					QMenu* menu2=new QMenu(this);
					add_2->setMenu(menu2);
					QDomElement submenu_3=ac_2.firstChildElement();
					QDomNodeList actions_3 = submenu_3.childNodes();
					int l=actions_3.length();
					for(int k=0;k<l;k++)
					{
						QDomNode ac_3 =actions_3.at(k);
						
						QString img3 =ac_3.toElement().attribute("image");
						
		
						QAction * add_3 =new QAction(this);
		                add_3->setText(img3);
						
						/*
						pixmap.load(img3);menuItem * menulist2=new menuItem(this);
						menulist2->setBackgroundImage(pixmap);
						menulist2->resize(pixmap.size().width(),pixmap.size().height());
						QWidgetAction *  add_3 = new QWidgetAction(menu2); 
						add_3->setDefaultWidget(menulist2);  */
						menu2->addAction(add_3);
					}
				}

			}

		}
	
	}
	//connect(menu, SIGNAL(triggered(QAction*)),
	//		this, SLOT(slot_show_groupname(QAction*)));  
	QString ap=QString("%1,%2").arg(pos().x()).arg(pos().y());
	QString app=QString("%1,%2").arg(QCursor::pos().x()).arg(QCursor::pos().y());
}

mode_select::~mode_select()
{
	
}
void mode_select::mousePressEvent(QMouseEvent* event)
{

  // menu->exec(QCursor::pos());
	
//	mode_select->setMenu(menu);
	qDebug("button clicked");


    QPoint t;
	t.setX(event->screenPos().x());
	t.setY(event->screenPos().y());
	
//	QAction * ac1=new QAction("he",this);
//	QAction * ac2=new QAction("go",this);
//	QMenu *menu =new QMenu(this);
//	menu->addAction(ac1);
//	menu->addAction(ac2);
	menu->exec(t);  





}

void mode_select::showMenu()
{
	QFile file("menus.xml");  
	if (!file.open(QFile::ReadOnly | QFile::Text)) {  
		return ;  
	}  
	QDomDocument domDocument;  
	if (!domDocument.setContent(&file, true)) {  
		file.close();  
		return ;  
	}  
	
	//QTreeWidget* treewidget=new QTreeWidget(this);	

	menu = new QMenu(this);


	QDomElement tree = domDocument.documentElement(); 
	QDomElement children=tree.childNodes().at(0).toElement();
	QDomNodeList actions = children.childNodes();

//	setMenu(menu);

	int n=actions.length();
	for(int i=0;i<n;i++)
	{
		QDomNode ac =actions.at(i);	
		menuItem * menulist=new menuItem(this);
		QString img =ac.toElement().attribute("image");
		QPixmap pixmap(img);
		menulist->setBackgroundImage(pixmap);
		menulist->resize(pixmap.size().width(),pixmap.size().height());
		
		QWidgetAction *  action = new QWidgetAction(menu);

		action->setDefaultWidget(menulist);
         menu->addAction(action);

		if(ac.hasChildNodes())
		{
			QMenu* menu1=new QMenu(this);
			action->setMenu(menu1);
			QDomElement submenu_2=ac.firstChildElement();
			QDomNodeList actions_2 = submenu_2.childNodes();
			int m=actions_2.length();
			for(int j=0;j<m;j++)
			{
				QDomNode ac_2 =actions_2.at(j);
		 

		        menuItem * menulist1=new menuItem(this);
			    QString img2 =ac_2.toElement().attribute("image");
				pixmap.load(img2);
				menulist1->setBackgroundImage(pixmap);
				menulist1->resize(pixmap.size().width(),pixmap.size().height());
                QWidgetAction *  add_2 = new QWidgetAction(menu1); 
				add_2->setDefaultWidget(menulist1);
				menu1->addAction(add_2);

				if(ac_2.hasChildNodes())
				{
					QMenu* menu2=new QMenu(this);
					add_2->setMenu(menu2);
					QDomElement submenu_3=ac_2.firstChildElement();
					QDomNodeList actions_3 = submenu_3.childNodes();
					int l=actions_3.length();
					for(int k=0;k<l;k++)
					{
						QDomNode ac_3 =actions_3.at(k);
						 menuItem * menulist2=new menuItem(this);
						QString img3 =ac_3.toElement().attribute("image");
						pixmap.load(img3);
						menulist2->setBackgroundImage(pixmap);
						menulist2->resize(pixmap.size().width(),pixmap.size().height());
						QWidgetAction *  add_3 = new QWidgetAction(menu2); 
						add_3->setDefaultWidget(menulist2);
						menu2->addAction(add_3);
					}
				}

			}

		}
	
	}
	//connect(menu, SIGNAL(triggered(QAction*)),
	//		this, SLOT(slot_show_groupname(QAction*)));  
//	QString ap=QString("%1,%2").arg(pos().x()).arg(pos().y());
//	QString app=QString("%1,%2").arg(QCursor::pos().x()).arg(QCursor::pos().y());
  // menu->exec(QCursor::pos());
	
//	mode_select->setMenu(menu);
	



}