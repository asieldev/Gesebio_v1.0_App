//---------------------------------------------------------------------------

#include <vcl.h>
#include <string.h>
 #include <math.h>
#include "Unit2.h"

#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm2 *Form2;

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}

void __fastcall TForm2::SpeedButton3Click(TObject *Sender)
{

exit(1);
}
//---------------------------------------------------------------------------





void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
exit(1);
}
//---------------------------------------------------------------------------




