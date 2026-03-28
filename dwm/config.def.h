/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx    	= 15;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/

/* alt-tab configuration */
static const unsigned int tabModKey 		= 0x40;	/* if this key is hold the alt-tab functionality stays acitve. This key must be the same as key that is used to active functin altTabStart `*/
static const unsigned int tabCycleKey 		= 0x17;	/* if this key is hit the alt-tab program moves one position forward in clients stack. This key must be the same as key that is used to active functin altTabStart */
static const unsigned int tabPosY 			= 1;	/* tab position on Y axis, 0 = bottom, 1 = center, 2 = top */
static const unsigned int tabPosX 			= 1;	/* tab position on X axis, 0 = left, 1 = center, 2 = right */
static const unsigned int maxWTab 			= 600;	/* tab menu width */
static const unsigned int maxHTab 			= 100;	/* tab menu height */

static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font Mono:pixelsize=20:antialias=true:autohint=true" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font Mono:pixelsize=20:antialias=true:autohint=true";
static const char stfont[] 			= "JetBrainsMono Nerd Font Mono:pixelsize=20:antialias=true:autohint=true";
static const char col_gray1[] = "#2E3440";  /* bg */
static const char col_gray2[] = "#4C566A";  /* border */
static const char col_gray3[] = "#D8DEE9";  /* fg */
static const char col_gray4[] = "#ECEFF4";  /* sel fg */
static const char col_cyan[]  = "#5E81AC";  /* sel bg / border */
static const char *colors[][3] = {
    /*                       fg           bg           border   */
    [SchemeNorm]         = { "#bbbbbb", "#222222", "#444444" },
    [SchemeSel]          = { "#eeeeee", "#005577", "#005577" },
    [SchemeTagActive]    = { "#FFE000", "#222222", "#222222" }, /* Pac-Man yellow */
    [SchemeGhost0]       = { "#FF0000", "#222222", "#222222" }, /* Blinky red */
    [SchemeGhost1]       = { "#FFB8FF", "#222222", "#222222" }, /* Pinky pink */
    [SchemeGhost2]       = { "#00FFFF", "#222222", "#222222" }, /* Inky cyan */
    [SchemeGhost3]       = { "#FFB852", "#222222", "#222222" }, /* Clyde orange */
};

/* tagging */
/* We use placeholder names; drawbar will replace them */
static const char *tags[] = { "1", "2", "3", "4", "5"};

/* Pac-Man symbols */
static const char *tag_active      = "󰮯"; /* nf-md-pac_man*/
static const char *tag_occupied    = "󰊠";  /* Ghost */
static const char *tag_empty[]     = { "󰊠","󰊠","󰊠","󰊠","󰊠" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

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
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/local/bin/st", "-f", stfont, cmd, NULL } }

/* commands */
static const char *screenshotcmd[] = {
  "sh", "-c",
  "mkdir -p ~/Pictures/Screenshots && maim -s | tee ~/Pictures/Screenshots/screenshot-$(date +%Y%m%d-%H%M%S).png | xclip -selection clipboard -t image/png",
  NULL
};
/* power menu command */
static const char *powermenucmd[] = { "sh", "-c",
    "choice=$(printf 'Shutdown\\nReboot\\nSuspend\\nLogout' | dmenu -c -l 4 -fn \"JetBrainsMono Nerd Font Mono:pixelsize=20\" -nb '#2E3440' -nf '#D8DEE9' -sb '#5E81AC' -sf '#ECEFF4') && "
    "case \"$choice\" in "
    "Shutdown) poweroff ;; "
    "Reboot) reboot ;; "
    "Suspend) systemctl suspend ;; "
    "Logout) pkill dwm ;; "
    "esac", NULL };
static const char *voldowncmd[] = { "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "5%-", NULL };
static const char *volupcmd[]   = { "wpctl", "set-volume", "-l", "1.5", "@DEFAULT_AUDIO_SINK@", "5%+", NULL };
static const char *lockcmd[] = { "slock", NULL };
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-c", "-l", "10", NULL };
static const char *clipmenucmd[] = { "/usr/bin/clipmenu", "-c", NULL };
static const char *termcmd[] = { "st", "-f", stfont, NULL };

static const BarButton barbuttons[] = {
    /* label        scheme          command       */
    { " ⏻ ",       SchemeGhost0,   powermenucmd  },  /* rightmost */
    /* add more here, each one appears one step to the left */
};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.001} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.001} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ Mod1Mask,             		XK_F4,     killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
  	{ MODKEY|ControlMask,         	XK_Right,  viewnext,       {0} },
  	{ MODKEY|ControlMask,         	XK_Left,   viewprev,       {0} },
	{ ControlMask|Mod1Mask,         XK_t,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_v,      spawn,          {.v = clipmenucmd } },
	{ Mod1Mask,             		XK_Tab,    altTabStart,	   {0} },
	{ MODKEY, 						XK_l, 	   spawn, 		   {.v = lockcmd } },
	{ 0, 							XF86XK_AudioLowerVolume, spawn, {.v = voldowncmd } },
	{ 0, 							XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd   } },
	{ MODKEY|ShiftMask, 			XK_s,      spawn, 		   {.v = screenshotcmd } },
	{ 0,                			XK_Print,  spawn, 		   {.v = screenshotcmd } },
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
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkPowerBtn, 			0, 				Button1, 		spawn, 			{.v = powermenucmd } },
};

