#ifndef HEADQUATER_H
#define HEADQUATER_H

#include <QMainWindow>
#include <QGridLayout>
#include <QImage>
#include <QLabel>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QTableView>
#include <QTabWidget>

class QTableView;
class QGridLayout;
class QTabWidget;

class Person : public QWidget
{
    Q_OBJECT

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

   //for own page
   void pageSetUp();
   QWidget *personalTab;
   QGridLayout *personalLayout;
   QImage *IRPicture;
   QLabel *answer;
   QTextEdit *messageText;
   QPushButton *enteringMessage;
   QLabel *additionalData;
   QLabel *TempHead;
   QLabel *TempFoot;
   QLabel *COHead;
   QLabel *COFoot;

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
    void sendNewMessage(int ID, QString Message);

private:
    //other
    QWidget *mainWidget;
    QGridLayout *layout;//really useful
    void createConnections();

    //Status related
    QTableView *StatusView;
    QString Stati[4]={"Status1","Status2","Status3","Status4"};

    //different Personaes
    QString Name [5]= {" ","Aron Haselhoff","Timon Gronotte","Vicky Bietenbeck","Beke Pierick"};
    Person *PersonID1;
    Person *PersonID2;
    Person *PersonID3;
    Person *PersonID4;
    QTabWidget *Tabs;

    //communication
    QString Answers[3] = {" ","angenommen","nicht verfügbar"};

};

#endif // HEADQUATER_H
