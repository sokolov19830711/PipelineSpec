#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <QJSEngine>

class ScriptEngine : public QJSEngine
{
    Q_OBJECT
public:
    explicit ScriptEngine(QObject *parent = 0);
    ~ScriptEngine();
    void makeQObjectScriptable(QObject* object, QString prefixName);
    QJSValue evaluateScriptFromFile(const QString& scriptFileName);
    QList<QJSValue> evaluateScriptsFromDirectory(const QString& directoryName);

signals:

public slots:
};

#endif // SCRIPTENGINE_H
