/*
	quakedef.h
	primary header for client

	$Header: /home/ozzie/Download/0000/uhexen2/hexen2/quakedef.h,v 1.86 2006-07-04 16:25:23 sezero Exp $
*/


#ifdef _MSC_VER
#pragma warning(disable:4244)
#endif

#define __STRINGIFY(x) #x
#define STRINGIFY(x) __STRINGIFY(x)

#include "arch_def.h"

#define	HOT_VERSION_MAJ		1
#define	HOT_VERSION_MID		4
#define	HOT_VERSION_MIN		1
#define	HOT_VERSION_REL_DATE	"2006-07-04"
#define	HOT_VERSION_BETA	1
#define	HOT_VERSION_BETA_STR	"pre8"
#define	HOT_VERSION_STR		STRINGIFY(HOT_VERSION_MAJ) "." STRINGIFY(HOT_VERSION_MID) "." STRINGIFY(HOT_VERSION_MIN)
#define	GLQUAKE_VERSION		1.00
#define	ENGINE_VERSION		1.15
#define	ENGINE_NAME		"Hexen2"

#ifndef	DEMOBUILD
#ifdef __MACOSX__
#define	AOT_USERDIR		"Library/Application Support/Hexen2"
#else
#define	AOT_USERDIR		".hexen2"
#endif
#else
#ifdef __MACOSX__
#define	AOT_USERDIR		"Library/Application Support/Hexen2 Demo"
#else
#define	AOT_USERDIR		".hexen2demo"
#endif
#endif

#define	MAX_QPATH	64	// max length of a quake game pathname
#define	MAX_OSPATH	256	// max length of a filesystem pathname

#define	QUAKE_GAME		// as opposed to utilities
//define	PARANOID	// speed sapping error checking

// COMPILE TIME OPTION: Whether we want the mission pack support to
// be activated directly.
// Default is no: player must use the -portals command line argument
// to activate it.  If you want direct activation, change the below
// undef to a define : in that case, player must use the -noportals
// command line argument to disable mission pack support.
#undef	H2MP

#include <sys/types.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

// !!! if this is changed, it must be changed in d_ifacea.h too !!!
#define CACHE_SIZE	32	// used to align key data structures

#define UNUSED(x)	(x = x)	// for pesky compiler / lint warnings

#define	MINIMUM_MEMORY	0x550000
#define	MINIMUM_MEMORY_LEVELPAK	(MINIMUM_MEMORY + 0x100000)

#define MAX_NUM_ARGVS	50

// up / down
#define	PITCH		0

// left / right
#define	YAW		1

// fall over
#define	ROLL		2


//
// Timing macros
//
#define HX_FRAME_TIME	0.05
#define HX_FPS		20


//#ifdef DEMOBUILD
//#define	MAX_SCOREBOARD	8
//#endif
#define	MAX_SCOREBOARD	16
#define	MAX_SCOREBOARDNAME	32

#define	SOUND_CHANNELS	8


#define	ON_EPSILON	0.1		// point on plane side epsilon

//#define	MAX_MSGLEN	8000		// max length of a reliable message
//#define	MAX_MSGLEN	16000		// max length of a reliable message
#define	MAX_MSGLEN	20000		// for mission pack tibet2

//#define	MAX_DATAGRAM	2048		// max length of unreliable message  TEMP: This only for E3
#define	MAX_DATAGRAM	1024		// max length of unreliable message


//
// per-level limits
//
#define	MAX_EDICTS	600		// FIXME: ouch! ouch! ouch!
#define	MAX_LIGHTSTYLES	64
#define	MAX_MODELS	512		// Sent over the net as a word
#define	MAX_SOUNDS	512		// Sent over the net as a byte


#define	SAVEGAME_COMMENT_LENGTH	39

#define	MAX_STYLESTRING		64

//
// stats are integers communicated to the client by the server
//
#define	MAX_CL_STATS		32
//#define	STAT_HEALTH		0
#define	STAT_FRAGS		1
#define	STAT_WEAPON		2
//#define	STAT_AMMO		3
#define	STAT_ARMOR		4
#define	STAT_WEAPONFRAME	5
//#define	STAT_SHELLS		6
//#define	STAT_NAILS		7
//#define	STAT_ROCKETS		8
//#define	STAT_CELLS		9
//#define	STAT_ACTIVEWEAPON	10
#define	STAT_TOTALSECRETS	11
#define	STAT_TOTALMONSTERS	12
#define	STAT_SECRETS		13	// bumped on client side by svc_foundsecret
#define	STAT_MONSTERS		14	// bumped by svc_killedmonster
//#define	STAT_BLUEMANA		15
//#define	STAT_GREENMANA		16
//#define	STAT_EXPERIENCE		17

#define	MAX_INVENTORY		15	// Max inventory array size

#define	MAX_SAVEGAMES		12	// max number of savegames

//
// stock defines
//
#define	IT_SHOTGUN		1
#define	IT_SUPER_SHOTGUN	2
#define	IT_NAILGUN		4
#define	IT_SUPER_NAILGUN	8
#define	IT_GRENADE_LAUNCHER	16
#define	IT_ROCKET_LAUNCHER	32
#define	IT_LIGHTNING		64
#define	IT_SUPER_LIGHTNING	128
#define	IT_SHELLS		256
#define	IT_NAILS		512
#define	IT_ROCKETS		1024
#define	IT_CELLS		2048
#define	IT_AXE			4096
#define	IT_ARMOR1		8192
#define	IT_ARMOR2		16384
#define	IT_ARMOR3		32768
#define	IT_SUPERHEALTH		65536
#define	IT_KEY1			131072
#define	IT_KEY2			262144
#define	IT_INVISIBILITY		524288
#define	IT_INVULNERABILITY	1048576
#define	IT_SUIT			2097152
#define	IT_QUAD			4194304
#define	IT_SIGIL1		(1 << 28)
#define	IT_SIGIL2		(1 << 29)
#define	IT_SIGIL3		(1 << 30)
#define	IT_SIGIL4		(1 << 31)

#define	ART_HASTE			1
#define	ART_INVINCIBILITY		2
#define	ART_TOMEOFPOWER			4
#define	ART_INVISIBILITY		8
#define	ARTFLAG_FROZEN			128
#define	ARTFLAG_STONED			256
#define	ARTFLAG_DIVINE_INTERVENTION	512

//
// edict->drawflags
//
#define MLS_MASKIN			7	// MLS: Model Light Style
#define MLS_MASKOUT			248
#define MLS_NONE			0
#define MLS_FULLBRIGHT			1
#define MLS_POWERMODE			2
#define MLS_TORCH			3
#define MLS_TOTALDARK			4
#define MLS_ABSLIGHT			7
#define SCALE_TYPE_MASKIN		24
#define SCALE_TYPE_MASKOUT		231
#define SCALE_TYPE_UNIFORM		0	// Scale X, Y, and Z
#define SCALE_TYPE_XYONLY		8	// Scale X and Y
#define SCALE_TYPE_ZONLY		16	// Scale Z
#define SCALE_ORIGIN_MASKIN		96
#define SCALE_ORIGIN_MASKOUT		159
#define SCALE_ORIGIN_CENTER		0	// Scaling origin at object center
#define SCALE_ORIGIN_BOTTOM		32	// Scaling origin at object bottom
#define SCALE_ORIGIN_TOP		64	// Scaling origin at object top
#define DRF_TRANSLUCENT			128
#define DRF_ANIMATEONCE			256


//===========================================

//
// game data flags
//
#define	GAME_DEMO		1
#define	GAME_OEM		2
#define	GAME_MODIFIED		4
#define	GAME_REGISTERED		8
#define	GAME_REGISTERED0	16
#define	GAME_REGISTERED1	32
#define	GAME_PORTALS		64
#define	GAME_HEXENWORLD		128

//
// Player Classes
//
#define MAX_PLAYER_CLASS	5
#define	PORTALS_EXTRA_CLASSES	1
#define ABILITIES_STR_INDEX	400

#define CLASS_PALADIN		1
#define CLASS_CLERIC 		2
#define CLASS_NECROMANCER	3
#define CLASS_THEIF   		4
#define CLASS_DEMON		5

//#define BASE_ENT_ON		1
//#define BASE_ENT_SENT	2

//=============================================================================

#include "common.h"
#include "bspfile.h"
#include "sys.h"
#include "zone.h"
#include "mathlib.h"
#include "cvar.h"

#include "protocol.h"
#include "net.h"

#include "cmd.h"
#include "crc.h"

//=============================================================================

typedef struct
{
	vec3_t	origin;
	vec3_t	angles;
	short	modelindex;
	byte	frame;
	byte	colormap;
	byte	skin;
	byte	effects;
	byte	scale;
	byte	drawflags;
	byte	abslight;
	byte	ClearCount[32];
} entity_state_t;

typedef struct
{
	byte	flags;
	short	index;

	vec3_t	origin;
	vec3_t	angles;
	short	modelindex;
	byte	frame;
	byte	colormap;
	byte	skin;
	byte	effects;
	byte	scale;
	byte	drawflags;
	byte	abslight;
} entity_state2_t;

typedef struct
{
	byte	flags;

	vec3_t	origin;
	vec3_t	angles;
	short	modelindex;
	byte	frame;
	byte	colormap;
	byte	skin;
	byte	effects;
	byte	scale;
	byte	drawflags;
	byte	abslight;
} entity_state3_t;

#define MAX_CLIENT_STATES	150
#define MAX_FRAMES		5
#define MAX_CLIENTS		8
#define CLEAR_LIMIT		2

#define ENT_STATE_ON		1
#define ENT_CLEARED		2

typedef struct
{
	entity_state2_t	states[MAX_CLIENT_STATES];
//	unsigned long	frame;
//	unsigned long	flags;
	int		count;
} client_frames_t;

typedef struct
{
	entity_state2_t	states[MAX_CLIENT_STATES*2];
	int		count;
} client_frames2_t;

typedef struct
{
	client_frames_t	frames[MAX_FRAMES+2]; // 0 = base, 1-max = proposed, max+1 = too late
} client_state2_t;

//=============================================================================

#ifndef SERVERONLY
#include "console.h"
#include "vid.h"
#include "wad.h"
#include "draw.h"
#include "render.h"
#include "view.h"
#include "screen.h"
#include "sbar.h"
#include "sound.h"
#include "cdaudio.h"
#include "mididef.h"
#endif

#include "progs.h"
#include "strings.h"
#include "cl_effect.h"
#ifdef SERVERONLY
#include "h2ded.h"
#else
#include "client.h"
#endif
#include "server.h"

#if defined(SERVERONLY)
#include "server/model.h"
#elif defined(GLQUAKE)
// gl_model.h is included from within glquake.h
#include "glquake.h"
#else
#include "model.h"
#include "d_iface.h"
#endif
#include "world.h"

#ifndef SERVERONLY
#include "input.h"
#include "keys.h"
#include "menu.h"
#endif

//=============================================================================

// the host system specifies the base of the directory tree, the
// command line parms passed to the program, and the amount of memory
// available for the program to use

typedef struct
{
	char	*basedir;
	char	*userdir;		// userspace directory on UNIX platforms
	int	argc;
	char	**argv;
	void	*membase;
	int	memsize;
} quakeparms_t;


//=============================================================================

//
// host
//
extern	quakeparms_t	host_parms;

extern	cvar_t		sys_ticrate;
extern	cvar_t		sys_nostdout;
extern	cvar_t		developer;

extern	qboolean	host_initialized;	// true if into command execution
extern	double		host_frametime;
extern	byte		*host_basepal;
extern	byte		*host_colormap;
extern	int		host_framecount;	// incremented every frame, never reset
extern	double		realtime;		// not bounded in any way, changed at
						// start of every frame, never reset

void Host_ClearMemory (void);
void Host_InitCommands (void);
void Host_Init (quakeparms_t *parms);
void Host_Shutdown(void);
void Host_Error (char *error, ...);
void Host_EndGame (char *message, ...);
void Host_Frame (float time);
void Host_Quit_f (void);
void Host_ClientCommands (char *fmt, ...);
void Host_ShutdownServer (qboolean crash);
void Host_RemoveGIPFiles (char *path);
qboolean Host_CopyFiles(char *source, char *pat, char *dest);
qboolean SaveGamestate (qboolean ClientsOnly);


extern	qboolean	isDedicated;

extern	qboolean	msg_suppress_1;	// suppresses resolution and cache size console output
					//  a fullscreen DIB focus gain/loss
extern	int		current_skill;	// skill level for currently loaded level (in case
					//  the user changes the cvar while the level is
					//  running, this reflects the level actually in use)

extern	qboolean	noclip_anglehack;
extern	int		sv_kingofhill;
extern	qboolean	intro_playing;	// whether the mission pack intro is playing
extern	qboolean	skip_start;	// for the mission pack intro
extern	int		num_intro_msg;	// for the mission pack intro

//
// chase
//
extern	cvar_t		chase_active;

void Chase_Init (void);
void Chase_Reset (void);
void Chase_Update (void);


/*
 * $Log: not supported by cvs2svn $
 * Revision 1.85  2006/07/03 14:05:36  sezero
 * re-visited the GL data types, made them to be of GL types and solved
 * the signedness issues. completely removed the scrap allocation option.
 * thanks to Levent Yavas for his help.
 *
 * Revision 1.84  2006/06/29 23:13:14  sezero
 * updated CHANGES (2006-06-29)
 *
 * Revision 1.83  2006/06/25 16:03:21  sezero
 * marked the snapshot of 2006-06-25 as 1.4.1-pre7
 *
 * Revision 1.82  2006/06/25 13:14:01  sezero
 * fixed compilation of h2ded
 *
 * Revision 1.81  2006/06/25 12:01:48  sezero
 * renamed CL_CopyFiles to Host_CopyFiles and CL_RemoveGIPFiles to
 * Host_RemoveGIPFiles, moved them to host.c
 *
 * Revision 1.80  2006/06/25 10:21:03  sezero
 * misc clean-ups and prepare for merging a dedicated server
 *
 * Revision 1.79  2006/06/17 19:54:54  sezero
 * marked the snapshot of 2006-06-17 as 1.4.1-pre6
 *
 * Revision 1.78  2006/06/15 20:05:51  sezero
 * bumped version to 1.4.1-pre5 / 2006-06-15
 *
 * Revision 1.77  2006/06/14 12:54:44  sezero
 * Updated CHANGES: version 1.4.1-pre4 / 2006-06-14
 *
 * Revision 1.76  2006/06/10 13:56:38  sezero
 * 1.4.1-pre3 / 2006-06-10
 *
 * Revision 1.75  2006/06/08 20:28:55  sezero
 * 1.4.1-pre3 / 2006-06-08
 *
 * Revision 1.74  2006/06/08 18:49:33  sezero
 * split strings out of pr_edict.c and sync'ed it with the hexenworld version
 *
 * Revision 1.73  2006/06/03 18:04:28  sezero
 * 1.4.1-pre3 / 2006-06-03
 *
 * Revision 1.72  2006/05/31 16:52:49  sezero
 * version 1.4.1-pre2 / 2006-05-31
 *
 * Revision 1.71  2006/05/26 10:20:54  sezero
 * moved platform definitions to a new arch_def.h header
 *
 * Revision 1.70  2006/05/26 08:32:00  sezero
 * bumped the version to 1.4.1-pre2 / 2006-05-26
 *
 * Revision 1.69  2006/05/20 13:41:01  sezero
 * 1.4.1-pre1 / 2006-05-20
 *
 * Revision 1.68  2006/05/19 13:38:38  sezero
 * added a compile time option to dicetly activate the mission pack
 * support without the need for a commandline option like -portals
 * or -h2mp
 *
 * Revision 1.67  2006/05/18 17:51:36  sezero
 * incremented the version to 1.4.1-pre1
 *
 * Revision 1.66  2006/05/18 17:49:58  sezero
 * AoT and earlier versions of HoT didn't create <userdir>/data1
 * and kept all user the data in <userdir> instead. Starting with
 * HoT 1.4.1, we are creating and using <userdir>/data1 . Added a
 * procedure in order to update the user direcory accordingly.
 *
 * Revision 1.65  2006/05/18 17:44:13  sezero
 * added MacOS and MacOSX to platform names. on macosx, set the userdir
 * to ~/Library/Application Support/Hexen2 instead of ~/.hexen2
 *
 * Revision 1.64  2006/04/18 08:49:18  sezero
 * 2006-04-18: HoT-1.4.0-final
 *
 * Revision 1.63  2006/04/17 14:00:50  sezero
 * minor update to version display stuff
 *
 * Revision 1.62  2006/04/12 07:53:10  sezero
 * marked the snapshot of 12 Apr. 2006 as 1.4.0-RC3
 *
 * Revision 1.61  2006/04/05 18:24:42  sezero
 * more tidy-ups (quakedef.h, qwswdef.h, bothdefs.h)
 *
 * Revision 1.60  2006/04/05 18:22:59  sezero
 * cdaudio and midi music headers tidy-up
 *
 * Revision 1.59  2006/04/05 06:19:07  sezero
 * Marked the sanpshot of 2006-04-04 as 1.4.0-RC2.
 *
 * Revision 1.58  2006/04/05 06:09:23  sezero
 * killed (almost) all H2MP ifdefs: this is the first step in making a single
 * binary which handles both h2 and h2mp properly. the only H2MP ifdefs left
 * are actually the ones for determining the icon and window manager text, so
 * nothing serious. the binary normally will only run the original h2 game.
 * if given a -portals or -missionpack or -h2mp argument, it will look for the
 * mission pack and run it (this is the same logic that quake used.) The only
 * serious side effect is that h2 and h2mp progs being different: This will be
 * solved by the next patch by adding support for the two progs versions into
 * a single binary.
 *
 * Revision 1.57  2006/03/26 16:53:58  sezero
 * Marked the snapshot of 2006-03-26 as 1.4.0-RC1 (-RC state, finally.)
 *
 * Revision 1.56  2006/03/26 14:10:39  sezero
 * 1.4.0 development has put in enough changes: Engine version is incremented
 * to 1.15 for hexen2 and 0.17 for hexenworld.
 *
 * Revision 1.55  2006/03/17 22:33:11  sezero
 * Updated CHANGES: 2006-03-17, 1.4.0-pre8
 *
 * Revision 1.54  2006/03/17 20:23:17  sezero
 * Updates to COM_LoadPackFile, COM_CheckRegistered and COM_InitFilesystem:
 * killed variables com_modified, com_portals and static_registered. Combined
 * all such info into an unsigned gameflags var. If correct versions of pak
 * files are installed at correct places, the state will be set: whether we
 * have the demo, oem or registered pakfiles, whether the registered game pak
 * files are version 1.11, whether it is a modified game (extra pak files in
 * the game directory or -game among the commandline switches), and whether
 * we have correct versions portals and hexnworld pakfiles. The game will
 * refuse to run on incorrect instances, h2mp will refuse to run if portals
 * isn't set and hexenworld will refuse to run if hexenworld isn't set.
 * Also activated the hexenworld progs crc check which was comment out (who
 * knows why): Server will refuse to run if it detects an incorrect crc for
 * its hwprogs.dat.
 *
 * Revision 1.53  2006/03/17 14:12:48  sezero
 * put back mission-pack only objectives stuff back into pure h2 builds.
 * it was a total screw-up...
 *
 * Revision 1.52  2006/03/14 13:19:42  sezero
 * marked the snapshot of 2006-03-14 as 1.4.0-pre7
 *
 * Revision 1.51  2006/03/13 22:26:33  sezero
 * continue making static functions and vars static. whitespace and
 * coding style cleanup. part 42: quakedef.h, bothdefs.h
 *
 * Revision 1.50  2006/03/04 15:50:38  sezero
 * marked the snapshot of 2006-03-04 as 1.4.0-pre6
 *
 * Revision 1.49  2006/03/04 15:35:23  sezero
 * opengl headers tidy-up
 *
 * Revision 1.48  2006/03/02 20:02:36  sezero
 * marked the snapshot of 2006-03-02 as 1.4.0-pre5
 *
 * Revision 1.47  2006/02/24 23:27:31  sezero
 * continue making static functions and vars static. whitespace and coding style
 * cleanup. (part 28: protocol.h, quakedef.h, server.h, pmove.c, pmovetst.c,
 * pmove.h).
 *
 * Revision 1.46  2006/02/23 13:56:39  sezero
 * Updated CHANGES: 2006-02-23, 1.4.0-pre4.
 *
 * Revision 1.45  2006/02/18 08:51:10  sezero
 * continue making static functions and vars static. whitespace and coding style
 * cleanup. also renamed the variables name and dest to savename and savedest in
 * host_cmd.c to prevent any confusion and pollution.
 *
 * Revision 1.44  2006/02/12 12:22:02  sezero
 * bumped version to 1.4.0-pre3 (2006-02-12)
 *
 * Revision 1.43  2006/01/24 17:09:27  sezero
 * bumped version to 1.4.0-pre2 (2006-01-24)
 *
 * Revision 1.42  2006/01/23 20:22:53  sezero
 * tidied up the version and help display stuff. bumped the HoT version to
 * 1.4.0-pre1. added conditionals to properly display beta version strings.
 *
 * Revision 1.41  2005/12/28 14:20:23  sezero
 * made COM_CopyFile return int and added ferror() calls after every fread()
 * and fwrite() calls, so that CL_CopyFiles can behave correctly under unix.
 * made SaveGamestate return qboolean, replaced the silly "ERROR: couldn't
 * open" message by goto retry_message calls. made Host_Savegame_f to return
 * immediately upon SaveGamestate failure.
 *
 * Revision 1.40  2005/12/04 11:19:18  sezero
 * gamma stuff update
 *
 * Revision 1.39  2005/10/25 17:14:23  sezero
 * added a STRINGIFY macro. unified version macros. simplified version
 * printing. simplified and enhanced version watermark print onto console
 * background. added HoT lines to the quit menu (shameless plug)
 *
 * Revision 1.38  2005/09/20 21:17:25  sezero
 * Moved VERSION_PLATFORM and id386 defines to sys.h, where they belong.
 *
 * Revision 1.37  2005/09/17 06:02:46  sezero
 * minor ifdef, syntax and defines clean-up
 *
 * Revision 1.36  2005/08/18 14:20:28  sezero
 * moved music volume update back into frame update. it has its merits (such as
 * correct bgmvolume on startup) this way..
 *
 * Revision 1.35  2005/07/30 15:16:26  sezero
 * bumped both HoT and engine versions
 *
 * Revision 1.34  2005/06/17 16:24:33  sezero
 * win32 fixes and clean-ups
 *
 * Revision 1.33  2005/06/15 22:03:02  sezero
 * vid_setgamma command is for sdl versions only.
 * also added notes on the WITH_SDL define in quakedef.h
 *
 * Revision 1.32  2005/06/12 07:28:51  sezero
 * clean-up of includes and a fix (hopefully) for endianness detection
 *
 * Revision 1.31  2005/06/01 14:10:42  sezero
 * removed win32-only net function prototypes from linquake.h
 * and updated linux_inc.h. also moved win32-only ipx netcode
 *
 * Revision 1.30  2005/05/29 08:53:57  sezero
 * get rid of silly name changes
 *
 * Revision 1.29  2005/05/21 17:04:16  sezero
 * - revived -nomouse that "disables mouse no matter what"
 * - renamed _windowed_mouse to _enable_mouse which is our intention,
 *   that is, dynamically disabling/enabling mouse while in game
 * - old code had many oversights/leftovers that prevented mouse being
 *   really disabled in fullscreen mode. fixed and cleaned-up here
 * - even in windowed mode, when mouse was disabled, mouse buttons and
 *   the wheel got processed. fixed it here.
 * - mouse cursor is never shown while the game is alive, regardless
 *   of mouse being enabled/disabled (I never liked an ugly pointer
 *   around while playing) Its only intention would be to be able to
 *   use the desktop, and for that see, the grab notes below
 * - if mouse is disabled, it is un-grabbed in windowed mode. Note: One
 *   can always use the keyboard shortcut CTRL-G for grabbing-ungrabbing
 *   the mouse regardless of mouse being enabled/disabled.
 * - ToggleFullScreenSA() used to update vid_mode but always forgot
 *   modestate. It now updates modestate as well.
 * - Now that IN_ActivateMouse() and IN_DeactivateMouse() are fixed,
 *   IN_ActivateMouseSA() and IN_DeactivateMouseSA() are redundant and
 *   are removed. BTW, I added a new qboolean mousestate_sa (hi Steve)
 *   which keeps track of whether we intentionally disabled the mouse.
 * - mouse disabling in fullscreen mode (in the absence of -nomouse
 *   arg) is not allowed in this patch, but this is done by a if 1/if 0
 *   conditional compilation. Next patch will change all those if 1 to
 *   if 0, and voila!, we can fully disable/enable mouse in fullscreen.
 * - moved modestate enums/defines to vid.h so that they can be used
 *   by other code properly.
 *
 * Revision 1.28  2005/05/21 08:56:11  sezero
 * MINIMUM_MEMORY_LEVELPAK was never used, switched to MINIMUM_MEMORY
 *
 * Revision 1.27  2005/05/20 12:28:13  sezero
 * leftovers after common.c sync-1
 *
 * Revision 1.26  2005/05/19 16:41:50  sezero
 * removed all unused (never used) non-RJNET and non-QUAKE2RJ code
 *
 * Revision 1.25  2005/05/19 16:35:51  sezero
 * removed all unused IDGODS code
 *
 * Revision 1.24  2005/05/19 12:46:56  sezero
 * synced h2 and hw versions of midi stuff
 *
 * Revision 1.23  2005/04/13 12:19:39  sezero
 * GAMENAME doesn't depend on QUAKE2 definition
 *
 * Revision 1.22  2005/04/10 14:30:44  sezero
 * Bumped the version for a new future release, updated the specfile
 *
 * Revision 1.21  2005/03/06 10:44:41  sezero
 * - move reinit_music to menu.c where it belongs
 * - fix reinit_music so that it works for the F4 key as well
 * - don't mess with music volume on every frame update, it's just silly
 *
 * Revision 1.20  2005/03/03 19:48:40  sezero
 * More bits from Steven:
 * - increase MAX_OSPATH to 256
 * - Sys_Mkdir is now int. Its return code should be checked in other places, too.
 * - Sys_GetUserdir now uses $HOME instead of the passwd struct
 *
 * Revision 1.19  2005/02/14 19:41:18  sezero
 * 1.2.4-rc1: prepare for 1.2.4 (2005-02-14)
 *
 * Revision 1.18  2005/02/05 16:18:25  sezero
 * added midi volume control (partially from Pa3PyX)
 *
 * Revision 1.17  2005/01/13 10:47:01  sezero
 * - Fixed mouse behavior which was always broken in hexen2-linux.
 *   Middle-button is MOUSE2, right-button is MOUSE3, not vice versa
 *   (see SDL_mouse.h). The wheelmouse patch fixed this a little, but
 *   introduced a mouse2/mouse3 fight in in_sdl.c. It is fixed here.
 * - Fixed the debug message about undefined mouse buttons.
 * - Did some syncing between H2 and HW versions of input files.
 *
 * Revision 1.16  2005/01/02 15:08:53  sezero
 * Retire AoT, aot and .aot: Change userdir (AOT_USERDIR) to .hexen2
 *
 * Revision 1.15  2004/12/30 14:27:15  sezero
 * userdir (AOT_USERDIR) is ~/.hexen2demo for make DEMOBUILD=yes [...]
 *
 * Revision 1.14  2004/12/26 10:05:57  sezero
 * prepare for 1.2.3
 *
 * Revision 1.12  2004/12/22 21:50:16  sezero
 * play with version and help display
 *
 * Revision 1.11  2004/12/19 10:35:30  sezero
 * - Add "implicitly declared" functions as externs: Software rendering files.
 * - Add comments on the asm/non-Intel status of the code
 *
 * Revision 1.10  2004/12/18 14:20:40  sezero
 * Clean-up and kill warnings: 11
 * A lot of whitespace cleanups.
 *
 * Revision 1.9  2004/12/18 13:59:25  sezero
 * Clean-up and kill warnings 8:
 * Missing prototypes.
 *
 * Revision 1.8  2004/12/18 13:54:43  sezero
 * Clean-up and kill warnings 6:
 * Include proper stock headers to avoid some "implicity declared" warnings
 *
 * Revision 1.7  2004/12/18 13:44:12  sezero
 * Clean-up and kill warnings 1:
 * Kill two pragmas that are ignored anyway.
 *
 * Revision 1.6  2004/12/18 13:20:37  sezero
 * make the music automatically restart when changed in the options menu
 *
 * Revision 1.5  2004/12/12 14:14:42  sezero
 * style changes to our liking
 *
 * Revision 1.4  2004/11/29 16:22:23  sezero
 * Grrrr......
 *
 * Revision 1.3  2004/11/29 16:02:07  sezero
 * bump version to 1.2.1a to reflect the latest changes
 *
 * Revision 1.2  2004/11/28 00:58:08  sezero
 *
 * Commit Steven's changes as of 2004.11.24:
 *
 * * Rewritten Help/Version message(s)
 * * Proper fullscreen mode(s) for OpenGL.
 * * Screen sizes are selectable with "-width" and "-height" options.
 * * Mouse grab in window modes , which is released when menus appear.
 * * Interactive video modes in software game disabled.
 * * Replaced Video Mode menu with a helpful message.
 * * New menu items for GL Glow, Chase mode, Draw Shadows.
 * * Changes to initial cvar_t variables:
 *      r_shadows, gl_other_glows, _windowed_mouse,
 *
 * Revision 1.1.1.1  2004/11/28 00:06:10  sezero
 * Initial import of AoT 1.2.0 code
 *
 * Revision 1.5  2002/01/02 15:16:37  phneutre
 * bumped version number to 1.2.0
 *
 * Revision 1.4  2001/12/13 16:06:15  phneutre
 * initial support for userspace directory (~/.aot) (parms.userdir)
 *
 * Revision 1.3  2001/12/03 22:45:09  theoddone33
 * Change version numbers
 *
 * Revision 1.2  2001/11/12 23:31:58  theoddone33
 * Some Loki-ish parameters and general cleanup/bugfixes.
 *
 * 8     3/19/98 12:53p Jmonroe
 * 
 * 7     3/13/98 5:01a Mgummelt
 * May have finally fixed that damn monster stair-stepping problem...
 * 
 * 6     3/12/98 6:31p Mgummelt
 * 
 * 5     3/06/98 4:55p Mgummelt
 * 
 * 4     3/03/98 1:41p Jmonroe
 * removed old mp stuff
 * 
 * 3     3/01/98 7:30p Jweier
 * 
 * 54    10/29/97 5:39p Jheitzman
 * 
 * 53    10/28/97 2:58p Jheitzman
 * 
 * 51    10/06/97 6:04p Rjohnson
 * Fix for save games and version update
 * 
 * 50    9/25/97 11:56p Rjohnson
 * Version update
 * 
 * 49    9/23/97 8:56p Rjohnson
 * Updates
 * 
 * 48    9/15/97 11:15a Rjohnson
 * Updates
 * 
 * 47    9/04/97 4:44p Rjohnson
 * Updates
 * 
 * 46    9/02/97 12:24a Rjohnson
 * Version Update
 * 
 * 45    8/30/97 6:17p Rjohnson
 * Network changes
 * 
 * 44    8/29/97 2:49p Rjohnson
 * Network updates
 * 
 * 43    8/28/97 3:36p Rjohnson
 * Version Update
 * 
 * 42    8/27/97 12:11p Rjohnson
 * Version Update
 * 
 * 41    8/26/97 8:17a Rjohnson
 * Just a few changes
 * 
 * 40    8/21/97 10:12p Rjohnson
 * Version Update
 * 
 * 39    8/20/97 2:59p Rjohnson
 * Version Update
 * 
 * 38    8/16/97 10:25a Rjohnson
 * Version Update
 * 
 * 37    8/11/97 2:52p Rlove
 * 
 * 36    8/09/97 10:39a Rjohnson
 * Version Update
 * 
 * 35    8/09/97 1:13a Bgokey
 * 
 * 34    8/05/97 3:55p Rjohnson
 * Version # Update
 * 
 * 33    8/05/97 3:49p Rjohnson
 * Fix for ipx networking
 * 
 * 32    8/01/97 6:25p Rjohnson
 * 
 * 31    7/30/97 1:56p Rjohnson
 * Changed version
 * 
 * 30    7/21/97 9:25p Rjohnson
 * Reduces the amount of memory used by RJNET
 * 
 * 29    7/11/97 5:21p Rjohnson
 * RJNET Updates
 * 
 * 28    6/16/97 5:38p Rlove
 * Temporary E3 fix of the max packet size MAX_DATAGRAM
 * 
 * 27    6/16/97 3:46p Rjohnson
 * Increased the reliable packet size
 * 
 * 26    6/06/97 11:21a Bgokey
 * 
 * 25    5/31/97 1:17p Bgokey
 * 
 * 24    5/27/97 4:46p Rjohnson
 * Added the smoke puff effect
 * 
 * 23    5/20/97 11:32a Rjohnson
 * Revised Effects
 * 
 * 22    5/19/97 2:54p Rjohnson
 * Added new client effects
 * 
 * 21    5/09/97 3:52p Rjohnson
 * Change to allow more than 256 precache models
 * 
 * 20    5/03/97 2:13p Bgokey
 * 
 * 19    4/20/97 5:05p Rjohnson
 * Networking Update
 * 
 * 18    4/15/97 9:02p Bgokey
 * 
 * 17    4/04/97 3:06p Rjohnson
 * Networking updates and corrections
 * 
 * 16    4/02/97 1:03p Bgokey
 * 
 * 15    3/07/97 1:57p Rjohnson
 * Id Updates
 * 
 * 14    2/27/97 4:12p Rjohnson
 * Added Midi prags
 * 
 * 13    2/24/97 3:51p Bgokey
 * Added HX_FRAME_TIME and HX_FPS.
 * 
 * 12    2/19/97 11:44a Rjohnson
 * Id Updates
 * 
 * 11    2/13/97 1:53p Bgokey
 * 
 * 10    2/07/97 1:37p Rlove
 * Artifact of Invincibility
 * 
 * 9     1/28/97 10:28a Rjohnson
 * Added experience and level advancement
 */
