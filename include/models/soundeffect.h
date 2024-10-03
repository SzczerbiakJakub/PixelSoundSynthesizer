#pragma once

#include <iostream>
#include <windows.h>
#include <Mmdeviceapi.h>
#include <audioclient.h>


/// <summary>
/// Klasa reprezentująca źródło dźwięku programu.
/// </summary>
class AudioSource
{
public:
    /// <summary>
    /// Konstruktor domyślny klasy.
    /// </summary>
    AudioSource() {};

    /// <summary>
    /// Konstruktor klasy.
    /// </summary>
	/// <param name=freq> Częstotliwość generowanego dźwięku. </param>
	/// <param name=noteSymbol> Symbol dźwięku. </param>
    AudioSource(float freq, std::string noteSymbol) : frequency(freq), noteSymbol(noteSymbol) {};

    /// <summary>
    /// Destruktor klasy.
    /// </summary>
    ~AudioSource();

    /// <summary>
    /// Metoda ustawiająca format dźwięku.
    /// </summary>
	/// <param name=wfex> Format dźwięku. </param>
    HRESULT SetFormat(WAVEFORMATEX* wfex);

    /// <summary>
    /// Metoda wczytująca dane dźwiękowe
    /// </summary>
    /// <param name=totalFrames> Ilość klatek. </param>
    /// <param name=dataOut> Wskaźnik na zewnętrzny bufor. </param>
    /// <param name=flags> Flagi bufora. </param>
    HRESULT LoadData(UINT32 totalFrames, BYTE* dataOut, DWORD* flags);

    /// <summary>
    /// Metoda wczytująca dźwięk od nowa.
    /// </summary>
    void refresh();

    /// <summary>
    /// Zmienna przechowująca symbol dźwięku.
    /// </summary>
    std::string noteSymbol;

private:
    /// <summary>
    /// Metoda inicjalizująca obiekt.
    /// </summary>
    void init();

    /// <summary>
    /// Zmienna przechowująca stan inicjalizacji obiektu.
    /// </summary>
    bool initialised = false;

    /// <summary>
    /// Zmienna przechowująca format dźwięku.
    /// </summary>
    WAVEFORMATEXTENSIBLE  format;

    /// <summary>
    /// Zmienna przechowująca chwilową pozycję danych.
    /// </summary>
    unsigned int pcmPos = 0;

    /// <summary>
    /// Zmienna przechowująca rozmiar bufora.
    /// </summary>
    UINT32 bufferSize;

    /// <summary>
    /// Zmienna przechowująca chwilową pozycje w buforze.
    /// </summary>
    UINT32 bufferPos = 0;

    /// <summary>
    /// Zmienna przechowująca ilość próbek dźwięku.
    /// </summary>
    static const unsigned int sampleCount = 96000;

    /// <summary>
    /// Zmienna przechowująca częstotliwość dźwięku.
    /// </summary>
    float frequency;

    /// <summary>
    /// Wskaźnik przechowujący dane dotyczące dźwięku obiektu.
    /// </summary>
    float* pcmAudio = nullptr;
};


#define REFTIMES_PER_SEC  1000000
#define REFTIMES_PER_MILLISEC  10000

#define EXIT_ON_ERROR(hres)  \
              if (FAILED(hres)) {std::cout << hres<< '\n'; goto Exit; }
#define SAFE_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { (punk)->Release(); (punk) = NULL; }


/// <summary>
/// Klasa reprezentująca strumień dźwięku programu.
/// </summary>
class AudioStream
{
public:
    /// <summary>
    /// Konstruktor klasy.
    /// </summary>
    AudioStream();

    /// <summary>
    /// Destruktor klasy.
    /// </summary>
    ~AudioStream();

    /// <summary>
    /// Metoda pozwalajaca na zagranie dźwięku.
    /// </summary>
    /// <param name=audioSource> Wskaźnik na źródło dźwięku. </param>
    HRESULT playAudio(AudioSource* audioSource);

    /// <summary>
    /// Metoda zwracająca wskaźnik na serwer dźwięku.
    /// </summary>
    IAudioClient* getAudioClient() { return pAudioClient; }

    /// <summary>
    /// Metoda zwracająca wskaźnik na odtwarzacz dźwięku.
    /// </summary>
    IAudioRenderClient* getAudioRenderClient() { return pRenderClient; }


private:
    /// <summary>
    /// Zmienna obiektu HRESULT.
    /// </summary>
    HRESULT hr;

    /// <summary>
    /// Żądana wielkość bufora.
    /// </summary>
    REFERENCE_TIME hnsRequestedDuration;

    /// <summary>
    /// Rzeczywista wielkość bufora.
    /// </summary>
    REFERENCE_TIME hnsActualDuration;

    /// <summary>
    /// Wskaźnik na serwer dźwięku.
    /// </summary>
    IAudioClient* pAudioClient;

    /// <summary>
    /// Wskaźnik na odtwarzacz dźwięku.
    /// </summary>
    IAudioRenderClient* pRenderClient;

    /// <summary>
    /// Wskaźnik na format dźwięku.
    /// </summary>
    WAVEFORMATEX* pwfx;

    /// <summary>
    /// Wskaźnik na najbliższy parametrami format dźwięku.
    /// </summary>
    WAVEFORMATEX* pClosestMatch = nullptr;

    /// <summary>
    /// Ilość klatek w buforze.
    /// </summary>
    UINT32 bufferFrameCount;

    /// <summary>
    /// Ilość dostępnych klatek.
    /// </summary>
    UINT32 numFramesAvailable;

    /// <summary>
    /// Ilość zajętych klatek.
    /// </summary>
    UINT32 numFramesPadding;

    /// <summary>
    /// Zmienna typu hEvent.
    /// </summary>
    HANDLE hEvent = NULL;

    /// <summary>
    /// Zmienna typu hTask.
    /// </summary>
    HANDLE hTask = NULL;

    /// <summary>
    /// Wskaźnik na bufor.
    /// </summary>
    BYTE* pData;

    /// <summary>
    /// Flagi bufora
    /// </summary>
    DWORD flags = 0;

    /// <summary>
    /// Częstotliwość próbek dźwięku na sekundę.
    /// </summary>
    const UINT32 sampleRate = 48000;
};
