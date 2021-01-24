#pragma once
#include <QAbstractListModel>
#include <QVector>
#include <QString>
#include <QModelIndex>
#include <QVariant>
#include "moveset.h"

#include "gameengine.hpp"

class MoveSetListModel : public QAbstractListModel
{

    Q_OBJECT


public:
    enum MoveSetRoles {
        NameRole = Qt::UserRole + 1,
        HighlightRole = Qt::UserRole,
    };

    Q_INVOKABLE void onClickedModel(int number);

    MoveSetListModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex&) const { return backing.size(); }
    virtual QVariant data(const QModelIndex &index, int role) const;

    QHash<int, QByteArray> roleNames() const;

    void setGameEngine(GameEngine* ge);
private:
    QVector<PlaySet*> backing;
    GameEngine* m_gameEngine;
};
