#pragma once

class Window final {

public:
  Window();
  Window(int id, const char *name, int width, int height, int x, int y);
  ~Window();

  void SetBufStr(const char *format, ...);
  void SetBufFd(int Fd, char *begin);
  void PrintBuf();
  void PrintStr(const char *format, ...);
  void MoveCursor(int x, int y);

private:
  int m_id;
  char m_name[8];
  char m_buf[4096];
  int m_width;
  int m_height;
  int m_x;
  int m_y;
};
