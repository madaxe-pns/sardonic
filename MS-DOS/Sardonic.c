/*******************************************

	Sardonic
	
	Code & Graphics by MadAxe
	Music by Frédéric Collet-Hahn
	
	(C) 2020 Penisoft

	Made in Portugal
	
	Requires a 386 and a VGA Card
	Adlib and Sound Blaster are supported
	
	Model Memory : Large
	To compile use: tcc -B -ml Sardonic.C
	
********************************************

/* Default Includes */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <dos.h>
#include <alloc.h>


/* My Defines - Jogo */
#define NUMINIS 15			/* Número de Sprites de Inimigos */
#define NUMPREMIOS 7		/* Número de Sprites de Prémios */
#define NUMEXPLOS 4			/* Número de Sprites de Explosões */
#define NUMTIROS 2			/* Número de Sprites de Tiros */
#define NUMTIROSINI 2		/* Número de Sprites de Tiros Inimigos */
#define NUMNAVES 2			/* Número de Sprites da Nave */
#define NUMPLANETAS 10		/* Número de Sprites de Planetas */

#define MAXINI 6			/* Número Máximo de Inimigos no Écran */
#define MAXTIRO 8			/* Número Máximo de Tiros no Écran */
#define MAXTIROINI 8		/* Número Máximo de Tiros Inimigos no Écran */
#define	MAXEXPLO 8			/* Número Máximo de Explosões no Écran */
#define MAXPREMIO 6			/* Número Máximo de Prémios no Écran */
#define NUMSTAR 30			/* Número Máximo de Estrelas no Écran */
#define NUMSTAR3D 45		/* Número Máximo de Estrelas 3D no Écran */

#define MAXVIDAS 9			/* Número Máximo de Vidas */
#define MAXBOMBAS 9 		/* Número Máximo de Bombas */

#define NUMWAVES 132		/* Número de Tipos de Attack Waves */
#define MAXWAVE 256			/* Número Máximo de Attack Waves */
#define MAXFPATH 46 		/* Número Máximo de Formation Paths */

#define ARMOUR 200			/* Tempo da Invencibilidade */
#define PRMTEMPO 125		/* Tempo que os Prémios ficam disponíveis */
#define RTIROFS 15			/* Intervalo de Tempo entre os Tiros : Fast Rate */
#define RTIROSL 25			/* Intervalo de Tempo entre os Tiros : Slow Rate */
#define RTINIPM 40			/* Intervalo de Tempo entre os Tiros dos Inimigos Pequenos/Médios */
#define RTINIBS 25			/* Intervalo de Tempo entre os Tiros dos Inimigos Bosses */

#define MAINTEMPO 10		/* Tempo dos Menus */

/* My Defines - VGA */
#define MAXRESX 320			/* Máxima resolução horizontal do Écran */
#define MAXRESY 200			/* Máxima resolução vertical do Écran */
#define MAXX 249			/* Máxima resolução horizontal do Jogo */
#define MAXY 199			/* Máxima resolução vertical do Jogo */
#define MINX 0				/* Máxima resolução horizontal */
#define MINY 0				/* Máxima resolução vertical */

#define PALINDEX 0x03c8		/* Porto Index da Palette */
#define PALRGBVL 0x03c9		/* Porto Valor RGB da Palette */

#define INPUT_STATUS 0x03da	/* Porto do Retrace */
#define VRETRACE 0x08		/* Valor do Vertical do Retrace */
#define HRETRACE 0x01		/* Valor do Horizontal do Retrace */

#define TXTX 8				/* Tamanho Horizontal da Fonte de Texto */
#define TYTX 8				/* Tamanho Horizontal da Fonte de Texto */
#define NCTX 40				/* Número de Carateres da Fonte do Texto */

/* Portos da Placa de Som FM AdLib */
#define ADL_REG		0x388	/* Porto dos Registos/Status na Adlib */
#define ADL_DAT		0x389 	/* Porto dos Dados na Adlib           */

/* Portos da Placa de Som FM Sound Blaster Pro */
#define SBP_REG		0x220	/* Porto Base dos Registos/Status na SB PRO */
#define SBP_DAT		0x221 	/* Porto Base dos Dados na SB PRO           */

/* Registos da Placa de Som FM */
#define FM_MIN_REG 0x01		/* Primeiro Registo */
#define FM_MAX_REG 0xF5		/* Último Registo   */

/* Registos dos Canais FM */
#define FM_CNL_0 0x20		/* Canal 1 */
#define FM_CNL_1 0x21		/* Canal 2 */
#define FM_CNL_2 0x22		/* Canal 3 */
#define FM_CNL_3 0x28		/* Canal 4 */
#define FM_CNL_4 0x29		/* Canal 5 */
#define FM_CNL_5 0x2A		/* Canal 6 */
#define FM_CNL_6 0x30		/* Canal 7 */
#define FM_CNL_7 0x31		/* Canal 8 */
#define FM_CNL_8 0x32		/* Canal 9 */

/* Frequência das Notas FM */
#define FM_V	0		/* Sem Nota */
#define FM_C	262		/* Dó */
#define FM_Cs	278		/* Dó Sustenido */
#define FM_D	294		/* Ré */
#define FM_Ds	312		/* Ré Sustenido */
#define FM_E	330		/* Mi */
#define FM_F	350		/* Fá */
#define FM_Fs	370		/* Fá Sustenido */
#define FM_G	392		/* Sol */
#define FM_Gs	416		/* Sol Sustenido */
#define FM_A	441		/* Lá */
#define FM_As	467		/* Lá Sustenido */
#define FM_B	494		/* Si */

#define MUSTEMPO 7			/* Tempo da Música */

#define SB_ADR		0x220		 /* Porto Base da Placa de Som */
#define DSP_CMD		SB_ADR+0x0C	 /* Porto dos Comandos do DSP  */
#define DSP_DAT		SB_ADR+0x0A  /* Porto dos Dados do DSP     */
#define DSP_RST		SB_ADR+0x06  /* Porto do Reset do DSP      */
#define DSP_BUF		SB_ADR+0x0E  /* Porto do Reset do DSP      */

/* Teclado - Interrupt */
#define KB_ESCAPE 1
#define KB_Q 16
#define KB_A 30
#define KB_O 24
#define KB_P 25
#define KB_SPACE 57
#define KB_LFT_ALT 56
#define KB_RETURN 28
#define KB_UP 72
#define KB_DOWN 80
#define KB_LEFT 75
#define KB_RIGHT 77

/* Teclado - kbhit */
#define KB_0 48
#define KB_1 49
#define KB_2 50
#define KB_3 51


/* My Prototypes */
void openscreen(void);
void closescreen(void);
void setupsom(void);
void setupkey(void);

int inicializa(void);
void mainloop(void);

void titulo(void);
void mainmenu(void);
void instrucoes1(void);
void instrucoes2(void);
void hiscore(void);

void initvar(void);
void desenhapainel(void);
void gameloop(void);
int vercriaini(int wcnt);

void gameover(void);
void welldone(void);

void clearsprites(void);
void printsprites(void);
void clearscreen(unsigned char databuf[]);

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

void criaplaneta(void);
void moveplaneta(void);
void apagaplaneta(void);

void criastar(void);
void movestar(void);
void putstar(int x,int y,unsigned char c,unsigned char databuf[]);
void clearstar(int x,int y,unsigned char databuf[]);

void criastar3d(void);
void movestar3d(void);
void putstar3d(int x,int y,unsigned char c);
void clearstar3d(int x,int y);

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
int lemusicafm(void);
void carregapatfm(void);
void playmusicafm(void);

/* AdLib */
void resetfm(void);
void initfm(void);
void writefm(int reg,int value);
int readfm(void);
void criasomfm(int canalg,int canalo,int freqindex);
void criasomfm2(int canalg,int canalo,int freqindex,int somindex);
void stopsomfm(int canalg);

/* Sound Blaster Pro */
void resetsb(void);
void initsb(void);
void writelsb(int reg,int value);
void writersb(int reg,int value);
int readlsb(void);
int readrsb(void);
void criasomsb(int canalg,int canalo,int freqindex);
void criasomsb2(int canalg,int canalo,int freqindex,int somindex);
void stopsomsb(int canalg);

void somexplosao(int ntx);
void sombomba(void);
void somdisparo(void);
void sompremio(int i,int ntx);
void somboss(void);

/* Ficheiros e Tipos de Inimigos */
int letabsincos(void);
int criasprites(void);
void freememory(void);
void criatipoini(void);

/* Carrega as Attack Waves e a Sequência de Attack Waves */
int loadwaves(void);

/* Parte Gráfica */
int lepalette(void);
void setpalette(void);

int lefontetxt(void);
void putfonte(int x,int y,int tx,int ty,int car,unsigned char databuf[]);
void printtxt(int x,int y,int tx,int ty,unsigned char txt[]);

int lesprites(void);
void getsprite(int x,int y,int tx,int ty,unsigned char dataspr[],unsigned char databuf[]);
void putsprite(int x,int y,int tx,int ty,unsigned char dataspr[],unsigned char databuf[]);
void clrsprite(int x,int y,int tx,int ty,unsigned char databuf[]);
void putrect(int x,int y,int tx,int ty,unsigned char dataspr[],unsigned char databuf[]);
void clrrect(int x,int y,int tx,int ty,unsigned char databuf[]);
void vgacopy(unsigned char databuf[]);

void wait_for_retrace(void);

/* Teclado */
static void interrupt (*old_keyb_int)(void);
static void interrupt keyb_int(void);
void hook_keyb_int(void);
void unhook_keyb_int(void);
int ctrlbrk_handler(void);

void definesons(void);

/* DSP */
int resetdsp(void);
void writedsp(int value);
int readdsp(void);
void playsom(void);
int lewave(void);

/* My Variables */
/* Definição dos Sprites */
struct sprites
{
	int x;
	int y;
	int tx;
	int ty;
	unsigned char *data;
};

struct sprites SpriteIni[NUMINIS],SpriteNv[NUMNAVES];
struct sprites SpriteTiro[NUMTIROS],SpriteTiroIni[NUMTIROSINI];
struct sprites SpriteExplo[NUMEXPLOS];
struct sprites SpritePremio[NUMPREMIOS];
struct sprites SpritePlaneta[NUMPLANETAS];
struct sprites SpriteTitle;
struct sprites SpritePainel;

int inimigos;
int tipini;
int xpos,ypos,rfact;
int tiros,ratetiro,rtiro;
int tirosini,ratetiroini,rtini;
int explosoes;
int premios,premiocnt;
int planetas,numplaneta;

int nx,ny,ntiro;
int nox,noy;
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

/* Parte Gráfica */
int regvga=0x13;
int regtxt=0x03;
int vgamem=0xA000;

/* Valores da Palette */
unsigned char pal[256][3];

/* Fonte de Texto */
unsigned char *fonte;

/* Double Buffer para o Scroll */
unsigned char *dblbuf;

time_t time1,time2;

/* Música e Som */
/* Tipo de Placa de Som */
int cardtype;

/* Instrumentos FM */
unsigned char octinstfm[31];
unsigned char sifm;

/* Patterns FM */
unsigned char position;
unsigned char pattern,py;
unsigned char row;
unsigned char oitavafm;
unsigned char freqfm;
unsigned char volfm;
unsigned char *patinfofm;

/* Informação das Rows FM*/
unsigned char fmefectnum[64][9];
unsigned char fmfreq[64][9];
unsigned char fmoct[64][9];
unsigned char fmefectpar[64][9];
unsigned char fmsamplenum[64][9];

/* Música FM */
unsigned char songpos[128];
int playfmstart;

short notasfm[13]={FM_V,FM_C,FM_Cs,FM_D,FM_Ds,FM_E,FM_F,FM_Fs,FM_G,FM_Gs,FM_A,FM_As,FM_B};
short canaisfm[9]={FM_CNL_0,FM_CNL_1,FM_CNL_2,FM_CNL_3,FM_CNL_4,FM_CNL_5,FM_CNL_6,FM_CNL_7,FM_CNL_8};

/* Manipulação de bits */
unsigned char hi,lo;

/* Teclado */
unsigned char teclas[0x60];
int KB_code=0;
int inputtype=0;

/* Ficheiros */
FILE *fp;

/* DSP */
unsigned char *digidata;
long numsamples;
long frequencia;

/* Cheat */
unsigned char nilives;
unsigned char unlives;

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
	int ox,oy;
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
	int ox,oy;
	int tx,ty;
	int tipo;
};

/* Definição dos Tiros Inimigos */
struct stirosini
{
	int x,y;
	int ox,oy;
	int tx,ty;
	int tipo;
};

/* Definição das Explosões */
struct sexplos
{
	int x,y;
	int ox,oy;
	int tx,ty;
	int fase;
	int tempo;
};

/* Definição dos Prémios */
struct spremios
{
	int x,y;
	int ox,oy;
	int tx,ty;
	int tipo;
	int tempo;
	int cnt;
};

/* Definição dos Planetas */
struct splanetas
{
	int x,y;
	int ox,oy;
	int tx,ty;
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

/* Definição das Estrelas */
struct stars
{
	unsigned char ox,oy;
	unsigned char x,y;
	unsigned char c;
	unsigned char s;
	unsigned char s2;
};

/* Definição das Estrelas 3D */
struct stars3d
{
	int osx,osy;
	int sx,sy;
	int x,y,z;
	unsigned char c;
};

/* Definição dos Registos para cada Instrumento FM */
struct instregs
{
	char nome[20];
	unsigned char num;
	unsigned char regc0;
	unsigned char op1reg2;
	unsigned char op1reg4;
	unsigned char op1reg6;
	unsigned char op1reg8;
	unsigned char op1rege;
	unsigned char op2reg2;
	unsigned char op2reg4;
	unsigned char op2reg6;
	unsigned char op2reg8;
	unsigned char op2rege;
};

/* Definição do Cabeçalho da Música FM */
struct cabfilesfm
{
	char nome[20];
	unsigned char songlen;
	unsigned char maxpat;
};

/* Cabeçalho do Ficheiro WAVE */
struct wavecabs
{
  long         RIFF;
  char         NI1[4];
  long         WAVE;
  long         fmt;
  char         NI2[6];
  unsigned int Channels;
  long         Frequency;
  char         NI3[6];
  unsigned int BitRes;
  long         data;
  long         datasize;
};

struct tipoinis tipoini[NUMINIS];

struct inis ini[MAXINI];
struct stiros tiro[MAXTIRO];
struct stirosini tiroini[MAXTIROINI];
struct sexplos explo[MAXEXPLO];
struct spremios premio[MAXPREMIO];
struct splanetas planeta;

struct twaves twave[NUMWAVES];

struct stars star[NUMSTAR];
struct stars3d star3d[NUMSTAR3D];

struct instregs instreg[31];
struct cabfilesfm cabfilefm;

struct instregs instregsons[4];

struct wavecabs wavecab;


/* Main */
int main(int argc, char *argv[])
{


	if(argc==2 && (strcmp(argv[1],"belenensesrules")==0))
	{
		nilives=1;
		unlives=0;
	}
	
	if(argc==2 && (strcmp(argv[1],"thomasdegendtistheman")==0))
	{
		nilives=0;
		unlives=1;
	}

	setupsom();
	setupkey();
	
	if (inicializa()!=0)
		return(1);
	
	openscreen();
	
    ctrlbrk(ctrlbrk_handler);
    hook_keyb_int();
	
	setpalette();
	
	mainloop();
				
	unhook_keyb_int();
				
	freememory();
			
	closescreen();

	return(0);
	
}

/* Abre o Modo Gráfico VGA: 320x200x256 */
void openscreen(void)
{
	
	/* Requere um 386 */
	asm .386
	
	/* VGA */
	asm{
		mov ax,regvga
		int 0x10
	}
	
}

/* Volta ao Modo de Texto */
void closescreen(void)
{
	
	if (cardtype==1 || cardtype==2) resetfm(); /* Adlib, Sound Blaster */
	if (cardtype==3) resetsb();	/* Sound Blaster PRO */
	
	/* Para o DMA */
	if (cardtype==2 || cardtype==2) writedsp (0xD0); /* Sound Blaster, Sound Blaster PRO */
	
	/* Text Mode */
	asm{
		mov ax,regtxt
		int 0x10
	}
	
}

/* Sound Card Setup */
void setupsom(void)
{
	
	int setsts;

	/* Text Mode */	
	asm{
		mov ax,regtxt
		int 0x10
	}
	
	_setcursortype(_NOCURSOR);

	textcolor(4);
	gotoxy(22,2);cprintf("----------------------------------");
	textcolor(15);
	gotoxy(22,3);cprintf("Penisoft Presents: SARDONIC MS-DOS");
	textcolor(4);
	gotoxy(22,4);cprintf("----------------------------------");
	
	textcolor(14);
	gotoxy(25,6);cprintf("Please Select your Sound Card:");
	
	textcolor(11);
	gotoxy(30,8);cprintf("0 - No Sound");
	gotoxy(30,9);cprintf("1 - AdLib");
	gotoxy(30,10);cprintf("2 - Sound Blaster");
	gotoxy(30,11);cprintf("3 - Sound Blaster Pro");
	
	textcolor(10);
	gotoxy(19,14);cprintf("Sound Blaster and Sound Blaster Pro should");
	gotoxy(20,15);cprintf("be configured at Port 220h, IRQ 7, DMA 1");
	
	textcolor(13);
	gotoxy(25,18);cprintf("Original Music by Frederic Hahn");
	gotoxy(18,20);cprintf("Music Convertion and Music Routines by MadAxe");
	
	textcolor(15);
	gotoxy(28,24);cprintf("Copyright 2020 Penisoft");
	
	setsts=0;
	do
	{
		KB_code=getch();
		if (KB_code>=KB_0 && KB_code<=KB_3) setsts=1;
	}
	while(!setsts);
	
	cardtype=KB_code-48;
	
	/* Text Mode */	
	asm{
		mov ax,regtxt
		int 0x10
	}
	
}

/* Keyboard Setup */
void setupkey(void)
{
	
	int setsts;

	/* Text Mode */	
	asm{
		mov ax,regtxt
		int 0x10
	}
	
	_setcursortype(_NOCURSOR);

	textcolor(4);
	gotoxy(22,2);cprintf("----------------------------------");
	textcolor(15);
	gotoxy(22,3);cprintf("Penisoft Presents: SARDONIC MS-DOS");
	textcolor(4);
	gotoxy(22,4);cprintf("----------------------------------");
	
	textcolor(14);
	gotoxy(22,7);cprintf("Please Select your Control Scheme:");
	
	textcolor(11);
	gotoxy(27,10);cprintf("0 - CURSORS - Directions");
	gotoxy(27,11);cprintf("    Space - Fire");
	gotoxy(27,12);cprintf("    Left ALT - Bomb");
	
	gotoxy(27,16);cprintf("1 - Q A O P - Directions");
	gotoxy(27,17);cprintf("    Space - Fire");
	gotoxy(27,18);cprintf("    Left ALT - Bomb");
	
	textcolor(15);
	gotoxy(28,24);cprintf("Copyright 2020 Penisoft");
	
	setsts=0;
	do
	{
		KB_code=getch();
		if (KB_code>=KB_0 && KB_code<=KB_1) setsts=1;
	}
	while(!setsts);
	
	inputtype=KB_code-48;
	
	/* Text Mode */	
	asm{
		mov ax,regtxt
		int 0x10
	}
	
}

/* Inicializa */
int inicializa(void)
{
	
	if (letabsincos()!=0)
		return(1);
	
	if (loadwaves()!=0)
		return(1);
	
	if (lepalette()!=0)
		return(1);
	
	if (lefontetxt()!=0)
		return(1);
			
	if (lesprites()!=0)
		return(1);

	if (criasprites()!=0)
		return(2);
	
	if (lemusicafm()!=0)
		return(2);
	
	if (lewave()!=0)
		return(2);
	
	recorde=0;
	estado=9;
	
	criatipoini();
	
	criastar3d();
	
	/* Reset Som FM */
	if (cardtype==1 || cardtype==2) /* AdLib, Sound Blaster */
	{
		resetfm();
		initfm();
	}
	if (cardtype==3)			/* Sound Blaster PRO */
	{
		resetsb();
		initsb();
	}

	/* Reset DSP */
	if (cardtype==2 || cardtype==3) /* Sound Blaster, Sound Blaster PRO */
	{
		if (resetdsp()!=0) return(2);
	}
	
	inicializamusica();
	
	definesons();
	
	return(0);

}

/* Loop Principal */
void mainloop(void)
{

	while (estado!=10)
	{
		switch (estado)
		{
			case 0:mainmenu();break;
			case 1:instrucoes1();break;
			case 8:instrucoes2();break;
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
	
	clearscreen(dblbuf);
	
	putrect(66,4,SpriteTitle.tx,SpriteTitle.ty,SpriteTitle.data,dblbuf);

	playfmstart=0;
	estado=0;

}

/* Menu Principal - Estado=0 */
void mainmenu()
{

	int i;

	clrrect(0,22,320,178,dblbuf);
	
	time1=time(NULL);
	
	if (!inputtype)
		printtxt(80,36,TXTX,TYTX,"CURSORS - DIRECTIONS\0");
	else
		printtxt(80,36,TXTX,TYTX,"Q A O P - DIRECTIONS\0");
	printtxt(112,52,TXTX,TYTX,"SPACE - FIRE\0");
	printtxt(100,68,TXTX,TYTX,"LEFT ALT - BOMB\0");
			
	printtxt(108,100,TXTX,TYTX,"FIRE TO START\0");
	printtxt(104,116,TXTX,TYTX,"ESCAPE TO QUIT\0");
	
	printtxt(60,148,TXTX,TYTX,"CODE AND GRAPHICS - MADAXE\0");
	printtxt(80,164,TXTX,TYTX,"MUSIC - FREDERIC HAHN\0");
	
	printtxt(72,188,TXTX,TYTX,"COPYRIGHT 2020 PENISOFT\0");
	
	vgacopy(dblbuf);
	
	while (estado==0)
	{
		
		wait_for_retrace();
		movestar3d();

		if (cardtype>0)
		{
			playfmstart++;
			if (playfmstart>MUSTEMPO) playmusicafm();
		}
				
		time2=time(NULL);
		if (time2>time1+MAINTEMPO) estado=1;
		
		if (teclas[KB_SPACE]) estado=3;
		if (teclas[KB_ESCAPE]) estado=10;
		
	}

}

/* Instruções 1 - Inimigos - Estado=1 */
void instrucoes1(void)
{
	
	clrrect(0,22,320,178,dblbuf);

	time1=time(NULL);
		
	/* Inimigos */
	putsprite(59,48,SpriteIni[0].tx,SpriteIni[0].ty,SpriteIni[0].data,dblbuf);
	printtxt(88,50,TXTX,TYTX,"SCOUT      -  5 POINTS\0");
	
	putsprite(57,68,SpriteIni[6].tx,SpriteIni[6].ty,SpriteIni[6].data,dblbuf);
	printtxt(88,72,TXTX,TYTX,"FIGHTER I  - 10 POINTS\0");
	
	putsprite(56,90,SpriteIni[7].tx,SpriteIni[7].ty,SpriteIni[7].data,dblbuf);
	printtxt(88,94,TXTX,TYTX,"FIGHTER II - 20 POINTS\0");
	
	putsprite(57,112,SpriteIni[8].tx,SpriteIni[8].ty,SpriteIni[8].data,dblbuf);
	printtxt(88,120,TXTX,TYTX,"STEALTH    - 30 POINTS\0");
	
	putsprite(57,140,SpriteIni[9].tx,SpriteIni[9].ty,SpriteIni[9].data,dblbuf);
	printtxt(88,148,TXTX,TYTX,"BOMBER     - 50 POINTS\0");
	
	vgacopy(dblbuf);
		
	while (estado==1)
	{
		
		wait_for_retrace();
		movestar3d();
		
		if (cardtype>0)
		{
			playfmstart++;
			if (playfmstart>MUSTEMPO) playmusicafm();
		}
		
		time2=time(NULL);
		if (time2>time1+MAINTEMPO) estado=8;
		
		if (teclas[KB_SPACE]) estado=3;
		if (teclas[KB_ESCAPE]) estado=10;
		
	}

}

/* Instruções 2 - Prémios - Estado=8 */
void instrucoes2(void)
{
	
	clrrect(0,22,320,178,dblbuf);

	time1=time(NULL);
		
	/* Prémios */
	putsprite(108,38,SpritePremio[0].tx,SpritePremio[0].ty,SpritePremio[0].data,dblbuf);
	printtxt(124,40,TXTX,TYTX,"EXTRA LIVE\0");
	
	putsprite(108,60,SpritePremio[1].tx,SpritePremio[1].ty,SpritePremio[1].data,dblbuf);
	printtxt(124,62,TXTX,TYTX,"EXTRA FIRE\0");
	
	putsprite(108,82,SpritePremio[2].tx,SpritePremio[2].ty,SpritePremio[2].data,dblbuf);
	printtxt(124,84,TXTX,TYTX,"EXTRA BOMB\0");
		
	putsprite(108,104,SpritePremio[6].tx,SpritePremio[6].ty,SpritePremio[6].data,dblbuf);
	printtxt(124,106,TXTX,TYTX,"EXTRA RATE\0");
		
	putsprite(108,126,SpritePremio[5].tx,SpritePremio[5].ty,SpritePremio[5].data,dblbuf);
	printtxt(124,128,TXTX,TYTX,"EXTRA SPEED\0");
		
	putsprite(108,148,SpritePremio[3].tx,SpritePremio[3].ty,SpritePremio[3].data,dblbuf);
	printtxt(124,150,TXTX,TYTX,"EXTRA POINTS\0");
	
	putsprite(108,170,SpritePremio[4].tx,SpritePremio[4].ty,SpritePremio[4].data,dblbuf);
	printtxt(124,172,TXTX,TYTX,"EXTRA ARMOUR\0");
					
	vgacopy(dblbuf);
		
	while (estado==8)
	{
		
		wait_for_retrace();
		movestar3d();
		
		if (cardtype>0)
		{
			playfmstart++;
			if (playfmstart>MUSTEMPO) playmusicafm();
		}
		
		time2=time(NULL);
		if (time2>time1+MAINTEMPO) estado=2;
		
		if (teclas[KB_SPACE]) estado=3;
		if (teclas[KB_ESCAPE]) estado=10;
		
	}

}

/* HiScore - Estado=2 */
void hiscore(void)
{
	
	char txrec[6];
	
	clrrect(0,22,320,178,dblbuf);

	time1=time(NULL);
		
	printtxt(88,74,TXTX,TYTX,"HISCORE OF THE DAY\0");
	
	sprintf(txrec,"%05d\0",recorde);
	printtxt(136,98,TXTX,TYTX,txrec);
	
	vgacopy(dblbuf);
		
	while (estado==2)
	{
		
		wait_for_retrace();
		movestar3d();
		
		if (cardtype>0)
		{
			playfmstart++;
			if (playfmstart>MUSTEMPO) playmusicafm();
		}
		
		time2=time(NULL);
		if (time2>time1+MAINTEMPO) estado=0;
		
		if (teclas[KB_SPACE]) estado=3;
		if (teclas[KB_ESCAPE]) estado=10;
	}

}

/* Inicializa as variáveis - Estado=3 */
void initvar(void)
{
	
	clearscreen(dblbuf);
	
	inimigos=0;
	
	tiros=0;
	rtiro=0;
	ratetiro=RTIROSL;
	
	tirosini=0;
	ratetiroini=0;
	rtini=RTINIPM;
	
	explosoes=0;
	premios=0;
	premiocnt=5;
	
	planetas=0;
	numplaneta=2;
	
	if (!nilives) vidas=5;
	else vidas=9;
	
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
	
	criastar();
	
	if (cardtype==1 || cardtype==2) /* AdLib, Sound Blaster */
	{
		resetfm();
		initfm();
	}
	if (cardtype==3) /* Sound Blaster PRO */
	{
		resetsb();
		initsb();
	}
	
	estado=4;
	
}

/* Desenha o Painel */
void desenhapainel(void)
{
	
	char txpnl[6];
	
	putrect(250,0,SpritePainel.tx,SpritePainel.ty,SpritePainel.data,dblbuf);
	
	/* Pontos */
	sprintf(txpnl,"%05d\0",pontos);
	printtxt(266,32,TXTX,TYTX,txpnl);
	
	/* Vidas */	
	sprintf(txpnl,"%d\0",vidas);
	printtxt(282,80,TXTX,TYTX,txpnl);
	
	/* Bombas */	
	sprintf(txpnl,"%d\0",bombas);
	printtxt(282,128,TXTX,TYTX,txpnl);
	
	/* Nível */	
	sprintf(txpnl,"%d\0",nivel);
	printtxt(266+(8*(5-nivel)),176,TXTX,TYTX,txpnl);
	
}

/* Rotina Principal do Jogo - Estado=4 */
void gameloop(void)
{

	counter=0; /* Inicializa o Contador do Jogo */
	criaplaneta();
	
	do
	{
		wcnt=wave[counter];	/* Vai buscar a respetiva Attack Wave à Sequência de Attack Waves */
		inimigos=0;
		wcnt2=0;
		tpini=0;
		
		while (vercriaini(wcnt)==0 && estado==4)
		{
			
			wait_for_retrace();
			vgacopy(dblbuf);

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
			
			if (planetas) moveplaneta();
			
			if (ninvenc>0) ninvenc--;
			movenave();
			
			movestar();
		
			printsprites();

			/* Quit */
			if (teclas[KB_ESCAPE]) estado=6;
				
		}
			
		counter++;
		
		/* Cria Planetas */
		if (!(counter%10) && !planetas) criaplaneta();
		
		/* Modifica o Fire Rate dos Inimigos nos Bosses dos Finais de Nível */
		if (counter==49 || counter==99 || counter==149 || counter==199 || counter==254)
		{
			somboss();
			rtini=RTINIBS;
		}
		
		/* Modifica o Fire Rate dos Inimigos nos Bosses Intermédios do Último Nível */
		if (counter==209 || counter==219 || counter==229 || counter==239)
		{
			somboss();
			rtini=RTINIBS;
		}
		
		/* Modifica o Fire Rate dos Inimigos depois dos Bosses Intermédios do Último Nível */
		if (counter==210 || counter==220 || counter==230 || counter==240) rtini=RTINIPM;
		
						
	} while (counter<MAXWAVE && estado==4); /* Prossegue até WellDone, GameOver ou Exit */
	
	/* WellDone */
	if (counter>=MAXWAVE) estado=7;
	
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
	
	clearscreen(dblbuf);
	
	putrect(66,4,SpriteTitle.tx,SpriteTitle.ty,SpriteTitle.data,dblbuf);
	
	inicializamusica();
	time1=time(NULL);
		
	printtxt(112,64,TXTX,TYTX,"GAME OVER !!\0");
		
	if (pontos>recorde)
	{
		recorde=pontos;
		printtxt(92,104,TXTX,TYTX,"BUT YOU ACHIEVED\0");
		printtxt(96,120,TXTX,TYTX,"AN HISCORE YES!\0");
	}
	else
	{
		printtxt(80,104,TXTX,TYTX,"NO HISCORE ACHIEVED\0");
		printtxt(96,120,TXTX,TYTX,"MAYBE NEXT TIME\0");
	}
	
	printtxt(56,188,TXTX,TYTX,"PRESS RETURN TO MAIN MENU\0");
	
	vgacopy(dblbuf);
		
	while (estado==6)
	{
		
		wait_for_retrace();
		movestar3d();
		
		if (cardtype>0)
		{
			playfmstart++;
			if (playfmstart>MUSTEMPO) playmusicafm();
		}
		
		time2=time(NULL);
		if (time2>time1+MAINTEMPO*2) estado=0;

		if (teclas[KB_RETURN]) estado=0;
		
	}
	
}

/* WellDone - Estado=7 */
void welldone(void)
{
	
	clearscreen(dblbuf);
	
	putrect(66,4,SpriteTitle.tx,SpriteTitle.ty,SpriteTitle.data,dblbuf);
	
	inicializamusica();
	time1=time(NULL);
		
	printtxt(104,48,TXTX,TYTX,"WELL DONE !!!\0");
	printtxt(72,80,TXTX,TYTX,"YOU DEFEATED THE EVIL\0");
	printtxt(72,96,TXTX,TYTX,"SARDONIC AND ITS ARMY\0");
	
	printtxt(72,128,TXTX,TYTX,"THANK YOU FOR PLAYING\0");
	printtxt(92,144,TXTX,TYTX,"THIS LITTLE GAME\0");
	
	printtxt(56,188,TXTX,TYTX,"PRESS RETURN TO MAIN MENU\0");
	
	vgacopy(dblbuf);
	
	if (pontos>recorde) recorde=pontos;
		
	while (estado==7)
	{
		
		wait_for_retrace();
		movestar3d();

		if (cardtype>0)
		{		
			playfmstart++;
			if (playfmstart>MUSTEMPO) playmusicafm();
		}
		
		time2=time(NULL);
		if (time2>time1+MAINTEMPO*2) estado=0;
		
		if (teclas[KB_RETURN]) estado=0;
		
	}
	
}

/* Apaga os Sprites do écran */
void clearsprites()
{
	
	int i;
	
	/* Planetas */
	if (planetas)
		clrsprite(planeta.ox,planeta.oy,planeta.tx,planeta.ty,dblbuf);
	
	/* Inimigos */
	for (i=0; i<inimigos; i++)
		clrsprite(ini[i].ox,ini[i].oy,ini[i].tx,ini[i].ty,dblbuf);
		
	/* Disparos */
	for (i=0; i<tiros; i++)
		clrsprite(tiro[i].ox,tiro[i].oy,tiro[i].tx,tiro[i].ty,dblbuf);
		
	/* Disparos Inimigos */
	for (i=0; i<tirosini; i++)
		clrsprite(tiroini[i].ox,tiroini[i].oy,tiroini[i].tx,tiroini[i].ty,dblbuf);
		
	/* Nave */
	clrsprite(nox,noy,ntx,nty,dblbuf);
	
	/* Explosões */
	for (i=0; i<explosoes; i++)
		clrsprite(explo[i].ox,explo[i].oy,explo[i].tx,explo[i].ty,dblbuf);
	
	/* Prémios */
	for (i=0; i<premios; i++)
		clrsprite(premio[i].ox,premio[i].oy,premio[i].tx,premio[i].ty,dblbuf);
	
}

/* Desenha os Sprites no écran */
void printsprites()
{
	int i;
	
	/* Planetas */
	if (planetas)
	{
		planeta.ox=planeta.x;
		planeta.oy=planeta.y;
		putsprite(planeta.x,planeta.y,planeta.tx,planeta.ty,SpritePlaneta[numplaneta].data,dblbuf);
	}
	
	/* Inimigos */
	for (i=0; i<inimigos; i++)
	{
		ini[i].ox=ini[i].x;
		ini[i].oy=ini[i].y;
		putsprite(ini[i].x,ini[i].y,ini[i].tx,ini[i].ty,SpriteIni[ini[i].tipo].data,dblbuf);
		
	}
	
	/* Tiros */
	for (i=0; i<tiros; i++)
	{
		tiro[i].ox=tiro[i].x;
		tiro[i].oy=tiro[i].y;
		
	//	if (tiro[i].tipo!=2)
			putsprite(tiro[i].x,tiro[i].y,tiro[i].tx,tiro[i].ty,SpriteTiro[tiro[i].tipo].data,dblbuf);

	}
	
	/* Tiros Inimigos */
	for (i=0; i<tirosini; i++)
	{
		tiroini[i].ox=tiroini[i].x;
		tiroini[i].oy=tiroini[i].y;
		putsprite(tiroini[i].x,tiroini[i].y,tiroini[i].tx,tiroini[i].ty,SpriteTiroIni[tiroini[i].tipo].data,dblbuf);
	}
	
	/* Nave */
	nox=nx;
	noy=ny;
	putsprite(nx,ny,ntx,nty,SpriteNv[ninvenc&1].data,dblbuf);
	
	/* Explosões */
	for (i=0; i<explosoes; i++)
	{
		explo[i].ox=explo[i].x;
		explo[i].oy=explo[i].y;
		putsprite(explo[i].x,explo[i].y,explo[i].tx,explo[i].ty,SpriteExplo[explo[i].fase].data,dblbuf);
	}
	
	/* Prémios */
	for (i=0; i<premios; i++)
	{
		premio[i].ox=premio[i].x;
		premio[i].oy=premio[i].y;
		putsprite(premio[i].x,premio[i].y,premio[i].tx,premio[i].ty,SpritePremio[premio[i].tipo].data,dblbuf);
	}
	
}

/* Apaga o Écran */
void clearscreen(unsigned char databuf[])
{

	asm{
		push ds
		
		mov ax,ds
		mov es,ax

		xor ax,ax
	
		mov cx,64000
		les di,[databuf]
	
		cld	
		rep stosb
		
		pop ds
	}

}

/* Movimenta a Nave */
void movenave()
{
	
	if (!inputtype) /* Keyboard : CURSORS - Directions */
	{
		/* Cima */
		if(teclas[KB_UP])
			if (ny>=nspeed) ny-=nspeed;

		/* Baixo */
		if(teclas[KB_DOWN])
			if (ny<=MAXY-(nty+nspeed)) ny+=nspeed;

		/* Esquerda */
		if(teclas[KB_LEFT])
			if (nx>=nspeed) nx-=nspeed;

		/* Direita */
		if(teclas[KB_RIGHT])
			if (nx<=MAXX-(ntx+nspeed)) nx+=nspeed;	
	}
	else /* Keyboard : Q A O P - Directions */
	{
		/* Cima */
		if(teclas[KB_Q])
			if (ny>=nspeed) ny-=nspeed;

		/* Baixo */
		if(teclas[KB_A])
			if (ny<=MAXY-(nty+nspeed)) ny+=nspeed;

		/* Esquerda */
		if(teclas[KB_O])
			if (nx>=nspeed) nx-=nspeed;

		/* Direita */
		if(teclas[KB_P])
			if (nx<=MAXX-(ntx+nspeed)) nx+=nspeed;
	}

	/* Disparo */
	if(teclas[KB_SPACE])
		if (ratetiro==0)
			if (ntiro==0) criadisparo(nx+8,ny-8,0);
			else criadisparo(nx+3,ny-6,1);
				
	/* Bomba */
	if (ratebomba==0 && bombas>0 && inimigos>0 && teclas[KB_LFT_ALT])
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
						somexplosao(ex);
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
						somexplosao(ex);
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
				somexplosao(ex);
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
					ex=ini[i].x;
					ganhapontos(5);
					i++;
					somexplosao(ex);
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
				case 6:rtiro=1;break;
			}
			sompremio(premio[i].tipo,premio[i].x);
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
	rtiro=0;
	ex=nx;
	ey=ny;
	criaexplosao(ex,ey);
	somexplosao(ex);
				
	if (!unlives) vidas--;
	
	sprintf(txvid, "%d\0",vidas);
	printtxt(282,80,TXTX,TYTX,txvid);
	
	if (vidas==0) estado=6;
	
}

/* Ganha Vida */
void ganhavida(void)
{
	
	char txvid[2];

	if (vidas<MAXVIDAS)
	{
		vidas++;
		sprintf(txvid, "%d\0",vidas);
		printtxt(282,80,TXTX,TYTX,txvid);
	}
	
}

/* Ganha Bomba */
void ganhabomba(void)
{

	char txbmb[2];

	if (bombas<MAXBOMBAS)
	{
		bombas++;
		sprintf(txbmb, "%d\0",bombas);
		printtxt(282,128,TXTX,TYTX,txbmb);
	}
	
}

/* Perde Bomba */
void perdebomba(void)
{

	char txbmb[2];

	sprintf(txbmb, "%d\0",bombas);
	printtxt(282,128,TXTX,TYTX,txbmb);
	
}

/* Ganha Pontos */
void ganhapontos(int pts)
{
	
	char txpts[6];
	
	pontos+=pts;
	
	sprintf(txpts, "%05d\0",pontos);
	printtxt(266,32,TXTX,TYTX,txpts);
	
}

/* Muda de Nível */
void mudanivel(void)
{
	
	char txnvl[3]; 

	if (nivel<5)
	{
		ganhavida();
		ganhabomba();
		ganhapontos(nivel*100);
		nivel++;
		desenhapainel();
		sprintf(txnvl, "%d \0",nivel);
		printtxt(266+(8*(5-nivel)),176,TXTX,TYTX,txnvl);
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
		tiro[tiros].tx=1+ntp*9;
		tiro[tiros].ty=8;
		tiro[tiros].tipo=ntp;
		tiros++;
		if (rtiro==0) ratetiro=RTIROSL;
		else ratetiro=RTIROFS;
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
	
	for (k=i; k<tiros; k++)
	{
		tiro[k].x=tiro[k+1].x;
		tiro[k].y=tiro[k+1].y;
		tiro[k].ox=tiro[k+1].ox;
		tiro[k].oy=tiro[k+1].oy;
		tiro[k].tx=tiro[k+1].tx;
		tiro[k].ty=tiro[k+1].ty;
		tiro[k].tipo=tiro[k+1].tipo;
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
	
	for (k=i; k<tirosini; k++)
	{
		tiroini[k].x=tiroini[k+1].x;
		tiroini[k].y=tiroini[k+1].y;
		tiroini[k].ox=tiroini[k+1].ox;
		tiroini[k].oy=tiroini[k+1].oy;
		tiroini[k].tx=tiroini[k+1].tx;
		tiroini[k].ty=tiroini[k+1].ty;
		tiroini[k].tipo=tiroini[k+1].tipo;
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
	
	for (k=i; k<explosoes; k++)
	{
		explo[k].x=explo[k+1].x;
		explo[k].y=explo[k+1].y;
		explo[k].ox=explo[k+1].ox;
		explo[k].oy=explo[k+1].oy;
		explo[k].tx=explo[k+1].tx;
		explo[k].ty=explo[k+1].ty;
		explo[k].fase=explo[k+1].fase;
		explo[k].tempo=explo[k+1].tempo;
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
	
	if (vidas==9 && !rnd) rnd=3;
	if (bombas==9 && rnd==2) rnd=3;
	if (rtiro && rnd==6) rnd=3;
	if (ntiro && rnd) rnd=3;
	
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
	
	for (k=i; k<premios; k++)
	{
		premio[k].x=premio[k+1].x;
		premio[k].y=premio[k+1].y;
		premio[k].ox=premio[k+1].ox;
		premio[k].oy=premio[k+1].oy;
		premio[k].tx=premio[k+1].tx;
		premio[k].ty=premio[k+1].ty;
		premio[k].tipo=premio[k+1].tipo;
		premio[k].tempo=premio[k+1].tempo;
		premio[k].cnt=premio[k+1].cnt;
	}
	
	premios--;
	
}

/* Cria Planeta */
void criaplaneta(void)
{
	
	int rnd;
	
	rnd=(random(MAXX-50))+25;
	
	planeta.x=rnd;
	planeta.y=-SpritePlaneta[numplaneta].ty;
	planeta.tx=24;
	planeta.ty=24;
	planeta.cnt=3;

	planetas=1;
	
}

/* Move Planeta */
void moveplaneta(void)
{
	
	planeta.cnt--;
	if (planeta.cnt==0)
	{
		planeta.y++;
		planeta.cnt=3;
			
		if (planeta.y>=MAXY) apagaplaneta();
	}

}

/* Apaga Planeta */
void apagaplaneta(void)
{
	
	planetas=0;
	
	numplaneta++;
	if (numplaneta==NUMPLANETAS) numplaneta=0;
	
}

/* Cria o Star Field */
void criastar(void)
{

	int i,c,s;
	
	/* Star Field */
	for (i=0; i<NUMSTAR; i++)
	{
		if (i<10)
		{
			c=247;
			s=1;
		}
		if (i>9 && i<20)
		{
			c=245;
			s=2;
		}
		if (i>19)
		{
			c=14;
			s=3;
		}
	
		star[i].x=random(MAXX);
		star[i].y=random(MAXY);
		star[i].ox=star[i].x;
		star[i].oy=star[i].y;
		star[i].c=c;
		star[i].s=s;
		star[i].s2=s;
	}
	
}

/* Move o Star Field */
void movestar(void)
{

	int i;
	
	for (i=0; i<NUMSTAR; i++)
		clearstar(star[i].ox,star[i].oy,dblbuf);
	
	for (i=0; i<NUMSTAR; i++)
	{
		star[i].s--;
		if (star[i].s==0)
		{
			star[i].s=star[i].s2;
			star[i].y++;
			if (star[i].y>=MAXY) star[i].y=0;
			star[i].oy=star[i].y;
		}
	}
	
	for (i=0; i<NUMSTAR; i++)
		putstar(star[i].x,star[i].y,star[i].c,dblbuf);
			
}

/* Imprime o Star Field */
void putstar(int x,int y,unsigned char c,unsigned char databuf[])
{

	int comxy;
	
	comxy=y*MAXRESX+x;
	
	asm{
		push ds
		
		mov ax,ds
		mov es,ax

		les di,[databuf]
		add di,comxy
		mov al,c
		mov es:[di],al

		pop ds
	}
	
}

/* Apaga o Star Field */
void clearstar(int x,int y,unsigned char databuf[])
{

	int comxy;
	
	comxy=y*MAXRESX+x;
	
	asm{
		push ds
		
		mov ax,ds
		mov es,ax
		
		les di,[databuf]
		add di,comxy
		mov al,0
		mov es:[di],al

		pop ds
	}
	
}

/* Cria o Star Field 3D*/
void criastar3d(void)
{

	int i,c;

	/* Cria o Star Field 3D */
	for (i=0; i<NUMSTAR3D; i++)
	{
		if (i<15)
			c=247;

		if (i>14 && i<30)
			c=245;

		if (i>29)
			c=112;
	
		star3d[i].x=(rand()%300)-150;
		star3d[i].y=(rand()%199)-100;
		star3d[i].z=256;
	
		star3d[i].sx=((star3d[i].x*256)/star3d[i].z+150);
		star3d[i].sy=((star3d[i].y*256)/star3d[i].z+100);
		
		star3d[i].osx=star3d[i].sx;
		star3d[i].osy=star3d[i].sy;
		
		star3d[i].c=c;
	}
	
}

/* Move o Star Field 3D */
void movestar3d(void)
{

	int i;
	
	for (i=0; i<NUMSTAR3D; i++)
		clearstar3d(star3d[i].osx,star3d[i].osy);
	
	for (i=0; i<NUMSTAR3D; i++)
	{
		if(star3d[i].z<1)
		{
			star3d[i].x=(rand()%300)-150;
			star3d[i].y=(rand()%199)-100;
			star3d[i].z=256;
		}
		else star3d[i].z-=3;
		
		star3d[i].sx=((star3d[i].x*256)/star3d[i].z+150);
		star3d[i].sy=((star3d[i].y*256)/star3d[i].z+100);
		
		star3d[i].osx=star3d[i].sx;
		star3d[i].osy=star3d[i].sy;
	}
	
	for (i=0; i<NUMSTAR3D; i++)
	{
		if(star3d[i].sx>0 && star3d[i].sx<320 && star3d[i].sy>0 && star3d[i].sy<200)
			putstar3d(star3d[i].sx,star3d[i].sy,star3d[i].c);
		else
			star3d[i].z=0;
	}
			
}

/* Imprime o Star Field 3D */
void putstar3d(int x,int y,unsigned char c)
{

	int comxy;
	
	comxy=y*MAXRESX+x;
	
	asm{
		push ds
		
		mov ax,vgamem
		mov es,ax

		mov di,comxy
		
		mov al,es:[di]
		test al,al
		jnz loop1
		
		mov al,c
		mov es:[di],al

	}
loop1:
	asm{
		pop ds
	}
	
}

/* Apaga o Star Field 3D */
void clearstar3d(int x,int y)
{

	int comxy;
	
	comxy=y*MAXRESX+x;
	
	asm{
		push ds
		
		mov ax,vgamem
		mov es,ax
		
		mov di,comxy
		
		mov al,es:[di]
		cmp al,247
		jz loop2
		cmp al,245
		jz loop2
		cmp al,112
		jnz loop1
		
	}
loop2:
	asm{
		mov al,0
		mov es:[di],al
	}
loop1:
	asm{
		pop ds
	}
	
}

/* Cria Inimigo */
void criainimigo(int wcnt,int wcnt2)
{
	
	/* Inimigos */
	if (inimigos<MAXINI)
	{
		ini[inimigos].tipo=twave[wcnt].inis[wcnt2];
		tipini=ini[inimigos].tipo;
		if (twave[wcnt].xx[wcnt2]==255)
			ini[inimigos].x=250;
		else
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
	
	for (k=i; k<inimigos; k++)
	{
		ini[k].x=ini[k+1].x;
		ini[k].y=ini[k+1].y;
		ini[k].ox=ini[k+1].ox;
		ini[k].oy=ini[k+1].oy;
		ini[k].tx=ini[k+1].tx;
		ini[k].ty=ini[k+1].ty;
		ini[k].tipo=ini[k+1].tipo;
		ini[k].fpath=ini[k+1].fpath;
		ini[k].hull=ini[k+1].hull;
		ini[k].speed=ini[k+1].speed;
		ini[k].pontos=ini[k+1].pontos;
		ini[k].r=ini[k+1].r;
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
	
	if (ini[i].x>=MAXX) return(1);
	
	return(0);
	
}

/* 9 - Movimenta Horizontalmente o Inimigo para a Direita em Sinusoidal para Baixo */
int mvinihorzdirsindown(int i)
{
	
	ini[i].x+=ini[i].speed;
		
	ini[i].r++;
	if (ini[i].r>125) ini[i].r=0;
				
	ini[i].y+=(int)(tsincos[0][ini[i].r]*2);
	
	if (ini[i].x>=MAXX) return(1);
	
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
	
	if (ini[i].x>=MAXX) return(1);
	
	return(0);
		
}

/* 11 - Movimenta Horizontalmente o Inimigo para a Direita em Sinusoidal para Cima */
int mvinihorzdirsinup(int i)
{
	
	ini[i].x+=ini[i].speed;
		
	ini[i].r++;
	if (ini[i].r>125) ini[i].r=0;
			
	ini[i].y-=(int)(tsincos[0][ini[i].r]*2);
	
	if (ini[i].x>=MAXX) return(1);
	
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
	
	if (ini[i].x>=MAXX) return(1);
	
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
	
	if (ini[i].y>=MAXY || ini[i].x>=MAXX) return(1);
	
	return(0);
		
}

/* 19 - Movimenta Diagonalmente o Inimigo para a Direita e para Cima */
int mvinidiadirup(int i)
{
	
	ini[i].y-=ini[i].speed;
	ini[i].x+=ini[i].speed;
	
	if (ini[i].y<=-ini[i].ty || ini[i].x>=MAXX) return(1);
	
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

	if (cardtype==1 || cardtype==2) initfm();
	if (cardtype==3) initsb();
		

	/* Navegação nas Patterns */
	pattern=0;
	position=0;
	py=0;
	row=0;
	
	/* Navegação nos Instrumentos FM */
	sifm=0;
	
	/* Música */
	playfmstart=0;
	
	/* Carrega a Pattern com os Dados da Música */
	carregapatfm();
		
}

/* Cria o Som de uma Explosão */
void somexplosao(int ntx)
{
	
	volfm=instregsons[1].op2reg4;
	oitavafm=3;
	
	if (cardtype==1 || cardtype==2) criasomfm2(5,canaisfm[5],1,1); /* AdLib, Sound Blaster */
	
	if (cardtype==3)	/* Sound Blaster PRO */
		if (ntx>125) criasomsb2(5,canaisfm[5],1,1);
		else criasomsb2(6,canaisfm[6],1,1);
	
}

/* Cria o Som de um Bomba */
void sombomba(void)
{

	if (cardtype==1)	/* AdLib */
	{
		volfm=instregsons[1].op2reg4;
		oitavafm=3;
		criasomfm2(5,canaisfm[5],1,1);
		criasomfm2(6,canaisfm[6],1,1);
		criasomfm2(7,canaisfm[7],1,1);
		criasomfm2(8,canaisfm[8],1,1);
	}
	
	if (cardtype==2 || cardtype==3) playsom(); /* Sound Blaster, Sound Blaster PRO */
	
}

/* Cria o Som do Disparo */
void somdisparo(void)
{

	if (cardtype>0) /* AdLib, Sound Blaster, Sound Blaster PRO */
	{
		volfm=instregsons[0].op2reg4;
		oitavafm=4;
		criasomfm2(4,canaisfm[4],1,0);
	}
	
}

/* Cria o Som do Prémio */
void sompremio(int i,int ntx)
{
	
	volfm=instregsons[2].op2reg4;
	oitavafm=4;
	
	switch (i)
	{
		case 0:
		{
			if (cardtype==1 || cardtype==2) criasomfm2(6,canaisfm[6],1,2); /* AdLib, Sound Blaster */
			if (cardtype==3)	/* Sound Blaster PRO */
				if (ntx>125) criasomsb2(7,canaisfm[7],1,2);
				else criasomsb2(8,canaisfm[8],1,2);
			break;
		}
		case 1:
		{
			if (cardtype==1 || cardtype==2) criasomfm2(6,canaisfm[6],3,2); /* AdLib, Sound Blaster */
			if (cardtype==3)	/* Sound Blaster PRO */
				if (ntx>125) criasomsb2(7,canaisfm[7],3,2);
				else criasomsb2(8,canaisfm[8],3,2);
			break;
		}
		case 2:
		{
			if (cardtype==1 || cardtype==2) criasomfm2(6,canaisfm[6],5,2); /* AdLib, Sound Blaster */
			if (cardtype==3)	/* Sound Blaster PRO */
				if (ntx>125) criasomsb2(7,canaisfm[7],5,2);
				else criasomsb2(8,canaisfm[8],5,2);
			break;
		}
		case 3:
		{
			if (cardtype==1 || cardtype==2) criasomfm2(6,canaisfm[6],6,2); /* AdLib, Sound Blaster */
			if (cardtype==3)	/* Sound Blaster PRO */
				if (ntx>125) criasomsb2(7,canaisfm[7],6,2);
				else criasomsb2(8,canaisfm[8],6,2);
			break;
		}
		case 4:
		{
			if (cardtype==1 || cardtype==2) criasomfm2(6,canaisfm[6],8,2); /* AdLib, Sound Blaster */
			if (cardtype==3)	/* Sound Blaster PRO */
				if (ntx>125) criasomsb2(7,canaisfm[7],8,2);
				else criasomsb2(8,canaisfm[8],8,2);
			break;
		}
		case 5:
		{
			if (cardtype==1 || cardtype==2) criasomfm2(6,canaisfm[6],10,2); /* AdLib, Sound Blaster */
			if (cardtype==3)	/* Sound Blaster PRO */
				if (ntx>125) criasomsb2(7,canaisfm[7],10,2);
				else criasomsb2(8,canaisfm[8],10,2);
			break;
		}
		case 6:
		{
			if (cardtype==1 || cardtype==2) criasomfm2(6,canaisfm[6],12,2); /* AdLib, Sound Blaster */
			if (cardtype==3)	/* Sound Blaster PRO */
				if (ntx>125) criasomsb2(7,canaisfm[7],12,2);
				else criasomsb2(8,canaisfm[8],12,2);
			break;
		}
	}
	
	
}

/* Cria o Som do Boss */
void somboss(void)
{

	if (cardtype>0) /* AdLib, Sound Blaster, Sound Blaster PRO */
	{
		volfm=instregsons[3].op2reg4;
		oitavafm=4;
		criasomfm2(7,canaisfm[7],1,3);
	}
	
}

/* Lê Tabela de Senos e Cosenos */
int letabsincos(void)
{

	printf("Reading Sin and Cos Table File.\n");
	
	/* Lê a Tabela de Senos e Cosenos a partir de um Ficheiro */
	fp=fopen("data\\sincos.dat","rb");
	
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

/* Cria os Sprites a partir da Imagem Lida para o Buffer */
int criasprites(void)
{

	int i=0;
	
		
	/* Inimigos Pequenos : 0-5 */
	for (i=0; i<6; i++)
	{
		SpriteIni[i].x=112+(i*16);
		SpriteIni[i].y=32;
		SpriteIni[i].tx=12;
		SpriteIni[i].ty=12;
		SpriteIni[i].data=(char*)calloc(SpriteIni[i].tx*SpriteIni[i].ty,sizeof(char));
		getsprite(SpriteIni[i].x,SpriteIni[i].y,SpriteIni[i].tx,SpriteIni[i].ty,SpriteIni[i].data,dblbuf);
	}
		
	/*	Inimigo Fighter I : 6 */
	i=6;
	SpriteIni[i].x=0;
	SpriteIni[i].y=0;
	SpriteIni[i].tx=15;
	SpriteIni[i].ty=16;
	SpriteIni[i].data=(char*)calloc(SpriteIni[i].tx*SpriteIni[i].ty,sizeof(char));
	getsprite(SpriteIni[i].x,SpriteIni[i].y,SpriteIni[i].tx,SpriteIni[i].ty,SpriteIni[i].data,dblbuf);
		
	/*	Inimigo Fighter II : 7 */		
	i=7;
	SpriteIni[i].x=16;
	SpriteIni[i].y=0;
	SpriteIni[i].tx=16;
	SpriteIni[i].ty=15;
	SpriteIni[i].data=(char*)calloc(SpriteIni[i].tx*SpriteIni[i].ty,sizeof(char));
	getsprite(SpriteIni[i].x,SpriteIni[i].y,SpriteIni[i].tx,SpriteIni[i].ty,SpriteIni[i].data,dblbuf);
		
	/*	Inimigo Stealth : 8 */
	i=8;
	SpriteIni[i].x=32;
	SpriteIni[i].y=0;
	SpriteIni[i].tx=15;
	SpriteIni[i].ty=24;
	SpriteIni[i].data=(char*)calloc(SpriteIni[i].tx*SpriteIni[i].ty,sizeof(char));
	getsprite(SpriteIni[i].x,SpriteIni[i].y,SpriteIni[i].tx,SpriteIni[i].ty,SpriteIni[i].data,dblbuf);
		
	/*	Inimigo Bomber : 9 */
	i=9;
	SpriteIni[i].x=48;
	SpriteIni[i].y=0;
	SpriteIni[i].tx=15;
	SpriteIni[i].ty=23;
	SpriteIni[i].data=(char*)calloc(SpriteIni[i].tx*SpriteIni[i].ty,sizeof(char));
	getsprite(SpriteIni[i].x,SpriteIni[i].y,SpriteIni[i].tx,SpriteIni[i].ty,SpriteIni[i].data,dblbuf);
		
	/*	Inimigo Boss I : 10 */
	i=10;
	SpriteIni[i].x=112;
	SpriteIni[i].y=0;
	SpriteIni[i].tx=46;
	SpriteIni[i].ty=32;
	SpriteIni[i].data=(char*)calloc(SpriteIni[i].tx*SpriteIni[i].ty,sizeof(char));
	getsprite(SpriteIni[i].x,SpriteIni[i].y,SpriteIni[i].tx,SpriteIni[i].ty,SpriteIni[i].data,dblbuf);
		
	/*	Inimigo Boss II : 11 */
	i=11;
	SpriteIni[i].x=160;
	SpriteIni[i].y=0;
	SpriteIni[i].tx=46;
	SpriteIni[i].ty=32;
	SpriteIni[i].data=(char*)calloc(SpriteIni[i].tx*SpriteIni[i].ty,sizeof(char));
	getsprite(SpriteIni[i].x,SpriteIni[i].y,SpriteIni[i].tx,SpriteIni[i].ty,SpriteIni[i].data,dblbuf);
		
	/*	Inimigo Boss III : 12 */
	i=12;
	SpriteIni[i].x=208;
	SpriteIni[i].y=0;
	SpriteIni[i].tx=30;
	SpriteIni[i].ty=48;
	SpriteIni[i].data=(char*)calloc(SpriteIni[i].tx*SpriteIni[i].ty,sizeof(char));
	getsprite(SpriteIni[i].x,SpriteIni[i].y,SpriteIni[i].tx,SpriteIni[i].ty,SpriteIni[i].data,dblbuf);
		
	/*	Inimigo Boss IV : 13 */
	i=13;
	SpriteIni[i].x=80;
	SpriteIni[i].y=48;
	SpriteIni[i].tx=30;
	SpriteIni[i].ty=46;
	SpriteIni[i].data=(char*)calloc(SpriteIni[i].tx*SpriteIni[i].ty,sizeof(char));
	getsprite(SpriteIni[i].x,SpriteIni[i].y,SpriteIni[i].tx,SpriteIni[i].ty,SpriteIni[i].data,dblbuf);
		
	/*	Inimigo Boss V : 14 */
	i=14;
	SpriteIni[i].x=0;
	SpriteIni[i].y=96;
	SpriteIni[i].tx=64;
	SpriteIni[i].ty=30;
	SpriteIni[i].data=(char*)calloc(SpriteIni[i].tx*SpriteIni[i].ty,sizeof(char));
	getsprite(SpriteIni[i].x,SpriteIni[i].y,SpriteIni[i].tx,SpriteIni[i].ty,SpriteIni[i].data,dblbuf);
		
	/* Nave 1 */
	i=0;
	SpriteNv[i].x=0;
	SpriteNv[i].y=32;
	SpriteNv[i].tx=16;
	SpriteNv[i].ty=16;
	SpriteNv[i].data=(char*)calloc(SpriteNv[i].tx*SpriteNv[i].ty,sizeof(char));
	getsprite(SpriteNv[i].x,SpriteNv[i].y,SpriteNv[i].tx,SpriteNv[i].ty,SpriteNv[i].data,dblbuf);
	
	/* Nave 2 */
	i=1;
	SpriteNv[i].x=16;
	SpriteNv[i].y=32;
	SpriteNv[i].tx=16;
	SpriteNv[i].ty=16;
	SpriteNv[i].data=(char*)calloc(SpriteNv[i].tx*SpriteNv[i].ty,sizeof(char));
	getsprite(SpriteNv[i].x,SpriteNv[i].y,SpriteNv[i].tx,SpriteNv[i].ty,SpriteNv[i].data,dblbuf);
	
				
	/* Disparo 1 */
	i=0;
	SpriteTiro[i].x=32;
	SpriteTiro[i].y=80;
	SpriteTiro[i].tx=1;
	SpriteTiro[i].ty=8;
	SpriteTiro[i].data=(char*)calloc(SpriteTiro[i].tx*SpriteTiro[i].ty,sizeof(char));
	getsprite(SpriteTiro[i].x,SpriteTiro[i].y,SpriteTiro[i].tx,SpriteTiro[i].ty,SpriteTiro[i].data,dblbuf);
	
	/* Disparo 2 */
	i=1;
	SpriteTiro[i].x=48;
	SpriteTiro[i].y=80;
	SpriteTiro[i].tx=10;
	SpriteTiro[i].ty=8;
	SpriteTiro[i].data=(char*)calloc(SpriteTiro[i].tx*SpriteTiro[i].ty,sizeof(char));
	getsprite(SpriteTiro[i].x,SpriteTiro[i].y,SpriteTiro[i].tx,SpriteTiro[i].ty,SpriteTiro[i].data,dblbuf);
		
	/* Disparo Inimigo 1 */
	i=0;
	SpriteTiroIni[i].x=0;
	SpriteTiroIni[i].y=80;
	SpriteTiroIni[i].tx=1;
	SpriteTiroIni[i].ty=8;
	SpriteTiroIni[i].data=(char*)calloc(SpriteTiroIni[i].tx*SpriteTiroIni[i].ty,sizeof(char));
	getsprite(SpriteTiroIni[i].x,SpriteTiroIni[i].y,SpriteTiroIni[i].tx,SpriteTiroIni[i].ty,SpriteTiroIni[i].data,dblbuf);
	
	/* Disparo Inimigo 2 */
	i=1;
	SpriteTiroIni[i].x=16;
	SpriteTiroIni[i].y=80;
	SpriteTiroIni[i].tx=9;
	SpriteTiroIni[i].ty=8;
	SpriteTiroIni[i].data=(char*)calloc(SpriteTiroIni[i].tx*SpriteTiroIni[i].ty,sizeof(char));
	getsprite(SpriteTiroIni[i].x,SpriteTiroIni[i].y,SpriteTiroIni[i].tx,SpriteTiroIni[i].ty,SpriteTiroIni[i].data,dblbuf);
		
	/* Explosões */
	for (i=0; i<NUMEXPLOS; i++)
	{
		SpriteExplo[i].x=i*16;
		SpriteExplo[i].y=48;
		SpriteExplo[i].tx=16;
		SpriteExplo[i].ty=16;
		SpriteExplo[i].data=(char*)calloc(SpriteExplo[i].tx*SpriteExplo[i].ty,sizeof(char));
		getsprite(SpriteExplo[i].x,SpriteExplo[i].y,SpriteExplo[i].tx,SpriteExplo[i].ty,SpriteExplo[i].data,dblbuf);
	}
		
	/* Prémios */
	for (i=0; i<NUMPREMIOS-2; i++)
	{
		SpritePremio[i].x=32+(i*16);
		SpritePremio[i].y=32;
		SpritePremio[i].tx=10;
		SpritePremio[i].ty=11;
		SpritePremio[i].data=(char*)calloc(SpritePremio[i].tx*SpritePremio[i].ty,sizeof(char));
		getsprite(SpritePremio[i].x,SpritePremio[i].y,SpritePremio[i].tx,SpritePremio[i].ty,SpritePremio[i].data,dblbuf);
	}
	i=NUMPREMIOS-2;
	SpritePremio[i].x=64;
	SpritePremio[i].y=48;
	SpritePremio[i].tx=10;
	SpritePremio[i].ty=11;
	SpritePremio[i].data=(char*)calloc(SpritePremio[i].tx*SpritePremio[i].ty,sizeof(char));
	getsprite(SpritePremio[i].x,SpritePremio[i].y,SpritePremio[i].tx,SpritePremio[i].ty,SpritePremio[i].data,dblbuf);
	i=NUMPREMIOS-1;
	SpritePremio[i].x=64;
	SpritePremio[i].y=64;
	SpritePremio[i].tx=10;
	SpritePremio[i].ty=11;
	SpritePremio[i].data=(char*)calloc(SpritePremio[i].tx*SpritePremio[i].ty,sizeof(char));
	getsprite(SpritePremio[i].x,SpritePremio[i].y,SpritePremio[i].tx,SpritePremio[i].ty,SpritePremio[i].data,dblbuf);
	
	/* Planetas */
	for (i=0; i<NUMPLANETAS; i++)
	{
		SpritePlaneta[i].x=i*24;
		SpritePlaneta[i].y=174;
		SpritePlaneta[i].tx=24;
		SpritePlaneta[i].ty=24;
		SpritePlaneta[i].data=(char*)calloc(SpritePlaneta[i].tx*SpritePlaneta[i].ty,sizeof(char));
		getsprite(SpritePlaneta[i].x,SpritePlaneta[i].y,SpritePlaneta[i].tx,SpritePlaneta[i].ty,SpritePlaneta[i].data,dblbuf);
	}
	
	/* Título */
	SpriteTitle.x=0;
	SpriteTitle.y=128;
	SpriteTitle.tx=189;
	SpriteTitle.ty=18;
	SpriteTitle.data=(char*)calloc(SpriteTitle.tx*SpriteTitle.ty,sizeof(char));
	getsprite(SpriteTitle.x,SpriteTitle.y,SpriteTitle.tx,SpriteTitle.ty,SpriteTitle.data,dblbuf);
		
	/* Painel */
	SpritePainel.x=249;
	SpritePainel.y=0;
	SpritePainel.tx=70;
	SpritePainel.ty=200;
	SpritePainel.data=(char*)calloc(SpritePainel.tx*SpritePainel.ty,sizeof(char));
	getsprite(SpritePainel.x,SpritePainel.y,SpritePainel.tx,SpritePainel.ty,SpritePainel.data,dblbuf);
	
	return(0);
		
}

/* Limpa a Memória Alocada */
void freememory(void)
{
	
	int i;
	
	/* Fonte */
	free(fonte);
	
	/* Double Buffer */
	free(dblbuf);
	
	/* DSP */
	free(digidata);
		
	/* Inimigos */
	for (i=0; i<NUMINIS; i++);
		free(SpriteIni[i].data);
			
	/* Nave */
	free(SpriteNv[0].data);
	free(SpriteNv[1].data);
		
	/* Disparos */
	free(SpriteTiro[0].data);
	free(SpriteTiro[1].data);
		
	/* Disparos Inimigos */
	free(SpriteTiroIni[0].data);
	free(SpriteTiroIni[1].data);
		
	/* Explosões */
	for (i=0; i<NUMEXPLOS; i++);
		free(SpriteExplo[i].data);
			
	/* Prémios */
	for (i=0; i<NUMPREMIOS; i++);
		free(SpritePremio[i].data);
		
	/* Planetas */
	for (i=0; i<NUMPLANETAS; i++);
		free(SpritePlaneta[i].data);
		
	/* Título */
	free(SpriteTitle.data);
	
	/* Painel */
	free(SpritePainel.data);
	
	/* Música */
	free(patinfofm);
			
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
	
	printf("\nReading Attack Waves File.\n");
	
	fp=fopen("data\\waves.dat","rb");
    if(fp==NULL)
    {
		printf("Impossible to Open Attack Waves File!!\n");
		return(1);
    }
	
	/* Sequência de Attack Waves */
	if (fread(wave,sizeof(wave),1,fp)==0)
	{
		printf("Error Reading Attack Waves File!\n");
		fclose(fp);
		return(2);
	}
	
	/* Attack Waves */
	if (fread(twave,sizeof(twave),1,fp)==0)
	{
		printf("Error Reading Attack Waves File!\n");
		fclose(fp);
		return(2);
	}

	printf("Success Reading Attack Waves File!\n");
	
	fclose(fp);

	return(0);
	
}

/* Lê a Palette */
int lepalette(void)
{

	printf("\nReading Palette File.\n");
	
	/* Abre a Palette Para Leitura*/
	fp=fopen("data\\pal.dat","rb");
	if(fp==NULL)
    {
      printf("Impossible to Open Palette File!\n");
	  return(1);
    }

	/* Lê a Fonte de Texto*/
	if (fread(pal,768,1,fp)==0)
	{
		printf("Error Reading Palette File!\n");
		fclose(fp);
		return(2);
	}

	printf("Success Reading Palette File!\n");	
	fclose(fp);
	return(0);
}

/* Define os Valores RGB da Palette */
void setpalette(void)
{

	int i,val;
	
	val=outp(PALINDEX,0);
	
	for(i=0;i<256;i++)
	{
		val=outp(PALRGBVL,pal[i][0]);
		val=outp(PALRGBVL,pal[i][1]);
		val=outp(PALRGBVL,pal[i][2]);
	}
	
	val++;
	
}

/* Lê a Fonte de Texto */
int lefontetxt(void)
{
	
	printf("\nReading Text Font File.\n");
	
	/* Alloca Memória para a Fonte de Texto */
	fonte=(char*)calloc(TXTX*TYTX*NCTX,sizeof(char));
	if (fonte==NULL)
	{
		printf("Error Allocing Text Font Memory!\0");
		return(3);
	}
	
	/* Abre a Fonte de Texto Para Leitura*/
	fp=fopen("data\\fonte.dat","rb");
	if(fp==NULL)
    {
		printf("Impossible to Open Text Font File!\n");
		free(fonte);
		return(1);
    }

	/* Lê a Fonte de Texto*/
	if (fread(fonte,TXTX*TYTX*NCTX,1,fp)==0)
	{
		printf("Error Reading Text Font File!\n");
		free(fonte);
		fclose(fp);
		return(2);
	}

	printf("Success Reading Text Font File!\n");
	fclose(fp);
	
	return(0);
	
}

/* Imprime a Fonte de Texto no Écran */
void putfonte(int x,int y,int tx,int ty,int car,unsigned char databuf[])
{

	int comxy,start;
	
	start=car*(tx*ty);
	
	comxy=y*MAXRESX+x;
	
	asm{
		push ds
		
		mov ax,ds
		mov es,ax
		
		mov cx,ty
		
		lds si,[fonte]
		add si,start
		
		les bx,[databuf]
		add bx,comxy
	}
loop1:
	asm{
		mov di,bx
		mov dx,tx
	}
loop2:
	asm{
		lodsb
		mov es:[di],al

		inc di
		dec dx
		jnz loop2
		
		add bx,MAXRESX
		
		loop loop1
		
		pop ds
	}	
}

/* Imprime Texto utilizando a Fonte */
void printtxt(int x,int y,int tx,int ty,unsigned char txt[])
{

	int i=0,car;
	
	while (txt[i]!='\0')
	{
		if (txt[i]==32) car=0;
		if (txt[i]==':') car=1;
		if (txt[i]=='!') car=2;
		if (txt[i]=='-') car=3;
		if (txt[i]>47 && txt[i]<58) car=txt[i]-44;
		if (txt[i]>64 && txt[i]<91) car=txt[i]-51;
		putfonte(x+(tx*i),y,tx,ty,car,dblbuf);
		i++;
	}
	
}

/* Lê os Sprites */
int lesprites(void)
{

	printf("\nReading Sprites File.\n");
	
	/* Alloca Memória para os Sprites e o Double Buffer */
	dblbuf=(char*)calloc(64000,sizeof(char));
	if (fonte==NULL)
	{
		printf("Error Allocing Sprites Memory!\0");
		return(3);
	}
		
	/* Abre os Sprites Para Leitura*/
	fp=fopen("data\\sprites.dat","rb");
	if(fp==NULL)
    {
		printf("Impossible to Open Sprites File!\n");
		free(dblbuf);
		return(1);
    }

	/* Lê os Sprites */
	if (fread(dblbuf,64000,1,fp)==0)
	{
		printf("Error Reading Sprites File!\n");
		free(dblbuf);
		fclose(fp);
		return(2);
	}

	printf("Success Reading Sprites File!\n");
	fclose(fp);
	
	return(0);
	
}

/* Vai Buscar o Sprite ao Buffer */
void getsprite(int x,int y,int tx,int ty,unsigned char dataspr[],unsigned char databuf[])
{
	
	int comxy;
	
	comxy=y*MAXRESX+x;
		
	asm{
		push ds
		
		mov ax,ds
		mov es,ax
		
		mov cx,ty
		lds si,[dataspr]
		
		les bx,[databuf]
		add bx,comxy
	}
loop1:
	asm{
		mov di,bx
		mov dx,tx
	}
loop2:
	asm{
		mov al,es:[di]
		mov [si],al
		inc di
		inc si
		
		dec dx
		jnz loop2
		
		add bx,MAXRESX
			
		loop loop1
		
		pop ds
	}
	
}

/* Imprime o Sprite no Buffer */
void putsprite(int x,int y,int tx,int ty,unsigned char dataspr[],unsigned char databuf[])
{

	int comxy,start,adx=0;
	
	if (y<=-ty || y>MAXY) return;
	if (x<=-tx || x>MAXX) return;
	
	start=0;
	
	if (x<MINX)
	{
		x=-1*x;
		tx-=x;
		adx=x;
		start=x;
		x=0;
	}
		
	if (x+tx>MAXX)
	{
		adx=tx;
		tx=MAXX+1-x;
		adx-=(MAXX+1-x);
	}
		
	if (y<MINY)
	{
		ty+=y;
		start+=(tx+adx)*(-y);
		y=0;
	}
	
	if (y+ty>MAXY)
		ty=MAXY+1-y;
	
	comxy=y*MAXRESX+x;
	
	asm{
		push ds
		
		mov ax,ds
		mov es,ax
		
		mov cx,ty
		
		lds si,[dataspr]
		add si,start
		
		les bx,[databuf]
		add bx,comxy
	}
loop1:
	asm{
		mov di,bx
		mov dx,tx
	}
loop2:
	asm{
		lodsb
		test al,al
		jz loop3
		mov es:[di],al
	}
loop3:
	asm{
		inc di
		
		dec dx
		jnz loop2
	
		add bx,MAXRESX
		add si,adx
		
		loop loop1
		
		pop ds
	}
	
}

/* Apaga o Sprite do Buffer */
void clrsprite(int x,int y,int tx,int ty,unsigned char databuf[])
{
	
	int comxy,adx=0;
	
	if (y<=-ty || y>MAXY) return;
	if (x<=-tx || x>MAXX) return;
	
	if (x<MINX)
	{
		x=-1*x;
		tx-=x;
		adx=x;
		x=0;
	}
		
	if (x+tx>MAXX)
	{
		adx=tx;
		tx=MAXX+1-x;
		adx-=(MAXX+1-x);
	}
		
	if (y<MINY)
	{
		ty+=y;
		y=0;
	}
	
	if (y+ty>MAXY)
		ty=MAXY+1-y;
	
	comxy=y*MAXRESX+x;
	
	asm{
		push ds
		
		xor ax,ax
		mov dx,ty
		
		les bx,[databuf]
		add bx,comxy
	}
loop1:
	asm{
		mov di,bx
	
		mov cx,tx
		cld
		rep stosb
			
		add bx,MAXRESX
		
		dec dx
		jnz loop1
		
		pop ds
	}
	
}

/* Imprime um Sprite no Écran sem Restições de Posição */
void putrect(int x,int y,int tx,int ty,unsigned char dataspr[],unsigned char databuf[])
{

	int comxy;
	
	comxy=y*MAXRESX+x;
	
	asm{
		push ds
		
		mov ax,ds
		mov es,ax
		
		mov cx,ty
		
		lds si,[dataspr]
		
		les bx,[databuf]
		add bx,comxy
	}
loop1:
	asm{
		mov di,bx
		mov dx,tx
	}
loop2:
	asm{
		lodsb
		test al,al
		jz loop3
		mov es:[di],al
	}
loop3:
	asm{
		inc di
		
		dec dx
		jnz loop2
	
		add bx,MAXRESX
		
		loop loop1
		
		pop ds
	}
	
}

/* Apaga um Rectângulo no Écran */
void clrrect(int x,int y,int tx,int ty,unsigned char databuf[])
{
	
	int comxy;
	
	comxy=y*MAXRESX+x;
	
	asm{
		push ds
		
		xor ax,ax
		mov dx,ty
		
		les bx,[databuf]
		add bx,comxy
	}
loop1:
	asm{
		mov di,bx
	
		mov cx,tx
		cld
		rep stosb
			
		add bx,MAXRESX
		
		dec dx
		jnz loop1
		
		pop ds
	}
	
}

/* Copia do Buffer para o Écran */
void vgacopy(unsigned char databuf[])
{
	
	asm{
		push ds
		
		mov ax,vgamem
		mov es,ax
				
		cld
		mov cx,16000
		
		lds si,[databuf]
		mov di,0
		
		rep movsd
		
		pop ds
	}

}

/* Espera pelo Vertical Retrace */
void wait_for_retrace(void)
{
	
	asm{
		mov dx,INPUT_STATUS
	}
retrace:
	asm{
		in al,dx
		test al,VRETRACE
		jnz retrace
	}
 noretrace:
	asm{
		in al,dx
		test al,VRETRACE
		jz noretrace
	}
	
}

/* Interrupt do Teclado */
static void interrupt keyb_int(void)
{
 
	unsigned char tcode;

	asm{
		in  al,60h
		mov tcode,al
		in  al,61h
		or  al,80h
		out 61h,al
		and al,7fh
		out 61h,al
		mov al,20h
		out 20h,al
	}

	if (tcode>0x80)
		teclas[tcode-0x80]=0;
	else
		teclas[tcode]=1;

}

void hook_keyb_int(void)
{
	
    old_keyb_int = getvect(0x09);
    setvect(0x09, keyb_int);
	
}

void unhook_keyb_int(void)
{
	
    if (old_keyb_int != NULL)
	{
        setvect(0x09, old_keyb_int);
        old_keyb_int = NULL;
    }
	
}

int ctrlbrk_handler(void)
{
	
    unhook_keyb_int();
	
    return 0;
	
}

/* Faz o Reset à Placa de Som FM AdLib */
void resetfm(void)
{
	int i;
	
	for (i=FM_MIN_REG; i<FM_MAX_REG; i++) writefm(i,0);
	
}

/* Inicializa a Placa de Som FM AdLib */
void initfm(void)
{

	/* Waveform Enable para todos os Canais */
	writefm(0x01,0x20);
	
	/* Tremolo e Vibrato Enable para todos os Canais */
	writefm(0xBD,0xC0);
	
}

/* Escreve um Valor num Registo FM AdLib */
void writefm(int reg, int value)
{
	
//	int i,val;
	
//	val=outp(ADL_REG,reg);					/* Escreve o Registo no Porto Register/Status */
//	for (i = 0; i <6; i++) inp(ADL_REG);	/* Espera 12 ciclos */
	
//	val=outp(ADL_DAT,value);				/* Escreve o Valor no Porto Data */
//	for (i = 0; i <35; i++) inp(ADL_REG);   /* Espera 12 ciclos */
	
//	val++;

	asm{
		mov dx,ADL_REG
		mov al,reg
		out dx,al
	}
	
	asm{
		mov dx,ADL_DAT
		mov al,value
		out dx,al
	}
	
}

/* Lê um Valor do Porto Status/Register FM AdLib */
int readfm(void)
{
	return (inp(ADL_REG));
}

/* Produz um Som FM AdLib */
void criasomfm(int canalg,int canalo,int freqindex)
{
	
	int freq,freql,freqh;
	int regb0;

	freq=notasfm[freqindex];
		
	freqh=(int)(freq/256);
	freql=(int)(freq-(freqh*256));
	
	/* Desliga o Canal */
	regb0=0*1+4*oitavafm+freqh;
	writefm(0xB0+canalg,regb0);

	/* Toca o Instrumento */
	regb0=32*1+4*oitavafm+freqh;
	
	/* Operador 1 */
	writefm(canalo,instreg[sifm].op1reg2); /* Tremolo, Vibrato, Hold Note, Keyboard Scaling Rate, Harmonic */
	writefm(canalo+0x20,instreg[sifm].op1reg4); /* Scale Level, Volume Level */
	writefm(canalo+0x40,instreg[sifm].op1reg6); /* Attack, Decay */
	writefm(canalo+0x60,instreg[sifm].op1reg8); /* Sustain, Release */
	writefm(canalo+0xC0,instreg[sifm].op1rege); /* Envelope Type */
	
	/* Operador 2 */
	writefm(canalo+0x3,instreg[sifm].op2reg2); 	/* Tremolo, Vibrato, Hold Note, Keyboard Scaling Rate, Harmonic */
	writefm(canalo+0x23,volfm); 				/* Scale Level, Volume Level */
	writefm(canalo+0x43,instreg[sifm].op2reg6); /* Attack, Decay */
	writefm(canalo+0x63,instreg[sifm].op2reg8); /* Sustain, Release */
	writefm(canalo+0xC3,instreg[sifm].op2rege); /* Envelope Type */

	/* Geral */
	writefm(0xC0+canalg,instreg[sifm].regc0);  	/* Feedback Modulation, FM Synthesis ON/OFF */
	writefm(0xA0+canalg,freql); 				/* Frequência Low Byte */
	
//	if (cnlonfm[canalg]==1)
		writefm(0xB0+canalg,regb0);  			/* Play Note, Oitava, Frequência Hi Byte */
			
}

/* Produz um Som FM AdLib 2 */
void criasomfm2(int canalg,int canalo,int freqindex,int somindex)
{
	
	int freq,freql,freqh;
	int regb0;

	freq=notasfm[freqindex];
		
	freqh=(int)(freq/256);
	freql=(int)(freq-(freqh*256));
	
	/* Desliga o Canal */
	regb0=0*1+4*oitavafm+freqh;
	writefm(0xB0+canalg,regb0);

	/* Toca o Instrumento */
	regb0=32*1+4*oitavafm+freqh;
	
	/* Operador 1 */
	writefm(canalo,instregsons[somindex].op1reg2); /* Tremolo, Vibrato, Hold Note, Keyboard Scaling Rate, Harmonic */
	writefm(canalo+0x20,instregsons[somindex].op1reg4); /* Scale Level, Volume Level */
	writefm(canalo+0x40,instregsons[somindex].op1reg6); /* Attack, Decay */
	writefm(canalo+0x60,instregsons[somindex].op1reg8); /* Sustain, Release */
	writefm(canalo+0xC0,instregsons[somindex].op1rege); /* Envelope Type */
	
	/* Operador 2 */
	writefm(canalo+0x3,instregsons[somindex].op2reg2); 	/* Tremolo, Vibrato, Hold Note, Keyboard Scaling Rate, Harmonic */
	writefm(canalo+0x23,volfm); 				/* Scale Level, Volume Level */
	writefm(canalo+0x43,instregsons[somindex].op2reg6); /* Attack, Decay */
	writefm(canalo+0x63,instregsons[somindex].op2reg8); /* Sustain, Release */
	writefm(canalo+0xC3,instregsons[somindex].op2rege); /* Envelope Type */

	/* Geral */
	writefm(0xC0+canalg,instregsons[somindex].regc0);  	/* Feedback Modulation, FM Synthesis ON/OFF */
	writefm(0xA0+canalg,freql); 				/* Frequência Low Byte */
	
	writefm(0xB0+canalg,regb0);  			/* Play Note, Oitava, Frequência Hi Byte */
			
}

/* Desliga o Canal FM AdLib */
void stopsomfm(int canalg)
{
	
	/* Desliga o Canal */
	writefm(0xB0+canalg,0x00);
	
}

/* Faz o Reset à Placa de Som FM Sound Blaster Pro */
void resetsb(void)
{
	int i;
	
	for (i=FM_MIN_REG; i<FM_MAX_REG; i++)
	{
		writelsb(i,0);
		writersb(i,0);
	}
	
}

/* Inicializa a Placa de Som FM Sound Blaster Pro */
void initsb(void)
{

	/* Waveform Enable para todos os Canais */
	writelsb(0x01,0x20);
	writersb(0x01,0x20);
	
	/* Tremolo e Vibrato Enable para todos os Canais */
	writelsb(0xBD,0xC0);
	writersb(0xBD,0xC0);
	
}

/* Escreve um Valor num Registo no Speaker Esquerdo Sound Blaster Pro */
void writelsb(int reg, int value)
{
	
//	int i,val;
	
//	val=outp(SBP_REG,reg);					/* Escreve o Registo no Porto Register/Status */
//	for (i = 0; i <6; i++) inp(SBP_REG);	/* Espera 12 ciclos */
	
//	val=outp(SBP_DAT,value);				/* Escreve o Valor no Porto Data */
//	for (i = 0; i <35; i++) inp(SBP_REG);   /* Espera 12 ciclos */
	
//	val++;
	
	asm{
		mov dx,SBP_REG
		mov al,reg
		out dx,al
	}
	
	asm{
		mov dx,SBP_DAT
		mov al,value
		out dx,al
	}
	
}

/* Escreve um Valor num Registo no Speaker Direito Sound Blaster Pro */
void writersb(int reg, int value)
{
	
//	int i,val;
	
//	val=outp(SBP_REG+2,reg);					/* Escreve o Registo no Porto Register/Status */
//	for (i = 0; i <6; i++) inp(SBP_REG+2);	    /* Espera 12 ciclos */
	
//	val=outp(SBP_DAT+2,value);				    /* Escreve o Valor no Porto Data */
//	for (i = 0; i <35; i++) inp(SBP_REG+2);    /* Espera 12 ciclos */
	
//	val++;
	
	asm{
		mov dx,SBP_REG+2
		mov al,reg
		out dx,al
	}
	
	asm{
		mov dx,SBP_DAT+2
		mov al,value
		out dx,al
	}
	
}

/* Lê um Valor do Porto Status/Register no Speaker Esquerdo Sound Blaster Pro */
int readlsb(void)
{
	return (inp(SBP_REG));
}

/* Lê um Valor do Porto Status/Register no Speaker Esquerdo Sound Blaster Pro */
int readrsb(void)
{
	return (inp(SBP_REG+2));
}

/* Produz um Som FM Sound Blaster Pro */
void criasomsb(int canalg,int canalo,int freqindex)
{
	
	int freq,freql,freqh;
	int regb0;

	freq=notasfm[freqindex];
		
	freqh=(int)(freq/256);
	freql=(int)(freq-(freqh*256));

	if (canalg==0 || canalg==2 || canalg==4 || canalg==6 || canalg==8) /* Speaker Esquerdo */
	{
		/* Desliga o Canal */
		regb0=0*1+4*oitavafm+freqh;
		writelsb(0xB0+canalg,regb0);

		/* Toca o Instrumento */
		regb0=32*1+4*oitavafm+freqh;
	
		/* Operador 1 */
		writelsb(canalo,instreg[sifm].op1reg2); /* Tremolo, Vibrato, Hold Note, Keyboard Scaling Rate, Harmonic */
		writelsb(canalo+0x20,instreg[sifm].op1reg4); /* Scale Level, Volume Level */
		writelsb(canalo+0x40,instreg[sifm].op1reg6); /* Attack, Decay */
		writelsb(canalo+0x60,instreg[sifm].op1reg8); /* Sustain, Release */
		writelsb(canalo+0xC0,instreg[sifm].op1rege); /* Envelope Type */
	
		/* Operador 2 */
		writelsb(canalo+0x3,instreg[sifm].op2reg2); 	/* Tremolo, Vibrato, Hold Note, Keyboard Scaling Rate, Harmonic */
		writelsb(canalo+0x23,volfm); 				/* Scale Level, Volume Level */
		writelsb(canalo+0x43,instreg[sifm].op2reg6); /* Attack, Decay */
		writelsb(canalo+0x63,instreg[sifm].op2reg8); /* Sustain, Release */
		writelsb(canalo+0xC3,instreg[sifm].op2rege); /* Envelope Type */

		/* Geral */
		writelsb(0xC0+canalg,instreg[sifm].regc0);  	/* Feedback Modulation, FM Synthesis ON/OFF */
		writelsb(0xA0+canalg,freql); 				/* Frequência Low Byte */
	
		writelsb(0xB0+canalg,regb0);  			/* Play Note, Oitava, Frequência Hi Byte */
	}
	else	/* Speaker Direito */
	{
		/* Desliga o Canal */
		regb0=0*1+4*oitavafm+freqh;
		writersb(0xB0+canalg,regb0);

		/* Toca o Instrumento */
		regb0=32*1+4*oitavafm+freqh;
	
		/* Operador 1 */
		writersb(canalo,instreg[sifm].op1reg2); /* Tremolo, Vibrato, Hold Note, Keyboard Scaling Rate, Harmonic */
		writersb(canalo+0x20,instreg[sifm].op1reg4); /* Scale Level, Volume Level */
		writersb(canalo+0x40,instreg[sifm].op1reg6); /* Attack, Decay */
		writersb(canalo+0x60,instreg[sifm].op1reg8); /* Sustain, Release */
		writersb(canalo+0xC0,instreg[sifm].op1rege); /* Envelope Type */
	
		/* Operador 2 */
		writersb(canalo+0x3,instreg[sifm].op2reg2); 	/* Tremolo, Vibrato, Hold Note, Keyboard Scaling Rate, Harmonic */
		writersb(canalo+0x23,volfm); 				/* Scale Level, Volume Level */
		writersb(canalo+0x43,instreg[sifm].op2reg6); /* Attack, Decay */
		writersb(canalo+0x63,instreg[sifm].op2reg8); /* Sustain, Release */
		writersb(canalo+0xC3,instreg[sifm].op2rege); /* Envelope Type */

		/* Geral */
		writersb(0xC0+canalg,instreg[sifm].regc0);  	/* Feedback Modulation, FM Synthesis ON/OFF */
		writersb(0xA0+canalg,freql); 				/* Frequência Low Byte */
	
		writersb(0xB0+canalg,regb0);  			/* Play Note, Oitava, Frequência Hi Byte */
	}	
	
}

/* Produz um Som FM Sound Blaster Pro 2 */
void criasomsb2(int canalg,int canalo,int freqindex,int somindex)
{
	
	int freq,freql,freqh;
	int regb0;

	freq=notasfm[freqindex];
		
	freqh=(int)(freq/256);
	freql=(int)(freq-(freqh*256));

	if (canalg==0 || canalg==2 || canalg==4 || canalg==6 || canalg==8) /* Speaker Esquerdo */
	{
		/* Desliga o Canal */
		regb0=0*1+4*oitavafm+freqh;
		writelsb(0xB0+canalg,regb0);

		/* Toca o Instrumento */
		regb0=32*1+4*oitavafm+freqh;
	
		/* Operador 1 */
		writelsb(canalo,instregsons[somindex].op1reg2); /* Tremolo, Vibrato, Hold Note, Keyboard Scaling Rate, Harmonic */
		writelsb(canalo+0x20,instregsons[somindex].op1reg4); /* Scale Level, Volume Level */
		writelsb(canalo+0x40,instregsons[somindex].op1reg6); /* Attack, Decay */
		writelsb(canalo+0x60,instregsons[somindex].op1reg8); /* Sustain, Release */
		writelsb(canalo+0xC0,instregsons[somindex].op1rege); /* Envelope Type */
	
		/* Operador 2 */
		writelsb(canalo+0x3,instregsons[somindex].op2reg2); 	/* Tremolo, Vibrato, Hold Note, Keyboard Scaling Rate, Harmonic */
		writelsb(canalo+0x23,volfm); 				/* Scale Level, Volume Level */
		writelsb(canalo+0x43,instregsons[somindex].op2reg6); /* Attack, Decay */
		writelsb(canalo+0x63,instregsons[somindex].op2reg8); /* Sustain, Release */
		writelsb(canalo+0xC3,instregsons[somindex].op2rege); /* Envelope Type */

		/* Geral */
		writelsb(0xC0+canalg,instregsons[somindex].regc0);  	/* Feedback Modulation, FM Synthesis ON/OFF */
		writelsb(0xA0+canalg,freql); 				/* Frequência Low Byte */
	
		writelsb(0xB0+canalg,regb0);  			/* Play Note, Oitava, Frequência Hi Byte */
	}
	else	/* Speaker Direito */
	{
		/* Desliga o Canal */
		regb0=0*1+4*oitavafm+freqh;
		writersb(0xB0+canalg,regb0);

		/* Toca o Instrumento */
		regb0=32*1+4*oitavafm+freqh;
	
		/* Operador 1 */
		writersb(canalo,instregsons[somindex].op1reg2); /* Tremolo, Vibrato, Hold Note, Keyboard Scaling Rate, Harmonic */
		writersb(canalo+0x20,instregsons[somindex].op1reg4); /* Scale Level, Volume Level */
		writersb(canalo+0x40,instregsons[somindex].op1reg6); /* Attack, Decay */
		writersb(canalo+0x60,instregsons[somindex].op1reg8); /* Sustain, Release */
		writersb(canalo+0xC0,instregsons[somindex].op1rege); /* Envelope Type */
	
		/* Operador 2 */
		writersb(canalo+0x3,instregsons[somindex].op2reg2); 	/* Tremolo, Vibrato, Hold Note, Keyboard Scaling Rate, Harmonic */
		writersb(canalo+0x23,volfm); 				/* Scale Level, Volume Level */
		writersb(canalo+0x43,instregsons[somindex].op2reg6); /* Attack, Decay */
		writersb(canalo+0x63,instregsons[somindex].op2reg8); /* Sustain, Release */
		writersb(canalo+0xC3,instregsons[somindex].op2rege); /* Envelope Type */

		/* Geral */
		writersb(0xC0+canalg,instregsons[somindex].regc0);  	/* Feedback Modulation, FM Synthesis ON/OFF */
		writersb(0xA0+canalg,freql); 				/* Frequência Low Byte */
	

		writersb(0xB0+canalg,regb0);  			/* Play Note, Oitava, Frequência Hi Byte */
	}	
	
}

/* Desliga o Canal FM Sound Blaster Pro */
void stopsomsb(int canalg)
{
	
	/* Desliga o Canal */
	writelsb(0xB0+canalg,0x00);
	writersb(0xB0+canalg,0x00);
	
}

/* Lê a Música FM a partir de um Ficheiro */
int lemusicafm(void)
{

	printf("\nReading FM Music File.\n");
	
	/* Abre o Ficheiro para Leitura Binária */
	fp=fopen("data\\musfm.dat","rb");
	if(fp==NULL)
    {
      printf("Impossible to Open FM Music File!\n");
	  return(1);
    }

	/* Cabeçalho da Música FM */
	if (fread(&cabfilefm,sizeof(cabfilefm),1,fp)==0)
	{
		printf("Error Reading FM Music File!\n");
		fclose(fp);
		return(2);
	}
	
	/* Informação das Posições FM */
	if (fread(songpos,sizeof(songpos),1,fp)==0)
	{
		printf("Error Reading FM Music File!\n");
		fclose(fp);
		return(2);
	}
	
	/* Aloca Memória para as Patterns FM */
	patinfofm=(char*)calloc(1152*cabfilefm.maxpat,sizeof(char));
	if (patinfofm==NULL)
	{
		printf("Error Allocing FM Music Memory!\0");
		fclose(fp);
		return(3);
	}

	/* Informação das Patterns FM */
	if (fread(patinfofm,1152*cabfilefm.maxpat,1,fp)==0)
	{
		printf("Error Reading FM Music File!\n");
		free(patinfofm);
		fclose(fp);
		return(2);
	}
	
	/* Informação dos Instrumentos FM */
	if (fread(instreg,sizeof(instreg),1,fp)==0)
	{
		printf("Error Reading FM Music File!\n");
		free(patinfofm);
		fclose(fp);
		return(2);
	}
	
	/* Correcção Oitava Instrumentos FM */
	if (fread(octinstfm,sizeof(octinstfm),1,fp)==0)
	{
		printf("Error Reading FM Music File!\n");
		free(patinfofm);
		fclose(fp);
		return(2);
	}

	printf("Success Reading FM Music File!\n");
	fclose(fp);
	
	return(0);
	
}

/* Lê a Informação da Pattern FM corrente */
void carregapatfm(void)
{

	int i,j;
	int x,y;
	
	pattern=songpos[position];
	py=0;
	
	y=0;
	for (i=pattern*1152; i<((pattern*1152)+1152); i+=18)
	{
		x=0;
		for(j=0; j<18; j+=2)
		{
			
			/* Byte 0 - Frequência, Oitava e Número do Efeito */
			hi=(int)(patinfofm[i+j+0]/64);
			lo=(int)(patinfofm[i+j+0]-hi*64);
			
			fmefectnum[y][x]=hi;
			
			hi=(int)(lo/16);
			lo=(int)(lo-hi*16);
	
			fmoct[y][x]=hi;
			fmfreq[y][x]=lo;
			
			/* Byte 1 - Valor do Efeito e Número do Sample */
			hi=(int)(patinfofm[i+j+1]/32);
			lo=(int)(patinfofm[i+j+1]-hi*32);
			
			switch (fmefectnum[y][x])
			{
				case 0:fmefectpar[y][x]=0;fmsamplenum[y][x]=lo;break;
				case 1:fmefectpar[y][x]=hi*32+lo;fmsamplenum[y][x]=0;break;
				case 2:fmefectpar[y][x]=0;fmsamplenum[y][x]=0;break;
				case 3:fmefectpar[y][x]=hi*9;fmsamplenum[y][x]=lo;break;
			}
			
			x++;
		}
		y++;
	}
	
}

/* Toca a Música Convertida FM */
void playmusicafm(void)
{
	
	int i,j;
	int salta=0,saltap;

	if (position<cabfilefm.songlen)
	{
	
		playfmstart=0;
	
		i=row;
		for (j=0; j<9; j++)
		{
						
			if (fmefectnum[i][j]==2) salta=1;	/* Salta para a Próxima Pattern */
			
			if (fmefectnum[i][j]==1)			/* Salta para a Posição Definida pelo Parâmetro */
			{
				salta=2;
				saltap=fmefectpar[i][j];
			}
				
			if (fmfreq[i][j]!=0 && salta==0)	/* Se a Frequência não for Zero e se não houver Saltos */
			{
				
				sifm=fmsamplenum[i][j]-1;
				
				volfm=instreg[sifm].op2reg4;
			
				oitavafm=fmoct[i][j]+octinstfm[fmsamplenum[i][j]-1];
				
				if (cardtype==1 || cardtype==2) criasomfm(j,canaisfm[j],fmfreq[i][j]);	/* AdLib, Sound Blaster */
				if (cardtype==3) criasomsb(j,canaisfm[j],fmfreq[i][j]); /* Sound Blaster Pro */
			}
		}

		/* Fica na Pattern Corrente e Passa para a Próxima Row */
		if (salta==0)
		{
			row++;
			if (row==64)
			{
				row=0;
				position++;
				carregapatfm();
			}
		}
		
		/* Salta para a Próxima Posição */
		if (salta==1)
		{
			row=0;
			position++;
			carregapatfm();
		}
		
		/* Salta para a Posição definida pelo Parâmetro */
		if (salta==2)
		{
			row=0;
			position=saltap;
			carregapatfm();
		}
			
	}
	else
	{
		pattern=0;
		position=0;
		py=0;
		row=0;
		sifm=0;
		carregapatfm();
	}

}

/* Define os Valores dos Registos dos Sons do Jogo */
void definesons(void)
{

	/* Tiro da Nave */	
	sprintf(instregsons[0].nome,"tiro\0");
	instregsons[0].num=0;
	instregsons[0].regc0=0x0e;
	instregsons[0].op1reg2=0x2f;
	instregsons[0].op2reg2=0x0f;
	instregsons[0].op1reg4=0x00;
	instregsons[0].op2reg4=0x04;
	instregsons[0].op1reg6=0xf1;
	instregsons[0].op2reg6=0x99;
	instregsons[0].op1reg8=0x00;
	instregsons[0].op2reg8=0xb8;
	instregsons[0].op1rege=0x00;
	instregsons[0].op2rege=0x00;
	
	/* Explosão */	
	sprintf(instregsons[1].nome,"explosao\0");
	instregsons[1].num=1;
	instregsons[1].regc0=0x0e;
	instregsons[1].op1reg2=0x20;
	instregsons[1].op2reg2=0x00;
	instregsons[1].op1reg4=0x00;
	instregsons[1].op2reg4=0x04;
	instregsons[1].op1reg6=0xf5;
	instregsons[1].op2reg6=0xf5;
	instregsons[1].op1reg8=0x00;
	instregsons[1].op2reg8=0xb8;
	instregsons[1].op1rege=0x00;
	instregsons[1].op2rege=0x00;

	/* Prémios */
	sprintf(instregsons[2].nome,"premio\0");
	instregsons[2].num=2;
	instregsons[2].regc0=0x00;
	instregsons[2].op1reg2=0xcc;
	instregsons[2].op2reg2=0xdf;
	instregsons[2].op1reg4=0x00;
	instregsons[2].op2reg4=0x00;
	instregsons[2].op1reg6=0xf1;
	instregsons[2].op2reg6=0xf1;
	instregsons[2].op1reg8=0x5f;
	instregsons[2].op2reg8=0x5f;
	instregsons[2].op1rege=0x00;
	instregsons[2].op2rege=0x00;
	
	/* Boss */
	sprintf(instregsons[3].nome,"boss\0");
	instregsons[3].num=3;
	instregsons[3].regc0=0x00;
	instregsons[3].op1reg2=0x40;
	instregsons[3].op2reg2=0x56;
	instregsons[3].op1reg4=0x09;
	instregsons[3].op2reg4=0x04;
	instregsons[3].op1reg6=0x12;
	instregsons[3].op2reg6=0x21;
	instregsons[3].op1reg8=0x72;
	instregsons[3].op2reg8=0x21;
	instregsons[3].op1rege=0x00;
	instregsons[3].op2rege=0x00;
	
}

/* Faz o Reset ao DSP */
int resetdsp(void)
{
	
	int val;
	
	val=outp(DSP_RST,1);
	delay(10);
	val=outp(DSP_RST,0);
	delay(10);		
	val++;

	/* Verifica se o DSP foi inicializado */
	if (((inp(DSP_BUF) & 0x80)==0x80) && (inp(DSP_DAT)==0xAA))
	{
		printf("\nSound Card Found!\n");
		return(0);
	}
	else
	{
		printf("\nSound Card Not Found!\n");
		return(1);
	}
		
}

/* Escreve um Valor no Porto dos Comandos */
void writedsp(int value)
{
	
	int val;
	
	while ((inp(DSP_CMD) & 128)!=0);	/* Espera que o Porto dos Comandos esteja desimpedido */
	
	val=outp(DSP_CMD,value);			/* Escreve o valor no Porto dos Comandos */
			
	val++;
	
}

/* Lê um Valor no Porto dos Dados */
int readdsp(void)
{
	
	return(inp(DSP_DAT));	/* Lê o valor no Porto dos Dados */
			
}

/* Envia o som para o DSP através do DMA */
void playsom(void)
{

	long          LinearAddress;
	unsigned int  Page,OffSet;
	unsigned char TimeConstant;
	
	/* Calcula a TimeConstant */
	TimeConstant = (65536-(256000000/frequencia))>>8;
	
	/* Envia a Frequência (TimeConstant) para o DSP */
	writedsp(0x40);
	writedsp(TimeConstant);

	/* Converte o Ponteiro do Sample para o Linear Address */
	LinearAddress=FP_SEG(digidata);
	LinearAddress=(LinearAddress<<4)+FP_OFF(digidata);
	Page=LinearAddress>>16;      		/* Calculate a Página */
	OffSet=LinearAddress&0xFFFF; 		/* Calculate OffSet na Página */
	
	outportb(0x0A,5);              	/* Mascara o DMA channel 1 */
	outportb(0x0C,0);              	/* Limpa o Byte Pointer */
	outportb(0x0B,0x49);           	/* Set mode */
  
	outportb(0x02,OffSet&0xFF); 	/* Envia o OffSet para o DMA */
	outportb(0x02,OffSet>>8);

	outportb(0x83,Page);           	/* Envia a Página para o DMA */

	outportb(0x03,numsamples&0xFF);
	outportb(0x03,numsamples>>8);

	outportb(0x0A,1);              	/* Desmascara o DMA channel */

	writedsp(0xD1);					/* Liga o Speaker */

	writedsp(0x14);                 /* DSP comando 14h : Single cycle playback */
	writedsp(numsamples&0xFF);
	writedsp(numsamples>>8);
	
}

/* Lê o Ficheiro WAVE */
int lewave(void)
{

	printf("\nReading Explode Sound File.\n");

	fp=fopen("data\\explode.dat","rb");
    if(fp==NULL)
    {
		printf("Impossible to open Explode Sound File!\n");
		return(1);
	}
	
	/* Lê o Cabeçalho */
	if (fread(&wavecab,sizeof(wavecab),1,fp)==0)
	{
		printf("Error Reading Explode Sound File!\n");
		fclose(fp);
		return(2);
	}
	
	/* Lê a Frequência */
	frequencia=wavecab.Frequency;
	
	/* Verifica o tamanho do Sample */
	numsamples=wavecab.datasize;

     /* Alloca a Memória para o Sample */
	digidata=(char*)calloc(numsamples,sizeof(char));
	if (digidata==NULL)
	{
		printf("Error Allocing Explode Sound Memory!\0");
		fclose(fp);
		return(3);
	}
	
	if (fread(digidata,numsamples,1,fp)==0)
	{
		printf("Error Reading Explode Sound File!\n");
		free(digidata);
		fclose(fp);
		return(2);
	}
	
	printf("Success Reading Explode Sound File!\n");
	fclose(fp);
	
	return(0);
	
}