#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), centralWidget(new QWidget(this)), keyboardWidget(nullptr)
{
    buildUi();
    setFixedSize(1536, 800);

    viewModel = new MainWindowViewModel();

    QObject::connect(this, &MainWindow::keyPressSignal, viewModel, &MainWindowViewModel::keyPress);
    QObject::connect(this, &MainWindow::keyReleaseSignal, viewModel, &MainWindowViewModel::keyRelease);

    
    QObject::connect(menuWidget, &MenuWidget::displaySelectedAudioSignal, viewModel, &MainWindowViewModel::displayRecordedAudio);
    
    QObject::connect(viewModel, &MainWindowViewModel::visualiseKeyPressSignal , this, &MainWindow::visualiseKeyPress);
    QObject::connect(viewModel, &MainWindowViewModel::visualiseKeyReleaseSignal, this, &MainWindow::visualiseKeyRelease);
    QObject::connect(viewModel, &MainWindowViewModel::emitClearStaveSignal, this, &MainWindow::emitClearStave);
    QObject::connect(viewModel, &MainWindowViewModel::emitChangeSoundKeyPairSignal, this, &MainWindow::emitChangeSoundKeyPair);
    QObject::connect(viewModel, &MainWindowViewModel::emitPrevOptionSignal, this, &MainWindow::emitPrevOption);
    QObject::connect(viewModel, &MainWindowViewModel::emitNextOptionSignal, this, &MainWindow::emitNextOption);
    QObject::connect(viewModel, &MainWindowViewModel::emitLeftRelativeOptionSignal, this, &MainWindow::emitLeftRelativeOption);
    QObject::connect(viewModel, &MainWindowViewModel::emitRightRelativeOptionSignal, this, &MainWindow::emitRightRelativeOption);
    QObject::connect(viewModel, &MainWindowViewModel::emitSelectOptionSignal, this, &MainWindow::emitSelectOption);
    QObject::connect(viewModel, &MainWindowViewModel::emitCreateNewNoteSignal, this, &MainWindow::emitCreateNewNote);

}


MainWindow::~MainWindow()
{
    delete keyboardWidget;
    delete staveWidget;
    delete menuWidget;
    delete centralWidget;
    delete viewModel;
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
    if (!(event->isAutoRepeat()))
        emit keyPressSignal(event->key());
}



void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (!(event->isAutoRepeat()))
        emit keyReleaseSignal(event->key());
};


void MainWindow::visualiseKeyPress(int keyID) {
    emit keyboardWidget->keyPressedSignal(keyID);
}


void MainWindow::visualiseKeyRelease(int keyID) {
    emit keyboardWidget->keyReleasedSignal(keyID);
}

void MainWindow::emitClearStave() {
    emit staveWidget->clearStaveSignal();
}


void MainWindow::emitChangeSoundKeyPair(int keyID) {
    emit menuWidget->changeSoundKeyPairSignal(keyID);
}


void MainWindow::emitPrevOption() {
    emit menuWidget->prevOptionSignal();
}


void MainWindow::emitNextOption() {
    emit menuWidget->nextOptionSignal();
}


void MainWindow::emitLeftRelativeOption() {
    emit menuWidget->leftRelativeOptionSignal();
}


void MainWindow::emitRightRelativeOption() {
    emit menuWidget->rightRelativeOptionSignal();
}


void MainWindow::emitSelectOption() {
    emit menuWidget->selectOptionSignal();
}


void MainWindow::emitCreateNewNote(int keyPressed, int beats) {
    emit staveWidget->createNewNoteSignal(KeyboardData::getAudio(keyPressed), beats);
}