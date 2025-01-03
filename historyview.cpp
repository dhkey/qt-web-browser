#include "historyview.h"
#include "ui_historyview.h"
#include "historymanager.h"
#include <QDate>
#include <QTreeWidgetItem>

historyview::historyview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::historyview)
{
    ui->setupUi(this);

    QList<QPair<QString, QString>> todaysRecords =
        HistoryManager::getInstance().getRecordsByDateRange(
            QDateTime(QDate::currentDate(), QTime(0, 0, 0)),
            QDateTime(QDate::currentDate(), QTime(23, 59, 59))
            );

    renderItemsOnTableWidget(todaysRecords);

}

void historyview::renderItemsOnTableWidget(const QList<QPair<QString, QString>>& records)
{
    ui->table->setRowCount(records.size());
    for (int i = 0; i < records.size(); ++i) {
        QTableWidgetItem* urlItem = new QTableWidgetItem(records[i].first);
        ui->table->setItem(i, 0, urlItem);
        QTableWidgetItem* dateItem = new QTableWidgetItem(records[i].second);
        ui->table->setItem(i, 1, dateItem);
    }
    ui->table->resizeColumnsToContents();
}


historyview::~historyview()
{
    delete ui;
}

