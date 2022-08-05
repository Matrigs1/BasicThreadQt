#include <QCoreApplication>
#include <QScopedPointer>
#include "task.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Part 1 - QThread
      //criando um QThread no thread atual
//    QThread *thread = QThread::currentThread();
      //Dando um nome para o Thread
//    thread->setObjectName("Main Thread");

//    qInfo() << "Starting" << thread;

//    //tudo no mesmo thread
//    for(int i = 0; i < 10; i++)
//    {
//        qInfo() << i << "on" << thread;
//    }

//    qInfo() << "Finished" << thread;

    //Part 2 - Move to thread

    //setando o nome do thread atual como "Main Thread"
    QThread::currentThread()->setObjectName("Main Thread");
    //criando um novo QThread e setando o nome dele
    QThread worker;
    worker.setObjectName("Worker Thread");

    //Main thread
    qInfo() << "Starting work" << QThread::currentThread();
    //Task *task = new Task(&a); vai dar problema se mover de thread
    //Criando um ptr para Task
    QScopedPointer<Task> t(new Task()); //Auto-delete
    //Retorna o valor do ponteiro referênciado por esse obj (QScopedPointer) e joga em um ptr de Task
    Task *task = t.data();
    //Muda o thread do obj e de suas children. Não pode ser feito se tiver um parent.
    t->moveToThread(&worker);
    //Um signal de QThread::started é emitido quando começa a ser executado e esse
    //signal é enviado para o slot work de Task.
    worker.connect(&worker, &QThread::started, task, &Task::work);

    //aqui começa a execução
    worker.start();
    qInfo() << "Free to do other things..." << QThread::currentThread();

    return a.exec();
}
