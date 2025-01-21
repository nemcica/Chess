#include "mainwindow.h"
#include "ChessArray.h"
#include <QApplication>

vector<vector<Piece*>> ChessArray::chessPieces(8, vector<Piece*>(8, nullptr));

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
