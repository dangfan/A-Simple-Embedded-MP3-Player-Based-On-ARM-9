#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QStandardItemModel>
#include "musiclibrary.h"
#include "status.h"
#include "controller.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MusicLibrary lib;
    QVector<Song> currentSongs;
    QVector<Song> tmp;
    void scanFiles(QString dir);
    Status status;
    Controller controller;
    int currentSongIndex;
    bool isDying;
    void closeEvent(QCloseEvent *);
    QStandardItemModel *model;

private slots:
    void on_nowPlaying_clicked();
    void on_horizontalSlider_sliderReleased();
    void on_nextButton_clicked();
    void on_prevButton_clicked();
    void on_playButton_clicked();
    void on_back_clicked();
    void on_listView_clicked(QModelIndex index);
    void on_artists_clicked();
    void on_albums_clicked();
    void on_allSongs_clicked();
    void timeChanged(QString, int);
    void statusChanged(bool);
    void onFinished();
};

#endif // MAINWINDOW_H
