#include "widget.h"
#include "./ui_widget.h"
#include <QPixmap>
#include <QPainter>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->scrollArea->setGeometry(0,0,800,700); // 內部邊框
    ui->scrollArea->setWidgetResizable(false);

    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setGeometry(0,0,2000, 2000);// 內容的範圍


    ui->lineEdit->setGeometry(0, 0, 200, 20);
    ui->label->setGeometry(200, 0, 100, 20);

    ui->lineEdit_2->setGeometry(400, 0, 200, 20);
    ui->label_2->setGeometry(600, 0, 100, 20);

    ui->lineEdit_3->setGeometry(0, 20, 200, 20);
    ui->label_3->setGeometry(200, 20, 100, 20);

    ui->lineEdit_4->setGeometry(400, 20, 200, 20);
    ui->label_4->setGeometry(600, 20, 100, 20);

    ui->pushButton->setGeometry(680, 0, 90, 20);

    ui->label_5->setGeometry(0, 60, 2000, 2000);
}

Widget::~Widget()
{
    delete ui;
}

const std::vector<std::string> split_pattern(const std::string& str, const std::string& pattern) {
    std::vector<std::string> result;
    std::string::size_type begin, end;

    end = str.find(pattern);
    begin = 0;

    while (end != std::string::npos) {
        if (end - begin != 0) {
            result.push_back(str.substr(begin, end-begin));
        }
        begin = end + pattern.size();
        end = str.find(pattern, begin);
    }

    if (begin != str.length()) {
        result.push_back(str.substr(begin));
    }
    return result;
}



void Widget::on_pushButton_clicked()
{
    QPixmap pixmap(2000,2000);
    pixmap.fill(Qt::white);  // Fill with white background
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);

    string pattern=",";
    QString qtask,qlength,qstart,qend;
    qtask = ui->lineEdit->text();
    qlength = ui->lineEdit_2->text();
    qstart = ui->lineEdit_3->text();
    qend = ui->lineEdit_4->text();

    string task="",length="",start="",end="";
    task = qtask.toStdString();
    length = qlength.toStdString();
    start = qstart.toStdString();
    end = qend.toStdString();

    vector<string> ret1 = split_pattern(task,pattern);
    vector<string> ret2 = split_pattern(length,pattern);
    vector<string> ret3 = split_pattern(start,pattern);
    vector<string> ret4 = split_pattern(end,pattern);


    int len=ret1.size();
    int countline=1;
    int ini_x=200;
    int max=0;
    for(int i=0;i<len;i++){
        int tmp=ret1[i].size();
        if(tmp>max){
            max=tmp;
        }
    }
    int initmpx=max;

    string ini_text1,ini_text2,ini_text3,ini_text4;
    ini_text1="任務項目";
    ini_text2="起始時間";
    ini_text3="完成時間";
    ini_text4="所需時間";

    QString qinitext1,qinitext2,qinitext3,qinitext4;
    int countini=0;
    qinitext1 =QString::fromStdString(ini_text1);
    qinitext2 =QString::fromStdString(ini_text2);
    qinitext3 =QString::fromStdString(ini_text3);
    qinitext4 =QString::fromStdString(ini_text4);
    painter.drawText(ini_x+countini*initmpx*5,100,qinitext1);
    countini++;
    painter.drawText(ini_x+countini*initmpx*5,100,qinitext2);
    countini++;
    painter.drawText(ini_x+countini*initmpx*5,100,qinitext3);
    countini++;
    painter.drawText(ini_x+countini*initmpx*5,100,qinitext4);






    for(int i=0;i<len;i++){
        int x=0;
        string tmp="";
        QString qsec_out;
        tmp=ret1[i];
        int var=75;

        qsec_out = QString::fromStdString(tmp);
        painter.drawText(ini_x+x*initmpx*5,100+countline*20,qsec_out);
        x++;
        tmp=ret3[i];
        qsec_out = QString::fromStdString(tmp);
        painter.drawText(ini_x+x*initmpx*5,100+countline*20,qsec_out);
        x++;
        tmp=ret4[i];
        qsec_out = QString::fromStdString(tmp);
        painter.drawText(ini_x+x*initmpx*5,100+countline*20,qsec_out);
        x++;
        tmp=ret2[i];
        qsec_out = QString::fromStdString(tmp);
        painter.drawText(ini_x+x*initmpx*5,100+countline*20,qsec_out);
        countline++;
    }

    countline=countline+3;
    int x_hourv=26;
    int x_hour=0;
    int start_drawing_pos=0;
    for(int i=6;i<23;i++){
        QString qhour;
        string hour= to_string(i);
        qhour =QString::fromStdString(hour);
        painter.drawText(ini_x+x_hour*x_hourv,100+countline*20,qhour);
        if(i==6){
            start_drawing_pos=ini_x+x_hour*x_hourv;
        }
        x_hour++;
    }
    countline++;
    for(int i=0;i<len;i++){
        QString qsec_out;
        string tmp="";
        int trans1=0,trans2=0;
        trans1=stoi(ret3[i]);//start
        trans2=stoi(ret2[i]);//length
        tmp=ret1[i];
        qsec_out = QString::fromStdString(tmp);
        painter.drawText(ini_x-100,100+countline*20,qsec_out);
        painter.setBrush(Qt::yellow);
        painter.setPen(Qt::yellow);

        painter.drawRect(ini_x+(trans1-6)*x_hourv, 100+countline*20-17, trans2*x_hourv+10,18);
        painter.setPen(Qt::black);
        countline++;
    }

    for(int i=0;i<len;i++){

    }


    painter.end();
    ui->label_5->setPixmap(pixmap);
}

