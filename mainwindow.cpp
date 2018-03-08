#include "mainwindow.h"

#include <QDebug>

#include <QSettings>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QMessageBox>
#include "scriptconsolewidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//    centralWidget_ = new QWidget(this);
//    centralWidget_->setObjectName("centralWidget");
//    mdiArea_ = new QMdiArea(centralWidget_);
//    mdiArea_->setObjectName("mdiArea");
    itemListWidget_ = new ItemListWidget(this);

//    textEdit_ = new QTextEdit(this);
//    QFile* file = new QFile("ВТ — тест.htm");
//    file->open(QIODevice::ReadOnly | QIODevice::Text);
//    textEdit_->setHtml(QString(file->readAll()));
//    setCentralWidget(textEdit_);

    setCentralWidget(itemListWidget_);

    scriptEngine_ = new ScriptEngine(this);
    scriptEngine_->installExtensions(QJSEngine::ConsoleExtension);

    //---Действия-------------------------------------------------------------------------------------------

    newProjectAction_ = new QAction(this);
    newProjectAction_->setObjectName("newProjectAction");
    newProjectAction_->setText("Новый проект");
    newProjectAction_->setIcon(QIcon("data/icons/newProjectIcon.png"));

    openProjectAction_ = new QAction(this);
    openProjectAction_->setObjectName("openProjectAction");
    openProjectAction_->setText("Открыть проект...");
    openProjectAction_->setIcon(QIcon("data/icons/openProjectIcon.png"));

    saveProjectAction_ = new QAction(this);
    saveProjectAction_->setObjectName("saveProjectAction");
    saveProjectAction_->setText("Сохранить");
    saveProjectAction_->setIcon(QIcon("data/icons/saveProjectIcon.png"));

    saveProjectAsAction_ = new QAction(this);
    saveProjectAsAction_->setObjectName("saveProjectAsAction");
    saveProjectAsAction_->setText("Сохранить как...");

    newSectionAction_ = new QAction(this);
    newSectionAction_->setObjectName("newSectionAction");
    newSectionAction_->setText("Новый участок");
    newSectionAction_->setIcon(QIcon("data/icons/newSectionIcon.png"));

    deleteSectionAction_ = new QAction(this);
    deleteSectionAction_->setObjectName("deleteSectionAction");
    deleteSectionAction_->setText("Удалить участок");
    deleteSectionAction_->setIcon(QIcon("data/icons/deleteSectionIcon.png"));

    exitAction_ = new QAction(this);
    exitAction_->setObjectName("exitAction");
    exitAction_->setText("Выход");

    calcSectionParamsAction_ = new QAction(this);
    calcSectionParamsAction_->setObjectName("calcSectionParamsAction");
    calcSectionParamsAction_->setText("Рассчитать параметры");
    calcSectionParamsAction_->setIcon(QIcon("data/icons/calcSectionParams.png"));

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
    projectMenu_->addAction(deleteSectionAction_);

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
    mainToolBar_->addAction(deleteSectionAction_);
    mainToolBar_->addAction(calcSectionParamsAction_);

    statusBar_ = new QStatusBar(this);
    statusBar_->setObjectName("statusBar");
    setStatusBar(statusBar_);

    //---виджет общих данных проекта--------------------------------------------

    generalProjectDataWidgetDock_ = new QDockWidget(this);
    generalProjectDataWidget_ = new PropertyEditor("generalProjectDataWidget", generalProjectDataWidgetDock_);
    generalProjectDataWidgetDock_->setObjectName("generalProjectDataWidgetDock");
    generalProjectDataWidgetDock_->setWidget(generalProjectDataWidget_);
    generalProjectDataWidgetDock_->setWindowTitle("Общие данные проекта");
    generalProjectDataViewAction_ = generalProjectDataWidgetDock_->toggleViewAction();
    //    generalProjectDataViewAction_->setIcon(QIcon("data/icons/generalProjectDataIcon.png"));
    viewMenu_->addAction(generalProjectDataViewAction_);
    addDockWidget(Qt::LeftDockWidgetArea, generalProjectDataWidgetDock_, Qt::Vertical);

    //---виджет парметров участка--------------------------------------------

    sectionParamsWidgetDock_ = new QDockWidget(this);
    sectionParamsWidget_ = new PropertyEditor("sectionParamsWidget", generalProjectDataWidgetDock_);
    sectionParamsWidgetDock_->setObjectName("sectionParamsWidgetDock");
    sectionParamsWidgetDock_->setWidget(sectionParamsWidget_);
    sectionParamsWidgetDock_->setWindowTitle("Параметры участка");
    sectionParamsViewAction_ = sectionParamsWidgetDock_->toggleViewAction();
    viewMenu_->addAction(sectionParamsViewAction_);
    addDockWidget(Qt::LeftDockWidgetArea, sectionParamsWidgetDock_, Qt::Vertical);

    //---виджет со списком участков-----------------------------------------------

    sectionListWidgetDock_ = new QDockWidget(this);
    sectionListWidget_ = new SectionListWidget(generalProjectDataWidgetDock_);
    sectionListWidgetDock_->setObjectName("sectionListWidgetDock");
    sectionListWidgetDock_->setWidget(sectionListWidget_);
    sectionListWidgetDock_->setWindowTitle("Список участков");
    sectionListViewAction_ = sectionListWidgetDock_->toggleViewAction();
    viewMenu_->addAction(sectionListViewAction_);
    addDockWidget(Qt::RightDockWidgetArea, sectionListWidgetDock_, Qt::Vertical);

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
    connect(sectionParamsWidget_, &PropertyEditor::propertyValueChanged, sectionListWidget_, &SectionListWidget::on_propertyValueChanged);
    connect(sectionListWidget_, &SectionListWidget::currentSectionChanged, this, MainWindow::sectionListWidget_currentSectionChanged);

    QSettings settings("settings",  QSettings::IniFormat, this);
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());

    scriptEngine_->evaluateScriptFromFile("data/section.js");
    scriptEngine_->evaluateScriptFromFile("data/project.js");
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

//---private functions-------------------------------------------------------------------------------------------

void MainWindow::setCurrentSection(int index)
{
    if (index >= 0 and index < scriptEngine_->globalObject().property("currentProject").property("sectionList").property("length").toInt())
    {
        currentSection_ = scriptEngine_->globalObject().property("currentProject").property("sectionList").property(index);
        scriptEngine_->globalObject().setProperty("currentSection", currentSection_);
        currentProject_.setProperty("currentSectionIndex", index);
        sectionParamsWidget_->setupEditor(currentSection_);
        sectionParamsWidget_->refreshValues();
        sectionListWidget_->setupWidget(currentProject_);
    }
}

int MainWindow::currentSectionIndex() const
{
    return currentProject_.property("currentSectionIndex").toInt();
}

//---public slots----------------------------------------------------------------------------------------------

void MainWindow::on_openProjectAction_triggered()
{
    QFile file(QFileDialog::getOpenFileName(this, "Открыть проект", "projects", "Файлы проектов PipelineSpec (*.psp)"));
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        scriptEngine_->globalObject().deleteProperty("currentProject");
        currentProject_ = scriptEngine_->toScriptValue((QJsonDocument::fromJson(file.readAll())).toVariant());
        scriptEngine_->globalObject().setProperty("currentProject", currentProject_);
        currentProject_.setProperty("projectFileName", file.fileName());
        currentProject_.setPrototype(scriptEngine_->globalObject().property("project"));
        scriptEngine_->globalObject().property("restoreItemTypes").call({currentProject_.property("sectionList")});
        generalProjectDataWidget_->setupEditor(currentProject_);
        generalProjectDataWidget_->refreshValues();
        setCurrentSection(currentSectionIndex());
        sectionListWidget_->setupWidget(currentProject_);
    }
}

void MainWindow::on_saveProjectAction_triggered()
{
    if (currentProject_.property("projectFileName").toString() == "")
    {
        on_saveProjectAsAction_triggered();
        return;
    }

    QFile file(currentProject_.property("projectFileName").toString());
    if (file.open(QIODevice::WriteOnly))
    {
        file.write((QJsonDocument::fromVariant(currentProject_.toVariant())).toJson());
    }
}

void MainWindow::on_saveProjectAsAction_triggered()
{
    QFile file(QFileDialog::getSaveFileName(this, "Сохранить проект", "projects", "Файлы проектов PipelineSpec (*.psp)"));
    if (file.open(QIODevice::WriteOnly))
    {
        currentProject_.setProperty("projectFileName", file.fileName());
        file.write((QJsonDocument::fromVariant(currentProject_.toVariant())).toJson());
    }
}

void MainWindow::on_newProjectAction_triggered()
{
    scriptEngine_->globalObject().deleteProperty("currentProject");
    currentProject_ = scriptEngine_->globalObject().property("EmptyProject").callAsConstructor();
    currentProject_.setPrototype(scriptEngine_->globalObject().property("project"));
    scriptEngine_->globalObject().setProperty("currentProject", currentProject_);
    generalProjectDataWidget_->setupEditor(currentProject_);
    generalProjectDataWidget_->refreshValues();
    sectionParamsWidget_->clearTable();
    sectionListWidget_->setupWidget(currentProject_);
}

void MainWindow::on_newSectionAction_triggered()
{
    currentProject_.property("addNewSection").callWithInstance(currentProject_);
    setCurrentSection(currentSectionIndex());
}

void MainWindow::on_deleteSectionAction_triggered()
{
    if (QMessageBox::question(this, "Удаление выбранного участка", "Вы действительно хотите удалить участок?", "Удалить", "Отмена") == QMessageBox::NoButton)
    {
        currentProject_.property("deleteCurrentSection").callWithInstance(currentProject_);
        setCurrentSection(currentSectionIndex());
    }
}

void MainWindow::on_calcSectionParamsAction_triggered()
{
    currentSection_.property("calc").callWithInstance({currentSection_});
    sectionParamsWidget_->refreshValues();
}

void MainWindow::sectionListWidget_currentSectionChanged(int sectionIndex)
{
    if (sectionIndex != -1)
    {
        setCurrentSection(sectionIndex);
    }
}
