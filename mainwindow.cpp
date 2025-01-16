#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QUrl>
#include <QVBoxLayout>
#include <QFileInfo>
#include "historymanager.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>

void MainWindow::loadStyleSheet(const QString &sheetName) {
    QFile file(sheetName);
    if (file.open(QFile::ReadOnly)) {
        QString style = file.readAll();
        qApp->setStyleSheet(style);
        file.close();
    }
}

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

    connect(ui->actionTurn_on_INCOGNITO_mode, &QAction::triggered, this, [this]() {
        bool incognitoModeStatus = HistoryManager::getInstance().isIncognitoMode();
        if (!incognitoModeStatus){
            HistoryManager::getInstance().setIncognitoMode(true);
            this->ui->actionTurn_on_INCOGNITO_mode->setText("Turn off INCOGNITO mode");
            loadStyleSheet(":/styles/incognito.qss");
        }else{
            HistoryManager::getInstance().setIncognitoMode(false);
            this->ui->actionTurn_on_INCOGNITO_mode->setText("Turn on INCOGNITO mode");
            loadStyleSheet(":/styles/normal.qss");
        }
    });

    connect(ui->actionShow_History, &QAction::triggered, this, [this]() {
        tabManager->addHistoryTab();
    });

    connect(ui->urlLineEdit, &QLineEdit::returnPressed, this, &MainWindow::navigateToUrl);
    connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::navigateBack);
    connect(ui->forwardButton, &QPushButton::clicked, this, &MainWindow::navigateForward);
    connect(ui->reloadButton, &QPushButton::clicked, this, &MainWindow::reloadPage);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::navigateToUrl);

    connect(tabManager, &TabManager::loadProgress, this, &MainWindow::updateProgress);

    connect(ui->historyButton, &QPushButton::clicked, this, [this]() {
        tabManager->addHistoryTab();
    });

    connect(tabManager->currentWebView()->page()->profile(), &QWebEngineProfile::downloadRequested, this, &MainWindow::handleDownloadRequested);
    ui->download->setVisible(false);
    ui->downloadLabel->setVisible(false);
}

void MainWindow::handleDownloadRequested(QWebEngineDownloadRequest *download) {
    QString filePath = QFileDialog::getSaveFileName(this, "Save this file?", download->downloadFileName());
    if (filePath.isEmpty()) {
        download->cancel();
        return;
    }
    download->setDownloadDirectory(QFileInfo(filePath).absolutePath());
    download->setDownloadFileName(QFileInfo(filePath).fileName());
    download->accept();
    currentDownload = download;

    ui->download->setVisible(true);
    ui->downloadLabel->setText("Downloading... (" + QFileInfo(filePath).fileName() + ")");
    ui->downloadLabel->setVisible(true);

    connect(download, &QWebEngineDownloadRequest::receivedBytesChanged,
            this, &MainWindow::updateDownloadProgress);
    connect(download, &QWebEngineDownloadRequest::isFinishedChanged,
            this, &MainWindow::downloadFinished);

    QMessageBox::information(this, "Downloading", "Downloading have beed started!");
}

void MainWindow::downloadFinished(){
    ui->download->setVisible(false);
    ui->downloadLabel->setVisible(false);
    currentDownload = nullptr;
}

void MainWindow::updateDownloadProgress() {
    if (!currentDownload)
        return;

    qint64 bytesReceived = currentDownload->receivedBytes();
    qint64 bytesTotal = currentDownload->totalBytes();

    if (bytesTotal > 0) {
        int percentage = (bytesReceived * 100) / bytesTotal;
        ui->download->setValue(percentage);

        double receivedMB = bytesReceived / 1048576.0;
        double totalMB = bytesTotal / 1048576.0;
        ui->downloadLabel->setText(QString("Downloading: %1 MB of %2 MB")
                                         .arg(QString::number(receivedMB, 'f', 1))
                                         .arg(QString::number(totalMB, 'f', 1)));
    }
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
