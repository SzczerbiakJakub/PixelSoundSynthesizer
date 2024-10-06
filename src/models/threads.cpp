#include "threads.h"


KeyPressThread::KeyPressThread(bool* keyPressed, std::vector<int>* keysPressedStack) :
    keyPressed(keyPressed), keysPressedStack(keysPressedStack) {
    currentSound = SoundEffects::soundB4;
    audioStream = new AudioStream();
    displayAudio = false;
    keyPressTimer = new QElapsedTimer();
    //bufferCopy = new std::queue<std::pair<AudioSource*, int>>;

}

KeyPressThread::~KeyPressThread() {

}


void KeyPressThread::displayRecordedAudio(int index) {
    std::vector<std::queue<std::pair<AudioSource*, int>>*> records = *NoteData::recordedTracks;
    if (!records.empty())
    {
        //std::queue<std::pair<AudioSource*, int>> bufferCopy = *records[index-1];
        bufferCopy = *records[index - 1];

        displayAudio = true;
        /*while (!bufferCopy.empty()) {
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

        displayAudio = false;*/
    }
}

void KeyPressThread::displayAudioForCertainTime(int ms) {
    QElapsedTimer* timer = new QElapsedTimer();
    timer->start();

    while (timer->elapsed() < ms)
        //continue;
        if (currentSound != nullptr)
            audioStream->playAudio(currentSound);

    delete timer;
}


void KeyPressThread::run()
{
    while (true)
    {
        if ((!(keysPressedStack->empty())) and currentSound != nullptr)
        {
            while (!(keysPressedStack->empty()) or displayAudio)
            {
                audioStream->playAudio(currentSound);
            }
        }
        else if (displayAudio) {
            
            emit startPlayingRecordSignal();
            
            while (!bufferCopy.empty()) {
                if (bufferCopy.front().first != nullptr)
                    setCurrentSound(bufferCopy.front().first);
                else
                    setCurrentSound(nullptr);

                displayAudioForCertainTime(bufferCopy.front().second);
                bufferCopy.pop();
            }
            displayAudio = false;

            emit stopPlayingRecordSignal();
        }
        QThread::sleep(0.02);
    }
}


StaveWidgetRenderThread::StaveWidgetRenderThread(bool* recording, bool* playing)
    : recording(recording), playing(playing) {
    renderTimer = new QTimer();
}


StaveWidgetRenderThread::~StaveWidgetRenderThread() {
    delete renderTimer;
}


void StaveWidgetRenderThread::run() {

    while (*recording or *playing)
    {
        renderTimer->start(RECORD_STATE_RENDER_TIME);
    }
}
