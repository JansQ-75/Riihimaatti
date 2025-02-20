#include "mainwindow.h"
#include <QFontDatabase>
#include <QApplication>


void applyStyleSheet(QApplication &app){
    QFile file("style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    QTextStream in(&file);
    app.setStyleSheet(styleSheet);
    file.close();

    if (!file.exists()) {
        qDebug() << "Error: style.qss does NOT exist!";
        return;
    }

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Error: Could not open style.qss!" << file.errorString();
        return;
    }


    if (styleSheet.isEmpty()) {
        qDebug() << "Warning: style.qss is empty!";
        return;
    }

    qDebug() << "Loaded style.qss:\n";

}

void listAvailableFonts() {
    QStringList fonts = QFontDatabase().families();
    qDebug() << "Saatavilla olevat fontit:";
    for (const QString &font : fonts) {
        qDebug() << font;
    }

}
int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    applyStyleSheet(app);
  //  listAvailableFonts();


    MainWindow w;
    w.show();
    return app.exec();

}
