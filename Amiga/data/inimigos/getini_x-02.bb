;
; Cria a posicao horizontal dos inimigos em 8x
;

WBStartup

NEWTYPE .ltipoini
  tipoini.b[1000]
End NEWTYPE

DEFTYPE .ltipoini ltipoini

If ReadFile (0,"inimigos.dat")
  ReadMem 0,&ltipoini,SizeOf.ltipoini
  CloseFile 0
End If

NEWTYPE .linix
  inix.w[1000]
End NEWTYPE

DEFTYPE .linix linix


Dim tipo(9)

tipo(0)=0
tipo(1)=3
tipo(2)=3
tipo(3)=2
tipo(4)=3
tipo(5)=6
tipo(6)=6
tipo(7)=4
tipo(8)=6
tipo(9)=10


linix\inix[0]=0
linix\inix[1]=12 ;5  ;26 ;5
linix\inix[2]=19 ;26 ;19 ;12
linix\inix[3]=5  ;12 ;12 ;19
linix\inix[4]=26 ;19 ;5  ;26
linix\inix[5]=5  ;5  ;12 ;19
linix\inix[6]=19 ;26 ;19 ;12
linix\inix[7]=12 ;12 ;26 ;5

x.w

For n=8 To 999

  If ltipoini\tipoini[n]=0
    linix\inix[n]=0
    Goto proxn
  End If

.calc
  x=Int(Rnd(30-tipo(ltipoini\tipoini[n]))+5)

  If Joyb(1)=1 Goto sai

;  If x>linix\inix[n-7]-3 AND x<linix\inix[n-7]+3 Goto calc
  If x>linix\inix[n-6]-3 AND x<linix\inix[n-6]+3 Goto calc
  If x>linix\inix[n-5]-3 AND x<linix\inix[n-5]+3 Goto calc
  If x>linix\inix[n-4]-3 AND x<linix\inix[n-4]+3 Goto calc
  If x>linix\inix[n-3]-3 AND x<linix\inix[n-3]+3 Goto calc
  If x>linix\inix[n-2]-3 AND x<linix\inix[n-2]+3 Goto calc
  If x>linix\inix[n-1]-3 AND x<linix\inix[n-1]+3 Goto calc

  linix\inix[n]=x

.proxn
  NPrint n

Next n

For n=0 To 999
  linix\inix[n]*8
Next n

For n=0 To 999
  NPrint n,"-",ltipoini\tipoini[n],"-",linix\inix[n]
Next n


If WriteFile (1,"inimigos_x_04.dat")
  WriteMem 1,&linix,SizeOf.linix
  CloseFile 1
End If


While Joyb(0)<>2

Wend

.sai
End
