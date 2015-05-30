#include "dialog.h"
#include "ui_dialog.h"
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    layout = new QGridLayout;
    labelHash.insert(0,ui->label);
    labelHash.insert(1,ui->label_2);
    labelHash.insert(2,ui->label_3);
    labelHash.insert(3,ui->label_4);
    labelHash.insert(4,ui->label_5);
    labelHash.insert(5,ui->label_6);
    labelHash.insert(6,ui->label_7);
    labelHash.insert(7,ui->label_8);
    labelHash.insert(8,ui->label_9);
    labelHash.insert(9,ui->label_10);
    labelHash.insert(10,ui->label_11);
    labelHash.insert(11,ui->label_12);
    labelHash.insert(12,ui->label_13);
    labelHash.insert(13,ui->label_14);
    labelHash.insert(14,ui->label_15);
    labelHash.insert(15,ui->label_16);


    for(int i=0;i<16;i++)
    {
        labelHash.value(i)->setFrameShape(QLabel::Box);
        labelHash.value(i)->setText(" ");
        layout->addWidget(labelHash.value(i),i/4,i%4,1,1);
    }
    layout->setSpacing(4);
    this->ui->widget->setLayout(layout);
    this->ui->widget->resize(300,300);
    newgame();

}
void Dialog::newgame() //game start
{
     QTime time;
     time = QTime::currentTime();
     qsrand(time.msec()+time.second()*1000);
     for(int i=0;i<=3;i++) //init it
        for(int j=0;j<=3;j++)
             pane[i][j]=0;
     int m=qrand()%4;
     int n=qrand()%4;
     int b=qrand()%4;
     int q=qrand()%4;

     pane[m][n]=pane[b][q]=2;
    update(0);

}
void Dialog::upremoveblank()
{
    for(int j=0;j<4;j++){
        int k = 0;
        for(int i=0;i<4;i++){
            if(pane[i][j] != 0)
                pane[k++][j] = pane[i][j];
            }
        while(k<4)
        {
            pane[k][j] = 0;
            k++;
        }
    }
}

void Dialog::downremoveblank()
{
    for(int j=0;j<4;j++){
        int k = 3;
        for(int i=3;i>=0;i--){
            if(pane[i][j] != 0)
                pane[k--][j] = pane[i][j];
            }
        while(k>=0)
        {
            pane[k][j] = 0;
            k--;
        }
    }
}

void Dialog::leftremoveblank()
{
    for(int i=0;i<4;i++){
        int k = 0;
        for(int j=0;j<4;j++){
            if(pane[i][j] != 0)
                pane[i][k++] = pane[i][j];
            }
        while(k<4)
        {
            pane[i][k] = 0;
            k++;
        }
    }
}

void Dialog::rightremoveblank()
{
    for(int i=0;i<4;i++){
        int k = 3;
        for(int j=3;j>=0;j--){
            if(pane[i][j] != 0)
                pane[i][k--] = pane[i][j];
            }
        while(k>=0)
        {
            pane[i][k] = 0;
            k--;
        }
    }
}

void Dialog::upmove() //上移
{
     for(int j=0;j<4;j++){//每一列
         for(int i=0;i<3;i++){
             if(pane[i][j]==pane[i+1][j]){
                 pane[i][j]=pane[i][j]+pane[i+1][j];
                 score += pane[i][j];
                 pane[i+1][j]=0;
                 //移除空格
                 upremoveblank();
             }
         }
     }
}
void Dialog::downmove() //下移
{
   for(int j=0;j<4;j++){//每一列
       for(int i=3;i>=1;i--){
           if(pane[i][j]==pane[i-1][j]){
               pane[i][j]=pane[i][j]+pane[i-1][j];
               score += pane[i][j];
               pane[i-1][j]=0;
               //移除空格
               downremoveblank();
           }
       }
   }
}
void Dialog::leftmove() //左移
{
   for(int i = 0;i < 4;i++){
       for(int j = 0;j<3;j++){
           if(pane[i][j]==pane[i][j+1]){
               pane[i][j]+=pane[i][j+1];
               score += pane[i][j];
               pane[i][j+1]=0;
               leftremoveblank();
           }
       }
   }
}
void Dialog::rightmove() //右移
{
    for(int i=0;i<4;i++){
        for(int j=3;j >= 1;j--){
            if(pane[i][j]==pane[i][j-1]){
                pane[i][j]+=pane[i][j-1];
                score += pane[i][j];
                pane[i][j-1]=0;
                rightremoveblank();
            }
        }
    }
}
int Dialog::testup() //能否上移测试
{
    int flag=0;
    for(int j=0;j<=3;j++)
        for(int i=0;i<3;i++)
        {
            if(pane[i][j] == pane[i+1][j] || pane[i][j] == 0)
            {
                flag=1;
            }
        }
    return flag;
}
int Dialog::testdown() //测试能否下移
{
    int flag=0;
    for(int j=0;j<=3;j++)
        for(int i=3;i>0;i--)
        {
            if(pane[i][j] == pane[i-1][j] || pane[i][j] == 0)
            {
                 flag=1;
            }
        }
    return flag;
}
int Dialog::testleft() //测试能否左移
{
    int flag=0;
    for(int i=0;i<=3;i++)
        for(int j=0;j<3;j++)
        {
           if(pane[i][j] == pane[i][j+1] || pane[i][j] == 0)
            {
                 flag=1;
            }
        }
    return flag;
}
int Dialog::testright() //测试能否右移
{
    int flag=0;
    for(int i=0;i<=3;i++)
        for(int j=3;j>0;j--)
        {
           if(pane[i][j] == pane[i][j-1] || pane[i][j] == 0)
            {
                 flag=1;
            }
        }
    return flag;
}
int Dialog::panemax() //棋盘最大数
{
    int max=pane[0][0];
    for(int i=0;i<=3;i++)
        for(int j=0;j<=3;j++)
            if(pane[i][j]>max)
                max=pane[i][j];
    return max;
}
int Dialog::ifwin() //判断是否胜利
{
    int flag=0;
    if(panemax()==2048)
    {
        QMessageBox::about(this,"Congratulation","You Win!");
        flag=1;
    }
    return flag;
}
int Dialog::ifGameOver()  //判断是否游戏结束
{
    int flag=0;
    if(testup()+ testdown() + testleft() + testright() == 0)
    {
        QMessageBox::about(this,"Failed","Game Over!");
        flag=1;
    }
    return flag;
}

void Dialog::keyPressEvent(QKeyEvent *event)
{
    QTime time;
    static int t = 0;
    time = QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    switch (event->key()) {
    case Qt::Key_Up:
        upremoveblank();
        upmove();
        for(int i = 0,timer =0 ; timer < 1; i ++){
            if(pane[3][i] == 0)
                if(qrand()%2){
                    pane[3][i] = 2;
                    timer++;
                }
            }
        t++;
        update(t);
        break;
    case Qt::Key_Down:
        downremoveblank();
        downmove();
        for(int i = 0,timer =0 ; timer < 1; i ++)
         {
            if(pane[0][i] == 0)
                if(qrand()%2){
                    pane[0][i] = 2;
                    timer++;
                }
        }
         t++;
        update(t);
        break;
    case Qt::Key_Left:
        leftremoveblank();
        leftmove();

       for(int i = 0,timer =0 ; timer < 1; i ++){
            if(pane[i][3] == 0)
                if(qrand()%2){
                    pane[i][3] = 4;
                    timer ++;
                }
       }
        t++;
       update(t);
        break;
    case Qt::Key_Right:
        rightremoveblank();
        rightmove();
        for(int i = 0,timer =0 ; timer < 1; i ++){
            if(pane[i][0] == 0)
                if(qrand()%2){
                    pane[i][0] = 2;
                    timer++;
                }
        }
         t++;
       update(t);
        break;
    default:
        break;
    }
}

void Dialog::update(const int &t)
{
    ifGameOver();
    ifwin();
    for(int i = 0 ; i < 4 ; i++)
        for(int j = 0; j < 4; j++)
        {
            int p = i*4+j;
            if(pane[i][j])
            {
                labelHash.value(p)->setText(QString::number(pane[i][j]));
            }
            else
                labelHash.value(p)->setText(" ");
            QFont ftt;
            ftt.setPointSize(28);
            //labelHash.value(p)->setFont(ftt);
           // QPalette pa;
           // pa.setColor(QPalette::WindowText,Qt::white);
            //labelHash.value(p)->setPalette(pa);
            labelHash.value(p)->setAlignment(Qt::AlignCenter);
            //labelHash.value(p)->setStyleSheet("background-color:red");
        }
    ui->lcdNumber->display(QString::number(score));
   ui->lcdNumber_2->display(QString::number(t));
}


Dialog::~Dialog()
{
    delete layout;
    delete widget;
    delete ui;
}
