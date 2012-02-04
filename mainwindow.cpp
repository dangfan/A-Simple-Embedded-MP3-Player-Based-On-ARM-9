#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDirIterator>
#include <QStringListModel>
#include "listviewdelegate.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ListviewDelegate *delegate = new ListviewDelegate();
    model = new QStandardItemModel();
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView->setItemDelegate(delegate);
    ui->listView->setModel(model);
    scanFiles("/mnt/udisk");
    on_allSongs_clicked();
    currentSongIndex = -1;
    connect(&controller, SIGNAL(TimeChanged(QString,int)), this, SLOT(timeChanged(QString,int)));
    connect(&controller, SIGNAL(StatusChanged(bool)), this, SLOT(statusChanged(bool)));
    connect(&controller, SIGNAL(Finished()), this, SLOT(onFinished()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::scanFiles(QString dir)
{
    QDirIterator it(dir, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        QString path = it.next();
        if (path.endsWith(".mp3"))
        {
            lib.Add(Song(path));
        }
    }
}

void MainWindow::on_allSongs_clicked()
{
    tmp = lib.GetAllSongs();
    model->clear();
    foreach(Song song, tmp)
    {
        QStandardItem *item = new QStandardItem();
        QIcon icon(":/images/cur.png");
        item->setData(song.Title(),ListviewDelegate::headerTextRole);
        item->setData("    " + song.Artist() + " - " + song.Album(),ListviewDelegate::subHeaderTextrole);
        item->setData(icon,ListviewDelegate::IconRole);
        model->appendRow(item);
    }
    status = AllSongs;
    ui->state->setText("全部歌曲");
}

void MainWindow::on_albums_clicked()
{
    model->clear();
    foreach(QString album, lib.GetAlbums())
    {
        QStandardItem *item = new QStandardItem();
        QIcon icon(":/images/cur.png");
        item->setData(album,ListviewDelegate::headerTextRole);
        item->setData(icon,ListviewDelegate::IconRole);
        model->appendRow(item);
    }
    status = Albums;
    ui->state->setText("专辑");
}

void MainWindow::on_artists_clicked()
{
    QIcon icon(":/images/cur.png");
    model->clear();
    foreach(QString artist, lib.GetArtists())
    {
        QStandardItem *item = new QStandardItem();
        item->setData(artist,ListviewDelegate::headerTextRole);
        item->setData(icon,ListviewDelegate::IconRole);
        model->appendRow(item);
    }
    status = Artists;
    ui->state->setText("歌手");
}

void MainWindow::on_back_clicked()
{
    if (status == AlbumSongs)
    {
        on_albums_clicked();
    }
    else if (status == ArtistSongs)
    {
        on_artists_clicked();
    }
}

void MainWindow::timeChanged(QString str, int pos)
{
    ui->horizontalSlider->setValue(pos);
    ui->timeLabel->setText(str);
}

void MainWindow::statusChanged(bool isPlaying)
{
    if (isPlaying)
        ui->playButton->setIcon(QIcon(":/images/i_pause.png"));
    else
        ui->playButton->setIcon(QIcon(":/images/i_play.png"));
}

void MainWindow::on_playButton_clicked()
{
    controller.PlayPause();
}

void MainWindow::on_listView_clicked(QModelIndex index)
{
    QIcon icon(":/images/cur.png");
    if (status == Albums)
    {
        model->clear();
        tmp = lib.GetByAlbum(lib.GetAlbums()[index.row()]);
        foreach(Song song, tmp)
        {
            QStandardItem *item = new QStandardItem();
            item->setData(song.Title(), ListviewDelegate::headerTextRole);
            item->setData("  " + song.Artist() + " - " + song.Album(), ListviewDelegate::subHeaderTextrole);
            item->setData(icon,ListviewDelegate::IconRole);
            model->appendRow(item);
        }
        status = AlbumSongs;
    }
    else if (status == Artists)
    {
        model->clear();
        tmp = lib.GetByArtist(lib.GetArtists()[index.row()]);
        foreach(Song song, tmp)
        {
            QStandardItem *item = new QStandardItem();
            item->setData(song.Title(), ListviewDelegate::headerTextRole);
            item->setData("  " + song.Artist() + " - " + song.Album(), ListviewDelegate::subHeaderTextrole);
            item->setData(icon,ListviewDelegate::IconRole);
            model->appendRow(item);
        }
        status = ArtistSongs;
    }
    else
    {
        if (currentSongIndex != -1)
            model->item(currentSongIndex)->setData(QIcon(":images/cur.png"),ListviewDelegate::IconRole);
        currentSongs = tmp;
        currentSongIndex = index.row();
        controller.Switch(currentSongs[currentSongIndex].Path());
        model->item(currentSongIndex)->setData(QIcon(":images/now.png"),ListviewDelegate::IconRole);
        ui->listView->selectionModel()->clear();
        status = Now;
        ui->state->setText("正在播放");
    }
}

void MainWindow::on_prevButton_clicked()
{
    if (currentSongIndex)
    {
        controller.Switch(currentSongs[--currentSongIndex].Path());
        if (status != Now)
            return;
        model->item(currentSongIndex + 1)->setData(QIcon(":images/cur.png"),ListviewDelegate::IconRole);
        model->item(currentSongIndex)->setData(QIcon(":images/now.png"),ListviewDelegate::IconRole);
    }
}

void MainWindow::on_nextButton_clicked()
{
    if (currentSongIndex < currentSongs.size() - 1)
    {
        controller.Switch(currentSongs[++currentSongIndex].Path());
        if (status != Now)
            return;
        model->item(currentSongIndex - 1)->setData(QIcon(":images/cur.png"),ListviewDelegate::IconRole);
        model->item(currentSongIndex)->setData(QIcon(":images/now.png"),ListviewDelegate::IconRole);
    }
}

void MainWindow::onFinished()
{
    if (!isDying)
        on_nextButton_clicked();
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    controller.SetPos(ui->horizontalSlider->value() / 5);
}

void MainWindow::closeEvent(QCloseEvent*)
{
    isDying = true;
}

void MainWindow::on_nowPlaying_clicked()
{
    QIcon icon(":/images/cur.png");
    model->clear();
    foreach(Song song, currentSongs)
    {
        QStandardItem *item = new QStandardItem();
        item->setData(song.Title(),ListviewDelegate::headerTextRole);
        item->setData("   " + song.Artist() + " - " + song.Album(),ListviewDelegate::subHeaderTextrole);
        item->setData(icon,ListviewDelegate::IconRole);
        model->appendRow(item);
    }
    status = Now;
    ui->state->setText("正在播放");
    model->item(currentSongIndex)->setData(QIcon(":images/now.png"),ListviewDelegate::IconRole);
}
