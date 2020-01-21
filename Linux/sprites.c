#include "sprites.h"
#include "loadbmp.h"

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void Sprite_Move(Sprite *s)
{
	(void)s;
}

/*** ---------------------------------------------------------------------- ***/

static void Sprite_Draw(Sprite *s)
{
	SDL_Rect DestRect;

	s->SrcRect.x = s->AnimPhase * s->w; /* which animation phase need to draw? */
	DestRect.x = s->x; /* set screen positions */
	DestRect.y = s->y;
	DestRect.w = s->w;
	DestRect.h = s->h;
	SDL_BlitSurface(s->Image, &s->SrcRect, s->Surface, &DestRect);
	s->PrevRect = DestRect;
}

/*** ---------------------------------------------------------------------- ***/

/* we can separately determine the collision rectangle */
static void Sprite_GetCollisionRect(Sprite *s, SDL_Rect *Rect)
{
	Rect->x = s->x;
	Rect->y = s->y;
	Rect->w = s->w;
	Rect->h = s->h;
}

/*** ---------------------------------------------------------------------- ***/

/* Create a sprite. Transparent color is $00ff00ff */

void Sprite_Init(Sprite *s, const char *image, int width, int height)
{
	s->ID = 0;
	s->ParentList = NULL;
	s->Flags = 0;
	s->isDead = false;
	s->AnimPhase = 0;
	s->x = 0;
	s->y = 0;
	s->z = 0;
	s->w = width;
	s->h = height;
	s->SrcRect.x = 0;
	s->SrcRect.y = 0;
	s->SrcRect.w = s->w;
	s->SrcRect.h = s->h;
	s->PrevRect = s->SrcRect;
	s->Surface = NULL;
	s->Background = NULL;
	s->Image = NULL;

	s->Move = Sprite_Move;
	s->Draw = Sprite_Draw;
	s->Delete = Sprite_Delete;
	s->GetCollisionRect = Sprite_GetCollisionRect;

	if (image && *image)
	{
		s->Image = sdl_loadbmp(image);
		if (s->Image)
		{
			s->Flags = SDL_SRCCOLORKEY | SDL_RLEACCEL | SDL_HWACCEL;
			SDL_SetColorKey(s->Image, s->Flags, SDL_MapRGB(s->Image->format, 255, 0, 255));
		}
	}
}

Sprite *Sprite_New(const char *image, int width, int height)
{
	Sprite *s;

	s = (Sprite *)calloc(1, sizeof(*s));
	if (s == NULL)
		return s;
	Sprite_Init(s, image, width, height);
	return s;
}

/*** ---------------------------------------------------------------------- ***/

/* destroy sprite */
void Sprite_Free(Sprite *s)
{
	if (s == NULL)
		return;
	if (s->Image)
		SDL_FreeSurface(s->Image);
}

void Sprite_Delete(Sprite *s)
{
	Sprite_Free(s);
	free(s);
}

/*** ---------------------------------------------------------------------- ***/

/* we will need to destroy this sprite */
void Sprite_Kill(Sprite *s)
{
	s->isDead = true;
}

/*** ---------------------------------------------------------------------- ***/

/* remove sprite from screen, result=-2 then background surface is lost */
int Sprite_Remove(Sprite *s)
{
	s->PrevRect.w = s->w;
	s->PrevRect.h = s->h;
	return SDL_BlitSurface(s->Background, &s->PrevRect, s->Surface, &s->PrevRect);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

SpriteList *SpriteList_New(void)
{
	SpriteList *l;

	l = (SpriteList *)calloc(1, sizeof(*l));
	if (l == NULL)
		return l;
	l->count = 0;
	l->size = 0;
	l->items = NULL;

	return l;
}

/*** ---------------------------------------------------------------------- ***/

void SpriteList_Delete(SpriteList *l)
{
	if (l == NULL)
		return;
	free(l->items);
	free(l);
}

/*** ---------------------------------------------------------------------- ***/

void SpriteList_Put(SpriteList *l, int Index, Sprite *s)
{
	l->items[Index] = s;
}

/*** ---------------------------------------------------------------------- ***/

bool SpriteList_Add(SpriteList *l, Sprite *s)
{
	size_t i;

	i = l->count++;
	if (i >= l->size)
	{
		Sprite **newitems = (Sprite **)realloc(l->items, l->count * sizeof(Sprite *));
		if (newitems == NULL)
		{
			--l->count;
			return false;
		}
		l->items = newitems;
		l->size = l->count;
	}
	l->items[i] = s;
	return true;
}

/*** ---------------------------------------------------------------------- ***/

void SpriteList_Remove(SpriteList *l, int Index)
{
	size_t i = Index;

	if (i >= l->count)
		return;
	--l->count;
	if (i < l->count)
		memmove(&l->items[i], &l->items[i + 1], (l->count - i) * sizeof(Sprite *));
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

SpriteEngine *SpriteEngine_New(SDL_Surface *surface)
{
	SpriteEngine *e;

	e = (SpriteEngine *)calloc(1, sizeof(*e));
	if (e == NULL)
		return NULL;
	e->NeedSort = false;
	e->Sprites = SpriteList_New();
	e->Surface = surface;
	e->Background = NULL;
	e->NeedRedrawBackground = false;
	return e;
}

/*** ---------------------------------------------------------------------- ***/

void SpriteEngine_Delete(SpriteEngine *e)
{
	if (e == NULL)
		return;
	SpriteList_Delete(e->Sprites);
	free(e);
}

/*** ---------------------------------------------------------------------- ***/

/* add a sprite to list */
bool SpriteEngine_AddSprite(SpriteEngine *e, Sprite *Item)
{
	if (Item == NULL)
		return false;
	if (SpriteList_Add(e->Sprites, Item) == false)
		return false;
	Item->Surface = e->Surface; /* setting new sprite's surfaces */
	Item->Background = e->Background;
	Item->ParentList = e->Sprites;
	e->NeedSort = true;
	return true;
}

/*** ---------------------------------------------------------------------- ***/

/* move all sprites in the list */
void SpriteEngine_Move(SpriteEngine *e)
{
	size_t i, max;
	Sprite *TempSpr;

	if (e->Sprites->count > 0)
	{
		e->NeedRedrawBackground = false;
		i = 0;
		max = e->Sprites->count;
		do
		{
			Sprite *s = SpriteList_Get(e->Sprites, i);

			if (Sprite_Remove(s) == -2)
				e->NeedRedrawBackground = true;
			s->Move(s);
			if (s->isDead)
			{
				TempSpr = s;
				s->Delete(TempSpr);
				SpriteList_Remove(e->Sprites, i);
				--max;
			} else
			{
				++i;
			}
		} while (i < max);
	}
	if (e->NeedSort)
	{
		SpriteEngine_SortSprites(e);
		e->NeedSort = false;
	}
}

/*** ---------------------------------------------------------------------- ***/

static int compareZ(const void *item1, const void *item2)
{
	const Sprite *s1 = *((const Sprite *const *)item1);
	const Sprite *s2 = *((const Sprite *const *)item2);
	if (s1->z < s2->z)
		return -1;
	if (s1->z > s2->z)
		return 1;
	return 0;
}

void SpriteEngine_SortSprites(SpriteEngine *e)
{
	qsort(e->Sprites->items, e->Sprites->count, sizeof(Sprite *), compareZ);
}

/*** ---------------------------------------------------------------------- ***/

/* draw all sprites in the list */
void SpriteEngine_Draw(SpriteEngine *e)
{
	size_t i, count;
	Sprite *s;

	count = e->Sprites->count;
	for (i = 0; i < count; i++)
	{
		s = SpriteList_Get(e->Sprites, i);
		s->Draw(s);
	}
}

/*** ---------------------------------------------------------------------- ***/

/* set all sprites' Surface to _Surface */
void SpriteEngine_SetSurface(SpriteEngine *e, SDL_Surface *surface)
{
	size_t i, count;
	Sprite *s;

	e->Surface = surface;
	count = e->Sprites->count;
	for (i = 0; i < count; i++)
	{
		s = SpriteList_Get(e->Sprites, i);
		s->Surface = surface;
	}
}

/*** ---------------------------------------------------------------------- ***/

/* set all sprites' Background surface to _Surface */
void SpriteEngine_SetBackground(SpriteEngine *e, SDL_Surface *surface)
{
	size_t i, count;
	Sprite *s;

	e->Background = surface;
	count = e->Sprites->count;
	for (i = 0; i < count; i++)
	{
		s = SpriteList_Get(e->Sprites, i);
		s->Background = surface;
	}
}

/*** ---------------------------------------------------------------------- ***/

/* destroy all sprites from list */
void SpriteEngine_Clear(SpriteEngine *e)
{
	size_t i, count;
	Sprite *s;

	count = e->Sprites->count;
	for (i = 0; i < count; i++)
	{
		s = SpriteList_Get(e->Sprites, i);
		s->Delete(s);
	}
	e->Sprites->count = 0;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

bool isCollideRects(const SDL_Rect *Rect1, const SDL_Rect *Rect2)
{
	if (Rect1->x + Rect1->w <= Rect2->x ||
		Rect1->x >= Rect2->x + Rect2->w ||
		Rect1->y + Rect1->h <= Rect2->y ||
		Rect1->y >= Rect2->y + Rect2->h)
		return false;
	return true;
}
