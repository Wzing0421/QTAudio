#ifndef AUDIOSENDTHREAD_H
#define AUDIOSENDTHREAD_H
//这是发送线程

#include <QObject>
#include <QThread>
#include <QDebug>

#include <QAudio>
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioOutput>
#include <QIODevice>

#include <QtNetwork/QUdpSocket>
#include <QHostAddress>

class audiosendthread : public QThread
{
    Q_OBJECT
public:
    explicit audiosendthread(QObject *parent = nullptr);
    ~audiosendthread();

    QUdpSocket *udpSocket;
    QHostAddress destaddr;

    QAudioInput *input;
    QIODevice *inputDevice;
    QAudioFormat format;

    struct video{
        int lens;
        char data[960];
    };

    void setaudioformat(int samplerate, int channelcount, int samplesize);
    void mystart();
    void mystop();

public slots:
    void onReadyRead();

};

#endif // AUDIOSENDTHREAD_H
