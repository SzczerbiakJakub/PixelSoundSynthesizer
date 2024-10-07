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
#include <threads.h>
#include <menuwidget.h>
#include <stavewidget.h>
#include <keyboardwidget.h>
#include <mainwindowviewmodel.h>


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


private:

    MainWindowViewModel* viewModel;

    /// <summary>
    /// Metoda tworząca GUI obiektu.
    /// </summary>
    void buildUi();

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
    /// Metoda wywoływana przy wciśnięciu dowolnego przycisku klawiatury.
    /// </summary>
    void keyPressEvent(QKeyEvent* event) override;

    /// <summary>
    /// Metoda wywoływana przy odciśnięciu dowolnego przycisku klawiatury.
    /// </summary>
    void keyReleaseEvent(QKeyEvent* event) override;


signals:
    void keyPressSignal(int keyID);
    void keyReleaseSignal(int keyID);


private slots:

    void visualiseKeyPress(int keyID);
    void visualiseKeyRelease(int keyID);
    void emitClearStave();

    void emitChangeSoundKeyPair(int keyID);

    void emitPrevOption();
    void emitNextOption();
    void emitLeftRelativeOption();
    void emitRightRelativeOption();
    void emitSelectOption();
    void emitCreateNewNote(AudioSource* audioSource, int beats);

};