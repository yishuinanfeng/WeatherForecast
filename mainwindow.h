#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    Ui::MainWindow *ui;
    QMenu *exitMenu;
    QAction *exitAction;

    // QWidget interface
protected:
    void contextMenuEvent(QContextMenuEvent *event);
};
#endif // MAINWINDOW_H
