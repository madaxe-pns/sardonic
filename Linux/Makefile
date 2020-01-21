OPTS = -O2 -fomit-frame-pointer
WARN = -Wall -W -Wstrict-prototypes -Wmissing-prototypes -Wc++-compat -Werror
CFLAGS = $(OPTS) $(WARN)
LDFLAGS = -s
LIBS = -lSDL_mixer -lSDL

# For mingw cross compiler
#CC = i686-pc-mingw32-gcc
#EXEEXT = .exe

# For MiNT cross compiler
#CC = m68k-atari-mint-gcc
#LIBS += -lFLAC -lvorbisfile -lvorbis -lmikmod -logg -lmpg123 -lgem -lm
#EXEEXT = .tos

ifeq ($(shell echo -e "\#ifdef __WIN32__\nyes\n\#endif" | gcc -E - | grep yes),yes)
LDFLAGS = -mwindows
endif

OBJS = sardonic.o sprites.o loadbmp.o

all: sardonic$(EXEEXT)


sardonic$(EXEEXT): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)

$(OBJS): sprites.h

clean::
	$(RM) *.o sardonic sardonic.tos sardonic.exe
