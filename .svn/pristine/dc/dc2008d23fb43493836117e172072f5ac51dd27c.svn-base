#ifndef BOTTOM_LABEL_H
#define BOTTOM_LABEL_H

#include <QLabel>
#include <QDrag>
#include <QMouseEvent>
class bottom_label : public QLabel
{
	Q_OBJECT

public:
	bottom_label(QWidget *parent,int id);
	~bottom_label();
protected:
	void mousePressEvent(QMouseEvent *event);
	//QDrag *drag;
private:
	int id;
	QString image;
	
public:
	int GetID(void);

};

#endif // BOTTOM_LABEL_H
