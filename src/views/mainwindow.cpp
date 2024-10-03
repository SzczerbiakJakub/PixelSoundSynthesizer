#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), centralWidget(new QWidget(this)), keyboardWidget(nullptr)
{
    buildUi();
    setFixedSize(1536, 800);
    keyPressThread->start();
    noSoundTimer->start();

}

MainWindow::~MainWindow()
{
    delete audioStream;
    delete keyboardWidget;
    delete staveWidget;
    delete menuWidget;
    delete centralWidget;
    delete keyPressTimer;
    delete noSoundTimer;
    delete keysPressed;
    keyPressThread->terminate();
    delete keyPressThread;
}


void MainWindow::buildUi()
{
    QHBoxLayout* centralWidgetLayout = new QHBoxLayout(centralWidget);
    centralWidgetLayout->setSpacing(0);
    centralWidgetLayout->setContentsMargins(0, 0, 0, 0);

    QWidget * leftWidget = new QLabel(centralWidget), *leftBottomWidget = new QLabel(leftWidget);
    QVBoxLayout* leftWidgetLayout = new QVBoxLayout(leftWidget);
    QHBoxLayout* leftBottomWidgetLayout = new QHBoxLayout(leftBottomWidget);

    leftBottomWidgetLayout->setSpacing(0);
    leftBottomWidgetLayout->setContentsMargins(0, 0, 0, 0);

    leftWidgetLayout->setSpacing(0);
    leftWidgetLayout->setContentsMargins(0, 0, 0, 0);

    leftBottomWidget->setFixedSize(1078, 470);
    leftWidget->setFixedSize(1078, 770);

    
    staveWidget = new StaveWidget(leftWidget);
    keyboardWidget = new KeyboardWidget(leftBottomWidget);
    menuWidget = new MenuWidget(this);
    
    leftBottomWidgetLayout->addWidget(keyboardWidget, Qt::AlignHCenter);
    leftWidgetLayout->addWidget(staveWidget, Qt::AlignTop);
    leftWidgetLayout->addWidget(leftBottomWidget, Qt::AlignTop);
    centralWidgetLayout->addWidget(leftWidget);
    centralWidgetLayout->addWidget(menuWidget);

    setCentralWidget(centralWidget);

}


void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (!KeyboardData::isKeyUsed(event->key()))
        return;

    if (KeyboardData::isFunctionalKeyPressed(event->key()))
        return;

    if (event->isAutoRepeat())
        return;

    if (NoteData::recordingAudio)
    {
        int noSoundDuration = noSoundTimer->elapsed();
        if (!NoteData::recordedAudioBuffer->empty())
            NoteData::recordedAudioBuffer->push(std::pair<AudioSource*, int>(nullptr, noSoundDuration));
    }

    keysPressed->push(event->key());
    keyPressThread->setCurrentSound(KeyboardData::getAudio(keysPressed->top()));

    KeyWidget* keyWidget = keyboardWidget->getKeyWidget(event->key());
    keyWidget->highlightPressedKey();

    keyPressTimer->restart();
    keyPressed = true;
}



void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (!KeyboardData::isKeyUsed(event->key()))
    {
        if (KeyboardData::changeSoundKeyValue)
        {
            menuWidget->changeSoundKeyPair(event->key());
        }
        return;
    }

    if (event->key() == Qt::Key_Up)
    {
        menuWidget->prevOption();
        return;
    }
    else if (event->key() == Qt::Key_Down)
    {
        menuWidget->nextOption();
        return;
    }
    else if (event->key() == Qt::Key_Left)
    {
        menuWidget->leftRelativeOption();
        return;
    }
    else if (event->key() == Qt::Key_Right)
    {
        menuWidget->rightRelativeOption();
        return;
    }

    else if (event->key() == Qt::Key_Return)
    {
        if (menuWidget->getCurrentLayout() == 2 and menuWidget->getCurrentOption() != 0)
        {
            if (menuWidget->getCurrentOption() <= NoteData::recordedTracks->size())
                keyPressThread->displayRecordedAudio(menuWidget->getCurrentOption());
        }
        else
            menuWidget->selectOption();
        return;
    }

    if (event->isAutoRepeat())
        return;

    if (event->key() == Qt::Key_Space)
    {
        return;
    }
    else if (event->key() == Qt::Key_Escape)
    {
        staveWidget->clearStave();
        return;
    }

    int duration = keyPressTimer->elapsed(), beats = (int)(duration * 4 / 1000);

    if (NoteData::recordingAudio)
        NoteData::recordedAudioBuffer->push(std::pair<AudioSource*, int>(NoteData::getSound(keysPressed->top()), duration));

    if (keyPressed && keysPressed->empty())
    {
        keyPressed = false;
    }
    else
    {
        keyPressThread->setCurrentSound(KeyboardData::getAudio(keysPressed->top()));
        keyPressed = false;
    }


    staveWidget->newNote(KeyboardData::getAudio(keysPressed->top()), beats);

    if (!keysPressed->empty())
    {
        keysPressed->pop();
    }

    KeyWidget* keyWidget = keyboardWidget->getKeyWidget(event->key());
    keyWidget->unhighlightPressedKey();

    noSoundTimer->restart();
};