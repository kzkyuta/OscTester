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

int VerticalScrollArea::rowCount() const{
    if(childGrid->count() == 0){
        return 0;
    }
    return childGrid->rowCount();
}

void VerticalScrollArea::adaptSize(){
    if(rowCount() >= nRows ){
//        int v = 1.0*(height() - childGrid->verticalSpacing()*(nRows+1.6))/nRows;
//        int vCorrected = 100*rowCount() + childGrid->verticalSpacing()*(rowCount()+2);
        int vCorrected = 90*rowCount();
        contentWidget->setFixedHeight(vCorrected);
    }
    contentWidget->setFixedWidth(viewport()->width());
}

void VerticalScrollArea::resizeEvent(QResizeEvent *event){
    QScrollArea::resizeEvent(event);
    adaptSize();
}

