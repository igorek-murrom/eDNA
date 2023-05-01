#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <vector>
#include <QFileInfo>
#include <QSettings>
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void parse();
    void displayFish(QVector<QString> list);
signals:
    void parseReady(QVector<QString>);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<QString> fishNames = {
        "Rock_Beauty", "French_Angelfish", "Four_Eye_Butterfly_Fish", "Blue_Tang", "Yellowtail_Snapper",
        "Sargent_Major", "Goliath_Grouper", "Blue_Headed_Wrasse", "Queen_Parrotfish", "Dusky_Damselfish"
    };
    QString fishNums[11] = {"1", "61", "121", "181", "241", "301", "361", "421", "481", "541", "601"};
    QVector<QString> current;

private:
    Ui::MainWindow *ui;
    QSettings *m_settings;
    QTimer *timer;

};
#endif // MAINWINDOW_H
