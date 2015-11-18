#include "project.h"


project::project(void)
{
}


project::~project(void)
{
}

QString project::getNamge()
{
	return name;
}
void project::setName(QString a)
{
	name =a;
}