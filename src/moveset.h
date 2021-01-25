#ifndef MOVESET_H
#define MOVESET_H

#include <QPair>
#include<vector>
#include<QString>
#include<QStringList>
#include<QByteArray>
#include<QHash>
#include<QObject>


typedef QPair<int,int> coordinates;
//typedef QPair<coordinates,coordinates> turn;

class Move
{
 public:
    Move(coordinates figure, coordinates moveField);
    Move(QString figure, QString moveField);

    coordinates getFigureField();
    coordinates getNextField();

    static Move toMove(QString move);

private:
    static coordinates toPair(QString coordinates);
    static int letterToInt(QString letter);

    coordinates m_targetFigure;
    coordinates m_moveField;
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

Move getMove(int i,bool whiteTurn);
bool autoMove(bool whitesMove, int numberOfTurn);

bool isAutoMoveActive();
void setMoveList(QStringList moveList);
QString name();
QString getFilename();

void setPlayingAsWhite(bool playingAsWhite);
bool getPlayingAsWhite();

bool isTurnListempty();

bool getHighlighted() const;
void setHighlighted(bool highlighted);

private:
std::vector<Turn> m_turnSet;

bool m_autoMove = true;
bool m_PlayingAsWhite = true;

QString m_filename ="";
QString m_qrcPrefix ="";

bool m_highlighted = false;

};

#endif // MOVESET_H
