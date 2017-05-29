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
    void CharEventProcess(char c) {
        static char str[2] = {0, 0};
        static int oldDistance = 0;
        double xt = textx + TextStringWidth(text),
                yt = texty;
        //if(isInputText){
        switch (c) {
            case '\r':
                if (textlen > 0) {
                    cancelTimer(TIMER_BLINK500);
                    TIMERWORKING = FALSE;
                    DrawCursor(TRUE);
                    MovePen(textx, texty);
                    SetEraseMode(TRUE);
                    DrawTextString(text);
                    MovePen(textx, texty);
                    //submit text
                    MessageBoxA(NULL, text, "The Text", MB_OK);
                    textlen = 0;
                    text[0] = 0;
                    //cancelTimer(TIMER_BLINK500);
                    //SetEraseMode(FALSE);
                }
                break;
            case 27: /*ESC*/
                isInputText = FALSE;
                isMouseDraw = FALSE;
                FigureType = -1;
                break;
            case 8:

                if (textlen > 0) {
                    cancelTimer(TIMER_BLINK500);
                    DrawCursor(TRUE);
                    //Str[0]=text[curintext-1];
                    MovePen(textx, texty);
                    SetEraseMode(TRUE);
                    DrawTextString(text);
                    char *aftertext = text + curintext - 1;
                    while (*aftertext != '\0') {
                        *aftertext = *(aftertext + 1);
                        aftertext++;
                    }
                    MovePen(textx, texty);
                    SetEraseMode(FALSE);
                    DrawTextString(text);
                    textlen--;
                    curintext--;
                    startTimer(TIMER_BLINK500, mseconds500);

                }


                break;
            default:

                if (isInputText) {

                    str[0] = c;
                    cancelTimer(TIMER_BLINK500);
                    DrawCursor(TRUE);
                    MovePen(textx, texty);
                    SetEraseMode(TRUE);
                    DrawTextString(text);
                    char *aftercur = text + curintext;
                    char *tmp = text + textlen;
                    while (tmp != aftercur) {
                        *tmp = *(tmp - 1);
                        tmp--;
                    }
                    *aftercur = c;
                    MovePen(textx, texty);
                    SetEraseMode(FALSE);
                    textlen++;
                    text[textlen] = 0;
                    curintext++;
                    DrawTextString(text);

                    startTimer(TIMER_BLINK500, mseconds500);
                }
                break;
                // }
        }
    }
}