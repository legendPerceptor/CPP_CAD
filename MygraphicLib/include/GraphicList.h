//
// Created by achie on 5/26/2017.
//

#ifndef MYCAD_GRAPHICLIST_H
#define MYCAD_GRAPHICLIST_H

#include <windows.h>
//class GraphicList;
//typedef GraphicList* PtrToNode;
#define TEMP_STRING_LENGTH 500
#define TIMER_BLINK500  1
#define TIMER_BLINK1000 2
class GraphicList{
public:
    GraphicList(int type, RECT &region, GraphicList* next);
    void DrawFigure(BOOL mode=FALSE);
    GraphicList();
    BOOL is_InsideRegion(double x, double y);

    const RECT &getRegion() const;

    void setRegion(const RECT &region);

    void move(double dx,double dy);

    void insert(GraphicList* tmp);
    GraphicList* next;
private:
    int type;//1 for Line, 2 for Rectangle, 3 for Ellipse, 4 for String
    RECT region;

    double centerX,centerY;
};
class MemoryGraph{
    GraphicList* Head;
    HDC memoryHdc;

};
namespace MyGraphics {
    const int mseconds500 = 300;
    const int mseconds1000 = 1000;
    extern void DrawCursor(BOOL mode);


    extern void TimerEventProcess(int timerID);

    extern void CharEventProcess(char c);

    extern void MouseEventProcess(int x, int y, int button, int event);

    extern void KeyboardEventProcess(int key, int event);

    extern void DrawCursor(BOOL mode);
}

#endif //MYCAD_GRAPHICLIST_H
