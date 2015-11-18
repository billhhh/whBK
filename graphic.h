#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QtWidgets/QWidget>


class graphic : public QWidget
{
	Q_OBJECT

public:
	graphic(QWidget *parent = 0);
	~graphic();
	void mousePressEvent(QMouseEvent*);
	
private:

};

#endif // GRAPHIC_H

