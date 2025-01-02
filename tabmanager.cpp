#include "tabmanager.h"

TabManager::TabManager(QTabWidget *tabs, QObject *parent)
    : QObject(parent), tabs(tabs)
{
    connect(tabs, &QTabWidget::tabCloseRequested, this, &TabManager::closeTab);
}

void TabManager::addNewTab(const QUrl &url)
{
    auto *webView = new QWebEngineView();
    webView->setUrl(url);
    int index = tabs->addTab(webView, "New Tab");
    tabs->setCurrentIndex(index);
    connect(webView, &QWebEngineView::urlChanged, this, [this, webView](const QUrl &url) {
        int index = tabs->indexOf(webView);
        if (index != -1) {
            tabs->setTabText(index, url.host());
        }
        emit urlChanged(url.toString());
    });

    connect(webView, &QWebEngineView::titleChanged, this, &TabManager::tabTitleChanged);
}

QWebEngineView* TabManager::currentWebView() const
{
    return qobject_cast<QWebEngineView *>(tabs->currentWidget());
}

void TabManager::closeTab(int index)
{
    QWidget *tab = tabs->widget(index);
    tabs->removeTab(index);
    delete tab;
    if (tabs->count() == 0) {
        addNewTab();
    }
}

void TabManager::clearTabs()
{
    QWidget *tab = tabs;
    tabs->clear();
}
