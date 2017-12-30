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
#include <QVector>

#include <../Netzwerk/server/server.h>
#include <../Netzwerk/User/User.h>

class QTableView;
class QGridLayout;
class QTabWidget;

class Person : public QWidget//%
{
    Q_OBJECT

public slots:
    void updateImage(unsigned char *data);

public:
    Person(int ID);

    //personal values
    int ID;
    int index;
    int vectorID;
    QString Name;

    int recentStatus;
    int recentAnswer;
    QString recentMessage;

    int recentTempHead;
    int recentTempFoot;
    int recentCOHead;
    int recentCOFoot;


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
    QVector<unsigned char> *result;
    QVector<unsigned short> *rawData;
    QImage *rgbImage;

    int ImageWidth = 320;
    int ImageHeight = 240;
    int FrameWidth = 160;
    int FrameHeight = 120;
    int PacketWidth = 80;
    int PacketWords = PacketWidth + 2;
    int RowPacketWords = 2*PacketWords;
    int PacketBytes = 2*PacketWords;
    int FrameWords = FrameWidth*FrameHeight;
    int SegmentHeight = FrameHeight/4;
    int SegmentPackets = 60;
    unsigned short rawMin;
    unsigned short rawMax;

   //for status
    void updateStatus();

    QLabel *Status;

    QString colon = ": ";
    QString Stati[5]= {"Status1","Status2","Status3","Status4","emergency"};
    QString Answers[3] = {" ","angenommen","nicht verfügbar"};
};

class headquater : public QMainWindow
{
    Q_OBJECT

public:
    headquater(std::vector<user>*Informations,QWidget *parent = 0);
    ~headquater();
    void newData(int vectorNo);

signals:
    void newConfirmedIDSignal(int ID, int vectorNo);
    void updatedStatusSignal(int ID, int recentStatus);
    void updatedTempHeadSignal(int ID, int recentTemp);
    void updatedTempFootSignal(int ID,int recentTemp);
    void updatedCOHeadSignal(int ID, int recentCO);
    void updatedCOFootSignal(int ID, int recentCO);
    void answerdMessageSignal(int ID, int answer);
    void updatedImageSignal(int ID, unsigned char*);
    void newDataSignal(int vectorNo);


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
    void updatedImage(int ID,unsigned char *result);
    void sortingData(int vectorNo);

private:
    //other
    QWidget *mainWidget;
    QGridLayout *layout;
    void createConnections();
    std::vector<user> *Infos;

    //Status related
    QLabel *HeaderStatus;
    int noPersons;

    //different Personaes
    int tabIndex[5];
    QString Name[5]= {"Tobias Finke","Aron Haselhoff","Timon Gronotte","Vicky Bietenbeck","Beke Pierick"};

    QVector<Person*> Persons;

    Person *PersonID0;
    Person *PersonID1;
    Person *PersonID2;
    Person *PersonID3;
    Person *PersonID4;

    QTabWidget *Tabs;
};

#endif // HEADQUATER_H
