#pragma once
#include <QThread>
#include <QElapsedTimer>
#include <soundeffect.h>
#include <data.h>




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
    KeyPressThread(bool* keyPressed);

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

    /// <summary>
    /// Włącza wątek.
    /// </summary>
    void run() override;

    /// <summary>
    /// Odtwarza obecny dźwięk przez określony czas.
    /// </summary>
    /// <param name=ms> Czas w milisekundach.</param>
    void displayAudioForCertainTime(int ms);

    /// <summary>
    /// Parametr przechowujący informację odnośnie odtwarzania dźwięku.
    /// </summary>
    bool displayAudio;

    /// <summary>
    /// Wskaźnik na zmienną przechowującą informację o wciśnieciu klawisza.
    /// </summary>
    bool* keyPressed;

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

};