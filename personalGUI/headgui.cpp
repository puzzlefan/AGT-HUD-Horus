#include "headgui.h"

//#include "LeptonThread.h"
#include <iostream>

#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QResizeEvent>

HeadGUI::HeadGUI(QWidget *parent)
    : QMainWindow(parent)

{
    mainWidget = new QWidget();
    layout = new QGridLayout;

    mainWidget->setLayout(layout);
    resize(1400,500);

    createConnections();

    createIRPicture();
    createBiometric();

    setWindowTitle("PersonalGUI Helmet");

    emit certifyPersonaeSignal();
}

void HeadGUI::createBiometric()
{
    Personae = new QLabel();
    layout->addWidget(Personae,0,2,1,2);


    TempHead = new QLabel();
    layout->addWidget(TempHead,1,2,1,1);

    TempFoot = new QLabel();
    layout->addWidget(TempFoot,1,3,1,1);

    COHead = new QLabel();
    layout->addWidget(COHead,2,2,1,1);

    COFoot = new Label();
    layout->addWidget(COFoot,2,3,1,1);
    std::cout <<" created Biometric"<<std::endl;
}

void HeadGUI::createIRPicture()//: rawData(LeptonThread::FrameWords),
    //rgbImage(LeptonThread::FrameWidth, LeptonThread::FrameHeight, QImage::Format_RGB888)
{
    IRPicture = new QLabel();
    layout->addWidget(IRPicture, 0, 0, 3, 2, Qt::AlignCenter);

    QPixmap filler(ImageWidth, ImageHeight);
    filler.fill(Qt::red);
    IRPicture->setPixmap(filler);
    std::cout <<"created Image"<<std::endl;
/*
    thread = new LeptonThread();
    connect(thread, SIGNAL(updateImage(unsigned short *,int,int)), this, SLOT(updateImage(unsigned short *, int,int)));

    thread->start();*/
}

//Color for IRCamera
const int colormap[] = {255, 255, 255, 253, 253, 253, 251, 251, 251, 249, 249, 249, 247, 247, 247, 245, 245, 245, 243, 243, 243, 241, 241, 241, 239, 239, 239, 237, 237, 237, 235, 235, 235, 233, 233, 233, 231, 231, 231, 229, 229, 229, 227, 227, 227, 225, 225, 225, 223, 223, 223, 221, 221, 221, 219, 219, 219, 217, 217, 217, 215, 215, 215, 213, 213, 213, 211, 211, 211, 209, 209, 209, 207, 207, 207, 205, 205, 205, 203, 203, 203, 201, 201, 201, 199, 199, 199, 197, 197, 197, 195, 195, 195, 193, 193, 193, 191, 191, 191, 189, 189, 189, 187, 187, 187, 185, 185, 185, 183, 183, 183, 181, 181, 181, 179, 179, 179, 177, 177, 177, 175, 175, 175, 173, 173, 173, 171, 171, 171, 169, 169, 169, 167, 167, 167, 165, 165, 165, 163, 163, 163, 161, 161, 161, 159, 159, 159, 157, 157, 157, 155, 155, 155, 153, 153, 153, 151, 151, 151, 149, 149, 149, 147, 147, 147, 145, 145, 145, 143, 143, 143, 141, 141, 141, 139, 139, 139, 137, 137, 137, 135, 135, 135, 133, 133, 133, 131, 131, 131, 129, 129, 129, 126, 126, 126, 124, 124, 124, 122, 122, 122, 120, 120, 120, 118, 118, 118, 116, 116, 116, 114, 114, 114, 112, 112, 112, 110, 110, 110, 108, 108, 108, 106, 106, 106, 104, 104, 104, 102, 102, 102, 100, 100, 100, 98, 98, 98, 96, 96, 96, 94, 94, 94, 92, 92, 92, 90, 90, 90, 88, 88, 88, 86, 86, 86, 84, 84, 84, 82, 82, 82, 80, 80, 80, 78, 78, 78, 76, 76, 76, 74, 74, 74, 72, 72, 72, 70, 70, 70, 68, 68, 68, 66, 66, 66, 64, 64, 64, 62, 62, 62, 60, 60, 60, 58, 58, 58, 56, 56, 56, 54, 54, 54, 52, 52, 52, 50, 50, 50, 48, 48, 48, 46, 46, 46, 44, 44, 44, 42, 42, 42, 40, 40, 40, 38, 38, 38, 36, 36, 36, 34, 34, 34, 32, 32, 32, 30, 30, 30, 28, 28, 28, 26, 26, 26, 24, 24, 24, 22, 22, 22, 20, 20, 20, 18, 18, 18, 16, 16, 16, 14, 14, 14, 12, 12, 12, 10, 10, 10, 8, 8, 8, 6, 6, 6, 4, 4, 4, 2, 2, 2, 0, 0, 0, 0, 0, 9, 2, 0, 16, 4, 0, 24, 6, 0, 31, 8, 0, 38, 10, 0, 45, 12, 0, 53, 14, 0, 60, 17, 0, 67, 19, 0, 74, 21, 0, 82, 23, 0, 89, 25, 0, 96, 27, 0, 103, 29, 0, 111, 31, 0, 118, 36, 0, 120, 41, 0, 121, 46, 0, 122, 51, 0, 123, 56, 0, 124, 61, 0, 125, 66, 0, 126, 71, 0, 127, 76, 1, 128, 81, 1, 129, 86, 1, 130, 91, 1, 131, 96, 1, 132, 101, 1, 133, 106, 1, 134, 111, 1, 135, 116, 1, 136, 121, 1, 136, 125, 2, 137, 130, 2, 137, 135, 3, 137, 139, 3, 138, 144, 3, 138, 149, 4, 138, 153, 4, 139, 158, 5, 139, 163, 5, 139, 167, 5, 140, 172, 6, 140, 177, 6, 140, 181, 7, 141, 186, 7, 141, 189, 10, 137, 191, 13, 132, 194, 16, 127, 196, 19, 121, 198, 22, 116, 200, 25, 111, 203, 28, 106, 205, 31, 101, 207, 34, 95, 209, 37, 90, 212, 40, 85, 214, 43, 80, 216, 46, 75, 218, 49, 69, 221, 52, 64, 223, 55, 59, 224, 57, 49, 225, 60, 47, 226, 64, 44, 227, 67, 42, 228, 71, 39, 229, 74, 37, 230, 78, 34, 231, 81, 32, 231, 85, 29, 232, 88, 27, 233, 92, 24, 234, 95, 22, 235, 99, 19, 236, 102, 17, 237, 106, 14, 238, 109, 12, 239, 112, 12, 240, 116, 12, 240, 119, 12, 241, 123, 12, 241, 127, 12, 242, 130, 12, 242, 134, 12, 243, 138, 12, 243, 141, 13, 244, 145, 13, 244, 149, 13, 245, 152, 13, 245, 156, 13, 246, 160, 13, 246, 163, 13, 247, 167, 13, 247, 171, 13, 248, 175, 14, 248, 178, 15, 249, 182, 16, 249, 185, 18, 250, 189, 19, 250, 192, 20, 251, 196, 21, 251, 199, 22, 252, 203, 23, 252, 206, 24, 253, 210, 25, 253, 213, 27, 254, 217, 28, 254, 220, 29, 255, 224, 30, 255, 227, 39, 255, 229, 53, 255, 231, 67, 255, 233, 81, 255, 234, 95, 255, 236, 109, 255, 238, 123, 255, 240, 137, 255, 242, 151, 255, 244, 165, 255, 246, 179, 255, 248, 193, 255, 249, 207, 255, 251, 221, 255, 253, 235, 255, 255, 24};
/*
void HeadGUI::updateImage(unsigned short *data, int minValue, int maxValue)
{
    // Record the raw data and min/max values
    memcpy(&rawData[0], data, 2*LeptonThread::FrameWords);//memcpy(wohin gespeichert,woher daten, Nummer der Bytes die kopiert werden)
    rawMin = minValue; rawMax = maxValue;

    // Map "rawData" to rgb values in "rgbImage" via the colormap
    int diff = maxValue - minValue + 1;
    for (int y = 0; y < LeptonThread::FrameHeight; ++y) {
        for (int x = 0; x < LeptonThread::FrameWidth; ++x) {
            int baseValue = rawData[LeptonThread::FrameWidth*y + x]; // take input value in [0, 65536)
            int scaledValue = 256*(baseValue - minValue)/diff; // map value to interval [0, 256), and set the pixel to its color value above
            rgbImage.setPixel(x, y, qRgb(colormap[3*scaledValue], colormap[3*scaledValue+1], colormap[3*scaledValue+2]));
        }
    }

    // Update the on-screen image
    QPixmap pixmap = QPixmap::fromImage(rgbImage).scaled(ImageWidth, ImageHeight, Qt::KeepAspectRatio);
    QPainter painter(&pixmap);
    // ... mark up pixmap, if so desired
    IRPicture->setPixmap(pixmap);
}*/

void HeadGUI::createConnections()
{
    connect(this,SIGNAL(certifyPersonaeSignal()),this,SLOT(certifyPersonae()));
    connect(this,SIGNAL(upSignal()),this,SLOT(up()));
    connect(this,SIGNAL(downSignal()),this,SLOT(down()));
    connect(this,SIGNAL(rightSignal()),this,SLOT(right()));
    connect(this,SIGNAL(leftSignal()),this,SLOT(left()));
    connect(this,SIGNAL(backSignal()),this,SLOT(back()));
    connect(this,SIGNAL(certifySignal()),this,SLOT(certify()));
}

void HeadGUI::certifyPersonae()
{
    Personae->setText("Hello World");
}

void HeadGUI::up()
{
    //vertical -- if <1
}

void HeadGUI::down()
{
    //vertical ++
}

void HeadGUI::right()
{
    //horizontal ++
}

void HeadGUI::left()
{
    //horizontal --
}

void HeadGUI::back()
{
    //if first time horizontal and vertical =1, second time Mesagebox: Emergency, sending Emergency
}

void HeadGUI::certify()
{
    //sending whatever
}

HeadGUI::~HeadGUI()
{

}

Label::Label():QLabel(parent)
{
    setText("Hello World");
}
