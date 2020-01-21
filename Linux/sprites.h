#ifndef SPRITES_H
#define SPRITES_H

#include <stdint.h>
#include <stdbool.h>

#include <SDL/SDL.h>


/*
    Copyright (C) 2001  Róbert Kisnémeth

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*************************************************************************
  * Sprites.pas for JEDI-SDL                                             *
  * Written by Róbert Kisnémeth                                          *
  * Version 1.02 (02 oct 2001)                                           *
  * E-mail: mikrobi@freemail.hu                                          *
  * Please send me your opinions, ideas, bugreports, etc.                *
  * History:                                                             *
  * 08 aug  2001 RK: v1.0  Initial version                               *
  * 10 sept 2001 RK: v1.01 Added "SDL_DisplayFormat" for fast blitting   *
  * 02 oct  2001 RK: v1.02 Added SDL_Image, so now can load PNG, PCX...  *
  *************************************************************************/


typedef struct _SpriteList SpriteList;
typedef struct _Sprite Sprite;

struct _Sprite {
	uint8_t ID;					/* we can easily determine the sprite's type */
	SpriteList *ParentList;
	SDL_Rect PrevRect;			/* rectangle of previous position in the screen */
	unsigned int Flags;			/* for SDL_BlitSurface */
	bool isDead;				/* need to destroy ? */
	SDL_Rect SrcRect;			/* source rectangle what contains the image-data */
	int AnimPhase;				/* which image we draw */
	int x, y, z;				/* x, y coords for screen, z for sorting */
	int w, h;					/* Width & Height of sprite */
	SDL_Surface *Surface;		/* screen */
	SDL_Surface *Background;	/* background */
	SDL_Surface *Image;			/* sprite images */

	/* move a sprite */
	void (*Move)(Sprite *s);

	/* draw sprite on screen */
	void (*Draw)(Sprite *s);

	void (*Delete)(Sprite *s);

	void (*GetCollisionRect)(Sprite *s, SDL_Rect *Rect);
};


/* create sprite */
Sprite *Sprite_New(const char *image, int width, int height);
void Sprite_Init(Sprite *s, const char *image, int width, int height);

/* destroy sprite */
void Sprite_Delete(Sprite *s);
void Sprite_Free(Sprite *s);

/* remove sprite from screen, result=-2 then background surface is lost */
int Sprite_Remove(Sprite *s);

/* we will need to destroy this sprite */
void Sprite_Kill(Sprite *s);


struct _SpriteList {
	size_t count;
	size_t size;
	Sprite **items;
};

SpriteList *SpriteList_New(void);
void SpriteList_Delete(SpriteList *l);
Sprite *SpriteList_Get(SpriteList *l, int Index);
#define SpriteList_Get(l, Index) ((l)->items[Index])
void SpriteList_Put(SpriteList *l, int Index, Sprite *s);
bool SpriteList_Add(SpriteList *l, Sprite *s);
void SpriteList_Remove(SpriteList *l, int Index);


typedef struct _SpriteEngine SpriteEngine;
struct _SpriteEngine {
	bool NeedSort;				/* do we need to resort sprites by Z? */
	SDL_Surface *Surface;		/* screen */
	SDL_Surface *Background;	/* background surface */
	SpriteList *Sprites;		/* all sprites */
	bool NeedRedrawBackground; 	/* background surface is lost? */
};

SpriteEngine *SpriteEngine_New(SDL_Surface *surface);
void SpriteEngine_Delete(SpriteEngine *e);

/* destroy all sprites from list */
void SpriteEngine_Clear(SpriteEngine *e);

/* that is */
void SpriteEngine_SortSprites(SpriteEngine *e);

/* add a sprite to list */
bool SpriteEngine_AddSprite(SpriteEngine *e, Sprite *Item);

/* remove a sprite from list and from memory */
void SpriteEngine_RemoveSprite(SpriteEngine *e, Sprite *Item);

/* move all sprites in the list */
void SpriteEngine_Move(SpriteEngine *e);

/* draw all sprites in the list */
void SpriteEngine_Draw(SpriteEngine *e);

/* set all sprites Surface to surface */
void SpriteEngine_SetSurface(SpriteEngine *e, SDL_Surface *surface);

/* set all sprites Background surface to surface */
void SpriteEngine_SetBackground(SpriteEngine *e, SDL_Surface *surface);

bool isCollideRects(const SDL_Rect *Rect1, const SDL_Rect *Rect2);

#endif /* SPRITES_H */
