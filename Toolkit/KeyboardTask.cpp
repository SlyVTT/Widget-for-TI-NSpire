#include "KeyboardTask.h"

#include <libndls.h>
#include <SDL/SDL_video.h>
#include <SDL/SDL_gfxPrimitives.h>

KeyboardTask::KeyboardTask()
{
    base=(unsigned short *)0x900E0010;
}

KeyboardTask::~KeyboardTask()
{
    //dtor
}


bool KeyboardTask::iskeypressed()
{
    //unsigned short *base=(unsigned short *)0x900E0010;
    uint16_t temp = base[0]+base[1]+base[2]+base[3]+base[4]+base[5]+base[6]+base[7];
    if (temp==0) return false;
    else return true;
}


void KeyboardTask::logic( )
{
    unsigned short temp;

    if (iskeypressed() || any_key_pressed())
    {
        //stringRGBA( screen, 50 , 10, "Key pressed", 255, 0, 0, 255);

        if (keypressevent)
        {
            keypressevent = false;
            keyreleaseevent = false;
        }
        else
        {
            keypressevent = true;
            keyreleaseevent = false;
        }

        // check if keys are pressed
        temp=base[0];
        if ( temp != 0 )
        {
            //stringRGBA( screen, 50 , 10, "Key pressed ligne 0", 255, 255, 255, 255);

            if ( (temp & 1) != 0 ) kbRET = true;
            if ( (temp & 2) != 0 ) kbENTER = true;
            if ( (temp & 4) != 0 ) {}; // No key assigned to this bit
            if ( (temp & 8) != 0 ) kbMINUSPAR = true;
            if ( (temp & 16) != 0 ) kbSPACE = true;
            if ( (temp & 32) != 0 ) kbZ = true;
            if ( (temp & 64) != 0 ) kbY = true;
            if ( (temp & 128) != 0 ) kb0 = true;
            if ( (temp & 256) != 0 ) kbQUESTION = true;
            if ( (temp & 512) != 0 ) kbON = true; // NOTE : this seems to be a particular case, does not work ??
            if ( (temp & 1024) != 0 ) {}; // No key assigned to this bit
        }

        temp=base[1];
        if ( temp != 0 )
        {
            //stringRGBA( screen, 50 , 10, "Key pressed ligne 1", 255, 255, 255, 255);

            if ( (temp & 1) != 0 ) kbX = true;
            if ( (temp & 2) != 0 ) kbW = true;
            if ( (temp & 4) != 0 ) kbV = true;
            if ( (temp & 8) != 0 ) kb3 = true;
            if ( (temp & 16) != 0 ) kbU = true;
            if ( (temp & 32) != 0 ) kbT = true;
            if ( (temp & 64) != 0 ) kbS = true;
            if ( (temp & 128) != 0 ) kb1 = true;
            if ( (temp & 256) != 0 ) kbPI = true;
            if ( (temp & 512) != 0 ) kbTRIG = true;
            if ( (temp & 1024) != 0 ) kb10X = true;
        }

        temp=base[2];
        if ( temp != 0 )
        {
            //stringRGBA( screen, 50 , 10, "Key pressed ligne 2", 255, 255, 255, 255);

            if ( (temp & 1) != 0 ) kbR = true;
            if ( (temp & 2) != 0 ) kbQ = true;
            if ( (temp & 4) != 0 ) kbP = true;
            if ( (temp & 8) != 0 ) kb6 = true;
            if ( (temp & 16) != 0 ) kbO = true;
            if ( (temp & 32) != 0 ) kbN = true;
            if ( (temp & 64) != 0 ) kbM = true;
            if ( (temp & 128) != 0 ) kb4 = true;
            if ( (temp & 256) != 0 ) kbEE = true;
            if ( (temp & 512) != 0 ) kbX2 = true;
            if ( (temp & 1024) != 0 ) {}; // No key assigned to this bit
        }

        temp=base[3];
        if ( temp != 0 )
        {
            //stringRGBA( screen, 50 , 10, "Key pressed ligne 3", 255, 255, 255, 255);

            if ( (temp & 1) != 0 ) kbL = true;
            if ( (temp & 2) != 0 ) kbK = true;
            if ( (temp & 4) != 0 ) kbJ = true;
            if ( (temp & 8) != 0 ) kb9 = true;
            if ( (temp & 16) != 0 ) kbI = true;
            if ( (temp & 32) != 0 ) kbH = true;
            if ( (temp & 64) != 0 ) kbG = true;
            if ( (temp & 128) != 0 ) kb7 = true;
            if ( (temp & 256) != 0 ) kbDIV = true;
            if ( (temp & 512) != 0 ) kbEX = true;
            if ( (temp & 1024) != 0 ) {}; // No key assigned to this bit
        }

        temp=base[4];
        if ( temp != 0 )
        {
            //stringRGBA( screen, 50 , 10, "Key pressed ligne 4", 255, 255, 255, 255);

            if ( (temp & 1) != 0 ) kbF = true;
            if ( (temp & 2) != 0 ) kbE = true;
            if ( (temp & 4) != 0 ) kbD = true;
            if ( (temp & 8) != 0 ) {}; // No key assigned to this bit
            if ( (temp & 16) != 0 ) kbC = true;
            if ( (temp & 32) != 0 ) kbB = true;
            if ( (temp & 64) != 0 ) kbA = true;
            if ( (temp & 128) != 0 ) kbEQUAL = true;
            if ( (temp & 256) != 0 ) kbMULTIPLY = true;
            if ( (temp & 512) != 0 ) kbPOWER = true;
            if ( (temp & 1024) != 0 ) {}; // No key assigned to this bit
        }

        temp=base[5];
        if ( temp != 0 )
        {
            //stringRGBA( screen, 50 , 10, "Key pressed ligne 5", 255, 255, 255, 255);

            if ( (temp & 1) != 0 ) {}; // No key assigned to this bit
            if ( (temp & 2) != 0 ) kbVAR = true;
            if ( (temp & 4) != 0 ) kbMINUS = true;
            if ( (temp & 8) != 0 ) kbPARCLOSE = true;
            if ( (temp & 16) != 0 ) kbDOT = true;
            if ( (temp & 32) != 0 ) kbPAROPEN = true;
            if ( (temp & 64) != 0 ) kb5 = true;
            if ( (temp & 128) != 0 ) kbCATALOG = true;
            if ( (temp & 256) != 0 ) kbFRAC = true;
            if ( (temp & 512) != 0 ) kbDEL = true;
            if ( (temp & 1024) != 0 ) kbSCRATCH = true;
        }

        temp=base[6];
        if ( temp != 0 )
        {
            //stringRGBA( screen, 50 , 10, "Key pressed ligne 6", 255, 255, 255, 255);

            if ( (temp & 1) != 0 ) kbFLAG = true;
            if ( (temp & 2) != 0 ) {}; // No key assigned to this bit
            if ( (temp & 4) != 0 ) kbPLUS = true;
            if ( (temp & 8) != 0 ) kbDOC = true;
            if ( (temp & 16) != 0 ) kb2 = true;
            if ( (temp & 32) != 0 ) kbMENU = true;
            if ( (temp & 64) != 0 ) kb8 = true;
            if ( (temp & 128) != 0 ) kbESC = true;
            if ( (temp & 256) != 0 ) {}; // No key assigned to this bit
            if ( (temp & 512) != 0 ) kbTAB = true;
            if ( (temp & 1024) != 0 ) {}; // No key assigned to this bit
        }

        temp=base[7];
        if ( temp != 0 )
        {
            //stringRGBA( screen, 50 , 10, "Key pressed ligne 7", 255, 255, 255, 255);

            if ( (temp & 1) != 0 ) {}; // No key assigned to this bit
            if ( (temp & 2) != 0 ) {}; // No key assigned to this bit
            if ( (temp & 4) != 0 ) {}; // No key assigned to this bit
            if ( (temp & 8) != 0 ) {}; // No key assigned to this bit
            if ( (temp & 16) != 0 ) {}; // No key assigned to this bit
            if ( (temp & 32) != 0 ) {}; // No key assigned to this bit
            if ( (temp & 64) != 0 )  {}; // No key assigned to this bit
            if ( (temp & 128) != 0 ) {}; // No key assigned to this bit
            if ( (temp & 256) != 0 ) kbSHIFT = true;
            if ( (temp & 512) != 0 ) kbCTRL = true;
            if ( (temp & 1024) != 0 ) kbCOMMA = true;
        }


    }
    else
    {

        if (keypressevent)
        {
            keypressevent = false;
            keyreleaseevent = true;
        }
        else
        {
            keypressevent = false;
            keyreleaseevent = false;
        }


        { // First adress block
            kbRET = false;
            kbENTER = false;
            kbMINUSPAR = false;
            kbSPACE = false;
            kbZ = false;
            kbY = false;
            kb0 = false;
            kbQUESTION = false;
            kbON = false;
        }

        { // Second adress block
            kbX = false;
            kbW = false;
            kbV = false;
            kb3 = false;
            kbU = false;
            kbT = false;
            kbS = false;
            kb1 = false;
            kbPI = false;
            kbTRIG = false;
            kb10X = false;
        }

        { // Third adress block
            kbR = false;
            kbQ = false;
            kbP = false;
            kb6 = false;
            kbO = false;
            kbN = false;
            kbM = false;
            kb4 = false;
            kbEE = false;
            kbX2 = false;
        }

        { // Fourth adress block
            kbL = false;
            kbK = false;
            kbJ = false;
            kb9 = false;
            kbI = false;
            kbH = false;
            kbG = false;
            kb7 = false;
            kbDIV = false;
            kbEX = false;
        }

        { // Fifth adress block
            kbF = false;
            kbE = false;
            kbD = false;
            kbC = false;
            kbB = false;
            kbA = false;
            kbEQUAL = false;
            kbMULTIPLY = false;
            kbPOWER = false;
        }

        { // Sixth adress block
            kbVAR = false;
            kbMINUS = false;
            kbPARCLOSE = false;
            kbDOT = false;
            kbPAROPEN = false;
            kb5 = false;
            kbCATALOG = false;
            kbFRAC = false;
            kbDEL = false;
            kbSCRATCH = false;
        }

        { // Seventh adress block
            kbFLAG = false;
            kbPLUS = false;
            kbDOC = false;
            kb2 = false;
            kbMENU = false;
            kb8 = false;
            kbESC = false;
            kbTAB = false;
        }

        { // Eigth adress block
            kbSHIFT = false;
            kbCTRL = false;
            kbCOMMA = false;
        }

    }

    keyevent_arrow = false;

    if (isKeyPressed( KEY_NSPIRE_UP ))
    {
        keyevent_arrow = true;
        kbUP = true;
    }
    else
    {
        kbUP = false;
    }

    if (isKeyPressed( KEY_NSPIRE_UPRIGHT ))
    {
        keyevent_arrow = true;
        kbUPRIGHT = true;
    }
    else
    {
        kbUPRIGHT = false;
    }

    if (isKeyPressed( KEY_NSPIRE_RIGHT ))
    {
        keyevent_arrow = true;
        kbRIGHT = true;
    }
    else
    {
        kbRIGHT = false;
    }

    if (isKeyPressed( KEY_NSPIRE_RIGHTDOWN ))
    {
        keyevent_arrow = true;
        kbRIGHTDOWN = true;
    }
    else
    {
        kbRIGHTDOWN = false;
    }

    if (isKeyPressed( KEY_NSPIRE_DOWN ))
    {
        keyevent_arrow = true;
        kbDOWN = true;
    }
    else
    {
        kbDOWN = false;
    }

    if (isKeyPressed( KEY_NSPIRE_DOWNLEFT ))
    {
        keyevent_arrow = true;
        kbDOWNLEFT = true;
    }
    else
    {
        kbDOWNLEFT = false;
    }

    if (isKeyPressed( KEY_NSPIRE_LEFT ))
    {
        keyevent_arrow = true;
        kbLEFT = true;
    }
    else
    {
        kbLEFT = false;
    }

    if (isKeyPressed( KEY_NSPIRE_LEFTUP ))
    {
        keyevent_arrow = true;
        kbLEFTUP = true;
    }
    else
    {
        kbLEFTUP = false;
    }


    if (keypressevent || keyreleaseevent)
    {
        keyevent = true;
    }
    else
    {
        keyevent = false;
    }

}
