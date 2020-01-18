//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit13.h"
#include "Unit1.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TConcurent::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TConcurent::TConcurent(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall TConcurent::Execute()
{
	NameThreadForDebugging("TConcurentName");

	Form1->StatusBar1->Panels->Items[5]->Text="<N> "+ IntToStr(Form1->Series1->Count());

	



}
//---------------------------------------------------------------------------
