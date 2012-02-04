#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include <QObject>
#include <QVector>
#include <QHash>
#include "song.h"

class MusicLibrary : public QObject
{
    Q_OBJECT
public:
    explicit MusicLibrary(QObject *parent = 0);
    void Add(const Song& song);
    QVector<Song> GetAllSongs();
    QVector<Song> GetByAlbum(QString album);
    QVector<Song> GetByArtist(QString artist);
    QVector<QString> GetAlbums();
    QVector<QString> GetArtists();

private:
    QVector<Song> lib;
};

#endif // MUSICLIBRARY_H
