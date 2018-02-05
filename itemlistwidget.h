#ifndef ITEMLISTWIDGET_H
#define ITEMLISTWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QJSValue>

class ItemListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ItemListWidget(QWidget *parent = nullptr);
    ~ItemListWidget();

    void setupWidget(QJSValue& section);

signals:

public slots:
    void currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    QTableWidget* table_;
    QVBoxLayout* layout_;
    QJSValue section_;
};

#endif // ITEMLISTWIDGET_H
