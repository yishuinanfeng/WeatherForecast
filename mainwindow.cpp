#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QContextMenuEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(width(),height());

    exitMenu = new QMenu(this);
    exitAction = new QAction();

    exitAction->setText("退出");

    exitMenu->addAction(exitAction);

    connect(exitAction,&QAction::triggered,this,[=]{
        qApp->exit(0);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    //菜单栏弹在当前鼠标所在的位置
    exitMenu->exec(QCursor::pos());
    event->accept();
}

