#include "../includes/test_runner.h"
#include "../includes/profile.h"

#include <vector>
#include <list>
#include <algorithm>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
// template <typename Token>
// vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens)
// {
//   vector<Sentence<Token>> res;
//   list<Token> list_tokens;
//   for (auto &s : tokens)
//     list_tokens.push_back(move(s));

//   auto it = list_tokens.begin();
//   while (it != list_tokens.end())
//   {
//     Sentence<Token> sentence;
//     while (it != list_tokens.end() && !it->IsEndSentencePunctuation())
//     {
//       sentence.push_back(move(*it));
//       it = list_tokens.erase(it);
//     }
//     while (it != list_tokens.end() && it->IsEndSentencePunctuation())
//     {
//       sentence.push_back(move(*it));
//       it = list_tokens.erase(it);
//     }
//     res.push_back(move(sentence));
//   }

//   return move(res);
// }

// template <typename Token>
// vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens)
// {
//   vector<Sentence<Token>> res;

//   auto it = tokens.begin();
//   while (it != tokens.end())
//   {
//     Sentence<Token> sentence;
//     while (it != tokens.end() && !it->IsEndSentencePunctuation())
//     {
//       sentence.push_back(move(*it));
//       ++it;
//     }
//     while (it != tokens.end() && it->IsEndSentencePunctuation())
//     {
//       sentence.push_back(move(*it));
//       ++it;
//     }
//     res.push_back(move(sentence));
//   }

//   return res;
// }

template <typename TokenForwardIt>
TokenForwardIt FindSentenceEnd(TokenForwardIt tokens_begin, TokenForwardIt tokens_end)
{
  const TokenForwardIt before_sentence_end = adjacent_find(tokens_begin, tokens_end, [](const auto &left_token, const auto &right_token) {
    return left_token.IsEndSentencePunctuation() && !right_token.IsEndSentencePunctuation();
  });
  return before_sentence_end == tokens_end ? tokens_end : next(before_sentence_end);
}

template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens)
{
  vector<Sentence<Token>> sentences;

  auto tokens_begin = begin(tokens);
  const auto tokens_end = end(tokens);

  while (tokens_begin != tokens_end)
  {
    const auto sentence_end = FindSentenceEnd(tokens_begin, tokens_end);
    Sentence<Token> sentence;
    for (; tokens_begin != sentence_end; ++tokens_begin)
    {
      sentence.push_back(move(*tokens_begin));
    }
    sentences.push_back(move(sentence));
  }

  return sentences;
}

struct TestToken
{
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const
  {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken &other) const
  {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream &operator<<(ostream &stream, const TestToken &token)
{
  return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting()
{
  ASSERT_EQUAL(

      SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
      vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!"}}}));

  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
      vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!", true}}}));

  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}, {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
      vector<Sentence<TestToken>>({
          {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"!", true}},
          {{"Without"}, {"copies"}, {".", true}},
          {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"!", true}},
          {{"Without"}, {"copies"}, {".", true}},
      }));
}

vector<TestToken> GenerateHeavyTokens()
{
  vector<TestToken> res;
  for (size_t i = 0; i < 500000; ++i)
  {
    res.push_back(TestToken{"Split"});
    res.push_back(TestToken{"!", true});
  }

  return res;
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  vector<TestToken> heavy = GenerateHeavyTokens();
  vector<Sentence<TestToken>> res;
  LOG_DURATION("heavy")
  {
    res = SplitIntoSentences(move(heavy));
  }
  size_t s = res.size();
  return 0;
}
