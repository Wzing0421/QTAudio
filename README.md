how to use these files in mainwindow.cpp

in "mainwindow.h", define two objects:

AudioPlayThread aud;
audiosendthread audsend;

in mainwindow.cpp:

// to start the audio recieve thread:
aud.setCurrenSampletInfo(8000,16,1);
aud.setCurrentVolume(100);
aud.start();

//to start the audio send thread:
audsend.setaudioformat(8000,1,16);
audsend.mystart();

