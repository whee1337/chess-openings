#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QList>
#include <QQmlContext>
#include <QQmlEngine>
#include <QtQml>

#include <figurebishop.hpp>
#include <figureking.hpp>
#include <figureknight.hpp>
#include <figurepawn.hpp>
#include <figurequeen.hpp>
#include <figurerook.hpp>

#include <chessmodel.hpp>
#include <historymodel.hpp>

#include "gameengine.hpp"
#include "movepoints.hpp"

GameEngine::GameEngine(QObject *parent)
    : QObject(parent),
      m_history(new HistoryModel(this)),
      m_figures(new ChessModel(this)),
      m_isWhite(true),
      m_lastClick(nullptr),
       m_moveset(new PlaySet("","")){

  qmlRegisterUncreatableType<FigureIntf>("com.znocpmp.chess", 1, 0, "Figure",
                                         "");
  qmlRegisterType<ChessModel>("com.znocpmp.chess", 1, 0, "ChessModel");
}

GameEngine::~GameEngine() {}

void GameEngine::setupBoard() {

  m_numberOfTurn = 0;
  m_isWhite = true;

  resetBoard();

  for (int row = 0; row < 2; row++) {
    FigureIntf::Color color = row == 0 ? FigureIntf::Black : FigureIntf::White;
    int place = 8 - 7 * row;

    // Pawns
    for (int count = 1; count < 9; count++)
      m_figures->addFigure(
          new FigurePawn(place + (row == 0 ? -1 : 1), count, color));

    // Rooks
    m_figures->addFigure(new FigureRook(place, 1, color));
    m_figures->addFigure(new FigureRook(place, 8, color));

    // Bishops
    m_figures->addFigure(new FigureBishop(place, 3, color));
    m_figures->addFigure(new FigureBishop(place, 6, color));

    // Knights
    m_figures->addFigure(new FigureKnight(place, 2, color));
    m_figures->addFigure(new FigureKnight(place, 7, color));

    // Queen
    m_figures->addFigure(new FigureQueen(place, 4, color));

    // King
    m_figures->addFigure(new FigureKing(place, 5, color));
  }

  startGame();
}

void GameEngine::resetBoard()
{
    for(int i=1;i<10;i++)
    {
        for(int n=1;n<10;n++)
        {
            m_figures->removeAt(i,n);
        }
    }
}


void GameEngine::startGame()
{
    if(!m_moveset->getPlayingAsWhite() && !m_moveset->isTurnListempty())
   {
        doMove(m_moveset->getMove(m_numberOfTurn,true));
        m_isWhite = false;
    }
}

void GameEngine::doAutoMove()
{
    qDebug()<<"Do auto move";
   // itemClicked(2,2);
   // itemClicked();

    FigureIntf *item = m_figures->getFigure(2,2);
    item->moveTo(3,2);

    m_figures->rmHitSpot();

}

void GameEngine::doMove(Move move)
{
    coordinates figureField =move.getFigureField();
    coordinates nextField = move.getNextField();

    FigureIntf *item = m_figures->getFigure(figureField.first,figureField.second);

    m_figures->removeAt(nextField.first,nextField.second);
    item->moveTo(nextField.first,nextField.second);

    m_figures->rmHitSpot();
}


void GameEngine::clean() {
  m_figures->erase();
}

void GameEngine::save() {}

void GameEngine::load() {}

void GameEngine::move() {}

QObject *GameEngine::figures() {
  return m_figures;
}

QObject *GameEngine::history() {
  return m_history;
}

void GameEngine::itemClicked(coordinates move)
{
    itemClicked(move.first,move.second);
}

void GameEngine::itemClicked(uint x, uint y) {
  FigureIntf *item = m_figures->getFigure(x, y);

  if (m_lastClick != nullptr) {
    if (m_lastClick->moveList().indexOf(QPair<uint, uint>(x, y)) != -1) {

      auto expMove = m_moveset->getExpectedMove(m_numberOfTurn);

      if(expMove.getNextField() != coordinates(x,y))
      {
          m_lastClick = nullptr;
          turnDone(false);
          return;
      }

      turnDone(true);


      m_figures->removeAt(x, y);
      m_lastClick->moveTo(x, y);

      // Clean all up
      // next side to move
      m_isWhite = !m_isWhite;
      m_lastClick = nullptr;
      m_figures->rmHitSpot();

      m_numberOfTurn++;

      if(m_moveset!= nullptr && m_moveset->autoMove(m_isWhite, m_numberOfTurn))
      {
          qDebug() << "start automove";

          auto nextMove = m_moveset->getMove(m_numberOfTurn, m_isWhite);
         //itemClicked(nextMove.getFigureField());
          doMove(nextMove);
          m_isWhite = !m_isWhite;
      }
    } else if (m_lastClick->side() == item->side()) {
      m_lastClick = nullptr;
      m_figures->rmHitSpot();
      itemClicked(x, y);
    }
    }
  // Moves order
  else if ((item->side() == FigureIntf::Black) ^ m_isWhite) {
    item->defMoveList()->clear();
    qDebug() << "else if ";
    setFigureWays(item);
    m_lastClick = item;
  }
}


void GameEngine::setFigureWays(FigureIntf *figure) {
  qDebug() << "loading ways to move";

  MovePoints *points = figure->defMoveList();

  if (points->isEmpty()) {
    QListIterator<QPair<uint, uint> > iterList(points->moves());

    while (iterList.hasNext()) {
      QPair<uint, uint> point = iterList.next();

      FigureIntf *pFigure = m_figures->getFigure(point.first, point.second);

      if (!pFigure)
        points->append(point, MovePoints::Empty);
      else if (pFigure->side() == figure->side())
        points->append(point, MovePoints::Friendly);
      else
        points->append(point, MovePoints::Enemy);
    }
  }

  m_figures->addHitSpot(points->moveList());
}


void GameEngine::resetWithMoveSet(PlaySet *ms)
{
    if(m_moveset!=nullptr)
    {
        ms->setPlayingAsWhite(m_moveset->getPlayingAsWhite());
    }

    m_moveset = ms;
    setupBoard();
}

void GameEngine::setPlayingAsWhite(bool playinAsWhite)
{
    this->m_moveset->setPlayingAsWhite(playinAsWhite);
    setupBoard();
}

