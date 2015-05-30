#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QTime>
#include <QFont>
#include <QPalette>
#include <QObject>
#include <QKeyEvent>
#include <QEvent>
#include <QHash>
#include <QLayout>
#include <QtMath>



namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

  public:

    explicit Dialog(QWidget *parent = 0);
    void newgame(); //begin the game
    void upmove(); //上移
    void downmove(); //下移
    void leftmove(); //左移
    void rightmove(); //右移
    void upremoveblank();
    void downremoveblank();
    void leftremoveblank();
    void rightremoveblank();
    int testup(); //testing up
    int testdown(); //testing down
    int testright(); //testing right
    int testleft(); //testing left
    int panemax(); //max number in board
    int score=0;

    int ifwin(); //win or lose
    int ifGameOver();  //game over or not
    void update(const int& t);
    ~Dialog();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QWidget * widget;
    int pane[4][4]; //board

    Ui::Dialog *ui;
    QHash<int,QLabel*>labelHash;
    QGridLayout *layout;
};


#endif // DIALOG_H
