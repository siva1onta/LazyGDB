#pragma once

#define BUFFERSIZE 1024 * 1024

class Window {

public:
  Window();
  virtual ~Window();

  virtual void Init(int id, const char *name, int width, int height, int x, int y) final;
  virtual void SetSize(int width, int height) final;
  virtual void SetPos(int x, int y) final;
  virtual void SetBufStr(const char *format, ...) final;
  virtual void SetBufFd(int Fd, char *begin) final;
  virtual void PrintBuf() final;
  virtual void PrintStr(const char *format, ...) final;
  virtual void PrintBnd() final;

protected:
  int m_id;
  char m_name[8];
  char m_buf[BUFFERSIZE];
  int m_width;
  int m_height;
  int m_x;
  int m_y;
};
