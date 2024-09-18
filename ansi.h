#pragma once
#include <string>

using std::string;

class ansi
{
  public:
  class cursor
  {
    public:
    static string home();
    static string pos(unsigned short row, unsigned short col); // set position
    static string up(unsigned short pos);
    static string down(unsigned short pos);
    static string left(unsigned short pos);
    static string right(unsigned short pos);
    static string save();
    static string restore();
  };

  class erase
  {
    public:
    static string cursor_to_end();
    static string cursor_to_start();
    static string display();
    static string saved_line();
    static string to_eol();
    static string to_sol();
    static string line(); // erase current line
  };

  class graphic
  {
    public:
    static string reset();
    static string bold(bool value = false);
    static string faint(bool value = false);
    static string italic(bool value = false);
    static string blink(bool value = false);
    static string underline(bool value = false);
    static string inverse(bool value = false);
    static string hidden(bool value = false);
    static string strike(bool value = false);
    static string bg(unsigned char r, unsigned char g, unsigned char b);
    static string bg(unsigned char id);
    static string bg();
    static string fg(unsigned char r, unsigned char g, unsigned char b);
    static string fg(unsigned char id);
    static string fg();
  };
};
