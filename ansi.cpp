#include "ansi.h"
#include <string>
#include <iostream>

using namespace std;

string ansi::cursor::home()
{
  return "\033[H";
}

string ansi::cursor::pos(unsigned short row, unsigned short col)
{
  return "\033[" + to_string(row) + ';' + to_string(col) + 'H';
}

string ansi::cursor::up(unsigned short pos)
{
  return "\033[" + to_string(pos) + 'A';
}

string ansi::cursor::down(unsigned short pos)
{
  return "\033[" + to_string(pos) + 'B';
}

string ansi::cursor::left(unsigned short pos)
{
  return "\033[" + to_string(pos) + 'D';
}

string ansi::cursor::right(unsigned short pos)
{
  return "\033[" + to_string(pos) + 'C';
}

string ansi::cursor::save()
{
  return "\033 7";
}

string ansi::cursor::restore()
{
  return "\033 8";
}

string ansi::erase::cursor_to_end()
{
  return "\033[0J";
}

string ansi::erase::cursor_to_start()
{
  return "\033[1J";
}

string ansi::erase::display()
{
  return "\033[2J";
}

string ansi::erase::saved_line()
{
  return "\033[3J";
}

string ansi::erase::to_eol()
{
  return "\033[0K";
}

string ansi::erase::to_sol()
{
  return "\033[1K";
}

string ansi::erase::line()
{
  return "\033[2K";
}

string ansi::graphic::reset()
{
  return "\033[0m";
}

string ansi::graphic::bold(bool value)
{
  if(value)
    return "\033[1m";
  else
    return "\033[22m";

}

string ansi::graphic::faint(bool value)
{
  return "\033[" + value ? "2m" : "22m";
}

string ansi::graphic::italic(bool value)
{
  return "\033[" + value ? "3m" : "23m";
}

string ansi::graphic::underline(bool value)
{
  return "\033[" + value ? "4m" : "24m";
}

string ansi::graphic::blink(bool value)
{
  return "\033[" + value ? "5m" : "25m";
}

string ansi::graphic::inverse(bool value)
{
  return "\033[" + value ? "7m" : "27m";
}

string ansi::graphic::hidden(bool value)
{
  return "\033[" + value ? "8m" : "28m";
}

string ansi::graphic::strike(bool value)
{
  return "\033[" + value ? "9m" : "29m";
}

string ansi::graphic::bg(unsigned char r, unsigned char g, unsigned char b)
{
  return "\033[48;2;" + to_string(r) + ';' + to_string(g) + ';' + to_string(b) + 'm';
}

string ansi::graphic::bg(unsigned char id)
{
  return "\033[48;5;" + to_string(id) + 'm';
}

string ansi::graphic::bg()
{
  return "\033[49m";
}

string ansi::graphic::fg(unsigned char r, unsigned char g, unsigned char b)
{
  return "\033[38;2;" + to_string(r) + ';' + to_string(g) + ';' + to_string(b) + 'm';
}

string ansi::graphic::fg(unsigned char id)
{
  return "\033[38;5;" + to_string(id) + 'm';
}

string ansi::graphic::fg()
{
  return "\033[39m";
}
