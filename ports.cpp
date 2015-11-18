#include "ports.h"

ports::ports(QWidget *parent,QString a,QString c,QString e,QString f)
	: QWidget(parent)
{
	upper=new QLabel();
	upper->setPixmap(f);
	upper->setToolTip(e);
	pic=c;
	modify_type =a;	
}

ports::~ports()
{

}
