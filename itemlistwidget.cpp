#include "itemlistwidget.h"

ItemListWidget::ItemListWidget(QWidget *parent) : QWidget(parent)
{
    table_ = new QTableWidget(this);
    table_->horizontalHeader()->setStretchLastSection(true);
    table_->verticalHeader()->setVisible(false);
    table_->showGrid();
    table_->setColumnCount(7);
    table_->setHorizontalHeaderLabels({"№", "НАИМЕНОВАНИЕ", "МАТЕРИАЛ", "ЕД. ИЗМ.", "КОЛ.", "ОТБР., ММ", "ПРИМЕЧ"});
    QFont font;
    font.setBold(true);
    table_->horizontalHeaderItem(0)->setFont(font);
    table_->horizontalHeaderItem(1)->setFont(font);
    table_->horizontalHeaderItem(2)->setFont(font);
    table_->horizontalHeaderItem(3)->setFont(font);
    table_->horizontalHeaderItem(4)->setFont(font);
    table_->horizontalHeaderItem(5)->setFont(font);
    table_->horizontalHeaderItem(6)->setFont(font);
    table_->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignCenter);
    table_->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignCenter);
    table_->horizontalHeaderItem(2)->setTextAlignment(Qt::AlignCenter);
    table_->horizontalHeaderItem(3)->setTextAlignment(Qt::AlignCenter);
    table_->horizontalHeaderItem(4)->setTextAlignment(Qt::AlignCenter);
    table_->horizontalHeaderItem(5)->setTextAlignment(Qt::AlignCenter);
    table_->horizontalHeaderItem(6)->setTextAlignment(Qt::AlignCenter);
    table_->setColumnWidth(0, 30);
    table_->setColumnWidth(1, 600);

    layout_ = new QVBoxLayout(this);
    layout_->addWidget(table_);
    setLayout(layout_);

    connect(table_, &QTableWidget::currentCellChanged, this, &ItemListWidget::currentCellChanged);
}

 ItemListWidget::~ItemListWidget()
{

}

void ItemListWidget::currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{

}

void ItemListWidget::setupWidget(QJSValue& section)
{
    section_ = section;
}
