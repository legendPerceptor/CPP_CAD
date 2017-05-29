//
// Created by achie on 5/29/2017.
//
#include "GraphicList.h"
#include "extgraph.h"
namespace MyGraphics {
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
    void DrawCursor(BOOL mode) {
        //char buf[500];
        //buf[0]=0;
        //strncpy(buf,text,curintext);
        char c;
        char *tmp = text + curintext;
        c = *tmp;
        *tmp = 0;
        double cursorX = textx + TextStringWidth(text);
        double texth = TextStringHeight(text);
        *tmp = c;
        SetEraseMode(mode);
        char* oldpen = GetPenColor();
        char Color[]="Blue";
        if (mode == FALSE)
            SetPenColor(Color);
        MovePen(cursorX, texty);
        DrawLine(0, texth);
        SetPenColor(oldpen);
        //MovePen(cursorX,texty);
        //SetEraseMode(FALSE);
    }


    void TimerEventProcess(int timerID) {
        static BOOL erasemode = FALSE;
        switch (timerID) {
            case TIMER_BLINK500:
                erasemode = !erasemode;
                DrawCursor(erasemode);

                break;
            default:
                break;
        }
    }
}