program Sardonic;

uses
  SysUtils,
  Classes,
  Logger,
  SDL,
  SDL_Image,
  Sprites,
  SDL_Mixer,
  SDLUtils;

const
  TICK_INTERVAL = trunc(1000 / 120);
  idPLAYER=0;
  idLASER=1;
  idFIGHTER=2;
  idFIGHTER2=3;
  idSTEALTH=4;
  idBOMBER=5;
  idLASERINI=6;
  idPREMIOT=7;
  idPREMIOP=8;
  idPREMIOB=9;
  idPREMIOV=10;
  idBOSS1=11;
  idBOSS2=12;
  idBOSS3=13;
  idBOSS4=14;
  idBOSS5=15;
  idEXPLOSION=16;
  Chars = 'abcdefghijklmnopqrstuvwxyz0123456789.:! ';
  LEnemy:array [1..500] of byte = (0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
{025}                              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
{050}                              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
{075}                              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,5,
{100}                              0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
{125}                              2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
{150}                              2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
{175}                              2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,6,
{200}                              0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
{225}                              3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
{250}                              3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
{275}                              3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,7,
{300}                              0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
{325}                              4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
{350}                              4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
{375}                              4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,8,
{400}                              0,0,0,1,1,4,3,2,4,3,4,4,2,3,1,4,1,3,1,1,4,2,2,2,4,
{425}                              2,1,1,3,4,3,3,3,4,3,2,2,1,2,1,3,1,2,1,4,4,3,3,4,4,
{450}                              3,3,4,4,3,3,4,4,3,2,2,3,2,2,3,4,4,4,3,3,3,4,4,4,3,
{475}                              3,3,4,4,4,3,3,3,2,1,2,1,3,4,4,4,4,4,3,4,0,0,0,0,9);


  NumberOfSounds = 3;

  StarWx:array[0..19] of integer=(160,261,182,407,212,314,444,349,225,376,323,476,348,249,215,251,184,299,181,277);
  StarWy:array[0..19] of integer=(15,77,403,157,158,71,397,4,326,141,275,371,415,421,75,74,28,237,93,401);

  StarGx:array[0..19] of integer=(435,279,179,383,309,439,166,368,465,187,379,399,380,211,245,355,194,269,375,260);
  StarGy:array[0..19] of integer=(97,204,140,405,118,137,67,369,309,370,162,94,138,131,85,355,381,393,109,151);

  StarBx:array[0..19] of integer=(247,186,453,389,424,472,205,386,479,318,162,452,189,333,344,398,417,421,342,370);
  StarBy:array[0..19] of integer=(322,227,176,147,133,236,240,267,117,423,338,376,301,461,239,38,183,44,122,332);

  // Filenames
  SoundFilenames : array[1..NumberOfSounds] of string =
    ('laser.wav', 'eexplode.wav', 'pexplode.wav');

type

  TTitulo = class(TSprite)
    DestRect: TSDL_Rect;
    Rect: TSDL_Rect;
    constructor Create(_x, _y: integer);
    procedure Draw; override;
  end;

  TPlayer = class(TSprite)
    ShootCounter:integer;
    BombCounter:integer;
    DestRect: TSDL_Rect;
    Rect: TSDL_Rect;
    constructor Create;
    procedure Draw; override;
    procedure Move; override;
    procedure DetectCollision;
    procedure GetCollisionRect(Rect: PSDL_Rect); override;
  end;

  TLaser = class(TSprite)
    DestRect: TSDL_Rect;
    constructor Create(_x, _y: integer);
    procedure Draw; override;
    procedure Move; override;
  end;

  TLaserIni = class(TSprite)
    DestRect: TSDL_Rect;
    constructor Create(_x, _y: integer);
    procedure Draw; override;
    procedure Move; override;
    procedure DetectCollision;
    procedure GetCollisionRect(Rect: PSDL_Rect); override;
  end;

  TEnemy = class(TSprite)
    Hull: integer;
    DestRect: TSDL_Rect;
    Rect: TSDL_Rect;
    Speed, SpeedCounter, Tipo, dx: integer;
    constructor Create;
    procedure HitByLaser;
    procedure Draw; override;
    procedure Move; override;
    procedure DetectCollision;
    procedure GetCollisionRect(Rect: PSDL_Rect); override;
  end;

  TExplosion = class(TSprite)
    DestRect: TSDL_Rect;
    Rect: TSDL_Rect;
    Speed, SpeedCounter: integer;
    constructor Create(_x, _y: integer);
    procedure Move; override;
    procedure Draw; override;
  end;

  TPremio = class(TSprite)
    DestRect: TSDL_Rect;
    Rect: TSDL_Rect;
    Speed, SpeedCounter, Tipo: integer;
    Time, TimeCounter: integer;    
    constructor Create(_x, _y, _Tipo: integer);
    procedure Move; override;
    procedure Draw; override;
  end;

  TStar = record
     Wx,Wy:array[0..19] of integer;
     Gx,Gy:array[0..19] of integer;
     Bx,By:array[0..19] of integer;
     Wc,Gc,Bc:UInt32;
     Wt,Gt,Bt:integer;
     Wtc,Gtc,Btc:integer;
  end;

Type
     TEstado=(eTitulo,eInstrucoes,eGetReady,eHiscore,eJogo,eBoss,eSair,eGameOver,eFimJogo);
     TTextAlign = ( alLeft, alCenter, alRight );

var
  Screen, Background, Graphics, ecTitulo, ecPainel: PSDL_Surface;
  SpriteEngine: TSpriteEngine;
  next_time: cardinal = 0;
  EnemyRate: cardinal = 0;
  Event: TSDL_Event;
  Keys: PKeyStateArr;
  Tiros,Bombas,Vidas,Pontos,Recorde:integer;
  Estado:TEstado;
  Counter:integer;
  Inven:boolean;
  TInven:integer;
  TBomba:boolean;
  Chars15x9:PSDL_Surface;
  Nivel:integer;

  Music : PMix_Music = nil;
  Freq : integer = 22050;
  AudioFormat : cardinal = AUDIO_S16LSB;
  Sounds : array[1..NumberOfSounds] of PMix_Chunk;
  Channels : cardinal = 2;

  Star:TStar;

procedure StartSound(Index: integer);
begin

     if Sounds[Index] = nil then
          exit;

     Mix_PlayChannel( -1, Sounds[Index], 0 );

end;

constructor TTitulo.Create(_x, _y: integer);
begin

     inherited Create('', 380, 78);
     x := _x;
     y := _y;
     Rect.x := 0;
     Rect.y := 0;
     Rect.w := 380;
     Rect.h := 78;

end;

procedure TTitulo.Draw;
begin

     DestRect.x := x;
     DestRect.y := y;
     SDL_BlitSurface(ecTitulo,@Rect, Surface, @DestRect);
     PrevRect := DestRect;

end;

constructor TExplosion.Create(_x, _y: integer);
begin

     inherited Create('', 24, 24);
     id:=idEXPLOSION;
     Speed := 30;
     SpeedCounter:=0;
     x := _x;
     y := _y;
     z := 200;
     Rect.x := 0;
     Rect.y := 40;
     Rect.w := 24;
     Rect.h := 24;

end;

procedure TExplosion.Move;
begin

     inc(SpeedCounter);
     if SpeedCounter = speed then
          Kill;

end;

procedure TExplosion.Draw;
begin

     DestRect.x := x;
     DestRect.y := y;
     SDL_BlitSurface(Graphics,@Rect, Surface, @DestRect);
     PrevRect := DestRect;

end;

constructor TEnemy.Create;
var
     xis,wid,hei:integer;
     teste:boolean;
     nteste,i:integer;
begin

     wid:=0;
     hei:=0;

     if Estado=eJogo then
     begin
          Tipo:=LEnemy[counter];
          if Tipo=1 then
          begin
               wid:=23;
               hei:=16;
          end;
          if Tipo=2 then
          begin
               wid:=23;
               hei:=16;
          end;
          if Tipo=3 then
          begin
               wid:=15;
               hei:=24;
          end;
          if Tipo=4 then
          begin
               wid:=24;
               hei:=24;
          end;
     end;

     if Estado=eBoss then
     begin
          if Nivel=1 then
          begin
               Tipo:=5;
               wid:=92;
               hei:=48;
          end;
          if Nivel=2 then
          begin
               Tipo:=6;
               wid:=120;
               hei:=64;
          end;
          if Nivel=3 then
          begin
               Tipo:=7;
               wid:=120;
               hei:=192;
          end;
          if Nivel=4 then
          begin
               Tipo:=8;
               wid:=144;
               hei:=144;
          end;
          if Nivel=5 then
          begin
               Tipo:=9;
               wid:=231;
               hei:=88;
          end;
     end;

     xis:=0;
     if Tipo<5 then
     begin
          teste:=false;
          nteste:=0;
          while (not teste) and (nteste<100) do
          begin
               xis := random(320-wid)+160;
               teste:=true;
               for i:=0 to SpriteEngine.Sprites.Count-1 do
                    if (SpriteEngine.Sprites.Items[i].ID=idFIGHTER) or (SpriteEngine.Sprites.Items[i].ID=idFIGHTER2) or (SpriteEngine.Sprites.Items[i].ID=idSTEALTH) or (SpriteEngine.Sprites.Items[i].ID=idBOMBER) then
                         if ((xis>=SpriteEngine.Sprites.Items[i].x) and (xis<=SpriteEngine.Sprites.Items[i].x+SpriteEngine.Sprites.Items[i].w)) or ((xis+wid>=SpriteEngine.Sprites.Items[i].x) and (xis+wid<=SpriteEngine.Sprites.Items[i].x+SpriteEngine.Sprites.Items[i].w)) then
                              teste:=false;
               nteste:=nteste+1;
          end;
     end
     else
          xis := random(320-wid)+160;

     inherited Create('', wid, hei);

     case Tipo of
          1: id := idFIGHTER;
          2: id := idFIGHTER2;
          3: id := idSTEALTH;
          4: id := idBOMBER;
          5: id := idBOSS1;
          6: id := idBOSS2;
          7: id := idBOSS3;
          8: id := idBOSS4;
          9: id := idBOSS5;          
     end;

     SpeedCounter := 0;

     x:=xis;

     case Tipo of
          1:begin   // Fighter I
               y := -16;
               z := random(50);
               Rect.x := 24;
               Rect.y := 0;
               Rect.w := 23;
               Rect.h := 16;
               Hull := 1;
               Speed := 2;
          end;
          2:begin      // Fighter II
               y := -16;
               z := random(50);
               Rect.x := 47;
               Rect.y := 0;
               Rect.w := 23;
               Rect.h := 16;
               Hull := 2;
               Speed := 2;
          end;
          3:begin   // Stealth
               y := -24;
               z := random(50);
               Rect.x := 70;
               Rect.y := 0;
               Rect.w := 15;
               Rect.h := 24;
               Hull := 3;
               Speed := 1;
          end;
          4:begin      // Bomber
               y := -24;
               z := random(50);
               Rect.x := 0;
               Rect.y := 0;
               Rect.w := 24;
               Rect.h := 24;
               Hull := 3;
               Speed := 2;
          end;
          5:begin      // Boss I
               y := -48;
               z := random(50);
               Rect.x := 90;
               Rect.y := 0;
               Rect.w := 92;
               Rect.h := 48;
               Hull := 100;
               Speed := 3;
               dx:=-1;
          end;
          6:begin      // Boss II
               y := -64;
               z := random(50);
               Rect.x := 90;
               Rect.y := 50;
               Rect.w := 120;
               Rect.h := 64;
               Hull := 150;
               Speed := 3;
               dx:=-1;
          end;
          7:begin      // Boss III
               y := -192;
               z := random(50);
               Rect.x := 215;
               Rect.y := 0;
               Rect.w := 120;
               Rect.h := 192;
               Hull := 200;
               Speed := 2;
               dx:=-1;
          end;
          8:begin      // Boss IV
               y := -144;
               z := random(50);
               Rect.x := 340;
               Rect.y := 0;
               Rect.w := 144;
               Rect.h := 144;
               Hull := 300;
               Speed := 2;
               dx:=-1;
          end;
          9:begin      // Boss V
               y := -88;
               z := random(50);
               Rect.x := 0;
               Rect.y := 206;
               Rect.w := 231;
               Rect.h := 88;
               Hull := 500;
               Speed := 1;
               dx:=-1;
          end;
     end;

end;

procedure TEnemy.GetCollisionRect(Rect: PSDL_Rect);
begin

     Rect.x := x;
     Rect.y := y;

     case Tipo of
          1,2:begin
               Rect.w := 23;
               Rect.h := 16;
              end;
          3:begin
               Rect.w := 15;
               Rect.h := 24;
              end;
          4:begin
               Rect.w := 24;
               Rect.h := 24;
              end;
          5:begin
               Rect.w := 92;
               Rect.h := 48;
              end;
          6:begin
               Rect.w := 120;
               Rect.h := 64;
              end;
          7:begin
               Rect.w := 120;
               Rect.h := 192;
              end;
          8:begin
               Rect.w := 144;
               Rect.h := 144;
              end;
          9:begin
               Rect.w := 231;
               Rect.h := 88;
              end;
     end;

end;

procedure TEnemy.Move;
var i:integer;
begin

     inc(SpeedCounter);

     if SpeedCounter = speed then
     begin

          if (Tipo<5) then
          begin
               inc(y);
               SpeedCounter:=0;
          end
          else
          begin

               if TBomba then
               begin

                    Hull:=Hull-10;
                    Pontos:=Pontos+15;

                    for i:=1 to 20 do
                         SpriteEngine.AddSprite(TExplosion.Create(random(w)+x, random(h)+y));

                    if Hull<10 then
                    begin

                         case Tipo of
                              5:Pontos:=Pontos+1000;
                              6:Pontos:=Pontos+1500;
                              7:Pontos:=Pontos+2000;
                              8:Pontos:=Pontos+3000;
                              9:Pontos:=Pontos+5000;
                         end;

                         startsound(3);

                         Kill; { myself }
                         inc(Nivel);
                         if Nivel=6 then
                         begin
                              for i:=0 to ParentList.Count - 1 do
                                   if (ParentList[i].ID<>idPLAYER) or (ParentList[i].ID<>idEXPLOSION) then
                                        ParentList[i].Kill;
                              Estado:=eFimJogo;
                         end
                         else
                              Estado:=eJogo;

                    end;
                    TBomba:=false;
               end;


               if y<20 then
               begin
                    inc(y,1);
                    SpeedCounter:=0;
               end
               else
               begin
                    if (x<160) or (x>480-Rect.w) then
                         dx:=dx*(-1);

                    x:=x+1*dx;

                    SpeedCounter:=0;
               end;
          end;
     end;

     i:=random(5000);
     if i<25 then
     begin

          if Tipo=1 then
               SpriteEngine.AddSprite(TLaserIni.Create(x + 11, y+16));

          if Tipo=2 then
          begin
               SpriteEngine.AddSprite(TLaserIni.Create(x + 6, y+10));
               SpriteEngine.AddSprite(TLaserIni.Create(x + 18, y+10));
          end;

          if Tipo=3 then
               SpriteEngine.AddSprite(TLaserIni.Create(x + 7, y+24));

          if Tipo=4 then
          begin
               SpriteEngine.AddSprite(TLaserIni.Create(x + 5, y+16));
               SpriteEngine.AddSprite(TLaserIni.Create(x + 18, y+16));
          end;

     end;

     if i<400 then
     begin
          case Tipo of
               5:SpriteEngine.AddSprite(TLaserIni.Create(random(w-7)+(x+2), y+48));
               6:SpriteEngine.AddSprite(TLaserIni.Create(random(w-15)+(x+15), y+64));
               7:SpriteEngine.AddSprite(TLaserIni.Create(random(w-9)+(x+7), y+192));
               8:SpriteEngine.AddSprite(TLaserIni.Create(random(w-7)+(x+6), y+144));
               9:SpriteEngine.AddSprite(TLaserIni.Create(random(w-33)+(x+32), y+88));
          end;
     end;

     if y > 480 then
          Kill;

     DetectCollision;

end;

procedure TEnemy.Draw;
begin

     DestRect.x := x;
     DestRect.y := y;
     SDL_BlitSurface(Graphics,@Rect, Surface, @DestRect);
     PrevRect := DestRect;

end;

procedure TEnemy.DetectCollision;
var
     i,j: integer;
     MyRect, NMERect: TSDL_Rect;
begin

     GetCollisionRect(@MyRect);

     for i := 0 to ParentList.Count - 1 do
          if ParentList[i] <> Self then
          begin
               ParentList[i].GetCollisionRect(@NMERect);

               if isCollideRects(@MyRect, @NMERect) then
               begin
                    if ParentList[i].ID = idLASER then
                    begin
                         if Tipo>=5 then
                              SpriteEngine.AddSprite(TExplosion.Create(ParentList[i].x+12, ParentList[i].y-24));

                         ParentList[i].Kill;
                         startsound(2);
                         HitByLaser; { myself }
                    end
                    else if ParentList[i].ID = idPLAYER then
                    begin

                         if not Inven then
                         begin
                              Tiros:=1;
                              Vidas:=Vidas-1;

                              Inven:=true;
                              TInven:=0;

                              if Vidas=0 then
                                   Estado:=eGameOver;

                              startsound(2);
                              SpriteEngine.AddSprite(TExplosion.Create(ParentList[i].x-4,ParentList[i].y-4));

                              if (Tipo<5) then
                              begin
                                   startsound(2);
                                   Kill; { myself }
                                   SpriteEngine.AddSprite(TExplosion.Create(x, y));
                              end
                              else
                              begin
                                   Hull:=Hull-20;
                                   if Hull<20 then
                                   begin

                                        case Tipo of
                                             5:Pontos:=Pontos+1000;
                                             6:Pontos:=Pontos+1500;
                                             7:Pontos:=Pontos+2000;
                                             8:Pontos:=Pontos+3000;
                                             9:Pontos:=Pontos+5000;
                                        end;

                                        for j:=1 to 20 do
                                             SpriteEngine.AddSprite(TExplosion.Create(random(w)+x, random(h)+y));

                                        startsound(3);
                                        Kill; { myself }

                                        inc(Nivel);
                                        if Nivel=6 then
                                        begin

                                             for j:=0 to ParentList.Count - 1 do
                                                  if (ParentList[j].ID <> idPLAYER) or (ParentList[j].ID<>idEXPLOSION) then
                                                       ParentList[j].Kill;

                                             Estado:=eFimJogo;
                                        end
                                        else
                                             Estado:=eJogo;
                                   end;
                              end;
                         end;
                    end;
               end;
          end;
end;

procedure TEnemy.HitByLaser;
var
     i:integer;

begin

     Hull := Hull - 1;

     if Hull = 0 then
     begin
          Kill;

          if (Tipo<5) then
               SpriteEngine.AddSprite(TExplosion.Create(x, y))
          else
               for i:=1 to 20 do
                    SpriteEngine.AddSprite(TExplosion.Create(random(w)+x, random(h)+y));

          case Tipo of
               1:Pontos:=Pontos+10;
               2:Pontos:=Pontos+20;
               3:Pontos:=Pontos+30;
               4:Pontos:=Pontos+50;
               5:Pontos:=Pontos+1000;
               6:Pontos:=Pontos+1500;
               7:Pontos:=Pontos+2000;
               8:Pontos:=Pontos+3000;
               9:Pontos:=Pontos+5000;
          end;

          if Tipo<5 then
          begin
               i:=random(2000);
               if (i>=250) and (i<500) then
                    SpriteEngine.AddSprite(TPremio.Create(x+8, y+8, 1));

               if (i>=500) and (i<750) then
                    SpriteEngine.AddSprite(TPremio.Create(x+8, y+8, 2));

               if (i>=750) and (i<900) then
                    SpriteEngine.AddSprite(TPremio.Create(x+8, y+8, 3));

               if (i>=900) and (i<1000) then
                    SpriteEngine.AddSprite(TPremio.Create(x+8, y+8, 4));
          end
          else
          begin
               startsound(3);

               inc(Nivel);
               if Nivel=6 then
               begin
                    for i:=0 to ParentList.Count - 1 do
                         if (ParentList[i].ID<>idPLAYER) or (ParentList[i].ID<>idEXPLOSION) then
                              ParentList[i].Kill;
                    Estado:=eFimJogo;
               end
               else
                    Estado:=eJogo;

          end;

     end
     else
          pontos:=pontos+5;

end;

constructor TLaser.Create(_x, _y: integer);
begin

     inherited Create('', 1, 8);
     id := idLASER;
     x := _x;
     y := _y;
     z := 50;
     SrcRect.x := 2;
     SrcRect.y := 67;
     SrcRect.w := 1;
     SrcRect.h := 8;

end;

procedure TLaser.Move;
begin

     if y > -8 then
          dec(y, 2)
     else
          Kill;

end;

procedure TLaser.Draw;
begin

     DestRect.x := x;
     DestRect.y := y;
     SDL_BlitSurface(Graphics, @SrcRect, Surface, @DestRect);
     PrevRect := DestRect;

end;

constructor TLaserIni.Create(_x, _y: integer);
begin

     inherited Create('', 1, 8);
     id := idLASERINI;
     x := _x;
     y := _y;
     z := 50;
     SrcRect.x := 0;
     SrcRect.y := 67;
     SrcRect.w := 1;
     SrcRect.h := 8;

end;

procedure TLaserINI.Move;
begin

     if y < 480 then
          inc(y, 2)
     else
          Kill;

     DetectCollision;

end;

procedure TLaserIni.Draw;
begin

     DestRect.x := x;
     DestRect.y := y;
     SDL_BlitSurface(Graphics, @SrcRect, Surface, @DestRect);
     PrevRect := DestRect;

end;

procedure TLaserIni.GetCollisionRect(Rect: PSDL_Rect);
begin

     Rect.x := x;
     Rect.y := y;
     Rect.w := 1;
     Rect.h := 8;

end;

procedure TLaserIni.DetectCollision;
var
     i:integer;
     MyRect, NMERect: TSDL_Rect;
begin

     GetCollisionRect(@MyRect);

     for i := 0 to ParentList.Count - 1 do
          if ParentList[i] <> Self then
          begin
               ParentList[i].GetCollisionRect(@NMERect);

                if isCollideRects(@MyRect, @NMERect) then
                begin
                    if ParentList[i].ID = idPLAYER then
                    begin

                         if not Inven then
                         begin
                              Tiros:=1;
                              Vidas:=Vidas-1;

                              Inven:=true;
                              TInven:=0;

                              if Vidas=0 then
                                   Estado:=eGameOver;

//                            ParentList[i].Kill; { Player }
                              startsound(2);
                              SpriteEngine.AddSprite(TExplosion.Create(ParentList[i].x-4,ParentList[i].y-4));
                         end;
                         Kill; { myself }
                    end;
               end;
          end;

end;

constructor TPremio.Create(_x, _y, _Tipo: integer);
begin

     inherited Create('', 12, 12);
     x := _x;
     y := _y;
     Tipo:=_Tipo;
     z := 50;
     time:=500;
     timecounter:=0;
     speed:=4;
     speedcounter:=0;

     case Tipo of
          1:begin
               Rect.x := 42;
               Rect.y := 63;
               Rect.w := 12;
               Rect.h := 12;
               id := idPREMIOT;
            end;
          2:begin
               Rect.x := 66;
               Rect.y := 63;
               Rect.w := 12;
               Rect.h := 12;
               id := idPREMIOP;
            end;
          3:begin
               Rect.x := 54;
               Rect.y := 63;
               Rect.w := 12;
               Rect.h := 12;
               id := idPREMIOB;
            end;
          4:begin
               Rect.x := 30;
               Rect.y := 63;
               Rect.w := 12;
               Rect.h := 12;
               id := idPREMIOV;
            end;
     end;

end;

procedure TPremio.Move;
begin

     inc (timecounter);
     inc (speedcounter);

     if timecounter=time then
          kill;

     if speedcounter=speed then
     begin
          inc(y);
          speedcounter:=0;
     end;

     if y > 480 then
          Kill;

end;

procedure TPremio.Draw;
begin

     DestRect.x := x;
     DestRect.y := y;
     SDL_BlitSurface(Graphics, @Rect, Surface, @DestRect);
     PrevRect := DestRect;

end;

constructor TPlayer.Create;
begin

     inherited Create('', 16, 16);
     id := idPLAYER;
     z := 100;
     ShootCounter:=0;
     BombCounter:=0;
     x := 320 - 8;
     y := 479 - 16;
     Rect.x := 0;
     Rect.y := 24;
     Rect.w := 16;
     Rect.h := 16;

end;

procedure TPlayer.DetectCollision;
var
     i:integer;
     MyRect, NMERect: TSDL_Rect;
begin

     GetCollisionRect(@MyRect);

     for i := 0 to ParentList.Count - 1 do
          if ParentList[i] <> Self then
          begin
               ParentList[i].GetCollisionRect(@NMERect);

               if isCollideRects(@MyRect, @NMERect) then
               begin

                    if ParentList[i].ID = idPREMIOT then
                    begin
                         ParentList[i].Kill; {tiros}
                         if Tiros=1 then Tiros:=2;
                    end;
                    if ParentList[i].ID = idPREMIOP then
                    begin
                         ParentList[i].Kill; {pontos}
                         Pontos:=Pontos+500;
                    end;
                    if ParentList[i].ID = idPREMIOB then
                    begin
                         ParentList[i].Kill; {bombas}
                         if Bombas<9 then Bombas:=Bombas+1;
                    end;
                    if ParentList[i].ID = idPREMIOV then
                    begin
                         ParentList[i].Kill; {vidas}
                         if Vidas<99 then Vidas:=Vidas+1;
                    end;
               end;
          end;

end;

procedure TPlayer.GetCollisionRect(Rect: PSDL_Rect);
begin

     Rect.x := x;
     Rect.y := y;
     Rect.h := 16;
     Rect.w := 16;

end;

procedure TPlayer.Move;
var
     i:integer;
begin

{
     if (Keys[SDLK_LEFT] = 1) and (x > 0) then
          dec(x,1)
     else if (Keys[SDLK_RIGHT] = 1) and (x < 448 - 16) then
          inc(x,1);

     if (Keys[SDLK_UP] = 1) and (y > 0) then
          dec(y,1)
     else if (Keys[SDLK_DOWN] = 1) and (y < 480 - 16) then
          inc(y,1);
}

     if (Keys[SDLK_LEFT] = 1) and (x > 160) then
          dec(x,1);

     if (Keys[SDLK_RIGHT] = 1) and (x < 480 - 16) then
          inc(x,1);

     if (Keys[SDLK_UP] = 1) and (y > 0) then
          dec(y,1);

     if (Keys[SDLK_DOWN] = 1) and (y < 480 - 16) then
          inc(y,1);

     if (Keys[SDLK_LALT]=1) and (BombCounter=0) and (Bombas>0) then
     begin

          for i:=0 to ParentList.Count - 1 do
               if ParentList[i] <> Self then
                    if (ParentList[i].ID=idBOSS1) or (ParentList[i].ID=idBOSS2) or (ParentList[i].ID=idBOSS3) or (ParentList[i].ID=idBOSS4) or (ParentList[i].ID=idBOSS5) then
                    begin
                         TBomba:=true;
                    end
                    else
                    begin
                         ParentList[i].Kill;
                         if (ParentList[i].id=idFIGHTER) or (ParentList[i].id=idFIGHTER2) or (ParentList[i].id=idSTEALTH) or (ParentList[i].id=idBOMBER) then
                              SpriteEngine.AddSprite(TExplosion.Create(ParentList[i].x,ParentList[i].y));
                    end;

          Bombas:=Bombas-1;
          inc(BombCounter);
          ShootCounter := 0;
          startsound(3);
     end;

     if (Keys[SDLK_SPACE] = 1) and (ShootCounter = 0) then
     begin
          if Tiros=1 then
          begin
               SpriteEngine.AddSprite(TLaser.Create(x + 8, y-8));
               inc(ShootCounter);
          end
          else
          begin
               SpriteEngine.AddSprite(TLaser.Create(x + 3, y-3));
               SpriteEngine.AddSprite(TLaser.Create(x + 12, y-3));
               inc(ShootCounter);
          end;

          StartSound(1);
     end;

     if ShootCounter > 0 then
     begin
          inc(ShootCounter);
          if ShootCounter = 40 then
               ShootCounter := 0;
     end;

     if BombCounter > 0 then
     begin
          inc(BombCounter);
          if BombCounter = 100 then
               BombCounter := 0;
     end;

     DetectCollision;

     if Inven then
     begin
          inc(TInven);
          if TInven=200 then
               Inven:=false;
     end;

end;

procedure TPlayer.Draw;
begin

     DestRect.x := x;
     DestRect.y := y;
     SDL_BlitSurface(Graphics, @Rect, Surface, @DestRect);
     PrevRect := DestRect;

end;


function TimeLeft: UInt32;
var
     now: UInt32;
begin

     now := SDL_GetTicks;
     if next_time <= now then
     begin
          next_time := now + TICK_INTERVAL;
          result := 0;
          exit;
     end;

     result := next_time - now;

end;

procedure DrawStar;
var
     i:integer;
begin

     for i:=0 to 19 do
     begin
          Star.Wx[i]:=StarWx[i];
          Star.Wy[i]:=StarWy[i];
          Star.Gx[i]:=StarGx[i];
          Star.Gy[i]:=StarGy[i];
          Star.Bx[i]:=StarBx[i];
          Star.By[i]:=StarBy[i];
     end;

     Star.Wc:=SDL_MapRGB(Background.format, $FF, $FF, $FF);
     Star.Gc:=SDL_MapRGB(Background.format, $80, $80, $80);
     Star.Bc:=SDL_MapRGB(Background.format, $00, $00, $FF);

     Star.Wt:=1;
     Star.Gt:=3;
     Star.Bt:=2;
     Star.Wtc:=0;
     Star.Gtc:=0;
     Star.Btc:=0;

     for i:=0 to 19 do
     begin
          SDL_PutPixel(Background, Star.Wx[i], Star.Wy[i], Star.Wc);
          SDL_PutPixel(Background, Star.Gx[i], Star.Gy[i], Star.Gc);
          SDL_PutPixel(Background, Star.Bx[i], Star.By[i], Star.Bc);
     end;

     SDL_BlitSurface(Background, nil, Screen, nil);

end;

procedure ScrollStar;
var
     i:integer;
     MustLock: boolean;
begin

     MustLock := SDL_MustLock(Background);
     if MustLock then
          SDL_LockSurface(Background);

     inc(Star.Wtc);
     if Star.Wtc=Star.Wt then
          for i:=0 to 19 do
          begin
               SDL_PutPixel(Background, Star.Wx[i], Star.Wy[i], SDL_MapRGB(Background.format,0,0,0));
               inc(Star.Wy[i]);
               if Star.Wy[i]=480 then
                    Star.Wy[i]:=0;
               SDL_PutPixel(Background, Star.Wx[i], Star.Wy[i], Star.Wc);
               Star.Wtc:=0;
          end;

     inc(Star.Gtc);
     if Star.Gtc=Star.Gt then
          for i:=0 to 19 do
          begin
               SDL_PutPixel(Background, Star.Gx[i], Star.Gy[i], SDL_MapRGB(Background.format,0,0,0));
               inc(Star.Gy[i]);
               if Star.Gy[i]=480 then
                    Star.Gy[i]:=0;
               SDL_PutPixel(Background, Star.Gx[i], Star.Gy[i], Star.Gc);
               Star.Gtc:=0;
          end;

     inc(Star.Btc);
     if Star.Btc=Star.Bt then
          for i:=0 to 19 do
          begin
               SDL_PutPixel(Background, Star.Bx[i], Star.By[i], SDL_MapRGB(Background.format,0,0,0));
               inc(Star.By[i]);
               if Star.By[i]=480 then
                    Star.By[i]:=0;
               SDL_PutPixel(Background, Star.Bx[i], Star.By[i], Star.Bc);
               Star.Btc:=0;
          end;

     if MustLock then
          SDL_UnlockSurface(Background);

     SDL_BlitSurface(Background, nil, Screen, nil);

end;

procedure LoadMusic( const Filename : string );
const
  StrLoad = 'LoadMusic';
begin

     music := Mix_LoadMUS( PChar( Filename ) );

     if Music = nil then
     begin
          SDL_Quit;
          halt;
     end

end;

procedure StartMusic;
begin
     Mix_PlayMusic( music, 0 );
end;

procedure StopMusic;
begin
     Mix_FreeMusic( music );
     Music := nil;
end;

procedure RestartMusic;
begin

     if Mix_PlayingMusic = 0 then
          Mix_PlayMusic( music, 0 );
end;

procedure Inicializar;
var
     TempFlag:cardinal;
     i:integer;
begin


//   Set Hiscore
     Recorde:=0;

//   Set Graphics
     if SDL_Init(SDL_INIT_VIDEO) <> 0 then
          halt;

     SDL_WM_SetCaption('Sardonic', nil);

     Screen := SDL_SetVideoMode(640, 480, 16, SDL_FULLSCREEN or SDL_HWPALETTE);
     if Screen = nil then
     begin
          SDL_Quit;
          halt;
     end;

     Graphics := SDL_LoadBMP('sprites/sprites.bmp');
     if Graphics = nil then
     begin
          SDL_Quit;
          halt;
     end;
     SDL_SetColorKey(Graphics, SDL_HWACCEL or SDL_RLEACCEL or SDL_SRCCOLORKEY, 0);

     Background := SDL_CreateRGBSurface(SDL_SWSURFACE or SDL_HWPALETTE, 640, 480, 16, 0, 0, 0, 0);
     if Background = nil then
     begin
          SDL_Quit;
          halt;
     end;

     ecTitulo := SDL_LoadBMP('sprites/titulo.bmp');
     if ecTitulo = nil then
     begin
          SDL_Quit;
          halt;
     end;

     ecPainel := SDL_LoadBMP('sprites/Painel.bmp');
     if ecPainel = nil then
     begin
          SDL_Quit;
          halt;
     end;

     Chars15x9 := IMG_Load('sprites/fonte.png');
     if Chars15x9 = nil then
     begin
          SDL_Quit;
          halt;
     end
     else
          Chars15x9 := SDL_DisplayFormat(Chars15x9);


     SDL_ShowCursor(SDL_DISABLE);
     SpriteEngine := TSpriteEngine.Create(Screen);
     SpriteEngine.BackgroundSurface := Background;

//   Set Audio
     TempFlag:=SDL_INIT_AUDIO;
     if SDL_Init(TempFlag)=-1 then
     begin
          SDL_Quit;
          halt;
     end;

     if Mix_OpenAudio( Freq, AudioFormat, Channels, 1024 ) < 0 then
     begin
          SDL_Quit;
          halt;
     end
     else
          Mix_HookMusicFinished( @RestartMusic );

     for i := 1 to NumberOfSounds do
     begin
          Sounds[i] := Mix_LoadWav(PChar('sons/'+ SoundFilenames[i]));
          if Sounds[i] = nil then
          begin
               SDL_Quit;
               halt;
          end;
      end;

     loadmusic('musica/helico.xm');
     startmusic;

end;

procedure WriteText_15x9( Surf : PSDL_Surface; const Txt : string; x,y : integer;
  Align : TTextAlign );
var
     StartX, i : integer;
     SrcRect, DestRect : TSDL_Rect;
begin

     StartX := 0;
     SrcRect.y := 0;
     SrcRect.w := 15;
     SrcRect.h := 9;
     DestRect.y := y;

     case Align of
          alLeft : StartX := x;
          alCenter : StartX := x - length( txt ) * 8;
          alRight : StartX := x - length( txt ) * 15 + 1;
     end;

     for i := 0 to Length( txt ) - 1 do
     begin
          SrcRect.x := pos(Txt[i + 1],Chars) * 15 - 15;
          DestRect.x := StartX + i * 15;
          SDL_BlitSurface(Chars15x9, @SrcRect, Surf, @DestRect);
     end;

end;

procedure Titulo;
var
     Src,Dest: TSDL_Rect;
     counter:integer;
begin

     SDL_FillRect( Screen, nil, 0 );
     SDL_UpdateRect( Screen, 0, 0, 0, 0 );
     SDL_FillRect( background, nil, 0 );
     SDL_UpdateRect( background, 0, 0, 0, 0 );

//   Logo
     Src.w:=380;
     Src.h:=78;
     Src.x:=0;
     Src.y:=0;
     Dest.x:=130;
     Dest.y:=30;
     SDL_BlitSurface(ecTitulo, @Src, screen, @Dest);

//   Controls
     WriteText_15x9(screen, 'cursors: directions', 320,150, alCenter);
     WriteText_15x9(screen, 'space: fire', 320,170, alCenter);
     WriteText_15x9(screen, 'alt: bomb', 320,190, alCenter);
     WriteText_15x9(screen, 'fire to start game', 320,250, alCenter);
     WriteText_15x9(screen, 'escape to quit', 320,270, alCenter);

//   Credits
     WriteText_15x9(screen, 'code and graphics by madaxe', 320,330, alCenter);
     WriteText_15x9(screen, 'music by fred', 320,350, alCenter);
     WriteText_15x9(screen, 'copyright 2003 thc', 320,410, alCenter);


     SDL_UpdateRect(Screen, 0, 0, 0, 0);

     counter:=0;

     repeat

          SDL_Delay(TimeLeft);

          while SDL_PollEvent(@Event) > 0 do
          begin
               case Event.key.type_  of
                    SDL_KeyDown:begin
                                   if Event.key.keysym.sym = SDLK_SPACE then
                                        Estado:=eGetReady;
                                   if Event.key.keysym.sym = SDLK_ESCAPE then
                                        Estado:=eSair;
                                 end;
               end;
          end;

          inc(counter);
          if Counter=3000 then
               Estado:=eInstrucoes;

     until Estado <> eTitulo;

end;

procedure Instrucoes;
var
     Src,Dest: TSDL_Rect;
     counter:integer;
begin

     SDL_FillRect( Screen, nil, 0 );
     SDL_UpdateRect( Screen, 0, 0, 0, 0 );
     SDL_FillRect( background, nil, 0 );
     SDL_UpdateRect( background, 0, 0, 0, 0 );

//   Logo
     Src.w:=380;
     Src.h:=78;
     Src.x:=0;
     Src.y:=0;
     Dest.x:=130;
     Dest.y:=30;
     SDL_BlitSurface(ecTitulo, @Src, screen, @Dest);

//   Fighter I
     Src.w:=23;
     Src.h:=16;
     Src.x:=24;
     Src.y:=0;
     Dest.x:=130;
     Dest.y:=130;
     SDL_BlitSurface(Graphics, @Src, screen, @Dest);

//   Fighter II
     Src.w:=23;
     Src.h:=16;
     Src.x:=47;
     Src.y:=0;
     Dest.x:=130;
     Dest.y:=170;
     SDL_BlitSurface(Graphics, @Src, screen, @Dest);

//   Stealth
     Src.w:=15;
     Src.h:=24;
     Src.x:=70;
     Src.y:=0;
     Dest.x:=134;
     Dest.y:=210;
     SDL_BlitSurface(Graphics, @Src, screen, @Dest);

//   Bomber
     Src.w:=24;
     Src.h:=24;
     Src.x:=0;
     Src.y:=0;
     Dest.x:=130;
     Dest.y:=250;
     SDL_BlitSurface(Graphics, @Src, screen, @Dest);

     WriteText_15x9(screen, 'fighter i  : 10 points', 180,134, alLeft);
     WriteText_15x9(screen, 'fighter ii : 20 points', 180,174, alLeft);
     WriteText_15x9(screen, 'stealth    : 30 points', 180,218, alLeft);
     WriteText_15x9(screen, 'bomber     : 50 points', 180,258, alLeft);

//   Tiros
     Src.w:=12;
     Src.h:=12;
     Src.x:=42;
     Src.y:=63;
     Dest.x:=225;
     Dest.y:=310;
     SDL_BlitSurface(Graphics, @Src, screen, @Dest);

//   Pontos
     Src.w:=12;
     Src.h:=12;
     Src.x:=66;
     Src.y:=63;
     Dest.x:=225;
     Dest.y:=340;
     SDL_BlitSurface(Graphics, @Src, screen, @Dest);

//   Bombas
     Src.w:=12;
     Src.h:=12;
     Src.x:=54;
     Src.y:=63;
     Dest.x:=225;
     Dest.y:=370;
     SDL_BlitSurface(Graphics, @Src, screen, @Dest);

//   Vidas
     Src.w:=12;
     Src.h:=12;
     Src.x:=30;
     Src.y:=63;
     Dest.x:=225;
     Dest.y:=400;
     SDL_BlitSurface(Graphics, @Src, screen, @Dest);

     WriteText_15x9(screen, 'extra fire', 265,311, alLeft);
     WriteText_15x9(screen, 'extra points', 265,341, alLeft);
     WriteText_15x9(screen, 'extra bomb', 265,371, alLeft);
     WriteText_15x9(screen, 'extra live', 265,401, alLeft);

     SDL_UpdateRect(Screen, 0, 0, 0, 0);

     counter:=0;

     repeat

          SDL_Delay(TimeLeft);

          while SDL_PollEvent(@Event) > 0 do
          begin
               case Event.key.type_  of
                    SDL_KeyDown:begin
                                   if Event.key.keysym.sym = SDLK_SPACE then
                                        Estado:=eGetReady;
                                   if Event.key.keysym.sym = SDLK_ESCAPE then
                                        Estado:=eTitulo;
                                 end;
               end;
          end;

          inc(counter);
          if Counter=3000 then
               Estado:=eHiscore;

     until Estado <> eInstrucoes;

end;

procedure Hiscore;
var
     Src,Dest: TSDL_Rect;
     counter:integer;
begin

     SDL_FillRect( Screen, nil, 0 );
     SDL_UpdateRect( Screen, 0, 0, 0, 0 );
     SDL_FillRect( background, nil, 0 );
     SDL_UpdateRect( background, 0, 0, 0, 0 );

//   Logo
     Src.w:=380;
     Src.h:=78;
     Src.x:=0;
     Src.y:=0;
     Dest.x:=130;
     Dest.y:=30;
     SDL_BlitSurface(ecTitulo, @Src, screen, @Dest);

//   Hiscore
     WriteText_15x9(screen, 'hiscore of the day', 320,220, alCenter);
     WriteText_15x9(screen, stringofchar('0',6-length(inttostr(Recorde)))+inttostr(Recorde), 320,240, alCenter);

     SDL_UpdateRect(Screen, 0, 0, 0, 0);

     counter:=0;

     repeat

          SDL_Delay(TimeLeft);

          while SDL_PollEvent(@Event) > 0 do
          begin
               case Event.key.type_  of
                    SDL_KeyDown:begin
                                   if Event.key.keysym.sym = SDLK_SPACE then
                                        Estado:=eGetReady;
                                   if Event.key.keysym.sym = SDLK_ESCAPE then
                                        Estado:=eTitulo;
                                 end;
               end;
          end;

          inc(counter);
          if Counter=3000 then
               Estado:=eTitulo;

     until Estado <> eHiscore;

end;

procedure GetReady;
var
     Src,Dest: TSDL_Rect;
begin

     SpriteEngine.BackgroundSurface := Background;
     SDL_FillRect(Background, nil, 0 );
     SDL_UpdateRect(Background, 0, 0, 0, 0 );

     Src.w:=160;
     Src.h:=480;
     Src.x:=0;
     Src.y:=0;

     Dest.x:=0;
     Dest.y:=0;
     SDL_BlitSurface(ecPainel, @Src, Background, @Dest);

     Dest.x:=480;
     Dest.y:=0;
     SDL_BlitSurface(ecPainel, @Src, Background, @Dest);

     SDL_FillRect(Screen, nil, 0 );
     SDL_UpdateRect(Screen, 0, 0, 0, 0);

     Tiros:=1;
     Bombas:=5;
     Vidas:=5;
     Pontos:=0;
     Nivel:=1;

     counter:=0;
     TBomba:=false;
     Inven:=false;

     Estado:=eJogo;

end;

procedure Painel;
begin

     WriteText_15x9( screen, 'points', 35,120, alLeft);
     WriteText_15x9( screen, stringofchar('0',6-length(inttostr(Pontos)))+inttostr(Pontos), 35,140, alLeft);
     WriteText_15x9( screen, 'level', 43,240, alLeft);
     WriteText_15x9( screen, stringofchar('0',2-length(inttostr(Nivel)))+inttostr(Nivel), 65,260, alLeft);

     WriteText_15x9( screen, 'lives', 523,120, alLeft);
     WriteText_15x9( screen, stringofchar('0',2-length(inttostr(Vidas)))+inttostr(Vidas), 545,140, alLeft);
     WriteText_15x9( screen, 'bombs', 523,240, alLeft);
     WriteText_15x9( screen, stringofchar('0',2-length(inttostr(Bombas)))+inttostr(Bombas), 545,260, alLeft);

end;

procedure GameOver;
var tempo:integer;
begin

     SpriteEngine.Clear;
     SDL_UpdateRect(Screen, 0, 0, 0, 0);

     tempo:=0;

     repeat

//        update changes on screen
          ScrollStar;
          WriteText_15x9( screen, 'game over',320,235, alCenter);
          Painel;
          SDL_UpdateRect(Screen, 0, 0, 0, 0);
          SDL_Delay(TimeLeft);

          while SDL_PollEvent(@Event) > 0 do
          begin
               case Event.key.type_  of
                    SDL_KeyDown:begin
                                   if (Event.key.keysym.sym = SDLK_SPACE) or (Event.key.keysym.sym = SDLK_ESCAPE) then
                                        Estado:=eSair;
                                 end;
               end;
          end;

          tempo:=tempo+1;

     until (tempo=400) or (Estado<>eGameOver);

     if Pontos>Recorde then
          Recorde:=Pontos;

     Estado:=eTitulo;

end;

procedure FimJogo;
var tempo:integer;
begin

     tempo:=0;

     repeat

//        update changes on screen
          ScrollStar;
          WriteText_15x9( screen, 'well done !!',320,235, alCenter);
          Painel;
          SDL_UpdateRect(Screen, 0, 0, 0, 0);
          SDL_Delay(TimeLeft);

          while SDL_PollEvent(@Event) > 0 do
          begin
               case Event.key.type_  of
                    SDL_KeyDown:begin
                                   if (Event.key.keysym.sym = SDLK_SPACE) or (Event.key.keysym.sym = SDLK_ESCAPE) then
                                        Estado:=eSair;
                                 end;
               end;
          end;

          tempo:=tempo+1;

     until (tempo=1000) or (Estado<>eFimJogo);

     if Pontos>Recorde then
          Recorde:=Pontos;
          
     Estado:=eTitulo;

end;

procedure Jogo;
begin


     SpriteEngine.Clear;
     SDL_FillRect(Screen, nil, 0 );
     SDL_UpdateRect(Screen, 0, 0, 0, 0);
     DrawStar;
     SpriteEngine.AddSprite(TPlayer.Create);

     repeat

          while SDL_PollEvent(@Event) > 0 do
          begin
               case Event.key.type_ of
                    SDL_QUITEV:begin
                                   Estado:=eGameOver;
                                end;

                    SDL_KeyDown:begin
                                   if Event.key.keysym.sym = SDLK_ESCAPE then
                                        Estado:=eGameOver;
                                end;
               end;
          end;

          keys := PKeyStateArr(SDL_GetKeyState(nil));

//        remove all sprites from the screen and move all sprites
          SpriteEngine.Move;

//        Changing background
          ScrollStar;

          if Estado=eJogo then
          begin
               inc(EnemyRate);
               if EnemyRate = 90 then
               begin
                    if LEnemy[counter]<>0 then
                    begin
                         if (LEnemy[counter]=5) or (LEnemy[counter]=6) or (LEnemy[counter]=7) or (LEnemy[counter]=8) or (LEnemy[counter]=9) then
                              Estado:=eBoss;
                         SpriteEngine.AddSprite(TEnemy.Create);
                    end;
                    EnemyRate := 0;
                    counter:=counter+1;
               end;
          end;

          Painel;

//        redraw all sprites to the screen in new positions
          SpriteEngine.Draw;

//        update changes on screen
          SDL_UpdateRect(Screen, 0, 0, 0, 0);
          SDL_Delay(TimeLeft);

     until (Estado=eSair) or (Estado=eGameOver) or (Estado=eFimJogo);

end;

begin

     randomize;
     Inicializar;

     Estado:=eTitulo;

     repeat
          case Estado of
               eTitulo:Titulo;
               eInstrucoes:Instrucoes;
               eHiscore:Hiscore;
               eGetReady:GetReady;
               eJogo:Jogo;
               eGameOver:GameOver;
               eFimJogo:FimJogo;
          end;
     until Estado=eSair;

     SpriteEngine.Free;
     SDL_FreeSurface(Graphics);
     SDL_Quit;

end.

