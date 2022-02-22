#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    activeLine = 0;
    activeSegment = 0;
    w = false;
    l = false;

        //QFile file(QApplication::applicationDirPath() + "/wordlist.txt");
        //file.open(QIODevice::ReadWrite);
        std::fstream in;
        in.open("wordle.txt",std::ios::in);


        if(in.is_open()){
            //qDebug() << "qs";
            std::string s;

            while(std::getline(in,s)){
                //qDebug()<< QString::fromStdString(s);
                wordlist.append(s);
                //qDebug() << wordlist.size();


            }
            in.close();
        }
        else qDebug() << "f";

        for(int i = 0;i<5;i++){

            for(int j = 0;j<6;j++){

                grid[i][j] = ' ';
                colorGrid[i][j] = 'W';

            }
        }


        srand(time(NULL));
        randomWordNumber = rand() % 2315;
        randomWord = wordlist[randomWordNumber];

}

MainWindow::~MainWindow()
{
    delete ui;
    activeLine = 0;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    QPen pen(QColor(Qt::black),3);

    QPainterPath path;

    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setPen(pen);


    for(int i = 0;i<5;i++){
        for(int j = 0;j<6;j++){
                //painter.drawRect(10+j*110,10+i*110,100,100);


                path.addRoundedRect(QRectF(10+i*110,10+j*110,100,100), 10, 10);
                if(colorGrid[i][j] == 'Y')painter.fillPath(path,Qt::yellow);
                if(colorGrid[i][j] == 'G')painter.fillPath(path,QBrush (QColor("green")));
                else painter.drawPath(path);

        }
    }


    for(int i = 0;i<5;i++){
        for(int j = 0;j<6;j++){
            QString s;
            s.push_back(toupper(grid[i][j]));
            QFont font;
            font.setPixelSize(90);
            painter.setFont(font);

            painter.drawText(25+i*110,90+j*110,s);
        }
    }




    if(w == true) painter.drawText(30,300,"You won the game");

    if(l == true){
        std::string f = randomWord;
        QString s = "The word was:" + QString::fromStdString(f);
        QFont font;
        font.setPixelSize(56);
        painter.setFont(font);
        QPen pen;
        pen.setBrush(Qt::blue);

        painter.setPen(pen);
        painter.drawText(30,300,s);
    }

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if(w == false && l == false){
    if(activeSegment < 5 && isalpha(event->key()) == true){
        grid[activeSegment][activeLine] = event->key();
        activeSegment++;
        if(activeSegment == 5){
            checkForRightOnes();
            if(activeLine<6){

                activeLine++;
                activeSegment = 0;

                }
            }
            else{

        }


        }
    }
    update();
}

void MainWindow::checkForRightOnes()
{
    foundLetters.clear();
    std::string s;

        for(int i = 0;i<5;i++){
            s.push_back(grid[i][activeLine]);
        }

        if(s == randomWord){
            w = true;
            won();
        }
        if(s != randomWord && activeLine == 6){
            l = true;
            lost();
        }
        for(int i = 0;i<5;i++){
            for(int j = 0;j<5;j++){
                if(s.at(i) == randomWord.at(j)){
                    bool found = false;
                    for(int f = 0;f<foundLetters.size();f++)if(s.at(i) == foundLetters[f]) found = true;
                    if(found == false) foundLetters.append(s.at(i));
                }
            }
        }

        for(int i = 0;i<foundLetters.size();i++){
            for(int j = 0;j<5;j++){
                if(foundLetters[i] == s.at(j)){

                    colorGrid[j][activeLine] = 'Y';
                    j = 5;
                }
            }
        }

        for(int i = 0;i<5;i++){
            if(s.at(i) == randomWord.at(i))colorGrid[i][activeLine] = 'G';
        }

}

void MainWindow::won()
{
    w = true;
}

void MainWindow::lost()
{
    l = true;
}


