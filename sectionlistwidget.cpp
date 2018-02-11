#include "sectionlistwidget.h"

SectionListWidget::SectionListWidget(QWidget *parent) : QWidget(parent)
{
    list_ = new QListWidget(this);
    layout_ = new QVBoxLayout(this);
    layout_->addWidget(list_);
    setLayout(layout_);

    connect(list_, &QListWidget::itemClicked, this, &SectionListWidget::itemClicked);
}

SectionListWidget::~SectionListWidget()
{

}

void SectionListWidget::setupWidget(QJSValue &project)
{
    project_ = project;
    refreshList();
}

void SectionListWidget::on_propertyValueChanged(const QString& propertyName, const QString& value)
{
    if (propertyName == "sectionName") refreshList();
}

void SectionListWidget::refreshList()
{
    if (project_.property("sectionList").property("length").toInt() > 0)
    {
        QVariantList names = project_.property("sectionNamesList").callWithInstance(project_).toVariant().toList();
        list_->clear();
        for (auto & i : names)
        {
            list_->addItem(i.toString());
        }
        list_->item(project_.property("currentSectionIndex").toInt())->setBackground(QBrush(QColor(160, 160, 160)));
    }
}

void SectionListWidget::setCurrentRow(int row)
{
    if (row != -1) list_->setCurrentRow(row);
}

void SectionListWidget::itemClicked(QListWidgetItem* currentItem)
{
    emit currentSectionChanged(list_->row(currentItem));
}
