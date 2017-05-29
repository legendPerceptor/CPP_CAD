//
// Created by achie on 5/29/2017.
//
#include <iostream>
#include "GraphicList.h"
#include "extgraph.h"
#include "graphics.h"
#include <string>
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
    void KeyboardEventProcess(int key,int event){
        double xt=textx+TextStringWidth(text),
                yt=texty;
        static char Str[2]={0,0};
        char test_length[10];
        std::string Title;
        switch (event){
            case KEY_DOWN:

                switch(key){
                    case VK_F5://F5 TextMode
                        if(!isInputText){
                            Title="Text Mode(F5 for Text;F3 for drawing)";
                            SetWindowTitle((char*)Title.c_str());
                            isInputText=TRUE;
                            isMouseDraw=FALSE;
                            FigureType=-1;
                            WorkingMode=5;
                            //double dy=GetCursordelta(0,"DD");
                            //DrawLine(0,dy);
                        }
                        break;
                    case VK_F2:
                        if(isMouseDraw){
                            DrawingErase=!DrawingErase;
                            if(DrawingErase){
                                SetPenSize(100);
                                SetEraseMode(TRUE);

                            }else{
                                SetPenSize(1);
                                SetEraseMode(FALSE);

                            }
                        }
                        break;
                    case VK_F3://F3 Drawing Mode
                        Title="Drawing Mode(F5 for Text;F3 for drawing)";
                        SetWindowTitle((char*)Title.c_str());
                        isInputText=FALSE;
                        isMouseDraw=TRUE;
                        FigureType=-1;

                        if(TIMERWORKING)
                        {   cancelTimer(TIMER_BLINK500);
                            TIMERWORKING=FALSE;
                            DrawCursor(TRUE);
                            SetEraseMode(FALSE);
                        }
                        WorkingMode=3;
                        break;
                    case VK_F4:
                        Title="Rectangle Mode";
                        SetWindowTitle((char*)Title.c_str());
                        //GraphicList* tmp=new GraphicList();
                        //list.insert(tmp);
                        WorkingMode=37;
                        break;
                    case VK_LEFT:

                            cancelTimer(TIMER_BLINK500);
                            DrawCursor(TRUE);
                            if(curintext>1){

                                curintext--;
                                char curtext[TEMP_STRING_LENGTH];
                                strncpy(curtext,text,curintext);
                                MovePen(textx+TextStringWidth(curtext),yt);
                            }
                            startTimer(TIMER_BLINK500,mseconds500);

                        break;
                    case VK_F7:

                        sprintf(test_length,"%lf",TextStringWidth((char*)"\0"));
                        MessageBoxA(NULL,test_length,"TestTitle",MB_OK);
                        break;
                    case VK_F8://Draw Rectangle
                        //UpdateDisplay();
                        FigureType=3;
                        isMouseDraw=FALSE;
                        isInputText=FALSE;
                        break;
                    case VK_RIGHT:

                            cancelTimer(TIMER_BLINK500);
                            DrawCursor(TRUE);
                            if(curintext<textlen){
                                curintext++;
                                char curtext[TEMP_STRING_LENGTH];
                                strncpy(curtext,text,curintext);
                                MovePen(textx+TextStringWidth(curtext),yt);
                            }
                            startTimer(TIMER_BLINK500,mseconds500);

                        break;
                    default:
                        break;
                }
            default:
                break;
        }
    }
}