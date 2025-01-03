#include "tabmanager.h"
#include "historymanager.h"

TabManager::TabManager(QTabWidget *tabs, QObject *parent)
    : QObject(parent), tabs(tabs)
{
    connect(tabs, &QTabWidget::tabCloseRequested, this, &TabManager::closeTab);
    QShortcut *closeTabShortcut = new QShortcut(QKeySequence("Ctrl+W"), tabs);
    connect(closeTabShortcut, &QShortcut::activated, this, &TabManager::closeCurrentTab);
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
        HistoryManager::getInstance().addRecord(url.toString());
    });
    connect(webView, &QWebEngineView::titleChanged, this, &TabManager::tabTitleChanged);
    connect(webView, &QWebEngineView::loadProgress, this, [this, webView](int progress) {
        if (webView == currentWebView()) { emit loadProgress(progress); }
    });
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

void TabManager::closeCurrentTab(){
    int currentIndex = tabs->currentIndex();
    closeTab(currentIndex);
}


void TabManager::clearTabs()
{
    tabs->clear();
}

void TabManager::handleLoadProgress(int progress){
    emit loadProgress(progress);
}
