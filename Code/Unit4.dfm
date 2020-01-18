object Form4: TForm4
  Left = 366
  Top = 307
  BorderStyle = bsDialog
  Caption = '   Dibujar Se'#241'al'
  ClientHeight = 97
  ClientWidth = 318
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox5: TGroupBox
    Left = 8
    Top = 8
    Width = 297
    Height = 56
    Caption = 'Dato generales'
    TabOrder = 0
    object Label23: TLabel
      Left = 9
      Top = 21
      Width = 161
      Height = 13
      Caption = 'Definir Per'#237'odo de Muestreo(seg) '
    end
    object Edit11: TEdit
      Left = 176
      Top = 18
      Width = 97
      Height = 21
      TabOrder = 0
    end
  end
  object BitBtn1: TBitBtn
    Left = 134
    Top = 70
    Width = 62
    Height = 19
    Caption = 'Aceptar'
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 1
    OnClick = BitBtn1Click
  end
end
