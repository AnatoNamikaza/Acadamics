// winbgim.h version 3.51 - Nov 7, 2004
// modified by Adrian Sandor <aditsu@yahoo.com> based on
// http://www.cs.colorado.edu/~main/bgi/winbgim.h (version 3.4)
// only tested on mingw

// note: there is a version 3.41 at
// http://www.sfusd.edu/schwww/sch697/depts/math/simon/winbgim.h

// documentation: http://www.cs.colorado.edu/~main/bgi/README.html

// Modification log by Michael Main:
// --Version 2.1: Oct 17, 1998
//   Some mouse additions to Konstantin's original code
// --Version 2.2: November 1, 1998
//   Modified getch so that it can get the arrows and other keypad keys.
// --Version 2.3: November 17, 1998
//   Fixed a bug in getpixel.
// --Version 2.4: November 25, 1998
//   Added functions getactivepage() and getvisualpage() to get the current
//   page number of the active and visual pages. In this implementation, the
//   MAX_PAGES is set to 16, but I have used only pages 0 and 1 myself.
// --Version 3.1: June 17, 1999
//   Mostly implemented by Mark Richardson:
//   Implements getimage and putimage.
//   Adds new support for rgb colors.
// --Version 3.2: June 21, 1999
//   Made modifications so that everything works with the mingw32
//   G++ compiler for Windows. Details for installing and using this
//   free compiler are in www.cs.colorado.edu/~main/mingw32/README.html
// --Version 3.3: Oct 4, 1999
//   Added ismouseclick and getmouseclick
// --Version 3.4: Dec 21, 1999
//   Added clearmouseclick.
//   Fixed bug causing getmouseclick to fail when x and y are same variable.
//   Fixed bug in setcolor that sometimes caused the fill color to change
//   to the drawing color.

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <stddef.h>
#include <conio.h>
#include <windows.h>

/** Some different definitions for the Mingw32 g++ compiler and
*   the Borland 5.0 compiler. Added by Michael Main, June 21, 1999.
*   Michael Main -- 10/17/98 */

#if defined(_WINDOWS_H) || defined(_GNU_H_WINDOWS_H)
/* MINGW32 G++ Compiler:
*  Define CLR_INVALID from Borlands /win32/wingdi.h.
*  Get the memset prototype from string.h.
*  3.5: deleted some unnecessary things
*/
#if !defined(CLR_INVALID)
#define CLR_INVALID 0xFFFFFFFF
#endif
#include <string.h>
#endif

//3.5: COLORS are defined in conio.h (even for mingw)
#define colors COLORS

//define random for the bgidemo function.
#ifndef random
#define random(range) (rand() % (range))
#endif

enum write_modes {
    COPY_PUT, XOR_PUT, OR_PUT, AND_PUT, NOT_PUT
};

enum line_styles {
    SOLID_LINE, DOTTED_LINE, CENTER_LINE, DASHED_LINE, USERBIT_LINE
};

enum fill_styles {
    EMPTY_FILL, SOLID_FILL, LINE_FILL, LTSLASH_FILL, SLASH_FILL, BKSLASH_FILL,
    LTBKSLASH_FILL, HATCH_FILL, XHATCH_FILL, INTERLEAVE_FILL, WIDE_DOT_FILL,
    CLOSE_DOT_FILL, USER_FILL
};

enum text_directions {
    HORIZ_DIR, VERT_DIR
};

enum font_types {
    DEFAULT_FONT, TRIPLEX_FONT, SMALL_FONT, SANSSERIF_FONT, GOTHIC_FONT
};

#define LEFT_TEXT             0
#define CENTER_TEXT           1
#define RIGHT_TEXT            2
#define BOTTOM_TEXT           0
#define TOP_TEXT              2
#define NORM_WIDTH            1
#define THICK_WIDTH           3
#define DOTTEDLINE_LENGTH     2
#define CENTRELINE_LENGTH     4
#define USER_CHAR_SIZE        0
#define MAXCOLORS             15
#define CLIP_ON               1
#define CLIP_OFF              0
#define TOP_ON                1
#define TOP_OFF               0

// Definitions for the key pad extended keys are added here. I have also
// modified getch() so that when one of these keys are pressed, getch will
// return a zero followed by one of these values. This is the same way
// that it works in conio for dos applications.
// M. Main -- Nov 3, 1998
#define KEY_HOME       71
#define KEY_UP         72
#define KEY_PGUP       73
#define KEY_LEFT       75
#define KEY_CENTER     76
#define KEY_RIGHT      77
#define KEY_END        79
#define KEY_DOWN       80
#define KEY_PGDN       81
#define KEY_INSERT     82
#define KEY_DELETE     83
#define KEY_F1			  59
#define KEY_F2         60
#define KEY_F3         61
#define KEY_F4			  62
#define KEY_F5			  63
#define KEY_F6			  64
#define KEY_F7			  65
#define KEY_F8			  66
#define KEY_F9			  67

enum graphics_errors {
   grOk = 0,
   grNoInitGraph = -1,
   grNotDetected = -2,
   grFileNotFound = -3,
   grInvalidDriver   = -4,
   grNoLoadMem = -5,
   grNoScanMem = -6,
   grNoFloodMem = -7,
   grFontNotFound = -8,
   grNoFontMem = -9,
   grInvalidMode =   -10,
   grError = -11,
   grIOerror = -12,
   grInvalidFont = -13,
   grInvalidFontNum = -14,
   grInvalidDeviceNum = -15,
   grInvalidVersion = -18
};

/* Graphics drivers constants, includes X11 which is particular to XBGI. */
#define DETECT                0
#define CGA                1
#define MCGA                  2
#define EGA                3
#define EGA64                 4
#define EGAMONO                  5
#define IBM8514                  6
#define HERCMONO              7
#define ATT400                8
#define VGA                9
#define PC3270                10

/* Graphics modes constants. */
#define CGAC0                 0
#define CGAC1                 1
#define CGAC2                 2
#define CGAC3                 3
#define CGAHI                 4
#define MCGAC0                0
#define MCGAC1                1
#define MCGAC2                2
#define MCGAC3                3
#define MCGAMED                  4
#define MCGAHI                5
#define EGALO                 0
#define EGAHI                 1
#define EGA64LO                  0
#define EGA64HI                  1
#define EGAMONOHI             3
#define HERCMONOHI               0
#define ATT400C0              0
#define ATT400C1              1
#define ATT400C2              2
#define ATT400C3              3
#define ATT400MED             4
#define ATT400HI              5
#define VGALO                 0
#define VGAMED                1
#define VGAHI                 2
#define VGAMAX                                          3
#define PC3270HI              0
#define IBM8514LO             0
#define IBM8514HI             1

typedef struct arccoordstype {
    int x;
    int y;
    int xstart;
    int ystart;
    int xend;
    int yend;
} arccoordstype;

typedef char fillpatterntype[8];
typedef struct fillsettingstype {
    int pattern;
    int color;
} fillsettingstype;

typedef struct linesettingstype {
    int linestyle;
    unsigned int upattern;
    int thickness;
} linesettingstype;

typedef struct palettetype {
    unsigned char size;
    signed char colors[16];
} palettetype;

typedef struct textsettingstype {
    int font;
    int direction;
    int charsize;
    int horiz;
    int vert;
} textsettingstype;

typedef struct viewporttype {
    int left;
    int top;
    int right;
    int bottom;
    int clip;
} viewporttype;
 // This struct was moved here to allow access to the struct (Mark Richardson 11/29/98)
struct BGIimage {
	short width;		// 2 bytes
   short height;		// 2 bytes  Note:This means bits is also aligned to 32bit(DWORD) boundry
	char  bits[1];
};

#ifndef NOT_USE_PROTOTYPES
#define PROTO(ARGS) ARGS
#else
#define PROTO(ARGS) ()
#endif
#if defined(__cplusplus)
extern "C" {
#endif
//
// Setting this variable to 0 increase speed of drawing but
// correct redraw is not possible. By default this variable is initialized by 1
//

extern int bgiemu_handle_redraw;
//
// Default mode choosed by WinBGI if DETECT value is specified for
// device parameter of initgraoh(). Default value is VGAMAX which
// cause creation of maximized window (resolution depends on display mode)
//

extern int bgiemu_default_mode;
void _graphfreemem PROTO((void *ptr, unsigned int size));
void* _graphgetmem PROTO((unsigned int size));
void arc PROTO((int, int, int, int, int));
void bar PROTO((int, int, int, int));
void bar3d PROTO((int, int, int, int, int, int));
void circle PROTO((int, int, int));
void cleardevice PROTO((void));
void clearviewport PROTO((void));
void closegraph PROTO((void));
void detectgraph PROTO((int *, int *));
void drawpoly PROTO((int, int *));
void ellipse PROTO((int, int, int, int, int, int));
void fillellipse PROTO((int, int, int, int));
void fillpoly PROTO((int, int *));
void floodfill PROTO((int, int, int));
void getarccoords PROTO((arccoordstype *));
void getaspectratio PROTO((int *, int *));
int getbkcolor PROTO((void));
int getcolor PROTO((void));
palettetype* getdefaultpalette PROTO((void));
char* getdrivername PROTO((void));
void getfillpattern PROTO((fillpatterntype)); //3.51: fixed argument type
void getfillsettings PROTO((fillsettingstype *));
int getgraphmode PROTO((void));
void getimage PROTO((int, int, int, int, void *));
void getlinesettings PROTO((linesettingstype *));
int getmaxcolor PROTO((void));
int getmaxmode PROTO((void));
int getmaxx PROTO((void));
int getmaxy PROTO((void));
char* getmodename PROTO((int));
void getmoderange PROTO((int, int *, int *));
void getpalette PROTO((palettetype *));
int getpalettesize PROTO((void));
unsigned int getpixel PROTO((int, int));
void gettextsettings PROTO((textsettingstype *));
void getviewsettings PROTO((viewporttype *));
int getx PROTO((void));
int gety PROTO((void));
void graphdefaults PROTO((void));
char* grapherrormsg PROTO((int));
int graphresult PROTO((void));
unsigned int imagesize PROTO((int, int, int, int));
void initgraph PROTO((int *, int *, char const *));
int installuserdriver PROTO((char const *, int *));
int installuserfont PROTO((char const *));
void line PROTO((int, int, int, int));
void linerel PROTO((int, int));
void lineto PROTO((int, int));
void moverel PROTO((int, int));
void moveto PROTO((int, int));
void outtext PROTO((char const *));
void outtextxy PROTO((int, int, char const *));
void pieslice PROTO((int, int, int, int, int));
void putimage PROTO((int, int, void *, int));
void putpixel PROTO((int, int, int));
void rectangle PROTO((int, int, int, int));
int registerbgidriver PROTO((void *));
int registerbgifont PROTO((void *));
void restorecrtmode PROTO((void));
void sector PROTO((int, int, int, int, int, int));
void setactivepage PROTO((int));
void setallpalette PROTO((palettetype *));
void setaspectratio PROTO((int, int));
void setbkcolor PROTO((int));
void setcolor PROTO((int));
void setfillpattern PROTO((char const *, int));
void setfillstyle PROTO((int, int));
unsigned int setgraphbufsize PROTO((unsigned int));
void setgraphmode PROTO((int));
void setlinestyle PROTO((int, unsigned int, int));
void setpalette PROTO((int, int));
void setrgbpalette PROTO((int, int, int, int));
void settextjustify PROTO((int, int));
void settextstyle PROTO((int, int, int));
void setusercharsize PROTO((int, int, int, int));
void setviewport PROTO((int, int, int, int, int));
void setvisualpage PROTO((int));
void setwritemode PROTO((int));
int textheight PROTO((char const *));
int textwidth PROTO((char const *));
int getch PROTO((void));
int kbhit PROTO((void));
void delay PROTO((unsigned msec));
void restorecrtmode PROTO((void));

/* Prototypes for mouse handling functions. The mousex( ) and mousey( )
*  functions return the most recent x and y coordinates detected from the
*  mouse. For the other functions, the kind parameter should be one of these:
*   WM_MOUSEMOVE       -- mouse movement
*   WM_LBUTTONDBLCLK   -- left mouse button double-click
*   WM_LBUTTONDOWN     -- left mouse button pushed down
*   WM_LBUTTONUP       -- left mouse button released up
*   WM_MBUTTONDBLCLK   -- middle mouse button double-click (might not work!)
*   WM_MBUTTONDOWN     -- middle mouse button pushed down (might not work!)
*   WM_MBUTTONUP       -- middle mouse button released up (might not work!)
*   WM_RBUTTONDBLCLK   -- right mouse button double-click
*   WM_RBUTTONDOWN     -- right mouse button pushed down
*   WM_RBUTTONUP       -- right mouse button released up
* The parameter h must be a void function with two integer parameters.
* This function will be called whenever the corresponding event occurs.
* The two integer parameters will be the x- and y-coordinates where the
* event happened.
* 
* NOTE: The middle button events aren't being caught on my Windows 95 system.
* I don't know why.
* Added by Michael Main -- 11/3/98 and 10/4/99 and 12/21/99.
*/
int mousex PROTO(( ));
int mousey PROTO(( ));
void registermousehandler PROTO((UINT kind, void h(int, int)));
bool ismouseclick PROTO((UINT kind));
void getmouseclick PROTO((UINT kind, int& x, int& y));
void clearmouseclick PROTO((UINT kind));
    
/* Prototypes for other new functions, not in the original BGI graphics.
*  There is also a new initwindow function that can be called instead of
*  initgraph. The arguments are an explicit width and height.
*  As of 11/3, the width is now the first parameter.
*  The getactivepage() and getvisualpage() functions get the number of the
*  current active or visual page.
*/
void initwindow PROTO((int, int));
int getactivepage PROTO(( ));
int getvisualpage PROTO(( ));

/* Colors can be original bgi colors (ints in the range 0...MAXCOLORS) or
*  RGB colors constructed from red, green and blue components between
*  0 and 255.
*    IS_BGI_COLOR(v): true if v is one of the original BGI colors
*    IS_RGB_COLOR(v): true if v is one of the new RGB colors
*    RED_VALUE(v) is the red value of an RGB color v
*    GREEN_VALUE(v) is the red value of an RGB color v
*    BLUE_VALUE(v) is the red value of an RGB color v
*    COLOR(r,g,b): is the rgb color formed from a red, green and blue
*                  value (all in the range 0...255).
*/

#define IS_BGI_COLOR(c) (((c) >= 0) && ((c) <= MAXCOLORS))
#define IS_RGB_COLOR(c) ((c) & 0x04000000)
#define RED_VALUE(v)   ((v) & 0xFF)
#define GREEN_VALUE(v) (((v) >> 8) & 0xFF)
#define BLUE_VALUE(v)  (((v) >> 16)& 0xFF)
#define COLOR(r,g,b)   (0x04000000 | RGB(r,g,b))

void setwindowtitle(const char*title); //3.51: new function

#if defined(__cplusplus)
};
#endif

#endif
