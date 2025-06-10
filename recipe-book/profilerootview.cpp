#include "profilerootview.h"
#include "ui_profilerootview.h"

ProfileRootView::ProfileRootView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProfileRootView)
{
    ui->setupUi(this);
}

ProfileRootView::~ProfileRootView()
{
    delete ui;
}
