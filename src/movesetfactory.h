#pragma once
#include"moveset.h"

class MoveSetFactory
{
public:
    static MoveSetFactory& instance()
    {
        static MoveSetFactory _instance;
        return _instance;
    }
    ~MoveSetFactory(){};

    QVector<PlaySet*> getMoveVariationList();
    void readMoves(PlaySet *mv);

private:
       MoveSetFactory();
       MoveSetFactory(const MoveSetFactory&);
       MoveSetFactory & operator = (const MoveSetFactory&);
};

