//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm4::BitBtn1Click(TObject *Sender)
{
 Form1->Chart1->AxesList->Bottom->Automatic=false;
 Form1->Chart1->AxesList->Left->Automatic=false;

Form1->Series1->Clear();
  //Form1->Series1->AddXY(0,0);
  Form1->Frm=StrToFloat(Edit11->Text);
  Form1->OldXs=0.0;
Form1->OldYs=0.0;

 Form1->h=1;
  Form4->Close();

  //definir la cantidad de pnts que va a tener la X y la Y en Mapa de dibujo
  //definido a partir de la frecuencia de muentreo y el Vpp=+-5

   //Form1->AjustaChart(-5,5,Form1->Frm);



}
//---------------------------------------------------------------------------

