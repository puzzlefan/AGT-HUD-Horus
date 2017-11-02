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

class QTableView;
class QGridLayout;
class QTabWidget;

class Person : public QWidget
{
    Q_OBJECT

//public slots:
//    void updateImage(unsigned short *, int, int);

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
    enum { ImageWidth = 320, ImageHeight = 240 };
//   LeptonThread *thread;//%
   unsigned short rawMin, rawMax;

   //for status
    void updateStatus();
    QLabel *Status;
    QString colon = ": ";
    QString Stati[4]= {"Status1","Status2","Status3","Status4"};

};

class headquater : public QMainWindow
{
    Q_OBJECT

public:
    headquater(QWidget *parent = 0);
    ~headquater();

signals:
    void newMessage(int ID, QString Message);


private slots:
    void newConfirmedID(int ID);
    void updatedStatus(int ID, int recentStatus);
    void updatedTempHead(int ID, int recentTemp);
    void updatedTempFoot(int ID,int recentTemp);
    void updatedCOHead(int ID, int recentCO);
    void updatedCOFoot(int ID, int recentCO);
    void answerdMessage(int ID, int answer);
    void sendNewMessage();
    void newTopTab(int index);

private:
    //other
    QWidget *mainWidget;
    QGridLayout *layout;//really useful
    void createConnections();

    //Status related
    QLabel *HeaderStatus;
    int noPersons;

    //different Personaes
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
