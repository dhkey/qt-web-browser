#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void navigateToUrl();
    void updateUrl(const QUrl &url);
    void navigateBack();
    void navigateForward();
    void reloadPage();

private:
    QWebEngineView *webView;
    QLineEdit *urlInput;
    QPushButton *backButton;
    QPushButton *forwardButton;
    QPushButton *reloadButton;
};

#endif // MAINWINDOW_H
