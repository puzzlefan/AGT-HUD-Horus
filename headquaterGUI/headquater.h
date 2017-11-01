#ifndef HEADQUATER_H
#define HEADQUATER_H

#include <QMainWindow>
#include <QGridLayout>
#include <QImage>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QTableView>

class QTableView;
class QGridLayout;

class Person
{
public:
   Person(int ID);
   int ID;
   int recentStatus;
   int recentTempHead;
   int recentTempFoot;
   int recentCOHead;
   int recentCOFoot;
   QString Name;
   QString recentMessage;
   int recentAnswer;
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
    QGridLayout *layout;
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

    //communication
    QString Answers[3] = {" ","angenommen","nicht verfügbar"};

};

#endif // HEADQUATER_H
