#ifndef HEADGUI_H
#define HEADGUI_H

#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QResizeEvent>
#include <QPainter>

#include <../Lepton/LeptonThread.h>
//#include <../Netzwerk/client/client.h>
//#include <../Netzwerk/User/User.h>

class QLabel;
class QPixmap;
class QGridLayout;

class HeadGUI : public QMainWindow
{
    Q_OBJECT

public:
    HeadGUI(QWidget *parent = 0);
    ~HeadGUI();

public slots:
    void updateImage(unsigned short *, int, int);

signals:
    void changingLightSignal();
    void certifyPersonaeSignal();
    void upSignal();
    void downSignal();
    void rightSignal();
    void leftSignal();
    void backSignal();
    void certifySignal();
    void coosingStatusSignal();
    //Singals to headquater
    void newStatusSignal(int ID,int vertical);
    void answeredMessage(int ID,int vertical);
    void confirmedID(int ID);
    void updatedTempHeadSignal(int ID, int recentTemp);
    void updatedTempFootSignal(int ID, int recentTemp);
    void updatedCOHeadSignal(int ID, int recentCO);
    void updatedCOFootSignal(int ID, int recentCO);
    //from where does the signal come?
    void updateBraceletSignal(int valueUp,int valueDown,int valueRight,int valueLeft,int valueBack,int valueCertify);
    void updateTempHeadSignal(int recentTemp);
    void updateTempFootSignal(int recentTemp);
    void updateCOHeadSignal(int recentCO);
    void updateCOFootSignal(int recentCO);
    void messageRecivedSignal(QString sendMessage);// from headquater

private slots:
    void certifyPersonae();
    void up();
    void down();
    void right();
    void left();
    void back();
    void certify();
    void updateBracelet(int valueUp,int valueDown,int valueRight,int valueLeft,int valueBack,int valueCertify);
    void updateTempHead(int recentTemp);
    void updateTempFoot(int recentTemp);
    void updateCOHead(int recentCOHead);
    void updateCOFoot(int recentCOFoot);
    void coosingStatus();
    void messageRecived(QString sendMessage);
    void changingLight();

private:
    //other
    QGridLayout *layout;
    QWidget *mainWidget;
    void createConnections();
    void defauftValues();
    bool lightOn;

    //navigation/communication
    void createCommunication();
    QLabel *Status;
    QLabel *Messages;
    int vertical;
    int horizontal;
    bool emergencyPossible;
    bool SendEmergency;
    bool otherSignals;
    int NumberDiffMenues = 2;
    bool answerPossible;
    int NumberDiffValues[4] = {4,2,1,5};
    QString Stati[5]={"Status1","Status2","Status3","Status4","emergency"};
    QString recivedMessage;
    QString messageAnswers[3] = {" ","angenommen","nicht verfügbar"};
    int recentStatus;
    int recentAnswer;

    //biometric data
    void createBiometric();
    QLabel *Personae;
    QLabel *TempHead;
    QLabel *TempFoot;
    QLabel *Light;
    QString unitTemp =" °C";
    QLabel *COHead;
    QLabel *COFoot;
    QString unitCO = " ppm";
    QString lightSwitch[2] = {"Off","On"};
    int ID;
    QString Name [5]= {" ","Aron Haselhoff","Timon Gronotte","Vicky Bietenbeck","Beke Pierick"};

    //for Camera
    void createIRPicture();
    QLabel *IRPicture;
    QVector<unsigned short> rawData;
    QImage rgbImage;
    enum { ImageWidth = 320, ImageHeight = 240 };
    LeptonThread *thread;//%
    unsigned short rawMin, rawMax;

};

#endif // HEADGUI_H
