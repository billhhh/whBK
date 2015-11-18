#pragma once
#include"program.h"
#include<QString>
#include<QList>
class project
{
public:
	project(void);
	~project(void);
	QString getNamge();
	void setName(QString);
private:
	QList<program> programList;
	QString name;
};

