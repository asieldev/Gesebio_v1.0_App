//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
int i=100;
int k=0;
char *T[8]={"Inicializando...ECG_01_1000","Inicializando...FOTO_01_1000","Inicializando...Abriendo.","Inicializando...Abriendo..","Inicializando...Abriendo...","Inicializando...Abriendo.....","Inicializando...Abriendo.....","Listo..."};
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Timer1Timer(TObject *Sender)
{




  AlphaBlendValue=i;
 i++;
  if(i>=255)
  {
  i=255;
  k++;
   Sleep(1000);
  Label1->Caption= (T[k]);


  }
  if(k>7){
  Timer1->Enabled=false;
  for(int o=255;o>0;o--) {
   AlphaBlendValue=o;
	//Sleep(50);
  }
WinExec("Gesebiov1.exe",SW_SHOWDEFAULT);
Close();

  }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormActivate(TObject *Sender)
{
FILE *fp_ECG_01_1000;
 FILE *fp_FOTHO_01_10000;
 fp_ECG_01_1000=fopen("ECG_01_1000.dat","rb");
 fp_FOTHO_01_10000=fopen("FOTO_01_1000.dat","rb");

  if (fp_ECG_01_1000==0)
   {
   Timer1->Enabled=false;
   ShowMessage("Error al intentar abrir ECG_01_1000.dat necesario para la ejecución de esta aplicación. Compruebe que el fichero existe. Si el problema no es solucionado contacte urgente a los diseñadores ");

  exit(1);
  }
	if ( fp_FOTHO_01_10000==0)
	 {
	 Timer1->Enabled=false;
   ShowMessage("Error al intentar abrir FOTO_01_1000.dat necesario para la ejecución de esta aplicación. Compruebe que el fichero existe. Si el problema no es solucionado contacte urgente a los diseñadores ");
   exit(1);
   }
}
//---------------------------------------------------------------------------

