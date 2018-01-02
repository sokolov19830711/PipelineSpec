#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QDoubleSpinBox>

#include "scriptengine.h"

class PropertyEditor : public QWidget
{
    Q_OBJECT

public:
    explicit PropertyEditor(const QString& name, ScriptEngine* scriptEngine, QWidget *parent = 0);
    ~PropertyEditor();

    void setupEditor(QJSValue& item);
    void refreshValues();

    void setComboBox();
    void removeComboBox(int row);

    void setLineEdit();
    void removeLineEdit(int row);

    void setSpinBox();
    void removeSpinBox(int row);

signals:


protected:

private:

    ScriptEngine* scriptEngine_;
    QTableWidget* table_;
    QLabel* image_;
    QLabel* imageCaption_;
    QVBoxLayout* layout_;
    QJSValue item_;

    QVariant propertyDesc(int row, const QString& descriptorName) const;
    QString widgetType(int row) const;
    QString propertyName(int row) const;
    QStringList valueList(int row) const;
    void writePropertyValue(int row, const QString& value) const;

public slots:

    void currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
};

#endif // PROPERTYEDITOR_H
