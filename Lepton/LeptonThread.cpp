#include "LeptonThread.h"

#include <iostream>
#include <QString>
#include <QTextStream>

LeptonThread::LeptonThread()//constructer
    : QThread()
    , segmentRAW(PacketBytes*SegmentPackets)//holds packets until it is nown to which segment they belong
    , result(2 * PacketBytes*FrameHeight)//size of vector
    , rawData(FrameWords) { }//size of Vector
//ugly inhertance
LeptonThread::~LeptonThread() { }

#if HAVE_LEPTON
const char *LeptonThread::device = "/dev/spidev0.1"; // Change to 0.0 if necessary!
unsigned char LeptonThread::mode = 0, LeptonThread::bits = 8;
unsigned int LeptonThread::speed = 16000000;//12367872;//2770944;//12717500;//16000000;
unsigned short LeptonThread::delay = 0;
QVector<unsigned char> LeptonThread::tx(LeptonThread::PacketBytes, 0);//tells how long the vector is? %

bool LeptonThread::initLepton() {
    fd = open(device, O_RDWR);
    if (fd < 0)
        qDebug() << "Can't open device";
    else if (-1 == ioctl(fd, SPI_IOC_WR_MODE, &mode))
        qDebug() << "Can't set SPI mode";
    else if (-1 == ioctl(fd, SPI_IOC_RD_MODE, &mode))
        qDebug() << "Can't get SPI mode";
    else if (-1 == ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits))
        qDebug() << "Can't set bits per word";
    else if (-1 == ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits))
        qDebug() << "Can't get bits per word";
    else if (-1 == ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed))
        qDebug() << "Can't set max speed";
    else if (-1 == ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed))
        qDebug() << "Can't get max speed";
    else
        return true;
    return false;
}
#else
static int counter = 0;
#endif

int LeptonThread::getPacket(int iPacket, unsigned char *packetData) {
#if HAVE_LEPTON
    _tr.rx_buf = (unsigned long) packetData;//weist rx_buf einin pointer zu; l�sst werte in restult schreiben
    return ioctl(fd, SPI_IOC_MESSAGE(1), &_tr);//reads the value of the packet
#else
    packetData[0] = 0;
    packetData[1] = iPacket;
    for (int i = 4; i < PacketBytes; i += 2)
        *(short *)(packetData+i) = ((iPacket+counter) % 20) + ((i/2-2) % 26);
    return 1;
#endif
}

void LeptonThread::run() {
#if HAVE_LEPTON
    if (!initLepton()) return;

    usleep(250000);

	//SPI-Bus related
    _tr.tx_buf = (unsigned long) &tx[0];//poniter towrads the buffer?
    _tr.len = PacketBytes;//leght of rx_buf and tx_buf in bytes %
    _tr.delay_usecs = delay;
    _tr.speed_hz = speed;//clockspeed for the spi-bus
    _tr.bits_per_word = bits;//size of the word
#endif

    int resets = 0; // Number of times we've reset the 0...59 loop for packets
    int errors = 0; // Number of error-packets received
	while (true)
	{
		int iPacket;
		int iSegment = 0;
		for (iPacket = 0; iPacket < 2 * SegmentHeight; )
		{
			unsigned char *packet = &segmentRAW[iPacket*PacketBytes];// + (iSegment-1)*PacketBytes*SegmentHeight*2];//changed

			if (getPacket(iPacket, packet) < 1)
			{
				qDebug() << "Error transferring SPI packet";
				return;
			}

			int packetNumber;
			if ((packet[0] & 0xf) == 0xf)// & Bitweise und Verknüpfung ->packet has to have an value %
			{
				packetNumber = -1;
			}
			else
			{
				packetNumber = packet[1];
			}
#if DEBUG_LEPTON
			if (sequence.empty() || sequence.back().first != packetNumber)
				sequence.push_back(std::make_pair(packetNumber, 1));
			else
				++sequence.back().second;
#endif
			if (packetNumber == 20) // readout of the segment number, because of historical reasons this has to happen in two lines
			{//who is able to read has advanteges! 20 menas 20 and not 19!
				iSegment = packet[0];
				iSegment >>= 4;
			}


			if (packetNumber == -1)
			{
				usleep(1000);
				if (++errors > 300)
				{
					break;
				}
				continue;
			}

			if (packetNumber != iPacket)
			{
				usleep(1000);
				break;
			}

			++iPacket;
		}

		if (iPacket < 2 * SegmentHeight)//wird aktiviert wenn man aus der for-schleife raus springt
		{
			if (++resets >= 750) //timeout solange 750 nicht erreicht wird wird diese Schleife wiederholt
			{
				qDebug() << "Packet reset counter hit 750";
				resets = 0;
				usleep(750000);
			}
			continue;
		}

		if (iSegment != 0)//bringing the segment to the place it belongs to
		{
			for (int i = 0; i < PacketBytes * SegmentPackets; i++)
			{
				result[(iSegment - 1)*PacketBytes*SegmentHeight * 2 + i] = segmentRAW[i];
			}
		}

#if DEBUG_LEPTON
		QString msg;
		QTextStream os(&msg);
		bool chain = false, first = true; int chain0, chain1;
		for (std::list< std::pair<int, int> >::iterator iSeq = sequence.begin(); iSeq != sequence.end(); ++iSeq) {
			if (chain && iSeq->first == chain1 + 1) { ++chain1; continue; }
			if (chain && chain1 != chain0) os << "-" << chain1;
			if (iSeq->first >= 0 && !chain) { chain = true; chain0 = chain1 = iSeq->first; }
			if (first) first = false; else os << " ";
			if (iSeq->first == -1) os << "*"; else os << iSeq->first;
			if (iSeq->second != 1) { os << "^" << iSeq->second; chain = false; }
		}
		if (chain && chain1 != chain0) os << "-" << chain1;
		qDebug() << msg;
		sequence.clear();
		// qDebug() << resets << "resets," << errors << "errors";
#endif

		resets = 0; errors = 0;

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
		emit updateImage(&rawData[0], minValue, maxValue, &result[0]);//signal for the updateImage slot of mainwindow.cpp
		//std::cout << "hier auch nicht" << '\n';
#if !HAVE_LEPTON
		usleep(50000);  // Need to slow things down if no ioctl call!
		counter = (counter + 1) % 520;
#endif
	}
}
