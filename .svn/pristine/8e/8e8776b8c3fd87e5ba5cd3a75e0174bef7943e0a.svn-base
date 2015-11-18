#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include"graphic.h"
#include "module.h"
class view : public QGraphicsView
{
	Q_OBJECT

public:
	view(QWidget * parent);
	~view();
	int a;

	void checkForMatch();

	void dragLeaveEvent(QDragLeaveEvent *event);
	void dropEvent(QDropEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);	
    void dragEnterEvent(QDragEnterEvent *event);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent * event);
    //void paintEvent(QPaintEvent *event);
private:
	QList<QGraphicsItem*> selectItem;
    QGraphicsScene *scene;
    module *dragItem;
    module *dockItem;
    bool dragEnter;
    QPointF offset;
protected:
	int dragID;
	module* ptr_drag_modult;
public:
	bool isDragMoved;
};

#endif // VIEW_H
