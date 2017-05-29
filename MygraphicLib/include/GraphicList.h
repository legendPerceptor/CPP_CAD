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
#define CHOOSEMODE 29
#define DRAWRECTANGLE 37
#define ELLIPSEMODE 35
#define LINEMODE 33
#define DRAWFREEMODE 6
#define TEXTFREEMODE 5
class GraphicList{
public:
    GraphicList(int type, double x1,double x2,double y1,double y2, GraphicList* next);
    void DrawFigure(BOOL mode=FALSE,int pencolor=0);
    GraphicList();
    BOOL is_InsideRegion(double x, double y);

    void setRegion(const RECT &region);

    void move(double dx,double dy);

    void setType(int type);

    void setXl(double xl);

    double getCenterX() const;

    double getCenterY() const;

    void setNext(GraphicList *next);

    void setCenterX(double centerX);

    void setCenterY(double centerY);

    GraphicList *getNext() const;

    virtual ~GraphicList();

    double getXl() const;

    double getYt() const;

    double getXr() const;

    double getYb() const;

    void setYt(double yt);

    void setXr(double xr);

    void setYb(double yb);

    //void setLocation(int type)
    int getType() const;

    void insert(GraphicList* tmp);
    void remove();
    GraphicList *next,*prev;
    char *text;
private:
    int type;//1 for Line, 2 for Rectangle, 3 for Ellipse, 4 for String
    double xl,yt,xr,yb;

    double centerX,centerY;
};
/*class MemoryGraph{
    GraphicList* Head;
    HDC memoryHdc;

};*/
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
