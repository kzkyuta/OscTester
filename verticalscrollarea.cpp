#include "verticalscrollarea.h"

VerticalScrollArea::VerticalScrollArea(int rows, int cols, QWidget *parent = Q_NULLPTR)
    :QScrollArea(parent), nRows(rows), nColumns(cols)
{
    setWidgetResizable(true);
    contentWidget = new QWidget(this);
    setWidget(contentWidget);
    grid = new QGridLayout(contentWidget);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void VerticalScrollArea::addWidget(QWidget* w, int row, int col){
    grid->addWidget(w, row, col);
    adaptSize();
}

int VerticalScrollArea::columnCount() const{
    if(grid->count() == 0){
        return 0;
    }
    return grid->columnCount();
}

void VerticalScrollArea::adaptSize(){
    if(columnCount() >= nColumns ){
        int w = 1.0*(width() - grid->horizontalSpacing()*(nColumns+1.6))/nColumns;
        int wCorrected = w*columnCount() + grid->horizontalSpacing()*(columnCount()+2);
        contentWidget->setFixedWidth(wCorrected);
    }
    contentWidget->setFixedHeight(viewport()->height());
}

void VerticalScrollArea::resizeEvent(QResizeEvent *event){
    QScrollArea::resizeEvent(event);
    adaptSize();
}

