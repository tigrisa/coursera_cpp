#include "http_request.h"
#include "stats.h"

#include <map>
#include <string_view>
#include <algorithm>

using namespace std;

Stats::Stats()
{
    for (const string &m : available_methods)
        methods[m] = 0;
    for (const string &u : available_uris)
        uris[u] = 0;
}

void Stats::AddMethod(string_view method)
{
    auto key = find(available_methods.begin(), available_methods.end() - 1, method);
    if (key != available_methods.end())
        ++methods[*key];
    else
        ++methods[available_methods[available_methods.size() - 1]];
}

void Stats::AddUri(string_view uri)
{
    auto key = find(available_uris.begin(), available_uris.end() - 1, uri);
    if (key != available_uris.end())
        ++uris[*key];
    else
        ++uris[available_uris[available_uris.size() - 1]];
}

const map<string_view, int> &Stats::GetMethodStats() const
{
    return methods;
}

const map<string_view, int> &Stats::GetUriStats() const
{
    return uris;
}

string_view find_space(string_view &line)
{
    string_view res;
    size_t pos = line.find_first_of(' ');
    res = line.substr(0, pos == line.npos ? line.size() : pos);
    if (pos + 1 < line.size())
        line.remove_prefix(pos + 1);

    return res;
}

HttpRequest ParseRequest(string_view line)
{
    HttpRequest req;
    size_t pos = line.find_first_not_of(' ');
    if (pos > 0)
        line.remove_prefix(pos == line.npos ? line.size() : pos);
    if (line.size())
    {
        req.method = find_space(line);
        req.uri = find_space(line);
        req.protocol = find_space(line);
    }

    return req;
}
