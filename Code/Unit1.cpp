//---------------------------------------------------------------------------

#include <vcl.h>
#include <dir.h>
#include <math.h>
#include <condefs.h>

#define PI 3.14159265358

#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#pragma hdrstop
#include "WAVE.h"
#include "Unit1.h"
#include "Unit11.h"
#include "Unit12.h"
#include "Unit10.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"
#include "Unit7.h"
#include "Unit8.h"
#include "Unit9.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Chart"
#pragma link "Series"
#pragma link "TeeFunci"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma link "BubbleCh"
#pragma link "TeCanvas"
#pragma resource "*.dfm"
TForm1 *Form1;
FILE * fp_212;
FILE * fp1_212;

void ifft(double *real,double *imag,int NPuntos);

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------








//---------------------------------------------------------------------------

 void TForm1::DrawCross(int ax, int ay)
{
  TColor tmp;
  tmp = Chart1->BackColor;
  if (tmp == clTeeColor)
    tmp = clBtnFace;
  Chart1->Canvas->Pen->Color = (TColor)(CrossHairColor ^ ColorToRGB(tmp));

  Chart1->Canvas->Pen->Style = CrossHairStyle;
  Chart1->Canvas->Pen->Mode = pmXor;
  Chart1->Canvas->Pen->Width = 1;
  Chart1->Canvas->MoveTo(ax,Chart1->ChartRect.Top-Chart1->Height3D);
  Chart1->Canvas->LineTo(ax,Chart1->ChartRect.Bottom-Chart1->Height3D);
  Chart1->Canvas->MoveTo(Chart1->ChartRect.Left+Chart1->Width3D,ay);
  Chart1->Canvas->LineTo(Chart1->ChartRect.Right+Chart1->Width3D,ay);
}




void __fastcall TForm1::FormCreate(TObject *Sender)
{

	Hebra1 = new TConcurent(true);// Creation suspended--the second process does not run yet.
	Hebra1->FreeOnTerminate = true; // No need to clean up after termination
	Hebra1->Priority = tpLower;  // Set the priority to lower than normal.
	Hebra1->Start(); // Ahora arranca la hebra.





PageControl3->Align=alClient;
//
 String S="--"+Date().DateString()+ "  " + Time().TimeString()+"--";
Form1->ListBox1->Items->Add(S);
   //Chart1->SetFocus();

   z=1;
  press = false;

 // LineSeries1->FillSampleValues(30);  // <-- Con algunos valores aleatorios
  OldX = -1;                          // inicializar variables
  CrossHairColor = clYellow;
  CrossHairStyle = psSolid;
  Chart1->Cursor = crCross;

  // Form4->Visible=False;


 Form1->Chart1->AxesList->Bottom->Automatic=false;
 Form1->Chart1->AxesList->Left->Automatic=false;


(OldXs)=0.0;
(OldYs)=0.0;
 Frm=0.001;
 h=1;


HidePanel();
StatusBar1->Panels->Items[2]->Text= Date().DateString()+ "  " + Time().TimeString();
ProgressBar1->Visible=False;

  Ini_G();
}

//---------------------------------------------------------------------------






void __fastcall TForm1::Action9Execute(TObject *Sender)
{
if ((Series1->Count()==0))
{
MessageDlgPos("No hay ninguna se�al disponible para ser guardada  en el �rea de trabajo",

		mtWarning,

				  TMsgDlgButtons() << mbCancel ,
				  0, 350, 300);

 goto A;
}
if(SaveDialog1->Execute())
{

Path=new char [strlen(SaveDialog1->FileName.t_str())+5];
 Path= SaveDialog1->FileName+".sbio";
SaveSGN() ;
 flatPaht=true;
 StatusBar1->Panels->Items[0]->Text =Path;
}

 Form1->Outline1->Lines->Clear();

Form1->Path_Name=ExtractFileName(Form1->Path);
Form1->Outline1->Lines->Add(Form1->Path_Name);

Action10->Enabled=0;
 fSave=true;
A:
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action8Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action10Execute(TObject *Sender)
{
if ((Series1->Count()==0))
{
MessageDlgPos("No hay ninguna se�al disponible para ser guardada  en el �rea de trabajo",

		mtWarning,

				  TMsgDlgButtons() << mbCancel ,
				  0, 350, 300);
				  goto A;
}

if(!flatPaht)
{
SaveDialog1->Execute();

if(SaveDialog1->FileName!="")
{
Path=new char [strlen(SaveDialog1->FileName.t_str())+5];
 Path= SaveDialog1->FileName+".sbio";
 SaveSGN() ;
 flatPaht=true;
 StatusBar1->Panels->Items[0]->Text =Path;
 fSave=true;
 Action10->Enabled=0;

Form1->Outline1->Lines->Clear();
Form1->Path_Name=ExtractFileName(Form1->Path);
Form1->Outline1->Lines->Add(Form1->Path_Name);

 }

}else
{
 SaveSGN() ;
 fSave=true;
 Action10->Enabled=0;
}

A:
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action7Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action11Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action12Execute(TObject *Sender)
{
PageControl3->Visible=False;
LoadPanel();


if(Series1->Count()==0)
{
Clear=1;

Form9->ShowModal();
}
else{
Clear=0;
Form1->OldXs=0.0;

}
if(!Clear)
if(fSave)
{
Form1->Chart1->AxesList->Bottom->Automatic=false;
Form1->Chart1->AxesList->Left->Automatic=false;

Form1->Series1->Clear();
Clear=1;


Form1->OldXs=0.0;
Form1->OldYs=0.0;

Form1->h=1;
Form9->ShowModal();
}else{

String AA= "Guardar informaci�n " ;
String s ="�Desea guardar la informaci�n contenida en el proyecto actual?";
 if(Application->MessageBoxA(s.w_str(),AA.w_str(),MB_YESNO+MB_ICONWARNING)==IDYES )
 {

if(!flatPaht)
{


SaveDialog1->Execute();
if(SaveDialog1->FileName!="")
{

Path=new char [strlen(SaveDialog1->FileName.t_str())+5];
 Path= SaveDialog1->FileName+".sbio";
SaveSGN() ;
 flatPaht=true;
 Form1->Series1->Clear();
 fSave=true;
Action22->Enabled=false;
Clear=1;

}

if(OpenDialog1->Execute())
{

//Path=new char [strlen(OpenDialog1->FileName.t_str())];
Path= OpenDialog1->FileName.t_str();
LoadSGN() ;
 flatPaht=true;
 StatusBar1->Panels->Items[0]->Text =Path;
 Form1->StatusBar1->Panels->Items[5]->Text=" <N> "+IntToStr(Form1->Series1->Count());
  Action22->Enabled=false;
  fSave=true;

 Form1->Outline1->Lines->Clear();

Form1->Path_Name=ExtractFileName(Form1->Path);
Form1->Outline1->Lines->Add(Form1->Path_Name);
}

}else
{
 SaveSGN() ;
 fSave=true;
 Action22->Enabled=false;
 if(OpenDialog1->Execute())
{

//Path=new char [strlen(OpenDialog1->FileName.t_str())];
Path= OpenDialog1->FileName.t_str();
LoadSGN() ;
 flatPaht=true;
 StatusBar1->Panels->Items[0]->Text =Path;
  Form1->StatusBar1->Panels->Items[5]->Text=" <N> "+IntToStr(Form1->Series1->Count());
  Action22->Enabled=false;
  fSave=true;

 Form1->Outline1->Lines->Clear();

Form1->Path_Name=ExtractFileName(Form1->Path);
Form1->Outline1->Lines->Add(Form1->Path_Name);
}

}

Action10->Enabled=false;


//********LIMPIA**********


Form1->Chart1->AxesList->Bottom->Automatic=false;
Form1->Chart1->AxesList->Left->Automatic=false;


//Form1->Frm=0.001;
//Form9->ShowModal();

Form1->OldXs=0.0;
Form1->OldYs=0.0;

Form1->h=1;

}else
{
Form1->Chart1->AxesList->Bottom->Automatic=false;
Form1->Chart1->AxesList->Left->Automatic=false;

Form1->Series4->Clear();
Form1->Series5->Clear();
Form1->Series1->Clear();
Clear=1;

///////////////////////////////////////////////
if(OpenDialog1->Execute())
{

//Path=new char [strlen(OpenDialog1->FileName.t_str())];
Path= OpenDialog1->FileName.t_str();
LoadSGN() ;
 flatPaht=true;
 StatusBar1->Panels->Items[0]->Text =Path;
  Form1->StatusBar1->Panels->Items[5]->Text=" <N> "+IntToStr(Form1->Series1->Count());
  Action22->Enabled=false;
  fSave=true;

}
////////////////////////////////////////////////


Form1->OldXs=0.0;
Form1->OldYs=0.0;

Form1->h=1;
Action22->Enabled=false;

}

}

}

//---------------------------------------------------------------------------

void __fastcall TForm1::Action13Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Cleaning()
{
 Form1->ListBox3->Items->Clear();
 SpeedButton22->Visible=false;
 Form1->StatusBar1->Panels->Items[5]->Text="";

 Series1->Clear();
  Series3->Clear();
   Series9->Clear();
    Series10->Clear();

  Form1->ListBox1->Items->Clear();
 Form1->ListBox1->Items->Add("");
 Form1->ListBox1->Items->Add("--Nueva sesion--");
  Form1->ListBox1->Items->Add("");
 String S="--"+Date().DateString()+ "  " + Time().TimeString()+"--";
Form1->ListBox1->Items->Add(S);
Outline1->Lines->Clear();
Action27->Enabled=false;
RibbonComboBox1->Text="Ubicaci�n del fichero(*.WAV)";
ERROR1=0;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Genera_Bin()
{

   int  k=Series1->Count();
    ProgressBar1->Visible=true;
   ProgressBar1->Max=k;

   String s =IntToStr(k);
  Res_DAC=StrToInt(ComboBox2->Text);
  V_REF=StrToFloat(ComboBox3->Text);
  V_BIN=new    int [k];
	  Form1->ListBox3->Items->Clear();
	  SpeedButton22->Visible=true;
	for(int o=0;o<k;o++)
	  {
		V_BIN[o]=(( long int)pow(2,Res_DAC)-1)*Series1->YValue[o]/V_REF;

		ProgressBar1->Position=o;
		if(Series1->YValue[o]>=V_REF)
		V_BIN[o]=(int)(pow(2,Res_DAC)-1);

		if(Series1->YValue[o]<=-V_REF)
		V_BIN[o]=-( long int)(pow(2,Res_DAC)-1);

		Form1->ListBox3->Items->Strings[o]= String(IntToHex(V_BIN[o],16));
	  }

	  ProgressBar1->Visible=false;

	}



	void __fastcall TForm1::AjustaChart(double Y0,double YN,double X0,double XN)

	{
	   Chart1->AxesList->Left->SetMinMax(Y0,YN);
	   Chart1->AxesList->Bottom->SetMinMax(X0,XN);


	}

void __fastcall TForm1::FFT_L()
{
double *outfft;
double *yfft;
double *xfft;
xfft=new double  [Form1->nFFT];
yfft=new double  [Form1->nFFT];
outfft=new double  [Form1->nFFT];
 Series3->Clear();
for(int p=0;p<nFFT;p++)
{
xfft[p]=0;
yfft[p]=0;
outfft[p]=0;
}
for(int l=0;l<nFFT;l++)
{
 if(l<Form1->Series1->Count())
   xfft[l]=Series1->YValue[l];
 else
   xfft[l]=0;
}

fft(xfft,yfft,nFFT);

ProgressBar1->Max=nFFT;
ProgressBar1->Visible=true;

for(int a=0;a<nFFT/2;a++)
{
 outfft[a]= xfft[a]*xfft[a]+  yfft[a]*yfft[a];
 ProgressBar1->Position=a;
 outfft[0]=0;
 Series3->AddXY(((1/Form1->Frm)/2*a)/(Form1->nFFT/2),outfft[a]);
}

ProgressBar1->Visible=false;

}

	 void __fastcall TForm1::LoadSGN()
	 {
		  double *Data2;
	/*   A0= &(Form1->Ndata1);
	   A1= &(Form1-> Frm);
	   A2= &(Form1-> X0);
	   A3= &(Form1->XN);
	   A4= &(Form1->Y0);
	   A5= &(Form1->YN);;   */

	   FILE *fp1;
        Label18->Caption=Path;
		fp1=fopen(Path.t_str(),"rb");
		  if(fp1==NULL)ShowMessage("Error Abriendo...");
		  else{
		fseek(fp1, 0, 0);



	  fread(&Z0,sizeof(double),1,fp1);

		 Data2=new double [(Z0)];

		fseek(fp1, sizeof(double), SEEK_CUR);
		fread(&Z1,sizeof(double),1,fp1);

		fseek(fp1, sizeof(double), SEEK_CUR);
		fread(&Z2,sizeof(double),1,fp1);

		fseek(fp1, sizeof(double), SEEK_CUR);
		fread(&Z3,sizeof(double),1,fp1);

		fseek(fp1, sizeof(double), SEEK_CUR);
		fread(&Z4,sizeof(double),1,fp1);

		fseek(fp1, sizeof(double), SEEK_CUR);
		fread(&Z5,sizeof(double),1,fp1);
		   //Button2->Caption=Z5;
		fseek(fp1, sizeof(double), SEEK_CUR);
		fread(Data2,sizeof(double),(Z0),fp1);

		fclose(fp1);
		}

		Frm=Z1;
		OldXs=(Z3);
		OldYs=(Z5);
		 ProgressBar1->Max=Z0;
		 ProgressBar1->Visible=1;
		for(int t=0;t<(Z0);t++)
		{
		Form1->Series1->AddXY(t*(Z1),Data2[t]);
		ProgressBar1->Position=t;
		Sleep(1);
		}
		ProgressBar1->Position=0;
		ProgressBar1->Visible=0;
		fSave=true;
		Action10->Enabled=false;
        FFT_L();
		Form1->AjustaChart(Form1->Series1->MinYValue(),Form1->Series1->MaxYValue(),Form1->Series1->MinXValue(),OldXs);
      Form1->Outline1->Lines->Clear();

Form1->Path_Name=ExtractFileName(Form1->Path);
Form1->Outline1->Lines->Add(Form1->Path_Name);

 try{
String szFileName1;
String INF=".inf";
 String MDAT;
fnsplit(Path.t_str(),0,0,szFileName1.t_str(),0);
String ab=ExtractFilePath(Path.t_str());
MDAT=ab+szFileName1.t_str()+INF;


 RichEdit1->Lines->LoadFromFile(MDAT);

 } catch(Exception &exception ){
 ;

 }
}



void __fastcall TForm1::SaveSGNT()
{ FILE *FP;
FP=fopen(Patht.t_str(),"w+");
 for(int g=0;g<Series1->Count();g++)
 {
 fprintf(FP,"%e\n\r",Series1->YValue[g]);

 }
 fclose(FP);

}


void __fastcall TForm1::OpenSGNT()
{ FILE *FP1;
 float q;

int o;
int g=0;
FP1=fopen(Patht.t_str(),"rb");
 if(FP1==NULL)
 {
 ShowMessage("No se ha podido importar ning�n fichero de texto. La operaci�n ha sido interrumpida");
 }else{
  do
 {
o=fscanf(FP1,"%e\n\r",&q);
Series1->AddXY(g*Frm,q);

  g++;
 }while(o!=EOF);
 }
 fclose(FP1);


}


void __fastcall TForm1::SaveSGN()
	 {

		double *Data1;

	   A0= &(Form1->Ndata1);
	   A1= &(Form1-> Frm);
	   A2= &(Form1-> X0);
	   A3= &(Form1->XN);
	   A4= &(Form1->Y0);
	   A5= &(Form1->YN);

	  FILE *fp;
	  Form1->Ndata1=Form1->Series1->Count();


	  Data1=new double [Ndata1];

	  for(int i=0;i<(int)(Form1->Ndata1);i++)
	  {
	   Data1[i]= Form1->Series1->YValue[i];
	  }

	   Form1->X0=Form1->Series1->XValue[0];
	   Form1->XN=Form1->Series1->XValue[Ndata1-1];
	   Form1->Y0=Form1->Series1->MinYValue();
	   Form1->YN=Form1->Series1->MaxYValue();

	  // Button1->Caption=(*A5);
		fp=fopen(Path.t_str(),"wb");

		  if(fp==NULL)ShowMessage("Error Guardando...");
		  else{
		fseek(fp, 0, SEEK_SET);
		fwrite(A0,sizeof(double),1,fp);
		fseek(fp, sizeof(double), SEEK_CUR);
		fwrite(A1,sizeof(double),1,fp);
		fseek(fp, sizeof(double), SEEK_CUR);
		fwrite(A2,sizeof(double),1,fp);
		fseek(fp, sizeof(double), SEEK_CUR);
		fwrite(A3,sizeof(double),1,fp);
		fseek(fp, sizeof(double), SEEK_CUR);
		fwrite(A4,sizeof(double),1,fp);
		fseek(fp, sizeof(double), SEEK_CUR);
		fwrite(A5,sizeof(double),1,fp);
		fseek(fp, sizeof(double), SEEK_CUR);
		fwrite(Data1,sizeof(double),(*A0),fp);

		fclose(fp);

		  }



String szFileName1;
String INF=".inf";
 String MDAT;
fnsplit(Path.t_str(),0,0,szFileName1.t_str(),0);
String ab=ExtractFilePath(Path.t_str());
MDAT=ab+szFileName1.t_str()+INF;

FILE *FP;
FP=fopen(MDAT.t_str(),"w+");

String A=RichEdit1->Lines->Text;
 char *A1=new char[strlen(A.t_str())];
 A1=A.t_str();
 for(int g=0;g<strlen(A1);g++)
 {
 fprintf(FP,"%c",(A1[g]));

 }
 fclose(FP);

 }



  void __fastcall TForm1::LoadPanel()
	  {
		 Panel1->Visible=True;
		 Panel2->Visible=True;
		 Panel3->Visible=True;
		// GroupBox4->Visible=True;
		 PageControl2->Visible=True;
		 Panel5->Visible=True;
		// Panel4->Visible=True;
		  Panel6->Visible=True;

		  /////Regala el foco al Chart1
		  Form1->Chart1->SetFocus();
	  }
	 void __fastcall TForm1::HidePanel()
	  {
		 Panel1->Visible=False;
		 Panel2->Visible=False;
		 Panel3->Visible=False;
		 //Panel4->Visible=False;
		 Panel5->Visible=False;
		 Panel6->Visible=False;
		 //GroupBox4->Visible=False;
		 PageControl2->Visible=False;
	  }

	  void __fastcall TForm1::ERROR_FRM(int fd)
	  {
	   if((int)2*fd>=1/Frm)
	   {
		ShowMessage("Existe un problema. La frecuencia deseada para una correcta generaci�n debe de cumplir con la siguiente expresi�n (fd<=Frm/2) ");
	   }


	  }


void __fastcall TForm1::SpeedButton11Click(TObject *Sender)
{
if(Series1->Count()==0)
  ShowMessage("No existe ninguna Se�al Disponible");
else
{


Genera_Bin();

}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
delete Form2->A;
delete V_BIN;

if(!fSave)
if (Form1->Series1->Count()!=0) {


String AA= "Guardar informaci�n " ;
String s ="�Desea guardar la informaci�n contenida en el proyecto actual?";

int a=Application->MessageBoxA(s.w_str(),AA.w_str(),MB_YESNOCANCEL+MB_ICONWARNING);
 if(a==IDYES )
 {

if(!flatPaht)
{


SaveDialog1->Execute();
if(SaveDialog1->FileName!="")
{

Path=new char [strlen(SaveDialog1->FileName.t_str())+5];
 Path= SaveDialog1->FileName+".sbio";
SaveSGN() ;
 flatPaht=true;
}
}else
{
 SaveSGN() ;
}
fSave=true;
Action10->Enabled=false;

} else if (a==IDCANCEL) { Action=caNone;

	   }
}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Action18Execute(TObject *Sender)
{
exit(1);
}
//---------------------------------------------------------------------------








void __fastcall TForm1::SpeedButton17Click(TObject *Sender)
{


if(OpenDialog1->Execute())
{

//Path=new char [strlen(OpenDialog1->FileName.t_str())];
Path= OpenDialog1->FileName.t_str();
LoadSGN() ;
 flatPaht=true;
 StatusBar1->Panels->Items[0]->Text =Path;
  Form1->StatusBar1->Panels->Items[5]->Text=" <N> "+IntToStr(Form1->Series1->Count());
  Action22->Enabled=false;
  fSave=true;

Form1->Outline1->Lines->Clear();

Form1->Path_Name=ExtractFileName(Form1->Path);
Form1->Outline1->Lines->Add(Form1->Path_Name);
}
 PageControl3->Visible=False;
LoadPanel();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton18Click(TObject *Sender)
{

PageControl3->Visible=False;
LoadPanel();
Form9->Show();

Form1->Outline1->Lines->Clear();


Form1->Outline1->Lines->Add("<<Nuevo Proyecto>>");
 ListBox3->Clear();
 Series1->Clear();
 double y[501] ;
for(int a=0;a<500;a++)
{
 y[a]=sin(6.28*2*a*Frm)+sin(6.28*10*a*Frm);
 Series1->AddXY((double)a*Frm,y[a]);
 ListBox3->Items->Add(FloatToStr(y[a]));

}

Form1->OldXs=Form1->Series1->MaxXValue();
Form1->OldYs=Form1->Series1->YValue[Form1->Series1->LastValueIndex];

   Form1->AjustaChart(Form1->Series1->MinYValue(),Form1->Series1->MaxYValue(),Form1->Series1->MinXValue(),OldXs);


Action76Execute(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton19Click(TObject *Sender)
{
exit(1);
}
//---------------------------------------------------------------------------













void __fastcall TForm1::Action19Execute(TObject *Sender)
{
Form5->Show();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Action14Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action21Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action22Execute(TObject *Sender)
{
if(Form1->Series1->Count()==0)
{ShowMessage("No existe ninguna se�al disponible en el �rea de trabajo.");
 goto A;
}
Form8->Show();
 A:
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action23Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action24Execute(TObject *Sender)
{
Form6->Show();
}
//---------------------------------------------------------------------------





void __fastcall TForm1::CategoryPanelGroup2MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
press = false;
}
//---------------------------------------------------------------------------












void __fastcall TForm1::Label2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
press  = true;
X1 = X;
Y2 = Y;
}
//---------------------------------------------------------------------------








void __fastcall TForm1::Label1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
press  = true;
X1 = X;
Y2 = Y;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
if (press)
{
GetCursorPos(&pt);
Panel2->Left= pt.x - X1;
Panel2->Top = pt.y - Y2;

}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
press = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label2MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
if (press)
{
GetCursorPos(&pt);
Panel3->Left= pt.x - X1;
Panel3->Top = pt.y - Y2;

}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
press = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label17MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
press  = true;
X1 = X;
Y2 = Y;
}
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm1::Chart1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{

  if (Action92->Checked)
   {
   
    z=1;
   }

 double tmpX,tmpY;
  if (OldX != 1) {
    DrawCross(OldX,OldY);  // draw old crosshair
    OldX = 1;
  }

  // check if (mouse is inside Chart rectangle
  if (PtInRect((RECT*)&Chart1->ChartRect, Point(X-Chart1->Width3D,Y+Chart1->Height3D))) {


	DrawCross(X,Y);  // draw crosshair at current position
    // store old position
    OldX = X;
    OldY = Y;
    // set label text
	Series1->GetCursorValues(tmpX,tmpY);  // <-- get values under mouse cursor
	Label21->Caption =Series1->GetHorizAxis->LabelValue(tmpX)
	  + ";" + Series1->GetVertAxis->LabelValue(tmpY) ;
  }

  if(!z) Chart1->Zoom->Allow=false;
  else Chart1->Zoom->Allow=true;

  if(h==0){
    Action9->Enabled=true;
    Action10->Enabled=true;
	fSave=false;
	Clear=0;

  NewXs=Series1->XScreenToValue(X);
  NewYs=Series1->YScreenToValue(Y);
   //Edit1->Text=NewXs;
  if(z==0)
  if(((NewXs>OldXs)))
   {
	Cal_Mx(NewXs,NewYs,OldXs,OldYs);

   }
  else
   {




	Series5->Clear();
	Series4->Clear();
	double k=(Series1->XScreenToValue(X))/Frm;
   Series1->YValue[k]= Series1->YScreenToValue(Y);
	Series1->XValue[k]= Series1->XScreenToValue(X);
   }
   }   else ;

  }
//---------------------------------------------------------------------------

void __fastcall TForm1::Chart1AfterDraw(TObject *Sender)
{

 OldX = 1;
 
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
CrossHairColor = EditColor(this,CrossHairColor);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Action1Execute(TObject *Sender)
{
Form10->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
Form4->Hide();
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

void  __fastcall TForm1::Cal_Mx(double NewXs,double NewYs,double &OldXs,double &OldYs)

 {

  double offset=0;
  double m,n=0,y=0;
  offset= ((NewXs- OldXs)/Frm);
  m=(NewYs-OldYs)/(NewXs-OldXs);
  //Edit1->Text=Series1->XValue[Series1->Count()];
  n=(NewYs-(m*NewXs));
	 //Edit1->Text=NewXs;
  for (double i = 1; i < offset; ++i)
  {
  y=((m*(OldXs+(Frm*i)))+n);
  Series1->AddXY((OldXs+(Frm*i)),y);
  }

   OldXs=Series1->MaxXValue();
   OldYs=Series1->YValue[Series1->LastValueIndex];
 }



void  __fastcall TForm1::Ini_G()
{
fSave=false;
Frm=(double)1/250;
FM=250;
nFFT=32768;
Vent_Index=0;
X01=0;
Y01=-5;
Xn1=5;
Yn1=5;
Trefresco=1000;
Form1->Timer1->Enabled=false;
Form1->Timer1->Interval=Trefresco;
Form1->Timer1->Enabled=true;
flatPaht=false;
Clear=1;
fRecortar=0;
fSaveOther=false;
/*Action10->Enabled=false;
Action9->Enabled=false;   */
StatusBar1->Visible=true;
StatusBar1->Panels->Items[0]->Text ="<Ruta no especificada>";
AjustaChart(Y01,Yn1,X01,Xn1);
Action22->Enabled=false;
ERROR1=0;
}




















void __fastcall TForm1::Chart1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
h=1;
  //NewXs=Series1->XScreenToValue(X);
 // NewYs=Series1->YScreenToValue(Y);
   if (ERROR1==2)
  {
   ShowMessage("Incompatibilidad en frecuencia. Chequee que todos los tramos de la se�al tengan la misma frecuencia de muestreo ");
  ERROR1=1;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Chart1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
h=0;

}
//---------------------------------------------------------------------------







void __fastcall TForm1::Chart1Click(TObject *Sender)
{
Chart1->SetFocus();

}
//---------------------------------------------------------------------------



void __fastcall TForm1::Label22MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
press  = true;
X1 = X;
Y2 = Y;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label22MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
if (press)
{
GetCursorPos(&pt);
Panel6->Left= pt.x - X1;
Panel6->Top = pt.y - Y2;

}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label22MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
press = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action27Execute(TObject *Sender)
{
	  MediaPlayer1->FileName = RibbonComboBox1->Text;
	  MediaPlayer1->Open();
      MediaPlayer1->Wait = true;
	  MediaPlayer1->Play();
	  MediaPlayer1->Close();
 }
//---------------------------------------------------------------------------

void __fastcall TForm1::Action28Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action29Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action30Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action31Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action32Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action33Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Action34Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action36Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action37Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action38Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label17MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
   if (press)
{
GetCursorPos(&pt);
Panel5->Left= pt.x - X1;
Panel5->Top = pt.y - Y2;

}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label17MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
press = false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton12Click(TObject *Sender)
{
Chart1->ZoomPercent(120);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton13Click(TObject *Sender)
{
 Chart1->ZoomPercent(80);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton7Click(TObject *Sender)
{
  ScrollAxis(Chart1->TopAxis,10);
  ScrollAxis(Chart1->BottomAxis,10);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton9Click(TObject *Sender)
{
ScrollAxis(Chart1->LeftAxis,-10);
  ScrollAxis(Chart1->RightAxis,-10);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton10Click(TObject *Sender)
{
ScrollAxis(Chart1->LeftAxis,10);
  ScrollAxis(Chart1->RightAxis,10);
}
//---------------------------------------------------------------------------

  void __fastcall TForm1::ScrollAxis(TChartAxis* Axis, const double Percent)
{
  double Amount = ((Axis->Maximum-Axis->Minimum)/(100.0/Percent));
  Axis->SetMinMax(Axis->Minimum-Amount,Axis->Maximum-Amount);
}
void __fastcall TForm1::SpeedButton21Click(TObject *Sender)
{
 Chart1->UndoZoom();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action39Execute(TObject *Sender)
{
 PageControl1->TabIndex=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action40Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action41Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action42Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action43Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action44Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action45Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action46Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action47Execute(TObject *Sender)
{

if(Series1->Count()==0)
{
Clear=1;
Form9->ShowModal();
}
else{
Clear=0;
Form1->OldXs=0.0;

}
if(!Clear)
if(fSave)
{
Form1->Chart1->AxesList->Bottom->Automatic=false;
Form1->Chart1->AxesList->Left->Automatic=false;

Form1->Series1->Clear();
Clear=1;


Form1->OldXs=0.0;
Form1->OldYs=0.0;

Form1->h=1;

Form9->ShowModal();

}else{

String AA= "Guardar informaci�n " ;
String s ="�Desea guardar la informaci�n contenida en el proyecto actual?";
 if(Application->MessageBoxA(s.w_str(),AA.w_str(),MB_YESNO+MB_ICONWARNING)==IDYES )
 {

if(!flatPaht)
{


SaveDialog1->Execute();
if(SaveDialog1->FileName!="")
{

Path=new char [strlen(SaveDialog1->FileName.t_str())+5];
 Path= SaveDialog1->FileName+".sbio";
SaveSGN() ;
 flatPaht=true;
 Form1->Series1->Clear();
 fSave=true;
Action22->Enabled=false;
Clear=1;
}
}else
{
 SaveSGN() ;

 fSave=true;
 Action22->Enabled=false;
}

Action10->Enabled=false;


//********LIMPIA**********


Form1->Chart1->AxesList->Bottom->Automatic=false;
Form1->Chart1->AxesList->Left->Automatic=false;

 Form1->ListBox3->Items->Clear();
//Form1->Frm=0.001;
Form9->ShowModal();


Form1->OldXs=0.0;
Form1->OldYs=0.0;

Form1->h=1;

}else
{
Form1->Chart1->AxesList->Bottom->Automatic=false;
Form1->Chart1->AxesList->Left->Automatic=false;

Form1->Series4->Clear();
Form1->Series5->Clear();
Form1->Series1->Clear();
Clear=1;

   
 Form9->ShowModal();
Form1->OldXs=0.0;
Form1->OldYs=0.0;

Form1->h=1;
Action22->Enabled=false;

}





}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Action6Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action50Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action51Execute(TObject *Sender)
{
SpeedButton24Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action52Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------





void __fastcall TForm1::Chart1KeyPress(TObject *Sender, wchar_t &Key)
{
switch(Key) {
case 'Z':
case 'z':

 if(z==1){
 SpeedButton16->Visible=true;
 SpeedButton4->Visible=false;
 Label22->Caption=" Normal";
 StatusBar1->Panels->Items[1]->Text="Modo::Escritura";
  z=0;
 }else{
   SpeedButton16->Visible=false;
 SpeedButton4->Visible=true;
  Label22->Caption=" Zoom";
  StatusBar1->Panels->Items[1]->Text="Modo::Lectura";
  z=1;
 }


}
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button1Click(TObject *Sender)
{
SaveSGN();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
LoadSGN();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action58Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action59Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action60Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormActivate(TObject *Sender)
{

StatusBar1->SetFocus();

Form1->Enabled=True;
Path="p";
//----------------------------------------------
 FILE *fp_ECG_01_1000;
 FILE *fp_FOTHO_01_10000;
 fp_ECG_01_1000=fopen("ECG_01_1000.dat","rb");
 fp_FOTHO_01_10000=fopen("FOTO_01_1000.dat","rb");

  if (fp_ECG_01_1000>0)
	if(fp_FOTHO_01_10000>0)
	{
	 int status=fseek(fp_ECG_01_1000, 0, 0) ;
	 int status1=fseek(fp_FOTHO_01_10000, 0, 0) ;

	if (status>=0)
	 if (status1>=0)
	   {
		 fread(ECG_01, sizeof(double),1000, fp_ECG_01_1000);
		 fread(FTP_01, sizeof(double),1000, fp_FOTHO_01_10000);
	   }
	fclose(fp_ECG_01_1000);
	fclose(fp_FOTHO_01_10000);



	}


}


//---------------------------------------------------------------------------

void __fastcall TForm1::Action62Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action63Execute(TObject *Sender)
{
  ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action64Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action67Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action65Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action66Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action68Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action69Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action70Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action71Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action72Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action73Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action74Execute(TObject *Sender)
{
int u=0;
if(Series1->Count()==0)
{

ShowMessage("No hay se�al disponible en �rea de trabajo");
}else
  Form7->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action75Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action76Execute(TObject *Sender)
{

if(Series1->Count()==0)
{

ShowMessage("No hay se�al disponible en �rea de trabajo");
}else
  PageControl4Change(Sender);
}




//---------------------------------------------------------------------------

void __fastcall TForm1::Action77Execute(TObject *Sender)
{
if (!Panel5->Visible)
{
Panel5->Visible=true;
} else
 Panel5->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action78Execute(TObject *Sender)
{
if (!Panel3->Visible)
{
Panel3->Visible=true;
} else
 Panel3->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action79Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action80Execute(TObject *Sender)
{
if (!Panel2->Visible)
{
Panel2->Visible=true;
} else
 Panel2->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action81Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action82Execute(TObject *Sender)
{
if ((Series1->Count()==0))
{
MessageDlgPos("No hay ninguna se�al disponible para ser guardada  en el �rea de trabajo",

		mtWarning,

				  TMsgDlgButtons() << mbCancel ,
				  0, 350, 300);

 goto A;
}
if(SaveDialog2->Execute())
{

Patht=new char [strlen(SaveDialog2->FileName.t_str())+5];
 Patht= SaveDialog2->FileName+".txt";
SaveSGNT() ;
 //flatPaht=true;
 StatusBar1->Panels->Items[0]->Text =Path;
}


 fSave=true;
A:;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action84Execute(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action85Execute(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action87Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action86Execute(TObject *Sender)
{

;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action88Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action89Execute(TObject *Sender)
{
Form6->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action90Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Action91Execute(TObject *Sender)
{
WaveFile wf;

	wf.SetupFormat(FM,16,1);
	SaveDialog4->Execute();
	 //String eee="*.wav";
	String FF=SaveDialog4->FileName+".wav";

	if (!wf.OpenWrite(FF.t_str())) {
		//cout << "Can't open for writing: " << wf.GetError();

	}

	const dataLength = Series1->Count();
	 ProgressBar1->Position=0;
	 ProgressBar1->Max=dataLength;
	  ProgressBar1->Visible=1;

	for (int i = 0; i < dataLength; i++) {
		wf.WriteSample(Series1->YValue[i]/Series1->MaxYValue());
			 ProgressBar1->Position=i;

	}
		ProgressBar1->Visible=0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::fft(double *real, double *imag, int NPuntos)
{
 int Fases, Grupos;
 int fase, grupo, NumDatosGrupo, dual;
 int i, j, grupoini, pos, pos_dual,aux;
 double real_i, imag_i, real_dual, imag_dual;
 double coseno, seno;
 Fases = log(NPuntos)/log(2);
 Grupos = 1;
 for(fase=0; fase<Fases; fase++)
    {
        NumDatosGrupo = NPuntos/Grupos ;
        dual = NumDatosGrupo/2;
        grupoini = 0;

        for(grupo = 0; grupo < Grupos; grupo++)
           {
            for(i=0; i< dual; i++)
                {
                  pos = i + grupoini;
                  pos_dual = pos + dual;
                  real_i = real[pos] + real[pos_dual];
                  imag_i = imag[pos] + imag[pos_dual];
                  real_dual = real[pos] - real[pos_dual];
                  imag_dual = imag[pos] - imag[pos_dual];
                  coseno = cos(2*PI*i/NumDatosGrupo);
                  seno   = sin(2*PI*i/NumDatosGrupo);
                  real[pos_dual] = real_dual*coseno + imag_dual*seno;
                  imag[pos_dual] = imag_dual*coseno - real_dual*seno ;
                  real[pos] = real_i;
                  imag[pos] = imag_i;
                }
                grupoini += NumDatosGrupo;
           }
      Grupos *= 2;
    }
    // Bit reversal
    pos = 0;
    for(i=0; i < NPuntos; i++)
        {
            pos = i;
            dual = 0;
            aux = NPuntos/2;
            for(j=0 ; j <Fases ; j++)
            {
                dual = dual + (pos %2) * aux;
                pos = pos/2;
                aux = aux/2;
            }
        if(dual > i){
            real_i = real[i];
            imag_i = imag[i];
            real[i] = real[dual];
            imag[i] = imag[dual];
            real[dual] = real_i;
            imag[dual] = imag_i;
		  }
		}
}
void __fastcall TForm1::Chart1ClickSeries(TCustomChart *Sender, TChartSeries *Series,
          int ValueIndex, TMouseButton Button, TShiftState Shift, int X,
          int Y)
{
if(Series==Series1)
Series5->AddXY(X,Y) ;
}
//---------------------------------------------------------------------------




void __fastcall TForm1::Series1Click(TChartSeries *Sender, int ValueIndex, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
int x1=0;

x1=Series1->XScreenToValue(X)/Frm;

if(Action92->Checked){
z=0;
switch(fRecortar)
{
case 0:
StatusBar1->Panels->Items[4]->Text="Selecci�n parcial";
Series5->Clear();
Series4->Clear();
Series4->AddXY(Series1->XScreenToValue(X),Series1->YScreenToValue(Y)) ;
Label20->Font->Color=clRed;
Label23->Font->Color=clBlack;
Label20->Caption="Desde: "+ IntToStr(x1);
fRecortar=1;
Desde=X;
desde=x1;

break;
case 1:

Series4->AddXY(Series1->XScreenToValue(X),Series1->YScreenToValue(Y)) ;

Label20->Font->Color=clBlack;
Label23->Font->Color=clRed;
Label23->Caption="Hasta: "+ IntToStr(x1);
fRecortar=0;
//temp=X;
Hasta=X;
hasta=x1;

for( int aa=desde;aa<hasta;aa++)
{

Series5->AddXY(Series1->XValue[aa],Series1->YValue[aa]);

}

Action22->Enabled=true;
if(hasta<desde)
{
String o= "Ordenamiento" ;
String s ="La  secuencia seleccionada esta invertida. Marque aceptar para solucionar el problema";
 if(Application->MessageBoxA(s.w_str(),o.w_str(),MB_OKCANCEL+MB_ICONWARNING)==IDOK )
 { long int tp=0;
 tp=desde;
 desde=hasta;

 hasta=tp;

 Label23->Caption="Hasta: "+ IntToStr(hasta);
 Label20->Caption="Desde: "+ IntToStr(desde);

 for( int aqa=desde;aqa<hasta;aqa++)
{

Series5->AddXY(Series1->XValue[aqa],Series1->YValue[aqa]);

}

 }
}

Action99->Enabled=true;
break;
}
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Series1MouseEnter(TObject *Sender)
{
Series1->Cursor=crUpArrow;
Series1->Color=clRed;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Series1MouseLeave(TObject *Sender)
{
Series1->Color=clMaroon;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Action92Execute(TObject *Sender)
{
if (!Action92->Checked)
   {
	Series5->Clear();
	Series4->Clear();
	 desde=0;
	 hasta=Series1->Count();
	 Label23->Caption="Hasta: "+ IntToStr(hasta);
     Label20->Caption="Desde: "+ IntToStr(desde);
	 StatusBar1->Panels->Items[4]->Text="Selecci�n completa";
	 Action22->Enabled=true;
	 Action99->Enabled=false;
   }else{

 SpeedButton16->Visible=0;
 SpeedButton4->Visible=1;
 Label22->Caption=" Normal";
 StatusBar1->Panels->Items[1]->Text="Se�al no protegida";

 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label19MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
press  = true;
X1 = X;
Y2 = Y;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label19MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
 if (press)
{
GetCursorPos(&pt);
Panel1->Left= pt.x - X1;
Panel1->Top = pt.y - Y2;

}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label19MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
press = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton7MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
ScrollAxis(Chart1->TopAxis,10);
  ScrollAxis(Chart1->BottomAxis,10);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton8MouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
SpeedButton8Click(Sender);
}
//---------------------------------------------------------------------------




void __fastcall TForm1::SpeedButton24MouseEnter(TObject *Sender)
{
/*ScrollAxis(Chart1->TopAxis,-10);
ScrollAxis(Chart1->BottomAxis,-10);    */
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton25MouseEnter(TObject *Sender)
{
 ScrollAxis(Chart1->TopAxis,10);
  ScrollAxis(Chart1->BottomAxis,10);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action93Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action94Execute(TObject *Sender)
{
 WaveFile wfs;


	OpenDialog6->Execute();

	String FF=	OpenDialog6->FileName;

if(wfs.OpenRead(FF.t_str()))
   {
	const dataLength = wfs.GetNumSamples();
	double *buf=new double [dataLength];
	//ShowMessage(FloatToStr(wfs.GetSampleRate()+1));

    Series1->Clear();

	for (int i = 0; i < dataLength; i++) {
		wfs.ReadSample(buf[i]);
		 Series1->AddXY((double)i/wfs.GetSampleRate(),buf[i]);

	}

OldXs=Series1->MaxXValue();
long int POS=OldXs*wfs.GetSampleRate();
Frm=(double)1/wfs.GetSampleRate();

OldYs=Series1->YScreenToValue(POS);
 Form1->AjustaChart(Form1->Series1->MinYValue(),Form1->Series1->MaxYValue(),0, Form1->OldXs);
 Form1->Outline1->Clear();
 Form1->Path_Name=ExtractFileName(FF);
 Form1->Outline1->Lines->Add("<<"+Form1->Path_Name+">>");
 StatusBar1->Panels->Items[0]->Text =FF;
 Action27->Enabled=true;
 RibbonComboBox1->Text=FF.t_str();
	}
else {
ShowMessage("Error abriendo el fichero de audio. La operaci�n ha sido interrumpida ");

}


 Form1->ListBox1->Items->Add(" ");
  String S1=">>Incorporada se�al de audio::";
 Form1->ListBox1->Items->Add(S1);
 String S2="  -- Frecuencia de muestreo :: "+IntToStr((int)wfs.GetSampleRate())+ " Hz";
 Form1->ListBox1->Items->Add(S2);
 String S3="  -- N�mero de muestras : : "+IntToStr((int)wfs.GetNumSamples());
 Form1->ListBox1->Items->Add(S3);
 String S4="  -- N�mero de canales :: "+ FloatToStr(wfs.GetNumChannels());
 Form1->ListBox1->Items->Add(S4);
 String S5="  -- Duraci�n(seg) "+FloatToStr(wfs.GetNumSeconds())+" seg";
 Form1->ListBox1->Items->Add(S5);
 String S6="  -- Tama�o del fichero(byte) "+FloatToStr(wfs.GetDataLength())+" byte";
 Form1->ListBox1->Items->Add(S6);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action96Execute(TObject *Sender)
{OpenDialog2->FileName="          Seleccione el fichero(txt)";
OpenDialog2->Execute();
{

Patht=new char [strlen(OpenDialog2->FileName.t_str())];
Patht= OpenDialog2->FileName;
StatusBar1->Panels->Items[0]->Text =Patht;
OpenSGNT() ;
fSaveOther=false;
OldXs=Series1->MaxXValue();
long int POS=OldXs*1/Frm;

OldYs=Series1->YScreenToValue(POS);
 Form1->AjustaChart(Form1->Series1->MinYValue(),Form1->Series1->MaxYValue(),0, Form1->OldXs);
 Form1->Outline1->Clear();
 Form1->Path_Name=ExtractFileName(Patht);
Form1->Outline1->Lines->Add("<<"+Form1->Path_Name+">>");



}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action97Execute(TObject *Sender)
{

if(Series1->Count()==0)
{
Clear=1;

}
else{
Clear=0;
Form1->OldXs=0.0;

}
if(!Clear)
if(fSave)
{
Form1->Chart1->AxesList->Bottom->Automatic=false;
Form1->Chart1->AxesList->Left->Automatic=false;

Form1->Series1->Clear();
Clear=1;


Form1->OldXs=0.0;
Form1->OldYs=0.0;

Form1->h=1;



}else{

String AA= "Guardar informaci�n " ;
String s ="�Desea guardar la informaci�n contenida en el proyecto actual?";
 if(Application->MessageBoxA(s.w_str(),AA.w_str(),MB_YESNO+MB_ICONWARNING)==IDYES )
 {

if(!flatPaht)
{


SaveDialog1->Execute();
if(SaveDialog1->FileName!="")
{

Path=new char [strlen(SaveDialog1->FileName.t_str())+5];
 Path= SaveDialog1->FileName+".sbio";
SaveSGN() ;
 flatPaht=true;
 Form1->Series1->Clear();
 fSave=true;
Action22->Enabled=false;
Clear=1;
}
}else
{
 SaveSGN() ;

 fSave=true;
 Action22->Enabled=false;
}

Action10->Enabled=false;


//********LIMPIA**********


Form1->Chart1->AxesList->Bottom->Automatic=false;
Form1->Chart1->AxesList->Left->Automatic=false;

 Form1->ListBox3->Items->Clear();
//Form1->Frm=0.001;



Form1->OldXs=0.0;
Form1->OldYs=0.0;

Form1->h=1;

}else
{
Form1->Chart1->AxesList->Bottom->Automatic=false;
Form1->Chart1->AxesList->Left->Automatic=false;

Form1->Series4->Clear();
Form1->Series5->Clear();
Form1->Series1->Clear();
Clear=1;



Form1->OldXs=0.0;
Form1->OldYs=0.0;

Form1->h=1;
Action22->Enabled=false;

}





}

 //AQUI EMPIEZO A ABRIR EL FICHERO



if(OpenDialog3->Execute())
{
 String szFileName1;
 String DAT=".dat";
 String HEA=".hea";
 String MDAT,MHEA;
fnsplit(OpenDialog3->FileName.t_str(),0,0,szFileName1.t_str(),0);
String ab=ExtractFilePath  (OpenDialog3->FileName).t_str();
MDAT=ab+szFileName1.t_str()+DAT;
MHEA=ab+szFileName1.t_str()+HEA;


/*****************Cargando cabecera**************/

fp1_212=fopen(MHEA.t_str(),"rb+");
if ( fp1_212>0 )
 {

 fgets(s, 1000000, fp1_212);
 sscanf(s,"%s %d %d %d \n\r",&name_hea1, &canales, &frec_m,&n_muestras);
 fgets(s, 1000000, fp1_212);
 for(int b=0;b<canales;b++)
 {

 sscanf(s,"\n \r %s %d %d %d %d %d \n\r", &name_dat, &formato[b], &int_por_mV[b],&res_bit[b],&value_zero_point[b],&first_value_test[b]);
 fgets(s, 1000000, fp1_212);



 }





 fclose(fp1_212);

 } else  ShowMessage("Error abriendo el fichero correspondiente.");





/***************Cargando Fichero .DAT**************/



buf_212= new unsigned char[3*n_muestras+1];
X_212= new double [n_muestras+1];
Y_212= new double [n_muestras+1];

fp_212=fopen(MDAT.t_str(),"rb+");
if ( fp_212>0 )
 {


	 i_212=fseek(fp_212, 0, 0) ;

  if (i_212>=0)
   {
	 n_212= fread(buf_212,sizeof(unsigned char),3*n_muestras, fp_212);
	 fclose(fp_212);
	 Series1->Clear();

	  ProgressBar1->Visible=true;
	 ProgressBar1->Max=3*n_muestras;
	 Series1->Visible=1;
	 Series7->Visible=0;
	 Series8->Visible=0;

	 int p=0;
	 if(canales==2)
	 {
	 for(long int f=0;f<3*n_muestras;f=f+3)
	 {

	  X_212[p]= (double)((((buf_212[f+1]&0x000f)<<8)|buf_212[f])-value_zero_point[0])/int_por_mV[0]/1000;
	  Y_212[p]= (double)((((buf_212[f+1]&0x00f0)<<4)|buf_212[f+2])-value_zero_point[1])/int_por_mV[1]/1000;

	  p++;

	   ProgressBar1->Position=f;

	  }

	   ProgressBar1->Visible=false;


	   Frm=(double)1/frec_m;

	   for(long int fg=0;fg<n_muestras;fg++)
	  {
	  Series1->AddXY(fg*Frm,X_212[fg]);
	  Series7->AddXY(fg*Frm,X_212[fg]);
	  Series8->AddXY(fg*Frm,Y_212[fg]);
	  }

	  }else if (canales==1)
	   {
		ShowMessage("Incompatible para un solo canal. P�ngase en contacto con el fabricante");

	   }

	   OldXs=Series1->MaxXValue();
	   long int POS=OldXs*1/Frm;
	   OldYs=Series1->YScreenToValue(POS);

	  Form1->AjustaChart(Form1->Series1->MinYValue(),Form1->Series1->MaxYValue(),0, 5*Frm*frec_m);

String S_Path;
S_Path=MDAT;
Form1->Path_Name=ExtractFileName(S_Path);

Form1->Outline1->Lines->Clear();
Form1->Outline1->Lines->Add("<<"+Form1->Path_Name+">>");
for(int nc=0;nc<canales;nc++)
Form1->Outline1->Lines->Add("-- Canal "+IntToStr(nc));
Label10->Caption=IntToStr(0) ;

StatusBar1->Panels->Items[0]->Text =S_Path;
 Form1->StatusBar1->Panels->Items[5]->Text=" <N> "+IntToStr(Form1->Series1->Count());


//name_hea1, &canales, &frec_m,&n_muestras


//&name_dat, &formato[b], &int_por_mV[b],&res_bit[b],&value_zero_point[b],&first_value_test[b]


Action76Execute(Sender);

Form1->ListBox1->Items->Add(" ");
  String S1=">>Fichero de formato 2-12";
  Form1->ListBox1->Items->Add(" ");
   String Ss="  <<< Cabecera :: "+IntToStr(n_muestras);
 Form1->ListBox1->Items->Add(Ss);
 Form1->ListBox1->Items->Add(S1);

 String S3="  -- N�mero de canales :: "+IntToStr(canales);
 Form1->ListBox1->Items->Add(S3);
 String S4="  -- Frecuencia de muestreo :: "+IntToStr(frec_m)+" Hz";
 Form1->ListBox1->Items->Add(S4);
 String S5="  -- N�mero de muestras :: "+IntToStr(n_muestras);
 Form1->ListBox1->Items->Add(S5);
  String S6="  -- Resoluci�n (C1-C2) (int_por_mV) :: "+IntToStr(int_por_mV[0])+"-"+IntToStr(int_por_mV[1]);
 Form1->ListBox1->Items->Add(S6);

   String S7="  -- Resoluci�n (bit) (C1-C2) :: "+IntToStr(res_bit[0])+"-"+IntToStr(res_bit[1]);
 Form1->ListBox1->Items->Add(S7);




	}
   }  else ShowMessage("Error abriendo el fichero correspondiente.");
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action98Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action99Execute(TObject *Sender)
{

double *Sx = new double [Form1->Series1->Count()+5];
double *Sy = new double [Form1->Series1->Count()+5];
//int res0=Form1->desde;
//int res1=Form1->hasta;

int res=Form1->hasta-Form1->desde;

int c=0;
for(int k=0;k<desde;k++)
{

 Sx[k]=Form1->Series1->XValue[k];
 Sy[k]=Form1->Series1->YValue[k];
 c++;
}
for(int k1=hasta;k1<Form1->Series1->Count();k1++)
{

 Sx[c]=Form1->Series1->XValue[k1-res];
 Sy[c]=Form1->Series1->YValue[k1];
 c++;
}

Form1->Series1->Clear();
Series5->Clear();
Series4->Clear();
 for(int k2=0;k2<c;k2++)
{

Form1->Series1->AddXY(Sx[k2],Sy[k2]);

}

Form1->OldXs=Form1->Series1->MaxXValue();
Form1->OldYs=Form1->Series1->YValue[Form1->Series1->LastValueIndex];

//Form1->AjustaChart(Form1->Series1->MinYValue(),Form1->Series1->MaxYValue(),0, Form1->OldXs);

Action99->Enabled=false;

}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton22Click(TObject *Sender)
{
try{
Form10->SpeedButton1->Enabled=true;
Form10->Series3->Clear();

for(long int g=0;g<Form1->ListBox3->Items->Count;g++)
Form10->Series3->AddXY(g*Frm,V_BIN[g]);
Form10->Show();
SpeedButton22->Visible=false;
Form10->Series3->Title="Cuantificada";
} catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema al intentar visualizar la serie principal cuantificada. Por favor verifique el contenido de la se�al de entrada, posteriormente realice una cuantificaci�n previa a esta serie y vuelva a intentarlo.");}


}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton14Click(TObject *Sender)
{
if(Form1->Series1->Count()==0)
{ShowMessage("No existe ninguna se�al disponible en el �rea de trabajo.");
 goto A;
}
Form8->Show();
 A:
}
//---------------------------------------------------------------------------









void __fastcall TForm1::Outline1Expand(TObject *Sender, int Index)
{
switch(Index)
{
 case 1:
   ShowMessage(ListBox1->Items->Text);
  break;

  case 2:

if(Label10->Caption!=0)
  {
	ProgressBar1->Visible=true;
   ProgressBar1->Max=Series7->Count();
  Series1->Clear();



  for(int j=0;j<Series7->Count();j++)
  {
  Series1->AddXY(Series7->XValue[j],Series7->YValue[j]);
  ProgressBar1->Position=j;

  }

  }
  Label10->Caption=0 ;
  ProgressBar1->Visible=false;
  break;

  case 3:

  if(Label10->Caption!=1)
  {
  ProgressBar1->Visible=true;
  ProgressBar1->Max=Series8->Count();
  Series1->Clear();



  for(int j=0;j<Series8->Count();j++)
  {
  Series1->AddXY(Series8->XValue[j],Series8->YValue[j]);
  ProgressBar1->Position=j;


  }
  }
   Label10->Caption=1 ;
   ProgressBar1->Visible=false;
  break;

  default:
  ShowMessage("No existen m�s canales disponibles en la memoria");

}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton23Click(TObject *Sender)
{
 Form1->AjustaChart(Form1->Series1->MinYValue(),Form1->Series1->MaxYValue(),Form1->Series1->MinXValue(),OldXs);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton20Click(TObject *Sender)
{
Form11->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton16Click(TObject *Sender)
{
if(z==1){
 SpeedButton16->Visible=true;
 SpeedButton4->Visible=false;
 Label22->Caption=" Normal";
 StatusBar1->Panels->Items[1]->Text="Modo::Escritura";
  z=0;
 }else{
   SpeedButton16->Visible=false;
 SpeedButton4->Visible=true;
  Label22->Caption=" Zoom";
  StatusBar1->Panels->Items[1]->Text="Modo::Lectura";
  z=1;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
 if(z==1){
 SpeedButton16->Visible=true;
 SpeedButton4->Visible=false;
 Label22->Caption=" Normal";
 StatusBar1->Panels->Items[1]->Text="Modo::Escritura";
  z=0;
 }else{
   SpeedButton16->Visible=false;
 SpeedButton4->Visible=true;
  Label22->Caption=" Zoom";
  StatusBar1->Panels->Items[1]->Text="Modo::Lectura";
  z=1;
 }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton24Click(TObject *Sender)
{
if(SaveDialog3->Execute())
{

String Pathqq=new char [strlen(SaveDialog3->FileName.t_str())+5];
 Pathqq= SaveDialog3->FileName+".bmp";
Chart1->SaveToBitmapFile(Pathqq);
}

}
//---------------------------------------------------------------------------



void __fastcall TForm1::Action101Execute(TObject *Sender)
{
Form11->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action102Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action103Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------






void __fastcall TForm1::PageControl4Change(TObject *Sender)
{
if(PageControl4->TabIndex==0)
{
 //****Espectro de potencia**********
  FFT_L();
}
if(PageControl4->TabIndex==1)
{
//****Espectro de frecuencia Amplitud **********
 double *outfft;
double *yfft;
double *xfft;
xfft=new double  [Form1->nFFT];
yfft=new double  [Form1->nFFT];
outfft=new double  [Form1->nFFT];
Series9->Clear();
for(int p=0;p<nFFT;p++)
{
xfft[p]=0;
yfft[p]=0;
outfft[p]=0;
}


for(int l=0;l<nFFT;l++)
{
 if(l<Form1->Series1->Count())
   xfft[l]=Series1->YValue[l];
 else
   xfft[l]=0;
}

fft(xfft,yfft,nFFT);

ProgressBar1->Max=nFFT;
ProgressBar1->Visible=true;

for(int a=0;a<nFFT/2;a++)
{
 outfft[a]= pow((xfft[a]*xfft[a]+  yfft[a]*yfft[a]),0.5);
 ProgressBar1->Position=a;
 outfft[0]=0;
 Series9->AddXY(((1/Form1->Frm)/2*a)/(Form1->nFFT/2),outfft[a]);
}
ProgressBar1->Visible=false;



}
if(PageControl4->TabIndex==2)
{
 //****Espectro de fase**********
 try{
 //****Espectro de frecuencia**********
 double *outfft;
double *yfft;
double *xfft;
xfft=new double  [Form1->nFFT];
yfft=new double  [Form1->nFFT];
outfft=new double  [Form1->nFFT];
Series10->Clear();
for(int p=0;p<nFFT;p++)
{
xfft[p]=0;
yfft[p]=0;
outfft[p]=0;
}


for(int l=0;l<nFFT;l++)
{
 if(l<Form1->Series1->Count())
   xfft[l]=Series1->YValue[l];
 else
   xfft[l]=0;
}

fft(xfft,yfft,nFFT);

ProgressBar1->Max=nFFT;
ProgressBar1->Visible=true;

for(int a=0;a<nFFT/2;a++)
{
 outfft[a]=180* ArcTan(yfft[a]/xfft[a])/PI;
 ProgressBar1->Position=a;

 Series10->AddXY(((1/Form1->Frm)/2*a)/(Form1->nFFT/2),outfft[a]);
}

ProgressBar1->Visible=false;



}

 catch(Exception &exception )
 {
 ShowMessage("Verifique los par�metros de la se�al de entrada. Existe un problema!");
 }
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action104Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action105Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action106Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Action107Hint(UnicodeString &HintStr, bool &CanShow)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action108Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action109Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------






































void __fastcall TForm1::ListBox1Click(TObject *Sender)
{
int indice=ListBox1->ItemIndex;
if(indice<ListBox1->GetCount())
StatusBar1->Panels->Items[0]->Text=  ListBox1->Items->Strings[indice].t_str();

}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton8Click(TObject *Sender)
{

ScrollAxis(Chart1->TopAxis,-10);
ScrollAxis(Chart1->BottomAxis,-10);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ExportarINF(char *A )
{ String  Patht;
if(SaveDialog2->Execute())
{

Patht=new char [strlen(SaveDialog2->FileName.t_str())];
Patht= SaveDialog2->FileName+".txt";

FILE *FP;
FP=fopen(Patht.t_str(),"w+");
 for(int g=0;g<strlen(A);g++)
 {
 fprintf(FP,"%c",A[g]);

 }
 fclose(FP);



}

}


void __fastcall TForm1::ExportarINF1(char *A)
{ String  Patht;
if(SaveDialog5->Execute())
{

Patht=new char [strlen(SaveDialog5->FileName.t_str())];
Patht= SaveDialog5->FileName+".inf";

FILE *FP;
FP=fopen(Patht.t_str(),"w+");
 for(int g=0;g<strlen(A);g++)
 {
 fprintf(FP,"%c",A[g]);

 }
 fclose(FP);



}

}





void __fastcall TForm1::Exportarcomotexto1Click(TObject *Sender)
{

String A=ListBox1->Items->Text;

ExportarINF(A.t_str());
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Action110Execute(TObject *Sender)
{
ShowMessage("Tets");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action111Execute(TObject *Sender)
{
ShowMessage(ListBox1->Items->Text);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::SpeedButton5Click(TObject *Sender)
{//Form10->SpeedButton1->Enabled=false;
 Form10->Series2->Title="Serie principal";
Form10->Series2->ReplaceList(Form10->Series2->YValues,Series1->YValues);
Form10->Series2->ReplaceList(Form10->Series2->XValues,Series1->XValues);

Form10->Show();
 //


}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight,
          bool &Resize)
{
ProgressBar1->Left=(StatusBar1->Left)+622;
ProgressBar1->Top=(StatusBar1->Top)+3;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Exportaratxt1Click(TObject *Sender)
{
String A=ListBox3->Items->Text;

ExportarINF(A.t_str());
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton15Click(TObject *Sender)
{
   String  Patht;
if(SaveDialog2->Execute())
{

Patht=new char [strlen(SaveDialog2->FileName.t_str())];
Patht= SaveDialog2->FileName+".txt";

FILE *FP;
FP=fopen(Patht.t_str(),"w+");

 switch(PageControl4->TabIndex)
 { case 0:
 fprintf(FP,"%s\n","Espectro de potencia");
 for(int g=0;g<Form1->Series3->Count();g++)
 {
 fprintf(FP,"%f\n",Form1->Series3->YValue[g]);

 }
 break;
 case 1:
 fprintf(FP,"%s\n","Espectro de Amplitud");
 for(int g=0;g<Form1->Series9->Count();g++)
 {
 fprintf(FP,"%f\n",Form1->Series9->YValue[g]);

 } break;
 case 2:
 fprintf(FP,"%s\n","Espectro de fase");
   for(int g=0;g<Form1->Series10->Count();g++)
 {
 fprintf(FP,"%f\n",Form1->Series10->YValue[g]);

 }break;


 }
 fclose(FP);
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton6Click(TObject *Sender)
{
Series1->Color = EditColor(this,Series1->Color);
}
//---------------------------------------------------------------------------




void __fastcall TForm1::Guardarcomentario1Click(TObject *Sender)
{
String A=RichEdit1->Lines->Text;

ExportarINF1(A.t_str());
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action112Execute(TObject *Sender)
{
Form5->Show();
Form5->PageControl2->TabIndex=0;
Form5->PageControl3->TabIndex=3;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action114Execute(TObject *Sender)
{
Form5->Show();
Form5->PageControl2->TabIndex=0;
Form5->PageControl3->TabIndex=1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action115Execute(TObject *Sender)
{Form5->Show();
Form5->PageControl2->TabIndex=0;
Form5->PageControl3->TabIndex=2;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action116Execute(TObject *Sender)
{Form5->Show();
Form5->PageControl2->TabIndex=0;
Form5->PageControl3->TabIndex=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action117Execute(TObject *Sender)
{ Form5->Show();
Form5->PageControl2->TabIndex=0;
Form5->PageControl3->TabIndex=4;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action118Execute(TObject *Sender)
{Form5->Show();
Form5->PageControl2->TabIndex=1;
Form5->PageControl1->TabIndex=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action119Execute(TObject *Sender)
{Form5->Show();
Form5->PageControl2->TabIndex=1;
Form5->PageControl1->TabIndex=1;


}
//---------------------------------------------------------------------------


void __fastcall TForm1::Action120Execute(TObject *Sender)
{
Form12->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Series1BeforeDrawValues(TObject *Sender)
{
Form1->OldXs=Form1->Series1->MaxXValue();
  Form1->OldYs=Form1->Series1->YValue[Form1->Series1->LastValueIndex];

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Series1ClearValues(TChartSeries *Sender)
{
Form1->OldXs=0.0;
  Form1->OldYs=0.0;

}
//---------------------------------------------------------------------------


void ifft(double *real, double *imag, int NPuntos)
{
 {

 int Fases, Grupos;
 int fase, grupo, NumDatosGrupo, dual;
 int i, j, grupoini, pos, pos_dual,aux;
 double real_i, imag_i, real_dual, imag_dual;
 double coseno, seno;
 Fases = log(NPuntos)/log(2.0F)+1;
 Grupos = 1;
 for(fase=0; fase< Fases; fase++)
    {
        NumDatosGrupo = NPuntos/Grupos ;
        dual = NumDatosGrupo/2;
        grupoini = 0;
        for(grupo = 0; grupo < Grupos; grupo++)
           {
            for(i=0; i< dual; i++)
                {
                  pos = i + grupoini;
                  pos_dual = pos + dual;
                  real_i = real[pos] + real[pos_dual];
                  imag_i = imag[pos] + imag[pos_dual];
                  real_dual = real[pos] - real[pos_dual];
                  imag_dual = imag[pos] - imag[pos_dual];
                  coseno = cos(2*PI*i/NumDatosGrupo);
				  seno   = sin(2*PI*i/NumDatosGrupo);
                  real[pos_dual] = real_dual*coseno - imag_dual*seno;
                  imag[pos_dual] = real_dual*seno + imag_dual*coseno;
                  real[pos] = real_i;
                  imag[pos] = imag_i;

				}
            grupoini += NumDatosGrupo;
           }
        Grupos *= 2;
    }
    // Bit reversal
    pos = 0;
    for(i=0; i < NPuntos; i++)
        {
            pos = i;
            dual = 0;
            aux = NPuntos/2;
            for(j=0 ; j <= Fases ; j++)
            {
                dual = dual + (pos %2) * aux;
                pos = pos/2;
                aux = aux/2;
            }
        if(dual > i){
            real_i = real[i];
            imag_i = imag[i];
            real[i] = real[dual];
            imag[i] = imag[dual];
            real[dual] = real_i;
            imag[dual] = imag_i;
          }
		}
 for(i=0; i< NPuntos; i++){
	 real[i] /= (double)NPuntos;
	 imag[i] /= (double)NPuntos;
	}
}

}

//**************************************************

void __fastcall TForm1::Action121Execute(TObject *Sender)
{
if(Series1->Count()==0)
{

ShowMessage("No hay se�al disponible en �rea de trabajo");
}else

try{
//****Espectro de frecuencia Amplitud **********
 double *outfft;
  double *outifft;
double *yfft;
double *xfft;
xfft=new double  [nFFT*2];
yfft=new double  [nFFT*2];
outfft=new double  [nFFT*2];
outifft=new double  [nFFT*2];


for(int p1=0;p1<nFFT*2;p1++)
 {outifft[p1]=0;
 outfft[p1]=0;
 }

for(int p=0;p<nFFT;p++)
{
xfft[p]=0;
yfft[p]=0;

}


for(int l=0;l<nFFT;l++)
{
 if(l<Form1->Series1->Count())
   xfft[l]=Series1->YValue[l];
 else
   xfft[l]=0;
}

fft(xfft,yfft,nFFT);

ProgressBar1->Max=nFFT;
ProgressBar1->Visible=true;

for(int a1=0;a1<nFFT;a1++)
{
 outfft[a1]=  yfft[a1];
 ProgressBar1->Position=a1;


}

ProgressBar1->Visible=false;

fft(outfft,outifft,nFFT);

Form10->Series1->Clear();
 if (nFFT>Series1->Count())
 {
 for(int a=0;a<Series1->Count();a++)
	Form10->Series1->AddXY((double)a*Frm,outifft[a]*2);

 }else
 {
  for(int a=0;a<nFFT;a++)

	 Form10->Series1->AddXY((double)a*Frm,outifft[a]*2);


 }
 Form10->SpeedButton1->Enabled=true;
Form10->Series1->Visible=true;
Form10->Series1->Title="IFFT";
Form10->Show();
 }
 catch(Exception &exception )
 {ShowMessage("Gesebio ha detectado un problema error realizando IFFT. Por favor verifique el contenido de la se�al de entrada y vuelva a intentarlo.");}




}
//---------------------------------------------------------------------------

void __fastcall TForm1::Hex1Click(TObject *Sender)
{
try{
int  k=ListBox3->Count;
Form1->ListBox3->Clear();

for(int o=0;o<k;o++)
	  {

		Form1->ListBox3->Items->Strings[o]= String(IntToHex(V_BIN[o],16));
	  }
	  }

	 catch(Exception &exception ){
	  ShowMessage("Error detectado. Debe hacer una cuantificaci�n previa de la Serie principal ");

	  }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Mostrarendecimal1Click(TObject *Sender)
{try{
int  k=ListBox3->Count;
Form1->ListBox3->Clear();

for(int o=0;o<k;o++)
	  {

		Form1->ListBox3->Items->Strings[o]= String((V_BIN[o]));
	  }
	  }
	 catch(Exception &exception ){
	  ShowMessage("Error detectado. Debe hacer una cuantificaci�n previa de la Serie principal ");

	  }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Action122Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action123Execute(TObject *Sender)
{
 Cleaning();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	Form1->Hebra1 = new TConcurent(true);  // Creation suspended--the second process does not run yet.
	Form1->Hebra1->FreeOnTerminate = true;// No need to clean up after termination
	Form1->Hebra1->Priority = tpLower;   // Set the priority to lower than normal.
	Form1->Hebra1->Start();             // Ahora arranca la hebra.
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action124Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action125Execute(TObject *Sender)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action128Execute(TObject *Sender)
{
if (!Panel6->Visible)
{
Panel6->Visible=true;
} else
 Panel6->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Action129Execute(TObject *Sender)
{
if (!Panel1->Visible)
{
Panel1->Visible=true;
} else
 Panel1->Visible=false;
}
//---------------------------------------------------------------------------

