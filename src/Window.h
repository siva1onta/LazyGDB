#ifndef WINDOW_H_
#define WINDOW_H_

#define MAXROW 1024
#define MAXCOLUME 1024
#define MAXSIZE MAXROW * MAXCOLUME

#include <vector>

class Window {

public:
  Window(int id, const char *name);
  virtual ~Window() = 0;

  virtual void SetSizePos(int heigth, int width, int x, int y) final;
  virtual void SetActive(bool active) final;
  virtual void SetBufStr(const char *format, ...) final;
  virtual void SetBufFd(int fd) final;
  virtual void Print();
  virtual bool CommandChar(char cmd) = 0;
  virtual int GetId() const final;
  virtual bool GetActive() const final;
  virtual Window *GetFloatWindow() final;

protected:
  virtual void MoveCursor(int x, int y) final;
  virtual void DivideBuf() final;
  virtual void PrintBuf() final;
  virtual void PrintNum() final;
  virtual void PrintBnd() final;
  virtual void MoveDown(int n) final;
  virtual void MoveUp(int n) final;

  int m_id;
  char m_name[8];
  int m_margin;
  int m_digit;
  int m_movetype;
  Window *m_floatwindow;
  int m_height;
  int m_width;
  int m_x;
  int m_y;
  char m_buf[MAXSIZE];
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

#endif // WINDOW_H_
