#ifndef HEADQUATER_H
#define HEADQUATER_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>//right class?
#include <QTableView>//right class?

class QTableView;


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
    void updateCOHead(int ID, int recentCO);
    void updateCOFoot(int ID, int recentCO);
    void answerdMessage(int ID, int answer);

private:
    //Status retated
    QTableView *StatusView;

    //different Personaes

};

#endif // HEADQUATER_H
