/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel] =  { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "term", "media", "office", "chat", "5", "6", "7", "8", "web" };

static const Rule rules[] = {
	/*
	 * $ xprop | grep WM_CLASS
	 * xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       1 << 1,       False,       -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       False,       -1 },
	{ "Skype",    NULL,       NULL,       1 << 7,       True,        -1 },
	{ "MPlayer",  NULL,       NULL,       1 << 1,       False,       -1 },
	{ "vlc",      NULL,       NULL,       1 << 1,       False,       -1 },
	{ "Gpodder",  NULL,       NULL,       1 << 1,       False,       -1 },
	{ "Apvlv",    NULL,       NULL,       1 << 2,       False,       -1 },
	{ "Spotify",  NULL,       NULL,       1 << 1,       False,        0 },
	{ "Mirage",   NULL,       NULL,       1 << 1,       False,       -1 },
	{ "Chromium", NULL,       NULL,       1 << 7,       False,       -1 },
	{ "Google-chrome", NULL,       NULL,       1 << 7,       False,       -1 },
	{ "libreoffice-calc",     NULL,       NULL,         1 << 2,      False,       -1 },
	{ "libreoffice-impress",  NULL,       NULL,         1 << 2,      False,       -1 },
	{ "libreoffice-writer",   NULL,       NULL,         1 << 2,      False,       -1 },
	{ "Pcmanfm",  NULL,       NULL,       1 << 2,       False,       -1 },
	{ "Keepassx", NULL,       NULL,       1 << 5,       False,       -1 },
	{ "Cheese",   NULL,       NULL,       1 << 1,       False,       -1 },
	{ "Evince",   NULL,       NULL,       1 << 2,       False,       -1 },
	{ "Gthumb",   NULL,       NULL,       1 << 1,       False,       -1 },
	{ "Eog",      NULL,       NULL,       1 << 1,       False,       -1 },
	{ "Nautilus", NULL,       NULL,       1 << 2,       True,       -1 },
	{ "Gloobus-preview",      NULL,       NULL,       1 << 2,       True,       -1 },
	{ "discord",  NULL,       NULL,       1 << 5,       False,       -1 },
	{ "Tor Browser",  NULL,       NULL,       1 << 6,       False,       -1 },
	{ "Steam",    NULL,       NULL,       1 << 6,       False,       -1 },
	{ "Messenger for Desktop",    NULL,       NULL,       1 << 9,       True,       -1 },
	{ "whatsapp-desktop",    NULL,       NULL,       1 << 9,       True,       -1 },
	{ "Emoji-keyboard",    NULL,       NULL,       0,       True,       -1 },
	// Disabled because of https://github.com/meetfranz/franz/issues/620
	//{ "Franz",    NULL,       NULL,       0,       True,       -1 },
	{ "Franz",    NULL,       NULL,       1 << 3,       False,       -1 },
	//{ "Rambox",    NULL,       NULL,       1 << 3,       True,       -1 },
	{ "Rambox",    NULL,       NULL,       0,       True,       -1 },
	{ "Signal",    NULL,       NULL,       0,       True,       -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-i", NULL };
static const char *termcmd[]  = { "urxvtc", NULL };

// Keys defined in /usr/include/X11/keysymdef.h.
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_p,      setlayout,      {0} },
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

