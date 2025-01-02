#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QUrl>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    webView = new QWebEngineView(this);

    QVBoxLayout *layout = new QVBoxLayout(ui->webWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(webView);

    connect(ui->urlLineEdit, &QLineEdit::returnPressed, this, &MainWindow::navigateToUrl);
    connect(webView, &QWebEngineView::urlChanged, this, &MainWindow::updateUrl);
    connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::navigateBack);
    connect(ui->forwardButton, &QPushButton::clicked, this, &MainWindow::navigateForward);
    connect(ui->reloadButton, &QPushButton::clicked, this, &MainWindow::reloadPage);

    webView->setUrl(QUrl("https://www.google.com"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::navigateToUrl()
{
    QString url = ui->urlLineEdit->text();
    if (!url.startsWith("http://") && !url.startsWith("https://")) {
        url = "https://" + url;
    }
    webView->setUrl(QUrl(url));
}

void MainWindow::updateUrl(const QUrl &url)
{
    ui->urlLineEdit->setText(url.toString());
}

void MainWindow::navigateBack()
{
    webView->back();
}

void MainWindow::navigateForward()
{
    webView->forward();
}

void MainWindow::reloadPage()
{
    webView->reload();
}
