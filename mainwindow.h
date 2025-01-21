#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QLineEdit>
#include <QMainWindow>
#include "ChessArray.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setPiece(QPushButton* button, const QString& pieceImagePath);
    void setupChessPieces();

    void showTurnPlayer(char turn);
    void showGameStatus(string text);
    void handlePromotion(char turn, Piece* piece);

    void logMessage(pair<int, int> old_coords, pair<int, int> new_coords);

private slots:
    void handleButtonClick();
    void handlePromotionClick();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    char turn;
    ChessArray chessArray;
    bool pieceSelected;
    int x, y;
    QPushButton* saved_button;
    bool clickWait;
};
#endif // MAINWINDOW_H
