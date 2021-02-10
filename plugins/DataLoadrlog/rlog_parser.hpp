#pragma once

#include <PlotJuggler/plotdata.h>
#include <PlotJuggler/messageparser_base.h>

#include <capnp/dynamic.h>

using namespace PJ;

enum LargeArrayPolicy : bool
{
  DISCARD_LARGE_ARRAYS = true,
  KEEP_LARGE_ARRAYS = false
};

class rlogMessageParser : MessageParser{

public:
  rlogMessageParser(const std::string& topic_name, PJ::PlotDataMapRef& plot_data):
    MessageParser(topic_name, plot_data) {}

  bool parseMessageImpl(const std::string& topic_name, capnp::DynamicValue::Reader node, double timestamp);

  bool parseMessage(const MessageRef serialized_msg, double timestamp);

protected:
  bool _use_message_stamp;

};


