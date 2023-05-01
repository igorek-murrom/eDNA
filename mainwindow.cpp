#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_settings(new QSettings(QSettings::IniFormat, QSettings::UserScope,
                               "CfRD", "eDNA", this))
{
    ui->setupUi(this);
    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(parse()));
    connect(this, SIGNAL(parseReady(QVector<QString>)), this, SLOT(displayFish(QVector<QString>)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::parse() {
    QString str = ui->textEdit->toPlainText();
    QStringList strList = str.split('\n');
    QString strINI;
    QVariant strINIV;
    int chnum; bool ch;
    for (auto Names : fishNames) {
        ch = false;
        for (int i = 0; i < strList.size(); i++) {
            str = strList.at(i);
            strINIV = m_settings->value(Names + "/" + fishNums[i]);
            strINI = strINIV.toString(); strINI = strINI.left(str.size());

            for (int num = 0; num < current.size(); num++) {
                if (current[num] == Names) {
                    ch = true; chnum = num; break;
                }
            }
            if (ch and str != strINI) {
                current.erase(current.begin() + chnum);
            }
            if (!ch) {
                if (str == strINI) current.append(Names);
            }

        }
    }
//    QVector<QString> fishNamesCur = fishNames;
//    for (int i = 0; i < strList.size(); i++) {
//        str = strList.at(i); ch = false;
//        for (auto Names : fishNamesCur) {
//            strINIV = m_settings->value(Names + "/" + fishNums[i]);
//            strINI = strINIV.toString(); strINI = strINI.left(str.size());
//            for (int num = 0; num < current.size(); num++) {
//                if (current[num] == Names) {
//                    ch = true; chnum = num; break;
//                }
//            }
//            if (ch and str != strINI) {
//                current.erase(current.begin() + chnum);
//            }
//            if (!ch) {
//                if (str == strINI) current.append(Names);
//            }
//        }
//        fishNamesCur = current;
//    }
    emit parseReady(current);
}

void MainWindow::displayFish(QVector<QString> list) {
    ui->listWidget->clear();
    for (auto i : list) ui->listWidget->addItem(i);
}
