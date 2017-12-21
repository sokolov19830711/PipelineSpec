#include "mainwindow.h"

#include <QDebug>

#include <QSettings>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include "scriptconsolewidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centralWidget_ = new QWidget(this);
    centralWidget_->setObjectName("centralWidget");
    mdiArea_ = new QMdiArea(centralWidget_);
    mdiArea_->setObjectName("mdiArea");
    setCentralWidget(mdiArea_);

    scriptEngine_ = new ScriptEngine(this);
    scriptEngine_->installExtensions(QJSEngine::ConsoleExtension);
//    projectFile_ = new ProjectFile(this);
//    projectFile_->setObjectName("projectFile");
//    scriptEngine_->makeQObjectScriptable(projectFile_, projectFile_->objectName());

    //---Действия-------------------------------------------------------------------------------------------

    newProjectAction_ = new QAction(this);
    newProjectAction_->setObjectName("newProjectAction");
    newProjectAction_->setText("Новый проект");
    newProjectAction_->setIcon(QIcon("data/icons/newProjectIcon.png"));
//    scriptEngine_->makeQObjectScriptable(newProjectAction_, newProjectAction_->objectName());

    openProjectAction_ = new QAction(this);
    openProjectAction_->setObjectName("openProjectAction");
    openProjectAction_->setText("Открыть проект...");
    openProjectAction_->setIcon(QIcon("data/icons/openProjectIcon.png"));
//    scriptEngine_->makeQObjectScriptable(openProjectAction_, openProjectAction_->objectName());

    saveProjectAction_ = new QAction(this);
    saveProjectAction_->setObjectName("saveProjectAction");
    saveProjectAction_->setText("Сохранить");
    saveProjectAction_->setIcon(QIcon("data/icons/saveProjectIcon.png"));
//    scriptEngine_->makeQObjectScriptable(saveProjectAction_, saveProjectAction_->objectName());

    saveProjectAsAction_ = new QAction(this);
    saveProjectAsAction_->setObjectName("saveProjectAsAction");
    saveProjectAsAction_->setText("Сохранить как...");
//    scriptEngine_->makeQObjectScriptable(saveProjectAsAction_, saveProjectAsAction_->objectName());

    newSectionAction_ = new QAction(this);
    newSectionAction_->setObjectName("newSectionAction");
    newSectionAction_->setText("Новый участок");
    newSectionAction_->setIcon(QIcon("data/icons/newSectionIcon.png"));
//    scriptEngine_->makeQObjectScriptable(newSectionAction_, newSectionAction_->objectName());

    exitAction_ = new QAction(this);
    exitAction_->setObjectName("exitAction");
    exitAction_->setText("Выход");

    calcSectionParamsAction_ = new QAction(this);
    calcSectionParamsAction_->setObjectName("calcSectionParamsAction");
    calcSectionParamsAction_->setText("Рассчитать параметры");
    calcSectionParamsAction_->setIcon(QIcon("data/icons/calcSectionParams.png"));
//    scriptEngine_->makeQObjectScriptable(calcSectionParamsAction_, calcSectionParamsAction_->objectName());

    //---Главное меню------------------------------------------------------------------------------------------

    menuBar_ = new QMenuBar(this);
    menuBar_->setObjectName("menuBar");
    fileMenu_ = new QMenu(menuBar_);
    fileMenu_->setObjectName("fileMenu");
    recentProjectsMenu_ = new QMenu(fileMenu_);
    recentProjectsMenu_->setObjectName("recentProjectsMenu");
    QIcon icon15;
    icon15.addFile(QStringLiteral("data/icons/recentProjectsMenuIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
    recentProjectsMenu_->setIcon(icon15);
    editMenu_ = new QMenu(menuBar_);
    editMenu_->setObjectName("editMenu");
    projectMenu_ = new QMenu(menuBar_);
    projectMenu_->setObjectName("projectMenu");
    sectionMenu_ = new QMenu(menuBar_);
    sectionMenu_->setObjectName("sectionMenu");
    addItemMenu_ = new QMenu(sectionMenu_);
    addItemMenu_->setObjectName("addItemMenu");
    QIcon icon16;
    icon16.addFile(QStringLiteral("data/icons/addItemMenuIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
    addItemMenu_->setIcon(icon16);
    viewMenu_ = new QMenu(menuBar_);
    viewMenu_->setObjectName("viewMenu");
    settingsMenu_ = new QMenu(menuBar_);
    settingsMenu_->setObjectName("settingsMenu");
    helpMenu_ = new QMenu(menuBar_);
    helpMenu_->setObjectName("helpMenu");
    setMenuBar(menuBar_);

    menuBar_->addAction(fileMenu_->menuAction());
    menuBar_->addAction(editMenu_->menuAction());
    menuBar_->addAction(projectMenu_->menuAction());
    menuBar_->addAction(sectionMenu_->menuAction());
    menuBar_->addAction(viewMenu_->menuAction());
    menuBar_->addAction(settingsMenu_->menuAction());
    menuBar_->addAction(helpMenu_->menuAction());
    fileMenu_->setTitle("Файл");
    editMenu_->setTitle("Правка");
    projectMenu_->setTitle("Проект");
    sectionMenu_->setTitle("Участок");
    viewMenu_->setTitle("Вид");
    settingsMenu_->setTitle("Настройки");
    helpMenu_->setTitle("Помощь");

    fileMenu_->addAction(newProjectAction_);
    fileMenu_->addAction(openProjectAction_);
    fileMenu_->addAction(recentProjectsMenu_->menuAction());
    fileMenu_->addSeparator();
    fileMenu_->addAction(saveProjectAction_);
    fileMenu_->addAction(saveProjectAsAction_);
    fileMenu_->addAction(exitAction_);

    projectMenu_->addAction(newSectionAction_);

    sectionMenu_->addAction(calcSectionParamsAction_);

    //---Главная панель инструментов------------------------------------------------------------------

    mainToolBar_ = new QToolBar(this);
    mainToolBar_->setObjectName("mainToolBar");
    addToolBar(Qt::TopToolBarArea, mainToolBar_);
    mainToolBar_->addAction(newProjectAction_);
    mainToolBar_->addAction(openProjectAction_);
    mainToolBar_->addAction(saveProjectAction_);
    mainToolBar_->addSeparator();
    mainToolBar_->addAction(newSectionAction_);
    mainToolBar_->addAction(calcSectionParamsAction_);

    statusBar_ = new QStatusBar(this);
    statusBar_->setObjectName("statusBar");
    setStatusBar(statusBar_);

    //---скриптовая консоль-----------------------------------------------------

    consoleWidget_ = new QDockWidget(this);
    consoleWidget_->setObjectName("consoleWidget");
    consoleWidget_->setWidget(new ScriptConsoleWidget(scriptEngine_, this));
    consoleWidget_->setWindowTitle("Консоль JavaScript");
    addDockWidget(Qt::LeftDockWidgetArea, consoleWidget_, Qt::Vertical);
    viewMenu_->addAction(consoleWidget_->toggleViewAction());
    scriptEngine_->makeQObjectScriptable(consoleWidget_, consoleWidget_->objectName());

    //--------------------------------------------------------------------------

    QMetaObject::connectSlotsByName(this);

    QSettings settings("settings",  QSettings::IniFormat, this);
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QSettings settings("settings",  QSettings::IniFormat, this);
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}

void MainWindow::on_openProjectAction_triggered()
{
    QFile file(QFileDialog::getOpenFileName(this, "Открыть проект", "projects", "Файлы проектов PipelineSpec (*.psp)"));
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
//        QTextStream in(&file);
//        in.setCodec("Utf-8");
        QJSValue proj = scriptEngine_->toScriptValue((QJsonDocument::fromJson(file.readAll())).toVariant());
        scriptEngine_->globalObject().setProperty("proj",proj);
    }
}
