/*************************************\
 * This is the main include file for *
 *   the GUI Toolkit for TI nSpire   *
 *************************************
 *   Development by Sylvain PILLOT   *
 *************************************
 * |===============================| *
 * | Version 0.5 beta - 2021/03/16 | *
 * |===============================| *
\*************************************/

#define DEBUG_MODE_GUI_TOOLKIT


// These two #include files to be used for Touchpad (Mouse/Cursor) handling and Keyboard handling respectively

#include "CursorTask.h"
#include "KeyboardTask.h"


// These two #include files are used to manage the Color and Font Management Engines respectively

#include "ColorEngine.h"
#include "FontEngine.h"
#include "ThemeEngine.h"


// These #include files gives the definition of the different Widgets classes and associated methods

#include "WidgetApplication.h"          // The definition of the main class of the GUI Toolkit - It serves as a backbone of the Toolkit

#include "Widget.h"                     // This is the main Widget method (not a Widget by itself) from that all Widgets are inherited

#include "FrameWidget.h"
#include "ContainerHWidget.h"
#include "ContainerVWidget.h"
#include "SpacerWidget.h"

#include "DesktopWidget.h"

#include "WindowWidget.h"
#include "DialogBoxWidget.h"
#include "FileDialogBoxWidget.h"

#include "ButtonWidget.h"
#include "MiniButtonWidget.h"
#include "RadioControlWidget.h"
#include "CommuterWidget.h"
#include "CheckBoxWidget.h"

#include "SliderWidget.h"

#include "LabelWidget.h"
#include "ProgressBarWidget.h"

#include "ListBoxWidget.h"
#include "DropBoxWidget.h"

#include "MenuBarWidget.h"
#include "MenuItemWidget.h"
#include "MenuPaneWidget.h"

#include "IconBarWidget.h"
#include "IconItemWidget.h"

#include "InputWidget.h"
#include "MultiLineTextBoxWidget.h"

