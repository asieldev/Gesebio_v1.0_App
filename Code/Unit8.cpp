//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Unit8.h"
#include "Unit1.h"
#include "Unit6.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm8 *Form8;

//---------------------------------------------------------------------------
__fastcall TForm8::TForm8(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm8::BitBtn2Click(TObject *Sender)
{
try{
if(!Form1->Action92->Checked)
{
Form1->hasta=Form1->Series1->Count();
Form1->desde= 0;

}
int res=Form1->hasta-Form1->desde;

u = 100;

double *Randon=new double [res];
double *Salva=new double [Form1->Series1->Count()];
double Amp=StrToFloat(Edit5->Text);
int N=Form1->Series1->Count();
for(int w=0;w<N;w++)
 {Salva[w]= Form1->Series1->YValue[w];

 }
//Form1->Series1->Clear();

//Form1->Series1->AddXY(0.0,0.0);
int r=0;
Edit5->Text=N;
for(int k=Form1->desde;k<Form1->hasta;k++)
{

Randon[r]= (1+rand()%u)-50;
double aaa= Randon[r]/50*Amp+Salva[k];
Form1->Series1->YValue[k]=aaa;
 r++;
}

 Form1->ListBox1->Items->Add("");
 String S5="  <--> Ruido incorporado blanco gausiano ::";
 Form1->ListBox1->Items->Add(S5);
 String S6="  -- Ämplitud "+FloatToStr(Amp)+" V";
 Form1->ListBox1->Items->Add(S6);

}catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema con los parámetros de entrada. Por favor verifique el contenido de los mismos y vuelva a intentarlo.Si el problema continúa contacte inmediatamante a los diseñadores.");}

Form8->Visible=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm8::BitBtn3Click(TObject *Sender)
{

try{
 if(!Form1->Action92->Checked)
{
Form1->hasta=Form1->Series1->Count();
Form1->desde= 0;

}

int res=Form1->hasta-Form1->desde;
double *SIN=new double [res];
double *Salva=new double [Form1->Series1->Count()];
double frec=StrToFloat(Edit7->Text);
double offs=StrToFloat(Edit1->Text);
double Amp=StrToFloat(Edit4->Text);

int N=Form1->Series1->Count();
for(int w=0;w<N;w++)
 {Salva[w]= Form1->Series1->YValue[w];

 }

 int r=0;
 for(int k=Form1->desde;k<Form1->hasta;k++)
{
 SIN[r]=Amp*sin(6.28*r*frec*Form1->Frm)+offs;

double aaa= SIN[r]+Salva[k];
Form1->Series1->YValue[k]=aaa;
 r++;
}
 Form1->ListBox1->Items->Add("");
 String S5="  <--> Interferencia de la línea de potencia ::";
 Form1->ListBox1->Items->Add(S5);
 String S6="  -- Ämplitud "+FloatToStr(Amp)+" V";
 Form1->ListBox1->Items->Add(S6);
 String S7="  -- Frecuencia "+FloatToStr(frec)+" Hz";
 Form1->ListBox1->Items->Add(S7);
  String S8="  -- Offset "+FloatToStr(offs)+" V";
 Form1->ListBox1->Items->Add(S8);
}catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema con los parámetros de entrada. Por favor verifique el contenido de los mismos y vuelva a intentarlo.Si el problema continúa contacte inmediatamante a los diseñadores.");}

 Form8->Visible=0;
 }
//---------------------------------------------------------------------------


void __fastcall TForm8::SpeedButton1Click(TObject *Sender)
{
Form6->Show();
}
//---------------------------------------------------------------------------

