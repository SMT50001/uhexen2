# makefile to build hwsv for Windows using Open Watcom:
#    wmake -f Makefile.wat

# PATH SETTINGS:
!ifndef __UNIX__
PATH_SEP=\
UHEXEN2_TOP=..\..\..
ENGINE_TOP=..\..
HW_TOP=..
COMMONDIR=$(ENGINE_TOP)\h2shared
COMMON_HW=$(HW_TOP)\shared
UHEXEN2_SHARED=$(UHEXEN2_TOP)\common
LIBS_DIR=$(UHEXEN2_TOP)\libs
OSLIBS=$(UHEXEN2_TOP)\oslibs
!else
PATH_SEP=/
UHEXEN2_TOP=../../..
ENGINE_TOP=../..
HW_TOP=..
COMMONDIR=$(ENGINE_TOP)/h2shared
COMMON_HW=$(HW_TOP)/shared
UHEXEN2_SHARED=$(UHEXEN2_TOP)/common
LIBS_DIR=$(UHEXEN2_TOP)/libs
OSLIBS=$(UHEXEN2_TOP)/oslibs
!endif

# GENERAL OPTIONS (customize as required)

# use WinSock2 instead of WinSock-1.1? (disabled for w32 for compat.
# with old Win95 machines.) (enabled for Win64 in the win64 section.)
USE_WINSOCK2=no

# Names of the binaries
BINARY=hwsv.exe

#############################################################
# Compiler flags
#############################################################

CFLAGS = -zq -wx -bm -bt=nt -5s -sg -otexan -fp5 -fpi87 -ei -j -zp8
# newer OpenWatcom versions enable W303 by default
CFLAGS+= -wcd=303

# compiler includes
INCLUDES= -I. -I$(COMMON_HW) -I$(COMMONDIR) -I$(UHEXEN2_SHARED)

# end of compiler flags
#############################################################


#############################################################
# Other build flags
#############################################################

CPPFLAGS+= -DH2W -DSERVERONLY

!ifdef DEMO
CPPFLAGS+= -DDEMOBUILD
!endif

!ifdef DEBUG
CFLAGS  += -d2
# This activates some extra code in hexen2/hexenworld C source
CPPFLAGS+= -DDEBUG=1 -DDEBUG_BUILD=1
!endif


#############################################################
# Win32 flags/settings and overrides:
#############################################################

!ifndef __UNIX__
INCLUDES+= -I$(OSLIBS)\windows\misc\include
!else
INCLUDES+= -I$(OSLIBS)/windows/misc/include
!endif

!ifeq USE_WINSOCK2 yes
CPPFLAGS+=-D_USE_WINSOCK2
LIBWINSOCK=ws2_32.lib
!else
LIBWINSOCK=wsock32.lib
!endif

CPPFLAGS+= -DWIN32_LEAN_AND_MEAN
LIBS += $(LIBWINSOCK) winmm.lib

#############################################################

.c: $(COMMON_HW);$(COMMONDIR);$(UHEXEN2_SHARED)

.c.obj:
	wcc386 $(INCLUDES) $(CPPFLAGS) $(CFLAGS) -fo=$^@ $<

# Objects

SYSOBJ_SYS = sys_win.obj

# Final list of objects
OBJECTS = &
	q_endian.obj &
	link_ops.obj &
	sizebuf.obj &
	strlcat.obj &
	strlcpy.obj &
	qsnprint.obj &
	msg_io.obj &
	common.obj &
	quakefs.obj &
	info_str.obj &
	cmd.obj &
	crc.obj &
	cvar.obj &
	host_string.obj &
	mathlib.obj &
	zone.obj &
	hashindex.obj &
	huffman.obj &
	net_udp.obj &
	net_chan.obj &
	pmove.obj &
	pmovetst.obj &
	sv_model.obj &
	pr_cmds.obj &
	pr_edict.obj &
	pr_exec.obj &
	sv_effect.obj &
	sv_ccmds.obj &
	sv_ents.obj &
	sv_init.obj &
	sv_main.obj &
	sv_move.obj &
	sv_phys.obj &
	sv_send.obj &
	sv_user.obj &
	world.obj &
	$(SYSOBJ_SYS)

all: $(BINARY)
h2ded: $(BINARY)

# 512 KB stack.
$(BINARY): $(OBJECTS)
	wlink N $@ SYS NT OPTION q OPTION STACK=0x80000 LIBR {$(LIBS)} F {$(OBJECTS)}

clean: .symbolic
	rm -f *.obj *.res *.err
distclean: clean .symbolic
	rm -f $(BINARY)

