//
// Created by achie on 5/26/2017.
//

#ifndef MYCAD_GRAPHICLIST_H
#define MYCAD_GRAPHICLIST_H

#include <windows.h>
class GraphicList;
typedef GraphicList* PtrToNode;
class GraphicList{
    int type;//1 for Line, 2 for Rectangle, 3 for Ellipse, 4 for String
    RECT region;
    PtrToNode next;
    double centerX,centerY;

public:
    GraphicList(int type, const RECT &region, const PtrToNode next);
    void DrawFigure(BOOL mode=FALSE);

    BOOL is_InsideRegion(double x, double y);

    const RECT &getRegion() const;

    void setRegion(const RECT &region);

private:

};
class MemoryGraph{
    GraphicList* Head;
    HDC memoryHdc;

};

#endif //MYCAD_GRAPHICLIST_H
