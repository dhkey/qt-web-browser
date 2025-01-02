#include "mainwindow.h"
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Web Browser");
    resize(1024, 768);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *navLayout = new QHBoxLayout();

    backButton = new QPushButton("←", this);
    connect(backButton, &QPushButton::clicked, this, &MainWindow::navigateBack);
    navLayout->addWidget(backButton);

    forwardButton = new QPushButton("→", this);
    connect(forwardButton, &QPushButton::clicked, this, &MainWindow::navigateForward);
    navLayout->addWidget(forwardButton);

    reloadButton = new QPushButton("↻", this);
    connect(reloadButton, &QPushButton::clicked, this, &MainWindow::reloadPage);
    navLayout->addWidget(reloadButton);

    urlInput = new QLineEdit(this);
    connect(urlInput, &QLineEdit::returnPressed, this, &MainWindow::navigateToUrl);
    navLayout->addWidget(urlInput);

    QPushButton *goButton = new QPushButton("Go", this);
    connect(goButton, &QPushButton::clicked, this, &MainWindow::navigateToUrl);
    navLayout->addWidget(goButton);

    mainLayout->addLayout(navLayout);

    webView = new QWebEngineView(this);
    connect(webView, &QWebEngineView::urlChanged, this, &MainWindow::updateUrl);
    mainLayout->addWidget(webView);

    webView->setUrl(QUrl("https://www.google.com"));
}

void MainWindow::navigateToUrl()
{
    QString url = urlInput->text();
    if (!url.startsWith("http://") && !url.startsWith("https://")) {
        url = "https://" + url;
    }
    webView->setUrl(QUrl(url));
}

void MainWindow::updateUrl(const QUrl &url)
{
    urlInput->setText(url.toString());
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
