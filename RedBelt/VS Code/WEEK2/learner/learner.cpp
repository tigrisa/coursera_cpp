#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../../includes/profile.h"

using namespace std;

/*
EXAMPLE BAD CODE
class Learner {
 private:
  vector<string> dict;

 public:
  int Learn(const vector<string>& words) {
    int newWords = 0;
    for (const auto& word : words) {
      if (find(dict.begin(), dict.end(), word) == dict.end()) {
        ++newWords;
        dict.push_back(word);
      }
    }
    return newWords;
  }

  vector<string> KnownWords() {
    sort(dict.begin(), dict.end());
    dict.erase(unique(dict.begin(), dict.end()), dict.end());
    return dict;
  }
};
*/

class Learner
{
private:
  vector<string> dict;

public:
  // for opportunity to use lower_bound instead find
  // I insert new words in increasing order to create
  // sorted vector
  int Learn(const vector<string> &words)
  {
    int newWords = 0;
    for (const auto &word : words)
    {
      auto it = lower_bound(dict.begin(), dict.end(), word);
      if (it != dict.end())
      {
        if (*it != word)
        {
          ++newWords;
          dict.insert(it, word);
        }
      }
      else
      {
        if (dict.size() == 0 || *(--it) != word)
        {
          ++newWords;
          dict.push_back(word);
        }
      }
    }
    return newWords;
  }

  // No need anymore for sort and unique
  vector<string> KnownWords()
  {
    //LOG_DURATION("SORT")
    //sort(dict.begin(), dict.end());
    //dict.erase(unique(dict.begin(), dict.end()), dict.end());
    return dict;
  }
};

int main()
{
  LOG_DURATION("TOTAL")
  Learner learner;
  string line;
  ifstream myfile;
  myfile.open("words.txt");
  {
    LOG_DURATION("LEARN");
    while (getline(myfile, line))
    {
      vector<string> words;
      stringstream ss(line);
      string word;
      while (ss >> word)
      {
        words.push_back(word);
      }

      cout << learner.Learn(words) << "\n";
    }
  }
  cout << "=== known words ===\n";
  for (auto word : learner.KnownWords())
  {
    cout << word << "\n";
  }

  return 0;
}
