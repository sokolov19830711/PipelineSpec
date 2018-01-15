#include "sectionlistwidget.h"
#include <QDebug>

SectionListWidget::SectionListWidget(QWidget *parent) : QWidget(parent)
{
    list_ = new QListWidget(this);
    layout_ = new QVBoxLayout(this);
    layout_->addWidget(list_);
    setLayout(layout_);
}

SectionListWidget::~SectionListWidget()
{

}

void SectionListWidget::setupWidget(QJSValue &item)
{
    item_ = item;
    refreshList();
}

void SectionListWidget::on_propertyValueChanged(const QString& propertyName, const QString& value)
{
    if (propertyName == "sectionName") refreshList();
}

void SectionListWidget::refreshList()
{
    QVariantList names = item_.property("sectionNamesList").callWithInstance(item_).toVariant().toList();
    list_->clear();
    for (auto & i : names)
    {
        list_->addItem(i.toString());
    }
}
