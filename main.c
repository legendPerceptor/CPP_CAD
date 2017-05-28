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

#define deltax 0.03
#define deltay 0.03
#define TEMP_STRING_LENGTH 500
#define TIMER_BLINK500  1
#define TIMER_BLINK1000 2
static BOOL working= FALSE;
const int mseconds500 = 300;
const int mseconds1000 = 1000;
static char text[TEMP_STRING_LENGTH];
static double curx,cury;
static BOOL isInputText=FALSE;
static BOOL isMouseDraw=TRUE;
static double textx,texty;
static size_t curintext;
static int FigureType;
static int textlen;
void TimerEventProcess(int timerID);
void CharEventProcess(char c);
void MouseEventProcess(int x, int y, int button, int event);
void KeyboardEventProcess(int key,int event);
void DrawCursor(BOOL mode);
void Main(){
    InitGraphics();
    SetWindowTitle( "Drawing Mode(F5 for Text;F3 for drawing)");
    registerMouseEvent(MouseEventProcess);
    registerCharEvent(CharEventProcess);
    registerKeyboardEvent(KeyboardEventProcess);
    registerTimerEvent(TimerEventProcess);
    SetPenColor("Red");
    SetPenSize(2);
    MovePen(4,4);
    //DrawLine(3,3);

}
void KeyboardEventProcess(int key,int event){
    double xt=textx+TextStringWidth(text),
            yt=texty;
    static char Str[2]={0,0};
    char test_length[10];
    switch (event){
        case KEY_DOWN:

            switch(key){
                case VK_F5://F5 TextMode
                    if(!isInputText){
                        SetWindowTitle("Text Mode(F5 for Text;F3 for drawing)");
                        isInputText=TRUE;
                        isMouseDraw=FALSE;
                        FigureType=-1;

                        //double dy=GetCursordelta(0,"DD");
                        //DrawLine(0,dy);
                    }
                    break;
                case VK_F3://F3 Drawing Mode
                    SetWindowTitle("Drawing Mode(F5 for Text;F3 for drawing)");
                    isInputText=FALSE;
                    isMouseDraw=TRUE;
                    FigureType=-1;
                    cancelTimer(TIMER_BLINK500);
                    break;
                case VK_LEFT:
                    if(working==FALSE){
                        working=TRUE;
                        cancelTimer(TIMER_BLINK500);
                        DrawCursor(TRUE);
                        if(curintext>1){

                            curintext--;
                            char curtext[TEMP_STRING_LENGTH];
                            strncpy(curtext,text,curintext);
                            MovePen(textx+TextStringWidth(curtext),yt);
                        }
                        startTimer(TIMER_BLINK500,mseconds500);
                        working=FALSE;
                    }
                    break;
                case VK_F7:

                    sprintf(test_length,"%lf",TextStringWidth("\0"));
                    MessageBoxA(NULL,test_length,"TestTitle",MB_OK);
                    break;
                case VK_F8://Draw Rectangle
                    //UpdateDisplay();
                    FigureType=3;
                    isMouseDraw=FALSE;
                    isInputText=FALSE;
                    break;
                case VK_RIGHT:
                    if(working==FALSE){
                        working=TRUE;
                        cancelTimer(TIMER_BLINK500);
                        DrawCursor(TRUE);
                        if(curintext<textlen){
                            curintext++;
                            char curtext[TEMP_STRING_LENGTH];
                            strncpy(curtext,text,curintext);
                            MovePen(textx+TextStringWidth(curtext),yt);
                        }
                        startTimer(TIMER_BLINK500,mseconds500);
                        working=FALSE;
                    }
                    break;
                default:
                    break;
            }
        default:
            break;
    }
}
void CharEventProcess(char c)
{
    static char str[2] = {0, 0};
    static int oldDistance=0;
    double xt=textx+TextStringWidth(text),
            yt=texty;
    //if(isInputText){
    switch (c) {
        case '\r':
            if(textlen>0){
                cancelTimer(TIMER_BLINK500);
                DrawCursor(TRUE);
                MovePen(textx,texty);
                SetEraseMode(TRUE);
                DrawTextString(text);
                MovePen(textx,texty);
                //submit text
                MessageBoxA(NULL,text,"The Text",MB_OK);
                textlen=0;
                text[0]=0;
                cancelTimer(TIMER_BLINK500);
                //SetEraseMode(FALSE);
            }
            break;
        case 27: /*ESC*/
            isInputText=FALSE;
            isMouseDraw=FALSE;
            FigureType=-1;
            break;
        case 8:
            if(working==FALSE){
                working=TRUE;
                if(textlen>0){
                    cancelTimer(TIMER_BLINK500);
                    DrawCursor(TRUE);
                    //Str[0]=text[curintext-1];
                    MovePen(textx,texty);
                    SetEraseMode(TRUE);
                    DrawTextString(text);
                    char* aftertext=text+curintext-1;
                    while(*aftertext!='\0'){
                        *aftertext=*(aftertext+1);
                        aftertext++;
                    }
                    MovePen(textx,texty);
                    SetEraseMode(FALSE);
                    DrawTextString(text);
                    textlen--;
                    curintext--;
                    startTimer(TIMER_BLINK500,mseconds500);
/*
                    MovePen(xt-TextStringWidth(aftertext),yt);
                    SetEraseMode(TRUE);
                    DrawTextString(aftertext);
                    MovePen(xt-TextStringWidth(aftertext),yt);
                    SetEraseMode(FALSE);
                    DrawTextString(++aftertext);
                    MovePen(xt-TextStringWidth(aftertext),yt);
                    text[curintext-1]=0;
                    strcat(text,aftertext);*/

                }
                working=FALSE;
            }
            break;
        default:

            if(working==FALSE && isInputText){
                working=TRUE;
                str[0]=c;
                cancelTimer(TIMER_BLINK500);
                DrawCursor(TRUE);
                MovePen(textx,texty);
                SetEraseMode(TRUE);
                DrawTextString(text);
                char *aftercur=text+curintext;
                char *tmp=text+textlen;
                while (tmp!=aftercur){
                    *tmp=*(tmp-1);
                    tmp--;
                }
                *aftercur=c;
                MovePen(textx,texty);
                SetEraseMode(FALSE);
                textlen++;
                text[textlen]=0;
                curintext++;
                DrawTextString(text);


                working=FALSE;
                startTimer(TIMER_BLINK500,mseconds500);
            }
            break;
            // }
    }
}
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
                }else if(FigureType!=-1){

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
void TimerEventProcess(int timerID){
    static BOOL erasemode=FALSE;
    switch(timerID){
        case TIMER_BLINK500:
            erasemode=!erasemode;
                DrawCursor(erasemode);

            break;
        default:
            break;
    }
}
void DrawCursor(BOOL mode){
    //char buf[500];
    //buf[0]=0;
    //strncpy(buf,text,curintext);
    char c;
    char* tmp=text+curintext;
    c=*tmp;
    *tmp=0;
    double cursorX=textx+TextStringWidth(text);
    double texth=TextStringHeight(text);
    *tmp=c;
    SetEraseMode(mode);
    string oldpen=GetPenColor();
    if(mode==FALSE)
        SetPenColor("Blue");
    MovePen(cursorX,texty);
    DrawLine(0,texth);
    SetPenColor(oldpen);
    //MovePen(cursorX,texty);
    //SetEraseMode(FALSE);
}
