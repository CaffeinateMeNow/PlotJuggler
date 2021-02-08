#pragma once

#include <QObject>
#include <QtPlugin>
#include "PlotJuggler/dataloader_base.h"
#include <QThread>
#include <fstream>
#include <QDebug>
#include <QObject>
#include <QProgressDialog>
#include <QtNetwork>

#include <unistd.h>
#include <bzlib.h>

#include <capnp/schema.h>
#include <capnp/dynamic.h>
#include <capnp/serialize-packed.h>
#include <capnp/schema-parser.h>

#include "../../../../../cereal/gen/cpp/log.capnp.h"
#include "../../../../clib/channel.hpp"
#include <thread>

using namespace PJ;

class FileReader : public QObject {

/* 
        Edits:
        - commented out URL functionality
        - adding bz2 file loading

*/

  Q_OBJECT

public:
  FileReader(const QString& file_);
  // void startRequest(const QUrl &url);                                                                    
  ~FileReader();
  virtual void readyRead();
  // void httpFinished();
  virtual void done() {};

public slots:
  void process();

protected:
  QFile* loaded_file;
  // QNetworkReply *reply;

private:
  // QNetworkAccessManager *qnam;                                                                           
  // QElapsedTimer timer;                                                                                   
  QString file;
};

typedef QMultiMap<uint64_t, cereal::Event::Reader> Events;

class LogReader : public FileReader {
Q_OBJECT
public:
  LogReader(const QString& file, Events *events_, QReadWriteLock* events_lock_, QMap<int, QPair<int, int> > *eidx_);
  ~LogReader();

  void readyRead();
  void done() { is_done = true; };
  bool is_done = false;

private:
  bz_stream bStream;

  // backing store
  QByteArray raw;

  std::thread *parser;
  int event_offset;
  channel<int> cdled;

  // global                                                                                              
  void mergeEvents(int dled);
  Events *events;
  QReadWriteLock* events_lock;
  QMap<int, QPair<int, int> > *eidx;
};

