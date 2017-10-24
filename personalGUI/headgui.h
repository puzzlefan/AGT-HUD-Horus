#ifndef HEADGUI_H
#define HEADGUI_H

#include <QMainWindow>
#include <QLabel>
#include <LeptonThread.h>

class HeadGUI : public QMainWindow
{
    Q_OBJECT

public:
    HeadGUI(QWidget *parent = 0);
    ~HeadGUI();

public slots:
    void updateImage(unsigned short *, int, int);

signals:
    void upSignal();
    void downSignal();
    void rightSignal();
    void leftSignal();
    void backSignal();
    void certifySignal();

private slots:
    void up();
    void down();
    void right();
    void left();
    void back();
    void certify();

private:
    int vertical;
    int horizontal;
    int emergency;

    //for Camera
    QLabel *IRPicture;
    QVector<unsigned short> rawData;
    QImage rgbImage;
    enum { ImageWidth = 320, ImageHeight = 240 };
    LeptonThread *thread;//%
    unsigned short rawMin, rawMax;

};

#endif // HEADGUI_H
