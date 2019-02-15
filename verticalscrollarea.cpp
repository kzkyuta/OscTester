#include "verticalscrollarea.h"

VerticalScrollArea::VerticalScrollArea(int rows, int cols, QWidget *parent = Q_NULLPTR)
    :QScrollArea(parent), nRows(rows), nColumns(cols)
{
    setWidgetResizable(true);
    contentWidget = new QWidget(this);
    setWidget(contentWidget);
    parentGrid = new QVBoxLayout(contentWidget);
    childGrid = new QGridLayout();
    empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
    parentGrid->addLayout(childGrid);
    parentGrid->addWidget(empty);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void VerticalScrollArea::addWidget(QWidget* w, int row, int col){
    childGrid->addWidget(w, row, col);
    adaptSize();
}

int VerticalScrollArea::columnCount() const{
    if(childGrid->count() == 0){
        return 0;
    }
    return childGrid->columnCount();
}

void VerticalScrollArea::adaptSize(){
    if(columnCount() >= nColumns ){
        int w = 1.0*(width() - childGrid->horizontalSpacing()*(nColumns+1.6))/nColumns;
        int wCorrected = w*columnCount() + childGrid->horizontalSpacing()*(columnCount()+2);
        contentWidget->setFixedWidth(wCorrected);
    }
    contentWidget->setFixedHeight(viewport()->height());
}

void VerticalScrollArea::resizeEvent(QResizeEvent *event){
    QScrollArea::resizeEvent(event);
    adaptSize();
}

