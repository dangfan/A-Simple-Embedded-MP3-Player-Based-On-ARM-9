#include "controller.h"
#include <QTime>

Controller::Controller(QObject *parent) :
        QObject(parent)
{
    process.setProcessChannelMode(QProcess::MergedChannels);
    connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(&process, SIGNAL(finished(int)), this, SIGNAL(Finished()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(1000);
}

Controller::~Controller()
{
    process.kill();
}

void Controller::PlayPause()
{
    process.write("pause\n");
    emit StatusChanged(isPlaying = !isPlaying);
}

void Controller::Switch(QString path)
{
    const QString mplayer("mplayer");
    QStringList args;
    args << "-slave" << "-quiet" << path;
    if (process.state() == QProcess::Running)
        process.write(QString("loadfile \"" + path + "\"\n").toLocal8Bit());
    else
        process.start(mplayer, args);
    process.write("get_time_length\n");
    emit StatusChanged(isPlaying = true);
}

void Controller::update()
{
    if (isPlaying)
        process.write("get_time_pos\n");
}

void Controller::readOutput()
{
    while(process.canReadLine())
    {
        QString message(process.readLine());
        if (message.startsWith("ANS_L"))
            totalTime = message.mid(11);
        else if (message.startsWith("ANS_T"))
            emit TimeChanged(getTimeString(message.mid(18)),
                             (int)(500 * message.mid(18).toDouble() / totalTime.toDouble()));
    }
}

QString Controller::getTimeString(const QString& cur)
{
    QTime t;
    return t.addSecs((int) (cur.toDouble() + 0.5)).toString("hh:mm:ss")
            + "/"
            + t.addSecs((int) (totalTime.toDouble() + 0.5)).toString("hh:mm:ss");
}

void Controller::SetPos(int pos)
{
    if (process.state() == QProcess::Running)
    {
        process.write(QString("seek " + QString::number(pos) + " 1").toLocal8Bit());
        emit StatusChanged(isPlaying = true);
    }
}
