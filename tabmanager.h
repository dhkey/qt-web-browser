#ifndef TABMANAGER_H
#define TABMANAGER_H

#include <QObject>
#include <QTabWidget>
#include <QWebEngineView>

class TabManager : public QObject {
    Q_OBJECT

public:
    explicit TabManager(QTabWidget *tabs, QObject *parent = nullptr);

    void addNewTab(const QUrl &url = QUrl("https://www.google.com"));
    QWebEngineView* currentWebView() const;

signals:
    void urlChanged(const QString &url);
    void tabTitleChanged(const QString &title);

public slots:
    void closeTab(int index);
    void clearTabs();

private:
    QTabWidget *tabs;
};

#endif // TABMANAGER_H
