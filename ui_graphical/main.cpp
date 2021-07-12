#include "mainwindow.h"
#include <QApplication>
#include <cstdio>
#include <exception>
#include <unistd.h>



int main(int argc, char *argv[])
{
    try{
        printf("this process's id: %d\n",getpid());
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();

    }catch(std::exception e){
        printf("%s\n",e.what());
    }
}
