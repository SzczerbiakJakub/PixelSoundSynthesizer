#include "threads.h"


KeyPressThread::KeyPressThread(bool* keyPressed) : keyPressed(keyPressed) { 
    currentSound = SoundEffects::soundB4;
    audioStream = new AudioStream();
    displayAudio = false;

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

        if ((*keyPressed || displayAudio) and currentSound != nullptr)
        {
            while ((*keyPressed || displayAudio))
                audioStream->playAudio(currentSound);
        }

        QThread::sleep(0.02);
    }
}