#pragma once

#include <QObject>
#include <stack>
#include <vector>
#include "soundeffect.h"
#include "threads.h"



class MainWindowViewModel : public QObject
{
	Q_OBJECT

public:
	MainWindowViewModel(QObject* parent=nullptr);
	~MainWindowViewModel();

private:

    /// <summary>
    /// Wskaźnik na obiekt AudioStream odpowiedzialny za streaming dźwięku w programie.
    /// </summary>
    AudioStream* audioStream;

    /// <summary>
    /// Wskaźnik na timer mierzący czas wciśnięcia przycisku.
    /// </summary>
    QElapsedTimer* keyPressTimer = new QElapsedTimer;

    /// <summary>
    /// Wskaźnik na timer mierzący czas braku dźwięku.
    /// </summary>
    QElapsedTimer* noSoundTimer = new QElapsedTimer;

    /// <summary>
    /// Wskaźnik na wątek odpowiedzialny za zmiane stanu programu zależnie od wciśnietego przycisku.
    /// </summary>
    KeyPressThread* keyPressThread;

    /// <summary>
    /// Zmienna logiczna przechowująca wartość o wciśnięciu dowolnego przycisku.
    /// </summary>
    bool keyPressed;

    /// <summary>
    /// Wskaźnik na stos zawierający ID wciśniętych przycisków.
    /// </summary>
    //std::stack<int>* keysPressed;
    std::vector<int>* keysPressed;


signals:
    void visualiseKeyPressSignal(int keyID);
    void visualiseKeyReleaseSignal(int keyID);
    void emitClearStaveSignal();
    void emitChangeSoundKeyPairSignal(int keyID);
    void emitPrevOptionSignal();
    void emitNextOptionSignal();
    void emitLeftRelativeOptionSignal();
    void emitRightRelativeOptionSignal();
    void emitSelectOptionSignal();
    void emitCreateNewNoteSignal(int keyPressed, int beats);

public slots:
	void displayRecordedAudio(int option);

    void keyPress(int keyID);
    void keyRelease(int keyID);

};

