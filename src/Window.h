#ifndef WINDOW_H_
#define WINDOW_H_

#define MAXROW 1024
#define MAXCOLUME 1024
#define BUFFERSIZE MAXROW * MAXCOLUME

#include <vector>

class Window {

public:
  Window(int id, const char *name);
  virtual ~Window() = 0;

  virtual void SetSizePos(int height, int width, int x, int y) final;
  virtual void SetActive(bool active) final;
  virtual void SetBufStr(const char *format, ...) final;
  virtual void SetBufFd(int fd) final;
  virtual void Print();
  virtual bool CommandChar(char cmd);
  virtual int GetId() const final;
  virtual bool GetActive() const final;

protected:
  virtual void DivideBuf() final;
  virtual void PrintBuf();
  virtual void PrintNum() final;
  virtual void PrintBnd() final;
  virtual void MoveDown() final;
  virtual void MoveUp() final;

  int m_id;
  char m_name[8];
  int m_height;
  int m_width;
  int m_x;
  int m_y;
  int m_margin;
  int m_digit;
  char m_buf[BUFFERSIZE];
  int m_size;
  int m_line;
  int m_firstline;
  int m_focusline;
  bool m_active;
  std::vector<int> m_offset;
  std::vector<int> m_length;
  std::vector<int> m_truthline;
  std::vector<int> m_subline;
};

#endif
