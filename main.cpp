/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2022 by vfssoft. All rights reserved.                 *
 *                                                                         *
 *   http://vfssoft.com                                                    *
 *                                                                         *
 ***************************************************************************/
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <SevenSegmentDisplay.h>


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
  QGuiApplication app(argc, argv);
  
  qmlRegisterType<SevenSegmentDisplay>("my.controls", 1, 0, "SevenSegmentDisplay");
  
  
  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
      QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);
  engine.load(url);
  
  return app.exec();
}
