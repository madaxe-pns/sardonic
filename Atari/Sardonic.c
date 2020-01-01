/**************************************************************************************

	Sardonic
	
	Code & Graphics by MadAxe
	Music by Fred
	
	(C) 2020 Penisoft

	Made in Portugal
	
**************************************************************************************/

/* Default Includes */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Atari Includes */
#include <tos.h>

/* GODLib Includes */
#include	<GODLIB\GEMDOS\GEMDOS.H>
#include	<GODLIB\FILE\FILE.H>
#include	<GODLIB\FONT8X8\FONT8X8.H>
#include	<GODLIB\IKBD\IKBD.H>
#include	<GODLIB\PLATFORM\PLATFORM.H>
#include	<GODLIB\PICTYPES\DEGAS.H>
#include	<GODLIB\SCREEN\SCREEN.H>
#include	<GODLIB\SPRITE\SPRITE.H>
#include	<GODLIB\VBL\VBL.H>
#include	<GODLIB\VIDEO\VIDEO.H>

/* My Defines */
#define NUMINIS 15			/* Número de Sprites de Inimigos */
#define NUMPREMIOS 6		/* Número de Sprites de Prémios */
#define NUMEXPLOS 4			/* Número de Sprites de Explosões */
#define NUMTIROS 2			/* Número de Sprites de Tiros */
#define NUMTIROSINI 2		/* Número de Sprites de Tiros Inimigos */
#define NUMNAVES 2			/* Número de Sprites da Nave */

#define MAXINI 6			/* Número Máximo de Inimigos no Écran */
#define MAXTIRO 8			/* Número Máximo de Tiros no Écran */
#define MAXTIROINI 8		/* Número Máximo de Tiros Inimigos no Écran */
#define	MAXEXPLO 8			/* Número Máximo de Explosões no Écran */
#define MAXPREMIO 6			/* Número Máximo de Prémios no Écran */
#define MAXSTAR 10			/* Número Máximo de Estrelas no Écran */

#define MAXVIDAS 9			/* Número Máximo de Vidas */
#define MAXBOMBAS 9 		/* Número Máximo de Bombas */

#define NUMWAVES 132		/* Número de Tipos de Attack Waves */
#define MAXWAVE 256			/* Número Máximo de Attack Waves */
#define MAXFPATH 46 		/* Número Máximo de Formation Paths */

#define MAXX 247			/* Máxima resolução horizontal */
#define MAXY 199			/* Máxima resolução vertical */
#define MINX 0				/* Máxima resolução horizontal */
#define MINY 0				/* Máxima resolução vertical */

#define ARMOUR 200			/* Tempo da Invencibilidade */
#define PRMTEMPO 125		/* Tempo que os Prémios ficam disponíveis */
#define RTINIPM 40			/* Intervalo de Tempo entre os Tiros dos Inimigos Pequenos/Médios */
#define RTINIBS 25			/* Intervalo de Tempo entre os Tiros dos Inimigos Bosses */

#define MAXNOTAS 2161		/* Número Máximo de Notas da Música */
#define MAXINSTRS 110		/* Número Máximo de Instrumentos da Música */
#define MUSTEMPO 23			/* Tempo da Música */

/* GodLib Prototypes */
void JagPad_PacketDisplay( const U8 aPacket );

/* My Prototypes */
void ScreenInit( void );

void inicializa(void);
void mainloop(void);

void titulo(void);
void mainmenu(void);
void instrucoes(void);
void hiscore(void);

void initvar(void);
void desenhapainel(void);
void gameloop(void);
int vercriaini(int wcnt);

void gameover(void);
void welldone(void);

void clearsprites(void);
void printsprites(void);
void clearscreen(void);

void movenave(void);

int colrect(int xi1,int yi1,int xf1,int yf1,int xi2,int yi2,int xf2,int yf2);

void verificacolisao1(void);
void verificacolisao2(void);
void verificacolisao3(void);
void verificacolisao4(void);

void perdevida(void);
void ganhavida(void);
void ganhabomba(void);
void perdebomba(void);
void ganhapontos(int pts);
void mudanivel(void);

void criadisparo(int ntx,int nty,int ntp);
void movedisparo(void);
void apagadisparo(int i);

void preparadisparoinimigo(int i);
void criadisparoinimigo(int ntix,int ntiy,int ntp);
void movedisparoinimigo(void);
void apagadisparoinimigo(int i);

void criaexplosaoboss(int ntx,int nty);

void criaexplosao(int ntx,int nty);
void moveexplosao(void);
void apagaexplosao(int i);

void criabomba(void);

void criapremio(int ntx,int nty);
void movepremio(void);
void apagapremio(int i);

void movestar(void);

void criainimigo(int wcnt,int wcnt2);
void moveinimigo(void);
void apagainimigo(int i);

/* Verticalmente Baixo */
int mvinivert(int i);
int mvinivertsindir(int i);
int mvinivertcircledir(int i);
int mvinivertsinesq(int i);
int mvinivertcircleesq(int i);

/* Circular */
void mvinicircledirnoxy(int i);
void mvinicircleesqnoxy(int i);

/* Horizontalmente Direita */
int mvinihorzdir(int i);
int mvinihorzdirsindown(int i);
int mvinihorzdircircledown(int i);
int mvinihorzdirsinup(int i);
int mvinihorzdircircleup(int i);

/* Horizontalmente Esquerda */
int mvinihorzesq(int i);
int mvinihorzesqsindown(int i);
int mvinihorzesqcircledown(int i);
int mvinihorzesqsinup(int i);
int mvinihorzesqcircleup(int i);

/* Diagonalmente */
int mvinidiadirdown(int i);
int mvinidiadirup(int i);
int mvinidiaesqdown(int i);
int mvinidiaesqup(int i);

/* Sinusoidal */
void mvinisindirnoxy(int i);
void mvinisinesqnoxy(int i);

/* Verticalmente mais Circular Direita / Esquerda*/
void mvinivertmaiscircledir(int i);
void mvinivertmaiscircleesq(int i);

/* Verticalmente mais Sinusoidal Direita / Esquerda */
void mvinivertmaissindir(int i);
void mvinivertmaissinesq(int i);

/* Verticalmente mais Vertical Sinusoidal Direita / Esquerda */
void mvinivertmaisvertsindir(int i);
void mvinivertmaisvertsinesq(int i);

/* Verticalmente mais Diagonal Direita / Esquerda */
void mvinivertmaisdiadir(int i);
void mvinivertmaisdiaesq(int i);

/* Verticalmente mais Vertical Circular Direita / Esquerda */
void mvinivertmaisvertcircledir(int i);
void mvinivertmaisvertcircleesq(int i);

/* Horizontalmente Direita mais Diagonal Cima / Baixo */
void mvinihorzdirmaisdiaup(int i);
void mvinihorzdirmaisdiadown(int i);

/* Horizontalmente Direita mais Horizontal Circular Cima / Baixo */
void mvinihorzdirmaishorcircleup(int i);
void mvinihorzdirmaishorcircledown(int i);

/* Horizontalmente Esquerda mais Diagonal Cima / Baixo */
void mvinihorzesqmaisdiaup(int i);
void mvinihorzesqmaisdiadown(int i);

/* Horizontalmente Esquerda mais Horizontal Circular Cima / Baixo */
void mvinihorzesqmaishorcircleup(int i);
void mvinihorzesqmaishorcircledown(int i);

/* Diagonalmente Direita Baixo mais Diagonal Direita Cima */
void mvinidiadirdownmaisdiadirup(int i);

/* Diagonalmente Esquerda Baixo mais Diagonal Esquerda Cima */
void mvinidiaesqdownmaisdiaesqup(int i);

/* Diagonalmente Direita Baixo mais Vertical*/
void mvinidiadirdownmaisvert(int i);

/* Diagonalmente Esquerda Baixo mais Vertical*/
void mvinidiaesqdownmaisvert(int i);

/* Música e Som */
void inicializamusica(void);
void somexplosao(void);
void sombomba(void);
void decsomdisparo(void);
void somdisparo(void);
void decsompremio(void);
void sompremio(int i);

/* Ficheiros e Tipos de Inimigos */
int letabsincos(void);
int getsprites(void);
void freesprites(void);
void criatipoini(void);

/* Carrega as Attack Waves e a Sequência de Attack Waves */
int loadwaves(void);

/* Rotinas da Música */
int lemusica(void);
int leinstrumentos(void);
void musicplayer(void);


/* GODLib Variables */
sDegas			*gpPicture;
sGraphicPos		lPos;
sGraphicRect	lRect;

sGraphicPos		lPosSavedIni[MAXINI][2],lPosSavedNv[2];
sGraphicPos		lPosSavedTiro[MAXTIRO][2];
sGraphicPos		lPosSavedTiroIni[MAXTIROINI][2];
sGraphicPos		lPosSavedExplo[MAXEXPLO][2];
sGraphicPos		lPosSavedPremio[MAXPREMIO][2];

sSprite 		*lpSpriteIni[NUMINIS],*lpSpriteNv[NUMNAVES];
sSprite			*lpSpriteTiro[NUMTIROS],*lpSpriteTiroIni[NUMTIROSINI];
sSprite			*lpSpriteExplo[NUMEXPLOS];
sSprite			*lpSpritePremio[NUMPREMIOS];
sSprite			*lpSpriteTitle;
sSprite			*lpSpritePainel;

U16 			*lpMskIni[NUMINIS],*lpMskNv[NUMNAVES];
U16				*lpMskTiro[NUMTIROS],*lpMskTiroIni[NUMTIROSINI];
U16				*lpMskExplo[NUMEXPLOS];
U16				*lpMskPremio[NUMPREMIOS];
U16				*lpMskTitle;
U16				*lpMskPainel;

U8 				aPacket;

sGraphicPos		lPosStar[10],lPosSavedStar[10][2];

/* My Variables */
int inimigos;
int tipini;
int xpos,ypos,rfact;
int tiros,ratetiro;
int tirosini,ratetiroini,rtini;
int explosoes;
int premios,premiocnt;

int nx,ny,ntiro;
int ntx,nty;
int ninvenc;
int nspeed;

int counter;
int estado;

int vidas;
int bombas;
int recorde;
int pontos;
int ratebomba;
int nivel;

unsigned short wave[MAXWAVE];
int wcnt,wcnt2,tpini;
float tsincos[2][126];

int ratestar;

int reg=128;
int sfx01;
float sfx02;

time_t time1,time2;
clock_t tmus1,tmus2;

int nota,musica;
int fine,course,mixer,volume;

unsigned short sawnaw[2];
unsigned short nwaves,mwaves;


/* Definição dos Tipos dos Inimigos */
struct tipoinis
{
		int tx,ty;
		int hull;
		int speed;
		int pontos;
};

/* Definição dos Inimigos */
struct inis
{
	int x,y;
	int tx,ty;
	int tipo;
	int fpath;
	int hull;
	int speed;
	int pontos;
	int r;
};

/* Definição dos Tiros */
struct stiros
{
	int x,y;
	int tx,ty;
	int tipo;
};

/* Definição dos Tiros Inimigos */
struct stirosini
{
	int x,y;
	int tx,ty;
	int tipo;
};

/* Definição das Explosões */
struct sexplos
{
	int x,y;
	int tx,ty;
	int fase;
	int tempo;
};

/* Definição dos Prémios */
struct spremios
{
	int x,y;
	int tx,ty;
	int tipo;
	int tempo;
	int cnt;
};

/* Definição das Attack Waves */
struct twaves
{
	unsigned char pini[MAXINI];
	unsigned char inis[MAXINI];
	unsigned char xx[MAXINI];
	unsigned char yy[MAXINI];
	unsigned char fpath[MAXINI];
};

/* Definição das Notas da Música */
struct tnotas
{
	unsigned char ca;
	unsigned char cb;
	unsigned char cc;
};

/* Definição dos Instrumentos da Música */
struct tinstrs
{
	unsigned char fin;
	unsigned char cou;
	unsigned char mix;
	unsigned char vol;
};

struct tipoinis tipoini[NUMINIS];
struct inis ini[MAXINI];
struct stiros tiro[MAXTIRO];
struct stirosini tiroini[MAXTIROINI];
struct sexplos explo[MAXEXPLO];
struct spremios premio[MAXPREMIO];
struct twaves twave[NUMWAVES];

struct tnotas notas[MAXNOTAS];
struct tinstrs instrs[MAXINSTRS];

/* Main */
S16	GodLib_Game_Main(void)
{

	if (letabsincos()!=0)
		return(1);
	
	if (loadwaves()!=0)
		return(1);
	
	if (lemusica()!=0)
		return(1);
	
	if (leinstrumentos()!=0)
		return(1);
	
	GemDos_Super( 0 );
	Platform_Init();

	if (getsprites()!=0)
	{
		Platform_DeInit();
		return(1);
	}
	
	inicializa();
	ScreenInit();
	mainloop();
				
	freesprites();
			
	Platform_DeInit();
		
	return(0);
	
}

/* Inicializa o Écran em Modo LowRes: 320x200x16 */
void ScreenInit( void )
{
	
	Screen_Init( 320, 200, eGRAPHIC_COLOURMODE_4PLANE, eSCREEN_SCROLL_NONE );
	
}

/* Inicializa */
void inicializa(void)
{
	
	recorde=0;
	
	estado=9;
	
	criatipoini();
	inicializamusica();

}

/* Loop Principal */
void mainloop(void)
{

	while (estado!=10)
	{
		switch (estado)
		{
			case 0:mainmenu();break;
			case 1:instrucoes();break;
			case 2:hiscore();break;
			case 3:initvar();break;
			case 4:gameloop();break;
			case 6:gameover();break;
			case 7:welldone();break;
			case 9:titulo();break;
		}
	}
	
}

/* Título - Estado=9 */
void titulo(void)
{
	
	clearscreen();
	
	lPos.mX=66;
	lPos.mY=0;
	Screen_Physic_DrawSprite_Clip(&lPos,lpSpriteTitle);
	
	Graphic_SetBlitterEnable(1);
	
	estado=0;
	musica=0;
	tmus1=clock();

}

/* Menu Principal - Estado=0 */
void mainmenu()
{

	IKBD_ClearBuffer();

	lRect.mX=0;
	lRect.mY=18;
	lRect.mWidth=320;
	lRect.mHeight=182;
	
	Screen_Physic_DrawBox(&lRect,0);
	
	time1=time(NULL);
		
	if(Graphic_GetBlitterEnable())
		Font8x8_Print( "Blitter is ON",Screen_GetpPhysic(),108,32);
	else
		Font8x8_Print( "Blitter is OFF",Screen_GetpPhysic(),104,32);

	Font8x8_Print("Joystick : Directions",Screen_GetpPhysic(),76,56);
	Font8x8_Print("Fire Button : Fire",Screen_GetpPhysic(),88,72);
	Font8x8_Print("Space : Bomb",Screen_GetpPhysic(),112,88);
			
	Font8x8_Print("Fire to Start",Screen_GetpPhysic(),112,112);
	Font8x8_Print("Escape to Quit",Screen_GetpPhysic(),104,128);
	
	Font8x8_Print("Code & Graphics : MadAxe",Screen_GetpPhysic(),64,152);
	Font8x8_Print("Music : Mod Synth by Fred",Screen_GetpPhysic(),64,168);
	
	Font8x8_Print("(C) 2020 Penisoft",Screen_GetpPhysic(),96,192);
	
	while (estado==0)
	{
		
		tmus2=clock();
		if (tmus2>tmus1+MUSTEMPO)
		{
			musicplayer();
			tmus1=clock();
		}
		
		time2=time(NULL);
		if (time2>time1+15) estado=1;
		
		aPacket=IKBD_GetJoy1Packet();
		if( aPacket & 128 ) estado=3;
		if (IKBD_GetKeyStatus(eIKBDSCAN_ESC)) estado=10;
	};

	IKBD_ClearBuffer();
	
}

/* Instruções - Estado=1 */
void instrucoes(void)
{
	
	lRect.mX=0;
	lRect.mY=18;
	lRect.mWidth=320;
	lRect.mHeight=182;
	
	Screen_Physic_DrawBox(&lRect,0);

	time1=time(NULL);
		
	/* Inimigos */
	lPos.mX=59;lPos.mY=32;
	Screen_Physic_DrawSprite_Clip(&lPos,lpSpriteIni[0]);
	Font8x8_Print("Scout      :  5 Points",Screen_GetpPhysic(),88,36);
	
	lPos.mX=57;lPos.mY=48;
	Screen_Physic_DrawSprite_Clip(&lPos,lpSpriteIni[6]);
	Font8x8_Print("Fighter I  : 10 Points",Screen_GetpPhysic(),88,52);
	
	lPos.mX=56;lPos.mY=68;
	Screen_Physic_DrawSprite_Clip(&lPos,lpSpriteIni[7]);
	Font8x8_Print("Fighter II : 20 Points",Screen_GetpPhysic(),88,72);
	
	lPos.mX=57;lPos.mY=86;
	Screen_Physic_DrawSprite_Clip(&lPos,lpSpriteIni[8]);
	Font8x8_Print("Stealth    : 30 Points",Screen_GetpPhysic(),88,94);
	
	lPos.mX=57;lPos.mY=112;
	Screen_Physic_DrawSprite_Clip(&lPos,lpSpriteIni[9]);
	Font8x8_Print("Bomber     : 50 Points",Screen_GetpPhysic(),88,120);
	
	/* Prémios */
	lPos.mX=40;lPos.mY=152;
	Screen_Physic_DrawSprite_Clip(&lPos,lpSpritePremio[0]);
	Font8x8_Print("Extra Live",Screen_GetpPhysic(),56,154);
	
	lPos.mX=40;lPos.mY=168;
	Screen_Physic_DrawSprite_Clip(&lPos,lpSpritePremio[1]);
	Font8x8_Print("Extra Fire",Screen_GetpPhysic(),56,170);
	
	lPos.mX=40;lPos.mY=184;
	Screen_Physic_DrawSprite_Clip(&lPos,lpSpritePremio[2]);
	Font8x8_Print("Extra Bomb",Screen_GetpPhysic(),56,186);
	
	lPos.mX=176;lPos.mY=152;
	Screen_Physic_DrawSprite_Clip(&lPos,lpSpritePremio[3]);
	Font8x8_Print("Extra Points",Screen_GetpPhysic(),192,154);
	
	lPos.mX=176;lPos.mY=168;
	Screen_Physic_DrawSprite_Clip(&lPos,lpSpritePremio[4]);
	Font8x8_Print("Extra Armour",Screen_GetpPhysic(),192,170);
	
	lPos.mX=176;lPos.mY=184;
	Screen_Physic_DrawSprite_Clip(&lPos,lpSpritePremio[5]);
	Font8x8_Print("Extra Speed",Screen_GetpPhysic(),192,186);
		
	while (estado==1)
	{
		
		tmus2=clock();
		if (tmus2>tmus1+MUSTEMPO)
		{
			musicplayer();
			tmus1=clock();
		}
		
		time2=time(NULL);
		if (time2>time1+15) estado=2;
		
		aPacket=IKBD_GetJoy1Packet();
		if( aPacket & 128 ) estado=3;
		if (IKBD_GetKeyStatus(eIKBDSCAN_ESC)) estado=10;
	};

	IKBD_ClearBuffer();
	
}

/* HiScore - Estado=2 */
void hiscore(void)
{
	
	char txrec[6]="00000\0";
	
	lRect.mX=0;
	lRect.mY=18;
	lRect.mWidth=320;
	lRect.mHeight=182;
	
	Screen_Physic_DrawBox(&lRect,0);

	time1=time(NULL);
		
	Font8x8_Print("Hiscore of the Day",Screen_GetpPhysic(),88,64);
	
	if (recorde!=0) sprintf(txrec, "%5d",recorde);
	
	Font8x8_Print(txrec,Screen_GetpPhysic(),140,88);
		
	while (estado==2)
	{
		
		tmus2=clock();
		if (tmus2>tmus1+MUSTEMPO)
		{
			musicplayer();
			tmus1=clock();
		}
		
		time2=time(NULL);
		if (time2>time1+15) estado=0;
		
		aPacket=IKBD_GetJoy1Packet();
		if( aPacket & 128 ) estado=3;
		if (IKBD_GetKeyStatus(eIKBDSCAN_ESC)) estado=10;
	};

	IKBD_ClearBuffer();	
	
}

/* Inicializa as variáveis - Estado=3 */
void initvar(void)
{
	
	int i;
	
	clearscreen();
	
	inimigos=0;
	
	tiros=0;
	ratetiro=0;
	
	tirosini=0;
	ratetiroini=0;
	rtini=RTINIPM;
	
	explosoes=0;
	premios=0;
	
	premiocnt=5;
	
	vidas=5;
	bombas=5;
	ratebomba=0;
	
	pontos=0;
	nivel=1; 
		
	nx=116;
	ny=184;
	ntx=16;
	nty=16;
	ntiro=0;
	ninvenc=0;
	nspeed=2;
	
	desenhapainel();
	
	ratestar=2;
	for (i=0; i<MAXSTAR; i++)
	{
		lPosStar[i].mX=random(MAXX);
		lPosStar[i].mY=random(MAXY);
		
		lPosSavedStar[i][0]=lPosStar[i];
		lPosSavedStar[i][1]=lPosStar[i];
	}
	
	inicializamusica();
	
	estado=4;
		
}

/* Desenha o Painel */
void desenhapainel(void)
{
	
	char txpnl[5];
	
	lPos.mX=239;
	lPos.mY=0;
	Screen_Physic_DrawSprite_Clip(&lPos,lpSpritePainel);
	Screen_Logic_DrawSprite_Clip(&lPos,lpSpritePainel);
	
	/* Pontos */
	sprintf(txpnl, "%5d",pontos);
	Font8x8_Print(txpnl,Screen_GetpLogic(),264,32);
	Font8x8_Print(txpnl,Screen_GetpPhysic(),264,32);
	
	/* Vidas */	
	sprintf(txpnl, "%d",vidas);
	Font8x8_Print(txpnl,Screen_GetpLogic(),280,80);
	Font8x8_Print(txpnl,Screen_GetpPhysic(),280,80);
	
	/* Bombas */	
	sprintf(txpnl, "%d",bombas);
	Font8x8_Print(txpnl,Screen_GetpLogic(),280,128);
	Font8x8_Print(txpnl,Screen_GetpPhysic(),280,128);
	
	/* Nível */	
	sprintf(txpnl, "%d",nivel);
	Font8x8_Print(txpnl,Screen_GetpLogic(),264+(8*(5-nivel)),176);
	Font8x8_Print(txpnl,Screen_GetpPhysic(),264+(8*(5-nivel)),176);
	
}

/* Rotina Principal do Jogo - Estado=4 */
void gameloop(void)
{

	IKBD_ClearBuffer();
	
	counter=0; /* Inicializa o Contador do Jogo */
	
	do
	{
		wcnt=wave[counter];	/* Vai buscar a respetiva Attack Wave à Sequência de Attack Waves */
		inimigos=0;
		wcnt2=0;
		tpini=0;
	
		while (vercriaini(wcnt)==0 && estado==4)
		{
			clearsprites(); 
			
			if (inimigos>0) moveinimigo();
			
			if (ratetiro>0) ratetiro--;
			if (tiros>0) movedisparo();
			
			if (ratetiroini>0) ratetiroini--;
			if (tirosini>0) movedisparoinimigo();
			
			if (ratebomba>0) ratebomba--;
			
			if (inimigos>0 && tiros>0) verificacolisao1(); 
			if (tirosini>0) verificacolisao2();
			if (inimigos>0)	verificacolisao3();
			if (premios>0) verificacolisao4();
			
			if (explosoes>0) moveexplosao();
			
			if (premios>0) movepremio();

			if (ninvenc>0) ninvenc--;
			movenave();
			
			if (ratestar>0) ratestar--;
			movestar();
			
			if (sfx01>0) decsomdisparo();
			if (sfx02>0) decsompremio();
			
			printsprites();

			/* Quit */
			if (IKBD_GetKeyStatus(eIKBDSCAN_ESC)) estado=6;
		}
			
		counter++;
		
		/* Desativa o Blitter nos Bosses dos Finais de Nível */
		if (counter==49 || counter==99 || counter==149 || counter==199 || counter==254)
		{
			rtini=RTINIBS;
			Graphic_SetBlitterEnable(0);
		}
		
		/* Desativa o Blitter nos Bosses Intermédios do Último Nível */
		if (counter==209 || counter==219 || counter==229 || counter==239)
		{
			rtini=RTINIBS;
			Graphic_SetBlitterEnable(0);
		}
		
		/* Ativa o Blitter depois dos Bosses Intermédios do Último Nível */
		if (counter==210 || counter==220 || counter==230 || counter==240)
		{
			rtini=RTINIPM;
			Graphic_SetBlitterEnable(1);
			desenhapainel();
		}
		
					
	} while (counter<MAXWAVE && estado==4); /* Prossegue até WellDone, GameOver ou Exit */
	
	/* WellDone */
	if (counter>=MAXWAVE) estado=7;
	
	IKBD_ClearBuffer();

}

/* Verifica se há Inimigos a criar na respectiva Attack Wave */
int vercriaini(int wcnt)
{
	
	if (wcnt2<MAXINI && tpini==0)
	{
		if (twave[wcnt].inis[wcnt2]!=255) 
		{
			criainimigo(wcnt,wcnt2); 		/* Cria Inimigo */
		}
		wcnt2++;
		tpini=twave[wcnt].pini[wcnt2];
	}
	else tpini--;
	
	if (wcnt2>=MAXINI && inimigos==0) return(1);	/* Verifica se acabou a Attack Wave atual */
	
	return(0);
	
}

/* Game Over - Estado=6 */
void gameover(void)
{
	
	IKBD_ClearBuffer();
	
	clearscreen();
	
	lPos.mX=66;
	lPos.mY=0;
	Screen_Physic_DrawSprite(&lPos,lpSpriteTitle);
	
	inicializamusica();
	musica=0;
	tmus1=clock();
		
	time1=time(NULL);
		
	Font8x8_Print("GAME OVER, MAN !!",Screen_GetpPhysic(),88,48);
	Font8x8_Print("YOU ARE NOT LIKE SKYWALKER,",Screen_GetpPhysic(),48,80);
	Font8x8_Print("YOU LOST YOUR SHIPS, HAHA!!",Screen_GetpPhysic(),48,96);
	
	if (pontos>recorde)
	{
		recorde=pontos;
		Font8x8_Print("BUT YOU ACHIEVED",Screen_GetpPhysic(),96,128);
		Font8x8_Print("AN HISCORE, YES!",Screen_GetpPhysic(),96,144);
	}
	else
	{
		Font8x8_Print("NO HISCORE ACHIEVED",Screen_GetpPhysic(),80,128);
		Font8x8_Print("MAYBE NEXT TIME.",Screen_GetpPhysic(),96,144);
	}
	
	Font8x8_Print("PRESS RETURN TO MAIN MENU",Screen_GetpPhysic(),56,188);
		
	while (estado==6)
	{
		
		tmus2=clock();
		if (tmus2>tmus1+MUSTEMPO)
		{
			musicplayer();
			tmus1=clock();
		}
		
		time2=time(NULL);
		if (time2>time1+20) estado=0;
		
		if (IKBD_GetKeyStatus(eIKBDSCAN_RETURN)) estado=0;
	}
	
	IKBD_ClearBuffer();
	
}

/* WellDone - Estado=7 */
void welldone(void)
{
	
	IKBD_ClearBuffer();
	
	clearscreen();
	
	lPos.mX=66;
	lPos.mY=0;
	Screen_Physic_DrawSprite(&lPos,lpSpriteTitle);
	
	inicializamusica();
	musica=0;
	tmus1=clock();
		
	time1=time(NULL);
		
	Font8x8_Print("WELL DONE !!!",Screen_GetpPhysic(),104,48);
	Font8x8_Print("YOU DEFEATED THE EVIL",Screen_GetpPhysic(),72,72);
	Font8x8_Print("SARDONIC AND ITS ARMY",Screen_GetpPhysic(),72,88);
	
	Font8x8_Print("THANK YOU FOR PLAYING",Screen_GetpPhysic(),72,112);
	Font8x8_Print("THIS LITTLE AND CRAP GAME",Screen_GetpPhysic(),56,128);
	
	Font8x8_Print("SEE YOU SOON ON THE",Screen_GetpPhysic(),80,152);
	Font8x8_Print("MSDOS VERSION, HEHE",Screen_GetpPhysic(),80,168);
	
	Font8x8_Print("PRESS RETURN TO MAIN MENU",Screen_GetpPhysic(),56,192);
	
	if (pontos>recorde) recorde=pontos;
		
	while (estado==7)
	{
		
		tmus2=clock();
		if (tmus2>tmus1+MUSTEMPO)
		{
			musicplayer();
			tmus1=clock();
		}
		
		time2=time(NULL);
		if (time2>time1+30) estado=0;
		
		if (IKBD_GetKeyStatus(eIKBDSCAN_RETURN)) estado=0;
	}
	
	IKBD_ClearBuffer();
	
}

/* Apaga os Sprites do écran */
void clearsprites()
{
	int i;
	
	Screen_Update(); 
	
	/* Inimigos */
	for (i=0; i<inimigos; i++)
	{
		lRect.mX = lPosSavedIni[i][ Screen_GetLogicIndex() ].mX;
		lRect.mY = lPosSavedIni[i][ Screen_GetLogicIndex() ].mY;
		lRect.mWidth = ini[i].tx;
		lRect.mHeight = ini[i].ty;
		Screen_Logic_DrawBox_Clip( &lRect, 0 );
	}
	
	
	/* Disparos */
	for (i=0; i<tiros; i++)
	{
		lRect.mX = lPosSavedTiro[i][Screen_GetLogicIndex()].mX;
		lRect.mY = lPosSavedTiro[i][Screen_GetLogicIndex()].mY;
		lRect.mWidth = tiro[i].tx;
		lRect.mHeight = tiro[i].ty;
		Screen_Logic_DrawBox_Clip( &lRect, 0 );
	}
	
	/* Disparos Inimigos */
	for (i=0; i<tirosini; i++)
	{
		lRect.mX = lPosSavedTiroIni[i][ Screen_GetLogicIndex() ].mX;
		lRect.mY = lPosSavedTiroIni[i][ Screen_GetLogicIndex() ].mY;
		lRect.mWidth = tiroini[i].tx;
		lRect.mHeight = tiroini[i].ty;
		Screen_Logic_DrawBox_Clip( &lRect, 0 );
	}
	
	/* Nave */
	lRect.mX = lPosSavedNv[ Screen_GetLogicIndex() ].mX;
	lRect.mY = lPosSavedNv[ Screen_GetLogicIndex() ].mY;
	lRect.mWidth = ntx;
	lRect.mHeight = nty;
	Screen_Logic_DrawBox_Clip( &lRect, 0 );
	
	/* Explosões */
	for (i=0; i<explosoes; i++)
	{
		lRect.mX = lPosSavedExplo[i][ Screen_GetLogicIndex() ].mX;
		lRect.mY = lPosSavedExplo[i][ Screen_GetLogicIndex() ].mY;
		lRect.mWidth = explo[i].tx;
		lRect.mHeight = explo[i].ty;
		Screen_Logic_DrawBox_Clip( &lRect, 0 );
	}
	
	/* Prémios */
	for (i=0; i<premios; i++)
	{
		lRect.mX = lPosSavedPremio[i][ Screen_GetLogicIndex() ].mX;
		lRect.mY = lPosSavedPremio[i][ Screen_GetLogicIndex() ].mY;
		lRect.mWidth = premio[i].tx;
		lRect.mHeight = premio[i].ty;
		Screen_Logic_DrawBox_Clip( &lRect, 0 );
	}

}

/* Desenha os Sprites no écran */
void printsprites()
{
	int i;
	
	/* Inimigos */
	for (i=0; i<inimigos; i++)
	{
		lPos.mX=ini[i].x;
		lPos.mY=ini[i].y;
		
		Screen_Logic_DrawSprite_Clip( &lPos, lpSpriteIni[ini[i].tipo] );
		lPosSavedIni[i][Screen_GetLogicIndex()] = lPos;
	}
	
	/* Tiros */
	for (i=0; i<tiros; i++)
	{
		lPos.mX=tiro[i].x;
		lPos.mY=tiro[i].y;
		
		if (tiro[i].tipo!=2)
			Screen_Logic_DrawSprite_Clip( &lPos, lpSpriteTiro[tiro[i].tipo] );
				
		lPosSavedTiro[i][Screen_GetLogicIndex()] = lPos;
	}
	
	/* Tiros Inimigos */
	for (i=0; i<tirosini; i++)
	{
		lPos.mX=tiroini[i].x;
		lPos.mY=tiroini[i].y;
		
		Screen_Logic_DrawSprite_Clip( &lPos, lpSpriteTiroIni[tiroini[i].tipo] );
		lPosSavedTiroIni[i][Screen_GetLogicIndex()] = lPos;
	}
	
	/* Nave */
	lPos.mX=nx;
	lPos.mY=ny;
		
	Screen_Logic_DrawSprite_Clip( &lPos, lpSpriteNv[ninvenc&1] );
	lPosSavedNv[ Screen_GetLogicIndex() ] = lPos;
	
	/* Explosões */
	for (i=0; i<explosoes; i++)
	{
		lPos.mX=explo[i].x;
		lPos.mY=explo[i].y;
		
		Screen_Logic_DrawSprite_Clip( &lPos, lpSpriteExplo[explo[i].fase] );
		lPosSavedExplo[i][Screen_GetLogicIndex()] = lPos;
	}
	
	/* Prémios */
	for (i=0; i<premios; i++)
	{
		lPos.mX=premio[i].x;
		lPos.mY=premio[i].y;

		Screen_Logic_DrawSprite_Clip( &lPos, lpSpritePremio[premio[i].tipo] );
		lPosSavedPremio[i][Screen_GetLogicIndex()] = lPos;
	}
	
}

/* Apaga o Écran */
void clearscreen()
{

	Screen_Physic_ClearScreen_Clip();
	Screen_Logic_ClearScreen_Clip();
	
}

/* Movimenta a Nave */
void movenave()
{
	aPacket=IKBD_GetJoy1Packet();
	
	/* Cima */
	if( aPacket & 1 )
		if (ny>=nspeed) ny-=nspeed;

	/* Baixo */
	if( aPacket & 2 )
		if (ny<=MAXY-(nty+nspeed)) ny+=nspeed;

	/* Esquerda */
	if( aPacket & 4 )
		if (nx>=nspeed) nx-=nspeed;

	/* Direita */
	if( aPacket & 8 )
		if (nx<=MAXX-(ntx+nspeed)) nx+=nspeed;
	
	/* Disparo */
	if( aPacket & 128 )
		if (ratetiro==0)
			if (ntiro==0) criadisparo(nx+8,ny-8,0);
			else criadisparo(nx+3,ny-6,1);
				
	/* Bomba */
	if (ratebomba==0 && bombas>0 && inimigos>0 && IKBD_GetKeyStatus(eIKBDSCAN_SPACE))
		criabomba();
			
}

/* Verifica o rectângulo de colisão */
int colrect(int xi1,int yi1,int xf1,int yf1,int xi2,int yi2,int xf2,int yf2)
{

	if (xf1<xi2); 
		else if (xi1>xf2);
			else if (yf1<yi2);
				else if (yi1>yf2);
					else return(1);
				
	return (0);
}

/* Verifica Colisão entre os Disparos e os Inimigos */
void verificacolisao1(void)
{
	int t,i,c;
	int ex,ey;

	t=0; /* Percorre todos os Disparos */
	do
	{
		i=0; /* Percorre todos os Inimigos */
		do
		{
			c=0;
			if (colrect(tiro[t].x,tiro[t].y,tiro[t].x+tiro[t].tx-1,tiro[t].y+tiro[t].ty-1,
				ini[i].x,ini[i].y,ini[i].x+ini[i].tx-1,ini[i].y+ini[i].ty-1)==1)
			{
				c=1;
								
				ini[i].hull-=tiro[t].tipo+1;
				if (ini[i].hull<=0) /* Verifica se é altura de destruir o Inimigo */
				{
					ex=ini[i].x;
					ey=ini[i].y;
					tipini=ini[i].tipo;
					ganhapontos(ini[i].pontos);
					if (ini[i].tipo>9) mudanivel(); /* Se o Inimigo for um Boss muda de Nível */
					apagainimigo(i);
					
					
					if (tipini<10)
					{
						criaexplosao(ex,ey);
						somexplosao();
					}
					else
					{
						criaexplosaoboss(ex,ey);
						sombomba();
					}
					
					/* Verifica a Criação de Prémio */
					premiocnt--;
					if (premiocnt==0) criapremio(ex,ey);
				}
				else
				{
					if (ini[i].tipo>9) /* Se o Inimigo for um Boss cria uma Explosão na posição do Disparo */
					{
						ex=tiro[t].x-8;
						ey=tiro[t].y-8;
						ganhapontos(5);
						criaexplosao(ex,ey);
						somexplosao();
					}
					i++;
				}
				
				apagadisparo(t); /* Apaga o Disparo */
					
			}
			else i++;
		}
		while (i<inimigos && c==0);
		
		if (c==0) t++;
		
	}
	while (t<tiros);
	
}

/* Verifica Colisão entre os Disparos Inimigos e a Nave */
void verificacolisao2(void)
{
	
	int t;
		
	t=0; /* Percorre todos os Disparos Inimigos */
	do
	{
		if (colrect(tiroini[t].x,tiroini[t].y,tiroini[t].x+tiroini[t].tx-1,tiroini[t].y+tiroini[t].ty-1,
			nx,ny,nx+ntx-1,ny+nty-1)==1)
		{
			apagadisparoinimigo(t); /* Apaga o Disparo Inimigo */
				
			/* Verifica se é altura de destruir a Nave */
			if (ninvenc==0) perdevida(); 
			
		}
		else t++;
	}
	while (t<tirosini);
	
}

/* Verifica Colisão entre os Inimigos e a Nave */
void verificacolisao3(void)
{
	
	int i;
	int ex,ey;
	
	i=0; /* Percorre todos os Inimigos */
	do
	{
		if (colrect(ini[i].x,ini[i].y,ini[i].x+ini[i].tx-1,ini[i].y+ini[i].ty-1,
			nx,ny,nx+ntx-1,ny+nty-1)==1)
		{
			
			if (ini[i].tipo<10) /* Se for um Inimigo Pequeno ou Médio */
			{
				ex=ini[i].x; 	/* Apaga o Inimigo */
				ey=ini[i].y;
				ganhapontos(ini[i].pontos);
				apagainimigo(i);
				criaexplosao(ex,ey);
				somexplosao();
			}
			else /* Se for um Boss */
			{
				ini[i].hull--;
				if (ini[i].hull==0) /* Verifica se é altura de destruir o Inimigo */
				{
					ex=ini[i].x;
					ey=ini[i].y;
					tipini=ini[i].tipo;
					ganhapontos(ini[i].pontos);
					mudanivel();
					apagainimigo(i);
					criaexplosaoboss(ex,ey);
					sombomba();
				}
				else
				{
					ganhapontos(5);
					i++;
					somexplosao();
				}
			}
							
			/* Verifica se é altura de destruir a Nave */
			if (ninvenc==0) perdevida();
			
		}
		else i++;
		
	}
	while (i<inimigos);
	
}

/* Verifica Colisão entre os Prémios e a Nave */
void verificacolisao4(void)
{
	
	int i;
	
	i=0; /* Percorre todos os Prémios */
	do
	{
		if (colrect(premio[i].x,premio[i].y,premio[i].x+premio[i].tx-1,premio[i].y+premio[i].ty-1,
			nx,ny,nx+ntx-1,ny+nty-1)==1)
		{
		
			switch (premio[i].tipo)
			{
				case 0:ganhavida();break;
				case 1:ntiro=1;break;
				case 2:ganhabomba();break;
				case 3:ganhapontos(30);break;
				case 4:ninvenc=ARMOUR;break;
				case 5:nspeed=3;break;
			}
			sompremio(premio[i].tipo);
			apagapremio(i);
					
		}
		else i++;
		
	}
	while (i<premios);
	
}

/* Perde Vida */
void perdevida(void)
{
	char txvid[2];
	int ex,ey;

	ninvenc=ARMOUR;
	ntiro=0;
	nspeed=2;
	ex=nx;
	ey=ny;
	criaexplosao(ex,ey);
	somexplosao();
				
	vidas--;
	
	sprintf(txvid, "%d",vidas);
	Font8x8_Print(txvid,Screen_GetpLogic(),280,80);
	Font8x8_Print(txvid,Screen_GetpPhysic(),280,80);
	
	if (vidas==0) estado=6;
	
}

/* Ganha Vida */
void ganhavida(void)
{
	
	char txvid[2];

	if (vidas<MAXVIDAS)
	{
		vidas++;
		sprintf(txvid, "%d",vidas);
		Font8x8_Print(txvid,Screen_GetpLogic(),280,80);
		Font8x8_Print(txvid,Screen_GetpPhysic(),280,80);
	}
	
}

/* Ganha Bomba */
void ganhabomba(void)
{

	char txbmb[2];

	if (bombas<MAXBOMBAS)
	{
		bombas++;
		sprintf(txbmb, "%d",bombas);
		Font8x8_Print(txbmb,Screen_GetpLogic(),280,128);
		Font8x8_Print(txbmb,Screen_GetpPhysic(),280,128);
	}
	
}

/* Perde Bomba */
void perdebomba(void)
{

	char txbmb[2];

	sprintf(txbmb, "%d",bombas);
	Font8x8_Print(txbmb,Screen_GetpLogic(),280,128);
	Font8x8_Print(txbmb,Screen_GetpPhysic(),280,128);
	
}

/* Ganha Pontos */
void ganhapontos(int pts)
{
	
	char txpts[5];
	
	pontos+=pts;
	
	sprintf(txpts, "%5d",pontos);
	Font8x8_Print(txpts,Screen_GetpLogic(),264,32);
	Font8x8_Print(txpts,Screen_GetpPhysic(),264,32);
	
}

/* Muda de Nível */
void mudanivel(void)
{
	
	char txnvl[5]; 

	Graphic_SetBlitterEnable(1);
	
	if (nivel<5)
	{
		nivel++;
		desenhapainel();
		sprintf(txnvl, "%d ",nivel);
		Font8x8_Print(txnvl,Screen_GetpLogic(),264+(8*(5-nivel)),176);
		Font8x8_Print(txnvl,Screen_GetpPhysic(),264+(8*(5-nivel)),176);
		rtini=RTINIPM;
	}
	
}

/* Cria Disparo */
void criadisparo(int ntx,int nty,int ntp)
{
	
	/* Disparos */
	if (tiros<MAXTIRO)
	{
		tiro[tiros].x=ntx;
		tiro[tiros].y=nty;
		tiro[tiros].tx=1+ntp*10;
		tiro[tiros].ty=8;
		tiro[tiros].tipo=ntp;
		tiros++;
		ratetiro=25;
		somdisparo();
	}
	
}

/* Movimenta Disparo */
void movedisparo()
{

	int i=0;
	
	do
	{
		tiro[i].y-=3;
		
		if (tiro[i].y<=-tiro[i].ty) apagadisparo(i);
		else i++;
	}
	while (i<tiros);
	
}

/* Apaga Disparo */
void apagadisparo(int i)
{
	
	int k;
	
	lRect.mX = lPosSavedTiro[i][Screen_GetPhysicIndex()].mX;
	lRect.mY = lPosSavedTiro[i][Screen_GetPhysicIndex()].mY;
	lRect.mWidth = tiro[i].tx;
	lRect.mHeight = tiro[i].ty;
	Screen_Physic_DrawBox_Clip( &lRect, 0 );
		
	for (k=i; k<tiros; k++)
	{
		tiro[k].x=tiro[k+1].x;
		tiro[k].y=tiro[k+1].y;
		tiro[k].tx=tiro[k+1].tx;
		tiro[k].ty=tiro[k+1].ty;
		tiro[k].tipo=tiro[k+1].tipo;
						
		lPosSavedTiro[k][0]=lPosSavedTiro[k+1][0];
		lPosSavedTiro[k][1]=lPosSavedTiro[k+1][1];
	}
	
	tiros--;
	
}

/* Prepara a Criação do Disparo Inimigo */
void preparadisparoinimigo(int i)
{

	int rnd; 

	if (ratetiroini==0)
	{
		rnd=(random(50));
	
		if (rnd<5)
		{
			
			if (ini[i].tipo==14)
			{
				criadisparoinimigo(ini[i].x+12,ini[i].y+ini[i].ty,1);
				criadisparoinimigo(ini[i].x+44,ini[i].y+ini[i].ty,1);
			}
			
			if (ini[i].tipo==12 || ini[i].tipo==13)
			{
				criadisparoinimigo(ini[i].x+3,ini[i].y+ini[i].ty,1);
				criadisparoinimigo(ini[i].x+18,ini[i].y+ini[i].ty,1);
			}
						
			if (ini[i].tipo==10 || ini[i].tipo==11)
			{
				criadisparoinimigo(ini[i].x+7,ini[i].y+ini[i].ty,1);
				criadisparoinimigo(ini[i].x+30,ini[i].y+ini[i].ty,1);
			}
			
			if (ini[i].tipo==7 || ini[i].tipo==9)
				criadisparoinimigo(ini[i].x+3,ini[i].y+ini[i].ty,1);
			
			if (ini[i].tipo<7)
				criadisparoinimigo(ini[i].x+8,ini[i].y+ini[i].ty,0);
	
		}
	}
	
}

/* Cria Disparo Inimigo */
void criadisparoinimigo(int ntix,int ntiy,int ntp)
{

	/* Disparos Inimigos */
	if (tirosini<MAXTIROINI)
	{
		tiroini[tirosini].x=ntix;
		tiroini[tirosini].y=ntiy;
		tiroini[tirosini].tx=1+ntp*8;
		tiroini[tirosini].ty=8;
		tiroini[tirosini].tipo=ntp;
		tirosini++;
		ratetiroini=rtini; 
	}

}

/* Movimenta Disparo Inimigo */
void movedisparoinimigo(void)
{
	
	int i=0;
	
	do
	{
		tiroini[i].y+=3;
		
		if (tiroini[i].y >= MAXY) apagadisparoinimigo(i);
		else i++;
	}
	while (i<tirosini);
	
}

/* Apaga Disparo Inimigo */
void apagadisparoinimigo(int i)
{
	
	int k;
	
	lRect.mX = lPosSavedTiroIni[i][Screen_GetPhysicIndex()].mX;
	lRect.mY = lPosSavedTiroIni[i][Screen_GetPhysicIndex()].mY;
	lRect.mWidth = tiroini[i].tx;
	lRect.mHeight = tiroini[i].ty;
	Screen_Physic_DrawBox_Clip( &lRect, 0 );
	
	for (k=i; k<tirosini; k++)
	{
		tiroini[k].x=tiroini[k+1].x;
		tiroini[k].y=tiroini[k+1].y;
		tiroini[k].tx=tiroini[k+1].tx;
		tiroini[k].ty=tiroini[k+1].ty;
		tiroini[k].tipo=tiroini[k+1].tipo;
					
		lPosSavedTiroIni[k][0]=lPosSavedTiroIni[k+1][0];
		lPosSavedTiroIni[k][1]=lPosSavedTiroIni[k+1][1];
	}
	
	tirosini--;
	
}

/* Cria várias Explosões quando um Boss é destruído */
void criaexplosaoboss(int ntx,int nty)
{

	/* Bosses I e II */
	if (tipini==10 || tipini==11)
	{
		criaexplosao(ntx,nty+8);
		criaexplosao(ntx+16,nty);
		criaexplosao(ntx+16,nty+16);
		criaexplosao(ntx+32,nty+8);
	}
	
	/* Boss III */
	if (tipini==12)
	{
		criaexplosao(ntx+8,nty-8);
		criaexplosao(ntx+8,nty+8);
		criaexplosao(ntx+8,nty+24);
		criaexplosao(ntx+8,nty+40);
	}
	
	/* Boss IV */
	if (tipini==13)
	{
		criaexplosao(ntx,nty);
		criaexplosao(ntx+16,nty);
		criaexplosao(ntx+8,nty+16);
		criaexplosao(ntx,nty+32);
		criaexplosao(ntx+16,nty+32);
	}
	
	/* Boss V */
	if (tipini==14)
	{
		criaexplosao(ntx,nty);
		criaexplosao(ntx+16,nty+16);
		criaexplosao(ntx+32,nty);
		criaexplosao(ntx+48,nty+16);
	}
	
}

/* Cria Explosão */
void criaexplosao(int ntx,int nty)
{

	/* Explosão */
	if (explosoes<MAXEXPLO)
	{
		if (ntx>232) ntx=232;
		explo[explosoes].x=ntx;
		explo[explosoes].y=nty;
		explo[explosoes].tx=16;
		explo[explosoes].ty=16;
		explo[explosoes].fase=0;
		explo[explosoes].tempo=3;
		explosoes++;
	}
	
}

/* "Move" Explosão */
void moveexplosao(void)
{
	
	int i=0;
	
	do
	{
		explo[i].tempo--;
		
		if (explo[i].tempo==0)
		{
			explo[i].fase++;
			explo[i].tempo=3;
		}
		
		if (explo[i].fase > 3) apagaexplosao(i);
		else i++;
	}
	while (i<explosoes);
	
}

/* Apaga Explosão */
void apagaexplosao(int i)
{
	
	int k;
	
	lRect.mX = lPosSavedExplo[i][Screen_GetPhysicIndex()].mX;
	lRect.mY = lPosSavedExplo[i][Screen_GetPhysicIndex()].mY;
	lRect.mWidth = explo[i].tx;
	lRect.mHeight = explo[i].ty;
	Screen_Physic_DrawBox_Clip( &lRect, 0 );
	
	for (k=i; k<explosoes; k++)
	{
		explo[k].x=explo[k+1].x;
		explo[k].y=explo[k+1].y;
		explo[k].tx=explo[k+1].tx;
		explo[k].ty=explo[k+1].ty;
		explo[k].fase=explo[k+1].fase;
		explo[k].tempo=explo[k+1].tempo;
					
		lPosSavedExplo[k][0]=lPosSavedExplo[k+1][0];
		lPosSavedExplo[k][1]=lPosSavedExplo[k+1][1];
	}
	
	explosoes--;
	
}

/* Cria Bomba */
void criabomba(void)
{

	int i;
	int ex,ey;
	
	/* Apaga Todos os Disparos */
	while (tiros>0) apagadisparo(0);
	
	/* Apaga Todos os Disparos Inimigos */
	while (tirosini>0) apagadisparoinimigo(0);
	
	/* Apaga Todos os Inimigos */
	i=0;
	while (i<inimigos)
		if (ini[i].tipo<10) /* Se for um Inimigo Pequeno ou Médio */
		{
			ex=ini[i].x;
			ey=ini[i].y;
			pontos+=ini[i].pontos;
			apagainimigo(i);
			criaexplosao(ex,ey);
			
			/* Verifica a Criação de Prémio */
			premiocnt--;
			if (premiocnt==0) criapremio(ex,ey);
		}
		else /* Se for um Boss */
		{
			ini[i].hull-=5;
			if (ini[i].hull<=0) /* Verifica se é altura de destruir o Inimigo */
			{
				ex=ini[i].x;
				ey=ini[i].y;
				tipini=ini[i].tipo;
				pontos+=ini[i].pontos;
				mudanivel();
				apagainimigo(i);
				criaexplosaoboss(ex,ey);
				
				/* Verifica a Criação de Prémio */
				premiocnt--;
				if (premiocnt==0) criapremio(ex,ey);
			}
			else
			{
				ex=ini[i].x;
				ey=ini[i].y;
				tipini=ini[i].tipo;
				criaexplosaoboss(ex,ey);
				pontos+=5;
				i++;
			}
		}
	
	sombomba();
	bombas--;
	perdebomba();
	ratebomba=40;
	
}

/* Cria Prémio */
void criapremio(int ntx,int nty)
{
	
	int rnd;
	
	rnd=(random(NUMPREMIOS));
	
	if (premios<MAXPREMIO)
	{
		premio[premios].x=ntx;
		premio[premios].y=nty;
		premio[premios].tx=10;
		premio[premios].ty=11;
		premio[premios].tipo=rnd;
		premio[premios].tempo=3;
		premio[premios].cnt=PRMTEMPO;
		premios++;
	}
	
	premiocnt=5;
	
}

/* Move Prémio */
void movepremio(void)
{
	
	int i=0;
	
	do
	{
		premio[i].tempo--;
		if (premio[i].tempo==0)
		{
			premio[i].tempo=2;
			premio[i].y++;
			premio[i].cnt--;
			
			if (premio[i].y>=MAXY || premio[i].cnt==0) apagapremio(i);
			else i++;
		}
		else i++;
	}
	while (i<premios);
}

/* Apaga Prémio */
void apagapremio(int i)
{
	
	int k;
	
	lRect.mX = lPosSavedPremio[i][Screen_GetPhysicIndex()].mX;
	lRect.mY = lPosSavedPremio[i][Screen_GetPhysicIndex()].mY;
	lRect.mWidth = premio[i].tx;
	lRect.mHeight = premio[i].ty;
	Screen_Physic_DrawBox_Clip( &lRect, 0 );
	
	for (k=i; k<premios; k++)
	{
		premio[k].x=premio[k+1].x;
		premio[k].y=premio[k+1].y;
		premio[k].tx=premio[k+1].tx;
		premio[k].ty=premio[k+1].ty;
		premio[k].tipo=premio[k+1].tipo;
		premio[k].tempo=premio[k+1].tempo;
		premio[k].cnt=premio[k+1].cnt;
							
		lPosSavedPremio[k][0]=lPosSavedPremio[k+1][0];
		lPosSavedPremio[k][1]=lPosSavedPremio[k+1][1];
	}
	
	premios--;
	
}

/* Move o StarField */
void movestar(void)
{

	int i;	
	
	for (i=0; i<MAXSTAR; i++)
	{
		Screen_Logic_DrawPixel( &lPosSavedStar[i][Screen_GetLogicIndex()],0);

		if (ratestar==0)
		{
			lPosStar[i].mY++;
			if (lPosStar[i].mY>MAXY)
			{
				lPosStar[i].mX=random(MAXX);
				lPosStar[i].mY=MINY;
			}
		}
				
		Screen_Logic_DrawPixel( &lPosStar[i],3);
		
		lPosSavedStar[i][Screen_GetLogicIndex()]=lPosStar[i];
	}	
		
	if (ratestar==0) ratestar=2;
			
}

/* Cria Inimigo */
void criainimigo(int wcnt,int wcnt2)
{
	
	/* Inimigos */
	if (inimigos<MAXINI)
	{
		ini[inimigos].tipo=twave[wcnt].inis[wcnt2];
		tipini=ini[inimigos].tipo;
		ini[inimigos].x=twave[wcnt].xx[wcnt2]-tipoini[tipini].tx;
		ini[inimigos].y=twave[wcnt].yy[wcnt2]-tipoini[tipini].ty;
		ini[inimigos].r=0;
		ini[inimigos].fpath=twave[wcnt].fpath[wcnt2];
		ini[inimigos].tx=tipoini[tipini].tx;
		ini[inimigos].ty=tipoini[tipini].ty;
		ini[inimigos].hull=tipoini[tipini].hull;
		ini[inimigos].speed=tipoini[tipini].speed;
		ini[inimigos].pontos=tipoini[tipini].pontos;
		inimigos++;
	}
	
}

/* Movimenta os Inimigos */
void moveinimigo(void)
{
	int i=0;
	int a=0;
	
	do
	{
		
		if (ini[i].tipo!=8)
			preparadisparoinimigo(i);
		
		switch (ini[i].fpath)
		{
			/* Verticalmente Baixo */
			case 1:a=mvinivert(i); break;
			case 2:a=mvinivertsindir(i); break;
			case 3:a=mvinivertcircledir(i); break;
			case 4:a=mvinivertsinesq(i); break;
			case 5:a=mvinivertcircleesq(i); break;
			
			/* Circular */
			case 6:mvinicircledirnoxy(i); break;
			case 7:mvinicircleesqnoxy(i); break;
			
			/* Horizontalmente Direita */
			case 8:a=mvinihorzdir(i); break;
			case 9:a=mvinihorzdirsindown(i); break;
			case 10:a=mvinihorzdircircledown(i); break;
			case 11:a=mvinihorzdirsinup(i); break;
			case 12:a=mvinihorzdircircleup(i); break;
			
			/* Horizontalmente Esquerda */
			case 13:a=mvinihorzesq(i); break;
			case 14:a=mvinihorzesqsindown(i); break;
			case 15:a=mvinihorzesqcircledown(i); break;
			case 16:a=mvinihorzesqsinup(i); break;
			case 17:a=mvinihorzesqcircleup(i); break;
			
			/* Diagonalmente */
			case 18:a=mvinidiadirdown(i); break;
			case 19:a=mvinidiadirup(i); break;
			case 20:a=mvinidiaesqdown(i); break;
			case 21:a=mvinidiaesqup(i); break;
			
			/* Sinusoidal */
			case 22:mvinisindirnoxy(i); break;
			case 23:mvinisinesqnoxy(i); break;
			
			/* Verticalmente mais Circular Direita / Esquerda */
			case 24:mvinivertmaiscircledir(i); break; 
			case 25:mvinivertmaiscircleesq(i); break;
			
			/* Verticalmente mais Sinusoidal Direita / Esquerda */
			case 26:mvinivertmaissindir(i); break;
			case 27:mvinivertmaissinesq(i); break;
			
			/* Verticalmente mais Vertical Sinusoidal Direita / Esquerda */
			case 28:mvinivertmaisvertsindir(i); break;
			case 29:mvinivertmaisvertsinesq(i); break;
			
			/* Verticalmente mais Diagonal Direita / Esquerda */
			case 30:mvinivertmaisdiadir(i); break;
			case 31:mvinivertmaisdiaesq(i); break;
			
			/* Verticalmente mais Vertical Circular Direita / Esquerda */
			case 32:mvinivertmaisvertcircledir(i); break;
			case 33:mvinivertmaisvertcircleesq(i); break;
			
			/* Horizontalmente Direita mais Diagonal Cima / Baixo */
			case 34:mvinihorzdirmaisdiaup(i); break;
			case 35:mvinihorzdirmaisdiadown(i); break;
			
			/* Horizontalmente Direita mais Horizontal Circular Cima / Baixo */
			case 36:mvinihorzdirmaishorcircleup(i); break;
			case 37:mvinihorzdirmaishorcircledown(i); break;
			
			/* Horizontalmente Esquerda mais Diagonal Cima / Baixo */
			case 38:mvinihorzesqmaisdiaup(i); break;
			case 39:mvinihorzesqmaisdiadown(i); break;
			
			/* Horizontalmente Esquerda mais Horizontal Circular Cima / Baixo */
			case 40:mvinihorzesqmaishorcircleup(i); break;
			case 41:mvinihorzesqmaishorcircledown(i); break;
			
			/* Diagonalmente Direita Baixo mais Diagonal Direita Cima */
			case 42:mvinidiadirdownmaisdiadirup(i); break;

			/* Diagonalmente Esquerda Baixo mais Diagonal Esquerda Cima */
			case 43:mvinidiaesqdownmaisdiaesqup(i); break;
			
			/* Diagonalmente Direita Baixo mais Vertical*/
			case 44:mvinidiadirdownmaisvert(i); break;

			/* Diagonalmente Esquerda Baixo mais Vertical*/
			case 45:mvinidiaesqdownmaisvert(i); break;
		}
		
		if (a==0) i++;
		else apagainimigo(i);
						
	}
	while (i<inimigos);
	
}

/* Apaga Inimigo */
void apagainimigo(int i)
{
	
	int k;
	
	lRect.mX = lPosSavedIni[i][Screen_GetPhysicIndex()].mX;
	lRect.mY = lPosSavedIni[i][Screen_GetPhysicIndex()].mY;
	lRect.mWidth = ini[i].tx;
	lRect.mHeight = ini[i].ty;
	Screen_Physic_DrawBox_Clip( &lRect, 0 );
	
	for (k=i; k<inimigos; k++)
	{
		ini[k].x=ini[k+1].x;
		ini[k].y=ini[k+1].y;
		ini[k].tx=ini[k+1].tx;
		ini[k].ty=ini[k+1].ty;
		ini[k].tipo=ini[k+1].tipo;
		ini[k].fpath=ini[k+1].fpath;
		ini[k].hull=ini[k+1].hull;
		ini[k].speed=ini[k+1].speed;
		ini[k].pontos=ini[k+1].pontos;
		ini[k].r=ini[k+1].r;
			
		lPosSavedIni[k][0]=lPosSavedIni[k+1][0];
		lPosSavedIni[k][1]=lPosSavedIni[k+1][1];
	}
	
	inimigos--;
	
}

/* 1 - Movimenta Verticalmente o Inimigo */
int mvinivert(int i)
{
	
	ini[i].y+=ini[i].speed;

	if (ini[i].y>=MAXY)	return(1);
	
	return(0);
	
}

/* 2 - Movimenta Verticalmente o Inimigo em Sinusoidal para a Direita */
int mvinivertsindir(int i)
{
	
	ini[i].y+=ini[i].speed;
		
	ini[i].r++;
	if (ini[i].r>125) ini[i].r=0;
				
	ini[i].x+=(int)(tsincos[0][ini[i].r]*2);
	
	if (ini[i].y>=MAXY)	return(1);
	
	return(0);
	
}

/* 3 - Movimenta Verticalmente o Inimigo em Círculo para a Direita */
int mvinivertcircledir(int i)
{
	
	ini[i].y+=ini[i].speed;
		
	ini[i].r++;
	if (ini[i].r>125) ini[i].r=0;
				
	ini[i].y+=(int)(tsincos[1][ini[i].r]*3);
	ini[i].x+=(int)(tsincos[0][ini[i].r]*3);
	
	if (ini[i].y>=MAXY)	return(1);
	
	return(0);
	
}

/* 4 - Movimenta Verticalmente o Inimigo em Sinusoidal para a Esquerda */
int mvinivertsinesq(int i)
{
	
	ini[i].y+=ini[i].speed;
		
	ini[i].r++;
	if (ini[i].r>125) ini[i].r=0;
					
	ini[i].x-=(int)(tsincos[0][ini[i].r]*2);
	
	if (ini[i].y>=MAXY)	return(1);
	
	return(0);
		
}

/* 5 - Movimenta Verticalmente o Inimigo em Círculo para a Esquerda */
int mvinivertcircleesq(int i)
{

	ini[i].y+=ini[i].speed;
	
	ini[i].r++;
	if (ini[i].r>125) ini[i].r=0;
			
	ini[i].y+=(int)(tsincos[1][ini[i].r]*3);
	ini[i].x-=(int)(tsincos[0][ini[i].r]*3);
	
	if (ini[i].y>=MAXY)	return(1);
	
	return(0);
	
}

/* 6 - Movimenta o Inimigo em Círculos para a Direita sem mover Y e X */
void mvinicircledirnoxy(int i)
{
	
	ini[i].r++;
	if (ini[i].r>125) ini[i].r=0;
					
	ini[i].y=ypos+(int)(tsincos[1][ini[i].r]*rfact);
	ini[i].x=xpos+(int)(tsincos[0][ini[i].r]*rfact);
	
}

/* 7 - Movimenta o Inimigo em Círculos para a Esquerda sem mover Y e X */
void mvinicircleesqnoxy(int i)
{
	
	ini[i].r++;
	if (ini[i].r>125) ini[i].r=0;
					
	ini[i].y=ypos+(int)(tsincos[1][ini[i].r]*rfact);
	ini[i].x=xpos-(int)(tsincos[0][ini[i].r]*rfact);
	
}

/* 8 - Movimenta Horizontalmente o Inimigo para a Direita */
int mvinihorzdir(int i)
{
	
	ini[i].x+=ini[i].speed;
	
	if (ini[i].x>=MAXX-ini[i].tx) return(1);
	
	return(0);
	
}

/* 9 - Movimenta Horizontalmente o Inimigo para a Direita em Sinusoidal para Baixo */
int mvinihorzdirsindown(int i)
{
	
	ini[i].x+=ini[i].speed;
		
	ini[i].r++;
	if (ini[i].r>125) ini[i].r=0;
				
	ini[i].y+=(int)(tsincos[0][ini[i].r]*2);
	
	if (ini[i].x>=MAXX-ini[i].tx) return(1);
	
	return(0);
	
}

/* 10 - Movimenta Horizontalmente o Inimigo para a Direita em Círculo para Baixo */
int mvinihorzdircircledown(int i)
{
	
	ini[i].x+=ini[i].speed;
		
	ini[i].r++;
	if (ini[i].r>125) ini[i].r=0;
					
	ini[i].x+=(int)(tsincos[1][ini[i].r]*3);
	ini[i].y+=(int)(tsincos[0][ini[i].r]*3);
	
	if (ini[i].x>=MAXX-ini[i].tx) return(1);
	
	return(0);
		
}

/* 11 - Movimenta Horizontalmente o Inimigo para a Direita em Sinusoidal para Cima */
int mvinihorzdirsinup(int i)
{
	
	ini[i].x+=ini[i].speed;
		
	ini[i].r++;
	if (ini[i].r>125) ini[i].r=0;
			
	ini[i].y-=(int)(tsincos[0][ini[i].r]*2);
	
	if (ini[i].x>=MAXX-ini[i].tx) return(1);
	
	return(0);

}

/* 12 - Movimenta Horizontalmente o Inimigo para a Direita em Círculo para Cima */
int mvinihorzdircircleup(int i)
{

	ini[i].x+=ini[i].speed;
		
	ini[i].r++;
	if (ini[i].r>125) ini[i].r=0;
				
	ini[i].x+=(int)(tsincos[1][ini[i].r]*3);
	ini[i].y-=(int)(tsincos[0][ini[i].r]*3);
	
	if (ini[i].x>=MAXX-ini[i].tx) return(1);
	
	return(0);
	
}

/* 13 - Movimenta Horizontalmente o Inimigo para a Esquerda */
int mvinihorzesq(int i)
{
	
	ini[i].x-=ini[i].speed;
	
	if (ini[i].x<=-ini[i].tx) return(1);
	
	return(0);
		
}

/* 14 - Movimenta Horizontalmente o Inimigo para a Esquerda em Sinusoidal para Baixo */
int mvinihorzesqsindown(int i)
{
	
	ini[i].x-=ini[i].speed;
		
	ini[i].r++;
	if (ini[i].r>125) ini[i].r=0;
				
	ini[i].y+=(int)(tsincos[0][ini[i].r]*2);
	
	if (ini[i].x<=-ini[i].tx) return(1);
	
	return(0);
	
}

/* 15 - Movimenta Horizontalmente o Inimigo para a Esquerda em Círculo para Baixo */
int mvinihorzesqcircledown(int i)
{
	
	ini[i].x-=ini[i].speed;
		
	ini[i].r++;
	if (ini[i].r>125) ini[i].r=0;
					
	ini[i].x-=(int)(tsincos[1][ini[i].r]*3);
	ini[i].y+=(int)(tsincos[0][ini[i].r]*3);
	
	if (ini[i].x<=-ini[i].tx) return(1);
	
	return(0);
		
}

/* 16 - Movimenta Horizontalmente o Inimigo para a Esquerda em Sinusoidal para Cima */
int mvinihorzesqsinup(int i)
{
	
	ini[i].x-=ini[i].speed;
		
	ini[i].r++;
	if (ini[i].r>125) ini[i].r=0;
				
	ini[i].y-=(int)(tsincos[0][ini[i].r]*2);
	
	if (ini[i].x<=-ini[i].tx) return(1);
	
	return(0);
	
}

/* 17 - Movimenta Horizontalmente o Inimigo para a Esquerda em Círculo para Cima */
int mvinihorzesqcircleup(int i)
{

	ini[i].x-=ini[i].speed;
		
	ini[i].r++;
	if (ini[i].r>125) ini[i].r=0;
			
	ini[i].x-=(int)(tsincos[1][ini[i].r]*3);
	ini[i].y-=(int)(tsincos[0][ini[i].r]*3);
	
	if (ini[i].x<=-ini[i].tx) return(1);
	
	return(0);
	
}

/* 18 - Movimenta Diagonalmente o Inimigo para a Direita e para Baixo */
int mvinidiadirdown(int i)
{
	
	ini[i].y+=ini[i].speed;
	ini[i].x+=ini[i].speed;
	
	if (ini[i].y>=MAXY || ini[i].x>=MAXX-ini[i].tx) return(1);
	
	return(0);
		
}

/* 19 - Movimenta Diagonalmente o Inimigo para a Direita e para Cima */
int mvinidiadirup(int i)
{
	
	ini[i].y-=ini[i].speed;
	ini[i].x+=ini[i].speed;
	
	if (ini[i].y<=-ini[i].ty || ini[i].x>=MAXX-ini[i].tx) return(1);
	
	return(0);
	
}

/* 20 - Movimenta Diagonalmente o Inimigo para a Esquerda e para Baixo */
int mvinidiaesqdown(int i)
{
	
	ini[i].y+=ini[i].speed;
	ini[i].x-=ini[i].speed;
	
	if (ini[i].y>=MAXY || ini[i].x<=-ini[i].tx) return(1);
	
	return(0);
	
}

/* 21 - Movimenta Diagonalmente o Inimigo para a Esquerda e para Cima */
int mvinidiaesqup(int i)
{
	
	ini[i].y-=ini[i].speed;
	ini[i].x-=ini[i].speed;
	
	if (ini[i].y<=-ini[i].ty || ini[i].x<=-ini[i].tx) return(1);
	
	return(0);
	
}

/* 22 - Movimenta o Inimigo em Sinusoidal para a Direita sem mover Y e X */
void mvinisindirnoxy(int i)
{
	
	ini[i].r++;
	if (ini[i].r>125) ini[i].r=0;
				
	ini[i].x=xpos+(int)(tsincos[0][ini[i].r]*rfact);
	
	
}

/* 23 - Movimenta o Inimigo em Sinusoidal para a Esquerda sem mover Y e X */
void mvinisinesqnoxy(int i)
{
	
	ini[i].r++;
	if (ini[i].r>125) ini[i].r=0;
				
	ini[i].x=xpos-(int)(tsincos[0][ini[i].r]*rfact);
	
}

/* 24 - Verticalmente mais Circular Direita */
void mvinivertmaiscircledir(int i)
{
	
	ini[i].y+=ini[i].speed;
	if (ini[i].y>=(MAXY-ini[i].ty)/2)
	{
		ypos=ini[i].y-45;
		xpos=ini[i].x;
		rfact=45;
		ini[i].fpath=6;
	}
	
}

/* 25 - Verticalmente mais Circular Esquerda */
void mvinivertmaiscircleesq(int i)
{
	
	ini[i].y+=ini[i].speed;
	if (ini[i].y>=(MAXY-ini[i].ty)/2)
	{
		ypos=ini[i].y-45;
		xpos=ini[i].x;
		rfact=45;
		ini[i].fpath=7;
	}
	
}

/* 26 - Verticalmente mais Sinusoidal Direita */
void mvinivertmaissindir(int i)
{
	
	ini[i].y+=ini[i].speed;
	if (ini[i].y>=(MAXY-ini[i].ty)/10)
	{
		xpos=ini[i].x;
		switch (ini[i].tipo)
		{
			case 10:rfact=101; break;
			case 11:rfact=101; break;
			case 12:rfact=109; break;
			case 13:rfact=109; break;
			case 14:rfact=92; break;
		}
		ini[i].fpath=22;
	}
	
}

/* 27 - Verticalmente mais Sinusoidal Esquerda */
void mvinivertmaissinesq(int i)
{
	
	ini[i].y+=ini[i].speed;
	if (ini[i].y>=(MAXY-ini[i].ty)/10)
	{
		xpos=ini[i].x;
		switch (ini[i].tipo)
		{
			case 10:rfact=101; break;
			case 11:rfact=101; break;
			case 12:rfact=109; break;
			case 13:rfact=109; break;
			case 14:rfact=92; break;
		}
		ini[i].fpath=23;
	}
	
}

/* 28 - Verticalmente mais Vertical Sinusoidal Direita */
void mvinivertmaisvertsindir(int i)
{
	
	ini[i].y+=ini[i].speed;
	if (ini[i].y>=(MAXY-ini[i].ty)/3) ini[i].fpath=2;
	
}

/* 29 - Verticalmente mais Vertical Sinusoidal Esquerda */
void mvinivertmaisvertsinesq(int i)
{
	
	ini[i].y+=ini[i].speed;
	if (ini[i].y>=(MAXY-ini[i].ty)/3) ini[i].fpath=4;
	
}

/* 30 - Verticalmente mais Diagonal Direita */
void mvinivertmaisdiadir(int i)
{

	ini[i].y+=ini[i].speed;
	if (ini[i].y>=(MAXY-ini[i].ty)/3) ini[i].fpath=18;

}

/* 31 - Verticalmente mais Diagonal Esquerda */
void mvinivertmaisdiaesq(int i)
{
	
	ini[i].y+=ini[i].speed;
	if (ini[i].y>=(MAXY-ini[i].ty)/3) ini[i].fpath=20;
	
}

/* 32 - Verticalmente mais Vertical Circular Direita */
void mvinivertmaisvertcircledir(int i)
{

	ini[i].y+=ini[i].speed;
	if (ini[i].y>=(MAXY-ini[i].ty)/3) ini[i].fpath=3;
	
}

/* 33 - Verticalmente mais Vertical Circular Esquerda */
void mvinivertmaisvertcircleesq(int i)
{

	ini[i].y+=ini[i].speed;
	if (ini[i].y>=(MAXY-ini[i].ty)/3) ini[i].fpath=5;
	
}

/* 34 - Horizontalmente Direita mais Diagonal Cima */
void mvinihorzdirmaisdiaup(int i)
{
	
	ini[i].x+=ini[i].speed;
	
	if (ini[i].x>=MAXX/2) ini[i].fpath=19;
	
}

/* 35 - Horizontalmente Direita mais Diagonal Baixo */
void mvinihorzdirmaisdiadown(int i)
{
	
	ini[i].x+=ini[i].speed;
	
	if (ini[i].x>=MAXX/2) ini[i].fpath=18;
	
}

/* 36 - Horizontalmente Direita mais Horizontal Circular Cima */
void mvinihorzdirmaishorcircleup(int i)
{
	
	ini[i].x+=ini[i].speed;
	
	if (ini[i].x>=MAXX/2) ini[i].fpath=12;
	
}

/* 37 - Horizontalmente Direita mais Horizontal Circular Baixo */
void mvinihorzdirmaishorcircledown(int i)
{
	
	ini[i].x+=ini[i].speed;
	
	if (ini[i].x>=MAXX/2) ini[i].fpath=10;
	
}

/* 38 - Horizontalmente Esquerda mais Diagonal Cima */
void mvinihorzesqmaisdiaup(int i)
{
	
	ini[i].x-=ini[i].speed;
	
	if (ini[i].x<=MAXX/2) ini[i].fpath=21;
	
}

/* 39 - Horizontalmente Esquerda mais Diagonal Baixo */
void mvinihorzesqmaisdiadown(int i)
{
	
	ini[i].x-=ini[i].speed;
	
	if (ini[i].x<=MAXX/2) ini[i].fpath=20;
	
}

/* 40 - Horizontalmente Esquerda mais Horizontal Circular Cima */
void mvinihorzesqmaishorcircleup(int i)
{
	
	ini[i].x-=ini[i].speed;
	
	if (ini[i].x<=MAXX/2) ini[i].fpath=17;
	
}

/* 41 - Horizontalmente Esquerda mais Horizontal Circular Baixo */
void mvinihorzesqmaishorcircledown(int i)
{
	
	ini[i].x-=ini[i].speed;
	
	if (ini[i].x<=MAXX/2) ini[i].fpath=15;
	
}

/* 42 - Diagonalmente Direita Baixo mais Diagonal Direita Cima */
void mvinidiadirdownmaisdiadirup(int i)
{
	
	ini[i].y+=ini[i].speed;
	ini[i].x+=ini[i].speed;
	
	if (ini[i].y>=MAXY/2 || ini[i].x>=MAXX/2) ini[i].fpath=19;
	
}

/* 43 - Diagonalmente Esquerda Baixo mais Diagonal Esquerda Cima */
void mvinidiaesqdownmaisdiaesqup(int i)
{
	
	ini[i].y+=ini[i].speed;
	ini[i].x-=ini[i].speed;
	
	if (ini[i].y>=MAXY/2 || ini[i].x<MAXX/2) ini[i].fpath=21;
	
}

/* 44 - Diagonalmente Direita Baixo mais Vertical*/
void mvinidiadirdownmaisvert(int i)
{
	
	ini[i].y+=ini[i].speed;
	ini[i].x+=ini[i].speed;
	
	if (ini[i].y>=MAXY/2 || ini[i].x>=MAXX/2) ini[i].fpath=1;
	
}

/* 45 - Diagonalmente Esquerda Baixo mais Vertical*/
void mvinidiaesqdownmaisvert(int i)
{
	
	ini[i].y+=ini[i].speed;
	ini[i].x-=ini[i].speed;
	
	if (ini[i].y>=MAXY/2 || ini[i].x<MAXX/2) ini[i].fpath=1;
	
}

/* Inicializa o Leitor da Música */
void inicializamusica(void)
{
	
	Giaccess(0,reg+0);	/* Fine Picth do Canal A */
	Giaccess(0,reg+1);	/* Course Picth do Canal A */
	Giaccess(0,reg+2);	/* Fine Picth do Canal B */
	Giaccess(0,reg+3);	/* Course Picth do Canal B */
	Giaccess(0,reg+4);	/* Fine Picth do Canal C */
	Giaccess(0,reg+5);	/* Course Picth do Canal C */
	Giaccess(31,reg+6);	/* Picth do Ruído */
	Giaccess(56,reg+7);	/* Mixer: Tom nos Canais ABC */
	Giaccess(0,reg+8); 	/* Volume do Canal A */
	Giaccess(0,reg+9); 	/* Volume do Canal B */
	Giaccess(0,reg+10);	/* Volume do Canal C */
	Giaccess(184,reg+11); /* Fine Duração do Envelope */
	Giaccess(11,reg+12);  /* Course Duração do Envelope */
	Giaccess(9,reg+13); /* Tipo de Envelope */
	
}

/* Cria o Som de uma Explosão */
void somexplosao(void)
{
	
	Giaccess(35,reg+7);	/* Ruído nos Canais AB, Tom no Canal C */
	Giaccess(16,reg+8); /* Volume do Canal A, 16: Usa o Envelope */
	Giaccess(sfx01,reg+9); /* Volume do Canal B */
	Giaccess(sfx02,reg+10); /* Volume do Canal C */
	Giaccess(160,reg+11); /* Fine Duração do Envelope */
	Giaccess(15,reg+12);  /* Course Duração do Envelope */
	Giaccess(9,reg+13); /* Tipo de Envelope */
	
}

/* Cria o Som de um Bomba */
void sombomba(void)
{

	Giaccess(7,reg+7);	/* Ruído nos Canais ABC */
	Giaccess(16,reg+8);  /* Volume do Canal A, 16: Usa o Envelope */
	Giaccess(16,reg+9);  /* Volume do Canal B, 16: Usa o Envelope */
	Giaccess(16,reg+10); /* Volume do Canal C, 16: Usa o Envelope */
	Giaccess(112,reg+11); /* Fine Duração do Envelope */
	Giaccess(23,reg+12);  /* Course Duração do Envelope */
	Giaccess(9,reg+13); /* Tipo de Envelope */
	
}

/* Decrementa o Som do Disparo */
void decsomdisparo(void)
{
	
	sfx01--;
	Giaccess(sfx01,reg+9); /* Volume do Canal B */
	
}

/* Cria o Som do Disparo */
void somdisparo(void)
{

	sfx01=9;
	Giaccess(35,reg+7);	/* Ruído nos Canais AB, Tom no Canal C */
	Giaccess(sfx01,reg+9); /* Volume do Canal B */
	
}

/* Decrementa o Som do Prémio */
void decsompremio(void)
{
	
	sfx02-=0.25;
	Giaccess(sfx02,reg+10); /* Volume do Canal C */
	
}

/* Cria o Som do Prémio */
void sompremio(int i)
{
	
	switch (i)
	{
		case 0:{
			Giaccess(190,reg+4);/* Fine Picth do Canal C */
			Giaccess(0,reg+5);	/* Course Picth do Canal C */
			break;
		}
		case 1:{
			Giaccess(125,reg+4);/* Fine Picth do Canal C */
			Giaccess(1,reg+5);	/* Course Picth do Canal C */
			break;
		}
		case 2:{
			Giaccess(95,reg+4);	/* Fine Picth do Canal C */
			Giaccess(0,reg+5);	/* Course Picth do Canal C */
			break;
		}
		case 3:{
			Giaccess(63,reg+4);	/* Fine Picth do Canal C */
			Giaccess(0,reg+5);	/* Course Picth do Canal C */
			break;
		}
		case 4:{
			Giaccess(127,reg+4);	/* Fine Picth do Canal C */
			Giaccess(0,reg+5);	/* Course Picth do Canal C */
			break;
		}
		case 5:{
			Giaccess(254,reg+4);/* Fine Picth do Canal C */
			Giaccess(0,reg+5);	/* Course Picth do Canal C */
			break;
		}
	}
	
	sfx02=15;
	Giaccess(35,reg+7);	/* Ruído nos Canais AB, Tom no Canal C */
	Giaccess(sfx02,reg+10); /* Volume do Canal C */
	
}

/* Lê Tabela de Senos e Cosenos */
int letabsincos(void)
{

	FILE *fp;
	
	printf("Reading Sin and Cos Table File.\n");
	
	/* Lê a Tabela de Senos e Cosenos a partir de um Ficheiro */
	fp=fopen("sincos.dat","rb");
	
    if(fp==NULL)
	{
		printf("Impossible to Open Sin and Cos Table File!\n");
		return(1);
	}

	if (fread(tsincos,sizeof(tsincos),1,fp)==0)
	{
		printf("Error Reading Sin and Cos Table File!\n");
		fclose(fp);
		return(2);
	}

	printf("Success Reading Sin and Cos Table File!\n");
	fclose(fp);
	return(0);
		
}

/* Lê os Sprites e Máscaras do ficheiro *.PI1 */
int getsprites(void)
{

	int f=1;
	int i=0;
	
	printf("\nLoading Sprites.\n");

	gpPicture = File_Load( "SPR_16.PI1" );

	if(gpPicture)
	{
		
		printf("Success Loading Sprites!\n");
		f=0;
		
		Video_SetPalST( &gpPicture->mHeader.mPalette[ 0 ] );

		/* Máscaras */
		/* Inimigos Pequenos : 0-5 */
		for (i=0; i<6; i++)
			lpMskIni[i] = Sprite_MaskCreate(&gpPicture->mPixels[ 2588+(i*4) ],16,12,4,4,0);
		
		/*	Inimigo Fighter I : 6 */
		lpMskIni[6] = Sprite_MaskCreate(&gpPicture->mPixels[ 0 ],16,16,4,4,0);
		
		/*	Inimigo Fighter II : 7 */
		lpMskIni[7] = Sprite_MaskCreate(&gpPicture->mPixels[ 4 ],16,16,4,4,0);
		
		/*	Inimigo Stealth : 8 */
		lpMskIni[8] = Sprite_MaskCreate(&gpPicture->mPixels[ 8 ],16,24,4,4,0);
		
		/*	Inimigo Bomber : 9 */
		lpMskIni[9] = Sprite_MaskCreate(&gpPicture->mPixels[ 12 ],16,23,4,4,0);
		
		/*	Inimigo Boss I : 10 */
		lpMskIni[10] = Sprite_MaskCreate(&gpPicture->mPixels[ 28 ],48,32,4,4,0);
		
		/*	Inimigo Boss II : 11 */
		lpMskIni[11] = Sprite_MaskCreate(&gpPicture->mPixels[ 40 ],48,32,4,4,0);
		
		/*	Inimigo Boss III : 12 */
		lpMskIni[12] = Sprite_MaskCreate(&gpPicture->mPixels[ 52 ],32,48,4,4,0);
		
		/*	Inimigo Boss IV : 13 */
		lpMskIni[13] = Sprite_MaskCreate(&gpPicture->mPixels[ 3860 ],32,46,4,4,0);
		
		/*	Inimigo Boss V : 14 */
		lpMskIni[14] = Sprite_MaskCreate(&gpPicture->mPixels[ 7680 ],64,30,4,4,0);
		
		/* Nave */
		lpMskNv[0] = Sprite_MaskCreate(&gpPicture->mPixels[ 2560 ],16,16,4,4,0);
		lpMskNv[1] = Sprite_MaskCreate(&gpPicture->mPixels[ 2564 ],16,16,4,4,0);
		
		/* Disparo 1 */
		lpMskTiro[0] = Sprite_MaskCreate(&gpPicture->mPixels[ 6408 ],16,8,4,4,0);
		
		/* Disparo 2 */
		lpMskTiro[1] = Sprite_MaskCreate(&gpPicture->mPixels[ 6412 ],16,8,4,4,0);
		
		/* Disparo Inimigo 1 */
		lpMskTiroIni[0] = Sprite_MaskCreate(&gpPicture->mPixels[ 6400 ],16,8,4,4,0);
		
		/* Disparo Inimigo 2 */
		lpMskTiroIni[1] = Sprite_MaskCreate(&gpPicture->mPixels[ 6404 ],16,8,4,4,0);
		
		/* Explosões */
		for (i=0; i<NUMEXPLOS; i++)
			lpMskExplo[i] = Sprite_MaskCreate(&gpPicture->mPixels[ 3840+(i*4) ],16,16,4,4,0);
		
		/* Prémios */
		for (i=0; i<NUMPREMIOS-1; i++)
			lpMskPremio[i] = Sprite_MaskCreate(&gpPicture->mPixels[ 2568+(i*4) ],16,11,4,4,0);
		lpMskPremio[NUMPREMIOS-1] = Sprite_MaskCreate(&gpPicture->mPixels[ 3856 ],16,11,4,4,0);
		
		/* Título */
		lpMskTitle = Sprite_MaskCreate(&gpPicture->mPixels[ 10240 ],192,18,4,4,0);
		
		/* Painel */
		lpMskPainel = Sprite_MaskCreate(&gpPicture->mPixels[ 60 ],80,200,4,4,0);
		
		/* Sprites */
		/* Inimigos Pequenos : 0-5 */
		for (i=0; i<6; i++)
			lpSpriteIni[i] = Sprite_Create(&gpPicture->mPixels[ 2588+(i*4) ],lpMskIni[i],16,12,4,4,0);
		
		/*	Inimigo Fighter I : 6 */		
		lpSpriteIni[6] = Sprite_Create(&gpPicture->mPixels[ 0 ],lpMskIni[6],16,16,4,4,0);
		
		/*	Inimigo Fighter II : 7 */		
		lpSpriteIni[7] = Sprite_Create(&gpPicture->mPixels[ 4 ],lpMskIni[7],16,16,4,4,0);
		
		/*	Inimigo Stealth : 8 */
		lpSpriteIni[8] = Sprite_Create(&gpPicture->mPixels[ 8 ],lpMskIni[8],16,24,4,4,0);
		
		/*	Inimigo Bomber : 9 */
		lpSpriteIni[9] = Sprite_Create(&gpPicture->mPixels[ 12 ],lpMskIni[9],16,23,4,4,0);
		
		/*	Inimigo Boss I : 10 */
		lpSpriteIni[10] = Sprite_Create(&gpPicture->mPixels[ 28 ],lpMskIni[10],48,32,4,4,0);
		
		/*	Inimigo Boss II : 11 */
		lpSpriteIni[11] = Sprite_Create(&gpPicture->mPixels[ 40 ],lpMskIni[11],48,32,4,4,0);
		
		/*	Inimigo Boss III : 12 */
		lpSpriteIni[12] = Sprite_Create(&gpPicture->mPixels[ 52 ],lpMskIni[12],32,48,4,4,0);
		
		/*	Inimigo Boss IV : 13 */
		lpSpriteIni[13] = Sprite_Create(&gpPicture->mPixels[ 3860 ],lpMskIni[13],32,46,4,4,0);
		
		/*	Inimigo Boss V : 14 */
		lpSpriteIni[14] = Sprite_Create(&gpPicture->mPixels[ 7680 ],lpMskIni[14],64,30,4,4,0);
		
		/* Nave */
		lpSpriteNv[0] = Sprite_Create(&gpPicture->mPixels[ 2560 ],lpMskNv[0],16,16,4,4,0);
		lpSpriteNv[1] = Sprite_Create(&gpPicture->mPixels[ 2564 ],lpMskNv[1],16,16,4,4,0);
		
		/* Disparo 1 */
		lpSpriteTiro[0] = Sprite_Create(&gpPicture->mPixels[ 6408 ],lpMskTiro[0],16,8,4,4,0);
		
		/* Disparo 2 */
		lpSpriteTiro[1] = Sprite_Create(&gpPicture->mPixels[ 6412 ],lpMskTiro[1],16,8,4,4,0);
		
		/* Disparo Inimigo 1 */
		lpSpriteTiroIni[0] = Sprite_Create(&gpPicture->mPixels[ 6400 ],lpMskTiroIni[0],16,8,4,4,0);
		
		/* Disparo Inimigo 2 */
		lpSpriteTiroIni[1] = Sprite_Create(&gpPicture->mPixels[ 6404 ],lpMskTiroIni[1],16,8,4,4,0);
		
		/* Explosões */
		for (i=0; i<NUMEXPLOS; i++)
			lpSpriteExplo[i] = Sprite_Create(&gpPicture->mPixels[ 3840+(i*4) ],lpMskExplo[i],16,16,4,4,0);
		
		/* Prémios */
		for (i=0; i<NUMPREMIOS-1; i++)
			lpSpritePremio[i] = Sprite_Create(&gpPicture->mPixels[ 2568+(i*4) ],lpMskPremio[i],16,11,4,4,0);
		lpSpritePremio[NUMPREMIOS-1] = Sprite_Create(&gpPicture->mPixels[ 3856 ],lpMskPremio[NUMPREMIOS-1],16,11,4,4,0);
	
		/* Título */
		lpSpriteTitle = Sprite_Create(&gpPicture->mPixels[ 10240 ],lpMskTitle,192,18,4,4,0);
		
		/* Painel */
		lpSpritePainel = Sprite_Create(&gpPicture->mPixels[ 60 ],lpMskPainel,80,200,4,4,0);
	
		/* Destrói as Máscaras */
		/* Inimigos */
		for (i=0; i<NUMINIS; i++)
			Sprite_MaskDestroy(lpMskIni[i]);
		
		/* Nave */
		Sprite_MaskDestroy(lpMskNv[0]);
		Sprite_MaskDestroy(lpMskNv[1]);
		
		/* Disparos */
		Sprite_MaskDestroy(lpMskTiro[0]);
		Sprite_MaskDestroy(lpMskTiro[1]);
		
		/* Disparos Inimigos */
		Sprite_MaskDestroy(lpMskTiroIni[0]);
		Sprite_MaskDestroy(lpMskTiroIni[1]);
		
		/* Explosões */
		for (i=0; i<NUMEXPLOS; i++)
			Sprite_MaskDestroy(lpMskExplo[i]);
		
		/* Prémios */
		for (i=0; i<NUMPREMIOS; i++)
			Sprite_MaskDestroy(lpMskPremio[i]);
		
		/* Título */
		Sprite_MaskDestroy(lpMskTitle);
		
		/* Painel */
		Sprite_MaskDestroy(lpMskPainel);
		
	}
	else printf("Error Loading Sprites!\n");
		
	File_UnLoad(gpPicture);
		
	return(f);
	
}

/* Destrói os Sprites */
void freesprites(void)
{
	
	int i;
		
	/* Inimigos */
	for (i=0; i<NUMINIS; i++);
		Sprite_Destroy(lpSpriteIni[i]);
			
	/* Nave */
	Sprite_Destroy(lpSpriteNv[0]);
	Sprite_Destroy(lpSpriteNv[1]);
		
	/* Disparos */
	Sprite_Destroy(lpSpriteTiro[0]);
	Sprite_Destroy(lpSpriteTiro[1]);
		
	/* Disparos Inimigos */
	Sprite_Destroy(lpSpriteTiroIni[0]);
	Sprite_Destroy(lpSpriteTiroIni[1]);
		
	/* Explosões */
	for (i=0; i<NUMEXPLOS; i++);
		Sprite_Destroy(lpSpriteExplo[i]);
			
	/* Prémios */
	for (i=0; i<NUMPREMIOS; i++);
		Sprite_Destroy(lpSpritePremio[i]);
		
	/* Título */
	Sprite_Destroy(lpSpriteTitle);
	
	/* Painel */
	Sprite_Destroy(lpSpritePainel);
			
}

/* Cria as definições dos Diversos Tipos de Inimigos */
void criatipoini(void)
{

	int i;
	
	/* Inimigos Pequenos : 0-5 */
	for (i=0; i<6; i++)
	{
		tipoini[i].tx=12;
		tipoini[i].ty=12;
		tipoini[i].hull=1;
		tipoini[i].speed=1;
		tipoini[i].pontos=5;
	}
	
	/* Inimigos Figther I : 6 */
	tipoini[6].tx=15;
	tipoini[6].ty=16;
	tipoini[6].hull=1;
	tipoini[6].speed=1;
	tipoini[6].pontos=10;
		
	/* Inimigos Figther II : 7 */
	tipoini[7].tx=16;
	tipoini[7].ty=15;
	tipoini[7].hull=2;
	tipoini[7].speed=2;
	tipoini[7].pontos=20;
		
	/* Inimigos Stealth : 8 */
	tipoini[8].tx=15;
	tipoini[8].ty=24;
	tipoini[8].hull=3;
	tipoini[8].speed=3;
	tipoini[8].pontos=40;
		
	/* Inimigos Bomber : 9 */
	tipoini[9].tx=15;
	tipoini[9].ty=23;
	tipoini[9].hull=3;
	tipoini[9].speed=1;
	tipoini[9].pontos=50;
		
	/* Inimigos Boss I : 10 */
	tipoini[10].tx=46;
	tipoini[10].ty=32;
	tipoini[10].hull=50;
	tipoini[10].speed=2;
	tipoini[10].pontos=100;
		
	/* Inimigos Boss II : 11 */
	tipoini[11].tx=46;
	tipoini[11].ty=32;
	tipoini[11].hull=75;
	tipoini[11].speed=2;
	tipoini[11].pontos=125;
		
	/* Inimigos Boss III : 12 */
	tipoini[12].tx=30;
	tipoini[12].ty=48;
	tipoini[12].hull=100;
	tipoini[12].speed=4;
	tipoini[12].pontos=150;
		
	/* Inimigos Boss IV : 13 */
	tipoini[13].tx=30;
	tipoini[13].ty=46;
	tipoini[13].hull=125;
	tipoini[13].speed=4;
	tipoini[13].pontos=175;
		
	/* Inimigos Boss V : 14 */
	tipoini[14].tx=64;
	tipoini[14].ty=30;
	tipoini[14].hull=250;
	tipoini[14].speed=5;
	tipoini[14].pontos=250;
		
}

/* Carrega as Attack Waves e a Sequência de Attack Waves */
int loadwaves(void)
{
	
	int i,j,k; 
	
	FILE *fp; 
	
	unsigned char *mnwaves;

	printf("\nReading Attack Waves File.\n");
	
	fp=fopen("waves.dat","rb");
    if(fp==NULL)
    {
		printf("Impossible to Open Attack Waves File!!\n");
		return(1);
    }
	
	/* Número de Sequências de Attack Waves e Número de Attack Waves */
	if (fread(sawnaw,sizeof(sawnaw),1,fp)==0)
	{
		printf("Error Reading Attack Waves File!\n");
		fclose(fp);
		return(2);
	}
	
	mwaves=sawnaw[0];
	nwaves=sawnaw[1];
			
	/* Sequência de Attack Waves */
	if (fread(wave,sizeof(wave),1,fp)==0)
	{
		printf("Error Reading Attack Waves File!\n");
		fclose(fp);
		return(2);
	}
	
	/* Attack Waves */
	mnwaves=malloc(sizeof(struct twaves)*nwaves);
	
	if (fread(mnwaves,sizeof(struct twaves)*nwaves,1,fp)==0)
	{
		printf("Error Reading Attack Waves File!\n");
		free(mnwaves);
		fclose(fp);
		return(2);
	}

	printf("Success Reading Attack Waves File!\n");
	
	fclose(fp);
		
	/* Copia os diferentes tipos de Attack Waves para a Variável Definitiva */
	k=0;
	for (i=0; i<nwaves; i++)
	{
		for (j=0; j<MAXINI; j++)
		{
			twave[i].pini[j]=mnwaves[k];
			twave[i].inis[j]=mnwaves[k+6];
			twave[i].xx[j]=mnwaves[k+12];
			twave[i].yy[j]=mnwaves[k+18];
			twave[i].fpath[j]=mnwaves[k+24];
			k++;
		}
		k+=24;
	}
		
	free(mnwaves);
	
	return(0);
	
}

/* Lê as Notas da Música */
int lemusica(void)
{

	int i; 
	
	FILE *fp;
	
	unsigned char *mnotas; 
	
	printf("\nReading Music Notes.\n");
	
	/* Lê as Notas da Música a partir de um Ficheiro */
	fp=fopen("musnotes.bin","rb");
	
    if(fp==NULL)
	{
		printf("Impossible to open Music Notes File!\n");
		return(1);
	}

	/* Aloca Memória para as Notas da Música */
	mnotas=malloc(MAXNOTAS*3);

	if (fread(mnotas,MAXNOTAS*3,1,fp)==0)
	{
		printf("Error Reading Music Notes File!\n");
		free(mnotas);
		fclose(fp);
		return(2);
	}

	printf("Success Reading Music Notes File!\n");
	
	for (i=0; i<MAXNOTAS; i++)
	{
		notas[i].ca=mnotas[i*3+0];
		notas[i].cb=mnotas[i*3+1];
		notas[i].cc=mnotas[i*3+2];
	}
	
	free(mnotas);
	fclose(fp);
	return(0);
	
}

/* Lê os Instrumentos da Música */
int leinstrumentos(void)
{

	int i;

	FILE *fp;
	
	unsigned char *minstrs; 
	
	printf("\nReading Music Instruments.\n");
	
	/* Lê os Instruments da Música a partir de um Ficheiro */
	fp=fopen("musdata.bin","rb");
	
    if(fp==NULL)
	{
		printf("Impossible to open Music Instruments File!\n");
		return(1);
	}

	/* Aloca Memória para os Instrumentos da Música */
	minstrs=malloc(MAXINSTRS*4);

	if (fread(minstrs,MAXINSTRS*4,1,fp)==0)
	{
		printf("Error Reading Music Instruments File!\n");
		free(minstrs);
		fclose(fp);
		return(2);
	}

	printf("Success Reading Music Instruments File!\n");
	
	for (i=0; i<MAXINSTRS; i++)
	{
		instrs[i].fin=minstrs[i];
		instrs[i].cou=minstrs[110+i];
		instrs[i].mix=minstrs[220+i];
		instrs[i].vol=minstrs[330+i];
	}
	
	free(minstrs);
	fclose(fp);
	return(0);
	
}

/* Leitor da Música */
void musicplayer(void)
{

	/* Canal A */
	nota=notas[musica].ca;
	
	if (nota!=255)
	{
		fine=instrs[nota].fin;
		course=instrs[nota].cou;
		mixer=instrs[nota].mix;
		volume=instrs[nota].vol;

		Giaccess(fine,reg+0);		/* Fine Picth do Canal A */
		Giaccess(course,reg+1);		/* Course Picth do Canal A */
		Giaccess(mixer,reg+7);		/* Mixer */
		Giaccess(volume,reg+8); 	/* Volume do Canal A */
		Giaccess(9,reg+13); 			/* Tipo de Envelope */
	}
	
	/* Canal B */
	nota=notas[musica].cb;
	
	if (nota!=255)
	{
		fine=instrs[nota].fin;
		course=instrs[nota].cou;
		mixer=instrs[nota].mix;
		volume=instrs[nota].vol;
	
		Giaccess(fine,reg+2);		/* Fine Picth do Canal B */
		Giaccess(course,reg+3);		/* Course Picth do Canal B */
		Giaccess(volume,reg+9); 	/* Volume do Canal B */
		Giaccess(9,reg+13); 			/* Tipo de Envelope */
	}
	
	/* Canal C */
	nota=notas[musica].cc;
	
	if (nota!=255)
	{
		fine=instrs[nota].fin;
		course=instrs[nota].cou;
		mixer=instrs[nota].mix;
		volume=instrs[nota].vol;
		
		Giaccess(fine,reg+4);		/* Fine Picth do Canal C */
		Giaccess(course,reg+5);		/* Course Picth do Canal C */
		Giaccess(volume,reg+10);	/* Volume do Canal C */
		Giaccess(9,reg+13); 			/* Tipo de Envelope */
	}
		
	
	musica++;
	
	if (musica==MAXNOTAS) musica=0;
	
}