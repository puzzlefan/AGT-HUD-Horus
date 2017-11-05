#ifndef HEADQUATER_H
#define HEADQUATER_H

#include <QMainWindow>
#include <QGridLayout>
#include <QImage>
#include <QLabel>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QPainter>

#include <mutex>

class QTableView;
class QGridLayout;
class QTabWidget;

class Person : public QWidget
{
    Q_OBJECT

public slots:
    void updateImage(unsigned short *, int, int);

public:
    Person(int ID);

    //personal values
    int ID;
    int recentStatus;
    int recentTempHead;
    int recentTempFoot;
    int recentCOHead;
    int recentCOFoot;
    QString Name;
    QString recentMessage;
    int recentAnswer;
    int index;

    //for own page
    void pageSetUp();
    void updateTempHead();
    void updateTempFoot();
    void updateCOHead();
    void updateCOFoot();
    void updateTab();
    void updateMessage();
    QWidget *personalTab;
    QGridLayout *personalLayout;
    QLabel *answer;
    QTextEdit *messageText;
    QPushButton *enteringMessage;
    QLabel *additionalData;
    QLabel *TempHead;
    QLabel *TempFoot;
    QLabel *COHead;
    QLabel *COFoot;
    QString unitTemp =" °C";
    QString unitCO = " ppm";

    //for IRPicture
    QLabel *IRPicture;
    QVector<unsigned short> rawData;
    QImage rgbImage;
    int ImageWidth = 320;
    int ImageHeight = 240;
    unsigned short rawMin, rawMax;
    int FrameWidth = 160;
    int FrameHeight = 120;
    int PacketWidth = 80;
    int PacketWords = PacketWidth + 2;
    int RowPacketWords = 2*PacketWords;
    int PacketBytes = 2*PacketWords;
    int FrameWords = FrameWidth*FrameHeight;
    int SegmentHeight = FrameHeight/4;
    int SegmentPackets = 60;

   //for status
    void updateStatus();
    QLabel *Status;
    QString colon = ": ";
    QString Stati[5]= {"Status1","Status2","Status3","Status4","emergency"};

};

class headquater : public QMainWindow
{
    Q_OBJECT

public:
    headquater(QWidget *parent = 0);
    ~headquater();
    void newData(int vectorNo);

signals:
    void newMessage(int ID, QString Message);
    void newConfirmedIDSignal(int ID, int vectorNo);
    void updatedStatusSignal(int ID, int recentStatus);
    void updatedTempHeadSignal(int ID, int recentTemp);
    void updatedTempFootSignal(int ID,int recentTemp);
    void updatedCOHeadSignal(int ID, int recentCO);
    void updatedCOFootSignal(int ID, int recentCO);
    void answerdMessageSignal(int ID, int answer);
    void newDataSignal(int vectorNo);
    void updatedImageSignal(int ID, unsigned short *, int, int);


private slots:
    void newConfirmedID(int ID, int vectorNo);
    void updatedStatus(int ID, int recentStatus);
    void updatedTempHead(int ID, int recentTemp);
    void updatedTempFoot(int ID,int recentTemp);
    void updatedCOHead(int ID, int recentCO);
    void updatedCOFoot(int ID, int recentCO);
    void answerdMessage(int ID, int answer);
    void sendNewMessage();
    void newTopTab(int index);
    void readingNewData(int vectorNo);
    void updatedImage(int ID,unsigned short *, int, int);

private:
    //other
    QWidget *mainWidget;
    QGridLayout *layout;//really useful
    void createConnections();

    //Status related
    QLabel *HeaderStatus;
    int noPersons;

    //different Personaes
    int vectorNumber[5];
    int tabIndex[4];
    QString Name[5]= {" ","Aron Haselhoff","Timon Gronotte","Vicky Bietenbeck","Beke Pierick"};
    Person *PersonID1;
    Person *PersonID2;
    Person *PersonID3;
    Person *PersonID4;
    QTabWidget *Tabs;

    //communication
    QString Answers[3]= {" ","angenommen","nicht verfügbar"};


};

#endif // HEADQUATER_H
