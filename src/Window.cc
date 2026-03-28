#include "Window.hh"

#include <unistd.h>

#include <cstdio>
#include <cstring>
#include <cstdarg>

Window::Window() {}

Window::Window(int id, const char *name, int width, int height, int x, int y) {
  m_id = id;
  memset(m_name, 0, sizeof(m_name));
  strcpy(m_name, name);
  m_width = width;
  m_height = height;
  m_x = x;
  m_y = y;
}

Window::~Window() {}

void Window::SetBufStr(const char *format, ...) {
  memset(m_buf, 0, 4096);
  va_list args;
  va_start(args, format);
  vsnprintf(m_buf, 4096, format, args);
  va_end(args);
}

void Window::SetBufFd(int fd, char *begin) {
  memset(m_buf, 0, 4096);
  read(fd, m_buf, 4096);
}

void Window::PrintBuf() {
  for (int line = 0; line < m_height; ++line) {
    MoveCursor(m_x, m_y + line);
    write(STDOUT_FILENO, m_buf + line * m_width, m_width);
  }
}

void Window::PrintStr(const char *format, ...) {
  char buf[4096] {0};
  char *ptr = nullptr;

  va_list args;
  va_start(args, format);
  vsnprintf(buf, 4096, format, args);
  va_end(args);

  for (ptr = buf; ptr - buf < strlen(buf); ++ptr) {
    printf("%.*s\n", m_width, ptr + 1);
  }
}

void Window::MoveCursor(int x, int y) {
  char buf[32];
  int len = snprintf(buf, sizeof(buf), "\033[%d;%dH", x, y);
  write(1, buf, len);
}
