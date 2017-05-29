#include "graphics.h"
#include "extgraph.h"
//#include <string>
#include "GraphicList.h"
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
using namespace MyGraphics;
namespace MyGraphics{

/*extern*/ char text[TEMP_STRING_LENGTH];
/*extern*/ BOOL TIMERWORKING=FALSE;
/*extern*/ double curx=0, cury=0;
/*extern*/ BOOL isInputText =FALSE;
/*extern*/ BOOL isMouseDraw =TRUE;
/*extern*/ double textx=0, texty=0;
/*extern*/ size_t curintext=0;
/*extern*/ int FigureType=0;
/*extern*/ int DrawingErase=0;
/*extern*/ int textlen=0;
/*extern*/ int WorkingMode=0;
/*extern*/ GraphicList list;
    GraphicList* theChosenOne=NULL;
    BOOL hasChosenOne=FALSE;
}
void Main() {

        InitGraphics();
        //std::string Title = ;
        //std::string color = ;
        SetWindowTitle((char *) "Drawing Mode(F5 for Text;F3 for drawing)");
        registerMouseEvent(MouseEventProcess);
        registerCharEvent(CharEventProcess);
        registerKeyboardEvent(KeyboardEventProcess);
        registerTimerEvent(TimerEventProcess);
        SetPenColor((char *) "Red");
        SetPenSize(2);
        MovePen(4, 4);
}

