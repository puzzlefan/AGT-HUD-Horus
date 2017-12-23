#include "headquater.h"

#include <iostream>

#include <../Netzwerk/server/server.h>
#include <../Netzwerk/User/User.h>

#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QPixmap>
#include <QVector>

headquater::headquater(std::vector<user>*Informations, QWidget *parent)
    : QMainWindow(parent)
{
    mainWidget = new QWidget;
    layout = new QGridLayout;

    Tabs = new QTabWidget;
    layout->addWidget(Tabs, 0, 0, 4, 6);

    Infos=Informations;

    Persons.append(PersonID0);
    Persons.append(PersonID1);
    Persons.append(PersonID2);
    Persons.append(PersonID3);
    Persons.append(PersonID4);

    createConnections();

    HeaderStatus = new QLabel;
    layout->addWidget(HeaderStatus, 0, 6, 1, 1, Qt::AlignCenter);
    HeaderStatus->setText("Stati:");

    mainWidget->resize(1000,750);

    mainWidget->setWindowTitle("HeadquaterGUI Leitstelle");
    mainWidget->setLayout(layout);
    mainWidget->show();

    noPersons = 1;
}

void headquater::createConnections()
{
    connect(this,SIGNAL(newConfirmedIDSignal(int,int)),this,SLOT(newConfirmedID(int,int)),Qt::DirectConnection);

    connect(this,SIGNAL(updatedImageSignal(int,unsigned char*)),this,SLOT(updatedImage(int,unsigned char*)),Qt::DirectConnection);
    connect(this,SIGNAL(updatedStatusSignal(int,int)),this,SLOT(updatedStatus(int,int)),Qt::DirectConnection);

    connect(this,SIGNAL(updatedTempHeadSignal(int,int)),this,SLOT(updatedTempHead(int,int)),Qt::DirectConnection);
    connect(this,SIGNAL(updatedTempFootSignal(int,int)),this, SLOT(updatedTempFoot(int,int)),Qt::DirectConnection);
    connect(this,SIGNAL(updatedCOHeadSignal(int,int)),this,SLOT(updatedCOHead(int,int)),Qt::DirectConnection);
    connect(this,SIGNAL(updatedCOFootSignal(int,int)),this,SLOT(updatedCOFoot(int,int)),Qt::DirectConnection);
    connect(this,SIGNAL(answerdMessageSignal(int,int)),this,SLOT(answerdMessage(int,int)),Qt::DirectConnection);

    connect(this,SIGNAL(newDataSignal(int)),this,SLOT(sortingData(int)),Qt::BlockingQueuedConnection);
    connect(Tabs,SIGNAL(currentChanged(int)),this,SLOT(newTopTab(int)));
}

void headquater::newData(int vectorNo)
{
    emit newDataSignal(vectorNo);
}

void headquater::sortingData(int vectorNo)
{
    int ID = Infos->at(vectorNo).getID();

    if(Infos->at(vectorNo).getBool(NEW_CONFIRMED_ID) == true)
    {
        Infos->at(vectorNo).setBools(NEW_CONFIRMED_ID,false);
        emit newConfirmedIDSignal(ID, vectorNo);
    }

    if(Infos->at(vectorNo).getBool(UPDATED_STATUS_SIGNAL) == true)
    {
        Infos->at(vectorNo).setBools(UPDATED_STATUS_SIGNAL,false);
        emit updatedStatus(ID,Infos->at(vectorNo).getInt(RECENT_STATUS));
    }

    if(Infos->at(vectorNo).getBool(UPDATED_TEMP_HEAD_SIGNAL) == true)
    {
        Infos->at(vectorNo).setBools(UPDATED_TEMP_HEAD_SIGNAL,false);
        emit updatedTempHeadSignal(ID,Infos->at(vectorNo).getInt(RECENT_TEMP_HEAD));
    }

    if(Infos->at(vectorNo).getBool(UPDATED_TEMP_FOOT_SIGNAL) == true)
    {
        Infos->at(vectorNo).setBools(UPDATED_TEMP_FOOT_SIGNAL,false);
        emit updatedTempFootSignal(ID,Infos->at(vectorNo).getInt(RECENT_TEMP_FOOT));
    }

    if(Infos->at(vectorNo).getBool(UPDATED_CO_HEAD_SIGNAL) == true)
    {
        Infos->at(vectorNo).setBools(UPDATED_CO_HEAD_SIGNAL,false);
        emit updatedCOHeadSignal(ID,Infos->at(vectorNo).getInt(RECENT_CO_HEAD));
    }

    if(Infos->at(vectorNo).getBool(UPDATED_CO_FOOT_SIGNAL) == true)
    {
        Infos->at(vectorNo).setBools(UPDATED_CO_FOOT_SIGNAL,false);
        emit updatedCOFootSignal(ID,Infos->at(vectorNo).getInt(RECENT_CO_FOOT));
    }

    if(Infos->at(vectorNo).getBool(UPDATE_IMAGE_SIGNAL)==true)
    {
        Infos->at(vectorNo).setBools(UPDATE_IMAGE_SIGNAL,false);
        Infos->at(vectorNo).setBITBildMutex(true);
        emit updatedImageSignal(ID,Infos->at(vectorNo).getBITBild());
        Infos->at(vectorNo).setBITBildMutex(false);
    }
}

void headquater::newConfirmedID(int ID, int vectorNo)
{
    Persons[ID] = new Person(ID);
    Persons.at(ID)->Name = Name[ID];
    Persons.at(ID)->vectorID = vectorNo;
    Persons.at(ID)->pageSetUp();
    connect(Persons.at(ID)->enteringMessage,SIGNAL(clicked(bool)),this,SLOT(sendNewMessage()));

    Persons.at(ID)->index = noPersons - 1;
    tabIndex[Persons.at(ID)->index] = ID;

    Tabs->addTab(Persons.at(ID)->personalTab, Persons[ID]->Name);

    Persons.at(ID)->Status = new QLabel;
    layout->addWidget(Persons.at(ID)->Status,noPersons,6,1,1,Qt::AlignCenter);
    Persons.at(ID)->Status->setText(Persons.at(ID)->Name);

    noPersons++;
}

void headquater::updatedImage(int ID, unsigned char *result)
{
    if(Persons.at(ID)->index == Tabs->currentIndex())
    {
        Persons.at(ID)->updateImage(result);
    }
}

void headquater::updatedStatus(int ID, int recentStatus)
{
    Persons.at(ID)->recentStatus = recentStatus;
    Persons.at(ID)->updateStatus();
}

void headquater::sendNewMessage()
{
    int sendToID = tabIndex[Tabs->currentIndex()];
    QString txtMessage;
    std::string stdMessage;

    txtMessage = Persons.at(sendToID)->messageText->toPlainText();
    stdMessage = txtMessage.toUtf8().constData();

    Infos->at(Persons.at(sendToID)->vectorID).setBools(NEW_MESSAGE,true);
    Infos->at(Persons.at(sendToID)->vectorID).setMessage(stdMessage);
}

void headquater::answerdMessage(int ID, int answer)
{
    Persons.at(ID)->recentAnswer = answer;
    if(Persons.at(ID)->index == Tabs->currentIndex())
    {
        Persons.at(ID)->updateMessage();
    }
}

void headquater::updatedTempHead(int ID, int recentTemp)
{
    Persons.at(ID)->recentTempHead = recentTemp;
    if(Persons.at(ID)->index == Tabs->currentIndex())
    {
        Persons.at(ID)->updateTempHead();
    }
}

void headquater::updatedTempFoot(int ID, int recentTemp)
{
    Persons.at(ID)->recentTempFoot = recentTemp;
    if(Persons.at(ID)->index == Tabs->currentIndex())
    {
        Persons.at(ID)->updateTempFoot();
    }
}

void headquater::updatedCOHead(int ID, int recentCO)
{
    Persons.at(ID)->recentCOHead = recentCO;
    if(Persons.at(ID)->index == Tabs->currentIndex())
    {
        Persons.at(ID)->updateCOHead();
    }
}

void headquater::updatedCOFoot(int ID, int recentCO)
{
    Persons.at(ID)->recentCOFoot = recentCO;
    if(Persons.at(ID)->index == Tabs->currentIndex())
    {
        Persons.at(ID)->updateCOFoot();
    }
}

void headquater::newTopTab(int index)
{
    int tabID = tabIndex[index];
    Persons.at(tabID)->updateTab();
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

void Person::pageSetUp()//: rawData(FrameWords),
//rgbImage(FrameWidth, FrameHeight, QImage::Format_RGB888)
{
    personalTab = new QWidget;
    personalLayout = new QGridLayout;

    IRPicture = new QLabel;
    personalLayout->addWidget(IRPicture, 0, 0, 3, 2, Qt::AlignCenter);

    QPixmap filler(ImageWidth, ImageHeight);
    filler.fill(Qt::red);
    IRPicture->setPixmap(filler);

   // connect(thread, SIGNAL(updateImage(unsigned short *,int,int)), this, SLOT(updateImage(unsigned short *, int,int)));//%

    additionalData = new QLabel;
    personalLayout->addWidget(additionalData,0,2,1,2, Qt::AlignCenter);

    TempHead = new QLabel;
    personalLayout->addWidget(TempHead,1,2,1,1, Qt::AlignCenter);
    TempHead->setText(unitTemp);

    TempFoot = new QLabel;
    personalLayout->addWidget(TempFoot,1,3,1,1, Qt::AlignCenter);
    TempFoot->setText(unitTemp);

    COHead = new QLabel;
    personalLayout->addWidget(COHead,2,2,1,1, Qt::AlignCenter);
    COHead->setText(unitCO);

    COFoot = new QLabel;
    personalLayout->addWidget(COFoot,2,3,1,1, Qt::AlignCenter);
    COFoot->setText(unitCO);

    messageText = new QTextEdit;
    personalLayout->addWidget(messageText,3,0,1,4);

    enteringMessage = new QPushButton;
    personalLayout->addWidget(enteringMessage,4,0,1,4);//maybe smaller
    enteringMessage->setText("Nachricht versenden");

    answer = new QLabel;
    personalLayout->addWidget(answer,5,0,1,4);

    personalTab->setLayout(personalLayout);
}

//Color for IRCamera
const int colormap[] = {255, 255, 255, 253, 253, 253, 251, 251, 251, 249, 249, 249, 247, 247, 247, 245, 245, 245, 243, 243, 243, 241, 241, 241, 239, 239, 239, 237, 237, 237, 235, 235, 235, 233, 233, 233, 231, 231, 231, 229, 229, 229, 227, 227, 227, 225, 225, 225, 223, 223, 223, 221, 221, 221, 219, 219, 219, 217, 217, 217, 215, 215, 215, 213, 213, 213, 211, 211, 211, 209, 209, 209, 207, 207, 207, 205, 205, 205, 203, 203, 203, 201, 201, 201, 199, 199, 199, 197, 197, 197, 195, 195, 195, 193, 193, 193, 191, 191, 191, 189, 189, 189, 187, 187, 187, 185, 185, 185, 183, 183, 183, 181, 181, 181, 179, 179, 179, 177, 177, 177, 175, 175, 175, 173, 173, 173, 171, 171, 171, 169, 169, 169, 167, 167, 167, 165, 165, 165, 163, 163, 163, 161, 161, 161, 159, 159, 159, 157, 157, 157, 155, 155, 155, 153, 153, 153, 151, 151, 151, 149, 149, 149, 147, 147, 147, 145, 145, 145, 143, 143, 143, 141, 141, 141, 139, 139, 139, 137, 137, 137, 135, 135, 135, 133, 133, 133, 131, 131, 131, 129, 129, 129, 126, 126, 126, 124, 124, 124, 122, 122, 122, 120, 120, 120, 118, 118, 118, 116, 116, 116, 114, 114, 114, 112, 112, 112, 110, 110, 110, 108, 108, 108, 106, 106, 106, 104, 104, 104, 102, 102, 102, 100, 100, 100, 98, 98, 98, 96, 96, 96, 94, 94, 94, 92, 92, 92, 90, 90, 90, 88, 88, 88, 86, 86, 86, 84, 84, 84, 82, 82, 82, 80, 80, 80, 78, 78, 78, 76, 76, 76, 74, 74, 74, 72, 72, 72, 70, 70, 70, 68, 68, 68, 66, 66, 66, 64, 64, 64, 62, 62, 62, 60, 60, 60, 58, 58, 58, 56, 56, 56, 54, 54, 54, 52, 52, 52, 50, 50, 50, 48, 48, 48, 46, 46, 46, 44, 44, 44, 42, 42, 42, 40, 40, 40, 38, 38, 38, 36, 36, 36, 34, 34, 34, 32, 32, 32, 30, 30, 30, 28, 28, 28, 26, 26, 26, 24, 24, 24, 22, 22, 22, 20, 20, 20, 18, 18, 18, 16, 16, 16, 14, 14, 14, 12, 12, 12, 10, 10, 10, 8, 8, 8, 6, 6, 6, 4, 4, 4, 2, 2, 2, 0, 0, 0, 0, 0, 9, 2, 0, 16, 4, 0, 24, 6, 0, 31, 8, 0, 38, 10, 0, 45, 12, 0, 53, 14, 0, 60, 17, 0, 67, 19, 0, 74, 21, 0, 82, 23, 0, 89, 25, 0, 96, 27, 0, 103, 29, 0, 111, 31, 0, 118, 36, 0, 120, 41, 0, 121, 46, 0, 122, 51, 0, 123, 56, 0, 124, 61, 0, 125, 66, 0, 126, 71, 0, 127, 76, 1, 128, 81, 1, 129, 86, 1, 130, 91, 1, 131, 96, 1, 132, 101, 1, 133, 106, 1, 134, 111, 1, 135, 116, 1, 136, 121, 1, 136, 125, 2, 137, 130, 2, 137, 135, 3, 137, 139, 3, 138, 144, 3, 138, 149, 4, 138, 153, 4, 139, 158, 5, 139, 163, 5, 139, 167, 5, 140, 172, 6, 140, 177, 6, 140, 181, 7, 141, 186, 7, 141, 189, 10, 137, 191, 13, 132, 194, 16, 127, 196, 19, 121, 198, 22, 116, 200, 25, 111, 203, 28, 106, 205, 31, 101, 207, 34, 95, 209, 37, 90, 212, 40, 85, 214, 43, 80, 216, 46, 75, 218, 49, 69, 221, 52, 64, 223, 55, 59, 224, 57, 49, 225, 60, 47, 226, 64, 44, 227, 67, 42, 228, 71, 39, 229, 74, 37, 230, 78, 34, 231, 81, 32, 231, 85, 29, 232, 88, 27, 233, 92, 24, 234, 95, 22, 235, 99, 19, 236, 102, 17, 237, 106, 14, 238, 109, 12, 239, 112, 12, 240, 116, 12, 240, 119, 12, 241, 123, 12, 241, 127, 12, 242, 130, 12, 242, 134, 12, 243, 138, 12, 243, 141, 13, 244, 145, 13, 244, 149, 13, 245, 152, 13, 245, 156, 13, 246, 160, 13, 246, 163, 13, 247, 167, 13, 247, 171, 13, 248, 175, 14, 248, 178, 15, 249, 182, 16, 249, 185, 18, 250, 189, 19, 250, 192, 20, 251, 196, 21, 251, 199, 22, 252, 203, 23, 252, 206, 24, 253, 210, 25, 253, 213, 27, 254, 217, 28, 254, 220, 29, 255, 224, 30, 255, 227, 39, 255, 229, 53, 255, 231, 67, 255, 233, 81, 255, 234, 95, 255, 236, 109, 255, 238, 123, 255, 240, 137, 255, 242, 151, 255, 244, 165, 255, 246, 179, 255, 248, 193, 255, 249, 207, 255, 251, 221, 255, 253, 235, 255, 255, 24};

void Person::updateImage(unsigned char *data)
{
    QImage rgbImage = QImage(FrameWidth,FrameHeight,QImage::Format_RGB888);
    QVector<unsigned short> rawData = QVector<unsigned short> (FrameWords);
    QVector<unsigned char> result = QVector<unsigned char> (2 * PacketBytes*FrameHeight);

    memcpy(&result[0], data, 39360);

    uint16_t minValue = 65535;
    uint16_t maxValue = 0;
    unsigned char *in = &result[0];
    unsigned short *out = &rawData[0];
    for (int iPacket = 0; iPacket < FrameHeight * 2; ++iPacket) {//!
        in += 4;//first color
        for (int iCol = 0; iCol < PacketWidth; ++iCol) //reads every pixel of the line(one subpacket)
        {
            unsigned short value = in[0];//value wird farbe zugewiesen
            value <<= 8;//8 weil Wort =8 bits, verschiebt um 8 Stellen nach vorne
            value |= in[1];//macht darauf eine 16-bit Farbe
            in += 2;//beginn von n�chster n�chtse Farbe

            if (value > maxValue)
            {
                maxValue = value;
            }

            if (value < minValue)
            {
                minValue = value;
            }

            *(out++) = value;//weist rawdata die Werte zu
        }
    }

    // Map "rawData" to rgb values in "rgbImage" via the colormap
    int diff = maxValue - minValue + 1;
    for (int y = 0; y < FrameHeight; ++y)
    {
        for (int x = 0; x < FrameWidth; ++x)
        {
            int baseValue = rawData[FrameWidth*y + x]; // take input value in [0, 65536)
            int scaledValue = 256*(baseValue - minValue)/diff; // map value to interval [0, 256), and set the pixel to its color value above
            rgbImage.setPixel(x, y, qRgb(colormap[3*scaledValue], colormap[3*scaledValue+1], colormap[3*scaledValue+2]));
        }
    }

    // Update the on-screen image
    QPixmap pixmap = QPixmap::fromImage(rgbImage).scaled(ImageWidth, ImageHeight, Qt::KeepAspectRatio);
    // ... mark up pixmap, if so desired
    IRPicture->setPixmap(pixmap);
}

void Person::updateStatus()
{
    QString txt = Name + colon + Stati[recentStatus];
    Status->setText(txt);
}


void Person::updateMessage()
{
    answer->setText(Answers[recentAnswer]);
}

void Person::updateTempHead()
{
    QString Temp = QString::number(recentTempHead);
    QString txt = Temp + unitTemp;
    TempHead->setText(txt);
}

void Person::updateTempFoot()
{
    QString Temp = QString::number(recentTempFoot);
    QString txt = Temp + unitTemp;
    TempFoot->setText(txt);
}

void Person::updateCOHead()
{
    QString CO = QString::number(recentCOHead);
    QString txt = CO + unitCO;
    COHead->setText(txt);
}

void Person::updateCOFoot()
{
    QString CO = QString::number(recentCOFoot);
    QString txt = CO + unitCO;
    COFoot->setText(txt);
}

void Person::updateTab()
{
    updateMessage();
    updateTempHead();
    updateTempFoot();
    updateCOHead();
    updateCOFoot();
}
