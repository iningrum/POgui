#include "../lib/dimensions.h"
#include <stdlib.h>
#include <unistd.h>
#include "winsys.h"
#include "clock.h"
int main(int argc, char *argv[])
{
  if (gfx_init())
    exit(3);
  int wxsize = MAX_W/4;
  int wysize = (MAX_H-MAX_W/8)/2;
  CRect ww1(CPoint(0,0),CPoint(wxsize,wysize));
  CRect ww2,ww3,ww4,ww5,ww6,ww7,ww8;
  ww2 = ww3 = ww4 = ww5 = ww6 = ww7 = ww8 = ww1;
  ww2.Move(wxsize,0);
  ww3.Move(2*wxsize,0);
  ww4.Move(3*wxsize,0);
  ww5.Move(0,wysize);
  ww6.Move(wxsize,wysize);
  ww7.Move(2*wxsize,wysize);
  ww8.Move(3*wxsize,wysize);
  
  CRect wpW4(CPoint(0,0),CPoint(7*(MAX_W/8),MAX_W/8));
  wpW4.Move(0,MAX_H-MAX_W/8);

  CRect wClock(CPoint(200,200), CPoint(MAX_W/8,MAX_W/8));
  wClock.Move(MAX_W-(MAX_W/8)-205,MAX_H-MAX_W/8);
  
  CWindow *pW1 = new CWindow(ww1);
  CFramedWindow* pW2 = new CFramedWindow(ww2);
  CFramedWindow* pW3 = new CFramedWindow(ww3);
  CFramedWindow* pW4 = new CFramedWindow(ww4);
  CFramedWindow* pW5 = new CFramedWindow(ww5);
  CFramedWindow* pW6 = new CFramedWindow(ww6);
  CFramedWindow* pW7 = new CFramedWindow(ww7);
  CFramedWindow* pW8 = new CFramedWindow(ww8);
  CFramedWindow* ppW3 = new CFramedWindow(CRect(CPoint(140, 200), CPoint(300, 300)), YELLOW, BLACK);
  
  CInputLine* ppW4 = new CInputLine(wpW4, BLACK,RED);

  CGroup* pG = new CGroup;
  //pG->insert(ppW3);
  pG->insert(ppW4);
  
  CClock* pClock = new CClock(wClock, GREEN, BLACK);

  CDesktop d;

  d.insert(pW1);
  d.insert(pW2);
  d.insert(pW3);
  d.insert(pW4);
  d.insert(pW5);
  d.insert(pW6);
  d.insert(pW7);
  d.insert(pW8);
  d.insert(pClock);
  d.insert(pG); 
  d.run();
  return 0;
}
