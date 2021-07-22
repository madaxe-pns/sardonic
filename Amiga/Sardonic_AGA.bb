;
; Sardonic - AGA Version
;
; (C) 2019 Penisoft
;
; Code & Graphics by Madaxe
; Music by Fred
;
; Made in Portugal
;


WBStartup

NPrint ""
NPrint "SARDONIC - (C) 2019 Penisoft"
NPrint "By MaxAxe"
NPrint ""
NPrint "AGA Version"
NPrint ""

; Verifica se e PAL ou NTSC
If NTSC
  NPrint ""
  NPrint "PAL is required"
  NPrint ""
  Goto fimfim
Else
  NPrint "PAL OK"
End If

;Definicao de Tipos, Constantes e Variaveis

DEFTYPE .w

.tipos

; Tipo dos Inimigos
NEWTYPE .ltipoini
  tipoini.b[1000]
End NEWTYPE

DEFTYPE .ltipoini ltipoini

; Posicao Horizontal dos Inimigos
NEWTYPE .linix
  inix.w[1000]
End NEWTYPE

DEFTYPE .linix linix

Dim linix.linix(3)

NPrint ""
NPrint "Loading Data"

; Le o Tipo dos Inimigos
If ReadFile (0,"data/inimigos/inimigos.dat")
  ReadMem 0,&ltipoini,SizeOf.ltipoini
  CloseFile 0
End If

; Le a Posicao Horizontal dos Inimigos
If ReadFile (1,"data/inimigos/inimigos_x_01.dat")
  ReadMem 1,&linix(0),SizeOf.linix
  CloseFile 1
End If

If ReadFile (2,"data/inimigos/inimigos_x_02.dat")
  ReadMem 2,&linix(1),SizeOf.linix
  CloseFile 2
End If

If ReadFile (3,"data/inimigos/inimigos_x_03.dat")
  ReadMem 3,&linix(2),SizeOf.linix
  CloseFile 3
End If

If ReadFile (4,"data/inimigos/inimigos_x_04.dat")
  ReadMem 4,&linix(3),SizeOf.linix
  CloseFile 4
End If


; Inimigos
NEWTYPE .linis
  x.w
  y.w
  tx.w
  ty.w
  sp.w
  hull.w
  tipo.w
  pontos.w
End NEWTYPE

Dim List lini.linis(7)

;Lista de Dados dos Inimigos
NEWTYPE .ltinis
  sp.w
  hull.w
  pontos.w
  tx.w
  ty.w
  py.w
End NEWTYPE

Dim ltini.ltinis(9)

ltini(0)\sp=0:ltini(0)\hull=0:ltini(0)\pontos=0
ltini(0)\tx=0:ltini(0)\ty=0:ltini(0)\py=0

ltini(1)\sp=3:ltini(1)\hull=1:ltini(1)\pontos=10
ltini(2)\sp=3:ltini(2)\hull=2:ltini(2)\pontos=20
ltini(3)\sp=4:ltini(3)\hull=3:ltini(3)\pontos=40
ltini(4)\sp=2:ltini(4)\hull=3:ltini(4)\pontos=50

ltini(1)\tx=23:ltini(1)\ty=16:ltini(1)\py=32
ltini(2)\tx=23:ltini(2)\ty=16:ltini(2)\py=32
ltini(3)\tx=15:ltini(3)\ty=24:ltini(3)\py=24
ltini(4)\tx=24:ltini(4)\ty=24:ltini(4)\py=24

ltini(5)\sp=2:ltini(5)\hull=50:ltini(5)\pontos=100
ltini(6)\sp=2:ltini(6)\hull=75:ltini(6)\pontos=125
ltini(7)\sp=4:ltini(7)\hull=100:ltini(7)\pontos=150
ltini(8)\sp=4:ltini(8)\hull=125:ltini(8)\pontos=175

ltini(5)\tx=46:ltini(5)\ty=32:ltini(5)\py=16
ltini(6)\tx=46:ltini(6)\ty=32:ltini(6)\py=16
ltini(7)\tx=30:ltini(7)\ty=48:ltini(7)\py=0
ltini(8)\tx=48:ltini(8)\ty=48:ltini(8)\py=0

ltini(9)\sp=5:ltini(9)\hull=250:ltini(9)\pontos=250
ltini(9)\tx=80:ltini(9)\ty=30:ltini(9)\py=18


; Disparos
NEWTYPE .ltiros
  x.w
  y.w
End NEWTYPE

Dim List ltiro.ltiros(16)

; Disparos Inimigos
NEWTYPE .ltirosini
  x.w
  y.w
End NEWTYPE

Dim List ltiroini.ltirosini(31)

; Premios
NEWTYPE .lpremios
  x.w
  y.w
  tipo.w
  cnt.w
  tmp.w
End NEWTYPE

Dim List lpremio.lpremios(8)

; Explosoes
NEWTYPE .lexplos
  x.w
  y.w
  cnt.w
  fase.w
End NEWTYPE

Dim List lexplo.lexplos(16)

Dim gex(3)
Dim gey(3)

.variaveis

; Estados
; 0 - Titulo
; 1 - Instrucoes
; 2 - Hiscore
; 3 - GetReady
; 4 - Jogo
; 5 - Boss
; 6 - Game Over
; 7 - Fim Jogo
; 8 - Ecran Final
; 9 - Inicializa o Menu

estado=9
counter=0
hiscore=0

joytype=0

; Textos

texto$=""
txtx=0
txty=0

Queue 0,64    ; Queue do Foreground Bitmap - Double Buffer 0
Queue 1,64    ; Queue do Foreground BitMap - Double Buffer 1

Buffer 0,1024 ; Buffer do Background Bitmap - Saturno e Planeta

BIT0 = 0 ; BitMap Foreground - Double Buffer : 0 ou 1

.constantes

#BIT1 = 2 ; BitMap Background
#BIT2 = 3 ; BitMap Shapes
#BIT3 = 4 ; BitMap Menu
#BIT4 = 5 ; BitMap Painel
#PAL = 0  ; Palette

#ECRAN = 256-16
#PANEL = 16

; Versao AGA

#COPPERP = 2 ; Copper Panel
#COPPERJ = 1 ; Copper Jogo
#COPPERM = 0 ; Copper Menu
#COPPERPROFJ = $8  ; 4+4 BitPlanes = 16+16 Cores - Jogo (Dual PlayField)
#COPPERPROFM = $8 ; 8 BitPlanes = 256 Cores - Menu
#PROF = 8  ; 8 BitPlanes = 256 cores
#CORES= 64 ; 64 Cores
#BITPLANES = 4

#CORMAX = 15 ; Numero Maximo de Cores no Background BitMap

#RGBMAX = 255 ; Valor maximo para o RGB
#RGBMED = 127 ; Valor medio para o RGB

#CORPLANETA = 31 ; Index da Cor do Planeta
#CORSATURNO = 26 ; Index da Cor do Saturno


#CORNV1 = 33 ; Index da Cor 1 da Nave
#CORNV2 = 35 ; Index da Cor 2 da Nave

#RGBNV11 = 224 ; RGB 1 da Cor 1 da Nave
#RGBNV12 = 224 ; RGB 2 da Cor 1 da Nave
#RGBNV13 = 128 ; RGB 3 da Cor 1 da Nave

#RGBNV21 = 128 ; RGB 1 da Cor 2 da Nave
#RGBNV22 = 32  ; RGB 2 da Cor 2 da Nave
#RGBNV23 = 0   ; RGB 3 da Cor 2 da Nave

#CORBOSS1 = 4 ; Index da Cor 1 do Boss 1
#CORBOSS2 = 5 ; Index da Cor 1 do Boss 2
#CORBOSS3 = 3 ; Index da Cor 1 do Boss 3
#CORBOSS4 = 1 ; Index da Cor 1 do Boss 4
#CORBOSS5 = 9 ; Index da Cor 1 do Boss 5

#RGBBOSS11 = 32  ; RGB 1 da Cor 1 do Boss 1
#RGBBOSS12 = 160 ; RGB 2 da Cor 1 do Boss 1
#RGBBOSS13 = 192 ; RGB 3 da Cor 1 do Boss 1

#RGBBOSS21 = 64  ; RGB 1 da Cor 1 do Boss 2
#RGBBOSS22 = 160 ; RGB 2 da Cor 1 do Boss 2
#RGBBOSS23 = 0   ; RGB 3 da Cor 1 do Boss 2

#RGBBOSS31 = 0   ; RGB 1 da Cor 1 do Boss 3
#RGBBOSS32 = 0   ; RGB 2 da Cor 1 do Boss 3
#RGBBOSS33 = 192 ; RGB 3 da Cor 1 do Boss 3

#RGBBOSS41 = 192 ; RGB 1 da Cor 1 do Boss 4
#RGBBOSS42 = 32  ; RGB 2 da Cor 1 do Boss 4
#RGBBOSS43 = 0   ; RGB 3 da Cor 1 do Boss 4

#RGBBOSS51 = 64  ; RGB 1 da Cor 1 do Boss 5
#RGBBOSS52 = 64  ; RGB 2 da Cor 1 do Boss 5
#RGBBOSS53 = 192 ; RGB 3 da Cor 1 do Boss 5

#CORRE = 2 ; Distancia entre os InitCopList do Jogo

#COUNTERMAX = 750 ; Tempo maximo para os Menus

#RATETIRO = 25 ; Intervalo de Tempo entre os Disparos da Nave

#RATETIROINIPM = 35 ; Intervalo de Tempo entre os Disparos dos Inimigos
#RATETIROINIBS = 25 ; Intervalo de Tempo entre os Disparos dos Bosses

#RATEINI = 35 ; Intervalo de Tempo entre os Inimigos

#TEMPOBOMBA = 50 ; Intervalo entre as Bombas

#MAXVIDAS = 5  ; Numero Maximo de Vidas
#MAXBOMBAS = 5 ; Numero Maximo de Bombas

#ARMOUR = 100 ; Tempo da Invencibilidade

#PRMTEMPO = 75 ; Tempo que os Premios ficam Disponiveis

; Ficheiro das Shapes

FileBIT$="data/graficos/spr_"+Str$(#CORES)+".lbm"


; Shapes

#nave=0

#tiro=10

#ini1=1
#ini2=2
#ini3=3
#ini4=4

#boss1=5
#boss2=6
#boss3=7
#boss4=8
#boss5=9

#tiroini=11

#prvidas=12
#prtiros=13
#prbombas=14
#prpontos=15

#explosao1=16
#explosao2=17
#explosao3=18
#explosao4=19

#titulo=20

#planeta=21
#saturno=22

; Sons

#fxtiro=0
#fxexplo=1
#fxbomba=2

#fxprvidas=3
#fxprtiros=4
#fxprbombas=5
#fxprpontos=6

; Inicializa os BitMaps, as Shapes e o Sprite
.bitmshapes

; Cria o BitMap das Shapes
BitMap #BIT2,320,175,#BITPLANES ; BitMap Shapes

NPrint "Loading Graphics"

LoadBitMap #BIT2,FileBIT$

InitPalette #PAL,#CORES

LoadPalette #PAL,FileBIT$,0

AGAPalRGB #PAL,0,0,0,0

; Vai buscar o Sprite da Nave

InitShape #nave,16,16,2
LoadShape #nave,"data/graficos/nave.lbm"
GetaSprite #nave,#nave
Free Shape #nave

; Vai buscar as Shapes de 16 cores em AGA ao BitMap

Use BitMap #BIT2

GetaShape #ini1,24,0,23,16
GetaShape #ini2,47,0,23,16
GetaShape #ini3,70,0,15,24
GetaShape #ini4,0,0,24,24

GetaShape #tiro,2,67,1,8

GetaShape #boss1,86,0,46,32
GetaShape #boss2,133,0,46,32
GetaShape #boss3,136,34,30,48
GetaShape #boss4,86,34,48,48
GetaShape #boss5,0,77,80,30

GetaShape #tiroini,0,67,1,8

GetaShape #prvidas,30,63,12,12
GetaShape #prtiros,42,63,12,12
GetaShape #prbombas,54,63,12,12
GetaShape #prpontos,66,63,12,12

GetaShape #explosao1,0,40,16,16
GetaShape #explosao2,16,40,16,16
GetaShape #explosao3,32,40,16,16
GetaShape #explosao4,48,40,16,16

GetaShape #planeta,0,150,24,24
GetaShape #saturno,26,150,28,24

Free BitMap #BIT2

; Le de novo as Shapes mas desta vez com 64 Cores em AGA

BitMap #BIT2,320,156,#PROF
LoadBitMap #BIT2,FileBIT$

; Vai buscar as Shapes de 64 Cores em AGA ao BitMap

Use BitMap #BIT2

GetaShape #titulo,0,130,189,18

GetaShape 32,0,119,8,8 ; Espaco
GetaShape 58,8,119,8,8 ; ":"
GetaShape 33,16,119,8,8 ; "!"
GetaShape 45,24,119,8,8 ; "-"

For n=0 To 9
  GetaShape 48+n,32+(n*8),119,8,8 ; Numeros
Next n

For n=0 To 25
  GetaShape 65+n,n*8,111,8,8 ; Letras
Next n

Free BitMap #BIT2

.copperlists
; Inicializa o CopperList para o Menu

COPPERTYPE.l=#COPPERPROFM ; Bitplanes
COPPERTYPE+$10000 ; AGA colours

InitCopList #COPPERM,44,256,COPPERTYPE,8,#CORES,0 ; Menu

; Inicializa o Copper List para o Jogo

COPPERTYPE.l=#COPPERPROFJ ; Bitplanes
COPPERTYPE+$20 ; Dual Playfield
COPPERTYPE+$10000 ; AGA colours

InitCopList #COPPERJ,44,#ECRAN,COPPERTYPE,8,#CORES,0 ; Jogo

; Inicializa o CopperList para o Painel

COPPERTYPE.l=#COPPERPROFM ; Bitplanes
COPPERTYPE+$10000 ; AGA colours

InitCopList #COPPERP,46+#ECRAN+#CORRE,#PANEL,COPPERTYPE,8,#CORES,0 ; Painel

; Ajusta a Palette em AGA
DisplayControls #COPPERJ,0,$1C00,$33


NPrint "Loading Music and Sounds"

; Le a Musica
LoadModule 0,"data/sons/helico.mod"

; Le os Sons
LoadSound #fxtiro,"data/sons/laser.iff" ; Disparo
LoadSound #fxexplo,"data/sons/eexplode.iff" ; Explosao
LoadSound #fxbomba,"data/sons/pexplode.iff" ; Bomba

LoadSound #fxprvidas,"data/sons/live.iff" ; Premio Vidas
LoadSound #fxprtiros,"data/sons/fire.iff" ; Premio Disparo
LoadSound #fxprbombas,"data/sons/bomb.iff" ; Premio Bomba
LoadSound #fxprpontos,"data/sons/points.iff" ; Premio Pontos

NPrint ""
NPrint "Waiting for disk caches to settle"

Format "00000"

VWait 5*50

; Blitz Mode - Pedal to the Metal, yeahhhhhh :)

BLITZ

; Loop Principal do Jogo
.mainloop

  Select estado
    Case 0
      Gosub menu
    Case 1
      Gosub instrucoes
    Case 2
      Gosub hiscore
    Case 3
      Gosub inicializar
    Case 4
      Gosub loopjogo
    Case 6
      Gosub gameover
    Case 7
      Gosub welldone
    Case 9
      Gosub initmenu
    Case 10
      Goto fim
  End Select

Goto mainloop


; Inicializa o Menu
.initmenu

; Liberta a Memoria dos BitMaps do Jogo
  If joytype<>0
    Free BitMap 0
    Free BitMap 1
    Free BitMap #BIT1
    Free BitMap #BIT4
  End If

; Cria o BitMap Menu
  BitMap #BIT3,320,256,#PROF

  CreateDisplay #COPPERM
  DisplayPalette #COPPERM,#PAL

  Use BitMap #BIT3
  DisplayBitMap #COPPERM,#BIT3

  If joytype=0 Gosub escolhejoystick

  Blit #titulo,50,10

  PlayModule 0

  estado=0

Return


; Escolhe o Tipo de Joystick
.escolhejoystick

  texto$="   PENISOFT PRESENTS"
  txtx=54
  txty=30
  Gosub imprimetexto

  texto$="     SARDONIC AGA"
  txtx=58
  txty=50
  Gosub imprimetexto

  texto$="    PLEASE SELECT"
  txtx=62
  txty=95
  Gosub imprimetexto

  texto$="1 - ONE BUTTON JOYSTICK"
  txtx=54
  txty=120
  Gosub imprimetexto

  texto$="2 - TWO BUTTON JOYSTICK"
  txtx=54
  txty=140
  Gosub imprimetexto

  texto$="COPYRIGHT 2019 PENISOFT"
  txtx=54
  txty=210
  Gosub imprimetexto

  While joytype=0
    If RawStatus($1) Then joytype=1
    If RawStatus($2) Then joytype=2
  Wend

Return


; Menu - Estado = 0
.menu

  counter=0

  Boxf 30,30,290,240,0

  Gosub imprimemenu

  While Joyb(1)<>1

    counter+1

    VWait

    If counter=#COUNTERMAX
      estado=1
      Return
    End If

    If RawStatus($45)
      estado=10
      Return
    End If

  Wend

  estado=3

Return

; Instrucoes - Estado = 1
.instrucoes

  counter=0

  Boxf 30,30,290,240,0

  Gosub imprimeinstrucoes

  While Joyb(1)<>1

    counter+1

    VWait

    If counter=#COUNTERMAX
      estado=2
      Return
    End If

    If RawStatus($45)
      estado=10
      Return
    End If

  Wend

  estado=3

Return

; Hiscore - Estado = 2
.hiscore

  counter=0

  Boxf 30,30,290,240,0

  Gosub imprimehiscore

  While Joyb(1)<>1

    counter+1

    VWait

    If counter=#COUNTERMAX
      estado=0
      Return
    End If

    If RawStatus($45)
      estado=10
      Return
    End If

  Wend

  estado=3

Return

; GameOver - Estado = 6
.gameover

  ClearList lini()     ; Apaga todos os Inimigos
  ClearList ltiro()    ; Apaga todos os Disparos
  ClearList ltiroini() ; Apaga todos os Disparos Inimigos
  ClearList lpremio()  ; Apaga todos os Premios
  ClearList lexplo()   ; Apaga todas as Explosoes

  Gosub initmenu

  counter=0

  Boxf 30,30,290,240,0

  Gosub imprimegameover

  While counter<#COUNTERMAX

    counter+1

    VWait

    If RawStatus($44)
      estado=0
      Return
    End If


  Wend

Return

; Well Done - Estado = 7
.welldone

  ClearList lini()     ; Apaga todos os Inimigos
  ClearList ltiro()    ; Apaga todos os Disparos
  ClearList ltiroini() ; Apaga todos os Disparos Inimigos
  ClearList lpremio()  ; Apaga todos os Premios
  ClearList lexplo()   ; Apaga todas as Explosoes

  Gosub initmenu

  If pontos>hiscore Then hiscore=pontos

  counter=0

  Boxf 30,30,290,240,0

  Gosub imprimewelldone

  While counter<#COUNTERMAX

    counter+1

    VWait

    If RawStatus($44)
      estado=0
      Return
    End If

  Wend

Return


; Jogo: GetReady - Estado = 3
.inicializar

; Liberta a Memoria do BitMap Menu
  Free BitMap #BIT3

; Cria os BitMaps do Jogo
  BIT0=0
  BitMap BIT0,320,312,#BITPLANES   ; BitMap Foreground - Double Buffer 0
  BitMap BIT0+1,320,312,#BITPLANES ; BitMap Foreground - Double Buffer 1

  BitMap #BIT1,320,528,#BITPLANES ; BitMap Background

  BitMap #BIT4,320,16,#PROF      ; BitMap Painel

  BlitzKeys On

  StopModule

; Repoe as cores originais da Nave
  AGAPalRGB #PAL,#CORNV1,#RGBNV11,#RGBNV12,#RGBNV13
  AGAPalRGB #PAL,#CORNV2,#RGBNV21,#RGBNV22,#RGBNV23

; Cria as Palettes
  DisplayPalette #COPPERJ,#PAL
  DisplayPalette #COPPERP,#PAL

; Inicializa as variaveis
  nvx=173
  nvy=224
  nvtiros=0
  nvinven=0
  nvcnt=0
  nvmc=0

  bcky=264
  bckc=1
  sat=1

  vidas=5
  pontos=0
  bombas=5
  nivel=1

  disparos=0
  tipo=0
  tipot=0
  inixi=0
  inixir=Int(Rnd(4))
  inimigos=0
  disparosini=0
  premios=0
  explos=0

  ratebomba=0
  getpremio=0

  dxi=0

  ptx=0
  pty=0
  ptix=0
  ptiy=0
  ptitx=0
  ptity=0
  bossexp=0

  px=0
  py=0
  pc=0

  counter=-1
  estado=4
  factor=0

  inicount=100

  tirocount=#RATETIRO

  tiroinirate=#RATETIROINIPM
  tiroinicount=tiroinirate

; Desenha o Painel
  Gosub imprimepainel

; Desenha o StarField no Background
  Use BitMap #BIT1
  Cls

; Desenha o StarField
  For n=0 To 200
    px=Int(Rnd(240))
    py=Int(Rnd(264))
    pc=Int(Rnd(#CORMAX))+16
    Plot px+40,py,pc
    Plot px+40,py+264,pc
  Next n

  BIT0=1
  Use BitMap BIT0
  Cls

  BIT0=0
  Use BitMap BIT0
  Cls

; Cria os Displays
  CreateDisplay #COPPERJ,#COPPERP

Return

; Loop Principal do Jogo - Estado = 4
.loopjogo

  While estado<>6 AND estado<>7

    If tirocount>0 tirocount-1
    If tiroinicount>0 tiroinicount-1
    If ratebomba>0 ratebomba-1

    Gosub counterjogo

    If disparos>0 Gosub movedisparo

    If inimigos>0 Gosub moveinimigo

    If disparosini>0 Gosub movedisparoinimigo

    If premios>0 Gosub movepremio

    If explos>0 Gosub moveexplosao

    If disparos>0 AND inimigos>0 Gosub verificacolisao1

    If disparosini>0 Gosub verificacolisao2

    If inimigos>0 Gosub verificacolisao3

    If premios>0 Gosub verificacolisao4

    If bossexp>0 Gosub moveexplosaoboss

    Gosub blitshapes

    VWait

    Gosub movebackground

    Gosub movenave

    BIT0=1-BIT0 ; Muda de Bitmap Double Buffer

    If RawStatus($45) estado=6  ; Verifica se o ESC foi premido

  Wend

Return


; Move o BackGround
.movebackground

  DisplayBitMap #COPPERJ,BIT0,15.5,48,#BIT1,15.5,bcky

  bcky-bckc
  bcky=QWrap(bcky,0,264)

  If bcky=263 ; Cria um Saturno ou um Planeta no 1o ecran

    UnBuffer 0
    sat=1-sat

    Use BitMap #BIT1
    px=Rnd(211)+40
    py=240

    If sat=1
      BBlit 0,#saturno,px,py
      AGAPalRGB #PAL,#CORSATURNO,Rnd(#RGBMAX),Rnd(#RGBMED),Rnd(#RGBMAX)
    Else
      BBlit 0,#planeta,px,py
      AGAPalRGB #PAL,#CORPLANETA,Rnd(#RGBMAX),Rnd(#RGBMED),Rnd(#RGBMAX)
    End If

    DisplayPalette #COPPERJ,#PAL
    Use BitMap BIT0

  End If

Return


; Move a Nave
.movenave

  If nvinven=1 ; Se a Nave estiver invencivel alterna-lhe as cores
    If nvmc=1
      AGAPalRGB #PAL,#CORNV1,#RGBNV21,#RGBNV22,#RGBNV23
      AGAPalRGB #PAL,#CORNV2,#RGBNV11,#RGBNV12,#RGBNV13
      DisplayPalette #COPPERJ,#PAL
      nvmc=0
    Else
      AGAPalRGB #PAL,#CORNV1,#RGBNV11,#RGBNV12,#RGBNV13
      AGAPalRGB #PAL,#CORNV2,#RGBNV21,#RGBNV22,#RGBNV23
      DisplayPalette #COPPERJ,#PAL
      nvmc=1
    End If
    nvcnt-1
    If nvcnt=0 nvinven=0
  End If

  nvx+Joyx(1)*2
  nvy+Joyy(1)*2

  nvx=QLimit(nvx,40,264)
  nvy=QLimit(nvy,0,224)

  DisplaySprite #COPPERJ,#nave,nvx,nvy,0

  If Joyb(1)=1 AND tirocount=0

    If nvtiros=0
      ptx=nvx+8
      pty=nvy+40
      Gosub criadisparo
    Else
      ptx=nvx+4
      pty=nvy+40
      Gosub criadisparo
      ptx=nvx+12
      pty=nvy+40
      Gosub criadisparo
    End If

    Sound #fxtiro,1

  End If

  If joytype=1 AND RawStatus($40) AND bombas>0 AND ratebomba=0 Gosub criabomba
  If joytype=2 AND Joyb(1)=2 AND bombas>0 AND ratebomba=0 Gosub criabomba

Return


; Cria disparo
.criadisparo

  If AddItem(ltiro())

    ltiro()\x=ptx
    ltiro()\y=pty

    tirocount=#RATETIRO
    disparos+1

  End If

Return

; Move Disparo
.movedisparo

  ResetList ltiro()

  While NextItem(ltiro())

    ltiro()\y-3

    If ltiro()\y<40
      KillItem ltiro()
      disparos-1
    End If

  Wend

Return


; Cria Inimigo
.criainimigo

  If AddItem(lini())

    lini()\tipo=tipo

    lini()\x=inixi
    lini()\y=ltini(tipo)\py

    lini()\tx=ltini(tipo)\tx
    lini()\ty=ltini(tipo)\ty
    lini()\sp=ltini(tipo)\sp
    lini()\hull=ltini(tipo)\hull
    lini()\pontos=ltini(tipo)\pontos

    inimigos+1
    inicount=#RATEINI

  End If

Return

; Move Inimigo
.moveinimigo

  ResetList lini()

  While NextItem(lini())

    tipo=lini()\tipo

    If tipo<>3 AND tiroinicount=0 Gosub criadisparoini

    If lini()\tipo<5      ; Inimigos

      lini()\y+lini()\sp

      If lini()\y>286
        KillItem lini()
        inimigos-1
      End If

    Else                  ; Bosses

      If lini()\y<48
        lini()\y+lini()\sp

      Else

        If dxi=0
          If lini()\x>30 lini()\x-lini()\sp Else dxi=1
        End If

        If dxi=1
          If lini()\x<289-lini()\tx lini()\x+lini()\sp Else dxi=0
        End If

      End If

     End If

  Wend

Return


; Prepara a Criacao do Disparo Inimigo
.criadisparoini

  factor=Int(Rnd(50))

  If factor>5
    tiroinicount=tirorateini
    Return
  EndIf

  Select tipo

    Case 1
      ptix=lini()\x+11
      ptiy=lini()\y+16
      Gosub criadisparoinimigo

    Case 2
      ptix=lini()\x+7
      ptiy=lini()\y+16
      Gosub criadisparoinimigo
      ptix=lini()\x+15
      ptiy=lini()\y+16
      Gosub criadisparoinimigo

    Case 4
      ptix=lini()\x+12
      ptiy=lini()\y+24
      Gosub criadisparoinimigo

    Case 5
      For t=0 To 3
        ptix=lini()\x+t*15
        ptiy=lini()\y+lini()\ty
        Gosub criadisparoinimigo
      Next t

    Case 6
      For t=0 To 3
        ptix=lini()\x+t*15
        ptiy=lini()\y+lini()\ty
        Gosub criadisparoinimigo
      Next t

    Case 7
      For t=0 To 3
        ptix=lini()\x+t*7
        ptiy=lini()\y+lini()\ty
        Gosub criadisparoinimigo
      Next t

    Case 8
      For t=0 To 5
        ptix=lini()\x+t*8
        ptiy=lini()\y+lini()\ty
        Gosub criadisparoinimigo
      Next t

    Case 9
      For t=0 To 7
        ptix=lini()\x+t*10
        ptiy=lini()\y+lini()\ty
        Gosub criadisparoinimigo
      Next t

  End Select

Return

; Cria Disparo Inimigo
.criadisparoinimigo

  If AddItem(ltiroini())

    ltiroini()\x=ptix
    ltiroini()\y=ptiy

    disparosini+1

  End If

  tiroinicount=tiroinirate

Return

; Move Disparo Inimigo
.movedisparoinimigo

  ResetList ltiroini()

  While NextItem (ltiroini())

    ltiroini()\y+5

    If ltiroini()\y>286
      KillItem ltiroini()
      disparosini-1
    End If

  Wend

Return


; Cria um Premio
.criapremio

  If AddItem(lpremio())

    lpremio()\x=ptix
    lpremio()\y=ptiy
    lpremio()\cnt=#PRMTEMPO
    lpremio()\tmp=2
    lpremio()\tipo=Int(Rnd(4))+1

    If lpremio()\tipo=1 AND vidas=#MAXVIDAS Then lpremio()\tipo=4
    If lpremio()\tipo=2 AND nvtiros=1 Then lpremio()\tipo=4
    If lpremio()\tipo=3 AND bombas=#MAXBOMBAS Then lpremio()\tipo=4

    getpremio=0
    premios+1

  End If

Return

; Move Premio
.movepremio

  ResetList lpremio()

  While NextItem (lpremio())

    lpremio()\tmp-1

    If lpremio()\tmp=0

      lpremio()\tmp=2
      lpremio()\y+1
      lpremio()\cnt-1

      If lpremio()\y>286 OR lpremio()\cnt=0
        KillItem lpremio()
        premios-1
      End If

    EndIf

  Wend

Return


; Cria Explosao
.criaexplosao

  If AddItem(lexplo())

    lexplo()\x=ptix
    lexplo()\y=ptiy
    lexplo()\cnt=5
    lexplo()\fase=0

    explos+1
    Sound #fxexplo,2

  End If

Return

; Move Explosao
.moveexplosao

  ResetList lexplo()

  While NextItem(lexplo())

    lexplo()\cnt-1

    If lexplo()\cnt=0
      lexplo()\fase+1
      lexplo()\cnt=5
    End If

   If lexplo()\fase=4
      KillItem lexplo()
      explos-1
    End If


  Wend

Return


; Muda a Cor do Boss para Branco quando ha uma bomba
.criaexplosaoboss

  Select tipo
    Case 5
      AGAPalRGB #PAL,#CORBOSS1,#RGBMAX,#RGBMAX,#RGBMAX
    Case 6
      AGAPalRGB #PAL,#CORBOSS2,#RGBMAX,#RGBMAX,#RGBMAX
    Case 7
      AGAPalRGB #PAL,#CORBOSS3,#RGBMAX,#RGBMAX,#RGBMAX
    Case 8
      AGAPalRGB #PAL,#CORBOSS4,#RGBMAX,#RGBMAX,#RGBMAX
    Case 9
      AGAPalRGB #PAL,#CORBOSS5,#RGBMAX,#RGBMAX,#RGBMAX
  End Select

  bossexp=10
  tipot=tipo
  DisplayPalette #COPPERJ,#PAL

Return

; Move Explosao Boss ou devolve a Cor original do Boss
.moveexplosaoboss

  bossexp-1

  If bossexp=0

    Select tipot
      Case 5
        AGAPalRGB #PAL,#CORBOSS1,#RGBBOSS11,#RGBBOSS12,#RGBBOSS13
      Case 6
        AGAPalRGB #PAL,#CORBOSS2,#RGBBOSS21,#RGBBOSS22,#RGBBOSS23
      Case 7
        AGAPalRGB #PAL,#CORBOSS3,#RGBBOSS31,#RGBBOSS32,#RGBBOSS33
      Case 8
        AGAPalRGB #PAL,#CORBOSS4,#RGBBOSS41,#RGBBOSS42,#RGBBOSS43
      Case 9
        AGAPalRGB #PAL,#CORBOSS5,#RGBBOSS51,#RGBBOSS52,#RGBBOSS53
    End Select

    DisplayPalette #COPPERJ,#PAL

  End If

Return


; Cria uma Grande Explosao para os Bosses quando Morrem
.criagrandeexplosao

  Select tipo
    Case 5
      gex(0)=ptix-1 :gey(0)=ptiy+4
      gex(1)=ptix+11:gey(1)=ptiy-8
      gex(2)=ptix+11:gey(2)=ptiy+16
      gex(3)=ptix+23:gey(3)=ptiy+4
      AGAPalRGB #PAL,#CORBOSS1,#RGBBOSS11,#RGBBOSS12,#RGBBOSS13
    Case 6
      gex(0)=ptix-1 :gey(0)=ptiy+4
      gex(1)=ptix+11:gey(1)=ptiy-8
      gex(2)=ptix+11:gey(2)=ptiy+16
      gex(3)=ptix+23:gey(3)=ptiy+4
      AGAPalRGB #PAL,#CORBOSS2,#RGBBOSS21,#RGBBOSS22,#RGBBOSS23
    Case 7
      gex(0)=ptix:gey(0)=ptiy-8
      gex(1)=ptix:gey(1)=ptiy+8
      gex(2)=ptix:gey(2)=ptiy+24
      gex(3)=ptix:gey(3)=ptiy+40
      AGAPalRGB #PAL,#CORBOSS3,#RGBBOSS31,#RGBBOSS32,#RGBBOSS33
    Case 8
      gex(0)=ptix:   gey(0)=ptiy
      gex(1)=ptix+24:gey(1)=ptiy
      gex(2)=ptix   :gey(2)=ptiy+24
      gex(3)=ptix+24:gey(3)=ptiy+24
      AGAPalRGB #PAL,#CORBOSS4,#RGBBOSS41,#RGBBOSS42,#RGBBOSS43
    Case 9
      gex(0)=ptix:   gey(0)=ptiy+2
      gex(1)=ptix+20:gey(1)=ptiy+2
      gex(2)=ptix+40:gey(2)=ptiy+2
      gex(3)=ptix+60:gey(3)=ptiy+2
      AGAPalRGB #PAL,#CORBOSS5,#RGBBOSS51,#RGBBOSS52,#RGBBOSS53
  End Select

  DisplayPalette #COPPERJ,#PAL

  For n=0 To 3
    If AddItem(lexplo())
      lexplo()\x=gex(n)
      lexplo()\y=gey(n)
      lexplo()\cnt=10
      lexplo()\fase=0
      explos+1
    End If
  Next n

  Sound #fxbomba,4

Return


; Verificao Colisao entre Disparos e Inimigos
.verificacolisao1

  ResetList ltiro()

  While NextItem (ltiro()) ; Percorre todos os Disparos

    colisao=0
    ResetList lini()

    While NextItem (lini()) AND colisao=0  ; Percorre todos os Inimigos ate haver colisao

      If RectsHit (ltiro()\x,ltiro()\y,1,8,lini()\x,lini()\y,lini()\tx,lini()\ty)

        colisao=1

        lini()\hull-1

        If lini()\tipo>4 AND lini()\hull>0 ; Se for um Boss e ainda estiver vivo
          Sound #fxexplo,2

          ptix=ltiro()\x    ; Cria Explosao
          ptiy=ltiro()\y
          Gosub criaexplosao

          pontos+5
          Gosub atualizapontos
      End If


        If lini()\hull=0 ; Verifica se e altura de terminar o Inimigo

          If lini()\tipo<5 ; Inimigos

            getpremio+1

            If getpremio=4  ; Cria Premio
              ptix=lini()\x
              ptiy=lini()\y
              Gosub criapremio
            EndIf

            ptix=lini()\x   ; Cria Explosao
            ptiy=lini()\y
            Gosub criaexplosao

          Else             ; Bosses

            tipo=lini()\tipo  ; Cria uma grande explosao
            ptix=lini()\x
            ptiy=lini()\y
            ptitx=lini()\tx
            ptity=lini()\ty
            Gosub criagrandeexplosao

            If tipo=9  ; Se for o Boss Final passa para o WellDone
              estado=7
            Else
              estado=4 ; Se nao for o Boss Final passa para o jogo
              nivel+1
              Gosub atualizanivel
            End If

          End If

          pontos+lini()\pontos
          KillItem lini()
          inimigos-1
          Gosub atualizapontos

        End If

      End If

    Wend

    If colisao=1
      KillItem ltiro()
      disparos-1
    End If

  Wend

Return


; Verifica Colisao entre a Nave e os Disparos Inimigos
.verificacolisao2

  ResetList ltiroini()

  While NextItem (ltiroini()) ; Percorre todos os Disparos Inimigos

    If RectsHit (ltiroini()\x,ltiroini()\y-48,1,8,nvx,nvy,16,16)

      KillItem ltiroini() ; Apaga o Disparo Inimigo
      disparosini-1

      If nvinven=0 ; Verifica a Invencibilidade da Nave
        nvinven=1
        nvmc=1
        nvcnt=#ARMOUR
        vidas-1
        nvtiros=0
        Gosub atualizavidas
        Sound #fxexplo,2
      End If

    End If

  Wend

Return

; Verifica Colisao entre a Nave e os Inimigos
.verificacolisao3

  ResetList lini()

  While NextItem (lini()) ; Percorre todos os Inimigos

    If RectsHit (lini()\x,lini()\y-48,lini()\tx,lini()\ty,nvx,nvy,16,16)

      If lini()\tipo<5 ; Inimigos

        ptix=lini()\x  ; Cria Explosao
        ptiy=lini()\y
        Gosub criaexplosao

        pontos+lini()\pontos
        KillItem lini() ; Apaga o Inimigo
        inimigos-1
        Gosub atualizapontos

      Else             ; Bosses

        lini()\hull-1

        If lini()\hull=0

          tipo=lini()\tipo  ; Cria uma grande explosao
          ptix=lini()\x
          ptiy=lini()\y
          ptitx=lini()\tx
          ptity=lini()\ty
          Gosub criagrandeexplosao

          If tipo=9  ; Se for o Boss Final passa para o WellDone
              estado=7
          Else
              estado=4 ; Se nao for o Boss Final passa para o jogo
              nivel+1
              Gosub atualizanivel
          End If

          pontos+lini()\pontos
          KillItem lini() ; Apaga o Inimigo
          inimigos-1
          Gosub atualizapontos

        Else

          tipo=lini()\tipo  ; Cria a Cor do Boss para branco
          Gosub criaexplosaoboss

        End If

      End If

      If nvinven=0 ; Verifica a Invencibilidade da Nave
        nvinven=1
        nvmc=1
        nvcnt=#ARMOUR
        nvtiros=0
        vidas-1
        Gosub atualizavidas
        Sound #fxexplo,2
      End If

    End If

  Wend

Return

; Verifica Colisao entre Nave e Premios
.verificacolisao4

  ResetList lpremio()

  While NextItem (lpremio()) ; Percorre todos os Premios

    If RectsHit (lpremio()\x,lpremio()\y-48,12,12,nvx,nvy,16,16)

      Select lpremio()\tipo
        Case 1
          If vidas<#MAXVIDAS vidas+1
          Gosub atualizavidas
          Sound #fxprvidas,8
        Case 2
          nvtiros=1
          Sound #fxprtiros,8
        Case 3
          If bombas<#MAXBOMBAS bombas+1
          Gosub atualizabombas
          Sound #fxprbombas,8
        Case 4
          pontos+30
          Gosub atualizapontos
          Sound #fxprpontos,8
      End Select

      KillItem lpremio() ; Apaga o Premio
      premios-1

    End If

  Wend

Return


; Cria uma Bomba e apaga todos os objetos do ecran
.criabomba

  bombas-1
  ratebomba=#TEMPOBOMBA
  Gosub atualizabombas

  ClearList ltiro()    ; Apaga todos os Disparos
  ClearList ltiroini() ; Apaga todos os Disparos Inimigos

  ResetList lini()

  While NextItem (lini()) ; Percorre todos os Inimigos

    If lini()\tipo<5 ; Inimigos

      ptix=lini()\x  ; Cria Explosao
      ptiy=lini()\y
      Gosub criaexplosao

      pontos+lini()\pontos
      KillItem lini() ; Apaga o Inimigo
      inimigos-1
      Gosub atualizapontos

    Else             ; Bosses

      lini()\hull-5

      If lini()\hull<=0

        tipo=lini()\tipo  ; Cria uma grande explosao
        ptix=lini()\x
        ptiy=lini()\y
        ptitx=lini()\tx
        ptity=lini()\ty
        Gosub criagrandeexplosao

        If tipo=9  ; Se for o Boss Final passa para o WellDone
          estado=7
        Else
          estado=4 ; Se nao for o Boss Final passa para o Jogo
          nivel+1
          Gosub atualizanivel
        End If

        pontos+lini()\pontos
        KillItem lini() ; Apaga o Inimigo
        inimigos-1
        Gosub atualizapontos

      Else

        tipo=lini()\tipo  ; Cria a Cor do Boss para branco
        Gosub criaexplosaoboss

      End If

    End If

  Wend

  Sound #fxbomba,4

Return


; Imprime todos as Shapes no BitMap respetivo - Foreground
.blitshapes

  UnQueue BIT0     ; Apaga as Shapes Atuais na Queue Respetiva

  Use BitMap BIT0  ; Seleciona o BitMap Respetivo - Foreground

; Inimigos
  ResetList lini()
  While NextItem(lini())
    QBlit BIT0,lini()\tipo,lini()\x,lini()\y
  Wend

; Disparos
  ResetList ltiro()
  While NextItem(ltiro())
    QBlit BIT0,#tiro,ltiro()\x,ltiro()\y
  Wend

; Disparos Inimigos
  ResetList ltiroini()
  While NextItem (ltiroini())
    QBlit BIT0,#tiroini,ltiroini()\x,ltiroini()\y
  Wend

; Premios
  ResetList lpremio()
  While NextItem (lpremio())
    QBlit BIT0,lpremio()\tipo+11,lpremio()\x,lpremio()\y
  Wend

; Explosoes
 ResetList lexplo()
  While NextItem(lexplo())
    QBlit BIT0,lexplo()\fase+#explosao1,lexplo()\x,lexplo()\y
  Wend

Return

; Imprime Textos no Ecran
.imprimetexto

  For n=1 To Len(texto$)
    Blit Asc(Mid$(texto$,n,1)),txtx+n*8,txty
  Next n

Return

; Imprime o Menu
.imprimemenu

  texto$="JOYSTICK : DIRECTIONS"
  txtx=52
  txty=50
  Gosub imprimetexto

  If joytype=1
    texto$=" FIRE BUTTON : FIRE"
    txtx=56
    txty=65
    Gosub imprimetexto

    texto$="    SPACE : BOMB"
    txtx=56
    txty=80
    Gosub imprimetexto
  Else
    texto$="FIRE 1 : FIRE"
    txtx=86
    txty=65
    Gosub imprimetexto

    texto$="FIRE 2 : BOMB"
    txtx=86
    txty=80
    Gosub imprimetexto
  End If

  texto$="FIRE TO START GAME"
  txtx=64
  txty=120
  Gosub imprimetexto

  texto$="ESCAPE TO EXIT"
  txtx=80
  txty=135
  Gosub imprimetexto

  texto$="CODE AND GRAPHICS : MADAXE"
  txtx=38
  txty=175
  Gosub imprimetexto

  texto$="MUSIC : MOD SYNTH BY FRED"
  txtx=42
  txty=190
  Gosub imprimetexto

  texto$="COPYRIGHT 2019 PENISOFT"
  txtx=50
  txty=230
  Gosub imprimetexto

Return

; Imprime as Instrucoes
.imprimeinstrucoes

  Blit #ini1,38,50
  Blit #ini2,38,70
  Blit #ini3,42,90
  Blit #ini4,38,120

  texto$="FIGHTER I  - 10 POINTS"
  txtx=68
  txty=54
  Gosub imprimetexto

  texto$="FIGHTER II - 20 POINTS"
  txtx=68
  txty=74
  Gosub imprimetexto

  texto$="STEALTH    - 30 POINTS"
  txtx=68
  txty=98
  Gosub imprimetexto

  texto$="BOMBER     - 50 POINTS"
  txtx=68
  txty=128
  Gosub imprimetexto

  Blit #prtiros,95,160
  Blit #prpontos,95,180
  Blit #prbombas,95,200
  Blit #prvidas,95,220

  texto$="EXTRA FIRE"
  txtx=110
  txty=162
  Gosub imprimetexto

  texto$="EXTRA POINTS"
  txtx=110
  txty=182
  Gosub imprimetexto

  texto$="EXTRA BOMB"
  txtx=110
  txty=202
  Gosub imprimetexto

  texto$="EXTRA LIVE"
  txtx=110
  txty=222
  Gosub imprimetexto

Return

; Imprime o Hiscore
.imprimehiscore

  texto$="HISCORE OF THE DAY"
  txtx=68
  txty=100
  Gosub imprimetexto

  texto$=Str$(hiscore)
  txtx=114
  txty=120
  Gosub imprimetexto

Return

; Imprime o Game Over
.imprimegameover

  texto$="GAME OVER !!"
  txtx=90
  txty=80
  Gosub imprimetexto

  If pontos>hiscore
    hiscore=pontos
    texto$="  BUT YOU ACHIEVED"
    txtx=60
    txty=130
    Gosub imprimetexto
    texto$="  AN HISCORE YES!!"
    txtx=60
    txty=150
    Gosub imprimetexto
  Else
    texto$="NO HISCORE ACHIEVED"
    txtx=60
    txty=130
    Gosub imprimetexto
    texto$="  MAYBE NEXT TIME"
    txtx=60
    txty=150
    Gosub imprimetexto
  End If

  texto$="PRESS RETURN TO MAIN MENU"
  txtx=40
  txty=220
  Gosub imprimetexto


Return

; Imprime o Well Done
.imprimewelldone

  texto$="WELL DONE !!"
  txtx=90
  txty=60
  Gosub imprimetexto

  texto$="YOU DEFEATED THE EVIL"
  txtx=50
  txty=90
  Gosub imprimetexto
  texto$="SARDONIC AND ITS ARMY"
  txtx=50
  txty=100
  Gosub imprimetexto

  texto$="THANK YOU FOR PLAYING"
  txtx=50
  txty=130
  Gosub imprimetexto
  texto$="   THIS LITTE GAME"
  txtx=50
  txty=140
  Gosub imprimetexto

  texto$="   SEE YOU SOON ON"
  txtx=50
  txty=170
  Gosub imprimetexto
  texto$="   ATARI ST VERSION"
  txtx=46
  txty=180
  Gosub imprimetexto

  texto$="PRESS RETURN TO MAIN MENU"
  txtx=40
  txty=220
  Gosub imprimetexto


Return

; Imprime o Painel
.imprimepainel

; Desenha o Painel
  Use BitMap #BIT4
  Cls
  Box 40,0,93,15,4   ; Pontos
  Box 41,1,92,14,7
  Box 95,0,155,15,4 ; Vidas
  Box 96,1,154,14,7
  Box 157,0,217,15,4 ; Bombas
  Box 158,1,216,14,7
  Box 219,0,279,15,4 ; Nivel
  Box 220,1,278,14,7

; Pontos
  Boxf 48,5,86,10,0
  texto$=Str$(pontos)
  txtx=40
  txty=5
  Gosub imprimetexto

; Vidas
  texto$="LIVES"
  txtx=92
  txty=5
  Gosub imprimetexto
  Blit 48+vidas,144,5

; Bombas
  texto$="BOMBS"
  txtx=154
  txty=5
  Gosub imprimetexto
  Blit 48+bombas,206,5

  texto$="LEVEL"
  txtx=216
  txty=5
  Gosub imprimetexto
  Blit 48+nivel,268,5

  DisplayBitMap #COPPERP,#BIT4

Return

; Atualiza os Pontos no Painel
.atualizapontos

  Use BitMap #BIT4

  Boxf 48,5,86,10,0

  texto$=Str$(pontos)
  txtx=40
  txty=5
  Gosub imprimetexto

Return

; Atualiza as Vidas no Painel
.atualizavidas

;If vidas>=0
  Use BitMap #BIT4
  Boxf 144,5,151,10,0
  Blit 48+vidas,144,5
;End If

  If vidas=0 Then estado=6

Return

; Atualiza as Bombas no Painel
.atualizabombas

  Use BitMap #BIT4
  Boxf 206,5,213,10,0
  Blit 48+bombas,206,5

Return

; Atualiza o Nivel no Painel
.atualizanivel

  Use BitMap #BIT4
  Boxf 268,5,275,10,0
  Blit 48+nivel,268,5

Return


; Contador do Jogo
.counterjogo

  If estado=4

    inicount-1
;    counter+1

    If inicount=0

      counter+1

      tipo=ltipoini\tipoini[counter]
      inixi=linix(inixir)\inix[counter]

      If tipo>0 Gosub criainimigo

      inicount=#RATEINI

      If tipo>4
        estado=5
        tiroinirate=#RATETIROINIBS
        bckc=2
      Else
        tiroinirate=#RATETIROINIPM
        bckc=1
      End If

    End If

  End If

Return


; Sai do Jogo e volta para a WB ou para o AmigaDOS
.fim

  Free BitMap 0
  Free BitMap 1
  Free BitMap #BIT1
  Free BitMap #BIT2
  Free BitMap #BIT3
  Free BitMap #BIT4

  Free Palette 0

  Free Sprite #nave

  StopModule

  Free Module 0

  Free Sound #fxtiro
  Free Sound #fxexplo
  Free Sound #fxbomba
  Free Sound #fxprvidas
  Free Sound #fxprtiros
  Free Sound #fxprbombas
  Free Sound #fxprpontos

  AMIGA

  NPrint ""
  NPrint "Thank you for playing this little game"
  NPrint ""

.fimfim

End

