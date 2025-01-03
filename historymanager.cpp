#include "historymanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QFileInfo>
#include <QDir>

HistoryManager::HistoryManager(const QString& path) : dbPath(path) {
    init();
}

HistoryManager::~HistoryManager() {
    if (db.isOpen()) {
        db.close();
    }
}

bool HistoryManager::init() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        return false;
    }

    QSqlQuery query;
    bool success = query.exec("CREATE TABLE IF NOT EXISTS history ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "url TEXT NOT NULL,"
                              "visit_date DATETIME DEFAULT CURRENT_TIMESTAMP"
                              ")");
    return success;
}

bool HistoryManager::addRecord(const QString& url) {
    if (!db.isOpen()) {
        return false;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO history (url) VALUES (:url)");
    query.bindValue(":url", url);
    return query.exec();
}

QList<QPair<QString, QString>> HistoryManager::getAllRecords() {
    QList<QPair<QString, QString>> records;
    if (!db.isOpen()) {
        return records;
    }

    QSqlQuery query("SELECT url, visit_date FROM history ORDER BY visit_date DESC");
    while (query.next()) {
        QString url = query.value(0).toString();
        QString date = query.value(1).toString();
        records.append(qMakePair(url, date));
    }
    return records;
}

QList<QPair<QString, QString>> HistoryManager::getRecordsByDateRange(const QDateTime& startDate, const QDateTime& endDate) {
    QList<QPair<QString, QString>> records;

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return records;
    }

    QSqlQuery query;
    query.prepare("SELECT url, visit_date FROM history WHERE strftime('%Y-%m-%d %H:%M:%S', visit_date) BETWEEN :start AND :end ORDER BY visit_date DESC");

    QString startDateStr = startDate.toString("yyyy-MM-dd HH:mm:ss");
    QString endDateStr = endDate.toString("yyyy-MM-dd HH:mm:ss");
    query.bindValue(":start", startDateStr);
    query.bindValue(":end", endDateStr);


    if (!query.exec()) {
        return records;
    }

    while (query.next()) {
        QString url = query.value(0).toString();
        QString date = query.value(1).toString();
        records.append(qMakePair(url, date));
    }

    return records;
}

QList<QString> HistoryManager::getUniqueMonths() {
    QList<QString> months;
    if (!db.isOpen()) {
        return months;
    }

    QSqlQuery query;
    query.prepare("SELECT DISTINCT strftime('%Y-%m', visit_date) AS month FROM history ORDER BY month DESC");

    if (!query.exec()) {
        return months;
    }

    while (query.next()) {
        QString month = query.value(0).toString();
        months.append(month);
    }
    return months;
}
