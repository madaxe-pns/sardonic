.org 52000

 jp inicializar

;variaveis auxiliares
attr .db 0
sai .db 0
fonte .dw 29500
scrfinal .dw 45000

ratecnt .db 20
counter .dw 0

tiros .db 0
vidas .db 5
nivel .db 1
ratebb .db 0
bombas .db 5

score .dw 0
tscore .db "00000"

hiscore .dw 0
thiscore .db 16,7,17,0,22,12,13,"00000"
tathiscore .db 0

;Estados
;0-Titulo
;1-Instrucoes
;2-Hiscore
;3-GetReady
;4-Jogo
;5-Boss
;6-GameOver
;7-FimJogo
;8-Écran Final
;9-Imprime Título

mudanivel .db 0
estado .db 0

;ltipoini .db 255,0,1,0,2,0,3,0,255,4,255,0,1,0,2,0,3,0,255,5,255,0,1,0,2,0,3,0,255,6,255,0,1,0,2,0,3,0,255,7,255,0,1,0,2,0,3,0,255,8,255
ltipoini .dw 32000
tipoini .db 255
linix00 .dw 33000
linix01 .dw 34000
linix02 .dw 35000
linix03 .dw 36000
linix .dw 0
inix .db 0


;textos						  12345678901234567890123456789012
texto01 .db 16,7,17,0,22,5,7,"Q - UP , A - DOWN"
		.db 16,7,17,0,22,6,6,"O - LEFT , P - RIGHT"
		.db 16,7,17,0,22,8,4,"SPACE - FIRE , X - BOMB"
		.db 16,7,17,0,22,10,7,"CAPS SHIFT TO QUIT"
		.db 16,7,17,0,22,13,9,"FIRE TO START"
		.db 16,7,17,0,22,17,3,"CODE AND GRAPHICS : MADAXE"
		.db 16,7,17,0,22,19,3,"MUSIC : MOD SYNTH BY FRED"
tatxt01 .db 0
texto02 .db 16,7,17,0,22,1,7,"(C) 2019 PENISOFT"
tatxt02 .db 0

texto11 .db 16,7,17,0,22,5,7,"FIGHTER I  : 10 POINTS"
		.db 16,7,17,0,22,8,7,"FIGHTER II : 20 POINTS"
		.db 16,7,17,0,22,12,7,"STEALTH    : 40 POINTS"
		.db 16,7,17,0,22,16,7,"BOMBER     : 50 POINTS"
		.db 16,7,17,0,22,21,5,"EXTRA FIRE"
		.db 16,7,17,0,22,21,19,"EXTRA POINTS"
tatxt11 .db 0

texto12 .db 16,7,17,0,22,1,5,"EXTRA BOMB"
		.db 16,7,17,0,22,1,19,"EXTRA LIVE"
tatxt12 .db 0

texto30 .db 16,7,17,0,22,10,7,"HISCORE OF THE DAY"
tatxt30 .db 0
texto31 .db 16,7,17,0,22,10,7,"GAME OVER!"
tatxt31 .db 0
texto32 .db 16,7,17,0,22,11,6,"WELL DONE!!"
tatxt32 .db 0

texto .dw 0
tatxt .db 0
ptxtx .db 0
ptxty .db 0
attxt .db 0

;Lista Dados Naves Inimigas
ldoffi1 .dw 25576,25696,25816,25928,26100,26292,26484,26676,26964
ldpiiy .db 254,254,253,253,252,252,250,250,252
ldtaixf1 .db 3,3,2,3,6,6,4,6,10
ldtaiyf1 .db 2,2,3,3,4,4,6,6,4
ldatti .db 5,4,7,3,5,4,7,3,6
ldspeedi .db 1,1,0,2,2,2,1,1,0
ldhulli .db 0,1,2,2,50,75,100,125,200
ldpontosi .db 10,20,40,50,100,125,150,175,250

;lista naves inimigas
inimigo .db 0
inimigos .db 0
lpiix .db 0,0,0,0,0,0
lpiiy .db 0,0,0,0,0,0
loffi1 .dw 0,0,0,0,0,0
ltaix .db 0,0,0,0,0,0
ltaiy .db 0,0,0,0,0,0
lpifx .db 0,0,0,0,0,0
lpify .db 0,0,0,0,0,0
latti .db 0,0,0,0,0,0
ltipoi .db 0,0,0,0,0,0
lspeedi .db 0,0,0,0,0,0
lspeedicnt .db 0,0,0,0,0,0
lhullicnt .db 0,0,0,0,0,0
lpontosi .db 0,0,0,0,0,0

;nave inimiga
piix .db 0
piiy .db 0
offi1 .dw 0
taix .db 0
taiy .db 0
pifx .db 0
pify .db 0
atti .db 0
tipoi .db 0
speedi .db 0
speedicnt .db 0
hullicnt .db 0
pontosi .db 0
dix .db 0


;lista tiros
rated .db 0
disparo .db 0
disparos .db 0
lptix .db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
lptiy .db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
lofft1 .dw 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

;tiro
ptix .db 0
ptiy .db 0
offt1 .dw 25200
offt2 .dw 25248
tatx .db 1
taty .db 1
attt .db 7


;lista tiros inimigos
ratedini .db 0
disparoini .db 0
disparosini .db 0
lptiniix .db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
lptiniiy .db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

;tiro inimigo
ptiniix .db 0
ptiniiy .db 0
offtini1 .dw 25272
tatinix .db 1
tatiniy .db 1
atttini .db 6


;cores dos prémios
;01 - bomba - vermelho - 66 (02)
;02 - tiros - cyan - 69 (05)
;03 - vidas - verde - 68 (04)
;04 - pontos - mangenta - 67 (03)

;Lista Dados premios
ldoffpr .dw 27316,27324,27332,27340
ldattpr .db 66,69,68,67

;lista premios
premio .db 0
premios .db 0
loffpr .dw 0,0,0,0,0,0,0,0,0,0
lattpr .db 0,0,0,0,0,0,0,0,0,0
lpprix .db 0,0,0,0,0,0,0,0,0,0
lppriy .db 0,0,0,0,0,0,0,0,0,0
ltipopr .db 0,0,0,0,0,0,0,0,0,0
lspeedprcnt .db 0,0,0,0,0,0,0,0,0,0
ltempoprcnt .db 0,0,0,0,0,0,0,0,0,0

;premios
pprix .db 0
ppriy .db 0
offpr .dw 0
taprx .db 1
tapry .db 1
attpr .db 0
tipopr .db 0
speedpr .db 9
speedprcnt .db 0
tempopr .db 99
tempoprcnt .db 0


;lista explosoes
explo .db 0
explos .db 0
lpexplox .db 0,0,0,0,0,0,0,0,0,0
lpexploy .db 0,0,0,0,0,0,0,0,0,0
lattexplo .db 0,0,0,0,0,0,0,0,0,0
ltempoexplocnt .db 0,0,0,0,0,0,0,0,0,0

;explosao
pexplox .db 0
pexploy .db 0
offexplo .dw 27284
taexplox .db 2
taexploy .db 2
attexplo .db 0
tempoexplo .db 0
tempoexplocnt .db 0


;sprite
pos .dw 0
posa .dw 0
psiya .db 0
psix .db 0
psiy .db 0
offs .dw 0
offs2 .dw 0
tasx .db 0
tasy .db 0
psfx .db 0
psfy .db 0
atts .db 0


;nave
pnix .db 16
pniy .db 22
offn1 .dw 25000
tanx .db 2
tany .db 2
pnfx .db 17
pnfy .db 23
attn .db 6
invencivel .db 0

;título
titulo .dw 27500

;painel
painel1 .dw 28100
painel2 .dw 28548
painel3 .dw 28996

;bombas
pbombas .dw 27884

;vidas
pvidas .dw 27900

;niveis
nivel1 .dw 27916
nivel2 .dw 27932
nivel3 .dw 27948
nivel4 .dw 27964
nivel5 .dw 27980

;niveis pequenos
nivel1p .dw 27996
nivel2p .dw 28012
nivel3p .dw 28028
nivel4p .dw 28044
nivel5p .dw 28060


;dados da música
musica .dw 38000

fine .dw 37500
course .dw 37610
mixer .dw 37720
volume .dw 37830

;dados dos canais de música
fa .db 0
ca .db 0
ma .db 0
va .db 0
fb .db 0
cb .db 0
mb .db 0
vb .db 0
fc .db 0
cc .db 0
mc .db 0
vc .db 0

ratemus .dw 1000
countermus .dw 0

sfx01 .db 0
sfx01cnt .db 0

sfx02 .db 0
sfx02cnt .db 0

sfx0200f .db 190
sfx0200c .db 0

sfx0201f .db 125
sfx0201c .db 1

sfx0202f .db 95
sfx0202c .db 0

sfx0203f .db 63
sfx0203c .db 0

sfx02f .db 0
sfx02c .db 0

;portos do AY-3-8912
ayctrl equ 65533
aydata equ 49149



;loop principal
inicializar:

 ld hl,0
 ld (hiscore),hl

 ld hl,0
 ld (counter),hl

 ld a,9
 ld (estado),a

 ld hl,23606 ;aponta para a fonte de caracteres
 ld (hl),60
 ld hl,23607
 ld (hl),114 

 call inicializamusica

linicializar:

 ld a,(estado)

 cp 0
 jp z, estado0 ;título

 cp 1
 jp z, estado1 ;instruções

 cp 2
 jp z, estado2 ;redorde

 cp 3
 jp z, estado3 ;get ready

 cp 4
 jp z, estado4 ;jogo

 cp 6
 jp z, estado6 ;game over

 cp 7
 jp z, estado7 ;jogo completado

 cp 8
 jp z, estado8 ;jogo completado - écran final

 cp 9
 jp z, estado9 ;apaga o écran e imprime o título

estado0:
 call mainlooptitulo ;título
 jp linicializar

estado1:
 call instrucoes ;instruções
 jp linicializar

estado2:
 call recordedodia ;redorde
 jp linicializar

estado3:
 call getready ;get ready
 jp linicializar

estado4:
 call mainloopjogo ;jogo
 jp linicializar

estado6:
 call gameover ;game over
 jp linicializar

estado7:
 call welldone ;jogo completado
 jp linicializar

estado8:
 call ecranfinal ;jogo completado - écran final
 jp linicializar

estado9:
 call printtitulo ;apaga o écran e imprime o título
 jp linicializar

fiminicializar:
 jp linicializar



;apaga o écran e imprime o título - estado=9
printtitulo

 call limpaecran

;título
 ld hl,(titulo)
 ld (offs),hl
 ld a,8
 ld (psix),a
 ld a,0
 ld (psiy),a
 ld a,16
 ld (tasx),a
 ld a,3
 ld (tasy),a
 ld a,6
 ld (atts),a
 call printsprite

 ;vai para o título
 ld a,0
 ld (estado),a

 ret


;main loop do título - estado=0
mainlooptitulo:

 call printmenu

 ld hl,5000
 ld (counter),hl

 ld a,0
 ld (sai),a

mainlooptitulo2:

 call ratecountermusica ;rate contador do player da música
 call playermusica ;player da música

 call ratecounterjogo ;rate contador do jogo

 call vstartgame ;verifica tecla de começo de jogo

 ld a,(sai)
 cp 1
 jr z, mainlooptitulo3 ;vai para o get ready

 ld a,(ratecnt)
 cp 0
 jp nz, mainlooptitulo2

 ld a,20
 ld (ratecnt),a

 ld hl,(counter)
 ld d,0
 ld e,1
 sbc hl,de
 jp z, mainlooptitulo1 ;vai para as instruções
 ld (counter),hl
 jp mainlooptitulo2

mainlooptitulo1: ;vai para as instruções
 ld a,1
 ld (estado),a
 jp saimainlooptitulo

mainlooptitulo3: ;vai para o get ready
 ld a,3
 ld (estado),a

saimainlooptitulo:
 ret


;verifica se foi primido a tecla de começo de jogo
vstartgame:

;verifica se o Space foi primido
 ld bc,32766
 in a,(c)
 bit 0,a
 jr nz,fimvstartgame
 ld a,1
 ld (sai),a
fimvstartgame:
 ret


;instrucoes - estado=1
instrucoes:

 call printinstrucoes

 ld hl,5000
 ld (counter),hl

 ld a,0
 ld (sai),a

instrucoes2:

 call ratecountermusica ;rate contador do player da música
 call playermusica ;player da música

 call ratecounterjogo; rate contador do jogo

 call vstartgame ; verifica tecla de começo de jogo

 ld a,(sai)
 cp 1
 jr z, instrucoes4 ;vai para o get ready

 ld a,(ratecnt)
 cp 0
 jp nz, instrucoes2

 ld a,20
 ld (ratecnt),a

 ld hl,(counter)
 ld d,0
 ld e,1
 sbc hl,de
 jp z, instrucoes3 ;vai para o recorde do dia
 ld (counter),hl
 jp instrucoes2

instrucoes3: ;vai para o recorde do dia
 ld a,2
 ld (estado),a
 jp saiinstrucoes

instrucoes4: ;vai para o get ready
 ld a,3
 ld (estado),a

saiinstrucoes:
 ret


;recorde do dia - estado=2
recordedodia:

 call printrecorde

 ld hl,5000
 ld (counter),hl

 ld a,0
 ld (sai),a

recordedodia2:

 call ratecountermusica ;rate contador do player da música
 call playermusica ;player da música

 call ratecounterjogo; rate contador do jogo

 call vstartgame ; verifica tecla de começo de jogo

 ld a,(sai)
 cp 1
 jr z, recordedodia3 ;vai para o get ready

 ld a,(ratecnt)
 cp 0
 jp nz, recordedodia2

 ld a,20
 ld (ratecnt),a

 ld hl,(counter)
 ld d,0
 ld e,1
 sbc hl,de
 jp z, recordedodia0 ;vai para o título
 ld (counter),hl
 jp recordedodia2

recordedodia0: ;vai para o título
 ld a,0
 ld (estado),a
 jp sairecordedodia

recordedodia3: ;vai para o get ready
 ld a,3
 ld (estado),a

sairecordedodia:
 ret


;quando se completa o jogo - estado=7
welldone:

 call printwelldone
 call atualizahiscore

 ld hl,5000
 ld (counter),hl

 ld a,0
 ld (sai),a

welldone2:
 call ratecounterjogo; rate contador do jogo

 ld a,(ratecnt)
 cp 0
 jp nz, welldone2

 ld a,20
 ld (ratecnt),a

 ld hl,(counter)
 ld d,0
 ld e,1
 sbc hl,de
 jp z, welldone8 ;vai para o écran final
 ld (counter),hl
 jp welldone2

welldone8: ;vai para o écran final
 ld a,8
 ld (estado),a

 call inicializamusica

 ret


;écran final: quando se completa o jogo - estado=8
ecranfinal:

 ld hl,(scrfinal) ;carrega o écran final
 ld de,16384
 ld bc,6912
 ldir

 ld hl,15000
 ld (counter),hl

 ld a,0
 ld (sai),a

ecranfinal2:

 call ratecountermusica ;rate contador do player da música
 call playermusica ;player da música

 call ratecounterjogo; rate contador do jogo

 call vstartgame ; verifica tecla de começo de jogo

 ld a,(sai)
 cp 1
 jr z, ecranfinal9 ;vai o imprime título e depois para o título

 ld a,(ratecnt)
 cp 0
 jp nz, ecranfinal2

 ld a,20
 ld (ratecnt),a

 ld hl,(counter)
 ld d,0
 ld e,1
 sbc hl,de
 jp z, ecranfinal9 ;vai para o título
 ld (counter),hl
 jp ecranfinal2

ecranfinal9: ;vai o imprime título e depois para o título
 ld a,9
 ld (estado),a

 ret


;quando se perde as vidas todas - estado=6
gameover:

 call printgameover
 call atualizahiscore

 ld hl,5000
 ld (counter),hl

 ld a,0
 ld (sai),a

gameover2:
 call ratecounterjogo; rate contador do jogo

 ld a,(ratecnt)
 cp 0
 jp nz, gameover2

 ld a,20
 ld (ratecnt),a

 ld hl,(counter)
 ld d,0
 ld e,1
 sbc hl,de
 jp z, gameover0 ;vai para o título
 ld (counter),hl
 jp gameover2

gameover0: ;vai para o imprime título e depois o título
 ld a,9
 ld (estado),a

 call inicializamusica

 ret



;get ready : inicializa as variáveis do jogo  - estado=3
getready:

 ld a,0
 ld (sai),a

 ld a,0
 ld (tiros),a
 
 ld a,5
 ld (vidas),a

 ld a,1
 ld (nivel),a

 ld a,0
 ld (mudanivel),a

 ld a,0
 ld (ratebb),a

 ld a,5
 ld (bombas),a

 ld hl,0
 ld (score),hl

 ld a,48
 ld hl,tscore
 ld (hl),a ;1
 inc hl
 ld (hl),a ;2
 inc hl
 ld (hl),a ;3
 inc hl
 ld (hl),a ;4
 inc hl
 ld (hl),a ;5

 ld a,10
 ld (ratecnt),a

 ld hl,0
 ld (counter),hl

 ld a,0
 ld (rated),a

 ld a,0
 ld (disparos),a

 ld a,0
 ld (ratedini),a

 ld a,0
 ld (disparosini),a

 ld a,0
 ld (inimigos),a

 ld a,255
 ld (tipoini),a

 ld a,0
 ld (inix),a

 ld a,0
 ld (premios),a

 ld a,0
 ld (explos),a

 ld a,0
 ld (dix),a

 ld a,16
 ld (pnix),a

 ld a,22
 ld (pniy),a

 ld a,17
 ld (pnfx),a

 ld a,23
 ld (pnfy),a

 ld a,6
 ld (attn),a

 ld a,0
 ld (invencivel),a

 ld a,4 ;vai para o jogo
 ld (estado),a

 call inicializamusica

;limpa o écran
 ld a,7
 ld (attr),a
 call limpaecran

 call printpainel

;sorteia que posição horizontal dos inimigos a usar
randomgetr:
 ld a,r
 cp 4
 jp nc,randomgetr

 cp 0 ;lista 00 de posições horizontais
 jp z,ginix00

 cp 1 ;lista 01 de posições horizontais
 jp z,ginix01

 cp 2 ;lista 02 de posições horizontais
 jp z,ginix02

 cp 3 ;lista 03 de posições horizontais
 jp z,ginix03

ginix00: ;lista 00 de posições horizontais
 ld hl,(linix00)
 ld (linix),hl
 jp fimgetready

ginix01: ;lista 01 de posições horizontais
 ld hl,(linix01)
 ld (linix),hl
 jp fimgetready

ginix02: ;lista 02 de posições horizontais
 ld hl,(linix02)
 ld (linix),hl
 jp fimgetready

ginix03: ;lista 03 de posições horizontais
 ld hl,(linix03)
 ld (linix),hl
 jp fimgetready

fimgetready:
 ret


;principal motor do jogo - estado=4
mainloopjogo:

 ld b,20 ;rotina de pausa do jogo
mainloopjogo2:
 ld a,255
mainloopjogo3:
 dec a
 jr nz,mainloopjogo3
 djnz mainloopjogo2

 call vsair ; verifica tecla de saída

 call ratedisparo; rate disparo

 call ratebomba; ratebomba

 call varreteclado ; varre teclado e move nave

 call ratecounterjogo; rate contador do jogo

 call incrementacounterjogo; incrementa o contador do jogo e cria inimigo

 ld a,(inimigos)
 cp 0
 call nz, moveinimigo ; move inimigo

 ld a,(disparos) 
 cp 0
 call nz, movefire; move disparo

 call ratedisparoinimigo; rate disparo inimigo

 ld a,(inimigos) 
 cp 0
 call nz, criafireini ;cria disparo inimigo

 ld a,(disparosini) 
 cp 0
 call nz, movefireinimigo; move disparo inimigo

 ld a,(premios) 
 cp 0
 call nz, movepremio; move prémio

 ld a,(explos) 
 cp 0
 call nz, moveexplosao; move explosao

 call verificacolisao1 ;colisão entre disparos e inimigos

 ld a,(invencivel) 
 cp 0
 call nz, rateinvencivel; rate invencibilidade da nave

 call verificacolisao2 ;colisão entre a nave e disparos inimigos

 call verificacolisao3 ;colisão entre a nave e inimigos

 call verificacolisao4 ;colisão entre a nave e prémios

 ld a,(sfx01) ;se houver o som de disparo decrementa o volume do Canal B
 cp 1
 call z,ratesfx01

 ld a,(sfx02) ;se houver o som de prémio decrementa o volume do Canal C
 cp 1
 call z,ratesfx02

 halt

 ld a,(estado) ;se o estado for Game Over ou Well Done acaba o jogo
 cp 6
 jp nc, saimainloopjogo

 ld a,(sai) ;se for premido a tecla de quit acaba com o jogo
 cp 1
 jp nz, mainloopjogo

 ld a,6
 ld (estado),a

 ld a,0
 ld (sai),a

saimainloopjogo:
 ret


;sair do jogo e voltar para o título
vsair:

;verifica se o Caps Shift foi primido
 ld bc,65278
 in a,(c)
 bit 0,a
 jr nz,fimvsair
 ld a,1
 ld (sai),a
fimvsair:
 ret



;rate disparo
ratedisparo:

 ld a,(rated)
 cp 0
 jr z, fimratedisparo
 dec a
 ld (rated),a

fimratedisparo:
 ret


;cria disparo
criafire:

 ld a,(rated)
 cp 0
 jp nz, saicriafire

 ld a,(disparos)
 cp 16
 jp z,saicriafire

 call somdisparo

 ld a,(tiros)
 cp 1
 jp z,segundotiro

;apenas um tiro
 ld a,(disparos)
 inc a
 ld (disparos),a

;cria dados do tiro
 ld a,(pniy) ;ptiy
 sub 1
 ld (ptiy),a
 ld a,(pnix) ;ptix
 ld (ptix),a

;coloca dados dos tiros na lista
 ld a,(disparos)
 dec a
 ld d,0
 ld e,a

 ld hl,lptiy ;ptiy
 add hl,de
 ld a,(ptiy)
 ld (hl),a
 ld hl,lptix ;ptix
 add hl,de
 ld a,(ptix)
 ld (hl),a

 ld a,(disparos) ;offt1
 dec a
 ld d,0
 ld e,a
 sla e

 ld hl,lofft1 ;offt1
 add hl,de
 push de
 ld de,(offt1)
 ld a,e
 ld (hl),a
 inc hl
 ld a,d
 ld (hl),a
 pop de

 jp fimcriafire

;dois tiros
segundotiro:

;primeiro tiro
 ld a,(disparos)
 inc a
 ld (disparos),a

 ld a,(pniy) ;ptiy
 sub 1
 ld (ptiy),a
 ld a,(pnix) ;ptix
 ld (ptix),a

;coloca dados do primeiro tiro na lista
 ld a,(disparos)
 dec a
 ld d,0
 ld e,a

 ld hl,lptiy ;ptiy
 add hl,de
 ld a,(ptiy)
 ld (hl),a
 ld hl,lptix ;ptix
 add hl,de
 ld a,(ptix)
 ld (hl),a

 ld a,(disparos) ;offt2
 dec a
 ld d,0
 ld e,a
 sla e

 ld hl,lofft1 ;offt2
 add hl,de
 push de
 ld de,(offt2)
 ld a,e
 ld (hl),a
 inc hl
 ld a,d
 ld (hl),a
 pop de

;segundo tiro
 ld a,(disparos)
 inc a
 ld (disparos),a

 ld a,(pniy) ;ptiy
 sub 1
 ld (ptiy),a
 ld a,(pnix) ;ptix
 inc a
 ld (ptix),a

;coloca dados do segundo tiro na lista
 ld a,(disparos)
 dec a
 ld d,0
 ld e,a

 ld hl,lptiy ;ptiy
 add hl,de
 ld a,(ptiy)
 ld (hl),a
 ld hl,lptix ;ptix
 add hl,de
 ld a,(ptix)
 ld (hl),a

 ld a,(disparos) ;offt2
 dec a
 ld d,0
 ld e,a
 sla e

 ld hl,lofft1 ;offt2
 add hl,de
 push de
 ld de,(offt1)
 ld a,e
 ld (hl),a
 inc hl
 ld a,d
 ld (hl),a
 pop de

fimcriafire:
 ld a,6
 ld (rated),a

saicriafire:
 ret


; move disparo
movefire:

 ld a,0
 ld (disparo),a

 ld a,(disparos)

lmovefire:
 push af

 ld a,(disparo)
 ld d,0
 ld e,a

;dados atuais
 ld a,0
 ld (attr),a
 ld hl,lptiy ;ptiy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lptix ;ptix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld a,(tatx) ;tatx
 ld (tasx),a
 ld a,(taty);taty
 ld (tasy),a

 push de
 call clearsprite
 pop de

;novos dados
 ld hl,lptiy ;ptiy
 add hl,de
 ld a,(hl)
 cp 255
 jp nz,promovefire

 call terminafire
 jp fimlmovefire

promovefire:
 dec a
 ld (hl),a

;dados para o sprite
 ld hl,lptiy ;ptiy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lptix ;ptix
 add hl,de
 ld a,(hl)
 ld (psix),a

 ld a,(tatx) ;tatx
 ld (tasx),a

 ld a,(taty) ;taty
 ld (tasy),a

 ld a,(attt) ;attt
 ld (atts),a

 push de
 ld hl,lofft1 ;offt1
 sla e
 add hl,de
 ld a,(hl)
 ld e,a
 inc hl
 ld a,(hl)
 ld d,a
 ld (offs),de
 pop de

 push de
 call printsprite
 pop de

 ld a,(disparo)
 inc a
 ld (disparo),a

fimlmovefire:
 pop af
 dec a
 jp nz, lmovefire

 ret


;termina disparo
terminafire:

 ld a,(disparos)
 dec a
 ld (disparos),a
 jp z,saiterminafire ;verifica se é o único da lista

;verifica se é o último da lista
 ld hl,disparos
 ld a,(disparo)
 cp (hl)
 jp z,saiterminafire

 ld a,(disparo) ;ptiy
 ld d,0
 ld e,a
 ld a,(disparos)
 ld hl,disparo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lptiy ;ptiy
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(disparo) ;ptix
 ld d,0
 ld e,a
 ld a,(disparos)
 ld hl,disparo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lptix ;ptix
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(disparo) ;offt
 ld d,0
 ld e,a
 sla e
 ld a,(disparos)
 sla a
 ld hl,disparo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lofft1 ;offt
 add hl,de
 ld d,h
 ld e,l
 inc hl
 inc hl
 ldir
 
saiterminafire:
 ret



; lê teclado e move nave
varreteclado:

;leitura do teclado

 ld bc,32766
 in a,(c)
 bit 0,a ; barra de espaços
 call z, criafire ; disparo

 ld bc,57342
 in a,(c)
 bit 0,a ; tecla 'p'
 call z, mvnaveright ; direita

 ld bc,57342
 in a,(c)
 bit 1,a ; tecla 'o'
 call z, mvnaveleft ; esquerda

 ld bc,64510
 in a,(c)
 bit 0,a ; tecla 'q'
 call z, mvnaveup ; cima

 ld bc,65022
 in a,(c)
 bit 0,a ; tecla 'a'
 call z, mvnavedown ; baixo

 ld bc,65278
 in a,(c)
 bit 2,a ; tecla 'x'
 call z, criabomba; bomba

;imprime a nave
 ld hl,(offn1)
 ld (offs),hl

 ld a,(pnix)
 ld (psix),a
 ld a,(pniy)
 ld (psiy),a
 ld a,(tanx)
 ld (tasx),a
 ld a,(tany)
 ld (tasy),a
 ld a,(attn)
 ld (atts),a
 call printsprite

 ret


;move nave esquerda
mvnaveleft:

 ld a,0
 ld (attr),a
 ld a,(pnix)
 ld (psix),a
 ld a,(pniy)
 ld (psiy),a
 ld a,(tanx)
 ld (tasx),a
 ld a,(tany)
 ld (tasy),a
 call clearsprite

 ld a,(pnix)
 cp 0
 jp z,fimmvnaveleft
 dec a
 ld (pnix),a

 ld hl,tanx ;tanx
 ld a,(hl)
 ld hl,pnix ;pnix
 add a,(hl)
 sub 1
 ld hl,pnfx ;pnfx
 ld (hl),a

fimmvnaveleft:
 ret


;move nave direita
mvnaveright:

 ld a,0
 ld (attr),a
 ld a,(pnix)
 ld (psix),a
 ld a,(pniy)
 ld (psiy),a
 ld a,(tanx)
 ld (tasx),a
 ld a,(tany)
 ld (tasy),a
 call clearsprite

 ld a,(pnix)
 cp 23
 jp z,fimmvnaveright
 inc a
 ld (pnix),a

 ld hl,tanx ;tanx
 ld a,(hl)
 ld hl,pnix ;pnix
 add a,(hl)
 sub 1
 ld hl,pnfx ;pnfx
 ld (hl),a

fimmvnaveright:
 ret


;move nave cima
mvnaveup:

 ld a,0
 ld (attr),a
 ld a,(pnix)
 ld (psix),a
 ld a,(pniy)
 ld (psiy),a
 ld a,(tanx)
 ld (tasx),a
 ld a,(tany)
 ld (tasy),a
 call clearsprite

 ld a,(pniy)
 cp 0
 jp z,fimmvnaveup
 dec a
 ld (pniy),a

 ld hl,tany ;tany
 ld a,(hl)
 ld hl,pniy ;pniy
 add a,(hl)
 sub 1
 ld hl,pnfy ;pnfy
 ld (hl),a

fimmvnaveup:
 ret


;move nave baixo
mvnavedown:

 ld a,0
 ld (attr),a
 ld a,(pnix)
 ld (psix),a
 ld a,(pniy)
 ld (psiy),a
 ld a,(tanx)
 ld (tasx),a
 ld a,(tany)
 ld (tasy),a
 call clearsprite

 ld a,(pniy)
 cp 22
 jp z,fimmvnavedown
 inc a
 ld (pniy),a

 ld hl,tany ;tany
 ld a,(hl)
 ld hl,pniy ;pniy
 add a,(hl)
 sub 1
 ld hl,pnfy ;pnfy
 ld (hl),a

fimmvnavedown:
 ret



;cria inimigo
criainimigo:

 ld a,(inimigos)
 cp 6
 jp z, saicriainimigo
 inc a
 ld (inimigos),a

;cria dados do novo inimigo
 ld a,(tipoini) ;tipoi
 ld hl,tipoi
 ld (hl),a

 ld a,(tipoi) ;verifica se é um Boss
 cp 4
 jp c, random ;se não for usa o um piix da lista

;se for um Boss
 ld a,6
 ld (piix),a ;piix

 jp procriaini

random:
 ld a,(inix) ;piix - posição x horizontal
 ld (piix),a

procriaini:
 ld a,(tipoi)   ;offi1
 ld d,0
 ld e,a
 sla e
 ld hl,ldoffi1
 add hl,de
 ld a,(hl)
 ld e,a
 inc hl
 ld a,(hl)
 ld d,a
 ld (offi1),de

 ld a,(tipoi)   ;piiy - posição y vertical
 ld d,0
 ld e,a
 ld hl,ldpiiy
 add hl,de
 ld a,(hl)
 ld (piiy),a

 ld a,(tipoi)   ;taix
 ld d,0
 ld e,a
 ld hl,ldtaixf1
 add hl,de
 ld a,(hl)
 ld (taix),a
 ld hl,piix  ;pifx
 add a,(hl)
 sub 1
 ld (pifx),a

 ld a,(tipoi)   ;taiy
 ld d,0
 ld e,a
 ld hl,ldtaiyf1
 add hl,de
 ld a,(hl)
 ld (taiy),a
 ld hl,piiy		;pify
 add a,(hl)
 sub 1		 
 ld (pify),a

 ld a,(tipoi) ;atti
 ld d,0
 ld e,a
 ld hl,ldatti
 add hl,de
 ld a,(hl)
 ld (atti),a

 ld a,(tipoi) ;speedi
 ld d,0
 ld e,a
 ld hl,ldspeedi
 add hl,de
 ld a,(hl)
 ld (speedi),a

 ld a,(tipoi)  ;speedicnt
 ld d,0
 ld e,a
 ld hl,ldspeedi
 add hl,de
 ld a,(hl)
 ld (speedicnt),a

 ld a,(tipoi) ;hullicnt
 ld d,0
 ld e,a
 ld hl,ldhulli
 add hl,de
 ld a,(hl)
 ld (hullicnt),a

 ld a,(tipoi) ;pontosi
 ld d,0
 ld e,a
 ld hl,ldpontosi
 add hl,de
 ld a,(hl)
 ld (pontosi),a

;coloca dados na lista dos inimigos
 ld a,(inimigos)
 dec a
 ld d,0
 ld e,a
 sla e

 ld hl,loffi1 ;offi1
 add hl,de
 push de
 ld de,(offi1)
 ld a,e
 ld (hl),a
 inc hl
 ld a,d
 ld (hl),a
 pop de

 ld a,(inimigos)
 dec a
 ld d,0
 ld e,a

 ld hl,lpiiy ;piiy
 add hl,de
 ld a,(piiy)
 ld (hl),a
 ld hl,lpiix ;piix
 add hl,de
 ld a,(piix)
 ld (hl),a
 ld hl,ltaix ;taix
 add hl,de
 ld a,(taix)
 ld (hl),a
 ld hl,ltaiy ;taiy
 add hl,de
 ld a,(taiy)
 ld (hl),a
 ld hl,lpify ;pify
 add hl,de
 ld a,(pify)
 ld (hl),a
 ld hl,lpifx ;pifx
 add hl,de
 ld a,(pifx)
 ld (hl),a
 ld hl,latti ;atti
 add hl,de
 ld a,(atti)
 ld (hl),a
 ld hl,ltipoi ;tipoi
 add hl,de
 ld a,(tipoi)
 ld (hl),a
 ld hl,lspeedi ;speedi
 add hl,de
 ld a,(speedi)
 ld (hl),a
 ld hl,lspeedicnt ;speedicnt
 add hl,de
 ld a,(speedicnt)
 ld (hl),a
 ld hl,lhullicnt ;hullicnt
 add hl,de
 ld a,(hullicnt)
 ld (hl),a
 ld hl,lpontosi ;pontosi
 add hl,de
 ld a,(pontosi)
 ld (hl),a

saicriainimigo:
 ret


;move inimigo;
moveinimigo:

 ld a,0
 ld (inimigo),a

 ld a,(inimigos)

lmoveinimigo:
 push af

 ld a,(inimigo)
 ld d,0
 ld e,a

;vai buscar os dados do inimigo à lista
 ld a,0
 ld (attr),a
 ld hl,lpiiy ;piiy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lpiix ;piix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld hl,ltaix ;taix
 add hl,de
 ld a,(hl)
 ld (tasx),a
 ld hl,ltaiy ;taiy
 add hl,de
 ld a,(hl)
 ld (tasy),a
 ld hl,ltipoi ;tipoi
 add hl,de
 ld a,(hl)
 ld (tipoi),a
 ld hl,lspeedi ;speedi
 add hl,de
 ld a,(hl)
 ld (speedi),a
 ld hl,lspeedicnt ;speedicnt
 add hl,de
 ld a,(hl)
 ld (speedicnt),a

;verifica se é altura de mover o inimigo
 ld a,(speedicnt)
 cp 0
 jr z,moveinimigome

 dec a
 ld (speedicnt),a

 ld a,(inimigo)
 ld d,0
 ld e,a
 ld hl,lspeedicnt ;speedicnt
 add hl,de
 ld a,(speedicnt)
 ld (hl),a
 jp fimlmoveinimigo2

moveinimigome:
 ld a,(inimigo)
 ld d,0
 ld e,a
 ld hl,lspeedicnt ;speedicnt
 add hl,de
 ld a,(speedi)
 ld (hl),a

 push de
 call clearsprite
 pop de

 ld a,(tipoi) ;verifica se é um Boss
 cp 4
 jp c,promoveini4 ;se não for um Boss

;se for um Boss verifica se já está todo no écran
 ld hl,lpiiy ;piiy
 add hl,de
 ld a,(hl)
 cp 0
 jp nz,promoveinimigo

 ld a,(dix)
 cp 1
 jp z, promovebossright

promovebossleft: ;movimenta o Boss para a esquerda
 ld hl,lpiix ;piix
 add hl,de
 ld a,(hl)
 cp 0
 jp z,fimpromovebossleft
 dec a
 ld (hl),a
 jp promoveinimigo2

fimpromovebossleft:
 ld a,1
 ld (dix),a
 jp promoveinimigo2


promovebossright: ;movimenta o Boss para a direita
 ld hl,lpifx ;pifx
 add hl,de
 ld a,(hl)
 cp 24
 jp z,fimpromovebossright
 ld hl,lpiix ;piix
 add hl,de
 ld a,(hl)
 inc a
 ld (hl),a
 jp promoveinimigo2

fimpromovebossright:
 ld a,0
 ld (dix),a
 jp promoveinimigo2


promoveini4:
 ld hl,lpiiy ;piiy
 add hl,de
 ld a,(hl)
 cp 24
 jp nz,promoveinimigo

 call terminainimigo
 jp fimlmoveinimigo

promoveinimigo:
 inc a
 ld (hl),a

promoveinimigo2:
 ld hl,ltaiy ;taiy
 add hl,de
 ld a,(hl)
 ld hl,lpiiy ;piiy
 add hl,de
 add a,(hl)
 sub 1
 ld hl,lpify ;pify
 add hl,de
 ld (hl),a

 ld hl,ltaix ;taix
 add hl,de
 ld a,(hl)
 ld hl,lpiix ;piix
 add hl,de
 add a,(hl)
 sub 1
 ld hl,lpifx ;pifx
 add hl,de
 ld (hl),a

 push de
 ld hl,loffi1 ;offs
 sla e
 add hl,de
 ld a,(hl)
 ld e,a
 inc hl
 ld a,(hl)
 ld d,a
 ld (offs),de
 pop de

 ld hl,lpiiy ;piiy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lpiix ;piix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld hl,ltaix ;taix
 add hl,de
 ld a,(hl)
 ld (tasx),a
 ld hl,ltaiy ;taiy
 add hl,de
 ld a,(hl)
 ld (tasy),a
 ld hl,latti ;atti
 add hl,de
 ld a,(hl)
 ld (atts),a

 push de
 call printsprite
 pop de

fimlmoveinimigo2:
 ld a,(inimigo)
 inc a
 ld (inimigo),a

fimlmoveinimigo:
 pop af
 dec a
 jp nz, lmoveinimigo
 
 ret 


;termina inimigo
terminainimigo:

 ld a,(inimigos)
 dec a
 ld (inimigos),a
 jp z, saiterminainimigo ; verifica se é o único da lista

;verifica se é o último da lista
 ld hl,inimigos
 ld a,(inimigo)
 cp (hl)
 jp z,saiterminainimigo

 ld a,(inimigo) ;piiy
 ld d,0
 ld e,a
 ld a,(inimigos)
 ld hl,inimigo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lpiiy ;piiy
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(inimigo) ;piix
 ld d,0
 ld e,a
 ld a,(inimigos)
 ld hl,inimigo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lpiix ;piix
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(inimigo) ;taix
 ld d,0
 ld e,a
 ld a,(inimigos)
 ld hl,inimigo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,ltaix ;taix
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(inimigo) ;taiy
 ld d,0
 ld e,a
 ld a,(inimigos)
 ld hl,inimigo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,ltaiy ;taiy
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(inimigo) ;pify
 ld d,0
 ld e,a
 ld a,(inimigos)
 ld hl,inimigo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lpify ;pify
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(inimigo) ;pifx
 ld d,0
 ld e,a
 ld a,(inimigos)
 ld hl,inimigo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lpifx ;pifx
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(inimigo) ;atti
 ld d,0
 ld e,a
 ld a,(inimigos)
 ld hl,inimigo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,latti ;atti
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(inimigo) ;tipoi
 ld d,0
 ld e,a
 ld a,(inimigos)
 ld hl,inimigo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,ltipoi ;tipoi
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(inimigo) ;speedi
 ld d,0
 ld e,a
 ld a,(inimigos)
 ld hl,inimigo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lspeedi ;speedi
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(inimigo) ;speedicnt
 ld d,0
 ld e,a
 ld a,(inimigos)
 ld hl,inimigo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lspeedicnt ;speedicnt
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(inimigo) ;hullicnt
 ld d,0
 ld e,a
 ld a,(inimigos)
 ld hl,inimigo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lhullicnt ;hullicnt
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(inimigo) ;pontosi
 ld d,0
 ld e,a
 ld a,(inimigos)
 ld hl,inimigo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lpontosi ;pontosi
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(inimigo) ;offi1
 ld d,0
 ld e,a
 sla e
 ld a,(inimigos)
 sla a
 ld hl,inimigo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,loffi1 ;offi1
 add hl,de
 ld d,h
 ld e,l
 inc hl
 inc hl
 ldir

saiterminainimigo:
 ret



;percorre lista dos inimigos para criar o disparo inimigo
criafireini:

 ld a,(ratedini)
 cp 0
 jp nz, saicriafireini

 ld a,r
 cp 10
 jp nc, saicriafireini

 ld a,0
 ld (inimigo),a

 ld a,(inimigos)

lcriafireini:
 push af

 ld a,(inimigo)
 ld d,0
 ld e,a

;vai buscar os dados do inimigo à lista
 ld hl,lpify ;pify
 add hl,de
 ld a,(hl)
 ld (pify),a
 ld hl,lpiix ;piix
 add hl,de
 ld a,(hl)
 ld (piix),a
 ld hl,ltipoi ;tipoi
 add hl,de
 ld a,(hl)
 ld (tipoi),a

 ld a,(tipoi) ;Inimigo 2 - não dispara
 cp 2
 jp z, fimlcriafireini

 ld a,(pify) ;abaixo da posição y=12 não já há disparos
 cp 12
 jp nc, fimlcriafireini

 ld a,(tipoi) ;Inimigo 1 - dois tiros
 cp 1
 jp z,segundotiroinimigo

 ld a,(tipoi) ;Boss 4 - dois tiros
 cp 4
 jp z,boss45

 ld a,(tipoi) ;Boss 5 - dois tiros
 cp 5
 jp z,boss45

 ld a,(tipoi) ;Boss 6 - quatro tiros
 cp 6
 jp z,boss6

 ld a,(tipoi) ;Boss 7 - quatro tiros
 cp 7
 jp z,boss7

 ld a,(tipoi) ;Boss 8 - seis tiros
 cp 8
 jp z,boss8

;Inimigo 0 e 2 - apenas um tiro
;Inimigo 0 e 2 -cria dados do tiro
 ld a,(pify) ;ptiniiy
 inc a
 ld (ptiniiy),a
 ld a,(piix) ;ptiniix
 inc a
 ld (ptiniix),a 

 push de
 call criafireinimigo
 pop de

 jp fimlcriafireini

;Inimigo 1 - dois tiros
segundotiroinimigo:
;Inimigo 1 - cria dados do primeiro tiro
 ld a,(pify) ;ptiniiy
 inc a
 ld (ptiniiy),a
 ld a,(piix) ;ptiniix
 ld (ptiniix),a

 push de
 call criafireinimigo
 pop de

;Inimigo 1 - cria dados do segundo tiro
 ld a,(pify) ;ptiniiy
 inc a
 ld (ptiniiy),a
 ld a,(piix) ;ptiniix
 add a,2
 ld (ptiniix),a

 push de
 call criafireinimigo
 pop de

 jp fimlcriafireini

;Boss 4 e 5 - 2 tiros
boss45:
;Boss 4 e 5 - cria dados do primeiro tiro
 ld a,(pify) ;ptiniiy
 inc a
 ld (ptiniiy),a
 ld a,(piix) ;ptiniix
 inc a
 ld (ptiniix),a

 push de
 call criafireinimigo
 pop de

;Boss 4 e 5 - cria dados do segundo tiro
 ld a,(pify) ;ptiniiy
 inc a
 ld (ptiniiy),a
 ld a,(piix) ;ptiniix
 add a,4
 ld (ptiniix),a

 push de
 call criafireinimigo
 pop de

 jp fimlcriafireini

;Boss 6 - 4 tiros
boss6:
;Boss 6 - cria dados do primeiro tiro
 ld a,(pify) ;ptiniiy
 inc a
 ld (ptiniiy),a
 ld a,(piix) ;ptiniix
 ld (ptiniix),a

 push de
 call criafireinimigo
 pop de

;Boss 6 - cria dados do segundo tiro
 ld a,(pify) ;ptiniiy
 inc a
 ld (ptiniiy),a
 ld a,(piix) ;ptiniix
 inc a
 ld (ptiniix),a

 push de
 call criafireinimigo
 pop de

;Boss 6 - cria dados do terceiro tiro
 ld a,(pify) ;ptiniiy
 inc a
 ld (ptiniiy),a
 ld a,(piix) ;ptiniix
 add a,2
 ld (ptiniix),a

 push de
 call criafireinimigo
 pop de

;Boss 6 - cria dados do quarto tiro
 ld a,(pify) ;ptiniiy
 inc a
 ld (ptiniiy),a
 ld a,(piix) ;ptiniix
 add a,3
 ld (ptiniix),a

 push de
 call criafireinimigo
 pop de

 jp fimlcriafireini

;Boss 7 - 4 tiros
boss7:
;Boss 7 - cria dados do primeiro tiro
 ld a,(pify) ;ptiniiy
 inc a
 ld (ptiniiy),a
 ld a,(piix) ;ptiniix
 ld (ptiniix),a

 push de
 call criafireinimigo
 pop de

;Boss 7 - cria dados do segundo tiro
 ld a,(pify) ;ptiniiy
 inc a
 ld (ptiniiy),a
 ld a,(piix) ;ptiniix
 add a,2
 ld (ptiniix),a

 push de
 call criafireinimigo
 pop de

;Boss 7 - cria dados do terceiro tiro
 ld a,(pify) ;ptiniiy
 inc a
 ld (ptiniiy),a
 ld a,(piix) ;ptiniix
 add a,3
 ld (ptiniix),a

 push de
 call criafireinimigo
 pop de

;Boss 7 - cria dados do quarto tiro
 ld a,(pify) ;ptiniiy
 inc a
 ld (ptiniiy),a
 ld a,(piix) ;ptiniix
 add a,5
 ld (ptiniix),a

 push de
 call criafireinimigo
 pop de

 jp fimlcriafireini

;Boss 8 - 6 tiros
boss8:
;Boss 8 - cria dados do primeiro tiro
 ld a,(pify) ;ptiniiy
 inc a
 ld (ptiniiy),a
 ld a,(piix) ;ptiniix
 add a,2
 ld (ptiniix),a

 push de
 call criafireinimigo
 pop de

;Boss 8 - cria dados do segundo tiro
 ld a,(pify) ;ptiniiy
 inc a
 ld (ptiniiy),a
 ld a,(piix) ;ptiniix
 add a,3
 ld (ptiniix),a

 push de
 call criafireinimigo
 pop de

;Boss 8 - cria dados do terceiro tiro
 ld a,(pify) ;ptiniiy
 inc a
 ld (ptiniiy),a
 ld a,(piix) ;ptiniix
 add a,4
 ld (ptiniix),a

 push de
 call criafireinimigo
 pop de

;Boss 8 - cria dados do quarto tiro
 ld a,(pify) ;ptiniiy
 inc a
 ld (ptiniiy),a
 ld a,(piix) ;ptiniix
 add a,5
 ld (ptiniix),a

 push de
 call criafireinimigo
 pop de

;Boss 8 - cria dados do quito tiro
 ld a,(pify) ;ptiniiy
 inc a
 ld (ptiniiy),a
 ld a,(piix) ;ptiniix
 add a,6
 ld (ptiniix),a

 push de
 call criafireinimigo
 pop de

;Boss 8 - cria dados do sexto tiro
 ld a,(pify) ;ptiniiy
 inc a
 ld (ptiniiy),a
 ld a,(piix) ;ptiniix
 add a,7
 ld (ptiniix),a

 push de
 call criafireinimigo
 pop de


fimlcriafireini:
 ld a,(inimigo)
 inc a
 ld (inimigo),a

 pop af
 dec a
 jp nz, lcriafireini

 ld a,6
 ld (ratedini),a

saicriafireini:
 ret


;rate disparo inimigo
ratedisparoinimigo:

 ld a,(ratedini)
 cp 0
 jr z, fimratedisparoinimigo
 dec a
 ld (ratedini),a

fimratedisparoinimigo:
 ret


;cria disparo inimigo
criafireinimigo:

 ld a,(disparosini)
 cp 18
 jp z,saicriafireinimigo

 ld a,(disparosini)
 inc a
 ld (disparosini),a

;coloca dados dos tiros na lista
 ld a,(disparosini)
 dec a
 ld d,0
 ld e,a

 ld hl,lptiniiy ;ptiniiy
 add hl,de
 ld a,(ptiniiy)
 ld (hl),a
 ld hl,lptiniix ;ptiniix
 add hl,de
 ld a,(ptiniix)
 ld (hl),a

saicriafireinimigo:
 ret


; move disparo inimigo
movefireinimigo:

 ld a,0
 ld (disparoini),a

 ld a,(disparosini)

lmovefireinimigo:
 push af

 ld a,(disparoini)
 ld d,0
 ld e,a

;dados atuais
 ld a,0
 ld (attr),a
 ld hl,lptiniiy ;ptiniiy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lptiniix ;ptiniix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld a,(tatinix) ;tatinix
 ld (tasx),a
 ld a,(tatiniy);tatiniy
 ld (tasy),a

 push de
 call clearsprite
 pop de

;novos dados
 ld hl,lptiniiy ;ptiniiy
 add hl,de
 ld a,(hl)
 cp 24
 jp nz, promovefireinimigo

 call terminafireinimigo
 jp fimlmovefireinimigo

promovefireinimigo:
 inc a
 ld (hl),a

;dados para o sprite
 ld hl,lptiniiy ;ptiniiy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lptiniix ;ptiniix
 add hl,de
 ld a,(hl)
 ld (psix),a

 ld a,(tatinix) ;tatinix
 ld (tasx),a

 ld a,(tatiniy) ;tatiniy
 ld (tasy),a

 ld a,(atttini) ;atttini
 ld (atts),a

 ld hl,(offtini1) ;offtini1
 ld (offs),hl

 push de
 call printsprite
 pop de

 ld a,(disparoini)
 inc a
 ld (disparoini),a

fimlmovefireinimigo:
 pop af
 dec a
 jp nz, lmovefireinimigo

 ret


;termina disparo inimigo
terminafireinimigo:

 ld a,(disparosini)
 dec a
 ld (disparosini),a
 jp z,saiterminafireinimigo ;verifica se é o único da lista

;verifica se é o último da lista
 ld hl,disparosini
 ld a,(disparoini)
 cp (hl)
 jp z,saiterminafireinimigo

 ld a,(disparoini) ;ptiniiy
 ld d,0
 ld e,a
 ld a,(disparosini)
 ld hl,disparoini
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lptiniiy ;ptiniiy
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(disparoini) ;ptiniix
 ld d,0
 ld e,a
 ld a,(disparosini)
 ld hl,disparoini
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lptiniix ;ptiniix
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

saiterminafireinimigo:
 ret



;cria prémio
criapremio:

;verifica se pode criar prémio
 ld a,r
 cp 50
 jp nc, saicriapremio

 ld a,(premios)
 cp 10
 jp z, saicriapremio
 inc a
 ld (premios),a

;cria dados do novo prémio
randompr0: ;tipo do prémio
 ld a,r
 cp 4
 jp nc,randompr0
 ld hl,tipopr
 ld (hl),a

 ld a,(tipopr)   ;offpr
 ld d,0
 ld e,a
 sla e
 ld hl,ldoffpr
 add hl,de
 ld a,(hl)
 ld e,a
 inc hl
 ld a,(hl)
 ld d,a
 ld (offpr),de

 ld a,(tipopr) ;attpr
 ld d,0
 ld e,a
 ld hl,ldattpr
 add hl,de
 ld a,(hl)
 ld (attpr),a

 ld a,(pify) ;ppriy
 ld (ppriy),a
 ld a,(piix) ;pprix
 ld (pprix),a

;coloca dados na lista dos premios
 ld a,(premios)
 dec a
 ld d,0
 ld e,a
 sla e

 ld hl,loffpr ;offpr
 add hl,de
 push de
 ld de,(offpr)
 ld a,e
 ld (hl),a
 inc hl
 ld a,d
 ld (hl),a
 pop de

 ld a,(premios)
 dec a
 ld d,0
 ld e,a

 ld hl,lppriy ;ppriy
 add hl,de
 ld a,(ppriy)
 ld (hl),a
 ld hl,lpprix ;pprix
 add hl,de
 ld a,(pprix)
 ld (hl),a
 ld hl,lattpr ;attpr
 add hl,de
 ld a,(attpr)
 ld (hl),a
 ld hl,ltipopr ;tipopr
 add hl,de
 ld a,(tipopr)
 ld (hl),a
 ld hl,lspeedprcnt ;speedprcnt
 add hl,de
 ld a,(speedpr)
 ld (hl),a
 ld hl,ltempoprcnt ;tempoprcnt
 add hl,de
 ld a,(tempopr)
 ld (hl),a

saicriapremio:
 ret


;move prémio
movepremio:

 ld a,0
 ld (premio),a

 ld a,(premios)

lmovepremio:
 push af

 ld a,(premio)
 ld d,0
 ld e,a

;vai buscar os dados do prémio à lista
 ld a,0
 ld (attr),a
 ld hl,lppriy ;ppriy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lpprix ;pprix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld a,(taprx) ;taprx
 ld (tasx),a
 ld a,(tapry) ;tapry
 ld (tasy),a
 ld hl,ltipopr ;tipopr
 add hl,de
 ld a,(hl)
 ld (tipopr),a
 ld hl,lspeedprcnt ;speedprcnt
 add hl,de
 ld a,(hl)
 ld (speedprcnt),a
 ld hl,ltempoprcnt ;tempoprcnt
 add hl,de
 ld a,(hl)
 ld (tempoprcnt),a

;verifica se é altura de apagar o prémio
 ld a,(tempoprcnt)
 cp 0
 jr nz,movepremiome0

 push de
 call clearsprite
 pop de

 call terminapremio
 jp fimlmovepremio

movepremiome0:
 dec a
 ld (tempoprcnt),a
 ld a,(premio)
 ld d,0
 ld e,a
 ld hl,ltempoprcnt ;tempoprcnt
 add hl,de
 ld a,(tempoprcnt)
 ld (hl),a

;verifica se é altura de mover o prémio
 ld a,(speedprcnt)
 cp 0
 jr z,movepremiome

 dec a
 ld (speedprcnt),a

 ld a,(premio)
 ld d,0
 ld e,a
 ld hl,lspeedprcnt ;speedprcnt
 add hl,de
 ld a,(speedprcnt)
 ld (hl),a
 jp fimlmovepremio2

movepremiome:
 ld a,(premio)
 ld d,0
 ld e,a
 ld hl,lspeedprcnt ;speedprcnt
 add hl,de
 ld a,(speedpr)
 ld (hl),a

 push de
 call clearsprite
 pop de

;novos dados
 ld hl,lppriy ;ppriy
 add hl,de
 ld a,(hl)
 cp 24
 jp nz,promovepremio

 call terminapremio
 jp fimlmovepremio

promovepremio:
 inc a
 ld (hl),a

;dados para o sprite
 ld hl,lppriy ;ppriy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lpprix ;pprix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld a,(taprx) ;taprx
 ld (tasx),a
 ld a,(tapry) ;tapry
 ld (tasy),a
 ld hl,lattpr ;attpr
 add hl,de
 ld a,(hl)
 ld (atts),a

 push de
 ld hl,loffpr ;offpr
 sla e
 add hl,de
 ld a,(hl)
 ld e,a
 inc hl
 ld a,(hl)
 ld d,a
 ld (offs),de
 pop de

 push de
 call printsprite
 pop de

fimlmovepremio2:
 ld a,(premio)
 inc a
 ld (premio),a

fimlmovepremio:
 pop af
 dec a
 jp nz, lmovepremio
 
 ret


;termina prémio
terminapremio:

 ld a,(premios)
 dec a
 ld (premios),a
 jp z,saiterminapremio ;verifica se é o único da lista

;verifica se é o último da lista
 ld hl,premios
 ld a,(premio)
 cp (hl)
 jp z,saiterminapremio

 ld a,(premio) ;ppriy
 ld d,0
 ld e,a
 ld a,(premios)
 ld hl,premio
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lppriy ;ppriy
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(premio) ;pprix
 ld d,0
 ld e,a
 ld a,(premios)
 ld hl,premio
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lpprix ;pprix
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(premio) ;attpr
 ld d,0
 ld e,a
 ld a,(premios)
 ld hl,premio
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lattpr ;attpr
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(premio) ;tipopr
 ld d,0
 ld e,a
 ld a,(premios)
 ld hl,premio
 sub (hl)
 ld b,0
 ld c,a

 ld hl,ltipopr ;tipopr
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(premio) ;speedprcnt
 ld d,0
 ld e,a
 ld a,(premios)
 ld hl,premio
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lspeedprcnt ;speedprcnt
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(premio) ;tempoprcnt
 ld d,0
 ld e,a
 ld a,(premios)
 ld hl,premio
 sub (hl)
 ld b,0
 ld c,a

 ld hl,ltempoprcnt ;tempoprcnt
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(premio) ;offpr
 ld d,0
 ld e,a
 sla e
 ld a,(premios)
 sla a
 ld hl,premio
 sub (hl)
 ld b,0
 ld c,a

 ld hl,loffpr ;offpr
 add hl,de
 ld d,h
 ld e,l
 inc hl
 inc hl
 ldir

saiterminapremio:
 ret



;cria explosão
criaexplosao:

 ld a,(explos)
 cp 10
 jp z,saicriaexplosao

 ld a,(explos)
 inc a
 ld (explos),a

;coloca dados da explosão na lista
 ld a,(explos)
 dec a
 ld d,0
 ld e,a

 ld hl,lpexploy ;pexploy
 add hl,de
 ld a,(pexploy)
 ld (hl),a
 ld hl,lpexplox ;pexplox
 add hl,de
 ld a,(pexplox)
 ld (hl),a
 ld hl,lattexplo ;attexplo
 add hl,de
 ld a,70
 ld (hl),a
 ld hl,ltempoexplocnt ;tempoexplocnt
 add hl,de
 ld a,(tempoexplo)
 ld (hl),a

saicriaexplosao:
 ret


; move explosão
moveexplosao:

 ld a,0
 ld (explo),a

 ld a,(explos)

lmoveexplosao:
 push af

 ld a,(explo)
 ld d,0
 ld e,a

;dados atuais
 ld a,0
 ld (attr),a
 ld hl,lpexploy ;pexploy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lpexplox ;pexplox
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld a,(taexplox) ;taexplox
 ld (tasx),a
 ld a,(taexploy) ;taexploy
 ld (tasy),a

 ld hl,ltempoexplocnt ;tempoexplocnt
 add hl,de
 ld a,(hl)
 ld (tempoexplocnt),a

;verifica se é altura de apagar a explosão
 ld a,(tempoexplocnt)
 cp 0
 jr nz,movepexplosao

 push de
 call clearsprite
 pop de

 call terminaexplosao
 jp fimlmoveexplosao

movepexplosao:
 dec a
 ld (tempoexplocnt),a
 ld a,(explo)
 ld d,0
 ld e,a
 ld hl,ltempoexplocnt ;tempoexplocnt
 add hl,de
 ld a,(tempoexplocnt)
 ld (hl),a

 ld hl,(offexplo)
 ld (offs),hl

 ld hl,lattexplo ;attexplo
 add hl,de
 ld a,(hl)
 ld (attexplo),a
 ld (atts),a

 push de
 call printsprite
 pop de

 ld a,(attexplo)
 cp 70
 jp nz, priexplosao2

 ld a,66
 ld hl,lattexplo ;attexplo
 add hl,de
 ld (hl),a
 jp fimlmoveexplosao2

priexplosao2:
 ld a,70
 ld hl,lattexplo ;attexplo
 add hl,de
 ld (hl),a

fimlmoveexplosao2:
 ld a,(explo)
 inc a
 ld (explo),a

fimlmoveexplosao:
 pop af
 dec a
 jp nz, lmoveexplosao

 ret


;termina explosão
terminaexplosao:

 ld a,(explos)
 dec a
 ld (explos),a
 jp z,saiterminaexplosao ;verifica se é o único da lista

;verifica se é o último da lista
 ld hl,explos
 ld a,(explo)
 cp (hl)
 jp z,saiterminaexplosao

 ld a,(explo) ;pexploy
 ld d,0
 ld e,a
 ld a,(explos)
 ld hl,explo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lpexploy ;pexploy
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(explo) ;pexplox
 ld d,0
 ld e,a
 ld a,(explos)
 ld hl,explo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lpexplox ;pexplox
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(explo) ;attexplo
 ld d,0
 ld e,a
 ld a,(explos)
 ld hl,explo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,lattexplo ;attexplo
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

 ld a,(explo) ;tempoexplocnt
 ld d,0
 ld e,a
 ld a,(explos)
 ld hl,explo
 sub (hl)
 ld b,0
 ld c,a

 ld hl,ltempoexplocnt ;tempoexplocnt
 add hl,de
 ld d,h
 ld e,l
 inc hl
 ldir

saiterminaexplosao:
 ret



;verifica colisão entre disparos e inimigos
verificacolisao1:

 ld a,(disparos) 
 cp 0
 jp z, saiverificacolisao1

 ld a,(inimigos)
 cp 0
 jp z, saiverificacolisao1

 ld a,0
 ld (disparo),a

 ld a,(disparos)

lvc1disparo:
 push af

 ld a,(disparo)
 ld d,0
 ld e,a

;lê dados do disparo
 ld hl,lptiy ;ptiy
 add hl,de
 ld a,(hl)
 ld (ptiy),a
 ld hl,lptix ;ptix
 add hl,de
 ld a,(hl)
 ld (ptix),a

 ld a,0
 ld (inimigo),a

 ld a,(inimigos) ;se não houver mais inimigos sai da rotina
 cp 0
 jp nz, lvc1inimigo

 pop af
 jp saiverificacolisao1

lvc1inimigo:
 push af

 ld a,(inimigo)
 ld d,0
 ld e,a

;lê dados do inimigo
 ld hl,lpiiy ;piiy
 add hl,de
 ld a,(hl)
 ld (piiy),a
 ld hl,lpify ;pify
 add hl,de
 ld a,(hl)
 ld (pify),a
 ld hl,lpiix ;piix
 add hl,de
 ld a,(hl)
 ld (piix),a
 ld hl,lpifx ;pifx
 add hl,de
 ld a,(hl)
 ld (pifx),a
 ld hl,lhullicnt ;hullicnt
 add hl,de
 ld a,(hl)
 ld (hullicnt),a
 ld hl,lpontosi ;pontosi
 add hl,de
 ld a,(hl)
 ld (pontosi),a
 ld hl,ltipoi ;tipoi
 add hl,de
 ld a,(hl)
 ld (tipoi),a

;verifica se acertou
 ld a,(pify)
 ld hl,ptiy
 cp (hl)
 jp c, fimlvc1inimigo2

 ld a,(ptiy)
 ld hl,piiy
 cp (hl)
 jp c, fimlvc1inimigo2

 ld a,(ptix)
 ld hl,piix
 cp (hl)
 jp c, fimlvc1inimigo2
 
 ld a,(pifx)
 ld hl,ptix
 cp (hl)
 jp c, fimlvc1inimigo2

;verifica se é altura de terminar o inimigo
 ld a,(hullicnt)
 cp 0
 jr z,provc1 ; se sim salta para o fim do disparo e do inimigo
 dec a
 ld (hullicnt),a

;se não termina só o disparo
 ld a,(inimigo)
 ld d,0
 ld e,a
 ld hl,lhullicnt ;lhullicnt
 add hl,de
 ld a,(hullicnt)
 ld (hl),a

;apaga o disparo
 ld a,(disparo)
 ld d,0
 ld e,a
 ld a,0
 ld (attr),a
 ld hl,lptiy ;ptiy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lptix ;ptix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld a,(tatx) ;tatx
 ld (tasx),a
 ld a,(taty);taty
 ld (tasy),a
 
 push de
 call clearsprite
 pop de

;se for um Boss cria os dados para uma pequena explosão do Boss
 ld a,(tipoi)
 cp 4
 jp c, provc10

 ld a,(ptiy)
 ld (pexploy),a
 ld a,(ptix)
 ld (pexplox),a
 ld a,5
 ld (tempoexplo),a

 call criaexplosao
 call somexplosao

 ld a,5 ;atualiza o score
 ld d,0
 ld e,a
 ld hl,(score)
 add hl,de
 ld (score),hl

 call atualizascore

provc10:
 call terminafire
 pop af
 jp fimlvc1disparo

;apaga o disparo e o inimigo
provc1:
;apaga o disparo
 ld a,(disparo)
 ld d,0
 ld e,a
 ld a,0
 ld (attr),a
 ld hl,lptiy ;ptiy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lptix ;ptix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld a,(tatx) ;tatx
 ld (tasx),a
 ld a,(taty);taty
 ld (tasy),a
 
 push de
 call clearsprite
 pop de

;apaga o inimigo
 ld a,(inimigo)
 ld d,0
 ld e,a
 ld a,0
 ld (attr),a
 ld hl,lpiiy ;piiy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lpiix ;piix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld hl,ltaix ;taix
 add hl,de
 ld a,(hl)
 ld (tasx),a
 ld hl,ltaiy ;taiy
 add hl,de
 ld a,(hl)
 ld (tasy),a

 push de
 call clearsprite
 pop de

;se for um Boss chama a rotina que cria as várias explosões do Boss
 ld a,(tipoi)
 cp 4
 jp c,provc11

 ld a,1
 ld (mudanivel),a
 call criaexplosaoboss
 call somexplosao
 jp provc12

provc11:
;cria os dados para a explosão do inimigo
 ld a,(piiy)
 ld (pexploy),a
 ld a,(piix)
 ld (pexplox),a
 ld a,9
 ld (tempoexplo),a

 call criaexplosao
 call somexplosao
 call criapremio

provc12:
 ld a,(pontosi) ;atualiza o score
 ld d,0
 ld e,a
 ld hl,(score)
 add hl,de
 ld (score),hl

 call atualizascore

 call terminainimigo
 call terminafire
 pop af
 jp fimlvc1disparo

fimlvc1inimigo2:
 ld a,(inimigo)
 inc a
 ld (inimigo),a

fimlvc1inimigo:
 pop af
 dec a
 jp nz, lvc1inimigo

fimlvc1disparo2:
 ld a,(disparo)
 inc a
 ld (disparo),a

fimlvc1disparo:
 pop af
 dec a
 jp nz, lvc1disparo

saiverificacolisao1:
 ret


;cria as várias explosões de um Boss
criaexplosaoboss

 ld a,(mudanivel)
 cp 1
 jp z,tempoexplo10

 ld a,4
 ld (tempoexplo),a
 jp procriaexplo

tempoexplo10:
 ld a,10
 ld (tempoexplo),a

procriaexplo:
 ld a,(tipoi)

 cp 4
 jp z, criaexplosaoboss45

 cp 5
 jp z, criaexplosaoboss45

 cp 6
 jp z, criaexplosaoboss6

 cp 7
 jp z, criaexplosaoboss7

 cp 8
 jp z, criaexplosaoboss8


;cria os dados para a explosão do Boss 4 e 5
criaexplosaoboss45:

 ld a,(piiy)
 inc a
 ld (pexploy),a
 ld a,(piix)
 ld (pexplox),a
 call criaexplosao

 ld a,(piiy)
 ld (pexploy),a
 ld a,(piix)
 add a,2
 ld (pexplox),a
 call criaexplosao

 ld a,(piiy)
 add a,2
 ld (pexploy),a
 ld a,(piix)
 add a,2
 ld (pexplox),a
 call criaexplosao

 ld a,(piiy)
 inc a
 ld (pexploy),a
 ld a,(piix)
 add a,4
 ld (pexplox),a
 call criaexplosao

 ld a,(mudanivel)
 cp 1
 jp nz,pnivel3

 ld a,(tipoi)
 cp 4
 jp z, pnivel2

 ld a,3
 ld (nivel),a
 jp pnivel2a

pnivel2:
 ld a,2
 ld (nivel),a

pnivel2a:
 ld a,4
 ld (estado),a

 call atualizanivel

pnivel3:
 jp saicriaexplosaoboss


;cria os dados para a explosão do Boss 6
criaexplosaoboss6:

 ld a,(piiy)
 ld (pexploy),a
 ld a,(piix)
 inc a
 ld (pexplox),a
 call criaexplosao

 ld a,(piiy)
 add a,2
 ld (pexploy),a
 ld a,(piix)
 ld (pexplox),a
 call criaexplosao

 ld a,(piiy)
 add a,2
 ld (pexploy),a
 ld a,(piix)
 add a,2
 ld (pexplox),a
 call criaexplosao

 ld a,(piiy)
 add a,4
 ld (pexploy),a
 ld a,(piix)
 inc a
 ld (pexplox),a
 call criaexplosao

 ld a,(mudanivel)
 cp 1
 jp nz,pnivel4

 ld a,4
 ld (nivel),a

 ld a,4
 ld (estado),a

 call atualizanivel

pnivel4:
 jp saicriaexplosaoboss


;cria os dados para a explosão do Boss 7
criaexplosaoboss7:

 ld a,(piiy)
 inc a
 ld (pexploy),a
 ld a,(piix)
 ld (pexplox),a
 call criaexplosao

 ld a,(piiy)
 add a,3
 ld (pexploy),a
 ld a,(piix)
 ld (pexplox),a
 call criaexplosao

 ld a,(piiy)
 ld (pexploy),a
 ld a,(piix)
 add a,2
 ld (pexplox),a
 call criaexplosao

 ld a,(piiy)
 add a,2
 ld (pexploy),a
 ld a,(piix)
 add a,2
 ld (pexplox),a
 call criaexplosao

 ld a,(piiy)
 add a,4
 ld (pexploy),a
 ld a,(piix)
 add a,2
 ld (pexplox),a
 call criaexplosao

 ld a,(piiy)
 inc a
 ld (pexploy),a
 ld a,(piix)
 add a,4
 ld (pexplox),a
 call criaexplosao

 ld a,(piiy)
 add a,3
 ld (pexploy),a
 ld a,(piix)
 add a,4
 ld (pexplox),a
 call criaexplosao

 ld a,(mudanivel)
 cp 1
 jp nz,pnivel5

 ld a,5
 ld (nivel),a

 ld a,4
 ld (estado),a

 call atualizanivel

pnivel5:
 jp saicriaexplosaoboss


;cria os dados para a explosão do Boss 8
criaexplosaoboss8:

 ld a,(piiy)
 inc a
 ld (pexploy),a
 ld a,(piix)
 ld (pexplox),a
 call criaexplosao

 ld a,(piiy)
 ld (pexploy),a
 ld a,(piix)
 add a,2
 ld (pexplox),a
 call criaexplosao

 ld a,(piiy)
 add a,2
 ld (pexploy),a
 ld a,(piix)
 add a,2
 ld (pexplox),a
 call criaexplosao

 ld a,(piiy)
 ld (pexploy),a
 ld a,(piix)
 add a,4
 ld (pexplox),a
 call criaexplosao

 ld a,(piiy)
 add a,2
 ld (pexploy),a
 ld a,(piix)
 add a,4
 ld (pexplox),a
 call criaexplosao

 ld a,(piiy)
 ld (pexploy),a
 ld a,(piix)
 add a,6
 ld (pexplox),a
 call criaexplosao

 ld a,(piiy)
 add a,2
 ld (pexploy),a
 ld a,(piix)
 add a,6
 ld (pexplox),a
 call criaexplosao

 ld a,(piiy)
 inc a
 ld (pexploy),a
 ld a,(piix)
 add a,8
 ld (pexplox),a
 call criaexplosao

 ld a,(mudanivel)
 cp 1
 jp nz,saicriaexplosaoboss

 ld a,6
 ld (nivel),a

 ld a,7
 ld (estado),a

 call atualizanivel

saicriaexplosaoboss:
 ret


;verifica invencibilidade da nave
rateinvencivel:

 ld a,(invencivel)
 cp 0
 jr z, fimrateinvencivel
 dec a
 ld (invencivel),a

 ld a,(attn)
 cp 6
 jp nz, pattn6

 ld a,2
 ld (attn),a
 jp fimrateinvencivel

pattn6:
 ld a,6
 ld (attn),a

fimrateinvencivel:
 ret


;verifica colisão a entre a nave e disparos inimigos
verificacolisao2:

 ld a,(disparosini)
 cp 0
 jp z, saiverificacolisao2

 ld a,0
 ld (disparoini),a

 ld a,(disparosini)

lvc2disparo:
 push af

 ld a,(disparoini)
 ld d,0
 ld e,a

;lê dados do disparo inimigo
 ld hl,lptiniiy ;ptiniiy
 add hl,de
 ld a,(hl)
 ld (ptiniiy),a
 ld hl,lptiniix ;ptiniix
 add hl,de
 ld a,(hl)
 ld (ptiniix),a

;verifica se acertou
 ld a,(ptiniiy)
 ld hl,pniy
 cp (hl)
 jp c, fimlvc2disparo2

 ld a,(pnfy) 
 ld hl,ptiniiy
 cp (hl)
 jp c, fimlvc2disparo2

 ld a,(ptiniix)
 ld hl,pnix
 cp (hl)
 jp c, fimlvc2disparo2
 
 ld a,(pnfx)
 ld hl,ptiniix
 cp (hl)
 jp c, fimlvc2disparo2

;verifica se é altura terminar a nave
 ld a,(invencivel)
 cp 0
 jr z,provc2 ; se sim salta para o fim do disparo inimigo e da nave

;termina só o disparo inimigo
;apaga o disparo inimigo
 ld a,(disparoini)
 ld d,0
 ld e,a
 ld a,0
 ld (attr),a
 ld hl,lptiniiy ;ptiniiy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lptiniix ;ptiniix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld a,(tatinix) ;tatinix
 ld (tasx),a
 ld a,(tatiniy);tatiniy
 ld (tasy),a
 
 push de
 call clearsprite
 pop de

 call terminafireinimigo
 jp fimlvc2disparo

;termina a nave e o disparo inimigo
provc2:
;apaga o disparo inimigo
 ld a,(disparo)
 ld d,0
 ld e,a
 ld a,0
 ld (attr),a
 ld hl,lptiniiy ;ptiniiy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lptiniix ;ptiniix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld a,(tatinix) ;tatinix
 ld (tasx),a
 ld a,(tatiniy);tatiniy
 ld (tasy),a
 
 push de
 call clearsprite
 pop de

;cria os dados para a explosão da nave
 ld a,(pniy)
 ld (pexploy),a
 ld a,(pnix)
 ld (pexplox),a
 ld a,4
 ld (tempoexplo),a

 call criaexplosao
 call somexplosao

 ld a,75 ;invencibilidade da nave
 ld (invencivel),a
 ld a,2
 ld (attn),a

 ld a,(vidas) ;atualiza as vidas
 dec a
 ld (vidas),a

 call atualizamenosvidas

 ld a,0 ;reduz para um disparo
 ld (tiros),a

 call terminafireinimigo
 jp fimlvc2disparo

fimlvc2disparo2:
 ld a,(disparoini)
 inc a
 ld (disparoini),a

fimlvc2disparo:
 pop af
 dec a
 jp nz, lvc2disparo

saiverificacolisao2:
 ret


;verifica colisão a entre a nave e inimigos
verificacolisao3:

 ld a,(inimigos)
 cp 0
 jp z, saiverificacolisao3

 ld a,0
 ld (inimigo),a

 ld a,(inimigos)

lvc3inimigo:
 push af

 ld a,(inimigo)
 ld d,0
 ld e,a

;lê dados do inimigo
 ld hl,lpiiy ;piiy
 add hl,de
 ld a,(hl)
 ld (piiy),a
 ld hl,lpiix ;piix
 add hl,de
 ld a,(hl)
 ld (piix),a
 ld hl,lpify ;pify
 add hl,de
 ld a,(hl)
 ld (pify),a
 ld hl,lpifx ;pifx
 add hl,de
 ld a,(hl)
 ld (pifx),a
 ld hl,lpontosi ;pontosi
 add hl,de
 ld a,(hl)
 ld (pontosi),a
 ld hl,lhullicnt ;hullicnt
 add hl,de
 ld a,(hl)
 ld (hullicnt),a
 ld hl,ltipoi ;tipoi
 add hl,de
 ld a,(hl)
 ld (tipoi),a

;verifica se acertou
 ld a,(pify)
 ld hl,pniy
 cp (hl)
 jp c, provc32

 ld a,(pnfy) 
 ld hl,piiy
 cp (hl)
 jp c, provc32

 ld a,(pnix)
 ld hl,piix
 cp (hl)
 jp c, provc32
 
 ld a,(pifx)
 ld hl,pnix
 cp (hl)
 jp c, provc32

 jp provc31

provc32:
 ld a,(pify)
 ld hl,pniy
 cp (hl)
 jp c, provc33

 ld a,(pnfy) 
 ld hl,piiy
 cp (hl)
 jp c, provc33

 ld a,(pnfx)
 ld hl,piix
 cp (hl)
 jp c, provc33
 
 ld a,(pifx)
 ld hl,pnfx
 cp (hl)
 jp c, provc33

 jp provc31

provc33:
 ld a,(piiy)
 ld hl,pniy
 cp (hl)
 jp c, fimlvc3inimigo2

 ld a,(pnfy) 
 ld hl,piiy
 cp (hl)
 jp c, fimlvc3inimigo2

 ld a,(piix)
 ld hl,pnix
 cp (hl)
 jp c, fimlvc3inimigo2
 
 ld a,(pnfx)
 ld hl,piix
 cp (hl)
 jp c, fimlvc3inimigo2


provc31:
;verifica se é altura terminar a nave
 ld a,(invencivel)
 cp 0
 jp z,provc3 ; se sim salta para o fim do inimigo e da nave

;se não termina só o inimigo
;verifica se é um Boss
 ld a,(tipoi)
 cp 4
 jp c,provc34

 ld a,(hullicnt)
 cp 5
 jp c,provc34 ; se sim salta para o fim do Boss
 sub 5
 ld (hullicnt),a

 ld a,(inimigo)
 ld d,0
 ld e,a
 ld a,(hullicnt)
 ld hl,lhullicnt ;hullicnt
 add hl,de
 ld (hl),a

;cria os dados para a explosão da nave
 ld a,(pniy)
 ld (pexploy),a
 ld a,(pnix)
 ld (pexplox),a
 ld a,4
 ld (tempoexplo),a

 call criaexplosao 
 call somexplosao

 jp fimlvc3inimigo2

provc34:
;apaga o inimigo
 ld a,(inimigo)
 ld d,0
 ld e,a
 ld a,0
 ld (attr),a
 ld hl,lpiiy ;piiy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lpiix ;piix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld hl,ltaix ;taix
 add hl,de
 ld a,(hl)
 ld (tasx),a
 ld hl,ltaiy ;taiy
 add hl,de
 ld a,(hl)
 ld (tasy),a
 
 push de
 call clearsprite
 pop de

;se for um Boss cria os dados para as várias explosões do Boss
 ld a,(tipoi)
 cp 4
 jp c,provc36

 ld a,1
 ld (mudanivel),a
 call criaexplosaoboss
 call somexplosao
 jp provc35

provc36:
;cria os dados para a explosão do inimigo
 ld a,(piiy)
 ld (pexploy),a
 ld a,(piix)
 ld (pexplox),a
 ld a,9
 ld (tempoexplo),a

 call criaexplosao
 call somexplosao

provc35:
 ld a,(pontosi) ;atualiza o score
 ld d,0
 ld e,a
 ld hl,(score)
 add hl,de
 ld (score),hl

 call atualizascore

 call terminainimigo
 jp fimlvc3inimigo


;termina a nave e o inimigo
provc3:
;verifica se é um Boss
 ld a,(tipoi)
 cp 4
 jp c,provc37

 ld a,(hullicnt)
 cp 5
 jp c,provc37 ;se sim salta para o fim do Boss
 sub 5
 ld (hullicnt),a

 ld a,(inimigo)
 ld d,0
 ld e,a
 ld a,(hullicnt)
 ld hl,lhullicnt ;hullicnt
 add hl,de
 ld (hl),a

 ld a,75 ;invencibilidade da nave
 ld (invencivel),a
 ld a,2
 ld (attn),a

 ld a,(vidas) ;atualiza as vidas
 dec a
 ld (vidas),a

 call atualizamenosvidas

 ld a,0 ;reduz para um disparo
 ld (tiros),a

 jp fimlvc3inimigo2

provc37:
;apaga o inimigo
 ld a,(inimigo)
 ld d,0
 ld e,a
 ld a,0
 ld (attr),a
 ld hl,lpiiy ;piiy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lpiix ;piix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld hl,ltaix ;taix
 add hl,de
 ld a,(hl)
 ld (tasx),a
 ld hl,ltaiy ;taiy
 add hl,de
 ld a,(hl)
 ld (tasy),a
 
 push de
 call clearsprite
 pop de

;cria os dados para a explosão da nave
 ld a,(pniy)
 ld (pexploy),a
 ld a,(pnix)
 ld (pexplox),a
 ld a,4
 ld (tempoexplo),a

 call criaexplosao 

 ld a,75 ;invencibilidade da nave
 ld (invencivel),a
 ld a,2
 ld (attn),a

 ld a,(vidas) ;atualiza as vidas
 dec a
 ld (vidas),a

 call atualizamenosvidas

 ld a,0 ;reduz para um disparo
 ld (tiros),a


;se for um Boss cria os dados para as várias explosões do Boss
 ld a,(tipoi)
 cp 4
 jp c,provc38

 ld a,1
 ld (mudanivel),a
 call criaexplosaoboss
 call somexplosao
 jp provc39

provc38:
;cria os dados para a explosão do inimigo
 ld a,(piiy)
 ld (pexploy),a
 ld a,(piix)
 ld (pexplox),a
 ld a,9
 ld (tempoexplo),a

 call criaexplosao
 call somexplosao

provc39:
 ld a,(pontosi) ;atualiza o score
 ld d,0
 ld e,a
 ld hl,(score)
 add hl,de
 ld (score),hl

 call atualizascore

 call terminainimigo
 jp fimlvc3inimigo

fimlvc3inimigo2:
 ld a,(inimigo)
 inc a
 ld (inimigo),a

fimlvc3inimigo:
 pop af
 dec a
 jp nz, lvc3inimigo

saiverificacolisao3:
 ret


;verifica colisão a entre a nave e prémios
verificacolisao4:

 ld a,(premios)
 cp 0
 jp z, saiverificacolisao4

 ld a,0
 ld (premio),a

 ld a,(premios)

lvc4premio:
 push af

 ld a,(premio)
 ld d,0
 ld e,a

;lê dados do prémio
 ld hl,lppriy ;ppriy
 add hl,de
 ld a,(hl)
 ld (ppriy),a
 ld hl,lpprix ;pprix
 add hl,de
 ld a,(hl)
 ld (pprix),a
 ld hl,ltipopr ;tipopr
 add hl,de
 ld a,(hl)
 ld (tipopr),a

;verifica se acertou
 ld a,(ppriy)
 ld hl,pniy
 cp (hl)
 jp c, fimlvc4premio2

 ld a,(pnfy) 
 ld hl,ppriy
 cp (hl)
 jp c, fimlvc4premio2

 ld a,(pprix)
 ld hl,pnix
 cp (hl)
 jp c, fimlvc4premio2
 
 ld a,(pnfx)
 ld hl,pprix
 cp (hl)
 jp c, fimlvc4premio2

;apaga o prémio
 ld a,(premio)
 ld d,0
 ld e,a
 ld a,0
 ld (attr),a
 ld hl,lppriy ;ppriy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lpprix ;pprix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld a,(taprx) ;taprx
 ld (tasx),a
 ld a,(tapry);tapry
 ld (tasy),a
 
 push de
 call clearsprite
 pop de

 call sompremio

 ld a,(tipopr) ;verifica tipo de prémio

 cp 0  ;bombas
 jr z,provc4bombas

 cp 1 ;tiros
 jr z,provc4tiros

 cp 2 ;vidas
 jr z,provc4vidas

 cp 3 ;pontos
 jr z,provc4pontos

provc4bombas:  ;atualiza as bombas
 ld a,(bombas)
 cp 10
 jp z,provc4
 inc a
 ld (bombas),a
 call atualizamaisbombas
 jp provc4

provc4tiros:  ;passa os tiros para dois
 ld a,1
 ld (tiros),a
 jp provc4

provc4vidas:  ;atualiza as vidas
 ld a,(vidas)
 cp 10
 jp z,provc4
 inc a
 ld (vidas),a
 call atualizamaisvidas
 jp provc4

provc4pontos:
 ld a,25 ;atualiza o score
 ld d,0
 ld e,a
 ld hl,(score)
 add hl,de
 ld (score),hl

 call atualizascore

provc4:

 call terminapremio
 jp fimlvc4premio

fimlvc4premio2:
 ld a,(premio)
 inc a
 ld (premio),a

fimlvc4premio:
 pop af
 dec a
 jp nz, lvc4premio

saiverificacolisao4:
 ret



;rate bomba
ratebomba:

 ld a,(ratebb)
 cp 0
 jr z, fimratebomba

 dec a
 ld (ratebb),a
 jp sairatebomba

fimratebomba:
 
 ld d,7 ;volume do canal C
 ld e,35
 call outer
 ld d,10 ;volume do canal C
 ld e,0
 call outer

sairatebomba:
 ret


;cria uma bomba e apaga todos os sprites do ecran
criabomba:

 ld a,(ratebb)
 cp 0
 jp nz, saicriabomba

 ld a,(bombas)
 cp 0
 jp z,saicriabomba
 dec a
 ld (bombas),a

 call atualizamenosbombas

;apaga todos os disparos
 ld a,(disparos)
 cp 0
 jp z, bombadisparosinimigos

 ld a,0
 ld (disparo),a

 ld a,(disparos)

lbombadisparos:
 push af

 ld a,(disparo)
 ld d,0
 ld e,a

;lê dados do disparo
 ld a,0
 ld (attr),a
 ld hl,lptiy ;ptiy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lptix ;ptix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld a,(tatx) ;tatx
 ld (tasx),a
 ld a,(taty);taty
 ld (tasy),a
 
 push de
 call clearsprite
 pop de

 call terminafire

 pop af
 dec a
 jp nz, lbombadisparos


;apaga todos os disparosinimigos
bombadisparosinimigos:
 ld a,(disparosini)
 cp 0
 jp z, bombainimigos

 ld a,0
 ld (disparoini),a

 ld a,(disparosini)

lbombadisparosinimigos:
 push af

 ld a,(disparoini)
 ld d,0
 ld e,a

;lê dados do disparo inimigo
 ld a,0
 ld (attr),a
 ld hl,lptiniiy ;ptiniiy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lptiniix ;ptiniix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld a,(tatinix) ;tatinix
 ld (tasx),a
 ld a,(tatiniy);tatiniy
 ld (tasy),a
 
 push de
 call clearsprite
 pop de

 call terminafireinimigo

 pop af
 dec a
 jp nz, lbombadisparosinimigos


;apaga todos os inimigos
bombainimigos:

 ld a,(inimigos)
 cp 0
 jp z, fimcriabomba

 call somgrandeexplosao

 ld a,0
 ld (inimigo),a

 ld a,(inimigos)

lbombainimigo:
 push af

 ld a,(inimigo)
 ld d,0
 ld e,a

;lê dados do inimigo
 ld hl,lpiiy ;piiy
 add hl,de
 ld a,(hl)
 ld (piiy),a
 ld hl,lpiix ;piix
 add hl,de
 ld a,(hl)
 ld (piix),a
 ld hl,lpify ;pify
 add hl,de
 ld a,(hl)
 ld (pify),a
 ld hl,lpifx ;pifx
 add hl,de
 ld a,(hl)
 ld (pifx),a
 ld hl,lpontosi ;pontosi
 add hl,de
 ld a,(hl)
 ld (pontosi),a
 ld hl,lhullicnt ;hullicnt
 add hl,de
 ld a,(hl)
 ld (hullicnt),a
 ld hl,ltipoi ;tipoi
 add hl,de
 ld a,(hl)
 ld (tipoi),a

;verifica se é um Boss
 cp 4
 jp c,procbi1

 ld a,(hullicnt)
 cp 5
 jp c,procbi1 ; se sim salta para o fim do Boss
 sub 5
 ld (hullicnt),a

 ld a,(inimigo)
 ld d,0
 ld e,a
 ld a,(hullicnt)
 ld hl,lhullicnt ;hullicnt
 add hl,de
 ld (hl),a

 ld a,0
 ld (mudanivel),a
 call criaexplosaoboss

 jp fimlbombainimigo2

procbi1:
;apaga o inimigo
 ld a,(inimigo)
 ld d,0
 ld e,a
 ld a,0
 ld (attr),a
 ld hl,lpiiy ;piiy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lpiix ;piix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld hl,ltaix ;taix
 add hl,de
 ld a,(hl)
 ld (tasx),a
 ld hl,ltaiy ;taiy
 add hl,de
 ld a,(hl)
 ld (tasy),a
 
 push de
 call clearsprite
 pop de

;se for um Boss cria os dados para as várias explosões do Boss
 ld a,(tipoi)
 cp 4
 jp c,procbi2

 ld a,1
 ld (mudanivel),a
 call criaexplosaoboss
 jp procbi3

procbi2:
;cria os dados para a explosão do inimigo
 ld a,(piiy)
 ld (pexploy),a
 ld a,(piix)
 ld (pexplox),a
 ld a,9
 ld (tempoexplo),a

 call criaexplosao
 call criapremio

procbi3:
 ld a,(pontosi) ;atualiza o score
 ld d,0
 ld e,a
 ld hl,(score)
 add hl,de
 ld (score),hl

 call atualizascore

 call terminainimigo
 jp fimlbombainimigo

fimlbombainimigo2:
 ld a,(inimigo)
 inc a
 ld (inimigo),a

fimlbombainimigo:
 pop af
 dec a
 jp nz, lbombainimigo

fimcriabomba:
 ld a,15
 ld (ratebb),a

saicriabomba: 
 ret



;rate contador do jogo
ratecounterjogo:

 ld a,(ratecnt)
 cp 0
 jr z, fimratecounterjogo
 dec a
 ld (ratecnt),a

fimratecounterjogo:
 ret


;incrementa o contador do jogo
incrementacounterjogo:

 ld a,(ratecnt)
 cp 0
 jp nz, saincrementacounterjogo

 ld a,(estado) ;Verifica se é um Boss
 cp 4
 jp nz, saincrementacounterjogo

 ld hl,(counter) ;incrementa o contador
 inc hl
 ld (counter),hl

 ld hl,(ltipoini) ;vai buscar o tipo de inimigo a criar
; ld hl,ltipoini ;;;;;;;;;;;;;;;;;;

 ld de,(counter)
 add hl,de
 ld a,(hl)
 ld (tipoini),a

 cp 255
 jp z, resetaratecnt

 ld hl,(linix) ;vai buscar a posição do inimigo a criar

 add hl,de
 ld a,(hl)
 ld (inix),a

 call criainimigo; cria inimigo

 ld a,(tipoini)
 cp 4
 jp nc, estado5

resetaratecnt:
 ld a,10
 ld (ratecnt),a

 jp saincrementacounterjogo

estado5:
 ld a,5
 ld (estado),a

saincrementacounterjogo:
 ret



;imprime o painel
printpainel:

;painel
 ld hl,(painel1) ;primeiro terço
 ld (offs),hl
 ld a,25
 ld (psix),a
 ld a,0
 ld (psiy),a
 ld a,7
 ld (tasx),a
 ld a,8
 ld (tasy),a
 ld a,57
 ld (atts),a
 call printsprite
 ld hl,(painel2) ;segundo terço
 ld (offs),hl
 ld a,25
 ld (psix),a
 ld a,8
 ld (psiy),a
 ld a,7
 ld (tasx),a
 ld a,8
 ld (tasy),a
 ld a,57
 ld (atts),a
 call printsprite
 ld hl,(painel3) ;terceiro terço
 ld (offs),hl
 ld a,25
 ld (psix),a
 ld a,16
 ld (psiy),a
 ld a,7
 ld (tasx),a
 ld a,8
 ld (tasy),a
 ld a,57
 ld (atts),a
 call printsprite

;score
 ld hl,tscore
 ld (texto),hl
 ld a,5
 ld (tatxt),a
 ld a,26
 ld (ptxtx),a
 ld a,3
 ld (ptxty),a
 ld a,56
 ld (attxt),a
 call printcar

;bombas
;primeira fila das bombas
 ld a,5
lpbombas:
 push af

 ld hl,(pbombas)
 ld (offs),hl
 add a,25
 ld (psix),a
 ld a,14
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,58
 ld (atts),a
 call printsprite

 pop af
 dec a
 jp nz, lpbombas

;segunda fila das bombas
 ld a,5
lpbombas2:
 push af

 ld hl,(pbombas)
 ld (offs),hl
 add a,25
 ld (psix),a
 ld a,16
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,58
 ld (atts),a
 call printsprite

 pop af
 dec a
 jp nz, lpbombas2

;apaga a última fila das bombas
 ld a,26
 ld (psix),a
 ld a,16
 ld (psiy),a
 ld a,5
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,63
 ld (atts),a
 call printattr


;vidas
;primeira fila das vidas
 ld a,5
lpvidas:
 push af

 ld hl,(pvidas)
 ld (offs),hl
 add a,25
 ld (psix),a
 ld a,7
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,56
 ld (atts),a
 call printsprite

 pop af
 dec a
 jp nz, lpvidas

;segunda fila das vidas
 ld a,5
lpvidas2:
 push af

 ld hl,(pvidas)
 ld (offs),hl
 add a,25
 ld (psix),a
 ld a,9
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,56
 ld (atts),a
 call printsprite

 pop af
 dec a
 jp nz, lpvidas2

;apaga a última fila das vidas
 ld a,26
 ld (psix),a
 ld a,9
 ld (psiy),a
 ld a,5
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,63
 ld (atts),a
 call printattr

;niveis
;nivel 1
 ld hl,(nivel1)
 ld (offs),hl
 ld a,26
 ld (psix),a
 ld a,21
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,57
 ld (atts),a
 call printsprite

;nivel 2
 ld hl,(nivel2p)
 ld (offs),hl
 ld a,27
 ld (psix),a
 ld a,21
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,56
 ld (atts),a
 call printsprite

;nivel 3
 ld hl,(nivel3p)
 ld (offs),hl
 ld a,28
 ld (psix),a
 ld a,21
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,56
 ld (atts),a
 call printsprite

;nivel 4
 ld hl,(nivel4p)
 ld (offs),hl
 ld a,29
 ld (psix),a
 ld a,21
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,56
 ld (atts),a
 call printsprite

;nivel 5
 ld hl,(nivel5p)
 ld (offs),hl
 ld a,30
 ld (psix),a
 ld a,21
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,56
 ld (atts),a
 call printsprite

 ret


;atualiza o nível no painel
atualizanivel:

 ld a,(nivel)

 cp 2
 jp z, atnivel2

 cp 3
 jp z, atnivel3

 cp 4
 jp z, atnivel4

 cp 5
 jp z, atnivel5

 cp 6
 jp z, atnivel6

atnivel2:
 ld hl,(nivel2)
 ld (offs2),hl
 ld hl,(nivel1p)
 ld (offs),hl
 jp proatnivel

atnivel3:
 ld hl,(nivel3)
 ld (offs2),hl
 ld hl,(nivel2p)
 ld (offs),hl
 jp proatnivel

atnivel4:
 ld hl,(nivel4)
 ld (offs2),hl
 ld hl,(nivel3p)
 ld (offs),hl
 jp proatnivel

atnivel5:
 ld hl,(nivel5)
 ld (offs2),hl
 ld hl,(nivel4p)
 ld (offs),hl
 jp proatnivel

atnivel6:
 ld hl,(nivel5p)
 ld (offs),hl

proatnivel:
;apaga o último nível
 ld a,(nivel)
 add a,24
 ld a,a
 ld (psix),a
 ld a,21
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,56
 ld (atts),a
 call printsprite

 ;acende o nível corrente
 ld hl,(offs2)
 ld (offs),hl
 ld a,(nivel)
 cp 6
 jp z,saiatualizanivel
 add a,25
 ld (psix),a
 ld a,21
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,57
 ld (atts),a
 call printsprite

saiatualizanivel:
 ret


;atualiza o aumento das bombas no painel
atualizamaisbombas:

 ;acende a bomba corrente na primeira fila
 ld a,(bombas)
 cp 6
 jp nc, amaisbombas2f
 add a,25
 ld (psix),a
 ld a,14
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,58
 ld (atts),a
 call printattr
 jp saiatualizamaisbombas

amaisbombas2f:
 ;acende a bomba corrente na segunda fila
 ld a,(bombas)
 add a,20
 ld (psix),a
 ld a,16
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,58
 ld (atts),a
 call printattr

saiatualizamaisbombas:
 ret


;atualiza a diminuição das bombas no painel
atualizamenosbombas:

;apaga a última bomba na primeira fila
 ld a,(bombas)
 cp 5
 jp nc, amenosbombas2f
 add a,26
 ld (psix),a
 ld a,14
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,63
 ld (atts),a
 call printattr
 jp saiatualizamenosbombas

amenosbombas2f:

;apaga a primeira bomba na segunda fila
 ld a,(bombas)
 add a,21
 ld (psix),a
 ld a,16
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,63
 ld (atts),a
 call printattr

saiatualizamenosbombas:
 ret


;atualiza o aumento das vidas no painel
atualizamaisvidas:

 ;acende a vida corrente na primeira fila
 ld a,(vidas)
 cp 6
 jp nc, amaisvidas2f
 add a,25
 ld (psix),a
 ld a,7
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,56
 ld (atts),a
 call printattr
 jp saiatualizamaisbombas

amaisvidas2f:
 ;acende a vida corrente na segunda fila
 ld a,(vidas)
 add a,20
 ld (psix),a
 ld a,9
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,56
 ld (atts),a
 call printattr

saiatualizamaisvidas:
 ret


;atualiza a diminuição das vidas no painel
atualizamenosvidas:

;apaga a última vida na primeira fila
 ld a,(vidas)
 cp 5
 jp nc, amenosvidas2f
 add a,26
 ld (psix),a
 ld a,7
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,63
 ld (atts),a
 call printattr
 jp fimtualizamenosvidas

amenosvidas2f:

;apaga a primeira vida na segunda fila
 ld a,(vidas)
 add a,21
 ld (psix),a
 ld a,9
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,63
 ld (atts),a
 call printattr

fimtualizamenosvidas:
 ld a,(vidas) ;verifica se as vidas acabaram
 cp 0
 jr nz,saiatualizamenosvidas

; ld a,1
; ld (vidas),a

 ld a,6
 ld (estado),a
 
saiatualizamenosvidas:
 ret


;atualiza o score no painel
atualizascore:

 ld hl,(score)
 ld de,tscore

 call num2dec

;score
 ld hl,tscore
 ld (texto),hl
 ld a,5
 ld (tatxt),a
 ld a,26
 ld (ptxtx),a
 ld a,3
 ld (ptxty),a
 ld a,56
 ld (attxt),a
 call printcar

 ret

;converte um número para string
num2dec:
 ld	bc,-10000
 call num1
 ld	bc,-1000
 call num1
 ld	bc,-100
 call num1
 ld	c,-10
 call num1
 ld	c,b

 ret

num1:
 ld	a,'0'-1
num2:
 inc a
 add hl,bc
 jr	c,num2
 sbc hl,bc
 ld	(de),a
 inc de

 ret


;atualiza o hiscore
atualizahiscore:

 ld hl,(score)
 ld de,(hiscore)
 and a
 sbc hl,de
 jp c, saiatualizahiscore

 ld hl,(score)
 ld (hiscore),hl
 
 ld hl,tscore
 ld de,thiscore

 inc de
 inc de
 inc de
 inc de
 inc de
 inc de
 inc de

 ld a,(hl) ;1
 ld (de),a
 inc hl
 inc de
 ld a,(hl) ;2
 ld (de),a
 inc hl 
 inc de
 ld a,(hl)
 ld (de),a ;3
 inc hl 
 inc de
 ld a,(hl)
 ld (de),a ;4
 inc hl 
 inc de
 ld a,(hl)
 ld (de),a ;5

saiatualizahiscore:
 ret



;imprime srite
printsprite:

 call printattr

 ld a,(psiy)
 ld (psiya),a

 ld a,(tasy)
 ld de,(offs)

loopn1:
 push af

 ld a,(psiya)
 cp 24
 jp c, priloopn1

 ld a,8
flloopn2:
 push af
 ld a,(tasx)
flloopn3:
 inc de
 dec a
 jr nz, flloopn3
 pop af
 dec a
 jr nz,flloopn2
 jp fimloopn1

priloopn1:
 ld a,8

 push af
 push de
 ld a,(psiya)
 cp 16
 jr c, terco2
 ld hl,20480
 sub 16
 cp 0
 jr z, fimterco
 ld b,a
 ld de,32
lterco1:
 add hl,de
 djnz lterco1
 jp fimterco

terco2:
 cp 8
 jr c, terco1
 ld hl,18432
 sub 8
 cp 0
 jr z, fimterco
 ld b,a
 ld de,32
lterco2:
 add hl,de
 djnz lterco2
 jp fimterco

terco1:
 ld hl,16384
 cp 0
 jr z, fimterco
 ld b,a
 ld de,32
lterco:
 add hl,de
 djnz lterco

fimterco:
 ld a,(psix)
 ld d,0
 ld e,a
 add hl,de
 ld (pos),hl
 pop de
 pop af

loopn2:
 push af
 push hl
 ld a,(tasx)

loopn3:
 push af
 ld a,(de)
 ld (hl),a
 pop af
 inc hl
 inc de
 dec a
 jr nz, loopn3

 pop hl
 inc h
 pop af
 dec a
 jr nz,loopn2

fimloopn1:
 ld a,(psiya)
 inc a
 ld (psiya),a
 pop af
 dec a
 jp nz,loopn1

 ret


;imprime atributo do sprite
printattr:

 ld a,(psiy)
 ld (psiya),a

 ld a,(tasy)
paloop1:
 push af 

 ld a,(psiya)
 cp 24
 jp c, pripaloopn1
 jp fimpaloopn1

pripaloopn1:
 ld hl,22528
 ld de,32
 ld a,(psiya)
 cp 0
 jr z, fimattrcor
attrcor:
 add hl,de
 dec a
 jr nz, attrcor
fimattrcor:
 ld a,(psix)
 ld d,0
 ld e,a
 add hl,de
 ld (posa),hl

 ld a,(tasx)
paloop2:
 push af
 ld a,(atts)
 ld (hl),a
 inc hl
 pop af
 dec a
 jr nz, paloop2

fimpaloopn1:
 ld a,(psiya)
 inc a
 ld (psiya),a
 pop af
 dec a
 jr nz, paloop1

 ret


;apaga sprite
clearsprite:

 ld a,7
 ld (atts),a
 call printattr

 ld a,(psiy)
 ld (psiya),a

 ld a,(tasy)

cnloopn1:
 push af

 ld a,(psiya)
 cp 24
 jp c, pricnloopn1
 jp fimcnloopn1

pricnloopn1:
 ld a,8

 push af
 ld a,(psiya)
 cp 16
 jr c, cnterco2
 ld hl,20480
 sub 16
 cp 0
 jr z, cnfimterco
 ld b,a
 ld de,32
cnlterco1:
 add hl,de
 djnz cnlterco1
 jp cnfimterco

cnterco2:
 cp 8
 jr c, cnterco1
 ld hl,18432
 sub 8
 cp 0
 jr z, cnfimterco
 ld b,a
 ld de,32
cnlterco2:
 add hl,de
 djnz cnlterco2
 jp cnfimterco

cnterco1:
 ld hl,16384
 cp 0
 jr z, cnfimterco
 ld b,a
 ld de,32
cnlterco3:
 add hl,de
 djnz cnlterco3

cnfimterco:
 ld a,(psix)
 ld d,0
 ld e,a
 add hl,de
 ld (pos),hl
 pop af

cnloopn2:
 push af
 push hl
 ld a,(tasx)

cnloopn3:
 push af
 ld a,(attr)
 ld (hl),a
 pop af
 inc hl
 dec a
 jr nz, cnloopn3

 pop hl
 inc h
 inc de
 pop af
 dec a
 jr nz, cnloopn2

fimcnloopn1:
 ld a,(psiya)
 inc a
 ld (psiya),a
 pop af
 dec a
 jr nz, cnloopn1

 ret


;limpa o ecrân
limpaecran:

 ld hl,16384
 ld b,192
lloop:
 ld a,32
lloop2:
 ld (hl),0
 inc hl
 dec a
 jr nz,lloop2
 djnz lloop

;ATRIBUTOS
 ld hl,22528
 ld b,24
cloop:
 ld a,32
cloop2:
 push af
 ld a,(attr)
 ld (hl),a
 pop af
 inc hl
 dec a
 jr nz,cloop2
 djnz cloop

;Border
 ld a,0
 call 8859

 ret


;apaga todos os atributos do écran a partir da linha y=5
apagaecran:

 ld hl,22688 ;y=5
 ld b,19
caloop:
 ld a,32
caloop2:
 push af
 ld a,(attr)
 ld (hl),a
 pop af
 inc hl
 dec a
 jr nz,caloop2
 djnz caloop

 ret



;imprime textos no écran
printcar:

 ld hl,(texto)
 ld a,(tatxt)

lprttxt:
 push hl
 push af
 ld a,(hl)
 sbc a,32 ;subtrai 32 para o começo da fonte
 ld hl,(fonte)
 ld d,0
 ld e,8

 cp 0
 jp z, provfx

vfx: ;múltiplica por 8
 add hl,de
 dec a
 cp 0
 jp nz, vfx

provfx:
 ld (offs),hl
 ld a,(ptxtx)
 ld (psix),a
 ld a,(ptxty)
 ld (psiy),a
 ld a,1
 ld (tasx),a
 ld a,1
 ld (tasy),a
 ld a,(attxt)
 ld (atts),a
 call printsprite

 ld a,(ptxtx)
 inc a
 ld (ptxtx),a

 pop af
 pop hl
 inc hl
 dec a
 cp 0
 jp nz, lprttxt

 ret



;imprime o menu
printmenu:

;limpa o écran
 call apagaecran

 ld a,2 ;imprime na parte de cima do écran
 call 5633           

 ld de,texto01
 ld bc,tatxt01-texto01
 call 8252

 ld a,1 ;imprime na parte de baixo do écran
 call 5633

 ld de,texto02
 ld bc,tatxt02-texto02
 call 8252

 ret


;imprime as instruções e os bónus
printinstrucoes:

;limpa o écran
 call apagaecran

;inimigo tipo 1
 ld hl,25576
 ld (offs),hl
 ld a,3
 ld (psix),a
 ld a,5
 ld (psiy),a
 ld a,3
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,5
 ld (atts),a
 call printsprite

;inimigo tipo 2
 ld hl,25696
 ld (offs),hl
 ld a,3
 ld (psix),a
 ld a,8
 ld (psiy),a
 ld a,3
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,4
 ld (atts),a
 call printsprite

;inimigo tipo 3
 ld hl,25816
 ld (offs),hl
 ld a,4
 ld (psix),a
 ld a,11
 ld (psiy),a
 ld a,2
 ld (tasx),a
 ld a,3
 ld (tasy),a
 ld a,7
 ld (atts),a
 call printsprite

;inimigo tipo 4
 ld hl,25928
 ld (offs),hl
 ld a,3
 ld (psix),a
 ld a,15
 ld (psiy),a
 ld a,3
 ld (tasx),a
 ld a,3
 ld (tasy),a
 ld a,3
 ld (atts),a
 call printsprite

;extra disparo
 ld hl,25416
 ld (offs),hl
 ld a,2
 ld (psix),a
 ld a,20
 ld (psiy),a
 ld a,2
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,69
 ld (atts),a
 call printsprite

;extra pontos
 ld hl,25544
 ld (offs),hl
 ld a,16
 ld (psix),a
 ld a,20
 ld (psiy),a
 ld a,2
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,67
 ld (atts),a
 call printsprite

 ld a,2 ;imprime na parte de cima do écran
 call 5633

 ld de,texto11
 ld bc,tatxt11-texto11
 call 8252

;extra bomba
 ld hl,25352
 ld (offs),hl
 ld a,2
 ld (psix),a
 ld a,22
 ld (psiy),a
 ld a,2
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,66
 ld (atts),a
 call printsprite

;extra live
 ld hl,25480
 ld (offs),hl
 ld a,16
 ld (psix),a
 ld a,22
 ld (psiy),a
 ld a,2
 ld (tasx),a
 ld a,2
 ld (tasy),a
 ld a,68
 ld (atts),a
 call printsprite

 ld a,1 ;imprime na parte de baixo do écran
 call 5633

 ld de,texto12
 ld bc,tatxt12-texto12
 call 8252

 ret


;imprime o recorde do dia
printrecorde:

;limpa o écran
 call apagaecran

 ld a,2 ;imprime na parte de cima do écran
 call 5633

;texto
 ld de,texto30
 ld bc,tatxt30-texto30
 call 8252

;hiscore
 ld de,thiscore
 ld bc,tathiscore-thiscore
 call 8252

 ret


;imprime o Well Done
printwelldone:

 call clearallsprites

 ld a,2 ;imprime na parte de cima do écran
 call 5633

;welldone
 ld de,texto32
 ld bc,tatxt32-texto32
 call 8252
 ret


;imprime o Game Over
printgameover:

 call clearallsprites

 ld a,2 ;imprime na parte de cima do écran
 call 5633

;game over
 ld de,texto31
 ld bc,tatxt31-texto31
 call 8252
 ret



;apaga todos os sprites do écran
clearallsprites:

;apaga todos os disparos
 ld a,(disparos)
 cp 0
 jp z, casdisparosinimigos

 ld a,0
 ld (disparo),a

 ld a,(disparos)

lcasdisparos:
 push af

 ld a,(disparo)
 ld d,0
 ld e,a

;lê dados do disparo
 ld a,0
 ld (attr),a
 ld hl,lptiy ;ptiy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lptix ;ptix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld a,(tatx) ;tatx
 ld (tasx),a
 ld a,(taty);taty
 ld (tasy),a
 
 push de
 call clearsprite
 pop de

 call terminafire

 pop af
 dec a
 jp nz, lcasdisparos


;apaga todos os disparosinimigos
casdisparosinimigos:
 ld a,(disparosini)
 cp 0
 jp z, casinimigos

 ld a,0
 ld (disparoini),a

 ld a,(disparosini)

lcasdisparosinimigos:
 push af

 ld a,(disparoini)
 ld d,0
 ld e,a

;lê dados do disparo inimigo
 ld a,0
 ld (attr),a
 ld hl,lptiniiy ;ptiniiy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lptiniix ;ptiniix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld a,(tatinix) ;tatinix
 ld (tasx),a
 ld a,(tatiniy);tatiniy
 ld (tasy),a
 
 push de
 call clearsprite
 pop de

 call terminafireinimigo

 pop af
 dec a
 jp nz, lcasdisparosinimigos


;apaga todos os inimigos
casinimigos:

 ld a,(inimigos)
 cp 0
 jp z, caspremios

 ld a,0
 ld (inimigo),a

 ld a,(inimigos)

lcasinimigos:
 push af

 ld a,(inimigo)
 ld d,0
 ld e,a

;lê dados do inimigo
 ld (attr),a
 ld hl,lpiiy ;piiy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lpiix ;piix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld hl,ltaix ;taix
 add hl,de
 ld a,(hl)
 ld (tasx),a
 ld hl,ltaiy ;taiy
 add hl,de
 ld a,(hl)
 ld (tasy),a
 
 push de
 call clearsprite
 pop de

 call terminainimigo

 pop af
 dec a
 jp nz, lcasinimigos


;apaga todos os prémios
caspremios:
 ld a,(premios)
 cp 0
 jp z, casexplosao

 ld a,0
 ld (premio),a

 ld a,(premios)

lcaspremios:
 push af

 ld a,(premio)
 ld d,0
 ld e,a

;lê dados do prémio
 ld a,0
 ld (attr),a
 ld hl,lppriy ;ppriy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lpprix ;pprix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld a,(taprx) ;taprx
 ld (tasx),a
 ld a,(tapry);tapry
 ld (tasy),a
 
 push de
 call clearsprite
 pop de

 call terminapremio

 pop af
 dec a
 jp nz, lcaspremios


;apaga todos as explosões
casexplosao:
 ld a,(explos)
 cp 0
 jp z, casnave

 ld a,0
 ld (explo),a

 ld a,(explos)

lcasexplosao:
 push af

 ld a,(explo)
 ld d,0
 ld e,a

;lê dados da explosão
 ld a,0
 ld (attr),a
 ld hl,lpexploy ;pexploy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,lpexplox ;pexplox
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld a,(taexplox) ;taexplox
 ld (tasx),a
 ld a,(taexploy);taexploy
 ld (tasy),a
 
 push de
 call clearsprite
 pop de

 call terminaexplosao

 pop af
 dec a
 jp nz, lcasexplosao


;apaga a nave
casnave:

;lê dados da nave
 ld a,0
 ld (attr),a
 ld hl,pniy ;pniy
 add hl,de
 ld a,(hl)
 ld (psiy),a
 ld hl,pnix ;pnix
 add hl,de
 ld a,(hl)
 ld (psix),a
 ld a,(tanx) ;tanx
 ld (tasx),a
 ld a,(tany);tany
 ld (tasy),a

 push de
 call clearsprite
 pop de

 ret



;produz o som de uma explosão - Canal A
somexplosao:

 ld d,7 ;mixer canais AB ruído, canal C tom
 ld e,35
 call outer
 ld d,8 ;volume do canal A: 16 - usa o envelope
 ld e,16
 call outer
 ld d,11 ;duração fine do envelope
 ld e,160
 call outer
 ld d,12 ;duração course do envelope
 ld e,15
 call outer
 ld d,13 ;tipo de envelope
 ld e,9
 call outer

 ret


;produz o som de uma grande explosão - Canais ABC
somgrandeexplosao:

 ld d,7 ;mixer canais ABC ruído
 ld e,7
 call outer
 ld d,8 ;volume do canal A: 16 - usa o envelope
 ld e,16
 call outer
 ld d,9 ;volume do canal B: 16 - usa o envelope
 ld e,16
 call outer
 ld d,10 ;volume do canal C: 16 - usa o envelope
 ld e,16
 call outer
 ld d,11 ;duração fine do envelope
 ld e,112
 call outer
 ld d,12 ;duração course do envelope
 ld e,23
 call outer
 ld d,13 ;tipo de envelope
 ld e,9
 call outer

 ret


;rate som disparo - dececrementa o som do Canal B
ratesfx01:

 ld a,(sfx01cnt)
 cp 0
 jr z, resetastx01

 dec a
 ld (sfx01cnt),a

 ld d,9 ;volume do canal B:
 ld e,a
 call outer

 jp fimratesfx01

resetastx01:
 ld a,0
 ld (sfx01),a

 ld a,0
 ld (sfx01cnt),a

fimratesfx01:
 ret


;produz o som do disparo - Canal B
somdisparo:

 ld d,7 ;mixer canais AB ruído, canal C tom
 ld e,35
 call outer
 ld d,9 ;volume do canal B:
 ld e,8
 call outer

 ld a,1
 ld (sfx01),a

 ld a,8
 ld (sfx01cnt),a

 ret


;rate som prémio - dececrementa o som do Canal C
ratesfx02:

 ld a,(sfx02cnt)
 cp 0
 jr z, resetastx02

 dec a
 ld (sfx02cnt),a

 ld d,10 ;volume do canal C
 ld e,a
 call outer

 jp fimratesfx02

resetastx02:
 ld a,0
 ld (sfx02),a

 ld a,0
 ld (sfx02cnt),a

fimratesfx02:
 ret


;produz o som do prémio - Canal C
sompremio:

 ld a,(tipopr)

 cp 0
 jp z,sompremio00

 cp 1
 jp z,sompremio01

 cp 2
 jp z,sompremio02

 cp 3
 jp z,sompremio03

sompremio00:
 ld a,(sfx0200f)
 ld (sfx02f),a
 ld a,(sfx0200c)
 ld (sfx02c),a
 jp lsompremio

sompremio01:
 ld a,(sfx0201f)
 ld (sfx02f),a
 ld a,(sfx0201c)
 ld (sfx02c),a
 jp lsompremio

sompremio02:
 ld a,(sfx0202f)
 ld (sfx02f),a
 ld a,(sfx0202c)
 ld (sfx02c),a
 jp lsompremio

sompremio03:
 ld a,(sfx0203f)
 ld (sfx02f),a
 ld a,(sfx0203c)
 ld (sfx02c),a

lsompremio:
 ld a,(sfx02f);fine picth do canal C
 ld d,4 
 ld e,a
 call outer
 ld a,(sfx02c);course picth do canal C
 ld d,5 
 ld e,a
 call outer
 ld d,7 ;mixer canais AB ruído, canal C tom
 ld e,35
 call outer
 ld d,10 ;volume do canal C:
 ld e,15
 call outer

 ld a,1
 ld (sfx02),a

 ld a,15
 ld (sfx02cnt),a

 ret


;coloca os valores do som nos respetivos portos
outer:

 ld bc,ayctrl
 out (c),d
 ld bc,aydata
 out (c),e

 ret


;inicializa o leitor da música
inicializamusica:

 ld d,0 ;fine picth do canal A
 ld e,0
 call outer
 ld d,1 ;course picth do canal A
 ld e,0
 call outer
 ld d,2 ;fine picth do canal B
 ld e,0
 call outer
 ld d,3 ;course picth do canal B
 ld e,0
 call outer
 ld d,4 ;fine picth do canal C
 ld e,0
 call outer
 ld d,5 ;course picth do canal C
 ld e,0
 call outer
 ld d,7 ;mixer: tom nos canais ABC
 ld e,56
 call outer
 ld d,6 ;picth do ruído
 ld e,31
 call outer
 ld d,8 ;volume do canal A:
 ld e,0
 call outer
 ld d,9 ;volume do canal B
 ld e,0
 call outer
 ld d,10 ;volume do canal C
 ld e,0
 call outer
 ld d,11 ;duração fine do envelope
 ld e,184
 call outer
 ld d,12 ;duração course do envelope
 ld e,11
 call outer
 ld d,13 ;tipo de envelope
 ld e,9
 call outer

 ld hl,1000
 ld (ratemus),hl

 ld hl,0
 ld (countermus),hl

 ret


;rate contador do player da música
ratecountermusica:

 ld hl,(ratemus)
 ld d,0
 ld e,1
 sbc hl,de
 jp z, zeraratemusica 
 ld (ratemus),hl
 jp fimratecountermusica

zeraratemusica:
 ld hl,0
 ld (ratemus),hl

fimratecountermusica:
 ret


;player da música
playermusica:

 ld hl,(ratemus)
 ld d,0
 ld e,1
 sbc hl,de
 jp nz, saiplayermusica

;canal A  
 ld de,(countermus)

 ld hl,(musica) ;vai as notas a serem tocadas
 add hl,de
 ld a,(hl)

 cp 255
 jp z, canalb ;salta para o canal B

 push de
 push hl
 ld hl,(fine) ;vai buscar o fine picth do canal A
 ld d,0
 ld e,a
 add hl,de
 push af
 ld a,(hl)
 ld (fa),a
 pop af

 ld hl,(course) ;vai buscar o course picth do canal A
 ld d,0
 ld e,a
 add hl,de
 push af
 ld a,(hl)
 ld (ca),a
 pop af

 ld hl,(mixer) ;vai buscar o mixer do canal A
 ld d,0
 ld e,a
 add hl,de
 push af
 ld a,(hl)
 ld (ma),a
 pop af

 ld hl,(volume) ;vai buscar o volume do canal A
 ld d,0
 ld e,a
 add hl,de
 push af
 ld a,(hl)
 ld (va),a
 pop af

 ld a,(fa);fine picth do canal A
 ld d,0
 ld e,a
 call outer
 ld a,(ca) ;course picth do canal A
 ld d,1
 ld e,a
 call outer
 ld a,(ma);mixer do canal A
 ld d,7
 ld e,a
 call outer
 ld a,(va) ;volume do canal A
 ld d,8
 ld e,a
 call outer
 ld d,13 ;tipo de envelope
 ld e,9
 call outer
 pop hl
 pop de

;canal B
canalb:
 inc de
 ld (countermus),de

 ld hl,(musica) ;vai as notas a serem tocadas
 add hl,de
 ld a,(hl)

 cp 255
 jp z, canalc ;salta para o canal C

 push de
 push hl
 ld hl,(fine) ;vai buscar o fine picth do canal B
 ld d,0
 ld e,a
 add hl,de
 push af
 ld a,(hl)
 ld (fb),a
 pop af

 ld hl,(course) ;vai buscar o course picth do canal B
 ld d,0
 ld e,a
 add hl,de
 push af
 ld a,(hl)
 ld (cb),a
 pop af

 ld hl,(mixer) ;vai buscar o mixer do canal B
 ld d,0
 ld e,a
 add hl,de
 push af
 ld a,(hl)
 ld (mb),a
 pop af

 ld hl,(volume) ;vai buscar o volume do canal B
 ld d,0
 ld e,a
 add hl,de
 push af
 ld a,(hl)
 ld (vb),a
 pop af

 ld a,(fb);fine picth do canal B
 ld d,2
 ld e,a
 call outer
 ld a,(cb) ;course picth do canal B
 ld d,3
 ld e,a
 call outer
 ld a,(vb) ;volume do canal B
 ld d,9
 ld e,a
 call outer
 ld d,13 ;tipo de envelope
 ld e,9
 call outer
 pop hl
 pop de

;canal C
canalc:
 inc de
 ld (countermus),de

 ld hl,(musica) ;vai as notas a serem tocadas
 add hl,de
 ld a,(hl)

 cp 255
 jp z, fimcanais ;salta para o fim dos canais

 push de
 push hl
 ld hl,(fine) ;vai buscar o fine picth do canal c
 ld d,0
 ld e,a
 add hl,de
 push af
 ld a,(hl)
 ld (fc),a
 pop af

 ld hl,(course) ;vai buscar o course picth do canal C
 ld d,0
 ld e,a
 add hl,de
 push af
 ld a,(hl)
 ld (cc),a
 pop af

 ld hl,(mixer) ;vai buscar o mixer do canal C
 ld d,0
 ld e,a
 add hl,de
 push af
 ld a,(hl)
 ld (mc),a
 pop af

 ld hl,(volume) ;vai buscar o volume do canal C
 ld d,0
 ld e,a
 add hl,de
 push af
 ld a,(hl)
 ld (vc),a
 pop af

 ld a,(fc);fine picth do canal C
 ld d,4
 ld e,a
 call outer
 ld a,(cc) ;course picth do canal C
 ld d,5
 ld e,a
 call outer
 ld a,(vc) ;volume do canal C
 ld d,10
 ld e,a
 call outer
 ld d,13 ;tipo de envelope
 ld e,9
 call outer
 pop hl
 pop de

fimcanais:
 ld hl,6483
 inc de
 ld (countermus),de

 sbc hl,de
 jp nz,resetaratemus

 ld de,0
 ld (countermus),de

resetaratemus:
 ld hl,1000
 ld (ratemus),hl

 jp saiplayermusica

saiplayermusica:
 ret


.end