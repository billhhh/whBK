#include "view.h"
#include"graphic.h"
#include<QMouseEvent>
#include<QGraphicsItem>
#include"mode_select.h"
#include<QMenu>
#include<QAction>
#include"module.h"
#include<QDragEnterEvent>
#include<QGraphicsProxyWidget>
#include<QAbstractItemView>
#include"mainwindow.h"
int shift = 0;
view::view(QWidget * parent):
	QGraphicsView(parent)
{
	scene=new QGraphicsScene;
    scene->setSceneRect(-400,-400,800,800);
	a=10;

  //  module * t =new module(1,7,0,1);
   

//	module * p =new module(1,7,0,1);
	//scene->addWidget(t);  
	//scene->addWidget(p);  
	
	

	setAcceptDrops(true);
	dragItem = NULL;
	dockItem = NULL;
	offset.setX(0); offset.setY(0);
	dragEnter = false;
	ptr_drag_modult = NULL;
//	menu->exec(t->pos());

//	test * p=new test;
	 
	//	scene->addWidget(menu);
//	scene->addWidget(p); 
	resize(800,800);
    setScene(scene);
    show();
	
}


view::~view()
{

}
void view::mouseMoveEvent(QMouseEvent * event)  //是其他的活动如显示tooltip还是移动某个模块
{
	
	qDebug("mouse move");
    if(event->buttons()&Qt::LeftButton&&(!dragItem==NULL)){
        QPointF itemPos = mapToScene(event->pos()) - offset;
        dragItem->move(itemPos.x(), itemPos.y());
        checkForMatch();
    }
    update();


}

void view::checkForMatch()
{
	 selectItem =scene->items();   //被选中的一些模块
	int length=selectItem.length();
    for(int i=0;i<length;i++){
        QGraphicsProxyWidget *tempPw = static_cast<QGraphicsProxyWidget*>(selectItem.at(i));
        module *tempModule = (module*)tempPw->widget();
        if(dragItem != tempModule){
            //selectItem.at(i)->setPos(120, 120);
            if(dragItem->boundingRect().intersects(tempModule->boundingRect())){
                //qDebug("yes");
                dockItem = tempModule;
                if(dragItem->pos().x()+dragItem->size().width()/2 > dockItem->pos().x()
                        &&dragItem->pos().x() < dockItem->pos().x()+dockItem->size().width()
                        &&shift == 0){
                    shift = dragItem->size().width() - (dockItem->pos().x() - dragItem->pos().x());
                    dockItem->move(dockItem->pos().x()+shift, dockItem->pos().y());

                }

                dragEnter = true;
                break;
            }else{
                dragEnter = false;
                if(dockItem)
                    dockItem->move(dockItem->pos().x()-shift, dockItem->pos().y());
                shift = 0;
                dockItem = NULL;
                continue;
            }
        }
	}
}





void view::mousePressEvent(QMouseEvent * event)
{ 
	qDebug("mouse press");
	QGraphicsItem *tempItem = NULL;
    if(event->button() == Qt::LeftButton)
    {
        tempItem = itemAt(event->pos());
    }
    if(!tempItem)
    {
        qDebug("2222");
        return;
    }
    QGraphicsProxyWidget *pw = static_cast<QGraphicsProxyWidget*>(tempItem);
    dragItem = (module*)pw->widget();
    offset = mapToScene(event->pos()) - dragItem->pos();
}

void view::mouseReleaseEvent(QMouseEvent * event)
{
	 
	if(dragEnter&&dockItem){
        if(dragItem->pos().x() > dockItem->pos().x()+dockItem->size().width()){
            dragItem->move(dockItem->pos().x()+dockItem->size().width(), dockItem->pos().y()+dockItem->size().height()/2-dragItem->size().height()/2);
        }else{
            dragItem->move(dockItem->pos().x()-dragItem->size().width(), dockItem->pos().y()+dockItem->size().height()/2-dragItem->size().height()/2);
        }
        shift = 0;
        dragEnter = false;
    }
    else
        event->ignore();

	qDebug("mouseRelease");
}


void view::dragEnterEvent(QDragEnterEvent *event)
{
	//QMimeData* data = event->mimeData();
	if (event->mimeData()->hasFormat("text/plain"))
	{
		int id = event->mimeData()->text().toInt();
		//QWidget* p = (QTabWidget*)this->parentWidget()->parentWidget()->parentWidget();
		//QString str = this->parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget()->objectName();
		//QString str2 = this->parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget()->objectName();
		/*QString qstr = event->source()->objectName();
		qDebug(qstr.toStdString().c_str());*/
		//scene->addItem(&text);4
		//text.moveBy(50,50);
		dragID = id;
		isDragMoved = false;
		/*if (id<8&&id>0)
		{
			qDebug("0<id<8");
		}else
			qDebug("id_err");*/
		
		
		event->acceptProposedAction();
	
	}

	
	event->acceptProposedAction();
	qDebug("dragenter");
}



void view::dragMoveEvent(QDragMoveEvent *event)
{
/*	if (event->mimeData()->hasFormat("customItem"))
	{
		QPointF point = mapToScene(event->pos());
		m_pScene->moveInsertingItem(QPoint(point.x(),point.y()));

		event->setDropAction(Qt::MoveAction);
		event->accept();
	}  */

	//MainWindow* p_mainWindow = (MainWindow*)this->parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget();
	//	//((MainWindow*)(this->parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget()->parentWidget()))->GetLabelPtr(id);
	//	bottom_label* ptr_bottom_label = p_mainWindow->GetLabelPtr(dragID);
	//	ptr_bottom_label->GetDrag()->setPixmap(QPixmap("C:/Users/Administrator/Desktop/mainwindow/mainwindow/yellow.png"));
	//	
	//	QPoint t;
	//	t.setX(0);2
	//	t.setY(0);
 //       ptr_bottom_label->GetDrag()->setHotSpot(t); //设置跟随图片的中心点  
	//	ptr_bottom_label->GetDrag()->exec();
	if (!ptr_drag_modult)
		{
			ptr_drag_modult =new module(1,7,0,1);
			qDebug("New");
			QPointF point = mapToScene(event->pos());
			scene->addWidget(ptr_drag_modult);
			int w=ptr_drag_modult->size().width();
			int h=ptr_drag_modult->size().height();
			ptr_drag_modult->move(point.x()-w/2,point.y()-h/2);
		}
	dragItem = ptr_drag_modult;
	checkForMatch();
	QPointF point = mapToScene(event->pos());
	int w=ptr_drag_modult->size().width();
	int h=ptr_drag_modult->size().height();
	ptr_drag_modult->move(point.x()-w/2,point.y()-h/2);
	
	//QPointF point = mapToScene(event->pos());
	event->setDropAction(Qt::MoveAction);
	event->accept();
	
	qDebug("dragmove");
}

void view::dropEvent(QDropEvent *event)
{
/*	if (event->mimeData()->hasFormat("customItem"))
	{
		this->setFocus();
		m_pScene->setFocus();
		
		m_pScene->insertingDone();
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}   */
	/*
	this->setFocus();
	event->setDropAction(Qt::MoveAction);
	event->accept();*/
	/*if (isDragMoved)
	{
		ptr_drag_modult = NULL;
		dragItem = NULL;
	}*/
	ptr_drag_modult = NULL;
		dragItem = NULL;
	qDebug("dropevnet");

}

void view::dragLeaveEvent(QDragLeaveEvent *event)
{
//	m_pScene->removeInsertingItem();
	
	qDebug("dragleave");
}




