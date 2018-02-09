#ifndef SECTIONLISTWIDGET_H
#define SECTIONLISTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QJSValue>

class SectionListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SectionListWidget(QWidget *parent = nullptr);
    ~SectionListWidget();

    void setupWidget(QJSValue& item);
    void refreshList();
    void setCurrentRow(int row);

signals:
    currentSectionChanged(int sectionIndex);

public slots:
    void on_propertyValueChanged(const QString& propertyName, const QString& value);
    void itemClicked(QListWidgetItem* currentItem);

private:
    QListWidget* list_;
    QVBoxLayout* layout_;
    QJSValue item_;
};

#endif // SECTIONLISTWIDGET_H
