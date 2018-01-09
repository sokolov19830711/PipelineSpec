#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDockWidget>
#include <QMdiArea>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include "scriptengine.h"
#include "propertyeditor.h"
#include "sectionlistwidget.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void on_openProjectAction_triggered();
    void on_saveProjectAction_triggered();
    void on_saveProjectAsAction_triggered();
    void on_newProjectAction_triggered();
    void on_newSectionAction_triggered();

protected:
    void closeEvent(QCloseEvent* event);

private:

    QJSValue currentProject_;
    QJSValue currentSection_;

    void setCurrentSection(int index);
    int currentSectionIndex() const;
    ScriptEngine* scriptEngine_;
    QDockWidget* consoleWidget_;

    PropertyEditor* generalProjectDataWidget_;
    QDockWidget* generalProjectDataWidgetDock_;
    PropertyEditor* sectionParamsWidget_;
    QDockWidget* sectionParamsWidgetDock_;
    QDockWidget* itemPropertiesWidgetDock_;
    SectionListWidget* sectionListWidget_;
    QDockWidget* sectionListWidgetDock_;


    QAction* generalProjectDataViewAction_;
    QAction* sectionParamsViewAction_;
    QAction* itemPropertiesViewAction_;
    QAction* sectionListViewAction_;

    QAction *newProjectAction_;
    QAction *openProjectAction_;
    QAction *saveProjectAction_;
    QAction *saveProjectAsAction_;
    QAction *exitAction_;

    QAction* calcSectionParamsAction_;

    QAction *undoAction_;
    QAction *redoAction_;
    QAction *copyAction_;
    QAction *pasteAction_;
    QAction *newSectionAction_;
    QAction *deleteSectionAction_;
    QAction *deleteItemAction_;
    QAction *addPosAction_;
    QAction *deletePosAction_;
    QAction *exportVTinWord_;
    QAction *movePosUpAction_;
    QAction *movePosDownAction_;

    QWidget *centralWidget_;
    QMdiArea *mdiArea_;
    QMenuBar *menuBar_;

    QMenu *fileMenu_;
    QMenu *recentProjectsMenu_;
    QMenu *editMenu_;
    QMenu *projectMenu_;
    QMenu *sectionMenu_;
    QMenu *addItemMenu_;
    QMenu *viewMenu_;
    QMenu *settingsMenu_;
    QMenu *helpMenu_;

    QToolBar *mainToolBar_;
    QStatusBar *statusBar_;
};

#endif // MAINWINDOW_H
