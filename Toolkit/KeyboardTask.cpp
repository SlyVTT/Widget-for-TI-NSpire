#include "KeyboardTask.h"

#include <libndls.h>
#include <SDL/SDL_video.h>
#include <SDL/SDL_gfxPrimitives.h>


KeyboardTask::KeyboardTask()
{
       base=(unsigned short *)0x900E0010;
       if (is_cx2)
              specialON=(unsigned short *)0x90140810;
       else
              specialON=(unsigned short *)0x900B0028;

}

KeyboardTask::~KeyboardTask()
{
       //dtor
}


bool KeyboardTask::iskeypressed()
{
       uint16_t temp = base[0]+base[1]+base[2]+base[3]+base[4]+base[5]+base[6]+base[7];
       if (is_cx2 && (temp==0) && ((specialON[0] & 256) != 0)) return false;
       else if (!is_cx2 && (temp==0) && ((specialON[0] & 16) != 0)) return false;
       else return true;
}


bool KeyboardTask::iskeyevent( )
{
       return keyevent;
};


bool KeyboardTask::iskeypressevent( )
{
       return keypressevent;
};


bool KeyboardTask::iskeyreleaseevent( )
{
       return keyreleaseevent;
};


bool KeyboardTask::iskeyarrowevent( )
{
       return keyevent_arrow;
};


void KeyboardTask::setselection( std::string select )
{
       selection = select;
}


std::string KeyboardTask::getselection( void )
{
       return selection;
}


void KeyboardTask::flushselection( void )
{
       selection.clear();
}



void KeyboardTask::logic( )
{
       unsigned short temp;

       if (iskeypressed() || any_key_pressed())
       {
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
       }

       //The ON/HOME Key has a special treatment in the TI nSpire CX and CX II
       //And is not mapped as it should be
       if ( is_cx2 )
       {
              if ((specialON[0] & 256) == 0 ) kbON = true;
              else kbON = false;
       }
       else
       {
              if ((specialON[0] & 16) == 0 ) kbON = true;
              else kbON = false;
       }

       // check if keys are pressed
       temp=base[0];
       //if ( temp != 0 )
       {
              if ( (temp & 1) != 0 ) kbRET = true;
              else kbRET = false;
              if ( (temp & 2) != 0 ) kbENTER = true;
              else kbENTER = false;
              if ( (temp & 4) != 0 ) {}; // No key assigned to this bit
              if ( (temp & 8) != 0 ) kbMINUSPAR = true;
              else kbMINUSPAR = false;
              if ( (temp & 16) != 0 ) kbSPACE = true;
              else kbSPACE = false;
              if ( (temp & 32) != 0 ) kbZ = true;
              else kbZ = false;
              if ( (temp & 64) != 0 ) kbY = true;
              else kbY = false;
              if ( (temp & 128) != 0 ) kb0 = true;
              else kb0 = false;
              if ( (temp & 256) != 0 ) kbQUESTION = true;
              else kbQUESTION = false;
              if ( (temp & 512) != 0 ) {}; // NOTE : this seems to be a particular case, does not work ?? was formerly mapped to kbON
              if ( (temp & 1024) != 0 ) {}; // No key assigned to this bit
       }

       temp=base[1];
       //if ( temp != 0 )
       {
              if ( (temp & 1) != 0 ) kbX = true;
              else kbX = false;
              if ( (temp & 2) != 0 ) kbW = true;
              else kbW = false;
              if ( (temp & 4) != 0 ) kbV = true;
              else kbV = false;
              if ( (temp & 8) != 0 ) kb3 = true;
              else kb3 = false;
              if ( (temp & 16) != 0 ) kbU = true;
              else kbU = false;
              if ( (temp & 32) != 0 ) kbT = true;
              else kbT = false;
              if ( (temp & 64) != 0 ) kbS = true;
              else kbS = false;
              if ( (temp & 128) != 0 ) kb1 = true;
              else kb1 = false;
              if ( (temp & 256) != 0 ) kbPI = true;
              else kbPI = false;
              if ( (temp & 512) != 0 ) kbTRIG = true;
              else kbTRIG = false;
              if ( (temp & 1024) != 0 ) kb10X = true;
              else kb10X = false;
       }

       temp=base[2];
       //if ( temp != 0 )
       {
              if ( (temp & 1) != 0 ) kbR = true;
              else kbR = false;
              if ( (temp & 2) != 0 ) kbQ = true;
              else kbQ = false;
              if ( (temp & 4) != 0 ) kbP = true;
              else kbP = false;
              if ( (temp & 8) != 0 ) kb6 = true;
              else kb6 = false;
              if ( (temp & 16) != 0 ) kbO = true;
              else kbO = false;
              if ( (temp & 32) != 0 ) kbN = true;
              else kbN = false;
              if ( (temp & 64) != 0 ) kbM = true;
              else kbM = false;
              if ( (temp & 128) != 0 ) kb4 = true;
              else kb4 = false;
              if ( (temp & 256) != 0 ) kbEE = true;
              else kbEE = false;
              if ( (temp & 512) != 0 ) kbX2 = true;
              else kbX2 = false;
              if ( (temp & 1024) != 0 ) {}; // No key assigned to this bit
       }

       temp=base[3];
       //if ( temp != 0 )
       {
              if ( (temp & 1) != 0 ) kbL = true;
              else kbL = false;
              if ( (temp & 2) != 0 ) kbK = true;
              else kbK = false;
              if ( (temp & 4) != 0 ) kbJ = true;
              else kbJ = false;
              if ( (temp & 8) != 0 ) kb9 = true;
              else kb9 = false;
              if ( (temp & 16) != 0 ) kbI = true;
              else kbI = false;
              if ( (temp & 32) != 0 ) kbH = true;
              else kbH = false;
              if ( (temp & 64) != 0 ) kbG = true;
              else kbG = false;
              if ( (temp & 128) != 0 ) kb7 = true;
              else kb7 = false;
              if ( (temp & 256) != 0 ) kbDIV = true;
              else kbDIV = false;
              if ( (temp & 512) != 0 ) kbEX = true;
              else kbEX = false;
              if ( (temp & 1024) != 0 ) {}; // No key assigned to this bit
       }

       temp=base[4];
       //if ( temp != 0 )
       {
              if ( (temp & 1) != 0 ) kbF = true;
              else kbF = false;
              if ( (temp & 2) != 0 ) kbE = true;
              else kbE = false;
              if ( (temp & 4) != 0 ) kbD = true;
              else kbD = false;
              if ( (temp & 8) != 0 ) {}; // No key assigned to this bit
              if ( (temp & 16) != 0 ) kbC = true;
              else kbC = false;
              if ( (temp & 32) != 0 ) kbB = true;
              else kbB = false;
              if ( (temp & 64) != 0 ) kbA = true;
              else kbA = false;
              if ( (temp & 128) != 0 ) kbEQUAL = true;
              else kbEQUAL = false;
              if ( (temp & 256) != 0 ) kbMULTIPLY = true;
              else kbMULTIPLY = false;
              if ( (temp & 512) != 0 ) kbPOWER = true;
              else kbPOWER = false;
              if ( (temp & 1024) != 0 ) {}; // No key assigned to this bit
       }

       temp=base[5];
       //if ( temp != 0 )
       {
              if ( (temp & 1) != 0 ) {}; // No key assigned to this bit
              if ( (temp & 2) != 0 ) kbVAR = true;
              else kbVAR = false;
              if ( (temp & 4) != 0 ) kbMINUS = true;
              else kbMINUS = false;
              if ( (temp & 8) != 0 ) kbPARCLOSE = true;
              else kbPARCLOSE = false;
              if ( (temp & 16) != 0 ) kbDOT = true;
              else kbDOT = false;
              if ( (temp & 32) != 0 ) kbPAROPEN = true;
              else kbPAROPEN = false;
              if ( (temp & 64) != 0 ) kb5 = true;
              else kb5 = false;
              if ( (temp & 128) != 0 ) kbCATALOG = true;
              else kbCATALOG = false;
              if ( (temp & 256) != 0 ) kbFRAC = true;
              else kbFRAC = false;
              if ( (temp & 512) != 0 ) kbDEL = true;
              else kbDEL = false;
              if ( (temp & 1024) != 0 ) kbSCRATCH = true;
              else kbSCRATCH = false;
       }

       temp=base[6];
       //if ( temp != 0 )
       {
              if ( (temp & 1) != 0 ) kbFLAG = true;
              else kbFLAG = false;
              if ( (temp & 2) != 0 ) {}; // No key assigned to this bit
              if ( (temp & 4) != 0 ) kbPLUS = true;
              else kbPLUS = false;
              if ( (temp & 8) != 0 ) kbDOC = true;
              else kbDOC = false;
              if ( (temp & 16) != 0 ) kb2 = true;
              else kb2 = false;
              if ( (temp & 32) != 0 ) kbMENU = true;
              else kbMENU = false;
              if ( (temp & 64) != 0 ) kb8 = true;
              else kb8 = false;
              if ( (temp & 128) != 0 ) kbESC = true;
              else kbESC = false;
              if ( (temp & 256) != 0 ) {}; // No key assigned to this bit
              if ( (temp & 512) != 0 ) kbTAB = true;
              else kbTAB = false;
              if ( (temp & 1024) != 0 ) {}; // No key assigned to this bit
       }

       temp=base[7];
       //if ( temp != 0 )
       {
              if ( (temp & 1) != 0 ) {}; // No key assigned to this bit
              if ( (temp & 2) != 0 ) {}; // No key assigned to this bit
              if ( (temp & 4) != 0 ) {}; // No key assigned to this bit
              if ( (temp & 8) != 0 ) {}; // No key assigned to this bit
              if ( (temp & 16) != 0 ) {}; // No key assigned to this bit
              if ( (temp & 32) != 0 ) {}; // No key assigned to this bit
              if ( (temp & 64) != 0 )  {}; // No key assigned to this bit
              if ( (temp & 128) != 0 ) {}; // No key assigned to this bit
              if ( (temp & 256) != 0 ) kbSHIFT = true;
              else kbSHIFT = false;
              if ( (temp & 512) != 0 ) kbCTRL = true;
              else kbCTRL = false;
              if ( (temp & 1024) != 0 ) kbCOMMA = true;
              else kbCOMMA = false;
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


       if (keypressevent)
       {
              // if not already locked in capitals and SHIFT+CTRL are pressed together --> we switch to capital mode
              if (!capsonmode && kbCTRL && kbSHIFT) capsonmode=true;
              //if capital mode is on and SHIFT is pressed without CTRL --> we switch back to normal mode
              else if (capsonmode && !kbCTRL && kbSHIFT) capsonmode = false;
              //if capital mode is on and CTRL is pressed without SHIFT --> we switch back to normal mode
              else if (capsonmode && kbCTRL && !kbSHIFT) capsonmode = false;
       }

}


char KeyboardTask::asciiget( )
{
       this->logic();

       //start scrutinizing the keyboard
       // first we look at the letter keys
       if (keyevent && kbA && !capsonmode && !kbSHIFT && ! kbCTRL) return 'a';
       if (keyevent && kbA && (capsonmode || kbSHIFT) && !kbCTRL) return 'A';
       if (keyevent && kbA && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbB && !capsonmode && !kbSHIFT && ! kbCTRL) return 'b';
       if (keyevent && kbB && (capsonmode || kbSHIFT) && !kbCTRL) return 'B';
       if (keyevent && kbB && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbC && !capsonmode && !kbSHIFT && ! kbCTRL) return 'c';
       if (keyevent && kbC && (capsonmode || kbSHIFT) && !kbCTRL) return 'C';
       if (keyevent && kbC && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke   /!\ this is COPY shortcut

       if (keyevent && kbD && !capsonmode && !kbSHIFT && ! kbCTRL) return 'd';
       if (keyevent && kbD && (capsonmode || kbSHIFT) && !kbCTRL) return 'D';
       if (keyevent && kbD && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbE && !capsonmode && !kbSHIFT && ! kbCTRL) return 'e';
       if (keyevent && kbE && (capsonmode || kbSHIFT) && !kbCTRL) return 'E';
       if (keyevent && kbE && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbF && !capsonmode && !kbSHIFT && ! kbCTRL) return 'f';
       if (keyevent && kbF && (capsonmode || kbSHIFT) && !kbCTRL) return 'F';
       if (keyevent && kbF && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbG && !capsonmode && !kbSHIFT && ! kbCTRL) return 'g';
       if (keyevent && kbG && (capsonmode || kbSHIFT) && !kbCTRL) return 'G';
       if (keyevent && kbG && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbH && !capsonmode && !kbSHIFT && ! kbCTRL) return 'h';
       if (keyevent && kbH && (capsonmode || kbSHIFT) && !kbCTRL) return 'H';
       if (keyevent && kbH && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbI && !capsonmode && !kbSHIFT && ! kbCTRL) return 'i';
       if (keyevent && kbI && (capsonmode || kbSHIFT) && !kbCTRL) return 'I';
       if (keyevent && kbI && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbJ && !capsonmode && !kbSHIFT && ! kbCTRL) return 'j';
       if (keyevent && kbJ && (capsonmode || kbSHIFT) && !kbCTRL) return 'J';
       if (keyevent && kbJ && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbK && !capsonmode && !kbSHIFT && ! kbCTRL) return 'k';
       if (keyevent && kbK && (capsonmode || kbSHIFT) && !kbCTRL) return 'K';
       if (keyevent && kbK && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbL && !capsonmode && !kbSHIFT && ! kbCTRL) return 'l';
       if (keyevent && kbL && (capsonmode || kbSHIFT) && !kbCTRL) return 'L';
       if (keyevent && kbL && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbM && !capsonmode && !kbSHIFT && ! kbCTRL) return 'm';
       if (keyevent && kbM && (capsonmode || kbSHIFT) && !kbCTRL) return 'M';
       if (keyevent && kbM && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbN && !capsonmode && !kbSHIFT && ! kbCTRL) return 'n';
       if (keyevent && kbN && (capsonmode || kbSHIFT) && !kbCTRL) return 'N';
       if (keyevent && kbN && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbO && !capsonmode && !kbSHIFT && ! kbCTRL) return 'o';
       if (keyevent && kbO && (capsonmode || kbSHIFT) && !kbCTRL) return 'O';
       if (keyevent && kbO && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbP && !capsonmode && !kbSHIFT && ! kbCTRL) return 'p';
       if (keyevent && kbP && (capsonmode || kbSHIFT) && !kbCTRL) return 'P';
       if (keyevent && kbP && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbQ && !capsonmode && !kbSHIFT && ! kbCTRL) return 'q';
       if (keyevent && kbQ && (capsonmode || kbSHIFT) && !kbCTRL) return 'Q';
       if (keyevent && kbQ && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbR && !capsonmode && !kbSHIFT && ! kbCTRL) return 'r';
       if (keyevent && kbR && (capsonmode || kbSHIFT) && !kbCTRL) return 'R';
       if (keyevent && kbR && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbS && !capsonmode && !kbSHIFT && ! kbCTRL) return 's';
       if (keyevent && kbS && (capsonmode || kbSHIFT) && !kbCTRL) return 'S';
       if (keyevent && kbS && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbT && !capsonmode && !kbSHIFT && ! kbCTRL) return 't';
       if (keyevent && kbT && (capsonmode || kbSHIFT) && !kbCTRL) return 'T';
       if (keyevent && kbT && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbU && !capsonmode && !kbSHIFT && ! kbCTRL) return 'u';
       if (keyevent && kbU && (capsonmode || kbSHIFT) && !kbCTRL) return 'U';
       if (keyevent && kbU && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbV && !capsonmode && !kbSHIFT && ! kbCTRL) return 'v';
       if (keyevent && kbV && (capsonmode || kbSHIFT) && !kbCTRL) return 'V';
       if (keyevent && kbV && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke   /!\ this is PASTE shortcut

       if (keyevent && kbW && !capsonmode && !kbSHIFT && ! kbCTRL) return 'w';
       if (keyevent && kbW && (capsonmode || kbSHIFT) && !kbCTRL) return 'W';
       if (keyevent && kbW && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbX && !capsonmode && !kbSHIFT && ! kbCTRL) return 'x';
       if (keyevent && kbX && (capsonmode || kbSHIFT) && !kbCTRL) return 'X';
       if (keyevent && kbX && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke   /!\ this is CUT shortcut

       if (keyevent && kbY && !capsonmode && !kbSHIFT && ! kbCTRL) return 'y';
       if (keyevent && kbY && (capsonmode || kbSHIFT) && !kbCTRL) return 'Y';
       if (keyevent && kbY && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbZ && !capsonmode && !kbSHIFT && ! kbCTRL) return 'z';
       if (keyevent && kbZ && (capsonmode || kbSHIFT) && !kbCTRL) return 'Z';
       if (keyevent && kbZ && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke


       /*       if (keyevent && kbA && !(capsonmode || kbSHIFT)) return 'a';
              if (keyevent && kbA && (capsonmode || kbSHIFT)) return 'A';

              if (keyevent && kbB && !(capsonmode || kbSHIFT)) return 'b';
              if (keyevent && kbB && (capsonmode || kbSHIFT)) return 'B';

              if (keyevent && kbC && !(capsonmode || kbSHIFT)) return 'c';
              if (keyevent && kbC && (capsonmode || kbSHIFT)) return 'C';

              if (keyevent && kbD && !(capsonmode || kbSHIFT)) return 'd';
              if (keyevent && kbD && (capsonmode || kbSHIFT)) return 'D';

              if (keyevent && kbE && !(capsonmode || kbSHIFT)) return 'e';
              if (keyevent && kbE && (capsonmode || kbSHIFT)) return 'E';

              if (keyevent && kbF && !(capsonmode || kbSHIFT)) return 'f';
              if (keyevent && kbF && (capsonmode || kbSHIFT)) return 'F';

              if (keyevent && kbG && !(capsonmode || kbSHIFT)) return 'g';
              if (keyevent && kbG && (capsonmode || kbSHIFT)) return 'G';

              if (keyevent && kbH && !(capsonmode || kbSHIFT)) return 'h';
              if (keyevent && kbH && (capsonmode || kbSHIFT)) return 'H';

              if (keyevent && kbI && !(capsonmode || kbSHIFT)) return 'i';
              if (keyevent && kbI && (capsonmode || kbSHIFT)) return 'I';

              if (keyevent && kbJ && !(capsonmode || kbSHIFT)) return 'j';
              if (keyevent && kbJ && (capsonmode || kbSHIFT)) return 'J';

              if (keyevent && kbK && !(capsonmode || kbSHIFT)) return 'k';
              if (keyevent && kbK && (capsonmode || kbSHIFT)) return 'K';

              if (keyevent && kbL && !(capsonmode || kbSHIFT)) return 'l';
              if (keyevent && kbL && (capsonmode || kbSHIFT)) return 'L';

              if (keyevent && kbM && !(capsonmode || kbSHIFT)) return 'm';
              if (keyevent && kbM && (capsonmode || kbSHIFT)) return 'M';

              if (keyevent && kbN && !(capsonmode || kbSHIFT)) return 'n';
              if (keyevent && kbN && (capsonmode || kbSHIFT)) return 'N';

              if (keyevent && kbO && !(capsonmode || kbSHIFT)) return 'o';
              if (keyevent && kbO && (capsonmode || kbSHIFT)) return 'O';

              if (keyevent && kbP && !(capsonmode || kbSHIFT)) return 'p';
              if (keyevent && kbP && (capsonmode || kbSHIFT)) return 'P';

              if (keyevent && kbQ && !(capsonmode || kbSHIFT)) return 'q';
              if (keyevent && kbQ && (capsonmode || kbSHIFT)) return 'Q';

              if (keyevent && kbR && !(capsonmode || kbSHIFT)) return 'r';
              if (keyevent && kbR && (capsonmode || kbSHIFT)) return 'R';

              if (keyevent && kbS && !(capsonmode || kbSHIFT)) return 's';
              if (keyevent && kbS && (capsonmode || kbSHIFT)) return 'S';

              if (keyevent && kbT && !(capsonmode || kbSHIFT)) return 't';
              if (keyevent && kbT && (capsonmode || kbSHIFT)) return 'T';

              if (keyevent && kbU && !(capsonmode || kbSHIFT)) return 'u';
              if (keyevent && kbU && (capsonmode || kbSHIFT)) return 'U';

              if (keyevent && kbV && !(capsonmode || kbSHIFT)) return 'v';
              if (keyevent && kbV && (capsonmode || kbSHIFT)) return 'V';

              if (keyevent && kbW && !(capsonmode || kbSHIFT)) return 'w';
              if (keyevent && kbW && (capsonmode || kbSHIFT)) return 'W';

              if (keyevent && kbX && !(capsonmode || kbSHIFT)) return 'x';
              if (keyevent && kbX && (capsonmode || kbSHIFT)) return 'X';

              if (keyevent && kbY && !(capsonmode || kbSHIFT)) return 'y';
              if (keyevent && kbY && (capsonmode || kbSHIFT)) return 'Y';

              if (keyevent && kbZ && !(capsonmode || kbSHIFT)) return 'z';
              if (keyevent && kbZ && (capsonmode || kbSHIFT)) return 'Z';
       */

       //then the number keys

       if (keyevent && kb0 && !capsonmode && !kbSHIFT && ! kbCTRL) return '0';
       if (keyevent && kb0 && (capsonmode || kbSHIFT) && !kbCTRL) return '0';
       if (keyevent && kb0 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke    /!\ this is SCREENSHOT shortcut

       if (keyevent && kb1 && !capsonmode && !kbSHIFT && ! kbCTRL) return '1';
       if (keyevent && kb1 && (capsonmode || kbSHIFT) && !kbCTRL) return '1';
       if (keyevent && kb1 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kb2 && !capsonmode && !kbSHIFT && ! kbCTRL) return '2';
       if (keyevent && kb2 && (capsonmode || kbSHIFT) && !kbCTRL) return '2';
       if (keyevent && kb2 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kb3 && !capsonmode && !kbSHIFT && ! kbCTRL) return '3';
       if (keyevent && kb3 && (capsonmode || kbSHIFT) && !kbCTRL) return '3';
       if (keyevent && kb3 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kb4 && !capsonmode && !kbSHIFT && ! kbCTRL) return '4';
       if (keyevent && kb4 && (capsonmode || kbSHIFT) && !kbCTRL) return '4';
       if (keyevent && kb4 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kb5 && !capsonmode && !kbSHIFT && ! kbCTRL) return '5';
       if (keyevent && kb5 && (capsonmode || kbSHIFT) && !kbCTRL) return '5';
       if (keyevent && kb5 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kb6 && !capsonmode && !kbSHIFT && ! kbCTRL) return '6';
       if (keyevent && kb6 && (capsonmode || kbSHIFT) && !kbCTRL) return '6';
       if (keyevent && kb6 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kb7 && !capsonmode && !kbSHIFT && ! kbCTRL) return '7';
       if (keyevent && kb7 && (capsonmode || kbSHIFT) && !kbCTRL) return '7';
       if (keyevent && kb7 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kb8 && !capsonmode && !kbSHIFT && ! kbCTRL) return '8';
       if (keyevent && kb8 && (capsonmode || kbSHIFT) && !kbCTRL) return '8';
       if (keyevent && kb8 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kb9 && !capsonmode && !kbSHIFT && ! kbCTRL) return '9';
       if (keyevent && kb9 && (capsonmode || kbSHIFT) && !kbCTRL) return '9';
       if (keyevent && kb9 && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke


       //then the symbols keys
       //(note that right now they are mapped as per nio_ascii_get, but this can be changed easily)

       if (keyevent && kbEX && !capsonmode && !kbSHIFT && ! kbCTRL) return '#';
       if (keyevent && kbEX && (capsonmode || kbSHIFT) && !kbCTRL) {}; //nothing for this combination of keystroke
       if (keyevent && kbEX && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbPAROPEN && !capsonmode && !kbSHIFT && ! kbCTRL) return '(';
       if (keyevent && kbPAROPEN && (capsonmode || kbSHIFT) && !kbCTRL) return '[';
       if (keyevent && kbPAROPEN && !(capsonmode || kbSHIFT) && kbCTRL) return '{';

       if (keyevent && kbPARCLOSE && !capsonmode && !kbSHIFT && ! kbCTRL) return ')';
       if (keyevent && kbPARCLOSE && (capsonmode || kbSHIFT) && !kbCTRL) return ']';
       if (keyevent && kbPARCLOSE && !(capsonmode || kbSHIFT) && kbCTRL) return '}';

       if (keyevent && kbEQUAL && !capsonmode && !kbSHIFT && ! kbCTRL) return '=';
       if (keyevent && kbEQUAL && (capsonmode || kbSHIFT) && !kbCTRL) return '|';
       if (keyevent && kbEQUAL && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbPOWER && !capsonmode && !kbSHIFT && ! kbCTRL) return '^';
       if (keyevent && kbPOWER && (capsonmode || kbSHIFT) && !kbCTRL) return '\''; //nothing for this combination of keystroke
       if (keyevent && kbPOWER && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbEE && !capsonmode && !kbSHIFT && ! kbCTRL) return '&';
       if (keyevent && kbEE && (capsonmode || kbSHIFT) && !kbCTRL) return '%';
       if (keyevent && kbEE && !(capsonmode || kbSHIFT) && kbCTRL) return '@';

       if (keyevent && kbCOMMA && !capsonmode && !kbSHIFT && ! kbCTRL) return ',';
       if (keyevent && kbCOMMA && (capsonmode || kbSHIFT) && !kbCTRL) return ';';
       if (keyevent && kbCOMMA && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbDOT && !capsonmode && !kbSHIFT && ! kbCTRL) return '.';
       if (keyevent && kbDOT && (capsonmode || kbSHIFT) && !kbCTRL) return ':';
       if (keyevent && kbDOT && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke !!! BE CAREFULL : SCREENSHOT SHORTCUT

       if (keyevent && kbMINUSPAR && !capsonmode && !kbSHIFT && ! kbCTRL) return '-';
       if (keyevent && kbMINUSPAR && (capsonmode || kbSHIFT) && !kbCTRL) return '_';
       if (keyevent && kbMINUSPAR && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbMULTIPLY && !capsonmode && !kbSHIFT && ! kbCTRL) return '*';
       if (keyevent && kbMULTIPLY && (capsonmode || kbSHIFT) && !kbCTRL) return '\"';
       if (keyevent && kbMULTIPLY && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbDIV && !capsonmode && !kbSHIFT && ! kbCTRL) return '/';
       if (keyevent && kbDIV && (capsonmode || kbSHIFT) && !kbCTRL) return '\\';
       if (keyevent && kbDIV && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbPLUS && !capsonmode && !kbSHIFT && ! kbCTRL) return '+';
       if (keyevent && kbPLUS && (capsonmode || kbSHIFT) && !kbCTRL) return '>';
       if (keyevent && kbPLUS && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbMINUS && !capsonmode && !kbSHIFT && ! kbCTRL) return '-';
       if (keyevent && kbMINUS && (capsonmode || kbSHIFT) && !kbCTRL) return '<';
       if (keyevent && kbMINUS && !(capsonmode || kbSHIFT) && kbCTRL) return '_';

       if (keyevent && kbENTER && !capsonmode && !kbSHIFT && ! kbCTRL) return '\n';
       if (keyevent && kbENTER && (capsonmode || kbSHIFT) && !kbCTRL) return '~';
       if (keyevent && kbENTER && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbQUESTION && !capsonmode && !kbSHIFT && ! kbCTRL) return '?';
       if (keyevent && kbQUESTION && (capsonmode || kbSHIFT) && !kbCTRL) return '!';
       if (keyevent && kbQUESTION && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke

       if (keyevent && kbSPACE && !capsonmode && !kbSHIFT && ! kbCTRL) return ' ';
       if (keyevent && kbSPACE && (capsonmode || kbSHIFT) && !kbCTRL) return '_';
       if (keyevent && kbSPACE && !(capsonmode || kbSHIFT) && kbCTRL) {}; //nothing for this combination of keystroke


       //and finally the special characters
       if (keyevent && kbRET) return '\n';
       if (keyevent && kbDEL) return '\b';
       if (keyevent && kbTAB) return '\t';

       return 0;
}


void KeyboardTask::resetstate( )
{
       // First adress block
       kbRET = false;
       kbENTER = false;
       kbMINUSPAR = false;
       kbSPACE = false;
       kbZ = false;
       kbY = false;
       kb0 = false;
       kbQUESTION = false;
       kbON = false;

       // Second adress block
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

       // Third adress block
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

       // Fourth adress block
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

       // Fifth adress block
       kbF = false;
       kbE = false;
       kbD = false;
       kbC = false;
       kbB = false;
       kbA = false;
       kbEQUAL = false;
       kbMULTIPLY = false;
       kbPOWER = false;

       // Sixth adress block
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

       // Seventh adress block
       kbFLAG = false;
       kbPLUS = false;
       kbDOC = false;
       kb2 = false;
       kbMENU = false;
       kb8 = false;
       kbESC = false;
       kbTAB = false;

       // Eigth adress block
       kbSHIFT = false;
       kbCTRL = false;
       kbCOMMA = false;

       // Keys of the Touchpad
       kbUP = false;
       kbUPRIGHT = false;
       kbRIGHT = false;
       kbRIGHTDOWN = false;
       kbDOWN = false;
       kbDOWNLEFT = false;
       kbLEFT = false;
       kbLEFTUP = false;
}
