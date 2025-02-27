#include "mainwindow.h"
#include <QFontDatabase>
#include <QApplication>
#include <QDialog>


void applyStyleSheet(QApplication &app){
    QFile file("../style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    QTextStream in(&file);
    app.setStyleSheet(styleSheet);
    file.close();
}

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    applyStyleSheet(app);

    MainWindow w;
    w.show();
    return app.exec();

}
