#ifndef KEYBOARDTASK_H
#define KEYBOARDTASK_H

#include <SDL/SDL.h>

class KeyboardTask
{
    public:
        KeyboardTask();
        virtual ~KeyboardTask();
        virtual void logic();

        virtual bool iskeypressed();
        virtual bool iskeyevent( ) { return keyevent; };
        virtual bool iskeypressevent( ) { return keypressevent; };
        virtual bool iskeyreleaseevent( ) { return keyreleaseevent; };
        virtual bool iskeyarrowevent( ) { return keyevent_arrow; };

        bool keypressevent = false;
        bool keyreleaseevent = false;
        bool keyevent = false;
        bool keyevent_arrow = false;
        bool capsonmode = false;

        // First adress block
        bool kbRET = false;
        bool kbENTER = false;
        bool kbMINUSPAR = false;
        bool kbSPACE = false;
        bool kbZ = false;
        bool kbY = false;
        bool kb0 = false;
        bool kbQUESTION = false;
        bool kbON = false;

        // Second adress block
        bool kbX = false;
        bool kbW = false;
        bool kbV = false;
        bool kb3 = false;
        bool kbU = false;
        bool kbT = false;
        bool kbS = false;
        bool kb1 = false;
        bool kbPI = false;
        bool kbTRIG = false;
        bool kb10X = false;

        // Third adress block
        bool kbR = false;
        bool kbQ = false;
        bool kbP = false;
        bool kb6 = false;
        bool kbO = false;
        bool kbN = false;
        bool kbM = false;
        bool kb4 = false;
        bool kbEE = false;
        bool kbX2 = false;

        // Fourth adress block
        bool kbL = false;
        bool kbK = false;
        bool kbJ = false;
        bool kb9 = false;
        bool kbI = false;
        bool kbH = false;
        bool kbG = false;
        bool kb7 = false;
        bool kbDIV = false;
        bool kbEX = false;

        // Fifth adress block
        bool kbF = false;
        bool kbE = false;
        bool kbD = false;
        bool kbC = false;
        bool kbB = false;
        bool kbA = false;
        bool kbEQUAL = false;
        bool kbMULTIPLY = false;
        bool kbPOWER = false;

        // Sixth adress block
        bool kbVAR = false;
        bool kbMINUS = false;
        bool kbPARCLOSE = false;
        bool kbDOT = false;
        bool kbPAROPEN = false;
        bool kb5 = false;
        bool kbCATALOG = false;
        bool kbFRAC = false;
        bool kbDEL = false;
        bool kbSCRATCH = false;

        // Seventh adress block
        bool kbFLAG = false;
        bool kbPLUS = false;
        bool kbDOC = false;
        bool kb2 = false;
        bool kbMENU = false;
        bool kb8 = false;
        bool kbESC = false;
        bool kbTAB = false;

        // Eigth adress block
        bool kbSHIFT = false;
        bool kbCTRL = false;
        bool kbCOMMA = false;

        // Keys of the Touchpad
        bool kbUP = false;
        bool kbUPRIGHT = false;
        bool kbRIGHT = false;
        bool kbRIGHTDOWN = false;
        bool kbDOWN = false;
        bool kbDOWNLEFT = false;
        bool kbLEFT = false;
        bool kbLEFTUP = false;


    private:
        unsigned short *base;
};

#endif // KEYBOARDTASK_H
