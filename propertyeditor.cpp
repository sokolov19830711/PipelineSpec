#include "propertyeditor.h"

#include <QDebug>

PropertyEditor::PropertyEditor(const QString &name, QWidget *parent) : QWidget(parent)
{
    setObjectName(name);

    table_ = new QTableWidget(this);
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

//    connect(table_, &QTableWidget::cellClicked, this, &PropertyEditor::cellClicked);
    connect(table_, &QTableWidget::currentCellChanged, this, &PropertyEditor::currentCellChanged);
}

PropertyEditor::~PropertyEditor()
{

}

void PropertyEditor::setupEditor(QJSValue& item)
{
    item_ = item;
    table_->setRowCount(0);
    for (auto & i : (item_.property("ui").call().property("table")).toVariant().toList())
    {
        table_->setRowCount(table_->rowCount() + 1);

        QTableWidgetItem* item = new QTableWidgetItem();
        item->setData(Qt::UserRole, i);
        table_->setItem(table_->rowCount() - 1, 0, item);

        QLabel* label = new QLabel((i.toMap()["caption"]).toString());
        label->setToolTip((i.toMap()["toolTip"]).toString());
        table_->setCellWidget(table_->rowCount() - 1, 0, label);
    }
}

void PropertyEditor::refreshValues()
{
    for (int i = 0; i < table_->rowCount(); i++)
    {
        QTableWidgetItem* newTableItem = new QTableWidgetItem;
        if (propertyDesc(i, "widgetType").toString() == "yesNoBox")
        {
            if (item_.property("properties").property(propertyDesc(i, "propertyName").toString()).toBool()) newTableItem->setText("Да");
            else newTableItem->setText("Нет");
        }
        else newTableItem->setText(item_.property("properties").property(propertyDesc(i, "propertyName").toString()).toString());
        table_->setItem(i, 1, newTableItem);
    }
}

void PropertyEditor::clearTable()
{
    for (int i = 0; i < table_->rowCount(); i++)
    {
        QTableWidgetItem* newTableItem = new QTableWidgetItem;
        table_->setItem(i, 1, newTableItem);
    }
}

void PropertyEditor::currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if (previousColumn != 0 and previousColumn != -1 and previousRow != -1)
    {
        if (widgetType(previousRow) == "lineEdit") removeLineEdit(previousRow);
        else if (widgetType(previousRow) == "spinBox") removeSpinBox(previousRow);
        else if (widgetType(previousRow) == "comboBox") removeComboBox(previousRow);
        else if (widgetType(previousRow) == "yesNoBox") removeYesNoBox(previousRow);
        emit propertyValueChanged(propertyDesc(previousRow,"propertyName").toString(), table_->item(previousRow, previousColumn)->text());
    }

    if (currentColumn != 0 and currentRow != -1)
    {
        if (widgetType(currentRow) == "lineEdit") setLineEdit();
        else if (widgetType(currentRow) == "spinBox") setSpinBox();
        else if (widgetType(currentRow) == "comboBox") setComboBox();
        else if (widgetType(currentRow) == "yesNoBox") setYesNoBox();
    }
}

QVariant PropertyEditor::propertyDesc(int row, const QString& descriptorName) const
{
    return table_->item(row,0)->data(Qt::UserRole).toMap()[descriptorName];
}

QString PropertyEditor::widgetType(int row) const
{
    return propertyDesc(row, "widgetType").toString();
}

QString PropertyEditor::propertyName(int row) const
{
    return propertyDesc(row, "propertyName").toString();
}

QStringList PropertyEditor::valueList(int row) const
{
    QVariantList vList = item_.property("ui").call().property("table").property(row).property("valueList").call({item_}).toVariant().toList();
    QStringList sList;
    for (auto & i : vList)
    {
        sList << i.toString();
    }
    return sList;
}

void PropertyEditor::writePropertyValue(int row, const QString &value) const
{
    item_.property("properties").setProperty(propertyName(row), QJSValue(value));
}

void PropertyEditor::writePropertyValue(int row, bool value) const
{
    item_.property("properties").setProperty(propertyName(row), QJSValue(value));
}

//------------------------------------------------------------------------------------------------------------

void PropertyEditor::setLineEdit()
{
    QLineEdit* lineEdit = new QLineEdit(this);
    lineEdit->setText(table_->item(table_->currentRow(), table_->currentColumn())->text());
    lineEdit->selectAll();
    table_->setCellWidget(table_->currentRow(), 1, lineEdit);
}

void PropertyEditor::removeLineEdit(int row)
{
    QTableWidgetItem* item = new QTableWidgetItem;
    QLineEdit* lineEdit = dynamic_cast<QLineEdit*> (table_->cellWidget(row, 1));
    if (lineEdit)
    {
        QString currentText = lineEdit->text();
        item->setText(currentText);
        writePropertyValue(row, currentText);
        table_->removeCellWidget(row, 1);
        table_->setItem(row, 1, item);

    }
}

void PropertyEditor::setSpinBox()
{
    QDoubleSpinBox* spinBox = new QDoubleSpinBox(this);
    spinBox->setDecimals(propertyDesc(table_->currentRow(), "decimals").toInt());
    spinBox->setMinimum(propertyDesc(table_->currentRow(), "minimum").toDouble());
    spinBox->setMaximum(propertyDesc(table_->currentRow(), "maximum").toDouble());
    spinBox->setValue(table_->item(table_->currentRow(), 1)->text().toDouble());
    spinBox->selectAll();
    table_->setCellWidget(table_->currentRow(), 1, spinBox);
}

void PropertyEditor::removeSpinBox(int row)
{
    QTableWidgetItem* item = new QTableWidgetItem;
    QDoubleSpinBox* spinBox = dynamic_cast<QDoubleSpinBox*> (table_->cellWidget(row, 1));
    if (spinBox)
    {
        QString currentText = spinBox->text().replace(",", ".");
        item->setText(currentText);
        writePropertyValue(row, currentText);
        table_->removeCellWidget(row, 1);

        table_->setItem(row, 1, item);
    }
}

void PropertyEditor::setComboBox()
{
    QComboBox* comboBox = new QComboBox(this);
    comboBox->addItems(valueList(table_->currentRow()));
    comboBox->setCurrentText(table_->item(table_->currentRow(), 1)->text());
    table_->setCellWidget(table_->currentRow(), 1, comboBox);
    comboBox->showPopup();
}

void PropertyEditor::removeComboBox(int row)
{
    QTableWidgetItem* item = new QTableWidgetItem;
    QComboBox* comboBox = dynamic_cast<QComboBox*> (table_->cellWidget(row, 1));
    if (comboBox)
    {
        QString currentText = comboBox->currentText();
        item->setText(currentText);
        writePropertyValue(row, currentText);
        table_->removeCellWidget(row, 1);
        table_->setItem(row, 1, item);
    }
}

void PropertyEditor::setYesNoBox()
{
    QComboBox* comboBox = new QComboBox(this);
    comboBox->addItems({"Да", "Нет"});
    comboBox->setCurrentText(table_->item(table_->currentRow(), 1)->text());
    table_->setCellWidget(table_->currentRow(), 1, comboBox);
    comboBox->showPopup();
}

void PropertyEditor::removeYesNoBox(int row)
{
    QTableWidgetItem* item = new QTableWidgetItem;
    QComboBox* comboBox = dynamic_cast<QComboBox*> (table_->cellWidget(row, 1));
    if (comboBox)
    {
        QString currentText = comboBox->currentText();
        item->setText(currentText);
        if (currentText == "Да") writePropertyValue(row, true);
        else writePropertyValue(row, false);
        table_->removeCellWidget(row, 1);
        table_->setItem(row, 1, item);
    }
}
