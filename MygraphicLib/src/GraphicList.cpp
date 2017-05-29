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
GraphicList::GraphicList(int type, double x1,double y1,double x2,double y2, GraphicList* next=NULL)
        :type(type),xl(x1),xr(x2),yb(y2),yt(y1),next(next){
    centerX=(xr-xl)/2;
    centerY=-(yb-yt)/2;
    if(type==4)
        text=new char[500];
    else text=NULL;
}
void GraphicList::DrawFigure(BOOL mode,int pencolor){
    //1 for Line, 2 for Rectangle, 3 for Ellipse, 4 for String
    double prex,prey;
    prex=GetCurrentX();
    prey=GetCurrentY();
    //double a,c;
    char* oldpen=NULL;
    oldpen=GetPenColor();
    if(pencolor==1 && mode==FALSE){
        SetPenColor((char*)"Blue");
    }else if(pencolor==2){
        SetPenColor((char*)"Green");
    }
    switch(type){
        case 1:
            SetEraseMode(mode);
            MovePen(xl,yt);
            DrawLine(xr-xl,yb-yt);
            //MovePen(prex,prey);
            break;
        case 2:

            SetEraseMode(mode);

            MovePen(xl,yt);
            DrawLine(xr-xl,0);
            DrawLine(0,yb-yt);
            DrawLine(xl-xr,0);
            DrawLine(0,yt-yb);
            //MovePen(prex,prey);

            break;
        case 3:
            /*MovePen(xl,yt);
            DrawLine(xr-xl,0);
            DrawLine(0,yb-yt);
            DrawLine(xl-xr,0);
            DrawLine(0,yt-yb);
*/
            //MovePen(centerX,centerY);
            //DrawLine(xr-xl,0);
            SetEraseMode(mode);
            MovePen(xr,(yb+yt)/2);

            DrawEllipticalArc((xr-xl)/2,(yt-yb)/2,0,360);
            //DrawArc((xr-xl)/2,0,360);
            break;
        case 4:
            SetEraseMode(mode);

            break;
        default:
            break;
    }
    if(pencolor!=0)
        SetPenColor(oldpen);
}

BOOL GraphicList::is_InsideRegion(double x,double y){

    double xleft=min(xl,xr),xright=max(xl,xr),ytop=max(yt,yb),ybottom=min(yt,yb);
    double k=(yb-yt)/(xr-xl);
    double nowy=k*(x-xl)+yt;
    if(type==1){return nowy-y<0.05 && nowy-y >-0.05;}
        return x>xleft && x<xright && y>ybottom && y<ytop;
    /*else if(type==3) {
        double c=(xr - xl)/2;
        double a=(yt-yb)/2;
        return ((x - centerX) * (x - centerX) / (a*a) +
               (y - centerY) * (y - centerY) / (a*a-c*c)<1);
    }*/
}

void GraphicList::setRegion(const RECT &region) {
    xl=region.left;
    xr=region.right;
    yb=region.bottom;
    yt=region.top;
}

void GraphicList::move(double dx,double dy){
    DrawFigure(TRUE);
    yb+=dy;
    yt+=dy;
    xr+=dx;
    xl+=dx;
    DrawFigure(FALSE);
}

GraphicList::GraphicList() {
    yb=yt=xl=xr=0;
    type=-1;
    prev=next=NULL;
    centerX=centerY=0;
    text=NULL;
}
void GraphicList::insert(GraphicList* tmp){
    tmp->next=this->next;
    tmp->prev=this;
    if(tmp->next!=NULL)
        tmp->next->prev=tmp;
    this->next=tmp;

}
void GraphicList::remove(){
    this->prev->next=this->next;
    if(this->next!=NULL)
        this->next->prev=this->prev;
    delete this;
}
void GraphicList::setType(int type) {
    GraphicList::type = type;

}

void GraphicList::setXl(double xl) {
    GraphicList::xl = xl;
}

void GraphicList::setYt(double yt) {
    GraphicList::yt = yt;
}

void GraphicList::setXr(double xr) {
    GraphicList::xr = xr;
}

void GraphicList::setYb(double yb) {
    GraphicList::yb = yb;
}

int GraphicList::getType() const {
    return type;
}

GraphicList *GraphicList::getNext() const {
    return next;
}

double GraphicList::getXl() const {
    return xl;
}

double GraphicList::getYt() const {
    return yt;
}

double GraphicList::getXr() const {
    return xr;
}

double GraphicList::getYb() const {
    return yb;
}

void GraphicList::setNext(GraphicList *next) {
    GraphicList::next = next;
}

void GraphicList::setCenterX(double centerX) {
    GraphicList::centerX = centerX;
}

void GraphicList::setCenterY(double centerY) {
    GraphicList::centerY = centerY;
}

double GraphicList::getCenterX() const {
    return centerX;
}

double GraphicList::getCenterY() const {
    return centerY;
}

GraphicList::~GraphicList() {
    if(type==4){
        delete []text;
    }
}
