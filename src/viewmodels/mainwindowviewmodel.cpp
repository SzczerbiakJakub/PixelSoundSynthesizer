#include "mainwindowviewmodel.h"
#include <QDebug>



MainWindowViewModel::MainWindowViewModel(QObject* parent) : QObject(parent) {
    keyPressed = false;
    keysPressed = new std::vector<int>;
    keyPressThread = new KeyPressThread(&keyPressed, keysPressed);
    noSoundTimer = new QElapsedTimer();
    audioStream = new AudioStream();
	keyPressThread->start();
	noSoundTimer->start();

    QObject::connect(keyPressThread, &KeyPressThread::emitCreateNewNoteSignal,
        this, &MainWindowViewModel::emitCreateNewNoteSignal);
}


MainWindowViewModel::~MainWindowViewModel() {
    delete keyPressTimer;
    delete noSoundTimer;
    delete keysPressed;
    keyPressThread->terminate();
    delete audioStream;
    delete keyPressThread;
};


void MainWindowViewModel::keyPress(int keyID) {

    if (!KeyboardData::isKeyUsed(keyID))
        return;

    if (KeyboardData::isFunctionalKeyPressed(keyID))
        return;


    if (NoteData::recordingAudio)
    {
        int noSoundDuration = noSoundTimer->elapsed();
        if (!NoteData::recordedAudioBuffer->empty())
            NoteData::recordedAudioBuffer->push(std::pair<AudioSource*, int>(nullptr, noSoundDuration));
    }

    if (!keysPressed->empty())
    {
        int duration = keyPressTimer->elapsed(), beats = (int)(duration * 4 / 1000);

        if (NoteData::recordingAudio)
            NoteData::recordedAudioBuffer->push(std::pair<AudioSource*, int>(NoteData::getSound(keysPressed->back()), duration));

        emit emitCreateNewNoteSignal(keysPressed->back(), beats);
        keyPressTimer->restart();
    }

    keysPressed->push_back(keyID);
    keyPressThread->setCurrentSound(KeyboardData::getAudio(keysPressed->back()));

    emit visualiseKeyPressSignal(keyID);

    keyPressTimer->restart();
    keyPressed = true;
}


void MainWindowViewModel::keyRelease(int keyID) {

    if (keyID == Qt::Key_Space)
    {
        return;
    }
    else if (keyID == Qt::Key_Escape)
    {
        emit emitClearStaveSignal();
        return;
    }

    if (!KeyboardData::isKeyUsed(keyID))
    {
        if (KeyboardData::changeSoundKeyValue)
        {
            emit emitChangeSoundKeyPairSignal(keyID);
        }
        return;
    }

    if (keyID == Qt::Key_Up)
    {
        emit emitPrevOptionSignal();
        return;
    }
    else if (keyID == Qt::Key_Down)
    {
        emit emitNextOptionSignal();
        return;
    }
    else if (keyID == Qt::Key_Left)
    {
        emit emitLeftRelativeOptionSignal();
        return;
    }
    else if (keyID == Qt::Key_Right)
    {
        emit emitRightRelativeOptionSignal();
        return;
    }

    else if (keyID == Qt::Key_Return)
    {
        emit emitSelectOptionSignal();
        return;
    }


    int duration = keyPressTimer->elapsed(), beats = (int)(duration * 4 / 1000);

    if (NoteData::recordingAudio)
        NoteData::recordedAudioBuffer->push(std::pair<AudioSource*, int>(NoteData::getSound(keysPressed->back()), duration));

    if (keyPressed && keysPressed->empty())
    {
        keyPressed = false;
    }

    emit emitCreateNewNoteSignal(keysPressed->back(), beats);

    if (!keysPressed->empty())
    {
        keysPressed->erase(std::remove(keysPressed->begin(), keysPressed->end(), keyID), keysPressed->end());
        if (!keysPressed->empty())
            keyPressThread->setCurrentSound(KeyboardData::getAudio(keysPressed->back()));
        else
            keyPressThread->setCurrentSound(nullptr);

        keyPressTimer->restart();
    }

    emit visualiseKeyReleaseSignal(keyID);

    noSoundTimer->restart();
}


void MainWindowViewModel::displayRecordedAudio(int option) {
    keyPressThread->displayRecordedAudio(option);
}