#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QMessageBox>

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
    /**
     * @brief offSet
     * 鼠标点击位置和窗口左上角位置的相对距离，在鼠标拖动窗口过程中相对距离保持不变。
     */
    QPoint offSet;

    QNetworkAccessManager *networkManager;

public  slots:
    void onNetReply(QNetworkReply *reply);

    // QWidget interface
protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void getWeatherInfo(QString cityCode);

};
#endif // MAINWINDOW_H
