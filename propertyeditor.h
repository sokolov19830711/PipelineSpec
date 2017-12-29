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

//    Q_PROPERTY(int rowCount READ rowCount WRITE setRowCount)

//    Q_INVOKABLE int rowCount() const;
//    Q_INVOKABLE void setRowCount(int rowCount);
//    Q_INVOKABLE int currentRow() const;

//    Q_INVOKABLE QString cellText(int row, int column) const;
//    Q_INVOKABLE void setCellText(int row, int column, const QString& text = "");
//    Q_INVOKABLE void replaceFullStop(int row, int column);

//    Q_INVOKABLE QString cellText(int row, int column) const;
//    Q_INVOKABLE void setCellLabel(int row, int column, const QString& text, const QString& toolTipText  = "");

//    Q_INVOKABLE void setCurrentCell(int row, int column);

//    Q_INVOKABLE void editCurrentItem();

//    Q_INVOKABLE void setComboBox(const QString& currentText, const QStringList& valueList);
//    Q_INVOKABLE void removeComboBox(int row);

//    Q_INVOKABLE void setLineEdit(const QString& currentText);
//    Q_INVOKABLE void removeLineEdit(int row);

//    Q_INVOKABLE void setSpinBox();
//    Q_INVOKABLE void removeSpinBox(int row);

//    Q_INVOKABLE void setYesNoBox(bool checked);
//    Q_INVOKABLE void removeYesNoBox(int row);

//    Q_INVOKABLE void setCheckBox();
//    Q_INVOKABLE void setInactiveCheckBox(int row, int column, bool checked);
//    Q_INVOKABLE void removeCheckBox(int row);

//    Q_INVOKABLE bool getBooleanValueFromCell(int row, int column);

signals:

    void cellClicked(int row, int column);
    void currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

protected:

private:
    ScriptEngine* scriptEngine_;
    QTableWidget* table_;
    QLabel* image_;
    QLabel* imageCaption_;
    QVBoxLayout* layout_;

public slots:
};

#endif // PROPERTYEDITOR_H
