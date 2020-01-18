//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#define PI 3.1416
#pragma hdrstop
#include "Unit1.h"
#include "Unit5.h"
#include "Unit6.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------




void __fastcall TForm5::SpeedButton2Click(TObject *Sender)
{

try{

double *A=new double [100000];
double *B=new double [100000];
for(long int t=0;t<100000;t++)
{
A[t]=0;
B[t]=0;

}
 A=Form1->ECG_01;

  int x1=0;
  int a=0;
  float i=0;

float inc=0;
float fd=StrToFloat(Edit1->Text)/60;
float Armonicos=StrToFloat(Edit2->Text);
float Amp=StrToFloat(Edit3->Text);
float Offset=StrToFloat(Edit4->Text);
int fs=1/Form1->Frm;
int x=0;



for(int ar=0;ar<Armonicos;ar++)
 {
//******************************

if(CheckBox2->Checked==true)
{
int dif=StrToInt(Edit38->Text)-StrToInt(Edit37->Text);
if (dif<0)
	ShowMessage("Error par�metros no v�lidos. Desde>Hasta");

fd=StrToInt(Edit37->Text)+rand()%dif;
//ShowMessage(FloatToStr(fd));
fd=(float)fd/60;
}
 inc=0.0;
 inc= (fd*1000)/fs;
 int l=0;

 x=0;

  a=0;
   i=0;
while(i<1000)
{

 l=( int)i;
 B[x]=((((A[l]+A[l+1])/2))*Amp)+ Offset;

 x++ ;
 i=i+inc;

}

//*******************************
 //ShowMessage(FloatToStr(fd*60));
 if (fd<1)
 {
for(int f=0;f<fd;f++)
  { a=0;
 while(a<x)
 {

   Form1->Series1->AddXY(Form1->OldXs+x1*Form1->Frm,B[a]);
   x1++;
   a++;
 }
 }
 }else
 {
  for(int f=0;f<(int)fd;f++)
  { a=0;
 while(a<x)
 {

   Form1->Series1->AddXY(Form1->OldXs+x1*Form1->Frm,B[a]);
   x1++;
   a++;
 }
 }
 }


 }
 HRV=false;

  Form1->OldXs=Form1->Series1->MaxXValue();
  Form1->OldYs=Form1->Series1->YValue[Form1->Series1->LastValueIndex];


 Form1->AjustaChart(Form1->Series1->MinYValue(),Form1->Series1->MaxYValue(),0, Form1->OldXs);

  Form1->StatusBar1->Panels->Items[5]->Text=" <N> "+IntToStr(Form1->Series1->Count());

 Form1->ListBox1->Items->Add(" ");
 Form1->ListBox1->Items->Add(">> ::Se�al de ECG::");
 String S2="  -- Latidos/minutos :: "+FloatToStr(fd*60);
 Form1->ListBox1->Items->Add(S2);
 String S3="  -- Amplitud deseada :: "+FloatToStr(Amp)+" V";
 Form1->ListBox1->Items->Add(S3);
 String S4="  -- Repetir :: "+FloatToStr(Armonicos)+" veces";
 Form1->ListBox1->Items->Add(S4);
 String S5="  -- Offset (V) :: "+FloatToStr(Offset)+" V";
 Form1->ListBox1->Items->Add(S5);

   //********FFT***** ***************************

 Form1->FFT_L();

 Form1->ListBox1->Items->Add(" ");
 String S6="    ::FFT Aplicada :: ";
 Form1->ListBox1->Items->Add(S6);
 String S7="      -- Numero de puntos FFT :: " +IntToStr(Form1->nFFT);
 Form1->ListBox1->Items->Add(S7);
 Form1-> Action10->Enabled=1;
 }catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema con los par�metros de entrada. Por favor verifique el contenido de los mismos y vuelva a intentarlo.");}

 Form5->Close();

}
//---------------------------------------------------------------------------

void __fastcall TForm5::SpeedButton1Click(TObject *Sender)
{
Form6->Show();
}
//---------------------------------------------------------------------------


void __fastcall TForm5::SpeedButton3Click(TObject *Sender)
{
try{
int i=0;

float fd=StrToFloat(Edit9->Text);
float Durac=StrToFloat(Edit10->Text);
float Fase=StrToFloat(Edit25->Text);
float Amp=StrToFloat(Edit11->Text);
float Offset=StrToFloat(Edit12->Text);
float fs=Form1->FM;
Form1->ERROR_FRM((int)fd);

double *B=new double [fs*Durac+100];

while(i<Durac*Form1->FM)
{
B[i]=Amp*sin(2*PI*i/fs*fd+Fase)+Offset;

Form1->Series1->AddXY((double)Form1->OldXs+i*Form1->Frm,B[i]);
i=i++;
}


  Form1->OldXs=Form1->Series1->MaxXValue();
  Form1->OldYs=Form1->Series1->YValue[Form1->Series1->LastValueIndex];


  Form1->AjustaChart(Form1->Series1->MinYValue(),Form1->Series1->MaxYValue(),0, Form1->OldXs);

  Form1->StatusBar1->Panels->Items[5]->Text=" <N> "+IntToStr(Form1->Series1->Count());


 Form1->ListBox1->Items->Add(" ");
  String S1=">>Se�al Seno::";
 Form1->ListBox1->Items->Add(S1);
 String S2="  -- Frecuencia :: "+FloatToStr(fd)+ " Hz";
 Form1->ListBox1->Items->Add(S2);
 String S3="  -- Amplitud deseada :: "+FloatToStr(Amp)+" V";
 Form1->ListBox1->Items->Add(S3);
 String S4="  -- Duraci�n :: "+FloatToStr(Durac)+" segundos";
 Form1->ListBox1->Items->Add(S4);
 String S5="  -- Offset (V) :: "+FloatToStr(Offset)+" V";
 Form1->ListBox1->Items->Add(S5);

 Form1->FFT_L();

 Form1->ListBox1->Items->Add("");
  String S6="    ::FFT Aplicada :: ";
 Form1->ListBox1->Items->Add(S6);
 String S7="      -- Numero de puntos FFT :: " +IntToStr(Form1->nFFT);
 Form1->ListBox1->Items->Add(S7);

 Form1-> Action10->Enabled=1;
}catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema con los par�metros de entrada. Por favor verifique el contenido de los mismos y vuelva a intentarlo.");}

  Form5->Close();
}
//---------------------------------------------------------------------------


 void __fastcall TForm5::Triangular(float Amp,float offset,float t_s, float t_b,int rep)
{
float A_t=0.0;
float cuenta=0;
float frec=1/(t_s+t_b);

int Count=1/Form1->Frm;
Data = new double [Count];




 float Rate=(float)Count*frec;

 A_t=1/Rate;
 cuenta= (float)t_s/A_t ;

 //Form1->Frm= A_t;
 int i;
 int j;

 for(j=0; j<1;j++)
 {
 for (i = (Count)*j; i < (cuenta+(Count)*j); i++)
 {
  Data[i]=(double)(offset+(i-Count*j)*Amp/cuenta);
 }

 for (i = cuenta+Count*j;i < Count*(j+1); i++)
 {
  Data[i]=(double)(offset+Amp-((i-(cuenta+Count*j))*Amp/(Count-cuenta)));
 }


 }


int x=0;
for(int h=0;h<rep;h++)
for(int t=0;t<Count;t++)
{

Form1->Series1->AddXY(Form1->OldXs+x*Form1->Frm,Data[t]);
x++;

}
}


void __fastcall TForm5::SpeedButton7Click(TObject *Sender)
{
try{
Form1-> ERROR1++;
float t_s=StrToFloat(Edit5->Text);
float t_c=StrToFloat(Edit6->Text);
float Amp=StrToFloat(Edit7->Text);
float offset=StrToFloat(Edit8->Text);
int rep=StrToInt(Edit26->Text);
Triangular(Amp,offset,t_s,t_c,rep);
Form1->OldXs=Form1->Series1->MaxXValue();
Form1->OldYs=Form1->Series1->YValue[Form1->Series1->LastValueIndex];

 Form1->AjustaChart(Form1->Series1->MinYValue(),Form1->Series1->MaxYValue(),0, Form1->OldXs);

}
catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema con los par�metros de entrada. Por favor verifique el contenido de los mismos y vuelva a intentarlo.");}
this ->Close();


}
//---------------------------------------------------------------------------


void __fastcall TForm5::SpeedButton5Click(TObject *Sender)
{try{
Form1-> ERROR1++;
float frec=StrToFloat(Edit21->Text);
float dutycicle=StrToFloat(Edit22->Text);
float Amp=StrToFloat(Edit23->Text);
float offset=StrToFloat(Edit24->Text);
int rep=StrToInt(Edit31->Text);
Cuadrada( Amp, offset, frec,  dutycicle,rep);
Form1->OldXs=Form1->Series1->MaxXValue();
Form1->OldYs=Form1->Series1->YValue[Form1->Series1->LastValueIndex];

 Form1->AjustaChart(Form1->Series1->MinYValue(),Form1->Series1->MaxYValue(),0, Form1->OldXs);
 }
 catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema con los par�metros de entrada. Por favor verifique el contenido de los mismos y vuelva a intentarlo.");}

 this ->Close();

}
//---------------------------------------------------------------------------

void __fastcall TForm5::Cuadrada(float Amp,float offset,float frec, float dutycicle,int rep)
 {

int Count=Form1->FM;
Data = new double [Count];

 float cuenta;

 cuenta= (float)Count*((double)dutycicle/100);

 int i;
 int j;

 if(RadioGroup1->ItemIndex==0){

 for(j=0; j<1;j++)
 {
 for (i = (Count)*j; i < (cuenta+(Count)*j); i++)
 {
  Data[i]=(double)Amp+offset;
 }

 for (i = cuenta+Count*j;i < Count*(j+1); i++)
 {
  Data[i]=(double)offset;
 }


 }

 }else
 {
   for(j=0; j<1;j++)
 {


 for (i = cuenta+Count*j;i < Count*(j+1); i++)
 {Data[i]=(double)Amp+offset;

 }

 for (i = (Count)*j; i < (cuenta+(Count)*j); i++)
 {
 Data[i]=(double)offset;
 }

 }


 }



int x=0;
float g=Count*frec/Form1->FM;
//Form1->Frm=(double)1/g;
for(int h=0;h<rep;h++)
for(int a=0;a<frec;a++)

 for(float t=0;t<Count;t=t+g)
{
Form1->Series1->AddXY((Form1->OldXs+(double)x/Form1->FM),Data[(int)t]);


x++;

}
Form1->OldXs=Form1->Series1->MaxXValue();
Form1->OldYs=Form1->Series1->YValue[Form1->Series1->LastValueIndex];


}
void __fastcall TForm5::SpeedButton6Click(TObject *Sender)
{

try{
Form1-> ERROR1++;
float Amp=StrToFloat(Edit17->Text);
float offset=StrToFloat(Edit19->Text);
float t_s=StrToFloat(Edit20->Text);
int rep=StrToInt(Edit32->Text);
Diente_Sierra( Amp, offset, t_s,rep);
Form1->OldXs=Form1->Series1->MaxXValue();
Form1->OldYs=Form1->Series1->YValue[Form1->Series1->LastValueIndex];

 Form1->AjustaChart(Form1->Series1->MinYValue(),Form1->Series1->MaxYValue(),0, Form1->OldXs);
 }
 catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema con los par�metros de entrada. Por favor verifique el contenido de los mismos y vuelva a intentarlo.");}


 this ->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Diente_Sierra(float Amp,float offset,float time, int rep)
{
float frec=1/time;

int Count=1/Form1->Frm;
Data = new double [Count];

float Rate=(float)Count*frec;
Form1->Frm=1/Rate;
 if(RadioGroup2->ItemIndex==0)
 {
 for(int j=0; j<1;j++)
 {
 for (int i = (Count)*j; i < ((Count)*(j+1)); i++)
 {
  Data[i]=(double)(offset+(i-Count*j)*Amp/Count);
 }

 }

 int x=0;

for(int h=0;h<rep;h++)
for(int t=0;t<Count;t++)
{
Form1->Series1->AddXY(Form1->OldXs+x/Rate,Data[t]);
x++;
}



}
else
{
 for(int j=0; j<1;j++)
 {
 for (int i = (Count)*j; i < ((Count)*(j+1)); i++)
 {
  Data[i]=(double)(offset+Amp-((i-(Count*j))*Amp/(Count)));
 }

 }

 int x=0;

for(int h=0;h<rep;h++)
for(int t=0;t<Count;t++)
{
Form1->Series1->AddXY(Form1->OldXs+x/Rate,Data[t]);
x++;
}


}
 Form1->OldXs=Form1->Series1->MaxXValue();
Form1->OldYs=Form1->Series1->YValue[Form1->Series1->LastValueIndex];
}
void __fastcall TForm5::Trapezoidal(float Amp,float offset,float t_s, float t_b,float t_ON,float t_OFF,int rep)
{
float A_t=0.0;
float cuenta1=0;
float cuenta2=0;
float cuenta3=0;
float frec=1/(t_s+t_b+t_ON+t_OFF);

int Count=1/Form1->Frm;
Data = new double [Count];

 float Rate=(float)Count*frec;

 A_t=1/Rate;
 cuenta1= (float)t_s/A_t ;
 cuenta2= (cuenta1+(t_ON/A_t));
 cuenta3= cuenta2+(t_b/A_t);

 int i;
 int j;



 Form1->Frm=A_t;
 for(j=0; j<1;j++)
 {
 for (i = (Count)*j; i < (cuenta1+(Count)*j); i++)
 {
  Data[i]=(double)(offset+(i-Count*j)*Amp/cuenta1);
 }

 for (i = cuenta1+Count*j;i < cuenta2+Count*(j); i++)
 {
 Data[i]= Amp+offset;

 }

 for (i = cuenta2+Count*j;i < cuenta3+Count*(j); i++)
 {
  Data[i]=(double)(offset+Amp-((i-(cuenta2+Count*j))*Amp/(cuenta3-cuenta2)));
 }

 for (i = cuenta3+Count*j;i < Count*(j+1); i++)
 {
 Data[i]=offset;

 }


 }


int x=0;

for(int h=0;h<rep;h++)
for(int t=0;t<Count;t++)
{
Form1->Series1->AddXY(Form1->OldXs+x/Rate,Data[t]);
x++;
}
Form1->OldXs=Form1->Series1->MaxXValue();
Form1->OldYs=Form1->Series1->YValue[Form1->Series1->LastValueIndex];

}
void __fastcall TForm5::SpeedButton4Click(TObject *Sender)
{ try{
Form1-> ERROR1++;
float Amp=StrToFloat(Edit15->Text);
float offset=StrToFloat(Edit16->Text);
int rep=StrToInt(Edit18->Text);
float t_s=StrToFloat(Edit13->Text);
float t_c=StrToFloat(Edit33->Text);
float t_on=StrToFloat(Edit34->Text);
float t_off=StrToFloat(Edit14->Text);
Trapezoidal( Amp, offset, t_s,t_c,t_on,t_off,rep);
Form1->OldXs=Form1->Series1->MaxXValue();
Form1->OldYs=Form1->Series1->YValue[Form1->Series1->LastValueIndex];

Form1->AjustaChart(Form1->Series1->MinYValue(),Form1->Series1->MaxYValue(),0, Form1->OldXs);
 }
 catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema con los par�metros de entrada. Por favor verifique el contenido de los mismos y vuelva a intentarlo.");}
this ->Close();
}
//---------------------------------------------------------------------------







void __fastcall TForm5::FormCreate(TObject *Sender)
{
HRV=false;
}
//---------------------------------------------------------------------------


void __fastcall TForm5::CheckBox2Click(TObject *Sender)
{
if(CheckBox2->Checked==true)
{
Edit37->Enabled=true;
Edit38->Enabled=true;
Edit1->Text=0;
Edit1->Enabled=false;

}else
{
Edit37->Enabled=false;
Edit38->Enabled=false;
Edit1->Enabled=true;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm5::SpeedButton8Click(TObject *Sender)
{
try{

double *A=new double [100000];
double *B=new double [100000];
for(long int t=0;t<100000;t++)
{
A[t]=0;
B[t]=0;

}
 A=Form1->FTP_01;

  int x1=0;
  int a=0;
  float i=0;

float inc=0;
float fd=StrToFloat(Edit27->Text)/60;
float Armonicos=StrToFloat(Edit28->Text);
float Amp=StrToFloat(Edit29->Text);
float Offset=StrToFloat(Edit30->Text);
int fs=1/Form1->Frm;
int x=0;



for(int ar=0;ar<Armonicos;ar++)
 {
//******************************

if(CheckBox1->Checked==true)
{
 int dif=StrToInt(Edit36->Text)-StrToInt(Edit35->Text);
if (dif<0)
	ShowMessage("Error par�metros no v�lidos. Desde>Hasta");

fd=StrToInt(Edit35->Text)+rand()%dif;

fd=(float)fd/60;
}

 inc= (fd*1000)/fs;
   int l=0;


 x=0;

  a=0;
   i=0;

while(i<1000)
{

 l=( int)i;
 B[x]=((((A[l]+A[l+1])/2))*Amp)+ Offset;

 x++ ;
 i=i+inc;

}

//*******************************

 if (fd<1)
 {
for(int f=0;f<fd;f++)
  { a=0;
 while(a<x)
 {

   Form1->Series1->AddXY(Form1->OldXs+x1*Form1->Frm,B[a]);
   x1++;
   a++;
 }
 }
 }else
 {
  for(int f=0;f<(int)fd;f++)
  { a=0;
 while(a<x)
 {

   Form1->Series1->AddXY(Form1->OldXs+x1*Form1->Frm,B[a]);
   x1++;
   a++;
 }
 }
 }


 }
 HRV=false;

  Form1->OldXs=Form1->Series1->MaxXValue();
  Form1->OldYs=Form1->Series1->YValue[Form1->Series1->LastValueIndex];


 Form1->AjustaChart(Form1->Series1->MinYValue(),Form1->Series1->MaxYValue(),0, Form1->OldXs);

  Form1->StatusBar1->Panels->Items[5]->Text=" <N> "+IntToStr(Form1->Series1->Count());

 Form1->ListBox1->Items->Add(" ");
 Form1->ListBox1->Items->Add(">> ::Se�al de Fotopletismograf�a::");
 String S2="  -- Latidos/minutos :: "+FloatToStr(fd*60);
 Form1->ListBox1->Items->Add(S2);
 String S3="  -- Amplitud deseada :: "+FloatToStr(Amp)+" V";
 Form1->ListBox1->Items->Add(S3);
 String S4="  -- Repetir :: "+FloatToStr(Armonicos)+" veces";
 Form1->ListBox1->Items->Add(S4);
 String S5="  -- Offset (V) :: "+FloatToStr(Offset)+" V";
 Form1->ListBox1->Items->Add(S5);

   //********FFT***** ***************************

 Form1->FFT_L();

 Form1->ListBox1->Items->Add(" ");
 String S6="    ::FFT Aplicada :: ";
 Form1->ListBox1->Items->Add(S6);
 String S7="      -- Numero de puntos FFT :: " +IntToStr(Form1->nFFT);
 Form1->ListBox1->Items->Add(S7);
 Form1-> Action10->Enabled=1;
 }catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema con los par�metros de entrada. Por favor verifique el contenido de los mismos y vuelva a intentarlo.");}

 Form5->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm5::CheckBox1Click(TObject *Sender)
{
if(CheckBox1->Checked==true)
{
Edit35->Enabled=true;
Edit36->Enabled=true;
Edit27->Text=0;
Edit27->Enabled=false;

}else
{
Edit35->Enabled=false;
Edit36->Enabled=false;
Edit27->Enabled=true;
}
}
//---------------------------------------------------------------------------


