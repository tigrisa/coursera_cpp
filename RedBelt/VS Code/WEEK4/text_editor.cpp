#include <string>
#include <list>
#include <functional>

#include "../includes/test_runner.h"
#include "../includes/profile.h"

using namespace std;

using It = list<char>::iterator;

class Editor
{
public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor()
  {
    position = text.begin();
    ++position;
  };

  void Left()
  {
    if (position != text.begin())
      --position;
  }

  void Right()
  {
    if (position != text.end())
      ++position;
  }

  void Insert(char token)
  {
    text.insert(position, token);
  }

  void Cut(size_t tokens = 1)
  {
    LoopText(tokens, [this](It &cur_position) { buffer.push_back(*cur_position); cur_position =text.erase(cur_position); });
  }

  void Copy(size_t tokens = 1)
  {
    LoopText(tokens, [this](It &cur_position) { buffer.push_back(*cur_position); ++cur_position; });
  }

  void Paste()
  {
    for (char s : buffer)
    {
      Insert(s);
    }
  }

  string GetText() const
  {
    string res;
    for (char s : text)
    {
      res.push_back(s);
    };

    return res;
  }

private:
  void LoopText(size_t tokens, std::function<void(It &)> lambda)
  {
    size_t i = 0;
    buffer.clear();
    It cur_position = position;
    --position;
    while (cur_position != text.end() && i < tokens)
    {
      lambda(cur_position);
      ++i;
    }
    ++position;
  }

  list<char> text;
  It position;
  list<char> buffer;
};

void TypeText(Editor &editor, const string &text)
{
  for (char c : text)
  {
    editor.Insert(c);
  }
}

void TestEditing()
{
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for (size_t i = 0; i < text_len; ++i)
    {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for (size_t i = 0; i < text_len - first_part_len; ++i)
    {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse()
{
  Editor editor;

  const string text = "esreveR";
  for (char c : text)
  {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText()
{
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer()
{
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

int main()
{
  TestRunner tr;
  LOG_DURATION("Total tests duration");
  {
    // примерно 86 операций с текстом в тестах. 1000000/86 итераций для проверки быстродействия
    for (size_t i = 0; i < 14706; ++i)
    {
      RUN_TEST(tr, TestEditing);
      RUN_TEST(tr, TestReverse);
      RUN_TEST(tr, TestNoText);
      RUN_TEST(tr, TestEmptyBuffer);
    }
  }
  return 0;
}