//
// Created by achie on 5/29/2017.
//
#include <iostream>
#include "GraphicList.h"
#include "extgraph.h"
#include "graphics.h"
#include <string>

namespace MyGraphics {
    extern const int mseconds500;
    extern const int mseconds1000;
    extern char text[TEMP_STRING_LENGTH];
    extern BOOL TIMERWORKING;
    extern double curx, cury;
    extern BOOL isInputText;
    extern BOOL isMouseDraw;
    extern double textx, texty;
    extern size_t curintext;
    extern int FigureType;
    extern int DrawingErase;
    extern int textlen;
    extern int WorkingMode;
    extern GraphicList list;
    extern GraphicList *theChosenOne;
    extern BOOL hasChosenOne;

    void KeyboardEventProcess(int key, int event) {
        double xt = textx + TextStringWidth(text),
                yt = texty;
        static char Str[2] = {0, 0};
        char test_length[10];
        std::string Title;
        GraphicList *tmp;
        switch (event) {
            case KEY_DOWN:

                switch (key) {
                    case VK_F5://F5 TextMode
                        if (!isInputText) {
                            Title = "Text Mode(F5 for Text;F3 for drawing)";
                            GetWholeWhite();
                            SetWindowTitle((char *) Title.c_str());
                            isInputText = TRUE;
                            isMouseDraw = FALSE;
                            FigureType = -1;
                            WorkingMode = TEXTFREEMODE;
                            textx=0;
                            texty=0;
                            textlen=0;
                            curintext=0;
                            //MovePen(4,4);
                            //double dy=GetCursordelta(0,"DD");
                            //DrawLine(0,dy);
                        }
                        break;
                    case VK_F1:
                        Title = "Line Mode";
                        SetWindowTitle((char *) Title.c_str());
                        //GraphicList* tmp=new GraphicList();
                        //list.insert(tmp);
                        GetWholeWhite();
                        for (GraphicList *t = list.next; t != NULL; t = t->next) {
                            //if(t==theChosenOne)continue;
                            t->DrawFigure(FALSE);
                        }
                        if (TIMERWORKING) {
                            cancelTimer(TIMER_BLINK500);
                            TIMERWORKING = FALSE;
                            DrawCursor(TRUE);
                            SetEraseMode(FALSE);
                        }
                        WorkingMode = LINEMODE;
                        break;
                    case VK_F10://Erase or not
                        if (WorkingMode==DRAWFREEMODE) {
                            DrawingErase = !DrawingErase;
                            if (DrawingErase) {
                                SetPenSize(100);
                                SetEraseMode(TRUE);

                            } else {
                                SetPenSize(1);
                                SetEraseMode(FALSE);

                            }
                        }
                        break;
                    case VK_F6://F6 Drawing Mode
                        Title = "Drawing Mode(F5 for Text;F6 for drawing)";
                        SetWindowTitle((char *) Title.c_str());
                        GetWholeWhite();
                        isInputText = FALSE;
                        isMouseDraw = TRUE;
                        FigureType = -1;
                        //printf("F6MODE\n");
                        if (TIMERWORKING) {
                            //printf("ERROR!\n");
                            cancelTimer(TIMER_BLINK500);
                            TIMERWORKING = FALSE;
                            DrawCursor(TRUE);
                            SetEraseMode(FALSE);
                        }
                        WorkingMode = DRAWFREEMODE;
                        break;
                    case VK_F3:
                        Title = "Rectangle Mode";
                        SetWindowTitle((char *) Title.c_str());
                        //GraphicList* tmp=new GraphicList();
                        //list.insert(tmp);
                        GetWholeWhite();
                        for (GraphicList *t = list.next; t != NULL; t = t->next) {
                            //if(t==theChosenOne)continue;
                            t->DrawFigure(FALSE);
                        }
                        if (TIMERWORKING) {
                            cancelTimer(TIMER_BLINK500);
                            TIMERWORKING = FALSE;
                            DrawCursor(TRUE);
                            SetEraseMode(FALSE);
                        }
                        WorkingMode = 37;
                        break;

                    case VK_F7:
                        Title = "Ellipse Mode";
                        SetWindowTitle((char *) Title.c_str());
                        //GraphicList* tmp=new GraphicList();
                        //list.insert(tmp);
                        GetWholeWhite();
                        for (GraphicList *t = list.next; t != NULL; t = t->next) {
                            //if(t==theChosenOne)continue;
                            t->DrawFigure(FALSE);
                        }
                        if (TIMERWORKING) {
                            cancelTimer(TIMER_BLINK500);
                            TIMERWORKING = FALSE;
                            DrawCursor(TRUE);
                            SetEraseMode(FALSE);
                        }
                        WorkingMode = ELLIPSEMODE;
                        //sprintf(test_length, "%lf", TextStringWidth((char *) "\0"));
                        //MessageBoxA(NULL, test_length, "TestTitle", MB_OK);
                        break;
                    case VK_F8://Choose Figure
                        //UpdateDisplay();
                        SetWindowTitle((char *) "ChoosingMode");
                        WorkingMode = CHOOSEMODE;

                        break;
                    case VK_UP:
                        switch(WorkingMode){
                            case CHOOSEMODE:
                                if (hasChosenOne && theChosenOne != NULL) {
                                    GetWholeWhite();
                                    double dx = 0.1, dy = 0.1;
                                    //theChosenOne->setXl(theChosenOne->getXl() + dx);
                                    //theChosenOne->setXr(theChosenOne->getXr() + dx);
                                    theChosenOne->setYb(theChosenOne->getYb() + dy);
                                    theChosenOne->setYt(theChosenOne->getYt() + dy);

                                    for (GraphicList *t = list.next; t != NULL; t = t->next) {
                                        if (t == theChosenOne)continue;
                                        t->DrawFigure(FALSE);
                                    }
                                    theChosenOne->DrawFigure(FALSE, 1);
                                }
                            default:break;
                        }
                        break;
                    case VK_DOWN:
                        switch(WorkingMode){
                            case CHOOSEMODE:
                                if (hasChosenOne && theChosenOne != NULL) {
                                    GetWholeWhite();
                                    double dx = 0.1, dy = -0.1;
                                    //theChosenOne->setXl(theChosenOne->getXl() + dx);
                                    //theChosenOne->setXr(theChosenOne->getXr() + dx);
                                    theChosenOne->setYb(theChosenOne->getYb() + dy);
                                    theChosenOne->setYt(theChosenOne->getYt() + dy);

                                    for (GraphicList *t = list.next; t != NULL; t = t->next) {
                                        if (t == theChosenOne)continue;
                                        t->DrawFigure(FALSE);
                                    }
                                    theChosenOne->DrawFigure(FALSE, 1);
                                }
                            default:break;
                        }
                        break;
                    case VK_LEFT:
                        switch (WorkingMode) {
                            case CHOOSEMODE:
                                if (hasChosenOne && theChosenOne != NULL) {
                                    GetWholeWhite();
                                    double dx = -0.1, dy = 0.1;
                                    theChosenOne->setXl(theChosenOne->getXl() + dx);
                                    theChosenOne->setXr(theChosenOne->getXr() + dx);
                                    //theChosenOne->setYb(theChosenOne->getYb() + dy);
                                    //theChosenOne->setYt(theChosenOne->getYt() + dy);
                                    //if(dx>0.05||dy>0.05)
                                    for (GraphicList *t = list.next; t != NULL; t = t->next) {
                                        if (t == theChosenOne)continue;
                                        t->DrawFigure(FALSE);
                                    }
                                    theChosenOne->DrawFigure(FALSE, 1);
                                }
                            case 5:
                                cancelTimer(TIMER_BLINK500);
                                DrawCursor(TRUE);
                                if (curintext > 1) {

                                    curintext--;
                                    char curtext[TEMP_STRING_LENGTH];
                                    strncpy(curtext, text, curintext);
                                    MovePen(textx + TextStringWidth(curtext), yt);
                                }
                                startTimer(TIMER_BLINK500, mseconds500);
                                break;
                            default:
                                break;
                        }
                        break;
                    case VK_RIGHT:
                        switch (WorkingMode) {
                            case CHOOSEMODE:
                                if (hasChosenOne && theChosenOne != NULL) {
                                    GetWholeWhite();
                                    double dx = 0.1, dy = 0.1;
                                    theChosenOne->setXl(theChosenOne->getXl() + dx);
                                    theChosenOne->setXr(theChosenOne->getXr() + dx);
                                    //theChosenOne->setYb(theChosenOne->getYb() + dy);
                                    //theChosenOne->setYt(theChosenOne->getYt() + dy);
                                    //if(dx>0.05||dy>0.05)
                                    for (GraphicList *t = list.next; t != NULL; t = t->next) {
                                        if (t == theChosenOne)continue;
                                        t->DrawFigure(FALSE);
                                    }
                                    theChosenOne->DrawFigure(FALSE, 1);
                                }
                                break;
                            case 5:
                                cancelTimer(TIMER_BLINK500);
                                DrawCursor(TRUE);
                                if (curintext < textlen) {
                                    curintext++;
                                    char curtext[TEMP_STRING_LENGTH];
                                    strncpy(curtext, text, curintext);
                                    MovePen(textx + TextStringWidth(curtext), yt);
                                }
                                startTimer(TIMER_BLINK500, mseconds500);
                                break;
                            default:break;
                        }
                        break;
                    case VK_DELETE:
                        if (hasChosenOne && theChosenOne != NULL) {
                            //theChosenOne->DrawFigure(TRUE);
                            theChosenOne->remove();
                            GetWholeWhite();
                            for (GraphicList *t = list.next; t != NULL; t = t->next) {
                                t->DrawFigure(FALSE);
                            }

                            theChosenOne = NULL;
                            hasChosenOne = FALSE;
                        }
                    default:
                        break;
                }
            default:
                break;
        }
    }
}