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

signals:

public slots:

private:
    QListWidget* list_;
    QVBoxLayout* layout_;
    QJSValue item_;
};

#endif // SECTIONLISTWIDGET_H
