#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QProcess>
#include <QTimer>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();
    void PlayPause();
    void Switch(QString);
    void SetPos(int);

signals:
    void TimeChanged(QString, int);
    void Finished();
    void StatusChanged(bool);

private slots:
    void update();
    void readOutput();

private:
    QProcess process;
    QTimer timer;
    bool isPlaying;
    QString totalTime;
    QString getTimeString(const QString&);
};

#endif // CONTROLLER_H
