#include "audiosendthread.h"


audiosendthread::audiosendthread(QObject *parent)
    : QThread(parent)
{
    udpSocket = new QUdpSocket(this);
    udpSocket -> bind(QHostAddress::Any, 10005);
    destaddr.setAddress("127.0.0.1");
}
audiosendthread::~audiosendthread(){
    delete udpSocket;
    delete input;
    delete inputDevice;
}

void audiosendthread::setaudioformat(int samplerate, int channelcount, int samplesize){
    format.setSampleRate(samplerate);
    format.setChannelCount(channelcount);
    format.setSampleSize(samplesize);
    format.setCodec("audio/pcm");
    format.setSampleType(QAudioFormat::SignedInt);
    format.setByteOrder(QAudioFormat::LittleEndian);

    input = new QAudioInput(format, this);

}

void audiosendthread::mystart(){
    qDebug()<<"audio begins to send";
    inputDevice = input->start();
    connect(inputDevice,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}

void audiosendthread::mystop(){
    qDebug()<<"audio ends!";
    input->stop();
}

void audiosendthread::onReadyRead(){
    video vp;
    memset(&vp.data,0,sizeof(vp));

    // read audio from input device
    vp.lens = inputDevice -> read(vp.data,960);
    int num = udpSocket -> writeDatagram((const char*)&vp, sizeof(vp),destaddr,10004);
    qDebug()<<num;
}
