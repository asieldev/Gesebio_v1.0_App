//---------------------------------------------------------------------------

#ifndef Unit7H
#define Unit7H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <pngimage.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Graphics.hpp>
#include "Chart.hpp"
#include "Series.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include <Menus.hpp>
//---------------------------------------------------------------------------
typedef struct complex
{
double x,y;

}complex;


typedef struct Filt_Params
{
double x,y;

}Filt_Params;


class TForm7 : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TLabel *Label12;
	TBevel *Bevel1;
	TSpeedButton *SpeedButton1;
	TPageControl *PageControl2;
	TTabSheet *TabSheet5;
	TTabSheet *TabSheet6;
	TPageControl *PageControl1;
	TTabSheet *TabSheet3;
	TGroupBox *GroupBox3;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label3;
	TEdit *Edit5;
	TEdit *Edit6;
	TComboBox *ComboBox1;
	TTabSheet *TabSheet4;
	TGroupBox *GroupBox5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TEdit *Edit4;
	TComboBox *ComboBox3;
	TGroupBox *GroupBox6;
	TImage *Image4;
	TBitBtn *BitBtn3;
	TTabSheet *TabSheet2;
	TGroupBox *GroupBox2;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *Edit1;
	TEdit *Edit2;
	TComboBox *ComboBox2;
	TEdit *Edit9;
	TGroupBox *GroupBox4;
	TImage *Image3;
	TBitBtn *BitBtn2;
	TTabSheet *TabSheet1;
	TGroupBox *GroupBox8;
	TImage *Image5;
	TBitBtn *BitBtn4;
	TBitBtn *BitBtn1;
	TImage *Image2;
	TPageControl *PageControl3;
	TTabSheet *TabSheet7;
	TGroupBox *GroupBox9;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	TEdit *Edit11;
	TEdit *Edit12;
	TBitBtn *BitBtn5;
	TTabSheet *TabSheet8;
	TGroupBox *GroupBox11;
	TImage *Image6;
	TBitBtn *BitBtn6;
	TTabSheet *TabSheet9;
	TGroupBox *GroupBox12;
	TLabel *Label26;
	TLabel *Label27;
	TLabel *Label28;
	TEdit *Edit15;
	TEdit *Edit16;
	TEdit *Edit17;
	TGroupBox *GroupBox13;
	TImage *Image7;
	TBitBtn *BitBtn7;
	TTabSheet *TabSheet10;
	TGroupBox *GroupBox15;
	TImage *Image8;
	TBitBtn *BitBtn8;
	TGroupBox *GroupBox16;
	TChart *Chart2;
	TLineSeries *LineSeries1;
	TLineSeries *LineSeries2;
	TGroupBox *GroupBox17;
	TListBox *ListBox2;
	TGroupBox *GroupBox18;
	TLabel *Label21;
	TImage *Image9;
	TImage *Image11;
	TGroupBox *GroupBox10;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Label24;
	TEdit *Edit13;
	TEdit *Edit14;
	TBitBtn *BitBtn9;
	TBitBtn *BitBtn10;
	TGroupBox *GroupBox14;
	TLabel *Label25;
	TLabel *Label29;
	TLabel *Label30;
	TEdit *Edit18;
	TEdit *Edit19;
	TEdit *Edit20;
	TBitBtn *BitBtn11;
	TPageControl *PageControl4;
	TTabSheet *TabSheet12;
	TBitBtn *BitBtn13;
	TTabSheet *TabSheet13;
	TBitBtn *BitBtn14;
	TChart *Chart1;
	TLineSeries *LineSeries3;
	TLineSeries *LineSeries4;
	TChart *Chart3;
	TLineSeries *LineSeries5;
	TGroupBox *GroupBox1;
	TListBox *ListBox1;
	TEdit *Edit7;
	TBitBtn *BitBtn12;
	TBitBtn *BitBtn15;
	TGroupBox *GroupBox7;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label16;
	TLabel *Label17;
	TEdit *Edit3;
	TEdit *Edit8;
	TComboBox *ComboBox4;
	TEdit *Edit10;
	TBitBtn *BitBtn16;
	TGroupBox *GroupBox19;
	TLabel *Label31;
	TTabSheet *Notch;
	TGroupBox *GroupBox20;
	TLabel *Label32;
	TLabel *Label34;
	TEdit *Edit21;
	TEdit *Edit22;
	TBitBtn *BitBtn17;
	TSplitter *Splitter2;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton3;
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall BitBtn9Click(TObject *Sender);
	void __fastcall BitBtn10Click(TObject *Sender);
	void __fastcall BitBtn11Click(TObject *Sender);
	void __fastcall BitBtn5Click(TObject *Sender);
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall ListBox1Click(TObject *Sender);
	void __fastcall ListBox2Click(TObject *Sender);
	void __fastcall BitBtn12Click(TObject *Sender);
	void __fastcall BitBtn15Click(TObject *Sender);
	void __fastcall BitBtn16Click(TObject *Sender);
	void __fastcall BitBtn17Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm7(TComponent* Owner);
	void __fastcall LPHP(double FC,double FS,double *COEF,int N,int T);
	void __fastcall BP(double FC1,double FC2,double FS,double *COEF,int N);
	void __fastcall BR(double FC1,double FC2,double FS,double *COEF,int N);

	double *COEF;
	double *COEF1;
    bool t;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm7 *Form7;
//---------------------------------------------------------------------------
#endif
