#include "headquater.h"

//#include "LeptonThread.h"
#include <iostream>

#include <QGridLayout>
#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QTableView>

headquater::headquater(QWidget *parent)
    : QMainWindow(parent)
{
    mainWidget = new QWidget;
    layout = new QGridLayout;

    mainWidget->setWindowTitle("HeadquaterGUI Leitstelle");
    mainWidget->setLayout(layout);
    mainWidget->show();
}

void headquater::newConfirmedID(int ID)
{
    switch (ID)
    {
    case 1:
    {
        Person PersonID1(ID);
        PersonID1.Name = Name[ID];

        break;
    }
    case 2:
    {
        Person PersonID2(ID);
        PersonID2.Name = Name[ID];

        break;
    }
    case 3:
    {
        Person PersonID3(ID);
        PersonID3.Name = Name[ID];

        break;
    }
    case 4:
    {
        Person PersonID4(ID);
        PersonID4.Name = Name[ID];

        break;
    }
    }

}

void headquater::updatedStatus(int ID, int recentStatus)
{
    switch(ID)
    {
    case 1:
       PersonID1->recentStatus = recentStatus;

        break;

    case 2:
        PersonID2->recentStatus = recentStatus;

        break;

    case 3:
        PersonID3->recentStatus = recentStatus;

        break;

    case 4:
        PersonID4->recentStatus = recentStatus;

        break;
    }
}

void headquater::updatedTempHead(int ID, int recentTemp)
{
    switch(ID)
    {
    case 1:
        PersonID1->recentTempHead = recentTemp;

        break;

    case 2:
        PersonID2->recentTempHead = recentTemp;

        break;

    case 3:
        PersonID3->recentTempHead = recentTemp;

        break;

    case 4:
        PersonID4->recentTempHead = recentTemp;

        break;
    }
}

void headquater::updatedTempFoot(int ID, int recentTemp)
{
    switch(ID)
    {
    case 1:
        PersonID1->recentTempFoot = recentTemp;

        break;

    case 2:
        PersonID2->recentTempFoot = recentTemp;

        break;

    case 3:
        PersonID3->recentTempFoot = recentTemp;

        break;

    case 4:
        PersonID4->recentTempFoot = recentTemp;

        break;
    }
}

void headquater::updatedCOHead(int ID, int recentCO)
{
    switch(ID)
    {
    case 1:
        PersonID1->recentCOHead = recentCO;

        break;

    case 2:
        PersonID2->recentCOHead = recentCO;

        break;

    case 3:
        PersonID3->recentCOHead = recentCO;

        break;

    case 4:
        PersonID4->recentCOHead = recentCO;

        break;
    }
}

void headquater::updatedCOFoot(int ID, int recentCO)
{
    switch(ID)
    {
    case 1:
        PersonID1->recentCOFoot = recentCO;

        break;

    case 2:
        PersonID2->recentCOFoot = recentCO;

        break;

    case 3:
        PersonID3->recentCOFoot = recentCO;

        break;

    case 4:
        PersonID4->recentCOFoot = recentCO;

        break;
    }
}

void headquater::answerdMessage(int ID, int answer)
{
    switch(ID)
    {
    case 1:
        PersonID1->recentAnswer = answer;

        break;

    case 2:
        PersonID2->recentAnswer = answer;

        break;

    case 3:
        PersonID3->recentAnswer = answer;

        break;

    case 4:
        PersonID4->recentAnswer = answer;

        break;
    }
}

void headquater::sendNewMessage(int ID, QString Message)
{
    //choosing right Adress and emit signal + Message
}

headquater::~headquater()
{

}

Person::Person(int trueID)
{
    //initializing values
    ID = trueID;
    recentStatus = 0;
    recentTempHead = 0;
    recentTempFoot = 0;
    recentCOHead = 0;
    recentCOFoot =0;
    recentMessage = " ";
    recentAnswer = 0;
}
