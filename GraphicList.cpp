//
// Created by achie on 5/26/2017.
//

#include "GraphicList.h"
#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
GraphicList::GraphicList(int type, const RECT &region, const PtrToNode next=NULL)
        :type(type),region(region),next(next){
    centerX=(region.right-region.left)/2;
    centerY=-(region.bottom-region.top)/2;
}
void GraphicList::DrawFigure(BOOL mode){
    //1 for Line, 2 for Rectangle, 3 for Ellipse, 4 for String
/*    double prex,prey;
    prex=GetCurrentX();
    prey=GetCurrentY();
    switch(type){
        case 1:
            SetEraseMode(mode);
            MovePen(region.left,region.top);
            DrawLine(region.right-region.left,region.bottom-region.top);
            MovePen(prex,prey);
            break;
        case 2:
            SetEraseMode(mode);

            MovePen(region.left,region.top);
            DrawLine(region.right-region.left,0);
            DrawLine(0,region.bottom-region.top);
            DrawLine(region.left-region.right,0);
            DrawLine(0,region.top-region.bottom);
            MovePen(prex,prey);
            break;
        case 3:
            break;
        case 4:
            SetEraseMode(mode);

            break;
        default:
            break;
    }*/
}

BOOL GraphicList::is_InsideRegion(double x,double y){
    return x>region.left && x<region.right && y>region.bottom && y<region.top;
}

void GraphicList::setRegion(const RECT &region) {
    GraphicList::region = region;
}

const RECT &GraphicList::getRegion() const {
    return region;
}
