#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "tabmanager.h"
#include <QMainWindow>
#include <QWebEngineView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void navigateToUrl();
    void updateUrl(const QUrl &url);
    void navigateBack();
    void navigateForward();
    void reloadPage();

private:
    Ui::MainWindow *ui;
    TabManager *tabManager;

};

#endif
