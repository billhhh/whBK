#pragma once
#include<QString>
class program
{
public:
	program(void);
	~program(void);
	QString getNamge();
	void setName(QString);
private:
	QString name;
};

