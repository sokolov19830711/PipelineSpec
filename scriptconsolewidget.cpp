#include "scriptconsolewidget.h"

ScriptConsoleWidget::ScriptConsoleWidget(QJSEngine *scriptEngine, QWidget *parent) : QWidget(parent)
{
    setObjectName("scriptConsoleWidget");
    setWindowFlags(Qt::Tool);
    if (scriptEngine != nullptr) scriptEngine_ = scriptEngine;
    else scriptEngine_ = new QJSEngine;

    consoleOutput_ = new QTextEdit(this);
    consoleOutput_->setObjectName("consoleOutput");
    consoleOutput_->setReadOnly(true);
    cmdLine_ = new QLineEdit(this);
    cmdLine_->setObjectName("cmdLine");
    layout_ = new QVBoxLayout(this);

    layout_->addWidget(consoleOutput_);
    layout_->addWidget(cmdLine_);
    setLayout(layout_);

}

ScriptConsoleWidget::~ScriptConsoleWidget()
{

}

void ScriptConsoleWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return or event->key() == Qt::Key_Enter)
    {
        QString currentCmd = cmdLine_->text();
        cmdLine_->clear();
        consoleOutput_->insertPlainText(currentCmd);
        consoleOutput_->insertPlainText("->");
        consoleOutput_->insertPlainText("\n");
        consoleOutput_->insertPlainText(scriptEngine_->evaluate(currentCmd).toString());
        consoleOutput_->insertPlainText("\n\n");
    }
}
