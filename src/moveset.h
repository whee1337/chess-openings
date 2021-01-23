#ifndef MOVESET_H
#define MOVESET_H

#include <QPair>
#include<vector>
#include<QString>
#include<QStringList>
#include<QByteArray>
#include<QHash>
#include<QObject>


typedef QPair<int,int> movePair;
typedef QPair<movePair,movePair> turn;

class Move
{
 public:
    Move(movePair figure, movePair moveField);
    Move(QString figure, QString moveField);

    movePair getFigureField();
    movePair getNextField();

    static Move toMove(QString move);

private:
    static movePair toPair(QString movePair);
    static int letterToInt(QString letter);

    movePair m_targetFigure;
    movePair m_moveField;
};

class Turn{
public:
    Turn(Move white , Move black);
    Turn(QString moveWhite, QString moveBlack);

    Move getBlackMove();
    Move getWhiteMove();

    /*
     *
     * Format -> h1h2,h3h5
     */
    static Turn toTurn(QString turn);

private:
    Move m_whiteMove;
    Move m_blackMove;
};

class PlaySet
{
public:
    PlaySet(QString m_filename, QString prefix);

Move getMove(int i);
bool autoMove(bool whitesMove);

bool isAutoMoveActive();
void importMoveList(QStringList moveList);
QString name();
QString getFilename();


private:
std::vector<Turn> turns;

bool m_autoMove = true;
bool m_PlayingAsBlack = true;

QString m_filename ="";
QString m_qrcPrefix ="";

};

#endif // MOVESET_H
