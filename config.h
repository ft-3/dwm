/* for volume key controls */
#include <X11/XF86keysym.h>

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx    = 4;        /* border pixel of windows */
static const unsigned int snap        = 10;       /* snap pixel */

static const unsigned int gappx       = 5;        /* gap in pixels between windows */

static const int showbar              = 0;        /* 0 means no bar */
static const int topbar               = 0;        /* 0 means bottom bar */

static const char *fonts[]            = { "terminus:size=8" };
static const char dmenufont[]         = "terminus:size=8";

/* my colors */
/* base16-ocean */
// static const char black[]             = "#2b303b";  // Black
// static const char red[]               = "#bf616a";  // Red
// static const char green[]             = "#a3be8c";  // Green
// static const char yellow[]            = "#ebcb8b";  // Yellow
// static const char blue[]              = "#8fa1b3";  // Blue
// static const char magenta[]           = "#b48ead";  // Magenta
// static const char cyan[]              = "#96b5b4";  // Cyan
// static const char white[]             = "#c0c5ce";  // White

/* base16-tomorrow-night */
static const char black[]             =   "#1d1f21"; // Black
static const char red[]               =   "#cc6666"; // Red
static const char green[]             =   "#b5bd68"; // Green
static const char yellow[]            =   "#f0c674"; // Yellow
static const char blue[]              =   "#81a2be"; // Blue
static const char magenta[]           =   "#b294bb"; // Magenta
static const char cyan[]              =   "#8abeb7"; // Cyan
static const char white[]             =   "#c5c8c6"; // White

static const char *colors[][3]      = {
	/*               fg         bg          border   */
	[SchemeNorm] = { white,     black,      white  },
	[SchemeSel]  = { magenta,    black,     magenta },
};

/* tagging */
static const char *tags[] = { "[]", "[]", "[]", "[]", "[]", "[]" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance    title       tags mask     isfloating   monitor */
	{ "tabbed",         NULL,       NULL,       0 << 2,       0,           -1 }
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", black, "-nf", white, "-sb", magenta, "-sf", black, "-b", NULL };
static const char *termcmd[]  = { "st", NULL };

  /////////////////
 // MY COMMANDS //
/////////////////

/* volume */
static const char *upvol[]   = { "volume","up", NULL };
static const char *downvol[] = { "volume", "down", NULL };
static const char *mutevol[] = { "volume", "mute", NULL };

/* screen lock */
static const char *screenlock[] = { "slock", NULL};

/* brightness */
static const char *upbrightness[] = { "brightness", "up", NULL };
static const char *downbrightness[] = { "brightness", "down", NULL };

/* browser */
static const char *browser[] = { "tabbed", "-c", "vimb", "-e", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_Return, spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_p,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },

    /* my stuff */
    { 0,              XF86XK_AudioRaiseVolume, spawn,          {.v = upvol } },
	{ 0,              XF86XK_AudioLowerVolume, spawn,          {.v = downvol } },
	{ 0,                     XF86XK_AudioMute, spawn,          {.v = mutevol } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = screenlock } },
	{ 0,               XF86XK_MonBrightnessUp, spawn,          {.v = upbrightness } },
	{ 0,             XF86XK_MonBrightnessDown, spawn,          {.v = downbrightness } },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = browser } },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

