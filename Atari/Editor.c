/*************************************************************************************

	Sardonic Editor 2.0
	
 *************************************************************************************
*/

/* Default Includes */
#include <stdio.h>
#include <stdlib.h>

/* Atari Includes */
#include <tos.h>

/* Pure C Includes */
#include <ext.h>

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

#define MAXINI 6			/* Número Máximo de Inimigos no Écran */
#define MAXSTAR 10			/* Número Máximo de Estrelas no Écran */

#define NUMWAVES 255		/* Número de Tipos de Attack Waves */
#define MAXWAVE 256			/* Número Máximo de Attack Waves */
#define MAXFPATH 46			/* Número Máximo de Formation Paths */

#define MAXX 247			/* Máxima resolução horizontal */
#define MAXY 199			/* Máxima resolução vertical */
#define MINX 0				/* Máxima resolução horizontal */
#define MINY 0				/* Máxima resolução vertical */


/* My Prototypes */
void ScreenInit( void );

void inicializa(void);
void mainloop(void);

void mainmenu(void);

/* Attack Waves */
void attackwaves(void);
void carregaattackwave(void);
void printcursor(void);
void clearcursor(void);
void inputaw(void);
void updateaw(void);
void criaaw(void);
void apagaaw(int i);

/* Attack Waves Sequence */
void awsequence(void);
void carregaawseq(void);
void inputawseq(void);
void updateawseq(void);
void criaawseq(void);
void apagaawseq(int i);

void switchblitter(void);

void loadkey(void);
void savekey(void);

void initvarplay(void);
void initvarseq(void);
void initvaraw(void);
void desenhapainel(void);
void gameloop(void);
int vercriaini(int wcnt);

void clearsprites(void);
void printsprites(void);
void clearscreen(void);

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

/* Verticalmente mais Circular Direita / Esquerda */
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

int letabsincos(void);
int getsprites(void);
void freesprites(void);
void criatipoini(void);

int gravawaves(void);
int loadwaves(void);

/* GODLib Variables */
sDegas			*gpPicture;
sGraphicPos		lPos;
sGraphicRect	lRect;

sGraphicPos		lPosSavedIni[MAXINI][2];
sSprite 		*lpSpriteIni[NUMINIS];

U16 			*lpMskIni[NUMINIS];

sGraphicPos		lPosStar[10],lPosSavedStar[10][2];

sGraphicPos		lPosCur,lPosSavedCur;

/* My Variables */
int inimigos;
int tipini;
int xpos,ypos,rfact;

int counter,tempcounter;
int estado,tempestado;

unsigned short wave[MAXWAVE];
int wcnt,wcnt2,tpini;
float tsincos[2][126];

unsigned short sawnaw[2];

short nwave,nwaves;
short mwave,mwaves;

short awx,awy;
char awc[3];
int awi,awj;
int awedit;
char tccc[3];
int cc=0,dd=0,uu=0;
int keypressed=0;

short swy;
short mswy;

short ratestar;

char txterror[50];


/* Definição dos Tipos dos Inimigos */
struct tipoinis
{
		int tx,ty;
		int hull;
		int speed;
		int pontos;
		int py;
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

/* Definição das Attack Waves */
struct twaves
{
	unsigned char pini[MAXINI];
	unsigned char inis[MAXINI];
	unsigned char xx[MAXINI];
	unsigned char yy[MAXINI];
	unsigned char fpath[MAXINI];
};

struct tipoinis tipoini[NUMINIS];
struct inis ini[MAXINI];

struct twaves twave[NUMWAVES];

/* Main */
S16	GodLib_Game_Main(void)
{

	if (letabsincos()!=0)
		return(1);
	
	inicializa();
	
	GemDos_Super(0);
	Platform_Init();

	if (getsprites()!=0)
	{
		Platform_DeInit();
		return(1);
	}

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
	Graphic_SetBlitterEnable(0);

}

/* Inicializa */
void inicializa(void)
{
	
	int f;
	
	criatipoini();

	printf("Reading Attack Waves File.\n");	
	f=loadwaves();
	
	if (f==0)
	{
		printf("Success Reading Attack Waves File!\n\n");
		
		mwave=0;
		nwave=nwaves-1;
	}
	else
	{
		if (f==1) printf("Impossible to Open Attack Waves File!\n");
		if (f==2) printf("Error Reading Attack Waves File!\n");
		if (f==3) printf("Error Allocating Memory!\n");
		
		mwave=0;
		mwaves=0;
	
		nwave=0;
		nwaves=0;
	}
	
}

/* Loop Principal */
void mainloop(void)
{

	while (estado!=10)
	{
		switch (estado)
		{
			case 0:mainmenu();break;
			case 1:attackwaves();break;
			case 2:awsequence();break;
			case 3:initvarplay();break;
			case 4:gameloop();break;
			case 5:initvarseq();break;
			case 6:initvaraw();break;
		}
	}
	
}

/* Menu Principal - Estado=0 */
void mainmenu()
{

	clearscreen();

	Font8x8_Print("Sardonic Editor 2.0",Screen_GetpPhysic(),82,16);
	
	
	if(Graphic_GetBlitterEnable())
		Font8x8_Print( "Blitter is ON ",Screen_GetpPhysic(),108,32);
	else
		Font8x8_Print( "Blitter is OFF",Screen_GetpPhysic(),104,32);
	

	Font8x8_Print("1 - Attack Waves",Screen_GetpPhysic(),16,56);
	Font8x8_Print("2 - Attack Waves Sequence",Screen_GetpPhysic(),16,72);
	Font8x8_Print("3 - Play Attack Waves Sequence",Screen_GetpPhysic(),16,88);
	Font8x8_Print("4 - Load Attack Waves",Screen_GetpPhysic(),16,104);
	Font8x8_Print("5 - Save Attack Waves",Screen_GetpPhysic(),16,120);
	Font8x8_Print("6 - Swicth Blitter ON/OFF",Screen_GetpPhysic(),16,136);
	
	Font8x8_Print("Escape - Quit",Screen_GetpPhysic(),108,176);
	Font8x8_Print("                                       ",Screen_GetpPhysic(),0,192);
	
	while (estado==0)
	{
		if (IKBD_GetKeyStatus(eIKBDSCAN_1)) estado=1;
		if (IKBD_GetKeyStatus(eIKBDSCAN_2)) estado=2;
		if (IKBD_GetKeyStatus(eIKBDSCAN_3)) estado=3;
		if (IKBD_GetKeyStatus(eIKBDSCAN_4)) loadkey();
		if (IKBD_GetKeyStatus(eIKBDSCAN_5)) savekey();
		if (IKBD_GetKeyStatus(eIKBDSCAN_6)) switchblitter();
		if (IKBD_GetKeyStatus(eIKBDSCAN_ESC)) estado=10;
	};

	IKBD_ClearBuffer();
	Screen_Physic_ClearScreen_Clip();
	
}

/* Cria/Edita as Attack Waves */
void attackwaves(void)
{

	clearscreen();
	
	lPosCur.mX=50;
	lPosCur.mY=64;
	
	lPosSavedCur.mX=lPosCur.mX;
	lPosSavedCur.mY=lPosCur.mY;
	
	awx=0;
	awy=0;
	awj=3;
	awedit=0;
	
	Font8x8_Print("Attack Waves Editor",Screen_GetpPhysic(),82,16);
	
	Font8x8_Print("AW - Z,X: -+1, V,B: -+5, N,M: Home End",Screen_GetpPhysic(),0,120);
	Font8x8_Print("AW - I: New, D: Delete, L: Load, S: Save",Screen_GetpPhysic(),0,128);
	Font8x8_Print("AW - P: Play, A: To Seq, Q: Zero to Seq",Screen_GetpPhysic(),0,136);
	Font8x8_Print("VL - Cursors, Num, Return, Delete, BS",Screen_GetpPhysic(),0,144);

	carregaattackwave();

	while (estado==1)
	{
		if (IKBD_GetKeyStatus(eIKBDSCAN_ESC)) estado=0; 
		
		/* Lê Attack Waves */
		if (IKBD_GetKeyStatus(eIKBDSCAN_L))
		{
			Font8x8_Print("Reading Attack Waves File.",Screen_GetpPhysic(),0,152);
			if (loadwaves()==0)
			{
				nwave=nwaves-1;
				carregaattackwave();
			}
			
			Font8x8_Print(txterror,Screen_GetpPhysic(),0,152);
		}
		
		/* Cria Nova Attack Waves */
		if (IKBD_GetKeyStatus(eIKBDSCAN_I))
		{
			criaaw();
			carregaattackwave();
		}
		
		if (nwaves>0)
		{
			
			/* Play Attack Wave Currente */
			if (IKBD_GetKeyStatus(eIKBDSCAN_P))
			{
				mwaves++;
				mwave=mwaves-1;
				wave[mwaves-1]=nwave;
				estado=6;
			}
			
			/* Adiciona Attack Wave Currente à Sequência de Attack Waves */
			if (IKBD_GetKeyStatus(eIKBDSCAN_A)) 
			{
				mwaves++;
				wave[mwaves-1]=nwave;
				delay(75);
				carregaattackwave();
			};
			
			/* Adiciona Attack Wave Vazia à Sequência de Attack Waves */
			if (IKBD_GetKeyStatus(eIKBDSCAN_Q)) 
			{
				mwaves++;
				wave[mwaves-1]=0;
				delay(75);
				carregaattackwave();
			};
			
			/* Attack Waves */
			if (IKBD_GetKeyStatus(eIKBDSCAN_Z) && nwave>0) /* Esquerda */
			{
				nwave--;
				carregaattackwave();
			};
		
			if (IKBD_GetKeyStatus(eIKBDSCAN_X) && nwave<nwaves-1) /* Direita */
			{
				nwave++;
				carregaattackwave();
			};
			
			if (IKBD_GetKeyStatus(eIKBDSCAN_N)) /* Home */
			{
				nwave=0;
				carregaattackwave();
			};
			
			if (IKBD_GetKeyStatus(eIKBDSCAN_M)) /* End */
			{
				nwave=nwaves-1;
				carregaattackwave();
			};
			
			if (IKBD_GetKeyStatus(eIKBDSCAN_V)) /* Page Down */
			{
				nwave-=10;
				if (nwave<0) nwave=0;
				carregaattackwave();
			};
			
			if (IKBD_GetKeyStatus(eIKBDSCAN_B)) /* Page Up */
			{
				nwave+=10;
				if (nwave>nwaves-1) nwave=nwaves-1;
				carregaattackwave();
			};
			
			/* Grava Attack Waves */
			if (IKBD_GetKeyStatus(eIKBDSCAN_S))
			{
				Font8x8_Print("Writing Attack Waves File.",Screen_GetpPhysic(),0,152);
				if (gravawaves()==0)
					carregaattackwave();
							
				Font8x8_Print(txterror,Screen_GetpPhysic(),0,152);
			}
			
			/* Apaga a Attack Wave Currente */
			if (IKBD_GetKeyStatus(eIKBDSCAN_D))
			{
				apagaaw(nwave);
				carregaattackwave();
			}
			
			/* Valores */
			if (IKBD_GetKeyStatus(eIKBDSCAN_LEFTARROW) && lPosCur.mX>50) /* Esquerda */
			{
				if (awedit==1) updateaw();
				lPosCur.mX-=40;
				awx--;
				printcursor();
			};
		
			if (IKBD_GetKeyStatus(eIKBDSCAN_RIGHTARROW) && lPosCur.mX<250) /* Direita */
			{
				if (awedit==1) updateaw();
				lPosCur.mX+=40;
				awx++;
				printcursor();
			};
			
			if (IKBD_GetKeyStatus(eIKBDSCAN_UPARROW) && lPosCur.mY>64) /* Cima */
			{
				if (awedit==1) updateaw();
				lPosCur.mY-=8;
				awy--;
				printcursor();
			};
		
			if (IKBD_GetKeyStatus(eIKBDSCAN_DOWNARROW) && lPosCur.mY<96) /* Baixo */
			{
				if (awedit==1) updateaw();
				lPosCur.mY+=8;
				awy++;
				printcursor();
			};
			
			inputaw();
			
			delay(75);
										
		}
				
	};
	
	IKBD_ClearBuffer();

}

/* Imprime as Attack Waves */
void carregaattackwave(void)
{
	
	char txwave[40];
	
	int i;
	
	if (nwaves==0)
	{
		sprintf(txwave,"Sem Attack Waves             ");
		Font8x8_Print(txwave,Screen_GetpPhysic(),0,40);
		
		for (i=64; i<104; i+=8)
		{
			sprintf(txwave,"                                        ");
			Font8x8_Print(txwave,Screen_GetpPhysic(),0,i);		
		}
		
		clearcursor();
	}
	else
	{
		sprintf(txwave,"Attack Wave %3d / %3d - %3d   ",nwave,nwaves-1,mwaves-1);
		Font8x8_Print(txwave,Screen_GetpPhysic(),0,40);
	
		/* Tempo */
		Font8x8_Print("Time - ",Screen_GetpPhysic(),0,64);
		for (i=0; i<MAXINI; i++)
		{
			sprintf(txwave, "%3d",twave[nwave].pini[i]);
			Font8x8_Print(txwave,Screen_GetpPhysic(),56+(i*5*8),64);
		}
	
		/* Inimigos */
		Font8x8_Print("Ini  - ",Screen_GetpPhysic(),0,72);
		for (i=0; i<MAXINI; i++)
		{
			sprintf(txwave, "%3d",twave[nwave].inis[i]);
			Font8x8_Print(txwave,Screen_GetpPhysic(),56+(i*5*8),72);
		}
	
		/* XX */
		Font8x8_Print("XX   - ",Screen_GetpPhysic(),0,80);
		for (i=0; i<MAXINI; i++)
		{
			sprintf(txwave, "%3d",twave[nwave].xx[i]);
			Font8x8_Print(txwave,Screen_GetpPhysic(),56+(i*5*8),80);
		}
	
		/* YY */
		Font8x8_Print("YY   - ",Screen_GetpPhysic(),0,88);
		for (i=0; i<MAXINI; i++)
		{
			sprintf(txwave, "%3d",twave[nwave].yy[i]);
			Font8x8_Print(txwave,Screen_GetpPhysic(),56+(i*5*8),88);
		}
	
		/* FPath */
		Font8x8_Print("FPth - ",Screen_GetpPhysic(),0,96);
		for (i=0; i<MAXINI; i++)
		{
			sprintf(txwave, "%3d",twave[nwave].fpath[i]);
			Font8x8_Print(txwave,Screen_GetpPhysic(),56+(i*5*8),96);
		}
		
		printcursor();
	}
	
	sprintf(txwave,"                                        ");
	Font8x8_Print(txwave,Screen_GetpPhysic(),0,152);
}

/* Imprime Cursor das Attack Waves */
void printcursor(void)
{
	
	clearcursor();
	
	lRect.mX=lPosCur.mX;
	lRect.mY=lPosCur.mY;
	lRect.mWidth=4;
	lRect.mHeight=8;
	
	Screen_Physic_DrawBox(&lRect,13);
	
	lPosSavedCur.mX=lPosCur.mX;
	lPosSavedCur.mY=lPosCur.mY;
	
}

/* Apaga Cursor das Attack Waves */
void clearcursor(void)
{
	
	lRect.mX=lPosSavedCur.mX;
	lRect.mY=lPosSavedCur.mY;
	lRect.mWidth=4;
	lRect.mHeight=8;
	
	Screen_Physic_DrawBox(&lRect,0);
		
}

/* Edita os Valores da Attack Wave */
void inputaw(void)
{
	
	cc=0;
	dd=0;
	uu=0;
	keypressed=0;
			
	if (IKBD_GetKeyStatus(eIKBDSCAN_0) && awj>0)
	{
		keypressed=1;
		uu=0;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_1) && awj>0)
	{
		keypressed=1;
		uu=1;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_2) && awj>0)
	{
		keypressed=1;
		uu=2;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_3) && awj>0)
	{
		keypressed=1;
		uu=3;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_4) && awj>0)
	{
		keypressed=1;
		uu=4;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_5) && awj>0)
	{
		keypressed=1;
		uu=5;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_6) && awj>0)
	{
		keypressed=1;
		uu=6;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_7) && awj>0)
	{
		keypressed=1;
		uu=7;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_8) && awj>0)
	{
		keypressed=1;
		uu=8;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_9) && awj>0)
	{
		keypressed=1;
		uu=9;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_BACKSPACE) && awj<3 && awedit==1)
	{
		awj++;
	
		if (awj==1)
		{
			awc[2]=awc[1];
			awc[1]=awc[0];
			awc[0]=' ';
		}
		
		if (awj==2)
		{
			awc[2]=awc[1];
			awc[1]=' ';
			awc[0]=' ';
		}
		
		if (awj==3)
		{
			awc[2]=' ';
			awc[1]=' ';
			awc[0]=' ';
		}
		
		awc[3]='\0';
		
		Font8x8_Print(awc,Screen_GetpPhysic(),56+(awx*5*8),(awy*8)+64);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_DELETE) && awj<3 && awedit==1)
	{
		
		if (awc[awj]==' ') awj++;
		else awc[awj]=' ';
		
		awc[3]='\0';
		
		Font8x8_Print(awc,Screen_GetpPhysic(),56+(awx*5*8),(awy*8)+64);
	};
	
	if (keypressed==1)
	{
		awj--;
	
		if (awj==0)
		{
			awc[0]=awc[1];
			awc[1]=awc[2];
		}
		
		if (awj==1)
		{
			awc[0]=' ';
			awc[1]=awc[2];
		}
		
		if (awj==2)
		{
			awc[0]=' ';
			awc[1]=' ';
		}
		
		awc[2]=uu+48;
		awc[3]='\0';
		
		Font8x8_Print(awc,Screen_GetpPhysic(),56+(awx*5*8),(awy*8)+64);
	}
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_RETURN) && awedit==1)
		updateaw();
			
}

/* Coloca os Novos Valores na Attack Wave */
void updateaw(void)
{
	
	awj=3;
		
	if (awc[0]==' ') cc=0;
	else cc=(int)((awc[0]-48)*100);
		
	if (awc[1]==' ') dd=0;
	else dd=(int)((awc[1]-48)*10);
		
	if (awc[2]==' ') uu=0;
	else uu=(int)(awc[2]-48);
	
	awi=cc+uu+dd;
		
	if (awy==0 && awi>255) awi=255;
	if (awy==1)
		if (awi>NUMINIS-1 && awi!=255) awi=NUMINIS-1;
	if (awy==2 && awi>248) awi=248;
	if (awy==3 && awi>160) awi=160;
	if (awy==4 && awi>MAXFPATH-1) awi=MAXFPATH-1;
		
	sprintf(tccc, "%3d",awi);
	Font8x8_Print(tccc,Screen_GetpPhysic(),56+(awx*5*8),(awy*8)+64);
		
	Screen_Physic_DrawBox(&lRect,13);
	awedit=0;
		
	if (awy==0)
		twave[nwave].pini[awx]=awi;
		
	if (awy==1)
		twave[nwave].inis[awx]=awi;
		
	if (awy==2)
		twave[nwave].xx[awx]=awi;
		
	if (awy==3)
		twave[nwave].yy[awx]=awi;
		
	if (awy==4)
		twave[nwave].fpath[awx]=awi;
	
}

/* Cria Nova Attack Wave */
void criaaw(void)
{
	
	int k,j;
	
	/* Se estivermos na Última Attack Wave */
	if (nwave==nwaves-1)
	{
		nwave++;
		nwaves++;
		/* Cria a Nova Attack Wave */
		for (k=0; k<MAXINI; k++)
		{
			twave[nwave].pini[k]=0;
			twave[nwave].inis[k]=255;
			twave[nwave].xx[k]=0;
			twave[nwave].yy[k]=0;
			twave[nwave].fpath[k]=0;
		}
	}
	else /* Se não estivermos na Última Attack Wave */
	{
		nwaves++;
		/* Rodas as Attack Waves para a frente */
		for (j=nwaves-1; j>nwave; j--)
			for (k=0; k<MAXINI; k++)
			{
				twave[j].pini[k]=twave[j-1].pini[k];
				twave[j].inis[k]=twave[j-1].inis[k];
				twave[j].xx[k]=twave[j-1].xx[k];
				twave[j].yy[k]=twave[j-1].yy[k];
				twave[j].fpath[k]=twave[j-1].fpath[k];
			}
	
		/* Cria a Nova Attack Wave */
		for (k=0; k<MAXINI; k++)
		{
			twave[nwave].pini[k]=0;
			twave[nwave].inis[k]=255;
			twave[nwave].xx[k]=0;
			twave[nwave].yy[k]=0;
			twave[nwave].fpath[k]=0;
		}
		
	}
	
}

/* Apaga Attack Wave */
void apagaaw(int i)
{
	
	int k,j;
	
	for (j=i; j<nwaves; j++)
		for (k=0; k<MAXINI; k++)
		{
			twave[j].pini[k]=twave[j+1].pini[k];
			twave[j].inis[k]=twave[j+1].inis[k];
			twave[j].xx[k]=twave[j+1].xx[k];
			twave[j].yy[k]=twave[j+1].yy[k];
			twave[j].fpath[k]=twave[j+1].fpath[k];
		}
		
	if (nwave==nwaves-1) nwave--;
		
	nwaves--;
	
}

/* Sequência de Attack Waves */
void awsequence(void)
{

	char txwave[20];
	
	int mudap;
	
	clearscreen();
	
	lPosCur.mX=42;
	lPosCur.mY=32;
	
	lPosSavedCur.mX=lPosCur.mX;
	lPosSavedCur.mY=lPosCur.mY;
	
	awj=3;
	awedit=0;
	
	swy=mwave;
	
	if (mwaves>20)
	{
		mswy=20;
		if (mwave+mswy>mwaves-1)
		{
			swy=mwaves-mswy;
			lPosCur.mY=32+((mwave-swy)*8);
		}
		else
		{
			swy=mwave;
			lPosCur.mY=32;
		}
	}
	else
	{
		swy=0;
		mswy=mwaves;
		lPosCur.mY=32+((mwave)*8);
	}
	
	Font8x8_Print("Attack Waves Sequence Editor",Screen_GetpPhysic(),48,0);
	
	Font8x8_Print("AWS: V,B:-+ 20, N,M:0 End",Screen_GetpPhysic(),96,32);
	Font8x8_Print("AWS: I:New, D:Delete",Screen_GetpPhysic(),96,40);
	Font8x8_Print("AWS: L:Load S:Save P:Play",Screen_GetpPhysic(),96,48);
	Font8x8_Print("VL - Cursors, Num, Return",Screen_GetpPhysic(),96,56);
	Font8x8_Print("VL - Delete, BS",Screen_GetpPhysic(),96,64);

	carregaawseq();

	while (estado==2)
	{
		if (IKBD_GetKeyStatus(eIKBDSCAN_ESC)) estado=0;
		
		/* Lê Attack Waves */
		if (IKBD_GetKeyStatus(eIKBDSCAN_L))
		{
			Font8x8_Print("Reading Attack Waves File.",Screen_GetpPhysic(),0,192);
			if (loadwaves()==0)
			{
				mwave=0;
				swy=mwave;
				carregaawseq();
			}
			
			Font8x8_Print(txterror,Screen_GetpPhysic(),0,192);
		}
		
		/* Cria Nova Sequência de Attack Waves */
		if (IKBD_GetKeyStatus(eIKBDSCAN_I))
		{
			criaawseq();
			
			if (mwave==mwaves-1)
			{
				if (mwaves>20)
				{
					swy++;
					lPosCur.mY=184;
				}
				else
				{
					mswy++;
					lPosCur.mY=32+((mswy-1)*8);
				}
			}
		
			carregaawseq();
		}
		
		if (mwaves>0)
		{
			
			/* Sequência de Attack Waves */
			if (IKBD_GetKeyStatus(eIKBDSCAN_N)) /* Home */
			{
				mwave=0;
				swy=0;
				lPosCur.mY=32;
				carregaawseq();
			};
			
			if (IKBD_GetKeyStatus(eIKBDSCAN_M)) /* End */
			{
				mwave=mwaves-1;
				
				if (mwaves>20)
				{
					swy=mwaves-mswy;
					lPosCur.mY=184;
				}
				else
				{
					swy=0;
					lPosCur.mY=32+((mswy-1)*8);
				}
				
				carregaawseq();
			};
			
			if (IKBD_GetKeyStatus(eIKBDSCAN_V)) /* Page Up */
			{
				mwave-=20;
				swy=mwave;
				lPosCur.mY=32;
				
				if (mwave<0)
				{
					mwave=0;
					swy=0;
				}
				
				carregaawseq();
			};
			
			if (IKBD_GetKeyStatus(eIKBDSCAN_B)) /* Page Down */
			{
				mwave+=20;
				swy=mwave;
				lPosCur.mY=32;
				
				if (mwave+mswy>mwaves-1 && mwaves>20)
				{
					mwave=mwaves-mswy;
					swy=mwave;
					lPosCur.mY=32;
				}
			
				if (mwave>mwaves-1)
				{
					mwave=mwaves-1;
					if (mwaves>20)	
					{
						swy=mwave-mswy+1;
						lPosCur.mY=184;
					}
					else
					{
						mswy=mwaves;
						swy=0;
						lPosCur.mY=32+((mswy-1)*8);
					}
				}
				
				carregaawseq();
			};
			
			/* Play Sequência de Attack Waves */
			if (IKBD_GetKeyStatus(eIKBDSCAN_P)) estado=5;
			
			/* Grava Attack Waves */
			if (IKBD_GetKeyStatus(eIKBDSCAN_S))
			{
				Font8x8_Print("Writing Attack Waves File.",Screen_GetpPhysic(),0,192);
				if (gravawaves()==0)
					carregaawseq();
							
				Font8x8_Print(txterror,Screen_GetpPhysic(),0,192);
			}
			
			/* Apaga a Sequência de Attack Wave Currente */
			if (IKBD_GetKeyStatus(eIKBDSCAN_D))
			{
				apagaawseq(mwave);
				
				if (mwave+mswy>mwaves-1 && mwaves>20 && swy>0)
					swy--;
				
				if (mwave==mwaves-1)
					if (mwaves>20)	
					{
						swy=mwave-mswy+1;
						lPosCur.mY=184;
					}
					else
					{
						mswy=mwaves;
						swy=0;
						if (mwaves>0) lPosCur.mY=32+((mswy-1)*8);
					}
					
				
				carregaawseq();
			}
			
			/* Valores */
			if (IKBD_GetKeyStatus(eIKBDSCAN_UPARROW) && mwave>0) /* Cima */
			{
				if (awedit==1)
				{
					updateawseq();
					carregaawseq();
				}
				
				mwave--;
				mudap=1;
				
				if (lPosCur.mY>32)
				{
					lPosCur.mY-=8;
					printcursor();
					mudap=0;
				}
							
				if (mwave>-1 && lPosCur.mY==32 && mudap==1)
				{
					swy--;
					carregaawseq();	
				}
				else
				{
					sprintf(txwave,"Sequencia %3d / %3d   ",mwave,mwaves-1); 
					Font8x8_Print(txwave,Screen_GetpPhysic(),0,16);
				}
			};
		
			if (IKBD_GetKeyStatus(eIKBDSCAN_DOWNARROW) && mwave<mwaves-1) /* Baixo */
			{
				if (awedit==1)
				{
					updateawseq();
					carregaawseq();
				}
				
				mwave++;
				mudap=1;
				
				if (lPosCur.mY<184)
				{
					lPosCur.mY+=8;
					printcursor();
					mudap=0;					
				}
												
				if (mwave<mwaves && lPosCur.mY==184 && mudap==1)
				{
					swy++;
					carregaawseq();	
				}
				else
				{
					sprintf(txwave,"Sequencia %3d / %3d   ",mwave,mwaves-1); 
					Font8x8_Print(txwave,Screen_GetpPhysic(),0,16);
				}
			};
			
			inputawseq();
			
			delay(75);
										
		}
				
	};
	
	IKBD_ClearBuffer();
	
}

/* Carrega Sequência de Attack Waves */
void carregaawseq(void)
{
	
	char txwave[40];
	
	int i;
	
	if (mwaves==0)
	{
		sprintf(txwave,"Sequencia Vazia             ");
		Font8x8_Print(txwave,Screen_GetpPhysic(),0,16);
		
		for (i=32; i<208; i+=8)
		{
			sprintf(txwave,"                                        ");
			Font8x8_Print(txwave,Screen_GetpPhysic(),0,i);		
		}
		
		clearcursor();
	}
	else
	{
		if (mwaves>20) mswy=20;
		else mswy=mwaves;
		
		sprintf(txwave,"Sequencia %3d / %3d   ",mwave,mwaves-1); 
		Font8x8_Print(txwave,Screen_GetpPhysic(),0,16);
	
		for (i=swy; i<(swy+mswy); i++)
		{
			sprintf(txwave, "%3d - %3d",i,wave[i]);
			Font8x8_Print(txwave,Screen_GetpPhysic(),0,32+((i-swy)*8));	
		}
		
		if (mwaves<20)
			for (i=(swy+mswy)*8; i<208; i+=8)
			{
				sprintf(txwave,"                                        ");
				Font8x8_Print(txwave,Screen_GetpPhysic(),0,32+i);		
			}
		
		printcursor();
	}
	
}

/* Edita os Valores da Sequência de Attack Waves */
void inputawseq(void)
{
	
	cc=0;
	dd=0;
	uu=0;
	keypressed=0;
			
	if (IKBD_GetKeyStatus(eIKBDSCAN_0) && awj>0)
	{
		keypressed=1;
		uu=0;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_1) && awj>0)
	{
		keypressed=1;
		uu=1;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_2) && awj>0)
	{
		keypressed=1;
		uu=2;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_3) && awj>0)
	{
		keypressed=1;
		uu=3;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_4) && awj>0)
	{
		keypressed=1;
		uu=4;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_5) && awj>0)
	{
		keypressed=1;
		uu=5;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_6) && awj>0)
	{
		keypressed=1;
		uu=6;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_7) && awj>0)
	{
		keypressed=1;
		uu=7;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_8) && awj>0)
	{
		keypressed=1;
		uu=8;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_9) && awj>0)
	{
		keypressed=1;
		uu=9;
		awedit=1;
		Screen_Physic_DrawBox(&lRect,2);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_BACKSPACE) && awj<3 && awedit==1)
	{
		awj++;
	
		if (awj==1)
		{
			awc[2]=awc[1];
			awc[1]=awc[0];
			awc[0]=' ';
		}
		
		if (awj==2)
		{
			awc[2]=awc[1];
			awc[1]=' ';
			awc[0]=' ';
		}
		
		if (awj==3)
		{
			awc[2]=' ';
			awc[1]=' ';
			awc[0]=' ';
		}
		
		awc[3]='\0';
		
		Font8x8_Print(awc,Screen_GetpPhysic(),lPosCur.mX+6,lPosCur.mY);
	};
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_DELETE) && awj<3 && awedit==1)
	{
		
		if (awc[awj]==' ') awj++;
		else awc[awj]=' ';
		
		awc[3]='\0';
		
		Font8x8_Print(awc,Screen_GetpPhysic(),lPosCur.mX+6,lPosCur.mY);
	};
	
	if (keypressed==1)
	{
		awj--;
	
		if (awj==0)
		{
			awc[0]=awc[1];
			awc[1]=awc[2];
		}
		
		if (awj==1)
		{
			awc[0]=' ';
			awc[1]=awc[2];
		}
		
		if (awj==2)
		{
			awc[0]=' ';
			awc[1]=' ';
		}
		
		awc[2]=uu+48;
		awc[3]='\0';
		
		Font8x8_Print(awc,Screen_GetpPhysic(),lPosCur.mX+6,lPosCur.mY);
	}
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_RETURN) && awedit==1)
		updateawseq();
			
}

/* Coloca os Novos Valores na Sequência de Attack Wave */
void updateawseq()
{

	awj=3;
		
	if (awc[0]==' ') cc=0;
	else cc=(int)((awc[0]-48)*100);
		
	if (awc[1]==' ') dd=0;
	else dd=(int)((awc[1]-48)*10);
		
	if (awc[2]==' ') uu=0;
	else uu=(int)(awc[2]-48);
	
	awi=cc+uu+dd;
		
	if (awi>nwaves-1) awi=nwaves-1;
		
	sprintf(tccc, "%3d",awi);
	Font8x8_Print(tccc,Screen_GetpPhysic(),lPosCur.mX+6,lPosCur.mY);
		
	Screen_Physic_DrawBox(&lRect,13);
	awedit=0;
		
	wave[mwave]=awi;
	
}

/* Cria Nova Sequência de Attack Waves */
void criaawseq(void)
{
	
	int j;
	
	/* Se estivermos na Última Sequência de Attack Waves */
	if (mwave==mwaves-1)
	{
		mwave++;
		mwaves++;
		/* Cria a Nova Attack Wave */
		wave[mwave]=0;
		
	}
	else /* Se não estivermos na Última Sequência de Attack Waves */
	{
		mwaves++;
		/* Roda as Sequências de Attack Waves para a frente */
		for (j=mwaves-1; j>mwave; j--)
			wave[j]=wave[j-1];
				
		/* Cria a Nova Sequência de Attack Waves */
		wave[mwave]=0;
	}
	
}

/* Apaga a Sequência de Attack Wave Currente */
void apagaawseq(int i)
{

	int j;
	
	for (j=i; j<mwaves; j++)
		wave[j]=wave[j+1];
		
	if (mwave==mwaves-1) mwave--;
		
	mwaves--;
	
}

/* Switch Blitter ON/OFF */
void switchblitter(void)
{

	Graphic_SetBlitterEnable(1-Graphic_GetBlitterEnable());
	
	if(Graphic_GetBlitterEnable())
		Font8x8_Print( "Blitter is ON ",Screen_GetpPhysic(),108,32);
	else
		Font8x8_Print( "Blitter is OFF",Screen_GetpPhysic(),104,32);
	
	delay(75);
	
}

/* Carrega as Attack Waves a partir do Menu */
void loadkey(void)
{

	int ldaw;
	
	Font8x8_Print("Reading Attack Waves File.",Screen_GetpPhysic(),0,192);
	ldaw=loadwaves();
	ldaw++;
	Font8x8_Print(txterror,Screen_GetpPhysic(),0,192);
	
}

/* Grava as Attack Waves a partir do Menu */
void savekey(void)
{

	int svaw;
	
	Font8x8_Print("Writing Attack Waves File.",Screen_GetpPhysic(),0,192);
	svaw=gravawaves();
	svaw++;
	Font8x8_Print(txterror,Screen_GetpPhysic(),0,192);

}

/* Inicializa as variáveis do Modo Play - Estado=3 */
void initvarplay(void)
{

	int i;

	inimigos=0;
	
	/* Desenha o StarField */
	ratestar=2;
	for (i=0; i<MAXSTAR; i++)
	{
		lPosStar[i].mX=random(MAXX);
		lPosStar[i].mY=random(MAXY);
		
		lPosSavedStar[i][0]=lPosStar[i];
		lPosSavedStar[i][1]=lPosStar[i];
	}
	
	desenhapainel();

	tempcounter=0;

	tempestado=3;
	estado=4;
		
}

/* Inicializa as variáveis do Modo Play Sequência - Estado=5 */
void initvarseq(void)
{

	int i;

	inimigos=0;
	
	/* Desenha o StarField */
	ratestar=2;
	for (i=0; i<MAXSTAR; i++)
	{
		lPosStar[i].mX=random(MAXX);
		lPosStar[i].mY=random(MAXY);
		
		lPosSavedStar[i][0]=lPosStar[i];
		lPosSavedStar[i][1]=lPosStar[i];
	}
	
	desenhapainel();

	tempcounter=mwave;

	tempestado=5;
	estado=4;
		
}

/* Inicializa as variáveis do Modo Play Attack Wave - Estado=5 */
void initvaraw(void)
{

	int i;

	inimigos=0;
	
	/* Desenha o StarField */
	ratestar=2;
	for (i=0; i<MAXSTAR; i++)
	{
		lPosStar[i].mX=random(MAXX);
		lPosStar[i].mY=random(MAXY);
		
		lPosSavedStar[i][0]=lPosStar[i];
		lPosSavedStar[i][1]=lPosStar[i];
	}
	
	desenhapainel();

	tempcounter=mwave;

	tempestado=6;
	estado=4;
		
}

/* Desenha Painel */
void desenhapainel(void)
{
	
	clearscreen();
	
	lRect.mX=248;
	lRect.mY=0;
	lRect.mWidth=72;
	lRect.mHeight=200;
	
	Screen_Logic_DrawBox(&lRect,6);
	Screen_Physic_DrawBox(&lRect,6);
	
}

/* Rotina Principal do Jogo - Estado=4 */
void gameloop(void)
{

	counter=tempcounter; /* Inicializa o Contador do Jogo */

	do
	{
		wcnt=wave[counter];	/* Vai buscar a respetiva Attack Wave */
		inimigos=0;
		wcnt2=0;
		tpini=0;
	
		while (vercriaini(wcnt)==0 && estado==4)
		{
			clearsprites(); 
			
			if (inimigos>0) moveinimigo();
			
			if (ratestar>0) ratestar--;
			movestar();
			
			printsprites();

			/* Quit */
			if (IKBD_GetKeyStatus(eIKBDSCAN_ESC))
			{
				if (tempestado==3) estado=0; 
				if (tempestado==5) estado=2;
				if (tempestado==6)
				{
					mwaves--;
					estado=1;
				}
			}
		}
			
/*		clearscreen(); */
		IKBD_ClearBuffer(); 
		counter++;
				
	} while (counter<mwaves && estado==4); /* Prossegue até WellDone, GameOver ou Exit */
	
	/* WellDone */
	if (counter>=mwaves && estado!=1)
	{
		if (tempestado==3) estado=0; 
		if (tempestado==5) estado=2;
		if (tempestado==6)
		{
			mwaves--;
			estado=1;
		}
	}

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
	
	if (IKBD_GetKeyStatus(eIKBDSCAN_RIGHTSHIFT))
	{
		wcnt2=MAXINI;
		inimigos=0;
	}
			
	if (wcnt2>=MAXINI && inimigos==0) return(1);	/* Verifica se acabou a Attack Wave atual */
	
	return(0);
	
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
	
	
}

/* Desenha os Sprites no écran */
void printsprites()
{
	int i;
	
	/* Texto */
	char txwave[20];
	sprintf(txwave, "%d/%d-%d  ",counter,mwaves-1,wave[counter]); 
	Font8x8_Print(txwave,Screen_GetpLogic(),0,0);

	/* Inimigos */
	for (i=0; i<inimigos; i++)
	{
		lPos.mX=ini[i].x;
		lPos.mY=ini[i].y;
		
		Screen_Logic_DrawSprite_Clip( &lPos, lpSpriteIni[ini[i].tipo] );
		lPosSavedIni[i][Screen_GetLogicIndex()] = lPos;
	}

}	

/* Apaga o Écran */
void clearscreen()
{

	Screen_Physic_ClearScreen_Clip();
	Screen_Logic_ClearScreen_Clip();
	
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
	else
	{
		if (fread(tsincos,sizeof(tsincos),1,fp)==0)
		{
			printf("Error Reading Sin and Cos Table File!\n");
			fclose(fp);
			return(1);
		}
		else
		{
			printf("Success Reading Sin and Cos Table File!\n\n");
			fclose(fp);
			return(0);
		}
	}
		
}

/* Lê os Sprites e Máscaras do ficheiro *.PI1 */
int getsprites(void)
{

	int f=1;
	int i=0;
	
	printf("Loading Sprites.\n");

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
		
		/* Destrói as Máscaras */
		/* Inimigos */
		for (i=0; i<NUMINIS; i++)
			Sprite_MaskDestroy(lpMskIni[i]);
		
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
		tipoini[i].py=12;
	}
	
	/* Inimigos Figther I : 6 */
	tipoini[6].tx=15;
	tipoini[6].ty=16;
	tipoini[6].hull=1;
	tipoini[6].speed=1;
	tipoini[6].pontos=10;
	tipoini[6].py=16;
	
	/* Inimigos Figther II : 7 */
	tipoini[7].tx=16;
	tipoini[7].ty=15;
	tipoini[7].hull=2;
	tipoini[7].speed=2;
	tipoini[7].pontos=20;
	tipoini[7].py=16;
	
	/* Inimigos Stealth : 8 */
	tipoini[8].tx=15;
	tipoini[8].ty=24;
	tipoini[8].hull=3;
	tipoini[8].speed=3;
	tipoini[8].pontos=40;
	tipoini[8].py=24;
	
	/* Inimigos Bomber : 9 */
	tipoini[9].tx=15;
	tipoini[9].ty=23;
	tipoini[9].hull=3;
	tipoini[9].speed=1;
	tipoini[9].pontos=50;
	tipoini[9].py=23;
	
	/* Inimigos Boss I : 10 */
	tipoini[10].tx=46;
	tipoini[10].ty=32;
	tipoini[10].hull=20; /*50;*/
	tipoini[10].speed=2;
	tipoini[10].pontos=100;
	tipoini[10].py=32;
	
	/* Inimigos Boss II : 11 */
	tipoini[11].tx=46;
	tipoini[11].ty=32;
	tipoini[11].hull=20; /*75;*/
	tipoini[11].speed=2;
	tipoini[11].pontos=125;
	tipoini[11].py=32;
	
	/* Inimigos Boss III : 12 */
	tipoini[12].tx=30;
	tipoini[12].ty=48;
	tipoini[12].hull=20; /*100;*/
	tipoini[12].speed=4;
	tipoini[12].pontos=150;
	tipoini[12].py=48;
	
	/* Inimigos Boss IV : 13 */
	tipoini[13].tx=30;
	tipoini[13].ty=46;
	tipoini[13].hull=20; /*125 */;
	tipoini[13].speed=4;
	tipoini[13].pontos=175;
	tipoini[13].py=48;
	
	/* Inimigos Boss V : 14 */
	tipoini[14].tx=64;
	tipoini[14].ty=30;
	tipoini[14].hull=20; /*250;*/
	tipoini[14].speed=5;
	tipoini[14].pontos=250;
	tipoini[14].py=30;
	
}

/* Grava o Número de Sequências de Attack Waves, o Número de Attack Waves, */
/* a Sequência de Attack Waves e as Attack Waves num Ficheiro.			   */ 
int gravawaves(void)
{
	
	int i,j,k;
	
	FILE *fp; 
	
	unsigned short *mmwaves;
	unsigned char *mnwaves;
	
	/* Número de Sequências de Attack Waves e o Número de Attack Waves */
	sawnaw[0]=mwaves;
	sawnaw[1]=nwaves;
	
	/* Copia a Sequência de Attack Waves para a Variável Temporária */
	mmwaves=malloc(sizeof(mwaves)*mwaves);
	if(mmwaves==NULL)
	{
		sprintf(txterror,"Error Allocating Memory!\0");
		return(3);
	}
	for (i=0; i<mwaves; i++)
		mmwaves[i]=wave[i];
	
				
	/* Copia os diferentes tipos de Attack Waves para a Variável Temporária */
	mnwaves=malloc(sizeof(struct twaves)*nwaves);
	if(mnwaves==NULL)
	{
		sprintf(txterror,"Error Allocating Memory!\0");
		return(3);
	}
	k=0;
	for (i=0; i<nwaves; i++)
	{
		for (j=0; j<MAXINI; j++)
        {
			mnwaves[k]=twave[i].pini[j];
			mnwaves[k+6]=twave[i].inis[j];
			mnwaves[k+12]=twave[i].xx[j];
			mnwaves[k+18]=twave[i].yy[j];
			mnwaves[k+24]=twave[i].fpath[j];
			k++;
        }
		k+=24;
	}
	
	fp=fopen("waves.dat","wb");
    if(fp==NULL)
    {
		sprintf(txterror,"Impossible to Create Attack Waves File!\0");
		free(mmwaves);
		free(mnwaves);
		return(1);
    }
	
	/* Número de Sequências de Attack Waves e Número de Attack Waves */
	if (fwrite(sawnaw,sizeof(sawnaw),1,fp)==0)
	{
		sprintf(txterror,"Error Writing Attack Waves File!\0");
		free(mmwaves);
		free(mnwaves);
		fclose(fp);
		return(2);	
	}
												
	/* Sequência de Attack Waves */
	if (fwrite(mmwaves,sizeof(mwaves)*mwaves,1,fp)==0)
	{
		sprintf(txterror,"Error Writing Attack Waves File!\0");
		free(mmwaves);
		free(mnwaves);
		fclose(fp);
		return(2);
	}
				
	/* Attack Waves */
	if (fwrite(mnwaves,sizeof(struct twaves)*nwaves,1,fp)==0)
	{
		sprintf(txterror,"Error Writing Attack Waves File!\0");
		free(mmwaves);
		free(mnwaves);
		fclose(fp);
		return(2);
	}
		
	sprintf(txterror,"Success Writing Attack Waves File!\0");
			
	fclose(fp);
	
	free(mmwaves);
	free(mnwaves);
	
	return(0);
	
}

/* Lê o Número de Sequências de Attack Waves, o Número de Attack Waves, */
/* a Sequência de Attack Waves e as Attack Waves de um Ficheiro.	    */
int loadwaves(void)
{
	
	int i,j,k;
	
	FILE *fp; 
	
	unsigned short *mmwaves;
	unsigned char *mnwaves;
	
	fp=fopen("waves.dat","rb");
    if(fp==NULL)
    {
		sprintf(txterror,"Impossible to Open Attack Waves File!\0");
		return(1);
    }
	
	/* Número de Sequências de Attack Waves e Número de Attack Waves */
	if (fread(sawnaw,sizeof(sawnaw),1,fp)==0)
	{
		sprintf(txterror,"Error Reading Attack Waves File!\0"); 
		fclose(fp);
		return(2);
	}
	
	mwaves=sawnaw[0];
	nwaves=sawnaw[1];
			
	/* Sequência de Attack Waves */
	mmwaves=malloc(sizeof(mwaves)*mwaves);
	if(mmwaves==NULL)
	{
		sprintf(txterror,"Error Allocating Memory!\0"); 
		fclose(fp);
		return(3);
	}
		
	if (fread(mmwaves,sizeof(mwaves)*mwaves,1,fp)==0)
	{
		sprintf(txterror,"Error Reading Attack Waves File!\0"); 
		free(mmwaves);
		fclose(fp);
		return(2);
	}
	
	/* Attack Waves */
	mnwaves=malloc(sizeof(struct twaves)*nwaves);
	if(mnwaves==NULL)
	{
		sprintf(txterror,"Error Allocating Memory!\0"); 
		fclose(fp);
		return(3);
	}
	
	if (fread(mnwaves,sizeof(struct twaves)*nwaves,1,fp)==0)
	{
		sprintf(txterror,"Error Reading Attack Waves File!\0"); 
		free(mmwaves);
		free(mnwaves);
		fclose(fp);
		return(2);
	}
	
	sprintf(txterror,"Success Reading Attack Waves File!\0");
	
	fclose(fp);
		
	/* Copia a Sequência de Attack Waves para a Variável Definitiva */
	for (i=0; i<mwaves; i++)
		wave[i]=mmwaves[i];
	
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
		
	free(mmwaves);
	free(mnwaves);
	
	return(0);
	
}