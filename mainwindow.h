#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <fstream>
#include <string>
#include <QDebug>
#include <QPainterPath>
#include <QFile>
#include <QString>
#include <iostream>
#include <vector>
#include <QKeyEvent>
#include <cctype>
#include <ctime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
private:
    Ui::MainWindow *ui;
    int activeLine;
    int activeSegment;
    char grid[5][6];
    char colorGrid[5][6];
    QVector<std::string> wordlist;
    int randomWordNumber;
    std::string randomWord;
    void checkForRightOnes();
    void won();
    void lost();
    bool w;
    bool l;
    QVector<char>foundLetters;
};
#endif // MAINWINDOW_H
