#ifndef VERTICALSCROLLAREA_H
#define VERTICALSCROLLAREA_H

#include <QGridLayout>
#include <QResizeEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QDebug>

class VerticalScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit VerticalScrollArea(int, int, QWidget*);
    ~VerticalScrollArea();
    void addWidget(QWidget*, int, int);
    int rowCount() const;
private:
    QWidget *contentWidget;
    QVBoxLayout *parentGrid;
    QGridLayout *childGrid;
    QWidget * empty;

    int nRows;
    int nColumns;
    void adaptSize();
protected:
    void resizeEvent(QResizeEvent*);
};

#endif // VERTICALSCROLLAREA_H
