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

    historyview::populateTreeWidget();

    connect(ui->tree, &QTreeWidget::itemClicked, this, &historyview::onTreeItemSelected);
}

void historyview::populateTreeWidget() {
    ui->tree->clear();
    QTreeWidgetItem* todayItem = new QTreeWidgetItem(ui->tree);
    todayItem->setText(0, "Today");
    QTreeWidgetItem* yesterdayItem = new QTreeWidgetItem(ui->tree);
    yesterdayItem->setText(0, "Yesterday");
    QList<QString> months = HistoryManager::getInstance().getUniqueMonths();
    for (const QString& month : months) {
        QDate date = QDate::fromString(month, "yyyy-MM");
        if (date.isValid()) {
            QString monthName = date.toString("MMMM yyyy");
            QTreeWidgetItem* monthItem = new QTreeWidgetItem(ui->tree);
            monthItem->setText(0, monthName);
        }
    }
    ui->tree->expandAll();
}


void historyview::onTreeItemSelected(QTreeWidgetItem* item, int column) {
    QString selectedText = item->text(0);
    QList<QPair<QString, QString>> records;

    if (selectedText == "Today") {
        records = HistoryManager::getInstance().getRecordsByDateRange(
            QDateTime(QDate::currentDate(), QTime(0, 0, 0)),
            QDateTime(QDate::currentDate(), QTime(23, 59, 59))
            );
    } else if (selectedText == "Yesterday") {
        QDate yesterday = QDate::currentDate().addDays(-1);
        records = HistoryManager::getInstance().getRecordsByDateRange(
            QDateTime(yesterday, QTime(0, 0, 0)),
            QDateTime(yesterday, QTime(23, 59, 59))
            );
    } else {
        QDate date = QDate::fromString(selectedText, "MMMM yyyy");
        if (date.isValid()) {
            QDateTime startOfMonth(date, QTime(0, 0, 0));
            QDateTime endOfMonth(date.addDays(date.daysInMonth() - 1), QTime(23, 59, 59));

            records = HistoryManager::getInstance().getRecordsByDateRange(startOfMonth, endOfMonth);
        }
    }

    renderItemsOnTableWidget(records);
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

