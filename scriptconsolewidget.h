#ifndef SCRIPTCONSOLEWIDGET_H
#define SCRIPTCONSOLEWIDGET_H

#include <QJSEngine>
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QKeyEvent>

class ScriptConsoleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScriptConsoleWidget(QJSEngine *scriptEngine, QWidget *parent = 0);
    ~ScriptConsoleWidget();

private:
    QJSEngine* scriptEngine_;
    QTextEdit* consoleOutput_;
    QLineEdit* cmdLine_;
    QVBoxLayout* layout_;

protected:

    void keyPressEvent(QKeyEvent* event);

};

#endif // SCRIPTCONSOLEWIDGET_H
