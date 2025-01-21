#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>
#include <string>
#include <sstream>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), turn('w'), chessArray(ChessArray()), pieceSelected(false), clickWait(false) {
    x = 9;
    y = 9;
    saved_button = nullptr;

    ui->setupUi(this);
    setupChessPieces();

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            char letter = 'A' + i;
            char number = '1' + j;
            QString coord;
            coord.append(letter);
            coord.append(number);

            connect(findChild<QPushButton*>(coord), &QPushButton::clicked, this, &MainWindow::handleButtonClick);
        }
    }

    connect(findChild<QPushButton*>("Rook"), &QPushButton::clicked, this, &MainWindow::handlePromotionClick);
    connect(findChild<QPushButton*>("Knight"), &QPushButton::clicked, this, &MainWindow::handlePromotionClick);
    connect(findChild<QPushButton*>("Bishop"), &QPushButton::clicked, this, &MainWindow::handlePromotionClick);
    connect(findChild<QPushButton*>("Queen"), &QPushButton::clicked, this, &MainWindow::handlePromotionClick);

    findChild<QPushButton*>("Rook")->hide();
    findChild<QPushButton*>("Knight")->hide();
    findChild<QPushButton*>("Bishop")->hide();
    findChild<QPushButton*>("Queen")->hide();


    showTurnPlayer(turn);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButtonClick() {
    if(clickWait) return;

    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {

        //Color check tiles red
        while(!chessArray.check_coords.empty()) {
            findChild<QPushButton*>(chessArray.check_coords.top())->setStyleSheet("background-color: red; ");
            chessArray.check_coords.pop();
        }

        QString buttonName = button->objectName();

        string temp = buttonName.toStdString();
        char letter;
        int number;
        istringstream ss(temp);
        ss >> letter >> number;

        pair<int, int> coordinatesNN = chessArray.convert_to_NN(make_pair(letter, number));

        //Check for checkmate
        if (chessArray.checkmate(turn) && turn == 'w') {
            showGameStatus("Winner is Black");
            return;
        }
        if(chessArray.checkmate(turn) && turn == 'b') {
            showGameStatus("Winner is White");
        }

        //Move selected piece
        if(pieceSelected && button->styleSheet().contains("blue")) {

            if (chessArray.isValidMove(chessArray.getPiece(x, y), coordinatesNN, turn)) {

                for (auto move : chessArray.getPiece(x, y)->getMoves(ChessArray::chessPieces)) {
                    if (coordinatesNN == move) {
                        logMessage(make_pair(x, y), coordinatesNN);
                        chessArray.getPiece(x, y)->movePiece(coordinatesNN, ChessArray::chessPieces);

                        QIcon icon = saved_button->icon();
                        button->setIcon(icon);
                        button->setIconSize(QSize(50, 50));
                        saved_button->setIcon(QIcon());

                        if (turn == 'w') turn = 'b';
                        else if (turn == 'b') turn = 'w';
                        pieceSelected = false;

                        //Return tile color to original after moving
                        for(int i = 0; i < 8; i++) {
                            for(int j = 0; j < 8; j++) {
                                char letter = 'A' + i;
                                char number = '1' + j;

                                QString tile;
                                tile.append(letter);
                                tile.append(number);
                                if((i + j) % 2 == 0) findChild<QPushButton*>(tile)->setStyleSheet("background-color: orange; ");
                                else findChild<QPushButton*>(tile)->setStyleSheet("background-color: white; ");
                            }
                        }
                        //Pawn promotion
                        if(chessArray.getPiece(coordinatesNN.first, coordinatesNN.second)->getCoords().second == 0 ||
                        chessArray.getPiece(coordinatesNN.first, coordinatesNN.second)->getCoords().second == 7) {
                            saved_button = button;
                            handlePromotion(turn, chessArray.getPiece(coordinatesNN.first, coordinatesNN.second));
                        }
                        break;
                    }
                }
            } else {
                return;
            }
        }

        //Return tile color to original if invalid tile
        if(pieceSelected && !(button->styleSheet().contains("blue"))) {
            for(int i = 0; i < 8; i++) {
                for(int j = 0; j < 8; j++) {
                    char letter = 'A' + i;
                    char number = '1' + j;

                    QString tile;
                    tile.append(letter);
                    tile.append(number);

                    if(findChild<QPushButton*>(tile)->styleSheet().contains("blue")) {
                        if((i + j) % 2 == 0) findChild<QPushButton*>(tile)->setStyleSheet("background-color: orange; ");
                        else findChild<QPushButton*>(tile)->setStyleSheet("background-color: white; ");
                    }

                }
            }
            pieceSelected = false;
            return;
        }

        if(!pieceSelected && button->icon().isNull()) return;

        //Select a piece
        if(!pieceSelected) {
            x = coordinatesNN.first;
            y = coordinatesNN.second;
            saved_button = button;

            //Check if the selected tile corresponds to the current player
            if (chessArray.getPiece(x, y)->getColor() != turn || chessArray.getPiece(x,y) == nullptr
                || chessArray.getPiece(x,y)->getMoves(ChessArray::chessPieces).size() == 0) {

                pieceSelected = false;
                return;

            } else {

                pieceSelected = true;

                //Get possible moves for the selected piece
                for (auto move : chessArray.getPiece(x, y)->getMoves(ChessArray::chessPieces)) {
                    pair<char, int> moveLN = chessArray.convert_to_LN(move);
                    stringstream possible_move;
                    possible_move << moveLN.first << moveLN.second;
                    //Color the possible move tiles
                    QPushButton* color_button = findChild<QPushButton*>(possible_move.str());
                    color_button->setStyleSheet("background-color: blue;");
                }
            }
        }

    }

    showTurnPlayer(turn);
}

void MainWindow::setPiece(QPushButton* button, const QString& pieceImagePath) {
    QPixmap piecePixmap(pieceImagePath);
    button->setIcon(QIcon(piecePixmap.scaled(50, 50, Qt::KeepAspectRatio)));
    button->setIconSize(QSize(50, 50));
}

void MainWindow::setupChessPieces() {

    for(int i = 0; i < 8; i++) {
        char letter = 'A' + i;
        QString coord_w;
        QString coord_b;
        coord_w.append(letter);
        coord_w.append('2');

        coord_b.append(letter);
        coord_b.append('7');

        setPiece(findChild<QPushButton*>(coord_w), ":/chess_pieces/resources/pawn_w.png");
        setPiece(findChild<QPushButton*>(coord_b), ":/chess_pieces/resources/pawn_b.png");
    }

    setPiece(findChild<QPushButton*>("A8"), ":/chess_pieces/resources/rook_b.png");
    setPiece(findChild<QPushButton*>("B8"), ":/chess_pieces/resources/knight_b.png");
    setPiece(findChild<QPushButton*>("C8"), ":/chess_pieces/resources/bishop_b.png");
    setPiece(findChild<QPushButton*>("D8"), ":/chess_pieces/resources/queen_b.png");
    setPiece(findChild<QPushButton*>("E8"), ":/chess_pieces/resources/king_b.png");
    setPiece(findChild<QPushButton*>("F8"), ":/chess_pieces/resources/bishop_b.png");
    setPiece(findChild<QPushButton*>("G8"), ":/chess_pieces/resources/knight_b.png");
    setPiece(findChild<QPushButton*>("H8"), ":/chess_pieces/resources/rook_b.png");

    setPiece(findChild<QPushButton*>("A1"), ":/chess_pieces/resources/rook_w.png");
    setPiece(findChild<QPushButton*>("B1"), ":/chess_pieces/resources/knight_w.png");
    setPiece(findChild<QPushButton*>("C1"), ":/chess_pieces/resources/bishop_w.png");
    setPiece(findChild<QPushButton*>("D1"), ":/chess_pieces/resources/queen_w.png");
    setPiece(findChild<QPushButton*>("E1"), ":/chess_pieces/resources/king_w.png");
    setPiece(findChild<QPushButton*>("F1"), ":/chess_pieces/resources/bishop_w.png");
    setPiece(findChild<QPushButton*>("G1"), ":/chess_pieces/resources/knight_w.png");
    setPiece(findChild<QPushButton*>("H1"), ":/chess_pieces/resources/rook_w.png");
}

void MainWindow::showTurnPlayer(char turn) {
    QString text = "Current Player: ";
    if(turn == 'w') text.append("white");
    else if (turn == 'b') text.append("black");
    findChild<QLineEdit *>("Turn_player")->setText(text);
}

void MainWindow::showGameStatus(string text) {
    findChild<QLineEdit *>("KingCheckLog")->setText(QString::fromStdString(text));
}

void MainWindow::handlePromotion(char turn, Piece* piece) {
    if(piece->getName().find("Pw") == string::npos) return;

    if(turn == 'w') {
        setPiece(findChild<QPushButton*>("Rook"), ":/chess_pieces/resources/rook_b.png");
        setPiece(findChild<QPushButton*>("Bishop"), ":/chess_pieces/resources/bishop_b.png");
        setPiece(findChild<QPushButton*>("Knight"), ":/chess_pieces/resources/knight_b.png");
        setPiece(findChild<QPushButton*>("Queen"), ":/chess_pieces/resources/queen_b.png");
    }

    if(turn == 'b') {
        setPiece(findChild<QPushButton*>("Rook"), ":/chess_pieces/resources/rook_w.png");
        setPiece(findChild<QPushButton*>("Bishop"), ":/chess_pieces/resources/bishop_w.png");
        setPiece(findChild<QPushButton*>("Knight"), ":/chess_pieces/resources/knight_w.png");
        setPiece(findChild<QPushButton*>("Queen"), ":/chess_pieces/resources/queen_w.png");
    }

    findChild<QPushButton*>("Rook")->show();
    findChild<QPushButton*>("Knight")->show();
    findChild<QPushButton*>("Bishop")->show();
    findChild<QPushButton*>("Queen")->show();

    clickWait = true;
}

void MainWindow::handlePromotionClick() {
    clickWait = false;

    QPushButton* button = qobject_cast<QPushButton*>(sender());

    QIcon icon = button->icon();
    saved_button->setIcon(icon);
    saved_button->setIconSize(QSize(50, 50));

    string temp = saved_button->objectName().toStdString();
    char letter;
    int number;
    istringstream ss(temp);
    ss >> letter >> number;

    pair<int, int> coordinatesNN = chessArray.convert_to_NN(make_pair(letter, number));

    chessArray.handlePawnPromotion(ChessArray::chessPieces[coordinatesNN.second][coordinatesNN.first], button->objectName().toStdString());

    findChild<QPushButton*>("Rook")->hide();
    findChild<QPushButton*>("Knight")->hide();
    findChild<QPushButton*>("Bishop")->hide();
    findChild<QPushButton*>("Queen")->hide();

    saved_button = nullptr;
}

void MainWindow::on_pushButton_clicked() {

    chessArray.~ChessArray();
    new(&chessArray) ChessArray();

    turn = 'w';
    pieceSelected = false;
    clickWait = false;
    x = 9;
    y = 9;
    saved_button = nullptr;

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            char letter = 'A' + i;
            char number = '1' + j;
            QString coord;
            coord.append(letter);
            coord.append(number);

            findChild<QPushButton*>(coord)->setIcon(QIcon());
        }
    }

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            char letter = 'A' + i;
            char number = '1' + j;

            QString tile;
            tile.append(letter);
            tile.append(number);

            if((i + j) % 2 == 0) findChild<QPushButton*>(tile)->setStyleSheet("background-color: orange; ");
            else findChild<QPushButton*>(tile)->setStyleSheet("background-color: white; ");

        }
    }

    ui->moveLog->clear();

    setupChessPieces();
}

void MainWindow::logMessage(pair<int, int> old_coords, pair<int, int> new_coords) {

    string logMsg;

    char letter;
    int number;

    letter = chessArray.convert_to_LN(old_coords).first;
    number = chessArray.convert_to_LN(old_coords).second;

    logMsg = chessArray.getPiece(old_coords.first, old_coords.second)->getName() + ": " + letter;
    logMsg += ('0' + number);
    logMsg += " -> ";

    letter = chessArray.convert_to_LN(new_coords).first;
    number = chessArray.convert_to_LN(new_coords).second;

    logMsg += letter;
    logMsg += ('0' + number);

    QString newLog = QString::fromStdString(logMsg);

    ui->moveLog->append(newLog);
}

