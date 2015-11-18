#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"project.h"
#include"bottom_label.h"
#include "msgInterface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
	void MainWindow::addProgram(QWidget * parent);
	void MainWindow::addProject();
	QList<project> projectList;
	void save();
public:
	bottom_label* GetLabelPtr(int id);


/* 
* Date:2015-10-19
* 
*    Author: Bill Wang
*/

public:
	void whWork();

private:
	msgInterface msginterface;
	
};

#endif // MAINWINDOW_H
