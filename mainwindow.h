#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "uiupdater.h"

#include <QMainWindow>
#include <QMenu>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
//汕头编码
#define DEFAULT_CITY_CODE "101280501"
#define DEFAULT_CURVE_PADDING 12

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

    UiUpdater *uiUpdater = nullptr;

public  slots:
    void onNetReply(QNetworkReply *reply);
    void onSearchCityClick(bool checked = false);
    void onSearchCityEnterClick();

    void drawHighCurve();
    void drawLowCurve();


    // QWidget interface
protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void getWeatherInfo(QString cityCode);


    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event);
};
#endif // MAINWINDOW_H
