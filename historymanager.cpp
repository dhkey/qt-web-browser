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
