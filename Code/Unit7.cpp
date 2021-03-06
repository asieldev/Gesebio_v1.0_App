//---------------------------------------------------------------------------

#include <vcl.h>
//#include <complex.h>
#pragma hdrstop
#include <math.h>
#define PI 3.14159265358
#include "Unit7.h"

#include "Unit6.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Chart"
#pragma link "Series"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma resource "*.dfm"
TForm7 *Form7;
 int IIR_Resp(double  *acoefs,double *bcoefs,double *magna,double *angle,int tot_pts,int order);
double cabs( complex z);
double WIN(int I,int N,int VEN);
void BR_FIR(double FC1,double FC2,double FS,double *COEF,int N,int VEN);
void  LP_FIR(double FC,double FS,double *COEF,int N,int VEN);
void  HP_FIR(double FC,double FS,double *COEF,int N,int VEN);
void BP_FIR(double FC1,double FC2,double FS,double *COEF,int N,int VEN);
void NOTCH(double *FN,double *AF,double FS,double *COEF);

//---------------------------------------------------------------------------
__fastcall TForm7::TForm7(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm7::SpeedButton1Click(TObject *Sender)
{
Form6->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm7::FormActivate(TObject *Sender)
{
String l="Filtrando  -"+ Form1->Path_Name;
Form7->Caption=l.t_str();
SpeedButton2->Enabled=false;
SpeedButton3->Enabled=false;
ListBox2->Clear();
LineSeries2->Clear();
LineSeries1->Clear();
LineSeries4->Clear();
LineSeries3->Clear();
for(int i=0;i<Form1->Series1->Count();i++)

{
LineSeries1->AddXY(Form1->Series1->XValue[i],Form1->Series1->YValue[i]);
LineSeries3->AddXY(Form1->Series1->XValue[i],Form1->Series1->YValue[i]);
}

}
//---------------------------------------------------------------------------

void __fastcall TForm7::BitBtn1Click(TObject *Sender)
{
try{
double *COEF;
SpeedButton3->Enabled=true;
int N,VEN;
ListBox1->Clear();
LineSeries4->Clear();
LineSeries5->Clear();

double FC=StrToFloat(Edit5->Text);
double FS=(double)1/(Form1->Frm);

 N=StrToInt(Edit6->Text);

 VEN= ComboBox1->ItemIndex+1;
  COEF=new double [2*N];

 LP_FIR( FC, FS, COEF, N, VEN);


 int g;
for(g=0;g<=(N);g++)
{
ListBox1->Items->Add(FloatToStr(COEF[g]));
LineSeries5->AddXY(g,COEF[g]);
}


 //Flitrando---------------------




double r;
double *OUTq= new double [Form1->Series1->Count()*2];
double *INq= new double [(Form1->Series1->Count()+N*2)];

int q=0;
for(int o1o=0;o1o<Form1->Series1->Count()+N*2;o1o++)
  INq[o1o]=0;

for(int oo=0;oo<Form1->Series1->Count();oo++)
  INq[oo]= Form1->Series1->YValue[oo];

for(int pp=0;pp<Form1->Series1->Count();pp++)
		{
			r = 0;
			for (int k=0; k<N; k++)
				r = r + INq[pp+k] * COEF[k];
			OUTq[pp]= r;
		}

for(int c = 0; c < Form1->Series1->Count(); c++)

LineSeries4->AddXY((double)c*Form1->Frm,OUTq[c]);


delete COEF;
delete COEF1;

delete OUTq;
        }catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema con los par�metros de entrada. Por favor verifique el contenido de los mismos y vuelva a intentarlo.Si el problema contin�a contacte inmediatamante a los dise�adores.");}


}
//---------------------------------------------------------------------------




/************************************************************************
Funcion: LPHP
Objetivo: Calcular coeficientes de Bicuadraticas de filtros
pasa bajo y pasa alto.
Entrada: FC, FS, N, T
FC = Frecuencia de Corte en Hz
FS = Frecuencia de Muestreo en Hz
N = Numero de Bicuadraticas
T = Tipo de Filtro (0=LP) (1=HP)
Salida: COEF
COEF = Arreglo con coeficientes de bicuadraticas
{SE,B2,B1,B0,A2,A1,SE,B2,...}
SE = Exponente de Normalizacion/Denormalizacion
************************************************************************/
void __fastcall TForm7::LPHP(double FC,double FS,double *COEF,int N,int T)
{


int I,J,K;
double WC,ANG,G,A1,A2,DEN;
if (T == 0)                         /* Si es LP */
WC = tan(PI*FC/FS);                  /* Wc = tan(pi*Fc/Fs */
else                              /* Si es HP */
  WC = 1.0/tan(PI*FC/FS);          /* Wc = cot(pi*Fc/Fs */
J = N/2;            					/* Correguir Num de Biquad */

for(I = 1; I <= J; I++)            /* Ciclo de Calculo */
{
  K = (I - 1)*6;                             /* Indice en Arreglo */
  ANG = PI*(N - 1 + 2*I)/(2*N);              /* Angulo de Polos */
  DEN = (1.0 - 2.0*WC*cos(ANG) + WC*WC);     /* Calculo de Denominador */
  G = (WC*WC) / DEN;                             /* Calculo de G */
  A1 = 2.0*(WC*WC-1) / DEN;                     /* Calculo de A1 */
  A2 = (1.0 + 2.0*WC*cos(ANG)+WC*WC)/ DEN;      /* Calculo de A2 */
  COEF[K+0] = 0;                             /* SE */
  COEF[K+1] = G;                             /* B2 */

if (T == 0)                                    /* Si es Pasa Bajo */
 COEF[K+2] = 2*G;                              /* B1 */
else                                            /* Si es Pasa Alto */
  COEF[K+2] = -2*G;                               /* B1 */
  COEF[K+3] = G;                               /* B0 */
  COEF[K+4] = -1*A2;                             /* A2 */
if (T == 0)                               /* Si es Pasa Bajo */

  COEF[K+5] = -1*A1;                         /* A1 */
else                                     /* Si es Pasa Alto */

  COEF[K+5] = A1;                        /* A1 */
 }
}

void __fastcall TForm7::SpeedButton2Click(TObject *Sender)
{

String AA= "Reemplazar serie principal " ;
String s ="�Est� seguro que desea reemplazar la serie principal de este proyecto por una nueva.?";

int a=Application->MessageBoxA(s.w_str(),AA.w_str(),MB_YESNO+MB_ICONWARNING);
 if(a==IDYES )
 {


Form1->Series1->Clear();
for(int i=0;i<LineSeries2->Count();i++)


Form1->Series1->AddXY(LineSeries2->XValue[i],LineSeries2->YValue[i]);

Form1->OldXs=Form1->Series1->MaxXValue();
Form1->OldYs=Form1->Series1->YValue[Form1->Series1->LastValueIndex];
} this->Close();
}
//---------------------------------------------------------------------------





void __fastcall TForm7::BitBtn9Click(TObject *Sender)
{try{
SpeedButton2->Enabled=true;
int N,T;
ListBox2->Clear();
LineSeries2->Clear();

double FC=StrToFloat(Edit13->Text);
double FS=(double)1/(Form1->Frm);

N=StrToInt(Edit14->Text);
 int kk=5*N*2;
COEF=new double [kk];
COEF1=new double [kk];



LPHP(FC,FS,COEF,N,1);




for(int i=0;i<N/2;i++)
{int j=i*6;
float gain= sqrt(COEF[j+1]*COEF[j+1]);
ListBox2->Items->Add("ETAPA "+IntToStr(i+1));
ListBox2->Items->Add("--------------------------");
ListBox2->Items->Add("Num2:: "+FloatToStr(COEF[j+1]/gain));
COEF1[i*5]= COEF[j+1];
ListBox2->Items->Add("Num1:: "+FloatToStr(COEF[j+2]/gain));
COEF1[i*5+1]= COEF[j+2];
ListBox2->Items->Add("Num0:: "+FloatToStr(COEF[j+3]/gain));
COEF1[i*5+2]=COEF[j+3];
ListBox2->Items->Add("Den2:: "+FloatToStr(-COEF[j+4]));
COEF1[i*5+3]= COEF[j+4];
ListBox2->Items->Add("Den1:: "+FloatToStr(-COEF[j+5]));
COEF1[i*5+4]=COEF[j+5];
ListBox2->Items->Add("Ganancia:: "+FloatToStr(gain));
ListBox2->Items->Add("--------------------------");

}


double *X=new double [Form1->Series1->Count()*2];
double ACUM;
double *OUTq=new double [Form1->Series1->Count()+N*2];

for(int o1o=0;o1o<Form1->Series1->Count()+N*2;o1o++)
  X[o1o]=0;



int ii=0;
int q=0;

for(int pp=0;pp<Form1->Series1->Count();pp++)
{
ACUM=Form1->Series1->YValue[pp];


for(ii = 0; ii < N/2; ii++)       // Repetir por N bicuadraticas
{
q = ii*5;                             // Ajustar Indice de variables
X[q+2] = ACUM;                       // X[n] = Valor del ADC
									 // o ultimo filtro!
ACUM = COEF1[q+2]*X[q+2];                 // Y[n] = B0*X[n]
ACUM = ACUM + COEF1[q+1]*X[q+1];           // Y[n] = Y[n] + B1*X[n-1]
ACUM = ACUM + COEF1[q+0]*X[q+0];               // Y[n] = Y[n] + B2*X[n-2]
ACUM = ACUM + COEF1[q+3]*X[q+3];                   // Y[n] = Y[n] + A1*Y[n-1]
ACUM = ACUM + COEF1[q+4]*X[q+4];           // Y[n] = Y[n] + A2*Y[n-2]
X[q+0] = X[q+ 1];               // X[n-2] = X[n-1]
X[q+1] = X[q+ 2];                   // X[n-1] = X[n]
X[q+3] = X[q+ 4];                   // Y[n-2] = Y[n-1]
X[q+4] = ACUM;                     // Y[n-1] = Y[n]
}
OUTq[pp]=ACUM;
}
for(int c = 0; c < Form1->Series1->Count(); c++)

LineSeries2->AddXY((double)c*Form1->Frm,OUTq[c]);


delete COEF;
delete COEF1;
delete X;
delete OUTq;
}catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema con los par�metros de entrada. Por favor verifique el contenido de los mismos y vuelva a intentarlo.Si el problema contin�a contacte inmediatamante a los dise�adores.");}

}
//---------------------------------------------------------------------------

void __fastcall TForm7::BP(double FC1,double FC2,double FS,double *COEF,int N)
{
int I,J,K;
double WC,WC1,WC2,ANG,G,A1,A2,A3,A4,FC,CC,DEN;
double A,B,C,D,Q,R,X;
double M0,M1,M2,N0,N1,N2;
double L,F1,F2;
complex T,T1,T2,S1,S2;
WC1 = 2*PI*FC1/FS; /* Normalizacion de FC1 */
WC2 = 2*PI*FC2/FS; /* Normalizacion de FC2 */
CC = sin(WC1 + WC2)/(sin(WC1) + sin(WC2)); /* Calculo de F central */
WC = fabs( (CC - cos(WC2))/sin(WC2)); /* Calculo de Wc */
J = N/2; /* Correguir Num de Biquad */
for(I = 1; I <= J; I++) /* Ciclo de Calculo */
{
K = (I - 1)*12; /* Indice en Arreglo */
ANG = PI*(N - 1 + 2*I)/(2*N); /* Angulo de Polos */
DEN = (1.0 - 2.0*WC*cos(ANG) + WC*WC);/* Calculo de Denominador */
G  = (WC*WC) / DEN; /* Calculo de G */
A1 = 4*CC*(WC*cos(ANG) - 1)/DEN; /* Calculo de A1*Z^-1 */
A2 = 2*(2*CC*CC + 1 - WC*WC)/DEN; /* Calculo de A2*Z^-2 */
A3 = -4*CC*(WC*cos(ANG) + 1)/DEN; /* Calculo de A3*Z^-3 */
A4 = (1.0 + 2.0*WC*cos(ANG) + WC*WC)/DEN;/* Calculo de A4*Z^-4 */
/************************************************************************
Los coeficientes antes calculados son de una Ecuacion Cuartica
aqui los convertiremos en dos cuadraticas.
Ref. Pag 2-14 de Handbook of Engineering Fundamentals
 Eshbach
 Second Edition
 Wiley Handbook Series 1952.
 ISBN: No existia en esos tiempos
 (Las Matematicas nunca cambian...)
a0*X^4 + a1*X^3 + a2*X^2 + a3*X + a4 = 0
dividimos entre a0 para obtener
X^4 + a*X^3 + b*X^2 + c*X + d = 0
29
buscamos cualquier raiz real y1 de
8*Y^3 - 4*B*Y^2 + 2(A*C - 4*D)*Y - (C^2 + D*(A^2 - 4B)) = 0
entonces las dos cuadraticas son
x^2 + (a/2 - (a^2/4 + 2*y1 - b)^.5)*x + (y1 + (y1^2 - d)^.5) = 0
x^2 + (a/2 + (a^2/4 + 2*y1 - b)^.5)*x + (y1 + (y1^2 - d)^.5) = 0
para encontrar una raiz real de una cubica
a*x^3 + b*x^2 + c*x + d = 0
hacemos
q = a*c - b^2
r = 0.5*(3*a*b*c - a^2*d) - b^3
s1 = (r + (q^3 + r^2)^.5)^(1/3)
s2 = (r - (q^3 + r^2)^.5)^(1/3)
Entonces las raices son
x1 = (s1 + s2 - b)/a
x2 = (-.5(s1 + s2) + (-3)^(1/3)*(s1-s2)/2 -b)/a
x3 = (-.5(s1 + s2) - (-3)^(1/3)*(s1-s2)/2 -b)/a
************************************************************************/
/************************************************************************
Calculo de raiz real y1 de cubica
************************************************************************/
A = 8.0; /* A = 8 */
B = -4*A2/3; /* B = -4*a2/3 */
C = 2*(A1*A3 - 4*A4)/3; /* C = 2*(a1*a3 - 4*a4)/3 */
D = -1.0*(A3*A3+ A4*(A1*A1 - 4*A2)); /* D = ... */
Q = A*C - B*B; /* Calculo de Q */
R = 0.5*(3*A*B*C - A*A*D) - B*B*B; /* Calculo de R */
L = Q*Q*Q + R*R; /* Argumento de Raiz Cuad Sx*/
if (L > 0.0) /* Si es positiva */
{
T.x = sqrt(L); /* Resultado es Real */
T.y = 0.0; /* Imaginario = 0 */
}
else /* Si es Negativa */
{
T.x = 0.0; /* Real = 0 */
T.y = sqrt(fabs(L)); /* Resultado Imaginario */
}
T1.x = R + T.x; /* Calculo del Resto de S1 */
T1.y =     T.y;
T2.x = cabs(T1);
T2.y = atan2(T1.y,T1.x);
S1.x = pow(T2.x,1.0/3.0);
S1.y = T2.y / 3.0;
T1.x = R - T.x; /* Calculo del Resto de S2 */
T1.y =     T.y;
T2.x = cabs(T1);
T2.y = atan2(T1.y,T1.x);
S2.x = pow(T2.x,1.0/3.0);

S2.y = T2.y / 3.0;
/* Calculo de X1 (REAL */
X = (S1.x*cos(S1.y) + S2.x*cos(S2.y) - B)/A;
/************************************************************************
Calculo de Coeficientes de Cuadraticas
************************************************************************/
F1 = A1*A1/4 + 2*X - A2;
F1 = sqrt(F1);
F2 = X*X - A4;
F2 = sqrt(F2);
N2 = 1;
N1 = A1/2 - F1;
N0 = X + F2;
M2 = 1;
M1 = A1/2 + F1;
M0 = X - F2;
/************************************************************************
Asignacion de Coeficientes de Cuadraticas
************************************************************************/
G = sqrt(G); /* Ponderacion de Ganancia */
/* En dos bicuadraticas */
/* Este metodo no da buenos */
/* resultados, ver informe */
COEF[K+0] = 0; /* SE */
COEF[K+1] = -G; /* B2 */
COEF[K+2] = 0; /* B1 */
COEF[K+3] = G; /* B0 */
COEF[K+4] = -1.0*N0; /* A2 */
COEF[K+5] = -1.0*N1; /* A1 */
COEF[K+6]  = 0; /* SE */
COEF[K+7]  = G; /* B2 */
COEF[K+8]  = 0; /* B1 */
COEF[K+9]  = G; /* B0 */
COEF[K+10] = -1.0*M0; /* A2 */
COEF[K+11] = -1.0*M1; /* A1 */
}
}

void __fastcall TForm7::BitBtn10Click(TObject *Sender)
{try{
SpeedButton2->Enabled=true;
int N;
ListBox2->Clear();
LineSeries2->Clear();

double FC1=StrToFloat(Edit15->Text);
double FC2=StrToFloat(Edit17->Text);
double FS=(double)1/(Form1->Frm);

 N=StrToInt(Edit16->Text);

COEF=new double [5*N*N+1];
COEF1=new double [5*N*N+1];



BP(FC1,FC2,FS,COEF,N);

for(int i=0;i<N/2;i++)
{int j=i*6;
float gain= sqrt(COEF[j+1]*COEF[j+1]);
ListBox2->Items->Add("ETAPA "+IntToStr(i+1));
ListBox2->Items->Add("--------------------------");
ListBox2->Items->Add("Num2:: "+FloatToStr(COEF[j+1]/gain));
COEF1[i*5]= COEF[j+1];
ListBox2->Items->Add("Num1:: "+FloatToStr(COEF[j+2]/gain));
COEF1[i*5+1]= COEF[j+2];
ListBox2->Items->Add("Num0:: "+FloatToStr(COEF[j+3]/gain));
COEF1[i*5+2]=COEF[j+3];
ListBox2->Items->Add("Den2:: "+FloatToStr(-COEF[j+4]));
COEF1[i*5+3]= COEF[j+4];
ListBox2->Items->Add("Den1:: "+FloatToStr(-COEF[j+5]));
COEF1[i*5+4]=COEF[j+5];
ListBox2->Items->Add("Ganancia:: "+FloatToStr(gain));
ListBox2->Items->Add("--------------------------");

}


double *X=new double [Form1->Series1->Count()*2];
double ACUM;
double *OUTq=new double [Form1->Series1->Count()+N*2];

for(int o1o=0;o1o<Form1->Series1->Count()+N*2;o1o++)
  X[o1o]=0;



int ii=0;
int q=0;

for(int pp=0;pp<Form1->Series1->Count();pp++)
{
ACUM=Form1->Series1->YValue[pp];


for(ii = 0; ii < N/2; ii++)       // Repetir por N bicuadraticas
{
q = ii*5;                             // Ajustar Indice de variables
X[q+2] = ACUM;                       // X[n] = Valor del ADC
									 // o ultimo filtro!
ACUM = COEF1[q+2]*X[q+2];                 // Y[n] = B0*X[n]
ACUM = ACUM + COEF1[q+1]*X[q+1];           // Y[n] = Y[n] + B1*X[n-1]
ACUM = ACUM + COEF1[q+0]*X[q+0];               // Y[n] = Y[n] + B2*X[n-2]
ACUM = ACUM + COEF1[q+3]*X[q+3];                   // Y[n] = Y[n] + A1*Y[n-1]
ACUM = ACUM + COEF1[q+4]*X[q+4];           // Y[n] = Y[n] + A2*Y[n-2]
X[q+0] = X[q+ 1];               // X[n-2] = X[n-1]
X[q+1] = X[q+ 2];                   // X[n-1] = X[n]
X[q+3] = X[q+ 4];                   // Y[n-2] = Y[n-1]
X[q+4] = ACUM;                     // Y[n-1] = Y[n]
}
OUTq[pp]=ACUM;
}
for(int c = 0; c < Form1->Series1->Count(); c++)

LineSeries2->AddXY((double)c*Form1->Frm,OUTq[c]);


delete COEF;
delete COEF1;
delete X;
delete OUTq;
}catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema con los par�metros de entrada. Por favor verifique el contenido de los mismos y vuelva a intentarlo.Si el problema contin�a contacte inmediatamante a los dise�adores.");}

}
//---------------------------------------------------------------------------

double cabs( complex z)
{
double o;
o=sqrt(z.x * z.x + z.y * z.y);
return o;
}




void __fastcall TForm7::BR(double FC1,double FC2,double FS,double *COEF,int N)
{
int I,J,K;
double WC,WC1,WC2,ANG,G,A1,A2,A3,A4,FC,CC,DEN;
double A,B,C,D,Q,R,X;
double M0,M1,M2,N0,N1,N2;
double L,F1,F2;
complex T,T1,T2,S1,S2;
WC1 = 2*PI*FC1/FS; /* Normalizacion de FC1 */
WC2 = 2*PI*FC2/FS; /* Normalizacion de FC2 */
CC = sin(WC1 + WC2)/(sin(WC1) + sin(WC2)); /* Calculo de F central */
WC = fabs( sin(WC2) / (cos(WC2) - CC)); /* Calculo de Wc */
J = N/2; /* Correguir Num de Biquad */
for(I = 1; I <= J; I++) /* Ciclo de Calculo */
{
K = (I - 1)*12; /* Indice en Arreglo */
ANG = PI*(N - 1 + 2*I)/(2*N); /* Angulo de Polos */
DEN = (1.0 - 2.0*WC*cos(ANG) + WC*WC);/* Calculo de Denominador */
G  = (WC*WC) / DEN; /* Calculo de G */
A1 = 4*CC*WC*(cos(ANG) - WC)/DEN; /* Calculo de A1*Z^-1 */
A2 = 2*(2*CC*CC*WC*WC + WC*WC - 1)/DEN;/* Calculo de A2*Z^-2 */
A3 = -4*CC*WC*(cos(ANG) + WC)/DEN; /* Calculo de A3*Z^-3 */
A4 = (1.0 + 2.0*WC*cos(ANG) + WC*WC)/DEN;/* Calculo de A4*Z^-4 */
/************************************************************************
Los coeficientes antes calculados son de una Ecuacion Cuartica
aqui los convertiremos en dos cuadraticas.
Ref. Pag 2-14 de Handbook of Engineering Fundamentals
 Eshbach
 Second Edition
 Wiley Handbook Series 1952.
 ISBN: No existia en esos tiempos
 (Las Matematicas nunca cambian...)
a0*X^4 + a1*X^3 + a2*X^2 + a3*X + a4 = 0
dividimos entre a0 para obtener
X^4 + a*X^3 + b*X^2 + c*X + d = 0
buscamos cualquier raiz real y1 de
8*Y^3 - 4*B*Y^2 + 2(A*C - 4*D)*Y - (C^2 + D*(A^2 - 4B)) = 0
entonces las dos cuadraticas son
x^2 + (a/2 - (a^2/4 + 2*y1 - b)^.5)*x + (y1 + (y1^2 - d)^.5) = 0
x^2 + (a/2 + (a^2/4 + 2*y1 - b)^.5)*x + (y1 + (y1^2 - d)^.5) = 0
para encontrar una raiz real de una cubica
32
a*x^3 + b*x^2 + c*x + d = 0
hacemos
q = a*c - b^2
r = 0.5*(3*a*b*c - a^2*d) - b^3
s1 = (r + (q^3 + r^2)^.5)^(1/3)
s2 = (r - (q^3 + r^2)^.5)^(1/3)
Entonces las raices son
x1 = (s1 + s2 - b)/a
x2 = (-.5(s1 + s2) + (-3)^(1/3)*(s1-s2)/2 -b)/a
x3 = (-.5(s1 + s2) - (-3)^(1/3)*(s1-s2)/2 -b)/a
************************************************************************/
/************************************************************************
Calculo de raiz real y1 de cubica
************************************************************************/
A = 8.0; /* A = 8 */
B = -4*A2/3; /* B = -4*a2/3 */
C = 2*(A1*A3 - 4*A4)/3; /* C = 2*(a1*a3 - 4*a4)/3 */
D = -1.0*(A3*A3+ A4*(A1*A1 - 4*A2)); /* D = ... */
Q = A*C - B*B; /* Calculo de Q */
R = 0.5*(3*A*B*C - A*A*D) - B*B*B; /* Calculo de R */
L = Q*Q*Q + R*R; /* Argumento de Raiz Cuad Sx*/
if (L > 0.0) /* Si es positiva */
{
T.x = sqrt(L); /* Resultado es Real */
T.y = 0.0; /* Imaginario = 0 */
}
else /* Si es Negativa */
{
T.x = 0.0; /* Real = 0 */
T.y = sqrt(fabs(L)); /* Resultado Imaginario */
}
T1.x = R + T.x; /* Calculo del Resto de S1 */
T1.y =     T.y;
T2.x = cabs(T1);
T2.y = atan2(T1.y,T1.x);
S1.x = pow(T2.x,1.0/3.0);
S1.y = T2.y / 3.0;
T1.x = R - T.x; /* Calculo del Resto de S2 */
T1.y =     T.y;
T2.x = cabs(T1);
T2.y = atan2(T1.y,T1.x);
S2.x = pow(T2.x,1.0/3.0);
S2.y = T2.y / 3.0;
/* Calculo de X1 (REAL */
X = (S1.x*cos(S1.y) + S2.x*cos(S2.y) - B)/A;
/************************************************************************
Calculo de Coeficientes de Cuadraticas
************************************************************************/

F1 = A1*A1/4 + 2*X - A2;
F1 = sqrt(F1);
F2 = X*X - A4;
F2 = sqrt(F2);
N2 = 1;
N1 = A1/2 - F1;
N0 = X + F2;
M2 = 1;
M1 = A1/2 + F1;
M0 = X - F2;
/************************************************************************
Asignacion de Coeficientes de Cuadraticas
************************************************************************/
G = sqrt(G); /* Ponderacion de Ganancia */
/* En dos bicuadraticas */
/* Este metodo no da buenos */
/* resultados, ver informe */
COEF[K+0] = 0; /* SE */
COEF[K+1] = G; /* B2 */
COEF[K+2] = -2*G; /* B1 */
COEF[K+3] = G; /* B0 */
COEF[K+4] = -1*N0; /* A2 */
COEF[K+5] = -1*N1; /* A1 */
COEF[K+6]  = 0; /* SE */
COEF[K+7]  = G; /* B2 */
COEF[K+8]  = -2*G; /* B1 */
COEF[K+9]  = G; /* B0 */
COEF[K+10] = -1*M0; /* A2 */
COEF[K+11] = -1*M1; /* A1 */
}
}


void __fastcall TForm7::BitBtn11Click(TObject *Sender)
{
try{
SpeedButton2->Enabled=true;
int N,T;
ListBox2->Clear();
LineSeries2->Clear();

double FC1=StrToFloat(Edit18->Text);
double FC2=StrToFloat(Edit20->Text);
double FS=(double)1/(Form1->Frm);

 N=StrToInt(Edit19->Text);

COEF=new double [5*N*N+1];
COEF1=new double [5*N*N+1];

BR(FC1,FC2,FS,COEF,N);

for(int i=0;i<N/2;i++)
{int j=i*6;
float gain= sqrt(COEF[j+1]*COEF[j+1]);
ListBox2->Items->Add("ETAPA "+IntToStr(i+1));
ListBox2->Items->Add("--------------------------");
ListBox2->Items->Add("Num2:: "+FloatToStr(COEF[j+1]/gain));
COEF1[i*5]= COEF[j+1];
ListBox2->Items->Add("Num1:: "+FloatToStr(COEF[j+2]/gain));
COEF1[i*5+1]= COEF[j+2];
ListBox2->Items->Add("Num0:: "+FloatToStr(COEF[j+3]/gain));
COEF1[i*5+2]=COEF[j+3];
ListBox2->Items->Add("Den2:: "+FloatToStr(-COEF[j+4]));
COEF1[i*5+3]= COEF[j+4];
ListBox2->Items->Add("Den1:: "+FloatToStr(-COEF[j+5]));
COEF1[i*5+4]=COEF[j+5];
ListBox2->Items->Add("Ganancia:: "+FloatToStr(gain));
ListBox2->Items->Add("--------------------------");
}


double *X=new double [Form1->Series1->Count()*2];
double ACUM;
double *OUTq=new double [Form1->Series1->Count()+N*2];

for(int o1o=0;o1o<Form1->Series1->Count()+N*2;o1o++)
  X[o1o]=0;



int ii=0;
int q=0;

for(int pp=0;pp<Form1->Series1->Count();pp++)
{
ACUM=Form1->Series1->YValue[pp];


for(ii = 0; ii < N/2; ii++)       // Repetir por N bicuadraticas
{
q = ii*5;                             // Ajustar Indice de variables
X[q+2] = ACUM;                       // X[n] = Valor del ADC
									 // o ultimo filtro!
ACUM = COEF1[q+2]*X[q+2];                 // Y[n] = B0*X[n]
ACUM = ACUM + COEF1[q+1]*X[q+1];           // Y[n] = Y[n] + B1*X[n-1]
ACUM = ACUM + COEF1[q+0]*X[q+0];               // Y[n] = Y[n] + B2*X[n-2]
ACUM = ACUM + COEF1[q+3]*X[q+3];                   // Y[n] = Y[n] + A1*Y[n-1]
ACUM = ACUM + COEF1[q+4]*X[q+4];           // Y[n] = Y[n] + A2*Y[n-2]
X[q+0] = X[q+ 1];               // X[n-2] = X[n-1]
X[q+1] = X[q+ 2];                   // X[n-1] = X[n]
X[q+3] = X[q+ 4];                   // Y[n-2] = Y[n-1]
X[q+4] = ACUM;                     // Y[n-1] = Y[n]
}
OUTq[pp]=ACUM;
}
for(int c = 0; c < Form1->Series1->Count(); c++)

LineSeries2->AddXY((double)c*Form1->Frm,OUTq[c]);


delete COEF;
delete COEF1;
delete X;
delete OUTq;
}catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema con los par�metros de entrada. Por favor verifique el contenido de los mismos y vuelva a intentarlo.Si el problema contin�a contacte inmediatamante a los dise�adores.");}

}
//---------------------------------------------------------------------------



void __fastcall TForm7::BitBtn5Click(TObject *Sender)
{
try{
SpeedButton2->Enabled=true;
int N,T;
ListBox2->Clear();
LineSeries2->Clear();

double FC=StrToFloat(Edit11->Text);
double FS=(double)1/(Form1->Frm);

 N=StrToInt(Edit12->Text);
int kk=5*N*2;
COEF=new double [kk];
COEF1=new double [kk];

LPHP(FC,FS,COEF,N,0);

for(int i=0;i<N/2;i++)
{int j=i*6;
float gain= sqrt(COEF[j+1]*COEF[j+1]);
ListBox2->Items->Add("ETAPA "+IntToStr(i+1));
ListBox2->Items->Add("--------------------------");
ListBox2->Items->Add("Num2:: "+FloatToStr(COEF[j+1]/gain));
COEF1[i*5]= COEF[j+1];
ListBox2->Items->Add("Num1:: "+FloatToStr(COEF[j+2]/gain));
COEF1[i*5+1]= COEF[j+2];
ListBox2->Items->Add("Num0:: "+FloatToStr(COEF[j+3]/gain));
COEF1[i*5+2]=COEF[j+3];
ListBox2->Items->Add("Den2:: "+FloatToStr(-COEF[j+4]));
COEF1[i*5+3]= COEF[j+4];
ListBox2->Items->Add("Den1:: "+FloatToStr(-COEF[j+5]));
COEF1[i*5+4]=COEF[j+5];
ListBox2->Items->Add("Ganancia:: "+FloatToStr(gain));
ListBox2->Items->Add("--------------------------");
}
/*
for(int ir=0;ir<ListBox2->Count;ir++)
{
COEF1[ir]=StrToFloat(ListBox2->Items->Strings[ir]);

}   */



double *X=new double [Form1->Series1->Count()*2];
double ACUM;
double *OUTq=new double [Form1->Series1->Count()+N*2];





for(int o1o=0;o1o<Form1->Series1->Count()+N*2;o1o++)
  X[o1o]=0;






int ii=0;
int q=0;

for(int pp=0;pp<Form1->Series1->Count();pp++)
{
ACUM=Form1->Series1->YValue[pp];


for(ii = 0; ii < N/2; ii++)       // Repetir por N bicuadraticas
{
q = ii*5;                             // Ajustar Indice de variables
X[q+2] = ACUM;                       // X[n] = Valor del ADC
									 // o ultimo filtro!
ACUM = COEF1[q+2]*X[q+2];                 // Y[n] = B0*X[n]
ACUM = ACUM + COEF1[q+1]*X[q+1];           // Y[n] = Y[n] + B1*X[n-1]
ACUM = ACUM + COEF1[q+0]*X[q+0];               // Y[n] = Y[n] + B2*X[n-2]
ACUM = ACUM + COEF1[q+3]*X[q+3];                   // Y[n] = Y[n] + A1*Y[n-1]
ACUM = ACUM + COEF1[q+4]*X[q+4];           // Y[n] = Y[n] + A2*Y[n-2]
X[q+0] = X[q+ 1];               // X[n-2] = X[n-1]
X[q+1] = X[q+ 2];                   // X[n-1] = X[n]
X[q+3] = X[q+ 4];                   // Y[n-2] = Y[n-1]
X[q+4] = ACUM;                     // Y[n-1] = Y[n]
}
OUTq[pp]=ACUM;
}
for(int c = 0; c < Form1->Series1->Count(); c++)

LineSeries2->AddXY((double)c*Form1->Frm,OUTq[c]);


delete COEF;
delete COEF1;
delete X;
delete OUTq;
}catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema con los par�metros de entrada. Por favor verifique el contenido de los mismos y vuelva a intentarlo.Si el problema contin�a contacte inmediatamante a los dise�adores.");}

}
//---------------------------------------------------------------------------


double WIN(int I,int N,int VEN)

{
double TEMP;
switch(VEN) /* Que Tipo de Ventana? */
{
case 1: /* Ventana: Rectangular */
TEMP = 1.0; /* Calcular Valor */
break;
case 2: /* Ventana: Hanning */
TEMP = 0.50 + 0.50*cos(2*PI*I/N);
break;
case 3: /* Ventana: Hamming */
TEMP = 0.540 + 0.460*cos(2*PI*I/N);
break;
case 4: /* Ventana: Blackman */
TEMP = 0.42 + 0.50*cos(2*PI*I/N) + 0.08*cos(4*PI*I/N);
break;
}
return TEMP; /* Retornar Resultado */
}



 void  HP_FIR(double FC,double FS,double *COEF,int N,int VEN)
{
int I,J,K;
double TEMP,WC;
FC = FC/FS; /* Normalizar F-corte */
WC = 2*PI*FC; /* Calcular W-corte */
J = -1*N/2; /* Limite Inferior */
K = N/2; /* Limite Superior */
for(I = J; I <= K; I++) /* Ciclo de Calculo */
{
if (I != 0) /* Si I <> 0 */
{
TEMP = -sin(I*WC); /* Calcular Nominador */
TEMP = TEMP/(PI*I); /* Dividir por Denominador */
COEF[I+K] = TEMP*WIN(I,N,VEN); /* Ponderar por Ventana */
}
else /* Cuando I = 0 */
/* Calcular y Ponderar */
COEF[I+K] = 1 - WC*WIN(I,N,VEN)/PI;
}
}




void  LP_FIR(double FC,double FS,double *COEF,int N,int VEN)
{
int I,J,K;
double TEMP,WC;
FC = FC/FS; /* Normalizar F-corte */
WC = 2*PI*FC; /* Calcular W-corte */

J = -1*N/2; /* Limite Inferior */
K = N/2; /* Limite Superior */
for(I = J; I <= K; I++) /* Ciclo de Calculo */
{
if (I != 0) /* Si I <> 0 */
{
TEMP = sin(I*WC); /* Calcular Nominador */
TEMP = TEMP/(PI*I); /* Dividir por Denominador */
COEF[I+K] = TEMP*WIN(I,N,VEN); /* Ponderar por Ventana */
}
else /* Cuando I = 0 */
COEF[I+K] = WC*WIN(I,N,VEN)/PI; /* Calcular y Ponderar */
}
}
void __fastcall TForm7::SpeedButton3Click(TObject *Sender)
{
String AA= "Reemplazar serie principal " ;
String s ="�Est� seguro que desea reemplazar la serie principal de este proyecto por una nueva.?";

int a=Application->MessageBoxA(s.w_str(),AA.w_str(),MB_YESNO+MB_ICONWARNING);
 if(a==IDYES )
 {


Form1->Series1->Clear();
for(int i=0;i<LineSeries4->Count();i++)


Form1->Series1->AddXY(LineSeries4->XValue[i],LineSeries4->YValue[i]);

Form1->OldXs=Form1->Series1->MaxXValue();
Form1->OldYs=Form1->Series1->YValue[Form1->Series1->LastValueIndex];
} this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm7::ListBox1Click(TObject *Sender)
{
int indice=ListBox1->ItemIndex;
if(indice<ListBox1->GetCount())
Form1->StatusBar1->Panels->Items[0]->Text=  ListBox1->Items->Strings[indice].t_str();

}
//---------------------------------------------------------------------------

void __fastcall TForm7::ListBox2Click(TObject *Sender)
{
int indice=ListBox2->ItemIndex;
if(indice<ListBox2->GetCount())
Form1->StatusBar1->Panels->Items[0]->Text=  ListBox2->Items->Strings[indice].t_str();

}
//---------------------------------------------------------------------------

void __fastcall TForm7::BitBtn12Click(TObject *Sender)
{
try{
  double *COEF;
SpeedButton3->Enabled=true;
int N,VEN;
ListBox1->Clear();
LineSeries4->Clear();
LineSeries5->Clear();

double FC=StrToFloat(Edit7->Text);
double FS=(double)1/(Form1->Frm);

 N=StrToInt(Edit4->Text);

 VEN= ComboBox3->ItemIndex+1;
  COEF=new double [2*N];

 HP_FIR( FC, FS, COEF, N, VEN);


 int g;
for(g=0;g<=(N);g++)
{
ListBox1->Items->Add(FloatToStr(COEF[g]));
LineSeries5->AddXY(g,COEF[g]);
}


 //Flitrando---------------------




double r;
double *OUTq= new double [Form1->Series1->Count()*2];
double *INq= new double [(Form1->Series1->Count()+N*2)];

int q=0;
for(int o1o=0;o1o<Form1->Series1->Count()+N*2;o1o++)
  INq[o1o]=0;

for(int oo=0;oo<Form1->Series1->Count();oo++)
  INq[oo]= Form1->Series1->YValue[oo];

for(int pp=0;pp<Form1->Series1->Count();pp++)
		{
			r = 0;
			for (int k=0; k<N; k++)
			{r = r + INq[pp+k] * COEF[k];


			}
			OUTq[pp]= r;
		}

for(int c = 0; c < Form1->Series1->Count(); c++)

LineSeries4->AddXY((double)c*Form1->Frm,OUTq[c]);


delete COEF;
delete COEF1;
delete OUTq;
        }catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema con los par�metros de entrada. Por favor verifique el contenido de los mismos y vuelva a intentarlo.Si el problema contin�a contacte inmediatamante a los dise�adores.");}


}
//---------------------------------------------------------------------------

void __fastcall TForm7::BitBtn15Click(TObject *Sender)
{
try{
double *COEF;
SpeedButton3->Enabled=true;
int N,VEN;
ListBox1->Clear();
LineSeries4->Clear();
LineSeries5->Clear();

double FC1=StrToFloat(Edit1->Text);
double FC2=StrToFloat(Edit9->Text);
double FS=(double)1/(Form1->Frm);

 N=StrToInt(Edit2->Text);

 VEN= ComboBox2->ItemIndex+1;
  COEF=new double [2*N];

 BP_FIR( FC1,FC2, FS, COEF, N, VEN);


 int g;
for(g=0;g<=(N);g++)
{
ListBox1->Items->Add(FloatToStr(COEF[g]));
LineSeries5->AddXY(g,COEF[g]);
}


 //Flitrando---------------------




double r;
double *OUTq= new double [Form1->Series1->Count()*2];
double *INq= new double [(Form1->Series1->Count()+N*2)];

int q=0;
for(int o1o=0;o1o<Form1->Series1->Count()+N*2;o1o++)
  INq[o1o]=0;

for(int oo=0;oo<Form1->Series1->Count();oo++)
  INq[oo]= Form1->Series1->YValue[oo];

for(int pp=0;pp<Form1->Series1->Count();pp++)
		{
			r = 0;
			for (int k=0; k<N; k++)
			{r = r + INq[pp+k] * COEF[k];


			}
			OUTq[pp]= r;
		}

for(int c = 0; c < Form1->Series1->Count(); c++)

LineSeries4->AddXY((double)c*Form1->Frm,OUTq[c]);


delete COEF;
delete COEF1;
delete OUTq;
}catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema con los par�metros de entrada. Por favor verifique el contenido de los mismos y vuelva a intentarlo.Si el problema contin�a contacte inmediatamante a los dise�adores.");}

}
//---------------------------------------------------------------------------


void BP_FIR(double FC1,double FC2,double FS,double *COEF,int N,int VEN)
 {
int I,J,K;
double TEMP,WC1,WC2;
FC1 = FC1/FS; /* Normalizar F-corte1 */
FC2 = FC2/FS; /* Normalizar F-corte2 */
WC1 = 2*PI*FC1; /* Calcular W-corte1 */
WC2 = 2*PI*FC2; /* Calcular W-corte2 */
J = -1*N/2; /* Limite Inferior */
K = N/2; /* Limite Superior */
for(I = J; I <= K; I++) /* Ciclo de Calculo */
if (I != 0) /* Si I <> 0 */
{
TEMP = sin(I*WC2) - sin(I*WC1); /* Calcular Nominador */
TEMP = TEMP/(PI*I);/* Dividir por Denominador */
COEF[I+K] = TEMP*WIN(I,N,VEN); /* Ponderar por Ventana */
}
else /* Si I = 0 */
/* Calcular y Ponderar */
COEF[I+K] = (WC2 - WC1)*WIN(I,N,VEN)/PI;
}



void BR_FIR(double FC1,double FC2,double FS,double *COEF,int N,int VEN)
{
int I,J,K;
double TEMP,WC1,WC2;
FC1 = FC1/FS; /* Normalizar F-corte1 */
FC2 = FC2/FS; /* Normalizar F-corte2 */

WC1 = 2*PI*FC1; /* Calcular W-corte1 */
WC2 = 2*PI*FC2; /* Calcular W-corte2 */
J = -1*N/2; /* Limite Inferior */
K = N/2; /* Limite Superior */
for(I = J; I <= K; I++) /* Ciclo de Calculo */
if (I != 0) /* Si I <> 0 */
{ /* Calcular Nominador */
TEMP = -1.0*(sin(I*WC2) - sin(I*WC1));
TEMP = TEMP/(PI*I);/* Dividir por Denominador */
COEF[I+K] = TEMP*WIN(I,N,VEN); /* Ponderar por Ventana */
}
else /* Si I = 0 */
/* Calcular y Ponderar */
COEF[I+K] = 1 - 1.0*(WC2 - WC1)*WIN(I,N,VEN)/PI;
}




void __fastcall TForm7::BitBtn16Click(TObject *Sender)
{
try{
double *COEF;
SpeedButton3->Enabled=true;
int N,VEN;
ListBox1->Clear();
LineSeries4->Clear();
LineSeries5->Clear();

double FC1=StrToFloat(Edit3->Text);
double FC2=StrToFloat(Edit10->Text);
double FS=(double)1/(Form1->Frm);

 N=StrToInt(Edit8->Text);

 VEN= ComboBox4->ItemIndex+1;
  COEF=new double [2*N];

 BR_FIR( FC1,FC2, FS, COEF, N, VEN);


 int g;
for(g=0;g<=(N);g++)
{
ListBox1->Items->Add(FloatToStr(COEF[g]));
LineSeries5->AddXY(g,COEF[g]);
}


 //Flitrando---------------------




double r;
double *OUTq= new double [Form1->Series1->Count()*2];
double *INq= new double [(Form1->Series1->Count()+N*2)];

int q=0;
for(int o1o=0;o1o<Form1->Series1->Count()+N*2;o1o++)
  INq[o1o]=0;

for(int oo=0;oo<Form1->Series1->Count();oo++)
  INq[oo]= Form1->Series1->YValue[oo];

for(int pp=0;pp<Form1->Series1->Count();pp++)
		{
			r = 0;
			for (int k=0; k<N; k++)
			{r = r + INq[pp+k] * COEF[k];


			}
			OUTq[pp]= r;
		}

for(int c = 0; c < Form1->Series1->Count(); c++)

LineSeries4->AddXY((double)c*Form1->Frm,OUTq[c]);


delete COEF;
delete COEF1;
delete OUTq;
}catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema con los par�metros de entrada. Por favor verifique el contenido de los mismos y vuelva a intentarlo.Si el problema contin�a contacte inmediatamante a los dise�adores.");}

}
//---------------------------------------------------------------------------



void NOTCH(double FN,double AF,double FS,double *COEF)
{
int I=0,J,K;
double A1,A2,B,WC;

K = I*6; /* Indice en Arreglo */
B = 1.0 / (1.0 + tan(PI*AF/FS)); /* Calculo de Ancho de Banda */
WC = 2*PI*FN/FS; /* Calculo de Freq. Central */
A1 = -2.0*B*cos(WC); /* Calculo de A1 */
A2 = (2*B-1.0); /* Calculo de A2 */
COEF[K+0] = 0; /* SE */
COEF[K+1] = B; /* B2 */
COEF[K+2] = -2*B*cos(WC); /* B1 */
COEF[K+3] = B; /* B0 */
COEF[K+4] = -1*A2; /* A2 */
COEF[K+5] = -1*A1; /* A1 */

}

void __fastcall TForm7::BitBtn17Click(TObject *Sender)
{
try{
SpeedButton2->Enabled=true;
int N,T;
ListBox2->Clear();
LineSeries2->Clear();

double FN=StrToFloat(Edit21->Text);
double AF=StrToFloat(Edit22->Text);
double FS=(double)1/(Form1->Frm);



COEF=new double [10];
COEF1=new double [10];
double *acoefs=new double [10];
double *bcoefs=new double [10];
double *magna=new double [(int)FS];
double *angle=new double [(int)FS];
NOTCH( FN, AF, FS, COEF);

for(int i=0;i<1;i++)
{int j=i*6;
float gain= sqrt(COEF[j+1]*COEF[j+1]);
ListBox2->Items->Add("ETAPA 1");
ListBox2->Items->Add("--------------------------");
ListBox2->Items->Add("Num2:: "+FloatToStr(COEF[j+1]/gain));
COEF1[i]=COEF[j+1];
ListBox2->Items->Add("Num1:: "+FloatToStr(COEF[j+2]/gain));
COEF1[i+1]=COEF[j+2];
ListBox2->Items->Add("Num0:: "+FloatToStr(COEF[j+3]/gain));
COEF1[i+2]=COEF[j+3];
ListBox2->Items->Add("Den2:: "+FloatToStr(-COEF[j+4]));
COEF1[i+3]=COEF[j+4];
ListBox2->Items->Add("Den1:: "+FloatToStr(-COEF[j+5]));
COEF1[i+4]=COEF[j+5];
ListBox2->Items->Add("Ganancia:: "+FloatToStr(gain));
ListBox2->Items->Add("--------------------------");
}

/*
for(int ir=0;ir<ListBox2->Count;ir++)
{
COEF1[ir]=StrToFloat(ListBox2->Items->Strings[ir]);

}   */

double *X=new double [6];
double ACUM;
double *OUTq=new double [Form1->Series1->Count()*2];



int ii=0;
int q=0;

for(int pp=0;pp<Form1->Series1->Count();pp++)
{
ACUM=Form1->Series1->YValue[pp];


for(ii = 0; ii < 1; ii++)       // Repetir por N bicuadraticas
{
q = ii*5;                             // Ajustar Indice de variables
X[q+2] = ACUM;                       // X[n] = Valor del ADC
									 // o ultimo filtro!
ACUM = COEF1[q+2]*X[q+2];                 // Y[n] = B0*X[n]
ACUM = ACUM + COEF1[q+1]*X[q+1];           // Y[n] = Y[n] + B1*X[n-1]
ACUM = ACUM + COEF1[q+0]*X[q+0];               // Y[n] = Y[n] + B2*X[n-2]
ACUM = ACUM + COEF1[q+3]*X[q+3];                   // Y[n] = Y[n] + A1*Y[n-1]
ACUM = ACUM + COEF1[q+4]*X[q+4];           // Y[n] = Y[n] + A2*Y[n-2]
X[q+0] = X[q+ 1];               // X[n-2] = X[n-1]
X[q+1] = X[q+ 2];                   // X[n-1] = X[n]
X[q+3] = X[q+ 4];                   // Y[n-2] = Y[n-1]
X[q+4] = ACUM;                     // Y[n-1] = Y[n]
}
OUTq[pp]=ACUM;
}
for(int c = 0; c < Form1->Series1->Count(); c++)

LineSeries2->AddXY((double)c*Form1->Frm,OUTq[c]);


delete COEF;
delete COEF1;
delete X;
delete OUTq;
}catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema con los par�metros de entrada. Por favor verifique el contenido de los mismos y vuelva a intentarlo.Si el problema contin�a contacte inmediatamante a los dise�adores.");}

}
//---------------------------------------------------------------------------


int IIR_Resp(double  *acoefs,double *bcoefs,double *magna,double *angle,int tot_pts,int order)
{ int     c,f,q;        /*  loop counters */
  double  rad2deg,      /*  rad to deg conversion */
          omega,omega2, /*  radian freq and square */
          rea,img;      /*  real and imag part */
  //Form7->Series1->Clear();
  rad2deg = 180.0 / PI; /*  set rad2deg */
  /*  Loop through each of the frequencies */
  for(f = 0 ;f < tot_pts; f++)
  { /*  Initialize magna and angle */
	magna[f] = 1;   //gain;
	angle[f] = 0.0;
    /*  Pre calc omega and omega squared */
	omega = 2*PI * f/250;
	omega2 = omega * omega;
    /*  Loop through coefs for each quadratic */
	for(q = 0 ;q < (order+1)/2; q++)
	{ /*  c is coef index = 3 * quad index */
	  c = q * 3;
      /* Numerator values */
	  rea = acoefs[c+2] - acoefs[c] * omega2;
	  img = acoefs[c+1] * omega;
	  magna[f] *= sqrt(rea*rea + img*img);
	  angle[f] += atan2(img,rea);
	  /* Denominator values */
	  rea = bcoefs[c+2] - bcoefs[c] * omega2;
	  img = bcoefs[c+1] * omega;
	  magna[f] /= sqrt(rea*rea + img*img);
	  angle[f] -= atan2(img,rea);
    }
	/* Convert to degrees */
	angle[f] *= rad2deg;
  }
  /*  Convert magnitude response to dB if indicated */

   for(f = 0 ;f < tot_pts; f++)
	{ /* Handle very small numbers */
	  if(magna[f] < 0.00000000001)
	  { magna[f] = 0.00000000001;}
	  magna[f] = 20 * log10(magna[f]);

	  //Form7->Series1->AddXY(1/Form1->Frm/2*f/(250/2),magna[f]);
	}

  return 1;
}



