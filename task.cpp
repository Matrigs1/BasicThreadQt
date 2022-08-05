#include "task.h"

Task::Task(QObject *parent)
    : QObject{parent}
{
    qInfo() << "Constructed " << this << " on: " << QThread::currentThread();
}

Task::~Task()
{
    qInfo() << "Deconstructed " << this << " on: " << QThread::currentThread();
}

void Task::work()
{
    //sinaliza qual thread está sendo executado
    QThread *thread = QThread::currentThread();

    qInfo() << "Starting " << thread;
    for(int i = 0; i < 10; i++)
    {
        qInfo() << i << " on " << thread;
    }
    qInfo() << "Finished " << thread;
}
