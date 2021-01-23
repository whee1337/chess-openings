/**
 *
 *
 *
 */

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <gameengine.hpp>
#include <moveset.h>

#include "varationlistmodel.h"
#include "movesetfactory.h"


/// Default programm running
int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  QQmlApplicationEngine engine;

//#ifdef QT_DEBUG
  engine.rootContext()->setContextProperty("debug", true);
//#else
 // engine.rootContext()->setContextProperty("debug", false);
//#endif


  GameEngine* ge;
  engine.rootContext()->setContextProperty("GameEngine", ge = new GameEngine);

  MoveSetListModel* dm;
  engine.rootContext()->setContextProperty("DemoModel", dm = new MoveSetListModel);

  dm->setGameEngine(ge);

  engine.load(QUrl(QStringLiteral("qrc:/qt-chess/qml/Window.qml")));

  MoveSetFactory::instance().getMoveVariationList();

  return app.exec();
}
