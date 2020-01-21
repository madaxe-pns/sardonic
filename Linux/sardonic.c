#if defined _WIN32 || defined(OS_cygwin)
# define SDL_MAIN_HANDLED
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "sprites.h"
#include "loadbmp.h"

#define STATIC

#define TICK_INTERVAL   ((uint32_t)(1000 / 120))

#define idPLAYER        0
#define idLASER         1
#define idFIGHTER       2
#define idFIGHTER2      3
#define idSTEALTH       4
#define idBOMBER        5
#define idLASERINI      6
#define idPREMIOT       7
#define idPREMIOP       8
#define idPREMIOB       9
#define idPREMIOV       10
#define idBOSS1         11
#define idBOSS2         12
#define idBOSS3         13
#define idBOSS4         14
#define idBOSS5         15
#define idEXPLOSION     16

static char const Chars[] = "abcdefghijklmnopqrstuvwxyz0123456789.:! ";

#undef random
#define random(x) (rand() % (x))

#if defined __TOS__ || defined(__atarist__)
#define SLASH "\\"
#else
#define SLASH "/"
#endif

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP    0

#define FONT_W 15
#define FONT_H 9


/* ZZZ: 1..500 */
static uint8_t const LEnemy[500] = {
	0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 5,
	0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 6,
	0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 7,
	0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 8,
	0, 0, 0, 1, 1, 4, 3, 2, 4, 3, 4, 4, 2, 3, 1, 4, 1, 3, 1, 1, 4, 2, 2, 2, 4,
	2, 1, 1, 3, 4, 3, 3, 3, 4, 3, 2, 2, 1, 2, 1, 3, 1, 2, 1, 4, 4, 3, 3, 4, 4,
	3, 3, 4, 4, 3, 3, 4, 4, 3, 2, 2, 3, 2, 2, 3, 4, 4, 4, 3, 3, 3, 4, 4, 4, 3,
	3, 3, 4, 4, 4, 3, 3, 3, 2, 1, 2, 1, 3, 4, 4, 4, 4, 4, 3, 4, 0, 0, 0, 0, 9
};

static int const StarWx[20] = {
	160, 261, 182, 407, 212, 314, 444, 349, 225, 376, 323, 476, 348, 249, 215,
	251, 184, 299, 181, 277
};

static int const StarWy[20] = {
	15, 77, 403, 157, 158, 71, 397, 4, 326, 141, 275, 371, 415, 421, 75, 74, 28,
	237, 93, 401
};

static int const StarGx[20] = {
	435, 279, 179, 383, 309, 439, 166, 368, 465, 187, 379, 399, 380, 211, 245,
	355, 194, 269, 375, 260
};

static int const StarGy[20] = {
	97, 204, 140, 405, 118, 137, 67, 369, 309, 370, 162, 94, 138, 131, 85, 355,
	381, 393, 109, 151
};

static int const StarBx[20] = {
	247, 186, 453, 389, 424, 472, 205, 386, 479, 318, 162, 452, 189, 333, 344,
	398, 417, 421, 342, 370
};

static int const StarBy[20] = {
	322, 227, 176, 147, 133, 236, 240, 267, 117, 423, 338, 376, 301, 461, 239,
	38, 183, 44, 122, 332
};


#define SOUND_LASER    0
#define SOUND_EEXPLODE 1
#define SOUND_PEXPLODE 2
#define NumberOfSounds 3

/* Filenames */
static const char *const SoundFilenames[NumberOfSounds] = {
	"laser.wav",
	"eexplode.wav",
	"pexplode.wav"
};

typedef struct _Title {
	Sprite s;
} Title;

typedef struct _Player {
	Sprite s;
	SDL_Rect DestRect;
	int ShootCounter;
	int BombCounter;
} Player;

typedef struct _Laser {
	Sprite s;
	SDL_Rect DestRect;
} Laser;

typedef struct _LaserIni {
	Sprite s;
	SDL_Rect DestRect;
} LaserIni;

typedef struct _Enemy {
	Sprite s;
	SDL_Rect DestRect;
	int Hull;
	int Speed;
	int SpeedCounter;
	int type;
	int dx;
} Enemy;

typedef struct _Explosion {
	Sprite s;
	SDL_Rect DestRect;
	int Speed;
	int SpeedCounter;
} Explosion;

typedef struct _Premio {
	Sprite s;
	SDL_Rect DestRect;
	int Speed;
	int SpeedCounter;
	int type;
	int Time;
	int TimeCounter;
} Premio;

typedef struct _Star {
	int Wx[20];
	int Wy[20];
	int Gx[20];
	int Gy[20];
	int Bx[20];
	int By[20];
	uint32_t Wc, Gc, Bc;
	int Wt, Gt, Bt;
	int Wtc, Gtc, Btc;
} Star;

enum State {
	eTitle,
	eInstructions,
	eGetReady,
	eHiscore,
	eGame,
	eBoss,
	eGoout,
	eGameOver,
	eEndGame
};

enum TextAlign {
	alLeft,
	alCenter,
	alRight
};

static SDL_Surface *Screen;
static SDL_Surface *Background;
static uint32_t black;
static SDL_Surface *Graphics;
static SDL_Surface *ecTitle;
static SDL_Surface *ecPanel;
static SpriteEngine *spriteengine;
static uint32_t next_time;
STATIC uint32_t EnemyRate;
static SDL_Event Event;
static uint8_t *Keys;
static int shots;
static int bombs;
static int lives;
static long points;
static long recorde;
static enum State state;
static int counter;
static bool Inven;
static int TInven;
static bool tbombs;
static SDL_Surface *Chars15x9;
static int level;
static Mix_Music *music;
static Mix_Chunk *Sounds[NumberOfSounds];
static Star *stars;
static bool nomusic = false;

static int const freq = 22050;
static uint16_t const AudioFormat = AUDIO_S16LSB;
static int const channels = 2;

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void startsound(int Index)
{
	if (Sounds[Index] == NULL)
		return;
	Mix_PlayChannel(-1, Sounds[Index], 0);
}

/*** ---------------------------------------------------------------------- ***/

/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
static void putpixel(SDL_Surface *surface, int x, int y, uint32_t pixel)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	uint8_t *p = (uint8_t *)surface->pixels + (size_t)y * surface->pitch + x * bpp;

	switch (bpp)
	{
	case 1:
		*p = pixel;
		break;

	case 2:
		*(uint16_t *)p = pixel;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		} else
		{
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

	case 4:
		*(uint32_t *)p = pixel;
		break;
	}
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

#if 0 /* unused */
static void Title_Draw(Sprite *s)
{
	Title *t = (Title *)s;
	SDL_Rect DestRect;

	DestRect.x = t->s.x; /* set screen positions */
	DestRect.y = t->s.y;
	DestRect.w = t->s.w;
	DestRect.h = t->s.h;
	SDL_BlitSurface(ecTitle, &t->s.SrcRect, t->s.Surface, &DestRect);
	t->s.PrevRect = DestRect;
}

/*** ---------------------------------------------------------------------- ***/

static Title *Title_New(int x, int y)
{
	Title *t;

	t = (Title *)calloc(1, sizeof(*t));
	if (t == NULL)
		return t;
	Sprite_Init(&t->s, NULL, 380, 78);

	t->s.Draw = Title_Draw;
	t->s.x = x;
	t->s.y = y;

	return t;
}
#endif

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void Explosion_Draw(Sprite *s)
{
	Explosion *e = (Explosion *)s;

	e->DestRect.x = e->s.x; /* set screen positions */
	e->DestRect.y = e->s.y;
	e->DestRect.w = e->s.w;
	e->DestRect.h = e->s.h;
	SDL_BlitSurface(Graphics, &e->s.SrcRect, e->s.Surface, &e->DestRect);
	e->s.PrevRect = e->DestRect;
}

/*** ---------------------------------------------------------------------- ***/

static void Explosion_Move(Sprite *s)
{
	Explosion *e = (Explosion *)s;

	++e->SpeedCounter;
	if (e->SpeedCounter == e->Speed)
		Sprite_Kill(&e->s);
}

/*** ---------------------------------------------------------------------- ***/

static Explosion *Explosion_New(int x, int y)
{
	Explosion *e;

	e = (Explosion *)calloc(1, sizeof(*e));
	if (e == NULL)
		return e;
	Sprite_Init(&e->s, NULL, 24, 24);

	e->s.Draw = Explosion_Draw;
	e->s.Move = Explosion_Move;

	e->s.ID = idEXPLOSION;
	e->Speed = 30;
	e->SpeedCounter = 0;
	e->s.x = x;
	e->s.y = y;
	e->s.z = 200;
	e->s.SrcRect.y = 40;
	return e;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void LaserIni_Draw(Sprite *s)
{
	LaserIni *l = (LaserIni *)s;

	l->DestRect.x = l->s.x; /* set screen positions */
	l->DestRect.y = l->s.y;
	l->DestRect.w = l->s.w;
	l->DestRect.h = l->s.h;
	SDL_BlitSurface(Graphics, &l->s.SrcRect, l->s.Surface, &l->DestRect);
	l->s.PrevRect = l->DestRect;
}

/*** ---------------------------------------------------------------------- ***/

static void LaserIni_DetectCollision(LaserIni *l)
{
	size_t i, count;
	SDL_Rect MyRect;
	SDL_Rect NMERect;

	l->s.GetCollisionRect(&l->s, &MyRect);
	count = l->s.ParentList->count;
	for (i = 0; i < count; i++)
	{
		Sprite *s = SpriteList_Get(l->s.ParentList, i);

		if (s != &l->s)
		{
			s->GetCollisionRect(s, &NMERect);

			if (isCollideRects(&MyRect, &NMERect))
			{
				if (s->ID == idPLAYER)
				{
					if (!Inven)
					{
						shots = 1;
						lives = lives - 1;

						Inven = true;
						TInven = 0;

						if (lives == 0)
							state = eGameOver;

#if 0
						Sprite_Kill(s); /* Player */
#endif
						startsound(SOUND_EEXPLODE);
						SpriteEngine_AddSprite(spriteengine, &Explosion_New(s->x - 4, s->y - 4)->s);
					}
					Sprite_Kill(&l->s); /* myself */
				}
			}
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

static void LaserIni_Move(Sprite *s)
{
	LaserIni *l = (LaserIni *)s;

	if (l->s.y < 480)
		l->s.y += 2;
	else
		Sprite_Kill(&l->s);

	LaserIni_DetectCollision(l);
}

/*** ---------------------------------------------------------------------- ***/

static LaserIni *LaserIni_New(int x, int y)
{
	LaserIni *l;

	l = (LaserIni *)calloc(1, sizeof(*l));
	if (l == NULL)
		return l;
	Sprite_Init(&l->s, NULL, 1, 8);
	l->s.Draw = LaserIni_Draw;
	l->s.Move = LaserIni_Move;
	l->s.ID = idLASERINI;
	l->s.x = x;
	l->s.y = y;
	l->s.z = 50;
	l->s.SrcRect.x = 0;
	l->s.SrcRect.y = 67;
	return l;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void Premio_Draw(Sprite *s)
{
	Premio *e = (Premio *)s;

	e->DestRect.x = e->s.x; /* set screen positions */
	e->DestRect.y = e->s.y;
	e->DestRect.w = e->s.w;
	e->DestRect.h = e->s.h;
	SDL_BlitSurface(Graphics, &e->s.SrcRect, e->s.Surface, &e->DestRect);
	e->s.PrevRect = e->DestRect;
}

/*** ---------------------------------------------------------------------- ***/

static void Premio_Move(Sprite *s)
{
	Premio *e = (Premio *)s;

	++e->TimeCounter;
	++e->SpeedCounter;

	if (e->TimeCounter == e->Time)
		Sprite_Kill(&e->s);

	if (e->SpeedCounter == e->Speed)
	{
		++e->s.y;
		e->SpeedCounter = 0;
	}

	if (e->s.y > 480)
		Sprite_Kill(&e->s);
}

/*** ---------------------------------------------------------------------- ***/

static Premio *Premio_New(int x, int y, int type)
{
	Premio *e;

	e = (Premio *)calloc(1, sizeof(*e));
	if (e == NULL)
		return e;

	Sprite_Init(&e->s, NULL, 12, 12);
	e->s.Draw = Premio_Draw;
	e->s.Move = Premio_Move;
	e->s.x = x;
	e->s.y = y;
	e->s.z = 50;
	e->type = type;
	e->Time = 500;
	e->TimeCounter = 0;
	e->Speed = 4;
	e->SpeedCounter = 0;

	switch (type)
	{
	case 1:
		e->s.SrcRect.x = 42;
		e->s.SrcRect.y = 63;
		e->s.ID = idPREMIOT;
	 	break;
	case 2:
		e->s.SrcRect.x = 66;
		e->s.SrcRect.y = 63;
		e->s.ID = idPREMIOP;
	 	break;
	case 3:
		e->s.SrcRect.x = 54;
		e->s.SrcRect.y = 63;
		e->s.ID = idPREMIOB;
	 	break;
	case 4:
		e->s.SrcRect.x = 30;
		e->s.SrcRect.y = 63;
		e->s.ID = idPREMIOV;
	 	break;
	}

	return e;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void Enemy_Draw(Sprite *s)
{
	Enemy *e = (Enemy *)s;

	e->DestRect.x = e->s.x; /* set screen positions */
	e->DestRect.y = e->s.y;
	e->DestRect.w = e->s.w;
	e->DestRect.h = e->s.h;
	SDL_BlitSurface(Graphics, &e->s.SrcRect, e->s.Surface, &e->DestRect);
	e->s.PrevRect = e->DestRect;
}

/*** ---------------------------------------------------------------------- ***/

static void KillAllEnemies(Sprite *e)
{
	size_t i, count;
	Sprite *s;

	count = e->ParentList->count;
	for (i = 0; i < count; i++)
	{
		s = SpriteList_Get(e->ParentList, i);
		if (s->ID != idPLAYER || s->ID != idEXPLOSION)
			Sprite_Kill(s);
	}
}

/*** ---------------------------------------------------------------------- ***/

static void Enemy_GetCollisionRect(Sprite *s, SDL_Rect *rect)
{
	Enemy *e= (Enemy *)s;

	rect->x = e->s.x;
	rect->y = e->s.y;

	switch (e->type)
	{
	case 1:
	case 2:
		rect->w = 23;
		rect->h = 16;
		break;
	case 3:
		rect->w = 15;
		rect->h = 24;
		break;
	case 4:
		rect->w = 24;
		rect->h = 24;
		break;
	case 5:
		rect->w = 92;
		rect->h = 48;
		break;
	case 6:
		rect->w = 120;
		rect->h = 64;
		break;
	case 7:
		rect->w = 120;
		rect->h = 192;
		break;
	case 8:
		rect->w = 144;
		rect->h = 144;
		break;
	case 9:
		rect->w = 231;
		rect->h = 88;
		break;
	}
}

/*** ---------------------------------------------------------------------- ***/

static void Enemy_HitByLaser(Enemy *e)
{
	int i;

	e->Hull = e->Hull - 1;

	if (e->Hull == 0)
	{
		Sprite_Kill(&e->s);

		if (e->type < 5)
		{
			SpriteEngine_AddSprite(spriteengine, &Explosion_New(e->s.x, e->s.y)->s);
		} else
		{
			for (i = 0; i < 20; i++)
				SpriteEngine_AddSprite(spriteengine, &Explosion_New(random(e->s.w) + e->s.x, random(e->s.h) + e->s.y)->s);
		}

		switch (e->type)
		{
		case 1:
			points += 10;
			break;
		case 2:
			points += 20;
			break;
		case 3:
			points += 30;
			break;
		case 4:
			points += 50;
			break;
		case 5:
			points += 1000;
			break;
		case 6:
			points += 1500;
			break;
		case 7:
			points += 2000;
			break;
		case 8:
			points += 3000;
			break;
		case 9:
			points += 5000;
			break;
		}

		if (e->type < 5)
		{
			i = random(2000);
			if (i >= 250 && i < 500)
				SpriteEngine_AddSprite(spriteengine, &Premio_New(e->s.x + 8, e->s.y + 8, 1)->s);

			if (i >= 500&& i < 750)
				SpriteEngine_AddSprite(spriteengine, &Premio_New(e->s.x + 8, e->s.y + 8, 2)->s);

			if (i >= 750 && i < 900)
				SpriteEngine_AddSprite(spriteengine, &Premio_New(e->s.x + 8, e->s.y + 8, 3)->s);

			if (i >= 900 && i < 1000)
				SpriteEngine_AddSprite(spriteengine, &Premio_New(e->s.x + 8, e->s.y + 8, 4)->s);
		} else
		{
			startsound(SOUND_PEXPLODE);

			++level;
			if (level == 6)
			{
				KillAllEnemies(&e->s);
				state = eEndGame;
			} else
			{
				state = eGame;
			}
		}
	} else
	{
		points += 5;
	}
}

/*** ---------------------------------------------------------------------- ***/

static void Enemy_DetectCollision(Enemy *e)
{
	size_t i, count;
	int j;
	SDL_Rect MyRect;
	SDL_Rect NMERect;

	e->s.GetCollisionRect(&e->s, &MyRect);
	count = e->s.ParentList->count;
	for (i = 0; i < count; i++)
	{
		Sprite *s;

		s = SpriteList_Get(e->s.ParentList, i);
		if (s != &e->s)
		{
			s->GetCollisionRect(s, &NMERect);

			if (isCollideRects(&MyRect, &NMERect))
			{
				if (s->ID == idLASER)
				{
					if (e->type >= 5)
						SpriteEngine_AddSprite(spriteengine, &Explosion_New(s->x + 12, s->y - 24)->s);

					Sprite_Kill(s);
					startsound(SOUND_EEXPLODE);
					Enemy_HitByLaser(e); /* myself */
				} else if (s->ID == idPLAYER)
				{
					if (!Inven)
					{
						shots = 1;
						lives = lives - 1;

						Inven = true;
						TInven = 0;

						if (lives == 0)
							state = eGameOver;

						startsound(SOUND_EEXPLODE);
						SpriteEngine_AddSprite(spriteengine, &Explosion_New(s->x - 4, s->y - 4)->s);

						if (e->type < 5)
						{
							startsound(SOUND_EEXPLODE);
							Sprite_Kill(&e->s); /* myself */
							SpriteEngine_AddSprite(spriteengine, &Explosion_New(e->s.x, e->s.y)->s);
						} else
						{
							e->Hull -= 20;
							if (e->Hull < 20)
							{
								switch (e->type)
								{
								case 5:
									points += 1000;
									break;
								case 6:
									points += 1500;
									break;
								case 7:
									points += 2000;
									break;
								case 8:
									points += 3000;
									break;
								case 9:
									points += 5000;
									break;
								}

								for (j = 0; j < 20; j++)
									SpriteEngine_AddSprite(spriteengine, &Explosion_New(random(e->s.w) + e->s.x, random(e->s.h) + e->s.y)->s);

								startsound(SOUND_PEXPLODE);
								Sprite_Kill(&e->s); /* myself */

								++level;
								if (level == 6)
								{
									KillAllEnemies(&e->s);
									state = eEndGame;
								} else
								{
									state = eGame;
								}
							}
						}
					}
				}
			}
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

static void Enemy_Move(Sprite *s)
{
	Enemy *e = (Enemy *)s;
	size_t i;

	++e->SpeedCounter;
	if (e->SpeedCounter == e->Speed)
	{
		if (e->type < 5)
		{
			++e->s.y;
			e->SpeedCounter = 0;
		} else
		{
			if (tbombs)
			{
				e->Hull = e->Hull - 10;
				points = points + 15;

				for (i = 0; i < 20; i++)
					SpriteEngine_AddSprite(spriteengine, &Explosion_New(random(e->s.w) + e->s.x, random(e->s.h) + e->s.y)->s);

				if (e->Hull < 10)
				{
					switch (e->type)
					{
					case 5:
						points += 1000;
						break;
					case 6:
						points += 1500;
						break;
					case 7:
						points += 2000;
						break;
					case 8:
						points += 3000;
						break;
					case 9:
						points += 5000;
						break;
					}

					startsound(SOUND_PEXPLODE);

					Sprite_Kill(&e->s); /* myself */
					++level;
					if (level == 6)
					{
						KillAllEnemies(&e->s);
						state = eEndGame;
					} else
					{
						state = eGame;
					}

				}
				tbombs = false;
			}


			if (e->s.y < 20)
			{
				e->s.y += 1;
				e->SpeedCounter = 0;
			} else
			{
				if (e->s.x < 160 || e->s.x > 480 - e->s.SrcRect.w)
					e->dx = -e->dx;

				e->s.x = e->s.x + e->dx;

				e->SpeedCounter = 0;
			}
		}
	}

	i = random(5000);
	if (i < 25)
	{
		if (e->type == 1)
			SpriteEngine_AddSprite(spriteengine, &LaserIni_New(e->s.x + 11, e->s.y + 16)->s);

		if (e->type == 2)
		{
			SpriteEngine_AddSprite(spriteengine, &LaserIni_New(e->s.x + 6, e->s.y + 10)->s);
			SpriteEngine_AddSprite(spriteengine, &LaserIni_New(e->s.x + 18, e->s.y + 10)->s);
		}

		if (e->type == 3)
			SpriteEngine_AddSprite(spriteengine, &LaserIni_New(e->s.x + 7, e->s.y + 24)->s);

		if (e->type == 4)
		{
			SpriteEngine_AddSprite(spriteengine, &LaserIni_New(e->s.x + 5, e->s.y + 16)->s);
			SpriteEngine_AddSprite(spriteengine, &LaserIni_New(e->s.x + 18, e->s.y + 16)->s);
		}

	}

	if (i < 400)
	{
		switch (e->type)
		{
		case 5:
			SpriteEngine_AddSprite(spriteengine, &LaserIni_New(random(e->s.w - 7) + e->s.x + 2, e->s.y + 48)->s);
			break;
		case 6:
			SpriteEngine_AddSprite(spriteengine, &LaserIni_New(random(e->s.w - 15) + e->s.x + 15, e->s.y + 64)->s);
			break;
		case 7:
			SpriteEngine_AddSprite(spriteengine, &LaserIni_New(random(e->s.w - 9) + e->s.x + 7, e->s.y + 192)->s);
			break;
		case 8:
			SpriteEngine_AddSprite(spriteengine, &LaserIni_New(random(e->s.w - 7) + e->s.x + 6, e->s.y + 144)->s);
			break;
		case 9:
			SpriteEngine_AddSprite(spriteengine, &LaserIni_New(random(e->s.w - 33) + e->s.x + 32, e->s.y + 88)->s);
			break;
		}
	}

	if (e->s.y > 480)
		Sprite_Kill(&e->s);

	Enemy_DetectCollision(e);
}

/*** ---------------------------------------------------------------------- ***/

static Enemy *Enemy_New(void)
{
	Enemy *e;
	int xis, wid = 0, hei = 0;

	e = (Enemy *)calloc(1, sizeof(*e));
	if (e == NULL)
		return e;

	if (state == eGame)
	{
		e->type = LEnemy[counter];
		if (e->type == 1)
		{
			wid = 23;
			hei = 16;
		}
		if (e->type == 2)
		{
			wid = 23;
			hei = 16;
		}
		if (e->type == 3)
		{
			wid = 15;
			hei = 24;
		}
		if (e->type == 4)
		{
			wid = 24;
			hei = 24;
		}
	}

	if (state == eBoss)
	{
		if (level == 1)
		{
			e->type = 5;
			wid = 92;
			hei = 48;
		}
		if (level == 2)
		{
			e->type = 6;
			wid = 120;
			hei = 64;
		}
		if (level == 3)
		{
			e->type = 7;
			wid = 120;
			hei = 192;
		}
		if (level == 4)
		{
			e->type = 8;
			wid = 144;
			hei = 144;
		}
		if (level == 5)
		{
			e->type = 9;
			wid = 231;
			hei = 88;
		}
	}

	xis = 0;
	if (e->type < 5)
	{
		bool teste = false;
		int nteste = 0;
		size_t i, count;

		count = spriteengine->Sprites->count;
		while (!teste && nteste < 100)
		{
			xis = random(320 - wid) + 160;
			teste = true;
			for (i = 0; i < count; i++)
			{
				Sprite *s = SpriteList_Get(spriteengine->Sprites, i);
				if (s->ID == idFIGHTER || s->ID == idFIGHTER2 || s->ID == idSTEALTH || s->ID == idBOMBER)
					if ((xis >= s->x && xis < s->x + s->w) ||
						(xis + wid > s->x && xis + wid <= s->x + s->w))
					{
						teste = false;
						break;
					}
			}
			nteste = nteste + 1;
		}
	} else
	{
		xis = random(320 - wid) + 160;
	}

	Sprite_Init(&e->s, NULL, wid, hei);

	e->SpeedCounter = 0;

	e->s.x = xis;

	switch (e->type)
	{
	case 1:	/* Fighter I */
		e->s.ID = idFIGHTER;
		e->s.y = -16;
		e->s.z = random(50);
		e->s.SrcRect.x = 24;
		e->s.SrcRect.y = 0;
		e->Hull = 1;
		e->Speed = 2;
		e->dx = 0;
		break;
	case 2:	/* Fighter II */
		e->s.ID = idFIGHTER2;
		e->s.y = -16;
		e->s.z = random(50);
		e->s.SrcRect.x = 47;
		e->s.SrcRect.y = 0;
		e->Hull = 2;
		e->Speed = 2;
		e->dx = 0;
		break;
	case 3:	/* Stealth */
		e->s.ID = idSTEALTH;
		e->s.y = -24;
		e->s.z = random(50);
		e->s.SrcRect.x = 70;
		e->s.SrcRect.y = 0;
		e->Hull = 3;
		e->Speed = 1;
		e->dx = 0;
		break;
	case 4:	/* Bomber */
		e->s.ID = idBOMBER;
		e->s.y = -24;
		e->s.z = random(50);
		e->s.SrcRect.x = 0;
		e->s.SrcRect.y = 0;
		e->Hull = 3;
		e->Speed = 2;
		e->dx = 0;
		break;
	case 5:	/* Boss I */
		e->s.ID = idBOSS1;
		e->s.y = -48;
		e->s.z = random(50);
		e->s.SrcRect.x = 90;
		e->s.SrcRect.y = 0;
		e->Hull = 100;
		e->Speed = 3;
		e->dx = -1;
		break;
	case 6:	/* Boss II */
		e->s.ID = idBOSS2;
		e->s.y = -64;
		e->s.z = random(50);
		e->s.SrcRect.x = 90;
		e->s.SrcRect.y = 50;
		e->Hull = 150;
		e->Speed = 3;
		e->dx = -1;
		break;
	case 7:	/* Boss III */
		e->s.ID = idBOSS3;
		e->s.y = -192;
		e->s.z = random(50);
		e->s.SrcRect.x = 215;
		e->s.SrcRect.y = 0;
		e->Hull = 200;
		e->Speed = 2;
		e->dx = -1;
		break;
	case 8:	/* Boss IV */
		e->s.ID = idBOSS4;
		e->s.y = -144;
		e->s.z = random(50);
		e->s.SrcRect.x = 340;
		e->s.SrcRect.y = 0;
		e->Hull = 300;
		e->Speed = 2;
		e->dx = -1;
		break;
	case 9:	/* Boss V */
		e->s.ID = idBOSS5;
		e->s.y = -88;
		e->s.z = random(50);
		e->s.SrcRect.x = 0;
		e->s.SrcRect.y = 206;
		e->Hull = 500;
		e->Speed = 1;
		e->dx = -1;
		break;
	}

	e->s.Draw = Enemy_Draw;
	e->s.Move = Enemy_Move;
	e->s.GetCollisionRect = Enemy_GetCollisionRect;

	return e;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void Laser_Draw(Sprite *s)
{
	Laser *l = (Laser *)s;

	l->DestRect.x = l->s.x; /* set screen positions */
	l->DestRect.y = l->s.y;
	l->DestRect.w = l->s.w;
	l->DestRect.h = l->s.h;
	SDL_BlitSurface(Graphics, &l->s.SrcRect, l->s.Surface, &l->DestRect);
	l->s.PrevRect = l->DestRect;
}

/*** ---------------------------------------------------------------------- ***/

static void Laser_Move(Sprite *s)
{
	Laser *l = (Laser *)s;

	if (l->s.y > -8)
		l->s.y -=2;
	else
		Sprite_Kill(&l->s);
}

/*** ---------------------------------------------------------------------- ***/

static Laser *Laser_New(int x, int y)
{
	Laser *l;

	l = (Laser *)calloc(1, sizeof(*l));
	if (l == NULL)
		return l;
	Sprite_Init(&l->s, NULL, 1, 8);
	l->s.Draw = Laser_Draw;
	l->s.Move = Laser_Move;
	l->s.ID = idLASER;
	l->s.x = x;
	l->s.y = y;
	l->s.z = 50;
	l->s.SrcRect.x = 2;
	l->s.SrcRect.y = 67;
	return l;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void Player_Draw(Sprite *s)
{
	Player *p = (Player *)s;

	p->DestRect.x = p->s.x; /* set screen positions */
	p->DestRect.y = p->s.y;
	p->DestRect.w = p->s.w;
	p->DestRect.h = p->s.h;
	SDL_BlitSurface(Graphics, &p->s.SrcRect, p->s.Surface, &p->DestRect);
	p->s.PrevRect = p->DestRect;
}

/*** ---------------------------------------------------------------------- ***/

static void Player_DetectCollision(Player *p)
{
	size_t i, count;
	SDL_Rect MyRect;
	SDL_Rect NMERect;

	p->s.GetCollisionRect(&p->s, &MyRect);
	count = p->s.ParentList->count;
	for (i = 0; i < count; i++)
	{
		Sprite *s;

		s = SpriteList_Get(p->s.ParentList, i);
		if (s != &p->s)
		{
			s->GetCollisionRect(s, &NMERect);

			if (isCollideRects(&MyRect, &NMERect))
			{
				if (s->ID == idPREMIOT)
				{
					Sprite_Kill(s); /* shots */
					if (shots == 1)
						shots = 2;
				}
				if (s->ID == idPREMIOP)
				{
					Sprite_Kill(s); /* points */
					points += 500;
				}
				if (s->ID == idPREMIOB)
				{
					Sprite_Kill(s); /* Bombs */
					if (bombs < 9)
						bombs = bombs + 1;
				}
				if (s->ID == idPREMIOV)
				{
					Sprite_Kill(s); /* lives */
					if (lives < 99)
						lives += 1;
				}
			}
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

static void Player_Move(Sprite *s)
{
	Player *p = (Player *)s;

#if 0
	if (Keys[SDLK_LEFT] && p->s.x > 0)
		p->s.x -= 1;
	else if (Keys[SDLK_RIGHT] && p->s.x < 448 - 16)
		p->s.x += 1;

	if (Keys[SDLK_UP] && p->s.y > 0)
		p->s.y -= 1;
	else if (Keys[SDLK_DOWN] && p->s.y < 480 - 16)
		p->s.y += 1;
#endif

	if (Keys[SDLK_LEFT] && p->s.x > 160)
		p->s.x -= 1;

	if (Keys[SDLK_RIGHT] && p->s.x < 480 - 16)
		p->s.x += 1;

	if (Keys[SDLK_UP] && p->s.y > 0)
		p->s.y -= 1;

	if (Keys[SDLK_DOWN] && p->s.y < 480 - 16)
		p->s.y += 1;

	if (Keys[SDLK_LALT] && p->BombCounter == 0 && bombs > 0)
	{
		size_t i, count;

		count = p->s.ParentList->count;
		for (i = 0; i < count; i++)
		{
			Sprite *s = SpriteList_Get(p->s.ParentList, i);
			if (s != &p->s)
			{
				if (s->ID == idBOSS1 || s->ID == idBOSS2 || s->ID == idBOSS3 || s->ID == idBOSS4 || s->ID == idBOSS5)
				{
					tbombs = true;
				} else
				{
					Sprite_Kill(s);
					if (s->ID == idFIGHTER || s->ID == idFIGHTER2 || s->ID == idSTEALTH || s->ID == idBOMBER)
						SpriteEngine_AddSprite(spriteengine, &Explosion_New(s->x, s->y)->s);
				}
			}
		}
		bombs -= 1;
		++p->BombCounter;
		p->ShootCounter = 0;
		startsound(SOUND_PEXPLODE);
	}

	if (Keys[SDLK_SPACE] && p->ShootCounter == 0)
	{
		if (shots == 1)
		{
			SpriteEngine_AddSprite(spriteengine, &Laser_New(p->s.x + 8, p->s.y - 8)->s);
			++p->ShootCounter;
		} else
		{
			SpriteEngine_AddSprite(spriteengine, &Laser_New(p->s.x + 3, p->s.y - 3)->s);
			SpriteEngine_AddSprite(spriteengine, &Laser_New(p->s.x + 12, p->s.y - 3)->s);
			++p->ShootCounter;
		}

		startsound(SOUND_LASER);
	}

	if (p->ShootCounter > 0)
	{
		++p->ShootCounter;
		if (p->ShootCounter == 40)
			p->ShootCounter = 0;
	}

	if (p->BombCounter > 0)
	{
		++p->BombCounter;
		if (p->BombCounter == 100)
			p->BombCounter = 0;
	}

	Player_DetectCollision(p);

	if (Inven)
	{
		++TInven;
		if (TInven == 200)
			Inven = false;
	}

}

/*** ---------------------------------------------------------------------- ***/

static Player *Player_New(void)
{
	Player *p;

	p = (Player *)calloc(1, sizeof(*p));
	if (p == NULL)
		return p;
	Sprite_Init(&p->s, NULL, 16, 16);
	p->s.Draw = Player_Draw;
	p->s.Move = Player_Move;
	p->s.ID = idPLAYER;
	p->ShootCounter = 0;
	p->BombCounter = 0;
	p->s.x = 320 - 8;
	p->s.y = 479 - 16;
	p->s.z = 100;
	p->s.SrcRect.x = 0;
	p->s.SrcRect.y = 24;
	return p;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static Star *Star_New(void)
{
	Star *s;

	s = (Star *)calloc(1, sizeof(*s));
	if (s == NULL)
		return s;
	return s;
}

/*** ---------------------------------------------------------------------- ***/

static void Star_Draw(Star *s)
{
	int i;
	bool mustlock;

	for (i = 0; i < 20; i++)
	{
		s->Wx[i] = StarWx[i];
		s->Wy[i] = StarWy[i];
		s->Gx[i] = StarGx[i];
		s->Gy[i] = StarGy[i];
		s->Bx[i] = StarBx[i];
		s->By[i] = StarBy[i];
	}

	s->Wc = SDL_MapRGBA(Background->format, 0xFF, 0xFF, 0xFF, 0xFF);
	s->Gc = SDL_MapRGBA(Background->format, 0x80, 0x80, 0x80, 0xFF);
	s->Bc = SDL_MapRGBA(Background->format, 0x00, 0x00, 0xFF, 0xFF);

	s->Wt = 1;
	s->Gt = 3;
	s->Bt = 2;
	s->Wtc = 0;
	s->Gtc = 0;
	s->Btc = 0;

    /* Lock the screen for direct access to the pixels */
	mustlock = SDL_MUSTLOCK(Background);
	if (mustlock)
	{
		if (SDL_LockSurface(Background) < 0)
		{
			/* fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError()); */
			return;
		}
	}

	for (i = 0; i < 20; i++)
	{
		putpixel(Background, s->Wx[i], s->Wy[i], s->Wc);
		putpixel(Background, s->Gx[i], s->Gy[i], s->Gc);
		putpixel(Background, s->Bx[i], s->By[i], s->Bc);
	}

    if (mustlock)
    {
        SDL_UnlockSurface(Background);
    }

	SDL_BlitSurface(Background, NULL, Screen, NULL);
}

/*** ---------------------------------------------------------------------- ***/

static void Star_Scroll(Star *s)
{
	int i;
	bool mustlock;

	mustlock = SDL_MUSTLOCK(Background);
	if (mustlock)
	{
		if (SDL_LockSurface(Background) < 0)
		{
			/* fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError()); */
			return;
		}
	}

	++s->Wtc;
	if (s->Wtc == s->Wt)
	{
		for (i = 0; i < 20; i++)
		{
			putpixel(Background, s->Wx[i], s->Wy[i], black);
			++s->Wy[i];
			if (s->Wy[i] == 480)
				s->Wy[i] = 0;
			putpixel(Background, s->Wx[i], s->Wy[i], s->Wc);
		}
		s->Wtc = 0;
	}

	++s->Gtc;
	if (s->Gtc == s->Gt)
	{
		for (i = 0; i < 20; i++)
		{
			putpixel(Background, s->Gx[i], s->Gy[i], black);
			++s->Gy[i];
			if (s->Gy[i] == 480)
				s->Gy[i] = 0;
			putpixel(Background, s->Gx[i], s->Gy[i], s->Gc);
		}
		s->Gtc = 0;
	}

	++s->Btc;
	if (s->Btc == s->Bt)
	{
		for (i = 0; i < 20; i++)
		{
			putpixel(Background, s->Bx[i], s->By[i], black);
			++s->By[i];
			if (s->By[i] == 480)
				s->By[i] = 0;
			putpixel(Background, s->Bx[i], s->By[i], s->Bc);
		}
		s->Btc = 0;
	}

	if (mustlock)
		SDL_UnlockSurface(Background);

	SDL_BlitSurface(Background, NULL, Screen, NULL);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static uint32_t TimeLeft(void)
{
	uint32_t now;

	now = SDL_GetTicks();
	if (next_time <= now)
	{
		next_time = now + TICK_INTERVAL;
		return 0;
	}

	return next_time - now;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void RestartMusic(void)
{
	if (music && Mix_PlayingMusic() == 0)
	{
		if (!nomusic)
			Mix_PlayMusic(music, 0);
	}
}

/*** ---------------------------------------------------------------------- ***/

static void LoadMusic(const char *Filename)
{
	music = Mix_LoadMUS(Filename);

	Mix_HookMusicFinished(RestartMusic);
	if (music == NULL)
	{
#if 0
		SDL_Quit();
		exit(EXIT_FAILURE);
#endif
	}
}

/*** ---------------------------------------------------------------------- ***/

static void StartMusic(void)
{
	if (music)
	{
		if (!nomusic)
		{
			Mix_VolumeMusic(32);
			Mix_PlayMusic(music, 0);
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

static void StopMusic(void)
{
	if (music)
	{
		Mix_HaltMusic();
	}
}

/*** ---------------------------------------------------------------------- ***/

static void ToggleMusic(void)
{
	nomusic = !nomusic;
	if (nomusic)
		StopMusic();
	else
		StartMusic();
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static bool Initializer(void)
{
	uint32_t TempFlag;
	int i;

	/* Set Hiscore */
	recorde = 0;

	/* Set Graphics */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return false;
	}

	SDL_WM_SetCaption("Sardonic", NULL);

	Screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
#if defined __TOS__ || defined(__atarist__)
		SDL_FULLSCREEN ||
#endif
		SDL_HWPALETTE);
	if (Screen == NULL)
	{
		fprintf(stderr, "Can't initialize screen:\n%s\n", SDL_GetError());
		return false;
	}

	Graphics = sdl_loadbmp("sprites" SLASH "sprites.bmp");
	if (Graphics == NULL)
	{
		fprintf(stderr, "Can't load sprites:\n%s\n", SDL_GetError());
		return false;
	}
	SDL_SetColorKey(Graphics, SDL_HWACCEL | SDL_RLEACCEL | SDL_SRCCOLORKEY, 0);

	Background = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_HWPALETTE, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, 0, 0, 0, 0);
	Background = sdl_display_surface(Background);
	if (Background == NULL)
	{
		fprintf(stderr, "Can't create background surface:\n%s\n", SDL_GetError());
		return false;
	}
	black = SDL_MapRGBA(Background->format, 0, 0, 0, 0xff);

	ecTitle = sdl_loadbmp("sprites" SLASH "title.bmp");
	if (ecTitle == NULL)
	{
		fprintf(stderr, "Can't load title:\n%s\n", SDL_GetError());
		return false;
	}

	ecPanel = sdl_loadbmp("sprites" SLASH "panel.bmp");
	if (ecPanel == NULL)
	{
		fprintf(stderr, "Can't load panel:\n%s\n", SDL_GetError());
		return false;
	}

	Chars15x9 = sdl_loadbmp("sprites" SLASH "font.bmp");
	if (Chars15x9 == NULL)
	{
		fprintf(stderr, "Can't load font:\n%s\n", SDL_GetError());
		return false;
	}

	SDL_ShowCursor(SDL_DISABLE);
	spriteengine = SpriteEngine_New(Screen);
	SpriteEngine_SetBackground(spriteengine, Background);
	stars = Star_New();

	/* Set Audio */
	TempFlag = SDL_INIT_AUDIO;
	if (SDL_Init(TempFlag) < 0)
	{
		fprintf(stderr, "Can't initialize audio:\n%s\n", SDL_GetError());
		return false;
	}

	if (Mix_OpenAudio(freq, AudioFormat, channels, 1024) < 0)
	{
		fprintf(stderr, "Can't open audio:\n%s\n", SDL_GetError());
		return false;
	}

	for (i = 0; i < NumberOfSounds; i++)
	{
		char filename[80];

		strcat(strcpy(filename, "sounds" SLASH), SoundFilenames[i]);
		Sounds[i] = Mix_LoadWAV(filename);
		if (Sounds[i] == NULL)
		{
			fprintf(stderr, "Can't load sound %s:\n%s\n", filename, SDL_GetError());
			return false;
		}
	}

	LoadMusic("music" SLASH "helico.xm");
	StartMusic();

	return true;
}

/*** ---------------------------------------------------------------------- ***/

static void WriteText_15x9(SDL_Surface *Surf, const char *txt, int x, int y, enum TextAlign Align)
{
	int StartX, i;
	SDL_Rect SrcRect;
	SDL_Rect DestRect;

	StartX = 0;
	SrcRect.y = 0;
	SrcRect.w = FONT_W;
	SrcRect.h = FONT_H;
	DestRect.y = y;

	switch (Align)
	{
	case alLeft:
		StartX = x;
		break;
	case alCenter:
		StartX = x - (strlen(txt) * FONT_W) / 2;
		break;
	case alRight:
		StartX = x - strlen(txt) * FONT_W + 1;
		break;
	}

	for (i = 0; txt[i] != '\0'; i++)
	{
		int pos = (int)(strchr(Chars, txt[i]) - Chars);
		SrcRect.x = pos * FONT_W;
		DestRect.x = StartX + i * FONT_W;
		SDL_BlitSurface(Chars15x9, &SrcRect, Surf, &DestRect);
	}
}

/*** ---------------------------------------------------------------------- ***/

static void WaitKey(enum State escstate, enum State timeoutstate)
{
	int counter;

	counter = 0;

	for (;;)
	{
		SDL_Delay(TimeLeft());

		while (SDL_PollEvent(&Event) > 0)
		{
			switch (Event.type)
			{
			case SDL_QUIT:
				state = eGoout;
				return;

			case SDL_KEYDOWN:
				switch (Event.key.keysym.sym)
				{
				case SDLK_SPACE:
					state = eGetReady;
					return;
				case SDLK_ESCAPE:
					state = escstate;
					return;
				case SDLK_m:
					ToggleMusic();
					break;
				default:
					break;
				}
				break;
			}
		}

		++counter;
		if (counter == 3000)
		{
			state = timeoutstate;
			return;
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

static void TitlePage(void)
{
	SDL_Rect Src;
	SDL_Rect Dest;

	SDL_FillRect(Screen, NULL, black);
	SDL_UpdateRect(Screen, 0, 0, 0, 0);
	SDL_FillRect(Background, NULL, black);
	SDL_UpdateRect(Background, 0, 0, 0, 0);

	/* Logo */
	Src.w = 380;
	Src.h = 78;
	Src.x = 0;
	Src.y = 0;
	Dest.x = 130;
	Dest.y = 30;
	SDL_BlitSurface(ecTitle, &Src, Screen, &Dest);

	/* Controls */
	WriteText_15x9(Screen, "cursors: directions", 320, 150, alCenter);
	WriteText_15x9(Screen, "space: fire", 320, 170, alCenter);
	WriteText_15x9(Screen, "alt: bomb", 320, 190, alCenter);
	WriteText_15x9(Screen, "fire to start game", 320, 250, alCenter);
	WriteText_15x9(Screen, "escape to quit", 320, 270, alCenter);

	/* Credits */
	WriteText_15x9(Screen, "linux port by thorsten otto", 320, 330, alCenter);
	WriteText_15x9(Screen, "original code and graphics by madaxe", 320, 350, alCenter);
	WriteText_15x9(Screen, "music by fred", 320, 370, alCenter);
	WriteText_15x9(Screen, "copyright 2020 penisoft", 320, 410, alCenter);

	SDL_UpdateRect(Screen, 0, 0, 0, 0);

	WaitKey(eGoout, eInstructions);
}

/*** ---------------------------------------------------------------------- ***/

static void InstructionsPage(void)
{
	SDL_Rect Src;
	SDL_Rect Dest;

	SDL_FillRect(Screen, NULL, black);
	SDL_UpdateRect(Screen, 0, 0, 0, 0);
	SDL_FillRect(Background, NULL, black);
	SDL_UpdateRect(Background, 0, 0, 0, 0);

	/* Logo */
	Src.w = 380;
	Src.h = 78;
	Src.x = 0;
	Src.y = 0;
	Dest.x = 130;
	Dest.y = 30;
	SDL_BlitSurface(ecTitle, &Src, Screen, &Dest);

	/* Fighter I */
	Src.w = 23;
	Src.h = 16;
	Src.x = 24;
	Src.y = 0;
	Dest.x = 130;
	Dest.y = 130;
	SDL_BlitSurface(Graphics, &Src, Screen, &Dest);

	/* Fighter II */
	Src.w = 23;
	Src.h = 16;
	Src.x = 47;
	Src.y = 0;
	Dest.x = 130;
	Dest.y = 170;
	SDL_BlitSurface(Graphics, &Src, Screen, &Dest);

	/* Stealth */
	Src.w = 15;
	Src.h = 24;
	Src.x = 70;
	Src.y = 0;
	Dest.x = 134;
	Dest.y = 210;
	SDL_BlitSurface(Graphics, &Src, Screen, &Dest);

	/* Bomber */
	Src.w = 24;
	Src.h = 24;
	Src.x = 0;
	Src.y = 0;
	Dest.x = 130;
	Dest.y = 250;
	SDL_BlitSurface(Graphics, &Src, Screen, &Dest);

	WriteText_15x9(Screen, "fighter i  : 10 points", 180, 134, alLeft);
	WriteText_15x9(Screen, "fighter ii : 20 points", 180, 174, alLeft);
	WriteText_15x9(Screen, "stealth    : 30 points", 180, 218, alLeft);
	WriteText_15x9(Screen, "bomber	: 50 points", 180, 258, alLeft);

	/* Shots */
	Src.w = 12;
	Src.h = 12;
	Src.x = 42;
	Src.y = 63;
	Dest.x = 225;
	Dest.y = 310;
	SDL_BlitSurface(Graphics, &Src, Screen, &Dest);

	/* Points */
	Src.w = 12;
	Src.h = 12;
	Src.x = 66;
	Src.y = 63;
	Dest.x = 225;
	Dest.y = 340;
	SDL_BlitSurface(Graphics, &Src, Screen, &Dest);

	/* Bombs */
	Src.w = 12;
	Src.h = 12;
	Src.x = 54;
	Src.y = 63;
	Dest.x = 225;
	Dest.y = 370;
	SDL_BlitSurface(Graphics, &Src, Screen, &Dest);

	/* Lives */
	Src.w = 12;
	Src.h = 12;
	Src.x = 30;
	Src.y = 63;
	Dest.x = 225;
	Dest.y = 400;
	SDL_BlitSurface(Graphics, &Src, Screen, &Dest);

	WriteText_15x9(Screen, "extra fire", 265, 311, alLeft);
	WriteText_15x9(Screen, "extra points", 265, 341, alLeft);
	WriteText_15x9(Screen, "extra bomb", 265, 371, alLeft);
	WriteText_15x9(Screen, "extra live", 265, 401, alLeft);

	SDL_UpdateRect(Screen, 0, 0, 0, 0);

	WaitKey(eTitle, eHiscore);
}

/*** ---------------------------------------------------------------------- ***/

static void Hiscore(void)
{
	SDL_Rect Src;
	SDL_Rect Dest;
	char buf[30];

	SDL_FillRect(Screen, NULL, black);
	SDL_UpdateRect(Screen, 0, 0, 0, 0);
	SDL_FillRect(Background, NULL, black);
	SDL_UpdateRect(Background, 0, 0, 0, 0);

	/* Logo */
	Src.w = 380;
	Src.h = 78;
	Src.x = 0;
	Src.y = 0;
	Dest.x = 130;
	Dest.y = 30;
	SDL_BlitSurface(ecTitle, &Src, Screen, &Dest);

	/* Hiscore */
	WriteText_15x9(Screen, "hiscore of the day", 320, 220, alCenter);
	sprintf(buf, "%06ld", recorde);
	WriteText_15x9(Screen, buf, 320, 240, alCenter);

	SDL_UpdateRect(Screen, 0, 0, 0, 0);

	WaitKey(eTitle, eTitle);
}

/*** ---------------------------------------------------------------------- ***/

static void GetReady(void)
{
	SDL_Rect Src;
	SDL_Rect Dest;

	SpriteEngine_SetBackground(spriteengine, Background);
	SDL_FillRect(Background, NULL, black);
	SDL_UpdateRect(Background, 0, 0, 0, 0);

	Src.w = 160;
	Src.h = 480;
	Src.x = 0;
	Src.y = 0;

	Dest.x = 0;
	Dest.y = 0;
	SDL_BlitSurface(ecPanel, &Src, Background, &Dest);

	Dest.x = 480;
	Dest.y = 0;
	SDL_BlitSurface(ecPanel, &Src, Background, &Dest);

	SDL_FillRect(Screen, NULL, black);
	SDL_UpdateRect(Screen, 0, 0, 0, 0);

	shots = 1;
	bombs = 5;
	lives = 5;
	points = 0;
	level = 1;

	counter = 0;
	EnemyRate = 0;
	tbombs = false;
	Inven = false;

	state = eGame;
}

/*** ---------------------------------------------------------------------- ***/

static void Panel(void)
{
	char buf[40];

	WriteText_15x9(Screen, "points", 35, 120, alLeft);
	sprintf(buf, "%06ld", points);
	WriteText_15x9(Screen, buf, 35, 140, alLeft);
	WriteText_15x9(Screen, "level", 43, 240, alLeft);
	sprintf(buf, "%02d", level);
	WriteText_15x9(Screen, buf, 65, 260, alLeft);

	WriteText_15x9(Screen, "lives", 523, 120, alLeft);
	sprintf(buf, "%02d", lives);
	WriteText_15x9(Screen, buf, 545,140, alLeft);
	WriteText_15x9(Screen, "bombs", 523, 240, alLeft);
	sprintf(buf, "%02d", bombs);
	WriteText_15x9(Screen, buf, 545, 260, alLeft);
}

/*** ---------------------------------------------------------------------- ***/

static void GameFinish(const char *msg, int timeout)
{
	int tempo;

	if (points > recorde)
		recorde = points;

	tempo = 0;

	do
	{
		/* update changes on screen */
		Star_Scroll(stars);
		WriteText_15x9(Screen, msg, 320, 235, alCenter);
		Panel();
		SDL_UpdateRect(Screen, 0, 0, 0, 0);
		SDL_Delay(TimeLeft());

		while (SDL_PollEvent(&Event) > 0)
		{
			switch (Event.type)
			{
			case SDL_QUIT:
				state = eGoout;
				return;

			case SDL_KEYDOWN:
				switch (Event.key.keysym.sym)
				{
				case SDLK_SPACE:
				case SDLK_ESCAPE:
					state = eTitle;
					break;
				case SDLK_m:
					ToggleMusic();
					break;
				default:
					break;
				}
				break;
			}
		}

		tempo = tempo + 1;
	} while (tempo != timeout && (state == eGameOver || state == eEndGame));

	state = eTitle;
}

/*** ---------------------------------------------------------------------- ***/

static void GameOver(void)
{
	SpriteEngine_Clear(spriteengine);
	SDL_UpdateRect(Screen, 0, 0, 0, 0);
	GameFinish("game over", 400);
}

/*** ---------------------------------------------------------------------- ***/

static void EndGame(void)
{
	GameFinish("well done !!", 1000);
}

/*** ---------------------------------------------------------------------- ***/

static void Game(void)
{
	SpriteEngine_Clear(spriteengine);
	SDL_FillRect(Screen, NULL, black);
	SDL_UpdateRect(Screen, 0, 0, 0, 0);
	Star_Draw(stars);
	SpriteEngine_AddSprite(spriteengine, &Player_New()->s);

	do
	{
		while (SDL_PollEvent(&Event) > 0)
		{
			switch (Event.type)
			{
			case SDL_QUIT:
				state = eGoout;
				break;

			case SDL_KEYDOWN:
				switch (Event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					state = eGoout;
					break;
				case SDLK_m:
					ToggleMusic();
					break;
				default:
					break;
				}
				break;
			}
		}

		Keys = SDL_GetKeyState(NULL);

		/* remove all sprites from the screen and move all sprites */
		SpriteEngine_Move(spriteengine);

		/* Changing background */
		Star_Scroll(stars);

		if (state == eGame)
		{
			++EnemyRate;
			if (EnemyRate == 90)
			{
				if (LEnemy[counter] != 0)
				{
					if (LEnemy[counter] == 5 || LEnemy[counter] == 6 || LEnemy[counter] ==7 || LEnemy[counter] == 8 || LEnemy[counter] == 9)
						state = eBoss;
					SpriteEngine_AddSprite(spriteengine, &Enemy_New()->s);
				}
				EnemyRate = 0;
				counter = counter + 1;
			}
		}

		Panel();

		/* redraw all sprites to the screen in new positions */
		SpriteEngine_Draw(spriteengine);

		/* update changes on screen */
		SDL_UpdateRect(Screen, 0, 0, 0, 0);
		SDL_Delay(TimeLeft());

	} while (state != eGoout && state != eGameOver && state != eEndGame);
}

/*** ---------------------------------------------------------------------- ***/

/* we don't link to SDL_main */
#undef main
#if defined(__MACOS__) || defined(__MACOSX__)
/* on macOS, the systems entry point is in SDLMain.M */
#define main SDL_main
#endif

int main(void)
{
	srand(time(NULL));
	if (!Initializer())
	{
		SDL_Quit();
		return EXIT_FAILURE;
	}

	state = eTitle;

	do
	{
		switch (state)
		{
		case eTitle:
			TitlePage();
			break;
		case eInstructions:
			InstructionsPage();
			break;
		case eHiscore:
			Hiscore();
			break;
		case eGetReady:
			GetReady();
			break;
		case eGame:
		case eBoss:
			Game();
			break;
		case eGameOver:
			GameOver();
			break;
		case eEndGame:
			EndGame();
			break;
		case eGoout:
			break;
		}
	} while (state != eGoout);

	SpriteEngine_Delete(spriteengine);
	SDL_FreeSurface(Graphics);
	StopMusic();
	Mix_FreeMusic(music);
	music = NULL;
	SDL_Quit();

	return EXIT_SUCCESS;
}
