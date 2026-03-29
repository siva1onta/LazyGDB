#pragma once

#define BUFFERSIZE 1024 * 1024

class Window final {

public:
  Window();
  ~Window();

  void Init(int id, const char *name, int width, int height, int x, int y);
  void SetSize();
  void SetBufStr(const char *format, ...);
  void SetBufFd(int Fd, char *begin);
  void PrintBuf();
  void PrintStr(const char *format, ...);
  void PrintBnd();

private:
  int m_id;
  char m_name[8];
  char m_buf[BUFFERSIZE];
  int m_width;
  int m_height;
  int m_x;
  int m_y;
};
