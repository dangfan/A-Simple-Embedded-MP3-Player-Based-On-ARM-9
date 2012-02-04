#include "musiclibrary.h"

MusicLibrary::MusicLibrary(QObject *parent) :
    QObject(parent)
{
}

void MusicLibrary::Add(const Song& song)
{
    lib.append(song);
}

QVector<Song> MusicLibrary::GetAllSongs()
{
    return lib;
}

QVector<Song> MusicLibrary::GetByAlbum(QString album)
{
    QVector<Song> tmp;
    foreach(Song song, lib)
    {
        if (song.Album() == album)
            tmp.append(song);
    }
    return tmp;
}

QVector<Song> MusicLibrary::GetByArtist(QString artist)
{
    QVector<Song> tmp;
    foreach(Song song, lib)
    {
        if (song.Artist() == artist)
            tmp.append(song);
    }
    return tmp;
}

QVector<QString> MusicLibrary::GetAlbums()
{
    QVector<QString> tmp;
    QHash<QString, bool> hash;
    foreach(Song song, lib)
    {
        hash[song.Album()] = true;
    }
    foreach(QString album, hash.keys())
    {
        tmp.append(album);
    }
    return tmp;
}

QVector<QString> MusicLibrary::GetArtists()
{
    QVector<QString> tmp;
    QHash<QString, bool> hash;
    foreach(Song song, lib)
    {
        hash[song.Artist()] = true;
    }
    foreach(QString artist, hash.keys())
    {
        tmp.append(artist);
    }
    return tmp;
}
