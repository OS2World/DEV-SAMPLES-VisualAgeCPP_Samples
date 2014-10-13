#include <iwindow.hpp>
#include <inotifev.hpp>
#include <isetcv.hpp>
#include "dialog.hpp"
#include "drivhdr.hpp"

/*******************************************************************************
* SampleDialog Class                                                           *
*******************************************************************************/
class SampleDialog : public Dialog {
typedef Dialog
  Inherited;
public:
/*------------------------------- Constructors -------------------------------*/
  SampleDialog  ( unsigned long id, IWindow* owner );

virtual
  ~SampleDialog ( );

/*------------------------------ Control Creation ----------------------------*/
virtual SampleDialog
 &comboBox           ( IComboBox*                aComboBox ),
 &listBox            ( IListBox*                 aListBox ),
 &pushButton         ( IPushButton*              aPushButton ),
 &staticText         ( IStaticText*              aStaticText ),
 &numericSpinButton  ( INumericSpinButton*       aSpinButton ),
 &entryField         ( IEntryField*              anEntryField ),
 &progressIndicator  ( IProgressIndicator*       aProgressIndicator ),
 &circularSlider     ( ICircularSlider*          aCircularSlider ),
 &mle                ( IMultiLineEdit*           aMLE );

private:
/*--------------------------------- Private ----------------------------------*/
SampleCommandHandler
  commandHandler;

SampleSelectHandler
  selectHandler;

SampleObserver
  sampleObserver;

};


/*******************************************************************************
* MyFrame Class                                                                *
*******************************************************************************/
class MyFrame : public IFrameWindow {
typedef IFrameWindow
  Inherited;
public:
/*------------------------------- Constructors -------------------------------*/
  MyFrame  ( );

virtual
  ~MyFrame ( );

/*------------------------------- Sample Dialog ------------------------------*/
virtual SampleDialog
 *dialog    ( ) const;

virtual MyFrame
 &setDialog ( SampleDialog* sampleDialog );

private:
/*--------------------------------- Private ----------------------------------*/
ISetCanvas
  clientCanvas;

IPushButton
  createButton,
  quitButton;

MyFrameCommandHandler
  commandHandler;

SampleDialog
 *pSampleDlg;
};

