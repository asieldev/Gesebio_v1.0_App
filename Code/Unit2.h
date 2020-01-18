//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include "Unit1.h"
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Ribbon.hpp>
#include <RibbonLunaStyleActnCtrls.hpp>
#include <RibbonActnCtrls.hpp>
#include <RibbonSilverStyleActnCtrls.hpp>
#include <RibbonObsidianStyleActnCtrls.hpp>
#include <Buttons.hpp>
#include <pngimage.hpp>
#include <Graphics.hpp>
#include <Dialogs.hpp>
#include <OleCtrls.hpp>
//---------------------------------------------------------------------------


class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TLabel *Label1;
	TSpeedButton *SpeedButton3;
	TOpenDialog *OpenDialog1;
	TListBox *ListBox1;
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);



private:	// User declarations
public:		// User declarations
double *A;
int HZ;
int Total;
double TS;

	__fastcall TForm2(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;


//---------------------------------------------------------------------------
#endif
