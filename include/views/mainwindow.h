#pragma once

#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>
#include <QElapsedTimer>
#include <QThread>
#include <stack>
#include <data.h>
#include <soundeffect.h>
#include <threads.h>
#include <optionswidget.h>
#include <stavewidget.h>
#include <keyboardwidget.h>


/// <summary>
/// Klasa reprezentująca główne okno programu.
/// </summary>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// <summary>
    /// Konstruktor klasy.
    /// </summary>
    /// <param name=parent> Nadrzędny widget. </param>
    MainWindow(QWidget* parent = nullptr);

    /// <summary>
    /// Destruktor klasy.
    /// </summary>
    ~MainWindow();

    /// <summary>
    /// Metoda zwracająca wskaźnik na wątek klasy KeyPressThread.
    /// </summary>
    KeyPressThread* getKeyPressThread() { return keyPressThread; };

    /// <summary>
    /// Parametr HRESULT.
    /// </summary>
    HRESULT hr;

private:
    /// <summary>
    /// Metoda tworząca GUI obiektu.
    /// </summary>
    void buildUi();

    /// <summary>
    /// Wskaźnik na obiekt AudioStream odpowiedzialny za streaming dźwięku w programie.
    /// </summary>
    AudioStream* audioStream;

    /// <summary>
    /// Wskaźnik na centralny widget okna.
    /// </summary>
    QWidget* centralWidget;

    /// <summary>
    /// Wskaźnik na widget klawiatury programu.
    /// </summary>
    KeyboardWidget* keyboardWidget;

    /// <summary>
    /// Wskaźnik na widget pięciolinii programu.
    /// </summary>
    StaveWidget* staveWidget;

    /// <summary>
    /// Wskaźnik na widget menu programu.
    /// </summary>
    MenuWidget* menuWidget;

    /// <summary>
    /// Wskaźnik na timer mierzący czas wciśnięcia przycisku.
    /// </summary>
    QElapsedTimer* keyPressTimer = new QElapsedTimer;

    /// <summary>
    /// Wskaźnik na timer mierzący czas braku dźwięku.
    /// </summary>
    QElapsedTimer* noSoundTimer = new QElapsedTimer;

    /// <summary>
    /// Zmienna logiczna przechowująca wartość o wciśnięciu dowolnego przycisku.
    /// </summary>
    bool keyPressed;

    /// <summary>
    /// Wskaźnik na stos zawierający ID wciśniętych przycisków.
    /// </summary>
    std::stack<int>* keysPressed = new std::stack<int>;

    /// <summary>
    /// Wskaźnik na wątek odpowiedzialny za zmiane stanu programu zależnie od wciśnietego przycisku.
    /// </summary>
    KeyPressThread* keyPressThread = new KeyPressThread(&keyPressed);

    /// <summary>
    /// Metoda wywoływana przy wciśnięciu dowolnego przycisku klawiatury.
    /// </summary>
    void keyPressEvent(QKeyEvent* event) override;

    /// <summary>
    /// Metoda wywoływana przy odciśnięciu dowolnego przycisku klawiatury.
    /// </summary>
    void keyReleaseEvent(QKeyEvent* event) override;
};