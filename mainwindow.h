#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    struct item {
        QString time{""};
        QString desc{""};
        int minute{0};
        int seconds{0};
    };

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_closeButton_clicked();

    void on_addButton_clicked();

    void on_xmlButton_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QVector<item> items;
    int minute{0};
    int seconds{0};
};

#endif // MAINWINDOW_H
