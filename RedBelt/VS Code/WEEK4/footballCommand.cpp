#include <list>
#include <algorithm>
#include <array>

#include "../includes/profile.h"

constexpr size_t ARRAY_SIZE = 100000;

using namespace std;
int main()
{
    LOG_DURATION("TOTAL");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    size_t query_count;
    cin >> query_count;

    list<uint16_t> players;
    array<list<uint16_t>::iterator, ARRAY_SIZE> iters;
    iters.fill(players.end());

    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        int user_id;
        cin >> user_id;
        int prev;
        cin >> prev;
        auto pos = iters[prev];
        iters[user_id] = players.insert(pos, user_id);
    }

    cout << endl;
    for (auto item : players)
    {
        cout << item << "\n";
    }
}