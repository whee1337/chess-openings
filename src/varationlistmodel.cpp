#include "varationlistmodel.h"
#include<QHash>
#include "movesetfactory.h"
#include<iostream>
MoveSetListModel::MoveSetListModel(QObject *parent)
{
     backing = MoveSetFactory::instance().getMoveVariationList();
}


QHash<int, QByteArray> MoveSetListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";

    return roles;
}

QVariant MoveSetListModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) {
        return QVariant();
    }
    if(role == NameRole) {
        return QVariant(backing[index.row()]->name());
    }

    return QVariant();
}


void MoveSetListModel::onClickedModel(int number)
{
    PlaySet* mv = backing[number];
    std::cout<<"clicked c++ : "<<number<< " file: " << backing[number]->name().toStdString() <<std::endl;

    MoveSetFactory::instance().readMoves(mv);

    PlaySet mvTemp("","");
    m_gameEngine->resetWithMoveSet(mvTemp);
}


void MoveSetListModel::setGameEngine(GameEngine* ge)
{
    m_gameEngine = ge;
}
