#include "moveset.h"

#include<QStringList>
#include<QDebug>

Move::Move(movePair figure, movePair targetField) : m_targetFigure(figure), m_moveField(targetField)
{

}

movePair Move::getFigureField()
{
    return m_targetFigure;
}

movePair Move::getNextField()
{
    return m_moveField;
}

/*
 * Format = StartField -> e4 | EndField -> a4 = e4a4
 *
*/
Move Move::toMove(QString text)
{
    QString figure = text.left(2);
    QString field = text.mid(2);

    return Move(toPair(figure), toPair(field));
}

movePair Move::toPair(QString text)
{
    QString letterX = text.left(1);
    QString posY = text.mid(1);

    return movePair(posY.toInt(), letterToInt(letterX));
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

PlaySet::PlaySet(QString m_filename, QString prefix) : m_filename(m_filename),m_qrcPrefix(prefix)
{
//    Move move1(movePair(7,7),movePair(6,7));
//    Move move2(movePair(7,1),movePair(6,1));
//    Move move3(Move::toMove("h7h6"));

//    moves_CPU.push_back(move1);
//    moves_CPU.push_back(move2);
//    moves_CPU.push_back(move3);
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

void PlaySet::importMoveList(QStringList moveList)
{

}

bool PlaySet::autoMove(bool whitesMove)
{
    if(!isAutoMoveActive())
        return false;

    if(m_PlayingAsBlack)
        return !whitesMove;

    return whitesMove;
}

Move PlaySet::getMove(int i)
{
   Move::toMove("asd");
}
