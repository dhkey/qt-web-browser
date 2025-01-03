#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QDebug>

class HistoryManager {
public:
    static HistoryManager& getInstance() {
        static HistoryManager instance;
        return instance;
    }

    HistoryManager(const HistoryManager&) = delete;
    HistoryManager& operator=(const HistoryManager&) = delete;

    bool addRecord(const QString& url);

private:
    HistoryManager(const QString& dbPath = "history.db");
    ~HistoryManager();

    bool init();

    QSqlDatabase db;
    QString dbPath;
};

#endif
