/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_project;
    QAction *actionNew_program;
    QAction *actionOpen_project;
    QAction *actionClose_file;
    QAction *actionClose_project;
    QAction *actionSave_project;
    QAction *actionSava_as;
    QAction *actionPrint;
    QAction *actionExit;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionChinese;
    QAction *actionEnglish;
    QAction *actionVoice;
    QAction *actionImage;
    QAction *actionMymodule;
    QAction *actionUpdate;
    QAction *actionWireless;
    QAction *actionModuleImport;
    QAction *actionDownload;
    QAction *actionMemoryBrowser;
    QAction *actionLogManager;
    QAction *actionDeleteFromDateSet;
    QAction *actionCreateLogProject;
    QAction *actionExportDateSet;
    QAction *actionImportProjectBlock;
    QAction *actionContextHelp;
    QAction *actionEV3help;
    QAction *actionUpdateSoftware;
    QAction *actionAbout;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *projects;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout;
    QTabWidget *programs;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_3;
    QGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout;
    QTabWidget *modules;
    QWidget *green;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer;
    QWidget *orange;
    QWidget *yellow;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QWidget *red;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QWidget *blue;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QWidget *mymodule;
    QWidget *gridLayoutWidget_6;
    QGridLayout *gridLayout_6;
    QLabel *label_43;
    QMenuBar *menuBar;
    QMenu *file;
    QMenu *edit;
    QMenu *menuLanguage;
    QMenu *tool;
    QMenu *help;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1693, 757);
        MainWindow->setStyleSheet(QStringLiteral(""));
        actionNew_project = new QAction(MainWindow);
        actionNew_project->setObjectName(QStringLiteral("actionNew_project"));
        actionNew_program = new QAction(MainWindow);
        actionNew_program->setObjectName(QStringLiteral("actionNew_program"));
        actionOpen_project = new QAction(MainWindow);
        actionOpen_project->setObjectName(QStringLiteral("actionOpen_project"));
        actionClose_file = new QAction(MainWindow);
        actionClose_file->setObjectName(QStringLiteral("actionClose_file"));
        actionClose_project = new QAction(MainWindow);
        actionClose_project->setObjectName(QStringLiteral("actionClose_project"));
        actionSave_project = new QAction(MainWindow);
        actionSave_project->setObjectName(QStringLiteral("actionSave_project"));
        actionSava_as = new QAction(MainWindow);
        actionSava_as->setObjectName(QStringLiteral("actionSava_as"));
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName(QStringLiteral("actionPrint"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QStringLiteral("actionCut"));
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QStringLiteral("actionCopy"));
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QStringLiteral("actionPaste"));
        actionChinese = new QAction(MainWindow);
        actionChinese->setObjectName(QStringLiteral("actionChinese"));
        actionEnglish = new QAction(MainWindow);
        actionEnglish->setObjectName(QStringLiteral("actionEnglish"));
        actionVoice = new QAction(MainWindow);
        actionVoice->setObjectName(QStringLiteral("actionVoice"));
        actionVoice->setShortcutContext(Qt::WidgetShortcut);
        actionImage = new QAction(MainWindow);
        actionImage->setObjectName(QStringLiteral("actionImage"));
        actionMymodule = new QAction(MainWindow);
        actionMymodule->setObjectName(QStringLiteral("actionMymodule"));
        actionUpdate = new QAction(MainWindow);
        actionUpdate->setObjectName(QStringLiteral("actionUpdate"));
        actionWireless = new QAction(MainWindow);
        actionWireless->setObjectName(QStringLiteral("actionWireless"));
        actionModuleImport = new QAction(MainWindow);
        actionModuleImport->setObjectName(QStringLiteral("actionModuleImport"));
        actionDownload = new QAction(MainWindow);
        actionDownload->setObjectName(QStringLiteral("actionDownload"));
        actionMemoryBrowser = new QAction(MainWindow);
        actionMemoryBrowser->setObjectName(QStringLiteral("actionMemoryBrowser"));
        actionLogManager = new QAction(MainWindow);
        actionLogManager->setObjectName(QStringLiteral("actionLogManager"));
        actionDeleteFromDateSet = new QAction(MainWindow);
        actionDeleteFromDateSet->setObjectName(QStringLiteral("actionDeleteFromDateSet"));
        actionCreateLogProject = new QAction(MainWindow);
        actionCreateLogProject->setObjectName(QStringLiteral("actionCreateLogProject"));
        actionExportDateSet = new QAction(MainWindow);
        actionExportDateSet->setObjectName(QStringLiteral("actionExportDateSet"));
        actionImportProjectBlock = new QAction(MainWindow);
        actionImportProjectBlock->setObjectName(QStringLiteral("actionImportProjectBlock"));
        actionContextHelp = new QAction(MainWindow);
        actionContextHelp->setObjectName(QStringLiteral("actionContextHelp"));
        actionEV3help = new QAction(MainWindow);
        actionEV3help->setObjectName(QStringLiteral("actionEV3help"));
        actionUpdateSoftware = new QAction(MainWindow);
        actionUpdateSoftware->setObjectName(QStringLiteral("actionUpdateSoftware"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(255, 255, 255);"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(12, 12, 12, 12);
        projects = new QTabWidget(centralWidget);
        projects->setObjectName(QStringLiteral("projects"));
        projects->setStyleSheet(QLatin1String("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);\n"
""));
        projects->setTabsClosable(true);
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        verticalLayout = new QVBoxLayout(tab_4);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        programs = new QTabWidget(tab_4);
        programs->setObjectName(QStringLiteral("programs"));
        programs->setStyleSheet(QStringLiteral(""));
        programs->setTabsClosable(true);
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        verticalLayout_3 = new QVBoxLayout(tab_6);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        graphicsView = new QGraphicsView(tab_6);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setEnabled(true);
        graphicsView->setFrameShape(QFrame::NoFrame);
        graphicsView->setFrameShadow(QFrame::Sunken);
        graphicsView->setLineWidth(0);
        graphicsView->setMidLineWidth(0);

        verticalLayout_3->addWidget(graphicsView);

        programs->addTab(tab_6, QString());

        verticalLayout->addWidget(programs);

        projects->addTab(tab_4, QString());

        verticalLayout_2->addWidget(projects);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        modules = new QTabWidget(centralWidget);
        modules->setObjectName(QStringLiteral("modules"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(modules->sizePolicy().hasHeightForWidth());
        modules->setSizePolicy(sizePolicy);
        modules->setMinimumSize(QSize(0, 168));
        modules->setMaximumSize(QSize(16777215, 168));
        modules->setAutoFillBackground(false);
        modules->setStyleSheet(QLatin1String("QTabWidget::tab-bar {left: 250px; }\n"
"background-image: url(:/image/mainwindow/widget.png);"));
        modules->setTabShape(QTabWidget::Rounded);
        modules->setIconSize(QSize(62, 21));
        modules->setElideMode(Qt::ElideNone);
        green = new QWidget();
        green->setObjectName(QStringLiteral("green"));
        green->setStyleSheet(QStringLiteral("background-image: url(:/image/mainwindow/1276_168.png);"));
        horizontalLayout_2 = new QHBoxLayout(green);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 23, -1, -1);
        horizontalSpacer_2 = new QSpacerItem(72, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label = new QLabel(green);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(117, 110));
        label->setMaximumSize(QSize(117, 110));
        label->setLineWidth(0);
        label->setPixmap(QPixmap(QString::fromUtf8(":/image/mainwindow/green_1.png")));

        horizontalLayout_2->addWidget(label);

        label_2 = new QLabel(green);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMinimumSize(QSize(117, 110));
        label_2->setMaximumSize(QSize(117, 110));
        label_2->setLineWidth(0);
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/image/mainwindow/green_2.png")));

        horizontalLayout_2->addWidget(label_2);

        label_3 = new QLabel(green);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setMinimumSize(QSize(117, 110));
        label_3->setMaximumSize(QSize(117, 110));
        label_3->setLineWidth(0);
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/image/mainwindow/green_3.png")));

        horizontalLayout_2->addWidget(label_3);

        label_4 = new QLabel(green);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setMinimumSize(QSize(117, 110));
        label_4->setMaximumSize(QSize(117, 110));
        label_4->setLineWidth(0);
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/image/mainwindow/green_4.png")));

        horizontalLayout_2->addWidget(label_4);

        label_5 = new QLabel(green);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        label_5->setMinimumSize(QSize(117, 110));
        label_5->setMaximumSize(QSize(117, 110));
        label_5->setLineWidth(0);
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/image/mainwindow/green_5.png")));

        horizontalLayout_2->addWidget(label_5);

        label_6 = new QLabel(green);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);
        label_6->setMinimumSize(QSize(117, 110));
        label_6->setMaximumSize(QSize(117, 110));
        label_6->setLineWidth(0);
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/image/mainwindow/green_6.png")));

        horizontalLayout_2->addWidget(label_6);

        label_7 = new QLabel(green);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);
        label_7->setMinimumSize(QSize(117, 110));
        label_7->setMaximumSize(QSize(117, 110));
        label_7->setLineWidth(0);
        label_7->setPixmap(QPixmap(QString::fromUtf8(":/image/mainwindow/green_5.png")));

        horizontalLayout_2->addWidget(label_7);

        horizontalSpacer = new QSpacerItem(72, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        QIcon icon;
        icon.addFile(QStringLiteral(":/image/mainwindow/green.png"), QSize(), QIcon::Normal, QIcon::Off);
        modules->addTab(green, icon, QString());
        orange = new QWidget();
        orange->setObjectName(QStringLiteral("orange"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/image/mainwindow/yellow.png"), QSize(), QIcon::Normal, QIcon::Off);
        modules->addTab(orange, icon1, QString());
        yellow = new QWidget();
        yellow->setObjectName(QStringLiteral("yellow"));
        gridLayoutWidget_3 = new QWidget(yellow);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(300, 40, 160, 80));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/image/mainwindow/orange.png"), QSize(), QIcon::Normal, QIcon::Off);
        modules->addTab(yellow, icon2, QString());
        red = new QWidget();
        red->setObjectName(QStringLiteral("red"));
        gridLayoutWidget_2 = new QWidget(red);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(350, 50, 160, 80));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/image/mainwindow/white.png"), QSize(), QIcon::Normal, QIcon::Off);
        modules->addTab(red, icon3, QString());
        blue = new QWidget();
        blue->setObjectName(QStringLiteral("blue"));
        gridLayoutWidget = new QWidget(blue);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(300, 30, 160, 80));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        modules->addTab(blue, icon, QString());
        mymodule = new QWidget();
        mymodule->setObjectName(QStringLiteral("mymodule"));
        gridLayoutWidget_6 = new QWidget(mymodule);
        gridLayoutWidget_6->setObjectName(QStringLiteral("gridLayoutWidget_6"));
        gridLayoutWidget_6->setGeometry(QRect(120, 10, 160, 80));
        gridLayout_6 = new QGridLayout(gridLayoutWidget_6);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/image/mainwindow/blue.png"), QSize(), QIcon::Normal, QIcon::Off);
        modules->addTab(mymodule, icon4, QString());

        horizontalLayout->addWidget(modules);

        label_43 = new QLabel(centralWidget);
        label_43->setObjectName(QStringLiteral("label_43"));
        sizePolicy1.setHeightForWidth(label_43->sizePolicy().hasHeightForWidth());
        label_43->setSizePolicy(sizePolicy1);
        label_43->setMinimumSize(QSize(623, 217));
        label_43->setMaximumSize(QSize(623, 217));
        label_43->setPixmap(QPixmap(QString::fromUtf8(":/image/mainwindow/623_217.png")));

        horizontalLayout->addWidget(label_43);


        verticalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1693, 23));
        menuBar->setAutoFillBackground(false);
        menuBar->setStyleSheet(QStringLiteral(""));
        file = new QMenu(menuBar);
        file->setObjectName(QStringLiteral("file"));
        file->setStyleSheet(QStringLiteral(""));
        edit = new QMenu(menuBar);
        edit->setObjectName(QStringLiteral("edit"));
        menuLanguage = new QMenu(edit);
        menuLanguage->setObjectName(QStringLiteral("menuLanguage"));
        tool = new QMenu(menuBar);
        tool->setObjectName(QStringLiteral("tool"));
        help = new QMenu(menuBar);
        help->setObjectName(QStringLiteral("help"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(file->menuAction());
        menuBar->addAction(edit->menuAction());
        menuBar->addAction(tool->menuAction());
        menuBar->addAction(help->menuAction());
        file->addAction(actionNew_project);
        file->addAction(actionNew_program);
        file->addAction(actionOpen_project);
        file->addSeparator();
        file->addAction(actionClose_file);
        file->addAction(actionClose_project);
        file->addSeparator();
        file->addAction(actionSave_project);
        file->addAction(actionSava_as);
        file->addSeparator();
        file->addAction(actionPrint);
        file->addSeparator();
        file->addAction(actionExit);
        edit->addAction(actionUndo);
        edit->addAction(actionRedo);
        edit->addSeparator();
        edit->addAction(actionCut);
        edit->addAction(actionCopy);
        edit->addAction(actionPaste);
        edit->addAction(menuLanguage->menuAction());
        menuLanguage->addAction(actionChinese);
        menuLanguage->addAction(actionEnglish);
        tool->addAction(actionVoice);
        tool->addAction(actionImage);
        tool->addAction(actionMymodule);
        tool->addAction(actionUpdate);
        tool->addAction(actionWireless);
        tool->addAction(actionModuleImport);
        tool->addAction(actionDownload);
        tool->addAction(actionMemoryBrowser);
        tool->addAction(actionLogManager);
        tool->addAction(actionDeleteFromDateSet);
        tool->addAction(actionCreateLogProject);
        tool->addAction(actionExportDateSet);
        tool->addAction(actionImportProjectBlock);
        help->addAction(actionContextHelp);
        help->addAction(actionEV3help);
        help->addSeparator();
        help->addAction(actionUpdateSoftware);
        help->addSeparator();
        help->addAction(actionAbout);

        retranslateUi(MainWindow);

        projects->setCurrentIndex(0);
        programs->setCurrentIndex(0);
        modules->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionNew_project->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", 0));
        actionNew_program->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\347\250\213\345\272\217", 0));
        actionNew_program->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        actionOpen_project->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\351\241\271\347\233\256", 0));
        actionOpen_project->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionClose_file->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\346\226\207\346\241\243", 0));
        actionClose_file->setShortcut(QApplication::translate("MainWindow", "Ctrl+W", 0));
        actionClose_project->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\351\241\271\347\233\256", 0));
        actionClose_project->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+W", 0));
        actionSave_project->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\351\241\271\347\233\256", 0));
        actionSave_project->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionSava_as->setText(QApplication::translate("MainWindow", "\351\241\271\347\233\256\345\217\246\345\255\230\344\270\272...", 0));
        actionSava_as->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", 0));
        actionPrint->setText(QApplication::translate("MainWindow", "\346\211\223\345\215\260", 0));
        actionPrint->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0));
        actionExit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0));
        actionUndo->setText(QApplication::translate("MainWindow", "\346\222\244\351\224\200", 0));
        actionUndo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", 0));
        actionRedo->setText(QApplication::translate("MainWindow", "\351\207\215\345\201\232", 0));
        actionRedo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Y", 0));
        actionCut->setText(QApplication::translate("MainWindow", "\345\211\252\345\210\207", 0));
        actionCut->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0));
        actionCopy->setText(QApplication::translate("MainWindow", "\345\244\215\345\210\266", 0));
        actionCopy->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0));
        actionPaste->setText(QApplication::translate("MainWindow", "\347\262\230\350\264\264", 0));
        actionPaste->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", 0));
        actionChinese->setText(QApplication::translate("MainWindow", "\344\270\255\346\226\207", 0));
        actionEnglish->setText(QApplication::translate("MainWindow", "\350\213\261\346\226\207", 0));
        actionVoice->setText(QApplication::translate("MainWindow", "\345\243\260\351\237\263\347\274\226\350\276\221\345\231\250", 0));
        actionVoice->setShortcut(QApplication::translate("MainWindow", "S", 0));
        actionImage->setText(QApplication::translate("MainWindow", "\345\233\276\345\203\217\347\274\226\350\276\221\345\231\250", 0));
        actionMymodule->setText(QApplication::translate("MainWindow", "\346\210\221\347\232\204\346\250\241\345\235\227\345\210\233\345\273\272\345\231\250", 0));
        actionUpdate->setText(QApplication::translate("MainWindow", "\345\233\272\344\273\266\345\215\207\347\272\247", 0));
        actionWireless->setText(QApplication::translate("MainWindow", "\346\227\240\347\272\277\350\256\276\347\275\256", 0));
        actionModuleImport->setText(QApplication::translate("MainWindow", "\346\250\241\345\235\227\345\257\274\345\205\245\345\220\221\345\257\274", 0));
        actionDownload->setText(QApplication::translate("MainWindow", "\344\275\234\344\270\272\345\272\224\347\224\250\344\270\213\350\275\275", 0));
        actionMemoryBrowser->setText(QApplication::translate("MainWindow", "\345\206\205\345\255\230\346\265\217\350\247\210\345\231\250", 0));
        actionLogManager->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\346\227\245\345\277\227\346\226\207\344\273\266\347\256\241\347\220\206\345\231\250", 0));
        actionDeleteFromDateSet->setText(QApplication::translate("MainWindow", "\344\273\216\346\225\260\346\215\256\350\256\276\345\244\207\344\270\255\345\210\240\351\231\244\345\200\274", 0));
        actionCreateLogProject->setText(QApplication::translate("MainWindow", "\345\210\233\345\273\272\346\225\260\346\215\256\346\227\245\345\277\227\347\250\213\345\272\217", 0));
        actionExportDateSet->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272\346\225\260\346\215\256\350\256\276\347\275\256", 0));
        actionImportProjectBlock->setText(QApplication::translate("MainWindow", "\345\257\274\345\205\245\347\250\213\345\272\217\345\235\227\347\250\213\345\272\217", 0));
        actionContextHelp->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272\344\270\212\344\270\213\346\226\207\345\270\256\345\212\251", 0));
        actionContextHelp->setShortcut(QApplication::translate("MainWindow", "Ctrl+H", 0));
        actionEV3help->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272EV3\345\270\256\345\212\251", 0));
        actionUpdateSoftware->setText(QApplication::translate("MainWindow", "\346\243\200\346\237\245\350\275\257\344\273\266\346\233\264\346\226\260", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216...", 0));
        programs->setTabText(programs->indexOf(tab_6), QApplication::translate("MainWindow", "Tab 1", 0));
        projects->setTabText(projects->indexOf(tab_4), QApplication::translate("MainWindow", "Tab 1", 0));
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QString());
        label_5->setText(QString());
        label_6->setText(QString());
        label_7->setText(QString());
        modules->setTabText(modules->indexOf(green), QString());
        modules->setTabText(modules->indexOf(orange), QString());
        modules->setTabText(modules->indexOf(yellow), QString());
        modules->setTabText(modules->indexOf(red), QString());
        modules->setTabText(modules->indexOf(blue), QString());
        modules->setTabText(modules->indexOf(mymodule), QString());
        label_43->setText(QString());
        file->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", 0));
        edit->setTitle(QApplication::translate("MainWindow", "\347\274\226\350\276\221", 0));
        menuLanguage->setTitle(QApplication::translate("MainWindow", "\346\233\264\346\224\271\350\257\255\350\250\200", 0));
        tool->setTitle(QApplication::translate("MainWindow", "\345\267\245\345\205\267", 0));
        help->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
