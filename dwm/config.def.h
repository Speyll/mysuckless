/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 10;       /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "cherry:size=10", "Siji:size=10" };
static const char dmenufont[]       = "cherry:size=10";
static const char col_gray1[]       = "#2E3440";
static const char col_gray2[]       = "#2E3440";
static const char col_gray3[]       = "#E5E9F0";
static const char col_gray4[]       = "#2E3440";
static const char col_cyan[]        = "#88C0D0";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray3 },
	[SchemeSel]  = { col_cyan, col_gray4,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "Br", "Te", "Fi", "En", "Dr", "Co", "Ga"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Pcmanfm",  NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Firefox",  NULL,       NULL,       1,            0,           -1 },
	{ "mpv",      NULL,       NULL,       1 << 3,       0,           -1 },
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
static const char *dmenucmd[] = { "dmenu_run", "-p", "owo what's this?", NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	
	/* Toggle dmenu // status bar */
		{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
		{ MODKEY|ShiftMask,             XK_s,      togglebar,      {0} },

	/* Move to master // Open terminal */
		{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
		{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },

	/* Focus window list */
		{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
		{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
		{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
		{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },

	/* Tile mode */
		{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
		{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
		{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
		{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
		{ MODKEY,                       XK_Left,   setmfact,       {.f = -0.05} },
		{ MODKEY,                       XK_Right,  setmfact,       {.f = +0.05} },

	/* View mode */
		{ MODKEY,                       XK_Tab,    view,           {0} },

	/* Kill windows / dmenu */
		{ MODKEY|ShiftMask,             XK_a,      killclient,     {0} },
		{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

	/* Layout style */
		{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
		{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
		{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
		{ MODKEY,                       XK_space,  setlayout,      {0} },
		{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

	/* Tags keybinds */
		{ MODKEY,                       XK_ccedilla,      view,    {.ui = ~0 } },
		{ MODKEY|ShiftMask,             XK_ccedilla,      tag,     {.ui = ~0 } },
		{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
		{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
		{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
		{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
		TAGKEYS(                        XK_ampersand,              0)
		TAGKEYS(                        XK_eacute,                 1)
		TAGKEYS(                        XK_quotedbl,               2)
		TAGKEYS(                        XK_apostrophe,             3)
		TAGKEYS(                        XK_parenleft,              4)
		TAGKEYS(                        XK_minus,                  5)
		TAGKEYS(                        XK_egrave,                 6)
		TAGKEYS(                        XK_underscore,             7)
		TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

