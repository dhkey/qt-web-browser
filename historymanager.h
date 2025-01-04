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
    void setIncognitoMode(bool enabled);
    bool isIncognitoMode() const { return incognitoMode; }

    QList<QPair<QString, QString>> getAllRecords();
    QList<QPair<QString, QString>> getRecordsByDateRange(const QDateTime& startDate, const QDateTime& endDate);
    QList<QString> getUniqueMonths();

private:
    HistoryManager(const QString& dbPath = "history.db");
    ~HistoryManager();

    bool incognitoMode;

    bool init();

    QSqlDatabase db;
    QString dbPath;
};

#endif
