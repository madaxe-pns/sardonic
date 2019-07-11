;
; Cria a posicao horizontal dos inimigos
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
tipo(1)=23
tipo(2)=23
tipo(3)=15
tipo(4)=24
tipo(5)=46
tipo(6)=46
tipo(7)=30
tipo(8)=48
tipo(9)=80


linix\inix[0]=0
linix\inix[1]=50
linix\inix[2]=125
linix\inix[3]=200
linix\inix[4]=250
linix\inix[5]=200
linix\inix[6]=125
linix\inix[7]=50

x.w

For n=8 To 999

  If ltipoini\tipoini[n]=0
    linix\inix[n]=0
    Goto proxn
  End If

.calc
  x=Int(Rnd(239-tipo(ltipoini\tipoini[n]))+40)

  If Joyb(1)=1 Goto sai

;  If x>linix\inix[n-7] AND x<linix\inix[n-7]+30 Goto calc
  If x>linix\inix[n-6]-24 AND x<linix\inix[n-6]+24 Goto calc
  If x>linix\inix[n-5]-24 AND x<linix\inix[n-5]+24 Goto calc
  If x>linix\inix[n-4]-24 AND x<linix\inix[n-4]+24 Goto calc
  If x>linix\inix[n-3]-24 AND x<linix\inix[n-3]+24 Goto calc
  If x>linix\inix[n-2]-24 AND x<linix\inix[n-2]+24 Goto calc
  If x>linix\inix[n-1]-24 AND x<linix\inix[n-1]+24 Goto calc

  linix\inix[n]=x

.proxn
  NPrint n

Next n


For n=0 To 999
  NPrint n,"-",ltipoini\tipoini[n],"-",linix\inix[n]
Next n


If WriteFile (1,"inimigos_x_01.dat")
  WriteMem 1,&linix,SizeOf.linix
  CloseFile 1
End If


While Joyb(0)<>2

Wend

.sai
End
