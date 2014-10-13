extern "C" {
  #define INCL_WINDIALOGS
  #define INCL_WINFRAMEMGR
  #include <os2.h>
}

#include <iframe.hpp>
#include <icombobx.hpp>
#include <ilistbox.hpp>
#include <ipushbut.hpp>
#include <istattxt.hpp>
#include <ispinnum.hpp>
#include <ientryfd.hpp>
#include <islider.hpp>
#include <icslider.hpp>
#include <imle.hpp>

#include "driver.hpp"
#include "driver.h"

/*------------------------------------------------------------------------------
| main                                                                         |
------------------------------------------------------------------------------*/
main()
{
  MyFrame myFrame;
  IApplication::current().run();
}


/*------------------------------------------------------------------------------
| MyFrame::MyFrame                                                             |
------------------------------------------------------------------------------*/
MyFrame::MyFrame( )
  : IFrameWindow( "Manipulating Dialogues in C++",
                  ID_MYFRAME,
                  IFrameWindow::defaultStyle() | IFrameWindow::shellPosition ),
    clientCanvas( FID_CLIENT, this, this ),
    createButton ( ID_CREATEBUTTON, &clientCanvas, &clientCanvas ),
    quitButton ( DID_CANCEL, &clientCanvas, &clientCanvas ),
    pSampleDlg( 0 ),
    commandHandler( *this )

{
  createButton
    .setText( "Create Dialogue" )
    .enableTabStop();

  quitButton
    .setText( "Quit" )
    .enableTabStop();

  commandHandler.handleEventsFor( this );

  setClient( &clientCanvas );
  sizeTo( ISize( 100, 100) + clientCanvas.minimumSize( ) );
  show();
  setFocus();
}


/*------------------------------------------------------------------------------
| MyFrame::~MyFrame                                                            |
------------------------------------------------------------------------------*/
MyFrame:: ~MyFrame( )
{
  delete this->pSampleDlg;
}


/*------------------------------------------------------------------------------
| MyFrame::dialog                                                              |
------------------------------------------------------------------------------*/
SampleDialog* MyFrame:: dialog() const
{
  return( this->pSampleDlg );
}

/*------------------------------------------------------------------------------
| MyFrame::setDialog                                                           |
------------------------------------------------------------------------------*/
MyFrame& MyFrame:: setDialog( SampleDialog* sampleDialog )
{
  this->pSampleDlg = sampleDialog;
  return( *this );
}


/*------------------------------------------------------------------------------
| SampleDialog::SampleDialog                                                   |
------------------------------------------------------------------------------*/
SampleDialog :: SampleDialog( unsigned long ulWindowId, IWindow* pOwner )
    : Dialog( ulWindowId, pOwner ),
      commandHandler( *this ),
      selectHandler( *this ),
      sampleObserver( *this )
{
  createControlsFromTemplate( );

  commandHandler.handleEventsFor( this );
  selectHandler.handleEventsFor( this );
}


/*------------------------------------------------------------------------------
| SampleDialog::~SampleDialog                                                  |
------------------------------------------------------------------------------*/
SampleDialog :: ~SampleDialog( )
{
}


/*------------------------------------------------------------------------------
| SampleDialog::comboBox                                                       |
------------------------------------------------------------------------------*/
SampleDialog& SampleDialog :: comboBox( IComboBox* pComboBox )
{
  unsigned long i;

  for (i = 1; i < 11; i++)
    pComboBox->addAsLast( "CB Item" + IString( i ) );

  pComboBox->select( 0 );
  return( *this );
}

/*------------------------------------------------------------------------------
| SampleDialog::listBox                                                        |
------------------------------------------------------------------------------*/
SampleDialog& SampleDialog :: listBox( IListBox* pListBox )
{
  unsigned long i;

  for (i = 1; i < 11; i++)
    pListBox->addAsLast( "LB Item" + IString( i ) );

  pListBox->select( 0 );
  return( *this );
}

/*------------------------------------------------------------------------------
| SampleDialog::pushButton                                                     |
------------------------------------------------------------------------------*/
SampleDialog& SampleDialog :: pushButton( IPushButton* pPushButton )
{
  return( *this );
}

/*------------------------------------------------------------------------------
| SampleDialog::staticText                                                     |
------------------------------------------------------------------------------*/
SampleDialog& SampleDialog :: staticText( IStaticText* pStaticText )
{
  return( *this );
}

/*------------------------------------------------------------------------------
| SampleDialog::numericSpinButton                                              |
------------------------------------------------------------------------------*/
SampleDialog& SampleDialog ::
              numericSpinButton( INumericSpinButton* pSpinButton )
{
  pSpinButton->setRange( IRange( 0, 50 ) );
  return( *this );
}

/*------------------------------------------------------------------------------
| SampleDialog::entryField                                                     |
------------------------------------------------------------------------------*/
SampleDialog& SampleDialog :: entryField( IEntryField* pEntryField )
{
  pEntryField->setText( IString( 25 ) );
  return( *this );
}

/*------------------------------------------------------------------------------
| SampleDialog::progressIndicator                                              |
------------------------------------------------------------------------------*/
SampleDialog& SampleDialog ::
              progressIndicator( IProgressIndicator* pProgressIndicator )
{
  pProgressIndicator->moveArmToTick( 25 );
  return( *this );
}

/*------------------------------------------------------------------------------
| SampleDialog::circularSlider                                                 |
------------------------------------------------------------------------------*/
SampleDialog& SampleDialog :: circularSlider( ICircularSlider* pCircularSlider )
{
  pCircularSlider->setArmRange( IRange( 0, 50 ) )
                  .setRotationIncrement( 5 )
                  .setTickSpacing( 5 )
                  .setValue( 25 )
                  .enableNotification();

  sampleObserver.handleNotificationsFor( *pCircularSlider );

  return( *this );
}

/*------------------------------------------------------------------------------
| SampleDialog::mle                                                            |
------------------------------------------------------------------------------*/
SampleDialog& SampleDialog :: mle( IMultiLineEdit* pMLE )
{
  return( *this );
}

