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
module::module(int a,int b,int c,int d)//处于b状态的c模块
	
{
	id=a;  //模块的ID
    state=b; //模块所处的模式  7
    kind=c;//模块的类型   0
    topright=d;  //右上角信息   1
	width=0;
	mode_sel =new mode_select(this);//模式选择按钮
	form(kind,state,topright); 	
	x=0;
	y=0;
//	setAcceptDrops(true);

}

module::~module()
{

}

QRectF module::boundingRect() const
{
    qreal adjust = 50;

    return QRectF(pos().x() - adjust/2, pos().y(), size().width() + adjust, size().height());

}
int module::form(int kind,int state,int topr)     //形成一个模块,state是模块的状态，kind表示是哪种基本模块，topright表示右上角的信息
{
//	QGridLayout*  gridlayout=new QGridLayout(this);
//	gridlayout->addWidget(icon,0,0,1,1);
//	gridlayout->addWidget(mode_sel,1,0,1,1);


	QFile file1("modules.xml");  //存储了每个模块的所有信息
	if (!file1.open(QFile::ReadOnly | QFile::Text)) {  
		return -1;  
	}  
	QDomDocument domDocument1;  
	if (!domDocument1.setContent(&file1, true)) {  
		file1.close();  
		return -2;  
	} 
	QDomElement root   = domDocument1.documentElement();  //    QDomElement module= root.firstChildElement();  
	QDomNodeList module_list =root.childNodes();
	QDomElement  module= module_list.at(kind).toElement();//模块k


	topright=topr;

/*	QString img_pic=module.attribute("img_pic");
	QString img_tooltip=module.attribute("img_tooltip");	
	QPixmap pixmap;
	pixmap.load(img_pic);
	icon->setPixmap(img_pic);
	icon->setToolTip(img_tooltip);  

    QString button_pic=module.attribute("button_pic");
	QString menu_tooltip=module.attribute("menu_tooltip");
	mode_sel->setToolTip(menu_tooltip);
	pixmap.load(button_pic);
	mode_sel->setIconSize(pixmap.size());
	mode_sel->setIcon(pixmap);  */


	QString left=module.attribute("left");
	QString right=module.attribute("right");
	QString middle=module.attribute("middle");


 //   QPainter painter(this);  

/*	QLabel* leftLabel =new QLabel(this);
	pixmap.load(left);
	
	leftLabel->resize(pixmap.size().width(),pixmap.size().height());
	leftLabel->setPixmap(pixmap);
	leftLabel->move(0,0);    */

	QWidget * a= new QWidget(this);
	QPalette palette;
	QPixmap pixmap;
	pixmap.load(left);
	int x=pixmap.size().width();
	int y=pixmap.size().height();
	a->resize(x,y);
    palette.setBrush(a->backgroundRole(), QBrush(pixmap));
    a->setPalette(palette);
    a->setAutoFillBackground(true);
	width+=pixmap.size().width();
//	a->setMask(pixmap);

	QLabel* icon;  //模块图标
	//模式选择按钮

	icon=new QLabel(a);
	//icon->setFixedSize(48,43);    //位置

    mode_sel=new mode_select(a);


	QString img_pic=module.attribute("img_pic");
	QString img_tooltip=module.attribute("img_tooltip");	
	pixmap.load(img_pic);
	icon->setPixmap(img_pic);
	icon->setToolTip(img_tooltip);  

    QString button_pic=module.attribute("button_pic");
	QString menu_tooltip=module.attribute("menu_tooltip");
	mode_sel->setToolTip(menu_tooltip);
	pixmap.load(button_pic);
	mode_sel->setIconSize(pixmap.size());
	mode_sel->setIcon(pixmap);

	icon->move(20,18);
	mode_sel->move(13,68);
	
	

	
	QFile file2("modes.xml");  //存储了每个模块的端口的所有图片
	if (!file2.open(QFile::ReadOnly | QFile::Text)) {  
		return -1;  
	}  
	QDomDocument domDocument2;  
	if (!domDocument2.setContent(&file2, true)) {  
		file2.close();  
		return -2;  
	}  

   QDomElement tree = domDocument2.documentElement();  
  //  QDomElement module= root.firstChildElement();  //模块1
	QDomNodeList modes=tree.childNodes();
	QDomElement mode= modes.at(kind).toElement();  //模块1	

	QDomNodeList allMode=mode.childNodes();
	QList<int> port_list;
	for(int i=0;state!=0;i++)// 判断条件 n!=0
	{
		if(state%2)
		{
			QDomNode in =allMode.at(i);	 
			QString modify_type = in.toElement().attribute("modify_type");
			QString data_img = in.toElement().attribute("data_img");
			QString tooltip = in.toElement().attribute("tooltip");
			QString icon_img = in.toElement().attribute("icon_img");

			int port=modify_type.toInt();
			

			QLabel* label =new QLabel(this);
	        pixmap.load(middle);
			label->resize(pixmap.size().width(),pixmap.size().height());
			label->setPixmap(pixmap);
			label->move(width,0);
	        width+=pixmap.size().width();
			label->setMask(pixmap.mask()); 


            QLabel *label1 =new QLabel(this);
			pixmap.load(icon_img);
			label1->resize(pixmap.size().width(),pixmap.size().height());
			label1->setPixmap(pixmap);
			label1->setToolTip(tooltip);
			label1->move(width,0);
			port_list.append(port);
		}  
		state=state/2;
	} 


	QLabel* rightLabel =new QLabel(this);
	pixmap.load(right);
	rightLabel->resize(pixmap.size().width(),pixmap.size().height());
	rightLabel->setPixmap(pixmap);
	rightLabel->move(width,0);
	width+=pixmap.size().width();  

	resize(width,pixmap.size().height());
	
	return 1;

}


void module::showMenu()
{
/*	qDebug("showmenu");
	QFile file("menus.xml");  
	if (!file.open(QFile::ReadOnly | QFile::Text)) {  
		return ;  
	}  
	QDomDocument domDocument;  
	if (!domDocument.setContent(&file, true)) {  
		file.close();  
		return ;  
	}  
	
	QTreeWidget* treewidget=new QTreeWidget(this);	
//	menu = new QMenu(treewidget);


	QDomElement tree = domDocument.documentElement(); 
	QDomElement children=tree.childNodes().at(kind).toElement();
	QDomNodeList actions = children.childNodes();

	mode_sel->setMenu(menu);



	int n=actions.length();
	for(int i=0;i<n;i++)
	{
		QDomNode ac =actions.at(i);
		
		menuItem * menulist=new menuItem(this);
		QString img =ac.toElement().attribute("text");
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
			    QString img2 =ac_2.toElement().attribute("text");
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
						QString img3 =ac_3.toElement().attribute("text");
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
	connect(menu, SIGNAL(triggered(QAction*)),
			this, SLOT(slot_show_groupname(QAction*)));  
//	QString ap=QString("%1,%2").arg(pos().x()).arg(pos().y());
//	QString app=QString("%1,%2").arg(QCursor::pos().x()).arg(QCursor::pos().y());
   //menu->exec(QCursor::pos());
	
//	mode_select->setMenu(menu);
	
	 */
	 
}

void module::slot_show_groupname(QAction* action)
{
	//icon->setText(action->text());
}

/*void  module::dragEnterEvent(QDragEnterEvent *event)
{
	qDebug("enter");
}  */


 