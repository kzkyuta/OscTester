#ifndef VERTICALSCROLLAREA_H
#define VERTICALSCROLLAREA_H

#include <QGridLayout>
#include <QResizeEvent>
#include <QScrollArea>
#include <QScrollBar>

class VerticalScrollArea : public QScrollArea
{
    QWidget *contentWidget;
    QGridLayout *grid;
    int nRows;
    int nColumns;
public:
    VerticalScrollArea(int, int, QWidget*);
    void addWidget(QWidget*, int, int);
    int columnCount() const;
private:
    void adaptSize();
protected:
    void resizeEvent(QResizeEvent*);
};

#endif // VERTICALSCROLLAREA_H
