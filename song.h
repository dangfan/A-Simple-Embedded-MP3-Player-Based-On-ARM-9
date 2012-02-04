#ifndef SONG_H
#define SONG_H

#include <QString>

class Song
{
public:
    Song();
    Song(QString path);
    QString Title();
    QString Artist();
    QString Album();
    QString Path();

private:
    QString title;
    QString artist;
    QString album;
    QString path;
};

#endif // SONG_H
