#include "menuitem.h"

menuItem::menuItem(QWidget *parent)
	: QWidget(parent)
{
	setAutoFillBackground(true);
}

menuItem::~menuItem()
{

}
void menuItem::setBackgroundImage(QPixmap img)
{
	  
		QPalette palette;
        palette.setBrush(this->backgroundRole(), QBrush(img));
        setPalette(palette);
}
