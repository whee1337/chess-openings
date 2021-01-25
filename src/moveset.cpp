#include "moveset.h"

#include<QStringList>
#include<QDebug>

Move::Move(coordinates figure, coordinates targetField) : m_targetFigure(figure), m_moveField(targetField)
{

}

coordinates Move::getFigureField()
{
    return m_targetFigure;
}

coordinates Move::getNextField()
{
    return m_moveField;
}

/*
 * Format = e4a4
 * StartField -> e4 | EndField -> a4
 *
*/
Move Move::toMove(QString text)
{
    QString figure = text.left(2);
    QString field = text.mid(2);

    return Move(toPair(figure), toPair(field));
}

coordinates Move::toPair(QString text)
{
    QString letterX = text.left(1);
    QString posY = text.mid(1);

    return coordinates(posY.toInt(), letterToInt(letterX));
}

 int Move::letterToInt(QString string)
 {
     QString letter = string.toLower();

    if(letter == "a")
        return 1;
    if(letter == "b")
        return 2;
    if(letter == "c")
        return 3;
    if(letter == "d")
        return 4;
    if(letter == "e")
        return 5;
    if(letter == "f")
        return 6;
    if(letter == "g")
        return 7;
    if(letter == "h")
        return 8;

    qDebug()<<"Wrong letter. Cant convert to coordinate";

    return 0;
 }

Turn::Turn(Move white , Move black) : m_whiteMove(white), m_blackMove(black)
{

}

Turn Turn::toTurn(QString str)
  {
     QStringList moveList = str.split(",");

     return Turn(Move::toMove(moveList.at(0)),Move::toMove(moveList.at(1)));
  }

 Move Turn::getBlackMove()
 {
     return m_blackMove;
 }

 Move Turn::getWhiteMove()
 {
     return m_whiteMove;
 }

PlaySet::PlaySet(QString m_filename, QString prefix) : m_filename(m_filename),m_qrcPrefix(prefix)
{
}

QString PlaySet::name()
{
    return QString(this->m_filename).remove(m_qrcPrefix);
}

QString PlaySet::getFilename()
{
    return this->m_filename;
}

bool PlaySet::isAutoMoveActive()
{
    return m_autoMove;
}

void PlaySet::setMoveList(QStringList moveList)
{
    if(moveList.isEmpty())
        return;

    for(QString const &str : moveList)
    {
        if(str.isNull() || str.isEmpty())
            continue;
        m_turnSet.push_back(Turn::toTurn(str));
    }
}

bool PlaySet::autoMove(bool whitesMove, int numberOfTurn)
{
    if(!isAutoMoveActive())
        return false;

    if(isTurnListempty())
        return false;

    if(m_turnSet.size() <= numberOfTurn)
        return false;

    if(m_PlayingAsWhite)
        return !whitesMove;
    else
        return whitesMove;
}

bool PlaySet::isTurnListempty()
{
    if(m_turnSet.empty())
        return true;

    return false;
}

bool PlaySet::getHighlighted() const
{
    return m_highlighted;
}

void PlaySet::setHighlighted(bool highlighted)
{
    m_highlighted = highlighted;
}

Move PlaySet::getMove(int i,bool whiteTurn)
{
    Turn turn = m_turnSet.at(i);

    if(whiteTurn)
        return turn.getWhiteMove();
    else
        return turn.getBlackMove();
}

void PlaySet::setPlayingAsWhite(bool playingAsWhite)
{
    m_PlayingAsWhite = playingAsWhite;
}

bool PlaySet::getPlayingAsWhite()
{
    return m_PlayingAsWhite;
}
