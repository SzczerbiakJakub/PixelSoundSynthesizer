#pragma once
#include <QThread>
#include <QElapsedTimer>
#include <QTimer>
#include <stack>
#include <soundeffect.h>
#include <data.h>



#define RECORD_STATE_RENDER_TIME 400	//	in ms

/// <summary>
/// Klasa reprezentująca wątek przetwarzania dźwięku w programie.
/// </summary>
class KeyPressThread : public QThread
{
    Q_OBJECT

public:
    /// <summary>
    /// Konstruktor klasy.
    /// </summary>
    /// <param name=keyPressed> Wskaźnik na wartość logiczną dotyczącą wciśnięcia klawisza.</param>
    KeyPressThread(bool* keyPressed, std::vector<int>* keysPressedStack);

    /// <summary>
    /// Destruktor klasy.
    /// </summary>
    ~KeyPressThread();

    /// <summary>
    /// Ustawia aktualny dźwięk na wybrany.
    /// </summary>
    /// <param name=sound> Wskaźnik na źródło dźwięku.</param>
    void setCurrentSound(AudioSource* sound) { currentSound = sound; };

    /// <summary>
    /// Ustawia aktualny klawisz na wybrany.
    /// </summary>
    /// <param name=pressedKey> Wskaźnik na wciśnięty klawisz.</param>
    void setCurrentKey(int* pressedKey) { key = pressedKey; };

    /// <summary>
    /// Ustawia odtwarzanie audio.
    /// </summary>
    /// <param name=displayAudioBool> Wskaźnik na wciśnięty klawisz.</param>
    void setDisplayAudio(bool displayAudioBool) { displayAudio = displayAudioBool; }

    /// <summary>
    /// Odtwarza nagranie o wybranym indeksie.
    /// </summary>
    /// <param name=index> Indeks nagrania.</param>
    void displayRecordedAudio(int index);


private:

    QElapsedTimer* keyPressTimer;

    std::queue<std::pair<AudioSource*, int>> bufferCopy;

    /// <summary>
    /// Włącza wątek.
    /// </summary>
    void run() override;


    /// <summary>
    /// Odtwarza obecny dźwięk przez określony czas.
    /// </summary>
    /// <param name=ms> Czas w milisekundach.</param>
    void displayAudioForCertainTime(AudioSource* audioSource, int ms);

    /// <summary>
    /// Parametr przechowujący informację odnośnie odtwarzania dźwięku.
    /// </summary>
    bool displayAudio;

    /// <summary>
    /// Wskaźnik na zmienną przechowującą informację o wciśnieciu klawisza.
    /// </summary>
    bool* keyPressed;
    
    std::vector<int>* keysPressedStack;

    /// <summary>
    /// Wskaźnik na klawisz.
    /// </summary>
    int* key;

    /// <summary>
    /// Wskaźnik na obecne źródło dźwięku.
    /// </summary>
    AudioSource* currentSound;

    /// <summary>
    /// Wskaźnik na obecny stream dźwięku.
    /// </summary>
    AudioStream* audioStream;


signals:
    void emitCreateNewNoteSignal(AudioSource* audioSource, int beats);
    void startPlayingRecordSignal();
    void stopPlayingRecordSignal();

public slots:
    void restartKeyPressTimer();

};


class StaveWidgetRenderThread : public QThread
{
    Q_OBJECT

public:
    StaveWidgetRenderThread(bool* recording, bool* playing);
    ~StaveWidgetRenderThread();

private:
    QTimer* renderTimer;

    bool* recording;
    bool* playing;

    void run() override;
signals:
    void delegateStaveRenderSignal();
};