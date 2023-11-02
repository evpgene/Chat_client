#pragma once
#include "ReceivedType.h"
#include <string>

struct ReceivedData {
  ReceivedData(ReceivedType type, const std::string_view& str_view)
      : _type(type), _str_view(str_view){};
  ~ReceivedData(){};
  ReceivedType _type;
  std::string_view _str_view;
};
