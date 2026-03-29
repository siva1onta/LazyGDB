#include "Window.hh"
#include "Utils.hh"

#include <unistd.h>

#include <cstdio>
#include <cstring>
#include <cstdarg>

Window::Window() {}

void Window::Init(int id, const char *name, int width, int height, int x, int y) {
  m_id = id;
  memset(m_name, 0, sizeof(m_name));
  strcpy(m_name, name);
  m_width = width;
  m_height = height;
  m_x = x;
  m_y = y;
}

void Window::SetSize(int width, int height) {
  m_width = width;
  m_height = height;
}

void Window::SetPos(int x, int y) {
  m_x = x;
  m_y = y;
}

Window::~Window() {}

void Window::SetBufStr(const char *format, ...) {
  memset(m_buf, 0, BUFFERSIZE);
  va_list args;
  va_start(args, format);
  vsnprintf(m_buf, BUFFERSIZE, format, args);
  va_end(args);
}

void Window::SetBufFd(int fd, char *begin) {
  memset(m_buf, 0, BUFFERSIZE);
  read(fd, m_buf, BUFFERSIZE);
}

void Window::PrintBuf() {
  PrintBnd();
  for (int line = 0; line < m_height; ++line) {
    MoveCursor(m_x + line, m_y);
    write(STDOUT_FILENO, m_buf + line * m_width, m_width);
  }
}

void Window::PrintStr(const char *format, ...) {
  PrintBnd();
  char buf[BUFFERSIZE] {0};

  va_list args;
  va_start(args, format);
  vsnprintf(buf, BUFFERSIZE, format, args);
  va_end(args);

  for (int line = 0; line < m_height; ++line) {
    MoveCursor(m_x + line, m_y);
    write(STDOUT_FILENO, buf + line * m_width, m_width);
  }
}

void Window::PrintBnd() {
  char buf[BUFFERSIZE];

  buf[0] = '+';
  buf[m_width + 1] = '+';
  for (int id = 0; id < m_width; ++id) {
    buf[id + 1] = '-';
  }
  MoveCursor(m_x - 1, m_y - 1);
  write(STDOUT_FILENO, buf, m_width + 2);
  MoveCursor(m_x + m_height, m_y - 1);
  write(STDOUT_FILENO, buf, m_width + 2);

  buf[0] = '|';
  buf[m_width + 1] = '|';
  for (int id = 0; id < m_width; ++id) {
    buf[id + 1] = ' ';
  }
  for (int id = 0; id < m_height; ++id) {
    MoveCursor(m_x + id, m_y - 1);
    write(STDOUT_FILENO, buf, m_width + 2);
  }
}
