/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const char font[]            = "-*-terminus-medium-r-normal-*-12-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#262729";
static const char normbgcolor[]     = "#262729";
static const char normfgcolor[]     = "#a6e22e";
static const char selbordercolor[]  = "#070810";
static const char selbgcolor[]      = "#161719";
static const char selfgcolor[]      = "#5496ff";
static const char urgbordercolor[]  = "#ff0066";
static const char urgbgcolor[]      = "#ff0066";
static const char urgfgcolor[]      = "#ffffff";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* settings for patches */
static const unsigned int shade     = 90;
static const unsigned int gappx     = 4;        /* gap pixel between windows */
static const int nmaster            = 2;        /* default number of clients in the master area */

/* tagging */
static const Tag tags[] = {
	/* name    layout   mfact */
	{ "term",  1,       -1   },
	{ "dev",   0,       -1   },
	{ "web",   2,       -1   },
	{ "chat",  0,       0.70 },
	{ "virt",  2,       -1   },
	{ "misc",  0,       -1   },
};

static const Rule rules[] = {
	/* class            instance        title           tags mask   isfloating  monitor  opacity */
	{ "Chromium",       NULL,           NULL,           1 << 2,     False,      -1,      -1 },
	{ "Pidgin",         NULL,           NULL,           1 << 3,     False,      -1,      -1 },
	{ "VirtualBox",     NULL,           NULL,           1 << 4,     False,      -1,      -1 },

	{ "Transmission",   NULL,           NULL,           1 << 5,     True,       -1,      -1 },
	{ "Gimp",           NULL,           NULL,           1 << 5,     True,       -1,      -1 },

	{ "feh",            NULL,           NULL,           0,          True,       -1,      -1 },
	{ "Wine",           NULL,           NULL,           0,          True,       -1,      -1 },
	{ "Nitrogen",       NULL,           NULL,           0,          True,       -1,      -1 },
	{ "MPlayer",        NULL,           NULL,           0,          True,       -1,      -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

#include "nbalanced.c"
static const Layout layouts[] = {
	/* symbol     add gaps   arrange function */
	{ "=2]",      True,      ntile },
	{ "T2T",      True,      nbstack },
	{ "[M]",      True,      monocle },
	{ "><>",      False,     NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
static const char history[]     = "/home/simongmzlj/.dmenu_history";
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define DMENUCONF "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor

#define ALSADEV "Master"
#define ALSARATE "5%"

/* commands */
static const char *termcmd[]    = { "urxvtc", NULL };
static const char *dmenucmd[]   = { "dmenu_run", "-hist", history, DMENUCONF, NULL };
static const char *webcmd[]     = { "chromium", NULL };
static const char *webpcmd[]    = { "chromium", "--incognito", NULL };

static const char *dmenunet[]   = { "sudo", "netcfg-dmenu", DMENUCONF, NULL };
static const char *autonet[]    = { "sudo", "netcfg-wpa_actiond", "wlan0", NULL };

static const char *amixvolu[]   = { "amixer", "-c", "0", "-q", "set", ALSADEV, ALSARATE"+", "unmute", NULL };
static const char *amixvold[]   = { "amixer", "-c", "0", "-q", "set", ALSADEV, ALSARATE"-", "unmute", NULL };
static const char *amixvolm[]   = { "amixer", "-c", "0", "-q", "set", ALSADEV, "toggle", NULL };

static const char *amixmpdvolu[]   = { "amixer", "-c", "0", "-q", "set", "MPD", ALSARATE"+", "unmute", NULL };
static const char *amixmpdvold[]   = { "amixer", "-c", "0", "-q", "set", "MPD", ALSARATE"-", "unmute", NULL };
static const char *amixmpdvolm[]   = { "amixer", "-c", "0", "-q", "set", "MPD", "toggle", NULL };

static const char *audioplay[]  = { "mpc", "toggle", NULL };
static const char *audiostop[]  = { "mpc", "stop", NULL };
static const char *audiopause[] = { "mpc", "pause", NULL };
static const char *audionext[]  = { "mpc", "next", NULL };
static const char *audioprev[]  = { "mpc", "prev", NULL };

#include "push.c"
#include "opacity.c"
#include "cycle.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0] } },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1] } },
	{ MODKEY,                       XK_a,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_z,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_x,      setnmaster,     {.i = 2 } },
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
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

    /* my keybindings */
	{ MODKEY,                       XK_w,      spawn,          {.v = dmenunet } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = autonet } },
	{ MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
	{ MODKEY|ShiftMask|ControlMask, XK_j,      setopy,         {.i = -10} },
	{ MODKEY|ShiftMask|ControlMask, XK_k,      setopy,         {.i = +10} },
	{ MODKEY,                       XK_e,      spawn,          {.v = webcmd } },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = webpcmd } },
	{ MODKEY|ControlMask,           XK_Left,   cycle,          {.i = -1} },
	{ MODKEY|ControlMask,           XK_Right,  cycle,          {.i = +1} },
	{ MODKEY|ShiftMask|ControlMask, XK_Left,   tagcycle,       {.i = -1} },
	{ MODKEY|ShiftMask|ControlMask, XK_Right,  tagcycle,       {.i = +1} },

	{ 0,            XF86XK_AudioLowerVolume,   spawn,          {.v = amixvold } },
	{ 0,            XF86XK_AudioRaiseVolume,   spawn,          {.v = amixvolu } },
	{ 0,            XF86XK_AudioMute,          spawn,          {.v = amixvolm } },
	{ MODKEY,       XF86XK_AudioLowerVolume,   spawn,          {.v = amixmpdvold } },
	{ MODKEY,       XF86XK_AudioRaiseVolume,   spawn,          {.v = amixmpdvolu } },
	{ MODKEY,       XF86XK_AudioMute,          spawn,          {.v = amixmpdvolm } },
	{ 0,            XF86XK_AudioPlay,          spawn,          {.v = audioplay } },
	{ 0,            XF86XK_AudioPause,         spawn,          {.v = audiopause } },
	{ 0,            XF86XK_AudioStop,          spawn,          {.v = audiostop } },
	{ 0,            XF86XK_AudioNext,          spawn,          {.v = audionext } },
	{ 0,            XF86XK_AudioPrev,          spawn,          {.v = audioprev } },
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

