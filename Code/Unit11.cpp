//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit11.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm11 *Form11;
//---------------------------------------------------------------------------
__fastcall TForm11::TForm11(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm11::Image1Click(TObject *Sender)
{
this->Close();
}
//---------------------------------------------------------------------------


void __fastcall TForm11::Image1MouseEnter(TObject *Sender)
{
AlphaBlendValue=255;


}
//---------------------------------------------------------------------------

void __fastcall TForm11::Image1MouseLeave(TObject *Sender)
{
Sleep(15) ;
AlphaBlendValue=225;
Sleep(15) ;
AlphaBlendValue=200;
Sleep(15) ;
AlphaBlendValue=190;
Sleep(15) ;
AlphaBlendValue=170;
Sleep(15) ;
AlphaBlendValue=150;
Sleep(15) ;
AlphaBlendValue=130;
Sleep(15) ;
}
//---------------------------------------------------------------------------

