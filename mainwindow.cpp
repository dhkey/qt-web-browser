#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QUrl>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Qt Web Browser");
    this->resize(1500, 900);
    tabManager = new TabManager(ui->tabs, this);
    connect(tabManager, &TabManager::urlChanged, this, &MainWindow::updateUrl);
    connect(ui->newTabButton, &QPushButton::clicked, this, [this]() {
        tabManager->addNewTab();
    });
    tabManager->clearTabs();
    tabManager->addNewTab();
    connect(ui->urlLineEdit, &QLineEdit::returnPressed, this, &MainWindow::navigateToUrl);
    connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::navigateBack);
    connect(ui->forwardButton, &QPushButton::clicked, this, &MainWindow::navigateForward);
    connect(ui->reloadButton, &QPushButton::clicked, this, &MainWindow::reloadPage);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::navigateToUrl);
    connect(tabManager, &TabManager::loadProgress, this, &MainWindow::updateProgress);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::navigateToUrl()
{
    if (auto *webView = tabManager->currentWebView()) {
        QString url = ui->urlLineEdit->text();
        if (!url.startsWith("http://") && !url.startsWith("https://")) {
            url = "https://www.google.com/search?q=" + url;
        }
        webView->setUrl(QUrl(url));
    }
}

void MainWindow::updateUrl(const QUrl &url)
{
    ui->urlLineEdit->setText(url.toString());
}

void MainWindow::navigateBack()
{
    if (auto *webView = tabManager->currentWebView()) {
        webView->back();
    }
}

void MainWindow::navigateForward()
{
    if (auto *webView = tabManager->currentWebView()) {
        webView->forward();
    }
}

void MainWindow::reloadPage()
{
    if (auto *webView = tabManager->currentWebView()) {
        webView->reload();
    }
}

void MainWindow::updateProgress(int progress)
{
    if (progress < 100) {
        ui->progressBar->show();
        ui->progressBar->setValue(progress);
    } else {
        ui->progressBar->hide();
    }
}
