#include "scriptengine.h"

#include <QFile>
#include <QDir>
#include <QTextStream>

ScriptEngine::ScriptEngine(QObject *parent) : QJSEngine(parent)
{

}

ScriptEngine::~ScriptEngine()
{

}

void ScriptEngine::makeQObjectScriptable(QObject* object, QString prefixName)
{
    QString objectName = object->objectName();
    if (objectName != "")
    {
        if (objectName != prefixName)
        {
            objectName = prefixName + "_" + objectName;
        }
        this->globalObject().setProperty(objectName, this->newQObject(object));

//        QObjectList children = object->children();
//        if (!children.isEmpty())
//        {
//            for (auto & i : children)
//            {
//                makeQObjectScriptable(i, prefixName);
//            }
//        }
    }
}

QJSValue ScriptEngine::evaluateScriptFromFile(const QString& scriptFileName)
{
    QFile scriptFile(scriptFileName);
    scriptFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&scriptFile);
    in.setCodec("Utf-8");
    QJSValue scriptResult = this->evaluate(QString(in.readAll()));
    scriptFile.close();
    return scriptResult;
}

QList<QJSValue> ScriptEngine::evaluateScriptsFromDirectory(const QString& directoryName)
{
    QDir scriptsDir = QDir(directoryName, "*.js", QDir::Name, QDir::Files);
    QStringList fileNames = scriptsDir.entryList();
    QList<QJSValue> results;

    for (auto & i : fileNames)
    {
        results.push_back(evaluateScriptFromFile(scriptsDir.absoluteFilePath(i)));
    }

    return results;
}
