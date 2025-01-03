#ifndef HISTORYVIEW_H
#define HISTORYVIEW_H

#include <QWidget>
#include <QTreeWidgetItem>

namespace Ui {
class historyview;
}

class historyview : public QWidget
{
    Q_OBJECT

public:
    explicit historyview(QWidget *parent = nullptr);
    ~historyview();

    void onTreeItemSelected(QTreeWidgetItem* item, int column);

private:
    Ui::historyview *ui;
    void renderItemsOnTableWidget(const QList<QPair<QString, QString>>& records);
    void populateTreeWidget();
};

#endif // HISTORYVIEW_H
