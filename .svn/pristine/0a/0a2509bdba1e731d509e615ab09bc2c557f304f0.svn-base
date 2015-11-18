#ifndef MODULE_H
#define MODULE_H


#include<QGraphicsSceneMouseEvent>
#include <QtWidgets/QWidget>
#include <QFile>   
#include <QString>  
#include <QDomDocument>
#include <QtXml>  
#include <QXmlStreamReader>
#include<QLabel>
#include<QGridLayout>
#include<QPushButton>
#include"mode_select.h"
class module : public QWidget
{
	Q_OBJECT

public:
	module(int a=0,int b=0,int c=0,int d=0);
	~module();
	QRectF boundingRect() const ;
protected:
//	void dragEnterEvent(QDragEnterEvent *event);
//	void mousePressEvent(QGraphicsSceneMouseEvent *event);
private slots:
	void showMenu();
	void slot_show_groupname(QAction*);
//	void mousePressEvent(QMouseEvent * event);
//	void module::mouseMoveEvent(QMouseEvent * event);

private:
	int id;//模块的唯一id号
	int state; //模块所处的模式
	int kind;//模块的类型,kind从0开始
    int topright;  //右上角信息
	int width;
	int form(int state,int kind,int topright);
	int x;
	int y;
	mode_select * mode_sel;  

};










#endif // MODULE_H