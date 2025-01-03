#include "historyview.h"
#include "ui_historyview.h"

historyview::historyview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::historyview)
{
    ui->setupUi(this);
}

historyview::~historyview()
{
    delete ui;
}
