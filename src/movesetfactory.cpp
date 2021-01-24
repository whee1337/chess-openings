#include "movesetfactory.h"

#include <QDirIterator>
#include <QDebug>

MoveSetFactory::MoveSetFactory()
{

}


QVector<PlaySet*> MoveSetFactory::getMoveVariationList()
{

    QVector<PlaySet*> results;
    QString prefix = ":/movesets/";
    QDirIterator it(prefix, QDirIterator::Subdirectories);
    int i =0;
    while (it.hasNext()) {
        results.append(new PlaySet(it.next(),prefix));
        i++;
    }

    return results;
}

void MoveSetFactory::readMoves(PlaySet* mv)
{
    QStringList stringList;

    QString fileName(mv->getFilename());
    QFile textFile(fileName);

    qDebug()<<"Try open file: "<< fileName ;


    if(!textFile.open(QIODevice::ReadOnly)) {
        qDebug()<<"filenot opened";
    }
    else
    {
        QTextStream textStream(&textFile);
        while (true)
        {
            QString line = textStream.readLine();
            if (line.isNull())
                break;
            else
                stringList.append(line);
        }
        mv->setMoveList(stringList);
    }

    textFile.close();
    int i = 0;
    for(auto const &s : stringList)
    {
        qDebug()<<"Gelesene Daten aus Datei:" <<s << " " << i;
        i++;
    }
}
