#ifndef LEPTONTHREAD
#define LEPTONTHREAD

#define HAVE_LEPTON true
#define DEBUG_LEPTON false
#define FREQUENZY false

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>

#include <mutex>

#if HAVE_LEPTON
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#endif

#if DEBUG_LEPTON
#include <list>
#include <utility>
#endif

#include <QThread>
#include <QDebug>
#include <QVector>

class LeptonThread : public QThread {
    Q_OBJECT

    QVector<unsigned char> segmentRAW;
    QVector<unsigned char> result;
    QVector<unsigned short> rawData;

#if HAVE_LEPTON
    static const char *device;
    static unsigned char mode, bits;
    static unsigned int speed;
    static unsigned short delay;
    static QVector<unsigned char> tx;

    int fd;
    struct spi_ioc_transfer _tr;//Bussystem source of the packets
	
#endif

	//bool Array der f�r jedes Segment angibt 
	bool SegmentUpdated[4];

	int packetf = 0;
	int neuBildf = 0;

#if DEBUG_LEPTON
    std::list< std::pair<int, int> > sequence; // ...of packet #'s received from Lepton, for troubleshooting
#endif

	bool SegmentCorrect;
    bool initLepton();
    int getPacket(int iRow, unsigned char *packetData);

public:
	enum {
		FrameWidth = 160,
		FrameHeight = 120,
		PacketWidth = 80,
    PacketWords = PacketWidth + 2,
		RowPacketWords = 2*PacketWords,
    PacketBytes = 2*PacketWords,
    FrameWords = FrameWidth*FrameHeight,
		SegmentHeight = FrameHeight/4,
    SegmentPackets = 60,
    };

    std::mutex *abc;
    LeptonThread(std::mutex *MUTEX);
    ~LeptonThread();

    void run();//loop
	void frequenzie();//seperate thread that counts the pictures per second and prints that

signals:
    void updateImage(unsigned short *, int, int, unsigned char*);
};

#endif
