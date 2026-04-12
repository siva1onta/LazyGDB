#include "Window.h"

#include <unistd.h>

#include <cstdio>
#include <cstring>
#include <cstdarg>

#include "Ulogger.h"

Window::Window(int id, const char *name) {
  m_id = id;
  memset(m_name, 0, sizeof(m_name));
  memcpy(m_name, name, sizeof(m_name));
  m_floatwindow = nullptr;
  m_size = 0;
  m_firstline = 0;
  m_focusline = 0;
  m_active = false;
}

Window::~Window() {}

void Window::SetSizePos(int height, int width, int x, int y) {
  m_height = height;
  m_width = width;
  m_x = x;
  m_y = y;
}

void Window::SetActive(bool active) {
  m_active = active;
}

void Window::SetBufStr(const char *format, ...) {
  memset(m_buf, 0, MAXSIZE);
  va_list args;
  va_start(args, format);
  m_size = vsnprintf(m_buf, MAXSIZE, format, args);
  va_end(args);

  DivideBuf();
  m_firstline = 0;
  m_focusline = 0;
}

void Window::SetBufFd(int fd) {
  memset(m_buf, 0, MAXSIZE);
  m_size = read(fd, m_buf, MAXSIZE);

  DivideBuf();
  m_firstline = 0;
  m_focusline = 0;
}

void Window::Print() {
  PrintBnd();
  PrintNum();
  PrintBuf();
  if (m_floatwindow->GetActive()) {
    m_floatwindow->Print();
  }
}

bool Window::CommandChar(char cmd) {
  switch (cmd) {
    case 'j' :
      MoveDown(1);
      return true;
    case 10 :
      MoveDown(5);
      return true;
    case 'k' :
      MoveUp(1);
      return true;
    case 11 :
      MoveUp(5);
      return true;
    default :
      return false;
  }
}

int Window::GetId() const {
  return m_id;
}

bool Window::GetActive() const {
  return m_active;
}

Window *Window::GetFloatWindow() {
  return m_floatwindow;
}

void Window::MoveCursor(int x, int y) {
  char buf[MAXCOLUME];
  int len = snprintf(buf, sizeof(buf), "\033[%d;%dH", x + m_x, y + m_y);
  write(STDOUT_FILENO, buf, len);
}

void Window::DivideBuf() {
  m_line = 0;
  m_offset.clear();
  m_length.clear();
  m_truthline.clear();
  m_subline.clear();

  int offset = 0, length = 0, truthline = 1, subline = 0;

  while (offset < m_size) {
    ++m_line;
    m_offset.push_back(offset);
    m_truthline.push_back(truthline);
    m_subline.push_back(subline);
    length = 0;

    while (length < (m_width - m_margin) && offset < m_size) {
      if (m_buf[offset] == '\n') {
        ++truthline;
        ++offset;
        subline = -1;
        break;
      }

      ++offset;
      ++length;
    }
    ++subline;
    m_length.push_back(length);
  }
}

void Window::PrintBuf() {
  int begin = m_firstline;
  int end = m_firstline + m_height;

  char buf[MAXCOLUME];

  for (int id = begin; id < end && id < m_line; ++id) {
    memset(buf, ' ', m_width);
    memcpy(buf, m_buf + m_offset[id], m_length[id]);

    MoveCursor(id - begin, m_margin);
    if (m_movetype < 2) {
      write(STDOUT_FILENO, buf, m_width - m_margin);
    } else if (m_movetype == 2) {
      if (m_truthline[id] == m_truthline[m_focusline]) {
        write(STDOUT_FILENO, "\033[48;5;240m", 11);
      }
      write(STDOUT_FILENO, buf, m_width - m_margin);
      if (m_truthline[id] == m_truthline[m_focusline]) {
        write(STDOUT_FILENO, "\033[0m", 4);
      }
    }
  }
}

void Window::PrintNum() {
  int begin = m_firstline;
  int end = m_firstline + m_height;

  char buf[MAXCOLUME];
  char fmt[MAXCOLUME];

  snprintf(fmt, sizeof(fmt), "%%%dd", m_digit);
  for (int id = begin; id < end && id < m_line; ++id) {
    if (m_subline[id] == 0) {
      MoveCursor(id - begin, 1);
      snprintf(buf, sizeof(buf), fmt, m_truthline[id]);
      write(STDOUT_FILENO, buf, m_digit);
    }
  }
}

void Window::PrintBnd() {
  char buf[MAXCOLUME];
  char info[MAXCOLUME];

  if (m_active) {
    strcpy(buf, "\033[32m");
    write(STDOUT_FILENO, buf, 5);
  }

  memset(buf, '-', m_width + 2);
  buf[0] = '+';
  buf[m_width + 1] = '+';
  MoveCursor(-1, -1);
  write(STDOUT_FILENO, buf, m_width + 2);
  MoveCursor(m_height, -1);
  write(STDOUT_FILENO, buf, m_width + 2);
  int len = snprintf(info, sizeof(info), "[%d]%s", m_id, m_name);
  MoveCursor(-1, 3);
  write(STDOUT_FILENO, info, len);

  memset(buf, ' ', m_width + 2);
  buf[0] = '|';
  buf[m_width + 1] = '|';
  for (int id = 0; id < m_height; ++id) {
    MoveCursor(id, -1);
    write(STDOUT_FILENO, buf, m_width + 2);
  }

  if (m_active) {
    strcpy(buf, "\033[0m");
    write(STDOUT_FILENO, buf, 4);
  }
}

void Window::MoveDown(int n) {
  int end = 0;
  switch (m_movetype) {
    case 0 :
      return;
    case 1 :
      for (int iter = 0; iter < n; ++iter) {
        end = m_firstline + m_height;
        if (end < m_line) {
          ++m_firstline;
        }
      }
      return;
    case 2 :
      for (int iter = 0; iter < n; ++iter) {
        end = m_firstline + m_height;
        if (m_focusline < m_line - 1) {
          ++m_focusline;
        }
        if (m_focusline > end - 5 && end < m_line) {
          ++m_firstline;
        }
      }
  }
}

void Window::MoveUp(int n) {
  int begin = 0;
  switch (m_movetype) {
    case 0 :
      return;
    case 1 :
      for (int iter = 0; iter < n; ++iter) {
        begin = m_firstline;
        if (begin > 0) {
          --m_firstline;
        }
      }
      return;
    case 2 :
      for (int iter = 0; iter < n; ++iter) {
        begin = m_firstline;
        if (m_focusline > 0) {
          --m_focusline;
        }
        if (m_focusline < begin + 5 && begin > 0) {
          --m_firstline;
        }
      }
      return;
  }
}

