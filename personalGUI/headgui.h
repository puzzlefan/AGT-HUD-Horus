#ifndef HEADGUI_H
#define HEADGUI_H

#include <QtGui>
#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
//#include <LeptonThread.h>


class HeadGUI : public QMainWindow
{
    Q_OBJECT

public:
    HeadGUI(QWidget *parent = 0);
    ~HeadGUI();
    void test();

//public slots:
  //  void updateImage(unsigned short *, int, int);

signals:
    void upSignal();
    void downSignal();
    void rightSignal();
    void leftSignal();
    void backSignal();
    void certifySignal();
/*
private slots:
    void up();
    void down();
    void right();
    void left();
    void back();
    void certify();
*/
private:
    QGridLayout *layout;
    QWidget *mainWidget;

    //navigation/communication
    void createCommunication();
    QLabel *Status;
    QMenu *ChoosingStatus;//% right class
    QLabel *Messages;
    QMenu * CoosingMessage;
    int vertical;
    int horizontal;
    int emergency;

    //biometric data
    void createBiometric();
    QLabel *Personae;
    QLabel *TempHead;
    QLabel *TempFoot;
    QLabel *COHead;
    QLabel *COFoot;
    QString Name [4]= {"Aron Haselhoff","Timon Gronotte","Vicky Bietenbeck","Beke Pierick"};

    //for Camera
    void createIRPicture();
    QLabel *IRPicture;
    QVector<unsigned short> rawData;
    QImage rgbImage;
    enum { ImageWidth = 320, ImageHeight = 240 };
 //   LeptonThread *thread;//%
    unsigned short rawMin, rawMax;

};

#endif // HEADGUI_H
