#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_gfxPrimitives_font.h>
#include <SDL/SDL_video.h>

#include "Widget.h"
#include "ButtonWidget.h"
#include "MiniButtonWidget.h"
#include "WidgetApplication.h"
#include "InputWidget.h"
#include "CheckBoxWidget.h"
#include "WindowWidget.h"
#include "LabelWidget.h"
#include "FrameWidget.h"
#include "SliderWidget.h"
#include "ContainerHWidget.h"
#include "ContainerVWidget.h"
#include "DesktopWidget.h"

#include "CursorTask.h"
#include "KeyboardTask.h"


void on_click( char *text )
{
        /*
        char affiche[50];
        sprintf(affiche, "%s : Button Pressed", text );
        stringRGBA( screen, 50 , 10, affiche, 0, 255, 0, 255);
        SDL_Flip( screen );
        */
}

void on_release( char *text )
{
        /*
        char affiche[50];
        sprintf(affiche, "%s : Button Released", text );
        stringRGBA( screen, 50 , 10, affiche, 255, 0, 0, 255);
        SDL_Flip( screen );
        */
}

void on_hover( char *text )
{
        /*
        char affiche[50];
        sprintf(affiche, "%s : Button Hovered", text );
        stringRGBA( screen, 50 , 10, affiche, 255, 255, 0, 255);
        SDL_Flip( screen );
        */
}


int main ( int argc, char** argv )
{
    bool done = false;

    char display[50];


    WidgetApplication *MyApp = new WidgetApplication();
    //MyApp->setuniformbackgroundcolor(255, 255, 255);
    MyApp->setbackgroundpicture( "/documents/Widget/001.bmp.tns" );


    DesktopWidget *desktop1 = new DesktopWidget( "First Desktop", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr );

    WindowWidget *window = new WindowWidget( "This is a Window", 20, 30, 250, 160, desktop1 );

    LabelWidget *label = new LabelWidget("I am a Label and this is a Input:", 25, 45, 240, 15, window );
    label->setalignment( left );

    InputWidget *input = new InputWidget( "Test 2", 25, 60, 240, 15, window );
    input->setcontent( "Hello World !!! This is the best widget I have ever seen in my Life !!!");

    ButtonWidget *button = new ButtonWidget( "Active Button", 30, 170, 110, 15, window );

    ButtonWidget *button2 = new ButtonWidget( "Disabled Button", 150, 170, 110, 15, window );
    button2->disable();

/*
    CheckBoxWidget * check1 = new CheckBoxWidget ("Checkbox Square tick", 25, 85, 200, 12, window );
    check1->settype( Square_Tick );

    CheckBoxWidget * check2 = new CheckBoxWidget ("Checkbox Cross tick", 25, 105, 200, 12, window );
    check2->settype( Cross_Tick );
    check2->disable();

    CheckBoxWidget * check3 = new CheckBoxWidget ("Checkbox unchecked", 25, 125, 200, 12, window );
    check3->settype( Cross_Tick );
    check3->disable();
*/

    FrameWidget *frame1 = new FrameWidget( "Frame Active", 25, 85, 240, 35, window );

    //FrameWidget *frame2 = new FrameWidget( "Frame Disabled", 25, 125, 240, 35, window );
    //frame2->disable();

    SliderWidget *slider = new SliderWidget( "Slider", 25, 125, 240, 35, window );

/*

    MiniButtonWidget *bottom = new MiniButtonWidget (" ", 20, 150, 12, 12, nullptr );
    bottom->settype( Bottom_Arrow );

    MiniButtonWidget *up = new MiniButtonWidget (" ", 35, 150, 12, 12, nullptr );
    up->settype( Up_Arrow );

    MiniButtonWidget *left = new MiniButtonWidget (" ", 50, 150, 12, 12, nullptr );
    left->settype( Left_Arrow );

    MiniButtonWidget *right = new MiniButtonWidget (" ", 65, 150, 12, 12, nullptr );
    right->settype( Right_Arrow );

    MiniButtonWidget *close = new MiniButtonWidget (" ", 80, 150, 12, 12, nullptr );
    close->settype( Close_Symbol );

    MiniButtonWidget *question = new MiniButtonWidget (" ", 95, 150, 12, 12, nullptr );
    question->settype( Question_Symbol );

    MiniButtonWidget *exclamation = new MiniButtonWidget (" ", 110, 150, 12, 12, nullptr );
    exclamation->settype( Exclamation_Symbol );


    CheckBoxWidget * check1 = new CheckBoxWidget ("Checkbox Square tick", 10, 175, 150, 12, nullptr );
    check1->settype( Square_Tick );

    CheckBoxWidget * check2 = new CheckBoxWidget ("Checkbox Cross tick", 10, 190, 150, 12, nullptr );
    check2->settype( Cross_Tick );


    MyApp->addchild( button );
    MyApp->addchild( input );

    MyApp->addchild( bottom );
    MyApp->addchild( up );
    MyApp->addchild( left );
    MyApp->addchild( right );
    MyApp->addchild( close );
    MyApp->addchild( question );
    MyApp->addchild( exclamation );

    MyApp->addchild( check1 );
    MyApp->addchild( check2 );
*/

    MyApp->addchild( desktop1 );

/*

    ButtonWidget *buttonchild = new ButtonWidget( "Child Button", 50, 100, 120, 25, button );

    ButtonWidget *Arrowleft = new ButtonWidget( "\u0011", 150, 155, 10, 10, button );
    ButtonWidget *Arrowright = new ButtonWidget( "\u0010", 175, 155, 10, 10, button );
    ButtonWidget *Arrowup = new ButtonWidget( "\u001e", 200, 155, 10, 10, button );
    ButtonWidget *Arrowdown = new ButtonWidget( "\u001f", 225, 155, 10, 10, button );
    ButtonWidget *Arrowclose = new ButtonWidget( "\u0001", 250, 155, 10, 10, button );
*/

    MyApp->adddesktop();
    MyApp->setcurrentdesktop( 1 );
    MyApp->setbackgroundpicture( "/documents/Widget/002.bmp.tns" );
    //button->linkonclick( on_click );
    //button->linkonrelease( on_release );
    //button->linkonhover( on_hover );

    DesktopWidget *desktop2 = new DesktopWidget( "First Desktop", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr );

    WindowWidget *window2 = new WindowWidget( "This is a Window", 50, 20, 250, 100, desktop2 );
    ContainerVWidget *containerv = new ContainerVWidget( "container", 1, 1, 1, 1, window2 );

    ContainerHWidget *containerh = new ContainerHWidget( "container", 1, 1, 1, 1, nullptr );
    ContainerHWidget *containerh2 = new ContainerHWidget( "container", 1, 1, 1, 1, nullptr );

    LabelWidget *labelA = new LabelWidget( "This is automatic positioning", 1, 1, 1, 1, nullptr );

    ButtonWidget *buttonB = new ButtonWidget( "Hide window", 1, 1, 1, 1, nullptr );
    ButtonWidget *buttonC = new ButtonWidget( "Show Window", 1, 1, 1, 1, nullptr );

    ButtonWidget *buttonD = new ButtonWidget( "Disable window", 1, 1, 1, 1, nullptr );
    ButtonWidget *buttonE = new ButtonWidget( "Enable Window", 1, 1, 1, 1, nullptr );

    ButtonWidget *buttonF = new ButtonWidget( "Quit", 1, 1, 1, 1, nullptr );

    containerv->addchild( labelA );

    containerh->addchild( buttonB );
    containerh->addchild( buttonC );

    containerv->addchild( containerh );

    containerh2->addchild( buttonD );
    containerh2->addchild( buttonE );

    containerv->addchild( containerh2 );

    containerv->addchild( buttonF );

    containerv->adjust();
    containerh->adjust();
    containerh2->adjust();

    MyApp->addchild( desktop2 );



    // We render the app for the first time so what we can see what's happening on the screen
    MyApp->render();


    while (!done)
    {

        MyApp->logic();
        //keyboard->logic();

        int Sint=slider->getvalueint();
        float Sfloat=slider->getvaluefloat();

        sprintf( display, "Slider Int : %d - Float %f", Sint , Sfloat );
        label->setlabel( (char *)display );



        if (MyApp->keyboard->kbCTRL && MyApp->keyboard->kbESC) done = true;

        if (MyApp->keyboard->kbCTRL && MyApp->keyboard->kbLEFT)
        {
            MyApp->setpreviousdesktop();
            SDL_Delay( 250 );
            //MyApp->setcurrentdesktop( 0 );
        };

        if (MyApp->keyboard->kbCTRL && MyApp->keyboard->kbRIGHT)
        {
            MyApp->setnextdesktop();
            SDL_Delay( 250 );
            //MyApp->setcurrentdesktop( 1 );
        };


        if (buttonB->ispressed()) window->setinvisible();
        if (buttonC->ispressed()) window->setvisible();
        if (buttonD->ispressed()) window->disable();
        if (buttonE->ispressed()) window->enable();


        if (MyApp->keyboard->kb7) window->setinvisible();
        if (MyApp->keyboard->kb8) window->setvisible();
        if (MyApp->keyboard->kb4) window->disable();
        if (MyApp->keyboard->kb5) window->enable();

        if (buttonF->ispressed()) done=true;


        //MyApp->render();

    }

    return 0;
}
