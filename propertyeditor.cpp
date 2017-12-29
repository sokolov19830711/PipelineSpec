#include "propertyeditor.h"

#include <QDebug>

PropertyEditor::PropertyEditor(const QString &name, ScriptEngine *scriptEngine, QWidget *parent) : QWidget(parent)
{
    setObjectName(name);
    scriptEngine_ = scriptEngine;

    table_ = new QTableWidget(this);
    table_->setObjectName(this->objectName() + "_table");
    table_->horizontalHeader()->setStretchLastSection(true);
    table_->verticalHeader()->setVisible(false);
    table_->setAlternatingRowColors(true);
    table_->showGrid();
    table_->setColumnCount(2);
    table_->setHorizontalHeaderLabels({"Свойство", "Значение"});
    QFont font;
    font.setBold(true);
    table_->horizontalHeaderItem(0)->setFont(font);
    table_->horizontalHeaderItem(1)->setFont(font);
    table_->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
    table_->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignLeft);
    table_->setColumnWidth(0, 180);
//    image_ = new QLabel(this);
//    image_->setObjectName("image");
//    imageCaption_ = new QLabel(this);
//    imageCaption_->setObjectName("imageCaption");

    layout_ = new QVBoxLayout(this);
    layout_->addWidget(table_);
//    layout_->addWidget(image_);
//    layout_->addWidget(imageCaption_);
    setLayout(layout_);

    connect(table_, &QTableWidget::cellClicked, this, &PropertyEditor::cellClicked);
    connect(table_, &QTableWidget::currentCellChanged, this, &PropertyEditor::currentCellChanged);
}

PropertyEditor::~PropertyEditor()
{

}

//int PropertyEditor::rowCount() const
//{
//    return table_->rowCount();
//}
//void PropertyEditor::setRowCount(int rowCount)
//{
//    table_->setRowCount(rowCount);
//}

//int PropertyEditor::currentRow() const
//{
//    return table_->currentRow();
//}

//QString PropertyEditor::cellText(int row, int column) const
//{
//    if (table_->item(row, column)) return table_->item(row, column)->text();
//    else return "<empty>";
//}

//void PropertyEditor::setCellText(int row, int column, const QString& text)
//{
//    QTableWidgetItem* item = table_->item(row, column);
//    if (!item)
//    {
//        item = new QTableWidgetItem;
//        table_->setItem(row, column, item);
//    }
//    item->setText(text);
//}

//void PropertyEditor::replaceFullStop(int row, int column)
//{
//    QString text = table_->item(row, column)->text();
//    text.replace(".", ",");
//    setCellText(row, column, text);
//}

//void PropertyEditor::setCellLabel(int row, int column, const QString& text, const QString& toolTipText)
//{
//    QLabel* label = new QLabel(this);
//    label->setText(text);
//    label->setToolTip(toolTipText);
//    table_->setCellWidget(row, column, label);
//}

//void PropertyEditor::setCurrentCell(int row, int column)
//{
//    table_->setCurrentCell(row, column);
//}

//void PropertyEditor::editCurrentItem()
//{
//    table_->editItem(table_->currentItem());
//}

//void PropertyEditor::setComboBox(const QString& currentText, const QStringList& valueList)
//{
//    QComboBox* comboBox = new QComboBox(this);
//    comboBox->setObjectName("comboBox");
//    comboBox->addItems(valueList);
//    comboBox->setCurrentText(currentText);
//    table_->setCellWidget(table_->currentRow(), 1, comboBox);
//    scriptEngine_->makeQObjectScriptable(comboBox, comboBox->objectName());
//    comboBox->showPopup();
//}

//void PropertyEditor::removeComboBox(int row)
//{
//    QTableWidgetItem* item = new QTableWidgetItem;
//    QComboBox* comboBox = dynamic_cast<QComboBox*> (table_->cellWidget(row, 1));
//    if (comboBox)
//    {
//        item->setText(comboBox->currentText());
//        table_->removeCellWidget(row, 1);
//        table_->setItem(row, 1, item);
//    }
//}

//void PropertyEditor::setLineEdit(const QString& currentText)
//{
//    QLineEdit* lineEdit = new QLineEdit(this);
//    lineEdit->setObjectName("lineEdit");
//    lineEdit->setText(currentText);
//    lineEdit->selectAll();
//    table_->setCellWidget(table_->currentRow(), 1, lineEdit);
//    scriptEngine_->makeQObjectScriptable(lineEdit, lineEdit->objectName());
//}

//void PropertyEditor::removeLineEdit(int row)
//{
//    QTableWidgetItem* item = new QTableWidgetItem;
//    QLineEdit* lineEdit = dynamic_cast<QLineEdit*> (table_->cellWidget(row, 1));
//    if (lineEdit)
//    {
//        item->setText(lineEdit->text());
//        table_->removeCellWidget(row, 1);
//        table_->setItem(row, 1, item);
//    }
//}

//void PropertyEditor::setSpinBox()
//{
//    QDoubleSpinBox* spinBox = new QDoubleSpinBox(this);
//    spinBox->setObjectName("spinBox");
//    table_->setCellWidget(table_->currentRow(), 1, spinBox);
//    scriptEngine_->makeQObjectScriptable(spinBox, spinBox->objectName());
//}

//void PropertyEditor::removeSpinBox(int row)
//{
//    QTableWidgetItem* item = new QTableWidgetItem;
//    QDoubleSpinBox* spinBox = dynamic_cast<QDoubleSpinBox*> (table_->cellWidget(row, 1));
//    if (spinBox)
//    {
//        item->setText(spinBox->text());
//        table_->removeCellWidget(row, 1);
//        table_->setItem(row, 1, item);
//    }
//}

//void PropertyEditor::setYesNoBox(bool checked)
//{
//    QComboBox* comboBox = new QComboBox(this);
//    comboBox->setObjectName("comboBox");
//    comboBox->addItems({"Да", "Нет"});
//    if (checked) comboBox->setCurrentText("Да");
//    else comboBox->setCurrentText("Нет");
//    table_->setCellWidget(table_->currentRow(), 1, comboBox);
//    scriptEngine_->makeQObjectScriptable(comboBox, comboBox->objectName());
//    comboBox->showPopup();
//}

//void PropertyEditor::removeYesNoBox(int row)
//{
//    QTableWidgetItem* item = new QTableWidgetItem;
//    QComboBox* comboBox = dynamic_cast<QComboBox*> (table_->cellWidget(row, 1));
//    if (comboBox)
//    {
//        item->setText(comboBox->currentText());
//        table_->removeCellWidget(row, 1);
//        table_->setItem(row, 1, item);
//    }
//}

//void PropertyEditor::setCheckBox()
//{
//    QCheckBox* checkBox = new QCheckBox(this);
//    checkBox->setObjectName("checkBox");
//    table_->setCellWidget(table_->currentRow(), 1, checkBox);
//    scriptEngine_->makeQObjectScriptable(checkBox, checkBox->objectName());
//}

//void PropertyEditor::setInactiveCheckBox(int row, int column, bool checked)
//{
//    QCheckBox* checkBox = new QCheckBox(this);
//    checkBox->setObjectName("");
//    checkBox->setChecked(checked);
//    table_->setCellWidget(row, column, checkBox);
//    scriptEngine_->makeQObjectScriptable(checkBox, checkBox->objectName());
//}

//void PropertyEditor::removeCheckBox(int row)
//{
//    QCheckBox* checkBox = dynamic_cast<QCheckBox*> (table_->cellWidget(row, 1));
//    if (checkBox)
//    {
//        checkBox->setObjectName("");
//    }
//}

//bool PropertyEditor::getBooleanValueFromCell(int row, int column)
//{
//    QCheckBox* checkBox = dynamic_cast<QCheckBox*> (table_->cellWidget(row, column));
//    if (checkBox)
//    {
//        return checkBox->isChecked();
//    }

//    return false;
//}
