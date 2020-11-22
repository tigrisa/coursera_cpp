#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
using namespace std;

class Stats
{
public:
  void AddMethod(string_view method);
  void AddUri(string_view uri);
  const map<string_view, int> &GetMethodStats() const;
  const map<string_view, int> &GetUriStats() const;

  Stats();

private:
  map<string_view, int> methods;
  map<string_view, int> uris;

  array<string, 5> available_methods = {"GET", "POST", "PUT", "DELETE", "UNKNOWN"};
  array<string, 6> available_uris = {"/", "/order", "/product", "/basket", "/help", "unknown"};
};

HttpRequest ParseRequest(string_view line);
