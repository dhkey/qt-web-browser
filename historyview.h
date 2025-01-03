#ifndef HISTORYVIEW_H
#define HISTORYVIEW_H

#include <QWidget>

namespace Ui {
class historyview;
}

class historyview : public QWidget
{
    Q_OBJECT

public:
    explicit historyview(QWidget *parent = nullptr);
    ~historyview();

    void renderItemsOnTableWidget(const QList<QPair<QString, QString>>& records);

private:
    Ui::historyview *ui;
};

#endif // HISTORYVIEW_H
