#include "song.h"
#include <QTextCodec>
#include <taglib/tag.h>
#include <taglib/taglib.h>
#include <taglib/fileref.h>

Song::Song()
{}

Song::Song(QString path)
{
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    this->path = path;
    TagLib::FileRef f(path.toUtf8());
    if (f.tag()->artist().isLatin1()) {
        title = gbk->toUnicode(f.tag()->title().toCString());
        artist = gbk->toUnicode(f.tag()->artist().toCString());
        album = gbk->toUnicode(f.tag()->album().toCString());
        title = title.trimmed();
        artist = artist.trimmed();
        album = album.trimmed();
    } else {
        title = TStringToQString(f.tag()->title()).trimmed();
        artist = TStringToQString(f.tag()->artist()).trimmed();
        album = TStringToQString(f.tag()->album()).trimmed();
    }
}

QString Song::Album()
{
    return album;
}

QString Song::Artist()
{
    return artist;
}

QString Song::Title()
{
    return title;
}

QString Song::Path()
{
    return path;
}
