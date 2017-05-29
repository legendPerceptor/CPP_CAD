//
// Created by achie on 5/29/2017.
//
#include "GraphicList.h"
#include "extgraph.h"
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
void MouseEventProcess(int x, int y, int button, int event){
    static BOOL isDrawing=FALSE;
    static BOOL isErasing=TRUE;
    POINT cur;
    double mx, my,curx,cury;
    GetCursorPos(&cur);
    curx=ScaleXInches(cur.x);
    cury=ScaleYInches(cur.y);
    mx = ScaleXInches(x);/*pixels --> inches*/
    my = ScaleYInches(y);/*pixels --> inches*/
    switch(event){
        case BUTTON_DOWN:

            if(button==LEFT_BUTTON){
                MovePen(mx,my);
                switch(WorkingMode){
                    case 37:
                    default:
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
                }

            }
            else if(button==RIGHT_BUTTON){

            }
            break;
        case BUTTON_UP:
            if(button==LEFT_BUTTON){
                isDrawing=FALSE;
            }
        case MOUSEMOVE:
            if(isDrawing){
                //	GetCursorPos(&cur);

                double dx,dy;
                dx=GetCurrentX();
                dy=GetCurrentY();
                DrawLine(mx-dx,my-dy);
            }
        default:break;
    }
}


}