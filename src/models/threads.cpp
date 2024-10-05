#include "threads.h"


KeyPressThread::KeyPressThread(bool* keyPressed, std::vector<int>* keysPressedStack) :
    keyPressed(keyPressed), keysPressedStack(keysPressedStack) {
    currentSound = SoundEffects::soundB4;
    audioStream = new AudioStream();
    displayAudio = false;
    keyPressTimer = new QElapsedTimer();

}

KeyPressThread::~KeyPressThread() {

}


void KeyPressThread::displayRecordedAudio(int index) {
    std::vector<std::queue<std::pair<AudioSource*, int>>*> records = *NoteData::recordedTracks;
    if (!records.empty())
    {
        std::queue<std::pair<AudioSource*, int>> bufferCopy = *records[index-1];

        displayAudio = true;
        while (!bufferCopy.empty()) {
            if (bufferCopy.front().first != nullptr)
            {
                setCurrentSound(bufferCopy.front().first);
                displayAudio = true;
            }
            else
                displayAudio = false;

            displayAudioForCertainTime(bufferCopy.front().second);
            bufferCopy.pop();
        }

        displayAudio = false;
    }
}

void KeyPressThread::displayAudioForCertainTime(int ms) {
    QElapsedTimer* timer = new QElapsedTimer();
    timer->start();

    while (timer->elapsed() < ms)
        continue;

    delete timer;
}


void KeyPressThread::run()
{
    while (true)
    {
        if ((!(keysPressedStack->empty()) or displayAudio) and currentSound != nullptr)
        {
            while (!(keysPressedStack->empty()) or displayAudio)
            {
                audioStream->playAudio(currentSound);
            }
        }
        QThread::sleep(0.02);
    }
}