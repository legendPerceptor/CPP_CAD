//
// Created by achie on 5/29/2017.
//
#include "GraphicList.h"
#include "extgraph.h"
#include <iostream>
namespace MyGraphics{
    extern const int mseconds500;
    extern const int mseconds1000;
    extern char text[TEMP_STRING_LENGTH];
    extern BOOL TIMERWORKING;
    extern double curx, cury;
    extern BOOL isInputText ;
    extern BOOL isMouseDraw ;
    extern double textx, texty;
    extern size_t curintext;
    extern int FigureType;
    extern int DrawingErase;
    extern int textlen;
    extern int WorkingMode;
    extern GraphicList list;
    extern GraphicList* theChosenOne;
    extern BOOL hasChosenOne;
void MouseEventProcess(int x, int y, int button, int event){
    static BOOL isDrawing=FALSE;
    static BOOL isErasing=TRUE;
    static BOOL isMoving=FALSE;
    static double lastX,lastY;
    POINT cur;
    double mx, my,curx,cury;
    double dx,dy;
    GetCursorPos(&cur);
    curx=ScaleXInches(cur.x);
    cury=ScaleYInches(cur.y);
    mx = ScaleXInches(x);/*pixels --> inches*/
    my = ScaleYInches(y);/*pixels --> inches*/
    GraphicList* tmp;
    switch(event){
        case BUTTON_DOWN:

            if(button==LEFT_BUTTON){
                MovePen(mx,my);
                switch(WorkingMode){
                    case DRAWRECTANGLE:
                        //printf("HERE!\n");
                        tmp=new GraphicList();
                            tmp->setType(2);
                            tmp->setXl(mx);
                            tmp->setYt(my);
                            tmp->setXr(mx);
                            tmp->setYb(my);


                        list.insert(tmp);
                        list.setType(127);
                       // printf("Still Run!\n");
                        break;
                    case ELLIPSEMODE:
                        tmp=new GraphicList();
                        tmp->setType(3);
                        tmp->setXl(mx);
                        tmp->setYt(my);
                        tmp->setXr(mx);
                        tmp->setYb(my);


                        list.insert(tmp);
                        list.setType(127);
                        break;
                    case LINEMODE:
                        tmp=new GraphicList();
                        tmp->setType(1);
                        tmp->setXl(mx);
                        tmp->setYt(my);
                        tmp->setXr(mx);
                        tmp->setYb(my);
                        list.insert(tmp);
                        list.setType(127);
                        break;
                    case CHOOSEMODE:
                    //std::cout<<"Inside CHOOSEMODE"<<theChosenOne<<std::endl;

                            if(theChosenOne!=NULL){
                                //std::cout<<"It is "<<theChosenOne->is_InsideRegion(mx,my)<<std::endl;
                                theChosenOne->DrawFigure(FALSE);
                                //theChosenOne->remove();
                                theChosenOne=NULL;
                                hasChosenOne=FALSE;
                            }

                            for (tmp = list.next; tmp != NULL; tmp = tmp->next) {
                              /*  std::cout<<"Finding ..."<<tmp<<"("<<tmp->getXl()<<","<<tmp->getYt()<<")"
                                         <<"-("<<tmp->getXr()<<","<<tmp->getYb()<<")"<<std::endl;
                                std::cout<<"("<<mx<<","<<my<<")"<<tmp->is_InsideRegion(mx,my)<<std::endl;*/
                                if (tmp->is_InsideRegion(mx, my)) {
                                    break;
                                }
                            }
                           // std::cout<<tmp<<std::endl;
                            if (tmp != NULL) {
                                theChosenOne = tmp;
                                theChosenOne->DrawFigure(FALSE,1);
                                hasChosenOne=TRUE;
                                lastX=mx;
                                lastY=my;
                                //theChosenOne->setCenterX(mx);
                                //theChosenOne->setCenterY(my);
                                isMoving=TRUE;
                            }

                    case DRAWFREEMODE:
                    case TEXTFREEMODE:
                        if(isMouseDraw){
                            isDrawing=TRUE;
                        }else if(isInputText){
                            cancelTimer(TIMER_BLINK500);
                            DrawCursor(TRUE);
                            textx=mx;
                            texty=my;
                            textlen=0;
                            curintext=0;
                            text[0]=0;
                            startTimer(TIMER_BLINK500,mseconds500);
                            TIMERWORKING=TRUE;
                        }
                        break;
                    default:break;
                }

            }
            break;
        case BUTTON_UP:
            if(button==LEFT_BUTTON){
                isDrawing=FALSE;
                switch(WorkingMode){
                    case DRAWRECTANGLE:
                    case ELLIPSEMODE:
                    case LINEMODE:
                        if(list.getType()==127 && list.next!=NULL) {
                            tmp = list.next;
                           // tmp->DrawFigure(TRUE);
                            tmp->setXr(mx);
                            tmp->setYb(my);
                            tmp->setCenterX((tmp->getXl()+mx)/2);
                            tmp->setCenterY((tmp->getYt()+my)/2);
                            tmp->DrawFigure(FALSE);
                            list.setType(404);
                        }
                        WorkingMode=-1;
                        break;
                    case CHOOSEMODE:
                       if(theChosenOne!=NULL){
                            theChosenOne->DrawFigure(FALSE,2);
                           isMoving=FALSE;

                        }
                        break;
                    default:
                        break;
                }
            }
        case MOUSEMOVE:
            switch(WorkingMode){
                case DRAWRECTANGLE:
                case ELLIPSEMODE:
                case LINEMODE:
                    if(list.getType()==127 && list.next!=NULL) {
                        tmp = list.next;
                        //tmp->DrawFigure(TRUE);
                        GetWholeWhite();
                        tmp->setXr(mx);
                        tmp->setYb(my);
                        for(GraphicList* t=list.next;t!=NULL;t=t->next){
                            //if(t==theChosenOne)continue;
                            t->DrawFigure(FALSE);
                        }

                       // tmp->DrawFigure(FALSE);
                        //list.setType(404);
                    }
                    break;
                case CHOOSEMODE:
                    if(isMoving &&hasChosenOne && theChosenOne!=NULL){
                        //theChosenOne->DrawFigure(TRUE);
                        GetWholeWhite();
                        dx=mx-lastX;
                        dy=my-lastY;
                        lastX=(mx);
                        lastY=(my);
                        //theChosenOne->setCenterX()
                        theChosenOne->setXl(theChosenOne->getXl()+dx);
                        theChosenOne->setXr(theChosenOne->getXr()+dx);
                        theChosenOne->setYb(theChosenOne->getYb()+dy);
                        theChosenOne->setYt(theChosenOne->getYt()+dy);
                        //if(dx>0.05||dy>0.05)
                        for(GraphicList* t=list.next;t!=NULL;t=t->next){
                            if(t==theChosenOne)continue;
                            t->DrawFigure(FALSE);
                        }
                        theChosenOne->DrawFigure(FALSE,1);
                    }
                    break;
                case DRAWFREEMODE:

                        //	GetCursorPos(&cur);
                    if(isDrawing) {
                        double dex, dey;
                        dex = GetCurrentX();
                        dey = GetCurrentY();
                        DrawLine(mx - dex, my - dey);
                    }
                    break;
                default:break;
            }

        default:break;
    }
}


}