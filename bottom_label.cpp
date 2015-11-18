#include "bottom_label.h"

#include <QMimeData>
bottom_label::bottom_label(QWidget *parent,int id)
	: QLabel(parent)
{
	//id=1;
	this->id = id;

}

bottom_label::~bottom_label()
{

}
void bottom_label::mousePressEvent(QMouseEvent *event){
	 if (event->button() == Qt::LeftButton) {
         QDrag* drag = new QDrag(this);
		 
		//const QPixmap *pPixmap = pixmap();   
  //      drag->setPixmap(*pPixmap); //这里设置拖拽时跟随鼠标的图片  
		//int w=pPixmap->size().width();
		//int h=pPixmap->size().height();
		//QPoint t;
		//t.setX(w);
		//t.setY(h);
  //      drag->setHotSpot(t); //设置跟随图片的中心点  



         QMimeData *mimeData = new QMimeData;
         mimeData->setText(QString::number(id));
         drag->setMimeData(mimeData);
         //drag->setPixmap(iconPixmap);
         Qt::DropAction dropAction = drag->exec();
		 drag->start(Qt::MoveAction);
     }
}

int bottom_label::GetID(void)
{
	return id;
}



