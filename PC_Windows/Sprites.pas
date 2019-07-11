unit Sprites;

{
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
}

{************************************************************************
 * Sprites.pas for JEDI-SDL                                             *
 * Written by Róbert Kisnémeth                                          *
 * Version 1.02 (02 oct 2001)                                           *
 * E-mail: mikrobi@freemail.hu                                          *
 * Please send me your opinions, ideas, bugreports, etc.                *
 * History:                                                             *
 * 08 aug  2001 RK: v1.0  Initial version                               *
 * 10 sept 2001 RK: v1.01 Added "SDL_DisplayFormat" for fast blitting   *
 * 02 oct  2001 RK: v1.02 Added SDL_Image, so now can load PNG, PCX...  *
 ************************************************************************}

Interface

Uses
  Classes,
  SysUtils,
  SDL_Image,
  SDL;

type
 TSpriteList = class;

 TSprite = class
   ID: byte; { we can easily determine the sprite's type }
   ParentList: TSpriteList;
   PrevRect: TSDL_Rect; { rectangle of previous position in the screen }
   Flags: cardinal; { for SDL_BlitSurface }
   isDead: boolean; { need to destroy ? }
   SrcRect: TSDL_Rect; { source rectangle what contains the image-data }
   AnimPhase: integer; { which image we draw }
   x, y, z: integer; { x, y coords for screen, z for sorting }
   w, h: integer; { Width & Height of sprite }
   Surface, Background, Image: PSDL_Surface; { Screen, Background and sprite images }
   constructor Create(const _Image: string; Width, Height: integer);
   procedure GetCollisionRect(Rect: PSDL_Rect); virtual;
   function Remove: integer; { remove sprite from screen, result=-2 then background surface is lost }
   procedure Draw; virtual; { draw sprite on screen }
   procedure Move; virtual; { move a sprite }
   procedure Kill; { we will need to destroy this sprite }
   procedure Free; virtual; { destroy sprite }
 end;

 TSpriteList = class(TList)
  protected
   function Get(Index: Integer): TSprite;
   procedure Put(Index: Integer; Item: TSprite);
  public
   property Items[Index: Integer]: TSprite read Get write Put; default;
  end;

  TSpriteEngine = class
   private
    NeedSort: boolean; { do we need to resort sprites by Z? }
    FSurface, FBackground: PSDL_Surface; { screen and background surface }
    procedure SetSurface(_Surface: PSDL_Surface);
    procedure SetBackground(_Surface: PSDL_Surface);
   public
    Sprites: TSpriteList; { all sprites }
    NeedRedrawBackground: boolean; { background surface is lost? }
    procedure Clear; { destroy all sprites from list }
    procedure SortSprites; { that is }
    procedure AddSprite(Item: TSprite); { add a sprite to list }
    procedure RemoveSprite(Item: TSprite); { remove a sprite from list and from memory }
    procedure Free;
    procedure Move; { move all sprites in the list }
    procedure Draw; { draw all sprites in the list }
    property Surface: PSDL_Surface read FSurface write SetSurface; { screen surface }
    property BackgroundSurface: PSDL_Surface read FBackground write SetBackground; { background surface }
    constructor Create(_Surface: PSDL_Surface);
  end;

function isCollideRects(Rect1, Rect2: PSDL_Rect): boolean;

implementation

{ Create a sprite. Transparent color is $00ff00ff }
constructor TSprite.Create(const _Image: string; Width, Height: integer);
begin
 inherited Create;
 ID:=0;
 if fileexists(_Image) then begin
  Image:=IMG_Load(PChar(_Image));
  Image:=SDL_DisplayFormat(Image);
  Flags:=SDL_SRCCOLORKEY or SDL_RLEACCEL or SDL_HWACCEL;
  SDL_SetColorKey(Image, Flags, SDL_MapRGB(Image.format,255,0,255));
 end; 
 AnimPhase:=0;
 isDead:=false;
 x:=0;
 y:=0;
 z:=0;
 w:=Width;
 h:=Height;
 SrcRect.y:=0;
 SrcRect.w:=w;
 SrcRect.h:=h;
end;

{ we can separately determine the collision rectangle }
procedure TSprite.GetCollisionRect(Rect: PSDL_Rect);
begin
 Rect.x:=x;
 Rect.y:=y;
 Rect.w:=w;
 Rect.h:=h;
end;

procedure TSprite.Free;
begin
 if Image<>nil then SDL_FreeSurface(Image);
 inherited Free;
end;

procedure TSprite.Move;
begin
end;

procedure TSprite.Kill;
begin
 isDead:=true;
end;

function TSprite.Remove: integer;
begin
 PrevRect.w:=w;
 PrevRect.h:=h;
 Result:=SDL_BlitSurface(Background, @PrevRect, Surface, @PrevRect);
end;

procedure TSprite.Draw;
var
 DestRect: TSDL_Rect;
begin
  SrcRect.x:=AnimPhase*w; { which animation phase need to draw? }
  DestRect.x:=x; { set screen positions }
  DestRect.y:=y;
  SDL_BlitSurface(Image, @SrcRect, Surface, @DestRect);
  PrevRect:=DestRect;
end;

{ - TSpriteList ---------------------------------------------------------- }

function TSpriteList.Get(Index: Integer): TSprite;
begin
 Result:=inherited Get(Index);
end;

procedure TSpriteList.Put(Index: Integer; Item: TSprite);
begin
 inherited Put(Index, Item);
end;

{ - TSpriteEngine -------------------------------------------------------- }

constructor TSpriteEngine.Create(_Surface: PSDL_Surface);
begin
 inherited Create;
 NeedSort:=false;
 Sprites:=TSpriteList.Create;
 FSurface:=_Surface;
 NeedRedrawBackground:=false;
end;

procedure TSpriteEngine.Free;
begin
 Clear;
 Sprites.Free;
 inherited Free;
end;

procedure TSpriteEngine.AddSprite(Item: TSprite);
begin
 Item.Surface:=Surface; { setting new sprite's surfaces }
 Item.Background:=FBackground;
 Item.ParentList:=Sprites;
 Sprites.Add(Item);
 NeedSort:=true;
end;

procedure TSpriteEngine.RemoveSprite(Item: TSprite);
begin
 Sprites.Remove(Item);
end;

procedure TSpriteEngine.Move;
var
 i, max: integer;
 TempSpr: TSprite;
begin
 if Sprites.Count>0 then begin
  NeedRedrawBackground:=false;
  i:=0; max:=Sprites.Count;
  repeat
   if Sprites[i].Remove=-2 then NeedRedrawBackground:=true;
   Sprites[i].Move;
   if Sprites[i].isDead then begin
    TempSpr:=Sprites[i];
    TempSpr.Free;
    Sprites.Delete(i);
    dec(Max);
   end else inc(i);
  until i>=Max;
 end;
 if NeedSort then begin
  SortSprites;
  NeedSort:=false;
 end; 
end;

procedure TSpriteEngine.Draw;
var
 i: integer;
begin
 if Sprites.Count>0 then begin
  for i:=0 to Sprites.Count-1 do
   Sprites[i].Draw;
 end;
end;

{ set all sprites' Surface to _Surface }
procedure TSpriteEngine.SetSurface(_Surface: PSDL_Surface);
var
 i: integer;
begin
 FSurface:=_Surface; 
 if Sprites.Count>0 then
  for i:=0 to Sprites.Count-1 do
   Sprites[i].Surface:=_Surface;
end;

{ set all sprites' Background surface to _Surface }
procedure TSpriteEngine.SetBackground(_Surface: PSDL_Surface);
var
 i: integer;
begin
 FBackground:=_Surface;
 if Sprites.Count>0 then
  for i:=0 to Sprites.Count-1 do
   Sprites[i].Background:=_Surface;
end;

procedure TSpriteEngine.Clear;
var
 TempSpr: TSprite;
begin
 while Sprites.Count>0 do begin { destroy all sprites }
  TempSpr:=Sprites[0];
  TempSpr.Free;
  Sprites.Delete(0);
 end;
 Sprites.Clear;
end;

procedure TSpriteEngine.SortSprites;

 function CompareZ(Item1, Item2: TSprite): Integer;
 begin
  if Item1.z<Item2.z then Result:=-1 else
  if Item1.z>Item2.z then Result:=1 else
  Result:=0;
 end;

begin
 Sprites.Sort(@CompareZ);
end;

function isCollideRects(Rect1, Rect2: PSDL_Rect): boolean;
begin
 Result:=true;
 if (Rect1.x+Rect1.w<Rect2.x) or (Rect1.x>Rect2.x+Rect2.w) or (Rect1.y+Rect1.h<Rect2.y) or (Rect1.y>Rect2.y+Rect2.h) then Result:=false;
end;

end.
