#include "../lib/dimensions.h"
#include <stdlib.h>
#include <unistd.h>
#include "winsys.h"
#include "clock.h"
#include "graph.h"
int main(int argc, char *argv[])
{
  if (gfx_init())
    exit(3);
  int wxsize = MAX_W/4;
  int wysize = (MAX_H-MAX_W/8)/2;
  std::vector<std::pair<float,float>> v;
  CRect ww1(CPoint(0,0),CPoint(wxsize,wysize));
  v.push_back(std::make_pair(0,0));
  CRect ww2,ww3,ww4,ww5,ww6,ww7,ww8;
  ww2 = ww3 = ww4 = ww5 = ww6 = ww7 = ww8 = ww1;
  ww2.Move(wxsize,0);
  v.push_back(std::make_pair(wxsize,0));
  ww3.Move(2*wxsize,0);
  v.push_back(std::make_pair(2*wxsize,0));
  ww4.Move(3*wxsize,0);
  v.push_back(std::make_pair(3*wxsize,0));
  ww5.Move(0,wysize);
  v.push_back(std::make_pair(0,wysize));
  ww6.Move(wxsize,wysize);
  v.push_back(std::make_pair(wxsize,wysize));
  ww7.Move(2*wxsize,wysize);
  v.push_back(std::make_pair(2*wxsize,wysize));
  ww8.Move(3*wxsize,wysize);
  v.push_back(std::make_pair(3*wxsize,wysize));
  
  CRect wpW4(CPoint(0,0),CPoint(7*(MAX_W/8),MAX_W/8));
  wpW4.Move(0,MAX_H-MAX_W/8);

  CRect wClock(CPoint(200,200), CPoint(MAX_W/8,MAX_W/8));
  wClock.Move(MAX_W-(MAX_W/8)-205,MAX_H-MAX_W/8);
  
  CWindow *pW1 = new CSensorGraph(ww1,v[0].first,v[0].second,-100,200);
  CFramedWindow* pW2 = new CSensorGraph(ww2,v[1].first,v[1].second,-100,200);

  CFramedWindow* pW3 = new CSensorGraph(ww3,v[2].first,v[2].second,-100,200);
  CFramedWindow* pW4 = new CSensorGraph(ww4,v[3].first,v[3].second,-100,200);
  CFramedWindow* pW5 = new CSensorGraph(ww5,v[4].first,v[4].second,-100,200);
  CFramedWindow* pW6 = new CSensorGraph(ww6,v[5].first,v[5].second,-100,200);
  CFramedWindow* pW7 = new CSensorGraph(ww7,v[6].first,v[6].second,-100,200);
  CFramedWindow* pW8 = new CSensorGraph(ww8,v[7].first,v[7].second,-100,200);
  //CFramedWindow* ppW3 = new CFramedWindow(CRect(CPoint(140, 200), CPoint(300, 300)), YELLOW, BLACK);
  
  CInputLine* ppW4 = new CInputLine(wpW4, BLACK,RED);

  CGroup* pG = new CGroup;
  //pG->insert(ppW3);
  pG->insert(ppW4);
  
  CClock* pClock = new CClock(wClock, GREEN, BLACK);

  CDesktop d;
  CSensorGraph* graph = new CSensorGraph(ww1,0,0,100,200);
  
  //graph->X.push_back(10);
  graph->Y.push_back(100);
  //graph->X.push_back(60);
  graph->Y.push_back(130);
  //graph->X.push_back(60);
  graph->Y.push_back(130);
  //graph->X.push_back(100);
  graph->Y.push_back(200);
  graph->Y.push_back(100);
  //graph->X.push_back(60);
  graph->Y.push_back(130);
  //graph->X.push_back(60);
  graph->Y.push_back(130);
  //graph->X.push_back(100);
  graph->Y.push_back(200);
  //graph->newX();
  graph->scaleGraph();
  graph->scaleY();
  //graph->newX();
  
  //d.insert(graph);
  graph->transpose();
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
