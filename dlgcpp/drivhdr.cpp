extern "C" {
  #define INCL_WINDIALOGS
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
| SampleCommandHandler::SampleCommandHandler                                   |
------------------------------------------------------------------------------*/
SampleCommandHandler :: SampleCommandHandler( SampleDialog& dialogue )
    : ICommandHandler( ),
      sampleDialog( dialogue )
{
}

/*------------------------------------------------------------------------------
| SampleCommandHandler::~SampleCommandHandler                                  |
------------------------------------------------------------------------------*/
SampleCommandHandler :: ~SampleCommandHandler( )
{
}

/*------------------------------------------------------------------------------
| SampleCommandHandler::command                                                |
------------------------------------------------------------------------------*/
Boolean SampleCommandHandler :: command( ICommandEvent& cmdevt )
{

  switch ( cmdevt.commandId( ) )
  {
    case DID_CANCEL:
      sampleDialog.dismiss( DID_CANCEL );
      break;

    case PB_QUERY:
      {
        IMultiLineEdit
          *pMLE = sampleDialog.mleWithId( MLE_TEST );

        pMLE->addLineAsLast( "*************** Query Results ***************" );

        // Simple combobox, so just grab entryfield text ...
        pMLE->addLineAsLast( IString( "Combo box selected item = " +
                             sampleDialog.comboBoxWithId( CB_TEST )->text() ) );

        // Display list box selected item
        IListBox
          *pListBox = sampleDialog.listBoxWithId( LB_TEST );
        pMLE->addLineAsLast( IString( "List box selected item = " +
                             pListBox->itemText( pListBox->selection() ) ) );

        // Display numeric spin button value
        IString
          strValue( sampleDialog.numericSpinButtonWithId( SPB_TEST )->value() );
        pMLE->addLineAsLast( IString( "Numeric spin button value = " +
                             strValue ) );

      }
      return( true );      // Finished processing event

  }
                           // Allow other handlers or default window procedure
  return( false );         // to process the event
}


/*------------------------------------------------------------------------------
| SampleSelectHandler::SampleSelectHandler                                     |
------------------------------------------------------------------------------*/
SampleSelectHandler :: SampleSelectHandler( SampleDialog& dialogue )
    : ISelectHandler( ),
      sampleDialog( dialogue )
{
}

/*------------------------------------------------------------------------------
| SampleSelectHandler::~SampleSelectHandler                                    |
------------------------------------------------------------------------------*/
SampleSelectHandler :: ~SampleSelectHandler( )
{
}

/*------------------------------------------------------------------------------
| SampleSelectHandler::selected                                                |
------------------------------------------------------------------------------*/
Boolean SampleSelectHandler :: selected( IControlEvent& ctlevt )
{
  if ( ctlevt.controlId() == LB_TEST )
  {
    IStaticText
      *pStaticText = sampleDialog.staticTextWithId( ST_TEXT );

    IListBox
      *pListBox = sampleDialog.listBoxWithId( LB_TEST );
        pStaticText->setText( pListBox->itemText( pListBox->selection() ) );

    return( true );        // Finished processing event
  }
                           // Allow other handlers or default window procedure
  return( false );         // to process the event
}


/*------------------------------------------------------------------------------
| SampleObserver::SampleObserver                                               |
------------------------------------------------------------------------------*/
SampleObserver :: SampleObserver( SampleDialog& dialogue )
    : IObserver( ),
      sampleDialog( dialogue )
{
  IObserver *x = this;
}

/*------------------------------------------------------------------------------
| SampleObserver::~SampleObserver                                              |
------------------------------------------------------------------------------*/
SampleObserver :: ~SampleObserver( )
{
}

/*------------------------------------------------------------------------------
| SampleObserver::dispatchNotificationEvent                                    |
------------------------------------------------------------------------------*/
SampleObserver& SampleObserver ::
                dispatchNotificationEvent  ( const INotificationEvent& event )
{
  if ( event.notificationId() == ICircularSlider::valueId )
  {
    IEntryField
      *pEntryField = sampleDialog.entryFieldWithId( EF_TEST );

    IProgressIndicator
      *pProgressIndicator = sampleDialog.progressIndicatorWithId( SLD_TEST );

    unsigned long
      ulValue = event.eventData().asUnsignedLong();
    pEntryField->setText( IString( ulValue ) );
    pProgressIndicator->moveArmToTick( ulValue );
  }

  return( *this );
}


/*------------------------------------------------------------------------------
| MyFrameCommandHandler::MyFrameCommandHandler                                 |
------------------------------------------------------------------------------*/
MyFrameCommandHandler :: MyFrameCommandHandler( MyFrame& aFrame )
    : ICommandHandler( ),
      myFrame( aFrame )
{
}

/*------------------------------------------------------------------------------
| MyFrameCommandHandler::~MyFrameCommandHandler                                |
------------------------------------------------------------------------------*/
MyFrameCommandHandler :: ~MyFrameCommandHandler( )
{
}

/*------------------------------------------------------------------------------
| MyFrameCommandHandler::command                                               |
------------------------------------------------------------------------------*/
Boolean MyFrameCommandHandler :: command( ICommandEvent& cmdevt )
{

  switch ( cmdevt.commandId( ) )
  {
    case DID_CANCEL:
      myFrame.close();
      break;

    case ID_CREATEBUTTON:
      {
        SampleDialog
         *pSampleDialog = myFrame.dialog();

        if ( pSampleDialog )
        {
          pSampleDialog->show();
          pSampleDialog->setFocus();
        }
        else
        {
          pSampleDialog = new SampleDialog( DLG_SAMPLEDIALOGUE, &myFrame );
          myFrame.setDialog( pSampleDialog );
        }
      }
      return( true );      // Finished processing event

  }
                           // Allow other handlers or default window procedure
  return( false );         // to process the event
}

