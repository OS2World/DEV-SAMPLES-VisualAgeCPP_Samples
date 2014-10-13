extern "C" {
  #define INCL_DOS                   /* Include OS/2 PM DOS Interface     */
  #define INCL_GPI                   /* Include OS/2 PM GPI Interface     */
  #define INCL_WIN                   /* Include OS/2 PM Windows Interface */
  #include <os2.h>
}

#include <igraphbt.hpp>
#include <ipushbut.hpp>
#include <icheckbx.hpp>
#include <i3statbx.hpp>
#include <iradiobt.hpp>
#include <iscroll.hpp>
#include <ilistbox.hpp>
#include <ientryfd.hpp>
#include <istattxt.hpp>
#include <igroupbx.hpp>
#include <iiconctl.hpp>
#include <ibmpctl.hpp>
#include <icombobx.hpp>
#include <imle.hpp>
#include <ispinnum.hpp>
#include <ispintxt.hpp>
#include <icnrctl.hpp>
#include <islider.hpp>
#include <inotebk.hpp>
#include <icslider.hpp>
#include <ithread.hpp>
#include <iexcept.hpp>

#include "dialog.hpp"

/************************************************************************/
/************************************************************************/
/************************************************************************/
/* DISCLAIMER OF WARRANTIES:                                            */
/* -------------------------                                            */
/* The following [enclosed] code is sample code created by IBM          */
/* Corporation and Prominare Inc.  This sample code is not part of any  */
/* standard IBM product and is provided to you solely for the purpose   */
/* of assisting you in the development of your applications.  The code  */
/* is provided "AS IS", without warranty of any kind.  Neither IBM nor  */
/* Prominare shall be liable for any damages arising out of your        */
/* use of the sample code, even if they have been advised of the        */
/* possibility of such damages.                                         */
/************************************************************************/
/************************************************************************/
/************************************************************************/
/*                     D I S C L A I M E R                              */
/* This code is provided on an as is basis with no implied support.     */
/* It should be considered freeware that cannot be rebundled as         */
/* part of a larger "*ware" offering without our consent.               */
/************************************************************************/
/************************************************************************/
/************************************************************************/

/* Copyright ¸ International Business Machines Corp., 1995.             */
/* Copyright ¸ 1995  Prominare Inc.  All Rights Reserved.               */

/* -------------------------------------------------------------------- */


/* -- Standard Window Classes ----------------------------------------- */

#define WINCLASS_FRAME             0x00000001L
#define WINCLASS_COMBOBOX          0x00000002L
#define WINCLASS_BUTTON            0x00000003L
#define WINCLASS_MENU              0x00000004L
#define WINCLASS_STATIC            0x00000005L
#define WINCLASS_ENTRYFIELD        0x00000006L
#define WINCLASS_LISTBOX           0x00000007L
#define WINCLASS_SCROLLBAR         0x00000008L
#define WINCLASS_TITLEBAR          0x00000009L
#define WINCLASS_MLE               0x0000000AL
/* 000B to 000F reserved */
#define WINCLASS_APPSTAT           0x00000010L
#define WINCLASS_KBDSTAT           0x00000011L
#define WINCLASS_PECIC             0x00000012L
#define WINCLASS_DBE_KKPOPUP       0x00000013L
/* 0014 to 001F reserved */
#define WINCLASS_SPINBUTTON        0x00000020L
/* 0021 to 0024 reserved */
#define WINCLASS_CONTAINER         0x00000025L
#define WINCLASS_SLIDER            0x00000026L
#define WINCLASS_VALUESET          0x00000027L
#define WINCLASS_NOTEBOOK          0x00000028L
#define WINCLASS_HWXENTRY          0x00000029L
#define WINCLASS_SKETCH            0x0000002aL
/* 002b to 0030 reserved */
/* 0030 to 003F reserved */
#define WINCLASS_GRAPHICBUTTON     0x00000040L
#define WINCLASS_CIRCULARSLIDER    0x00000041L


/*------------------------------------------------------------------------------
| Dialog::Dialog                                                               |
------------------------------------------------------------------------------*/
Dialog :: Dialog( unsigned long ulWindowId,
                  IWindow*      pOwner ) :
   IFrameWindow( deferCreation ),
   ulId( ulWindowId )
{
  IThread::current().initializeGUI();

  IResourceId
    resId( ulWindowId );

  IResourceLibrary
    resLib( resId.resourceLibrary() );

  IWindowHandle
    dialog = resLib.loadDialog( resId.id(),
                                0,
                                pOwner,
                                WinDefDlgProc,
                                0 );

                       /* Dialog was created.  Call IFrameWindow::start */
                       /* to create a new frame handler, add it to this */
                       /* frame window, and initiate message handling   */
                       /* for the window.                               */
  start( dialog );

} //Dialog::Dialog


/*------------------------------------------------------------------------------
| Dialog::~Dialog                                                              |
------------------------------------------------------------------------------*/
Dialog :: ~Dialog( )
{
}


/*------------------------------------------------------------------------------
| Dialog::createControlsFromTemplate                                           |
------------------------------------------------------------------------------*/
Dialog& Dialog :: createControlsFromTemplate( )
{
  PDLGTEMPLATE pdlgt;                /* Dialog Template Pointer         */
  void*        pvStart;              /* Dialog Template Item Pointer    */
  register unsigned long cItems,     /* Dialog Items Counter            */
                         ulRc,       /* Return code                     */
                         i;          /* Loop Counter                    */

                       /* Set mouse pointer to "wait" in case template  */
                       /* is large                                      */
  IPointerHandle oldPointer = mousePointer();
  ISystemPointerHandle systemPointer( ISystemPointerHandle::wait );
  setMousePointer( systemPointer );

                       /* Try reading in the dialog template for the    */
                       /* given dialog ID                               */
  ulRc = DosGetResource( 0, RT_DIALOG, this->ulId, (void **)&pdlgt );
  if ( ulRc != 0 )
  {
                       /* Dialog template not found;  reset mouse       */
                       /* pointer and throw exception                   */
    setMousePointer( oldPointer );
    ITHROWSYSTEMERROR( ulRc,
                       "DosGetResource",
                       IErrorInfo::accessError,
                       IException::recoverable );
  }
                       /* Save pointer to the start of the dlg template */
  pvStart = (void *)pdlgt;

                       /* Save the number of controls found within the  */
                       /* dialog template                               */
  cItems = pdlgt->adlgti[0].cChildren + 1;

                       /* Read in and create an Open Class Library C++  */
                       /* object for each of the controls within the    */
                       /* dialog template                               */
  for ( i = 1; i < cItems; i++ )
  {
                       /* Obtain the id of the control                  */
    unsigned long ulId = (unsigned long)(pdlgt->adlgti[i].id & 0xffff);

                       /* Skip the control if its id is -1              */
    if ( ulId != 0xffff )
    {
                       /* Check to see if a custom control is specified */
                       /* or if a standard PM control class is being    */
                       /* used                                          */
      if ( pdlgt->adlgti[i].cchClassName )
      {
                       /* Since a length for the class name present,    */
                       /* a custom control class name is being used for */
                       /* the control.  Point to the memory location    */
                       /* where the class name is found within the      */
                       /* dialog template information.                  */
        customControl( ulId,
                       ((char *)pvStart + pdlgt->adlgti[i].offClassName) );
      }
      else
      {
                       /* No class name length given indicating that a  */
                       /* standard PM class is being used.  The class   */
                       /* name is stored as an index value.  For        */
                       /* example, the class for static's is defined as */
                       /*                                               */
                       /* #define WC_STATIC ((PSZ)0xffff0005L)          */
                       /*                                               */
                       /* The values within the dialog template for     */
                       /* the static class would be                     */
                       /*                                               */
                       /* adlgti[i].cchClassName = 0                    */
                       /* adlgti[i].offClassName = 5                    */
                       /*                                               */
                       /* Therefore, the value of offClassName field    */
                       /* must be used as an index that is used to      */
                       /* actually select the class name.               */

        switch ( pdlgt->adlgti[i].offClassName )
        {
          case WINCLASS_BUTTON :
            {
              unsigned long ulStyle = pdlgt->adlgti[i].flStyle &
                                      BS_PRIMARYSTYLES;

              switch ( ulStyle )
              {
                case BS_PUSHBUTTON:
                  {
                    if ( pdlgt->adlgti[i].flStyle & (BS_BITMAP | BS_ICON) )
                    {
                      IGraphicPushButton*
                        pGraphicPushButton = new IGraphicPushButton( ulId,
                                                                     this );
                      pGraphicPushButton->setAutoDeleteObject( true );
                      graphicPushButton( pGraphicPushButton );
                    }
                    else
                    {
                      IPushButton*
                        pPushButton = new IPushButton( ulId, this );
                      pPushButton->setAutoDeleteObject( true );
                      this->pushButton( pPushButton );
                    }
                  }
                  break;

                case BS_CHECKBOX:
                case BS_AUTOCHECKBOX:
                  {
                    ICheckBox*
                      pCheckBox = new ICheckBox( ulId, this );
                    pCheckBox->setAutoDeleteObject( true );
                    checkBox( pCheckBox );
                  }
                  break;

                case BS_RADIOBUTTON:
                case BS_AUTORADIOBUTTON:
                  {
                    IRadioButton*
                      pRadioButton = new IRadioButton( ulId, this );
                    pRadioButton->setAutoDeleteObject( true );
                    radioButton( pRadioButton );
                  }
                  break;

                case BS_3STATE:
                case BS_AUTO3STATE:
                  {
                    I3StateCheckBox*
                      p3StateCheckBox = new I3StateCheckBox( ulId, this );
                    p3StateCheckBox->setAutoDeleteObject( true );
                    threeStateCheckBox( p3StateCheckBox );
                  }
                  break;

                case BS_USERBUTTON:
                  {
                    customButton( ulId );
                  }
                  break;
              } //end switch

            } //WINCLASS_BUTTON
            break;

          case WINCLASS_SCROLLBAR :
            {
              IScrollBar*
                pScrollBar = new IScrollBar( ulId, this );
              pScrollBar->setAutoDeleteObject( true );
              scrollBar( pScrollBar );
            }
            break;

          case WINCLASS_LISTBOX :
            {
              IListBox*
                pListBox = new IListBox( ulId, this );
              pListBox->setAutoDeleteObject( true );
              listBox( pListBox );
            }
            break;

          case WINCLASS_ENTRYFIELD :
            {
              IEntryField*
                pEntryField = new IEntryField( ulId, this );
              pEntryField->setAutoDeleteObject( true );
              entryField( pEntryField );
            }
            break;

          case WINCLASS_STATIC :
            {
              unsigned long ulStyle = pdlgt->adlgti[i].flStyle &
                                (SS_TEXT | SS_GROUPBOX | SS_ICON | SS_BITMAP);

              switch ( ulStyle )
              {
                case SS_TEXT:
                  {
                    IStaticText*
                      pStaticText = new IStaticText( ulId, this );
                    pStaticText->setAutoDeleteObject( true );
                    staticText( pStaticText );
                  }
                  break;

                case SS_GROUPBOX:
                  {
                    IGroupBox*
                      pGroupBox = new IGroupBox( ulId, this );
                    pGroupBox->setAutoDeleteObject( true );
                    groupBox( pGroupBox );
                  }
                  break;

                case SS_ICON:
                  {
                    IIconControl*
                      pIcon = new IIconControl( ulId, this );
                    pIcon->setAutoDeleteObject( true );
                    iconControl( pIcon );
                  }
                  break;

                case SS_BITMAP:
                  {
                    IBitmapControl*
                      pBitmap = new IBitmapControl( ulId, this );
                    pBitmap->setAutoDeleteObject( true );
                    bitmapControl( pBitmap );
                  }
                  break;
              } //end switch

            } //WINCLASS_STATIC
            break;

          case WINCLASS_COMBOBOX :
            {
              IComboBox*
                pComboBox = new IComboBox( ulId, this );
              pComboBox->setAutoDeleteObject( true );
              comboBox( pComboBox );
            }
            break;

          case WINCLASS_MLE :
            {
              IMultiLineEdit*
                pMLE = new IMultiLineEdit( ulId, this );
              pMLE->setAutoDeleteObject( true );
              mle( pMLE );
            }
            break;

          case WINCLASS_SPINBUTTON :
            {
              if ( pdlgt->adlgti[i].flStyle & SPBS_NUMERICONLY )
              {
                INumericSpinButton*
                  pNumericSpinButton = new INumericSpinButton( ulId, this );
                pNumericSpinButton->setAutoDeleteObject( true );
                numericSpinButton( pNumericSpinButton );
              }
              else
              {
                ITextSpinButton*
                  pTextSpinButton = new ITextSpinButton( ulId, this );
                pTextSpinButton->setAutoDeleteObject( true );
                textSpinButton( pTextSpinButton );
              }
            }
            break;

          case WINCLASS_CONTAINER :
            {
              IContainerControl*
                pContainer = new IContainerControl( ulId, this );
              pContainer->setAutoDeleteObject( true );
              container( pContainer );
            }
            break;

          case WINCLASS_SLIDER :
            {
              if ( pdlgt->adlgti[i].flStyle & SLS_READONLY )
              {
                IProgressIndicator*
                  pProgressIndicator = new IProgressIndicator( ulId, this );
                pProgressIndicator->setAutoDeleteObject( true );
                progressIndicator( pProgressIndicator );
              }
              else
              {
                ISlider*
                  pSlider = new ISlider( ulId, this );
                pSlider->setAutoDeleteObject( true );
                slider( pSlider );
              }
            }
            break;

          case WINCLASS_VALUESET :
            //No valueset class - see OS/2 C++ Class Library Power GUI
            //Programming with C Set++ for an implementation of a
            //valueset class.
            break;

          case WINCLASS_NOTEBOOK :
            {
              INotebook*
                pNotebook = new INotebook( ulId, this );
              pNotebook->setAutoDeleteObject( true );
              notebook( pNotebook );
            }
            break;

          case WINCLASS_CIRCULARSLIDER :
            {
              ICircularSlider*
                pCircularSlider = new ICircularSlider( ulId, this );
              pCircularSlider->setAutoDeleteObject( true );
              circularSlider( pCircularSlider );
            }
            break;
        } //end switch
      } //end if
    } //end if - id != -1

  } //end for
                       /* Release the memory allocated for the dlg      */
                       /* template before returning                     */
  DosFreeResource( pvStart );
                       /* Reset mouse pointer                           */
  setMousePointer( oldPointer );
  return( *this );
} //Dialog::createControlsFromTemplate


/*------------------------------------------------------------------------------
| Dialog::customControl                                                        |
------------------------------------------------------------------------------*/
Dialog& Dialog :: customControl( unsigned long ulId, const IString& className )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::graphicPushButton                                                    |
------------------------------------------------------------------------------*/
Dialog& Dialog :: graphicPushButton( IGraphicPushButton* pGraphicPushButton )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::graphicPushButtonWithId                                              |
------------------------------------------------------------------------------*/
IGraphicPushButton* Dialog :: graphicPushButtonWithId( unsigned long ulId )
{
  IGraphicPushButton*
    pGraphicPushButton =
            (IGraphicPushButton *)IWindow::windowWithOwner( ulId, this );

  if ( !pGraphicPushButton )
  {
    pGraphicPushButton = new IGraphicPushButton( ulId, this );
    pGraphicPushButton->setAutoDeleteObject( true );
  }

  return( pGraphicPushButton );
}


/*------------------------------------------------------------------------------
| Dialog::pushButton                                                           |
------------------------------------------------------------------------------*/
Dialog& Dialog :: pushButton( IPushButton* pPushButton )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::pushButtonWithId                                                     |
------------------------------------------------------------------------------*/
IPushButton* Dialog :: pushButtonWithId( unsigned long ulId )
{
  IPushButton*
    pPushButton = (IPushButton *)IWindow::windowWithOwner( ulId, this );

  if ( !pPushButton )
  {
    pPushButton = new IPushButton( ulId, this );
    pPushButton->setAutoDeleteObject( true );
  }

  return( pPushButton );
}


/*------------------------------------------------------------------------------
| Dialog::checkBox                                                             |
------------------------------------------------------------------------------*/
Dialog& Dialog :: checkBox( ICheckBox* pCheckBox )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::checkBoxWithId                                                       |
------------------------------------------------------------------------------*/
ICheckBox* Dialog :: checkBoxWithId( unsigned long ulId )
{
  ICheckBox*
    pCheckBox = (ICheckBox *)IWindow::windowWithOwner( ulId, this );

  if ( !pCheckBox )
  {
    pCheckBox = new ICheckBox( ulId, this );
    pCheckBox->setAutoDeleteObject( true );
  }

  return( pCheckBox );
}


/*------------------------------------------------------------------------------
| Dialog::threeStateCheckBox                                                   |
------------------------------------------------------------------------------*/
Dialog& Dialog :: threeStateCheckBox( I3StateCheckBox* p3StateCheckBox )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::threeStateCheckBoxWithId                                             |
------------------------------------------------------------------------------*/
I3StateCheckBox* Dialog :: threeStateCheckBoxWithId( unsigned long ulId )
{
  I3StateCheckBox*
    p3StateCheckBox = (I3StateCheckBox *)IWindow::windowWithOwner( ulId, this );

  if ( !p3StateCheckBox )
  {
    p3StateCheckBox = new I3StateCheckBox( ulId, this );
    p3StateCheckBox->setAutoDeleteObject( true );
  }

  return( p3StateCheckBox );
}


/*------------------------------------------------------------------------------
| Dialog::radioButton                                                          |
------------------------------------------------------------------------------*/
Dialog& Dialog :: radioButton( IRadioButton* pRadioButton )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::radioButtonWithId                                                    |
------------------------------------------------------------------------------*/
IRadioButton* Dialog :: radioButtonWithId( unsigned long ulId )
{
  IRadioButton*
    pRadioButton = (IRadioButton *)IWindow::windowWithOwner( ulId, this );

  if ( !pRadioButton )
  {
    pRadioButton = new IRadioButton( ulId, this );
    pRadioButton->setAutoDeleteObject( true );
  }

  return( pRadioButton );
}


/*------------------------------------------------------------------------------
| Dialog::customButtom                                                         |
------------------------------------------------------------------------------*/
Dialog& Dialog :: customButton( unsigned long ulId )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::scrollBar                                                            |
------------------------------------------------------------------------------*/
Dialog& Dialog :: scrollBar( IScrollBar* pScrollBar )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::scrollBarWithId                                                      |
------------------------------------------------------------------------------*/
IScrollBar* Dialog :: scrollBarWithId( unsigned long ulId )
{
  IScrollBar*
    pScrollBar = (IScrollBar *)IWindow::windowWithOwner( ulId, this );

  if ( !pScrollBar )
  {
    pScrollBar = new IScrollBar( ulId, this );
    pScrollBar->setAutoDeleteObject( true );
  }

  return( pScrollBar );
}


/*------------------------------------------------------------------------------
| Dialog::listBox                                                              |
------------------------------------------------------------------------------*/
Dialog& Dialog :: listBox( IListBox* pListBox )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::listBoxWithId                                                        |
------------------------------------------------------------------------------*/
IListBox* Dialog :: listBoxWithId( unsigned long ulId )
{
  IListBox*
    pListBox = (IListBox *)IWindow::windowWithOwner( ulId, this );

  if ( !pListBox )
  {
    pListBox = new IListBox( ulId, this );
    pListBox->setAutoDeleteObject( true );
  }

  return( pListBox );
}


/*------------------------------------------------------------------------------
| Dialog::entryField                                                           |
------------------------------------------------------------------------------*/
Dialog& Dialog :: entryField( IEntryField* pEntryField )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::entryFieldWithId                                                     |
------------------------------------------------------------------------------*/
IEntryField* Dialog :: entryFieldWithId( unsigned long ulId )
{
  IEntryField*
    pEntryField = (IEntryField *)IWindow::windowWithOwner( ulId, this );

  if ( !pEntryField )
  {
    pEntryField = new IEntryField( ulId, this );
    pEntryField->setAutoDeleteObject( true );
  }

  return( pEntryField );
}


/*------------------------------------------------------------------------------
| Dialog::staticText                                                           |
------------------------------------------------------------------------------*/
Dialog& Dialog :: staticText( IStaticText* pStaticText )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::staticTextWithId                                                     |
------------------------------------------------------------------------------*/
IStaticText* Dialog :: staticTextWithId( unsigned long ulId )
{
  IStaticText*
    pStaticText = (IStaticText *)IWindow::windowWithOwner( ulId, this );

  if ( !pStaticText )
  {
    pStaticText = new IStaticText( ulId, this );
    pStaticText->setAutoDeleteObject( true );
  }

  return( pStaticText );
}


/*------------------------------------------------------------------------------
| Dialog::groupBox                                                             |
------------------------------------------------------------------------------*/
Dialog& Dialog :: groupBox( IGroupBox* pGroupBox )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::groupBoxWithId                                                       |
------------------------------------------------------------------------------*/
IGroupBox* Dialog :: groupBoxWithId( unsigned long ulId )
{
  IGroupBox*
    pGroupBox = (IGroupBox *)IWindow::windowWithOwner( ulId, this );

  if ( !pGroupBox )
  {
    pGroupBox = new IGroupBox( ulId, this );
    pGroupBox->setAutoDeleteObject( true );
  }

  return( pGroupBox );
}


/*------------------------------------------------------------------------------
| Dialog::iconControl                                                          |
------------------------------------------------------------------------------*/
Dialog& Dialog :: iconControl( IIconControl* pIcon )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::iconControlWithId                                                    |
------------------------------------------------------------------------------*/
IIconControl* Dialog :: iconControlWithId( unsigned long ulId )
{
  IIconControl*
    pIconControl = (IIconControl *)IWindow::windowWithOwner( ulId, this );

  if ( !pIconControl )
  {
    pIconControl = new IIconControl( ulId, this );
    pIconControl->setAutoDeleteObject( true );
  }

  return( pIconControl );
}


/*------------------------------------------------------------------------------
| Dialog::bitmapControl                                                        |
------------------------------------------------------------------------------*/
Dialog& Dialog :: bitmapControl( IBitmapControl* pBitmap )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::bitmapControlWithId                                                  |
------------------------------------------------------------------------------*/
IBitmapControl* Dialog :: bitmapControlWithId( unsigned long ulId )
{
  IBitmapControl*
    pBitmapControl = (IBitmapControl *)IWindow::windowWithOwner( ulId, this );

  if ( !pBitmapControl )
  {
    pBitmapControl = new IBitmapControl( ulId, this );
    pBitmapControl->setAutoDeleteObject( true );
  }

  return( pBitmapControl );
}


/*------------------------------------------------------------------------------
| Dialog::comboBox                                                             |
------------------------------------------------------------------------------*/
Dialog& Dialog :: comboBox( IComboBox* pComboBox )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::comboBoxWithId                                                       |
------------------------------------------------------------------------------*/
IComboBox* Dialog :: comboBoxWithId( unsigned long ulId )
{
  IComboBox*
    pComboBox = (IComboBox *)IWindow::windowWithOwner( ulId, this );

  if ( !pComboBox )
  {
    pComboBox = new IComboBox( ulId, this );
    pComboBox->setAutoDeleteObject( true );
  }

  return( pComboBox );
}


/*------------------------------------------------------------------------------
| Dialog::mle                                                                  |
------------------------------------------------------------------------------*/
Dialog& Dialog :: mle( IMultiLineEdit* pMLE )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::mleWithId                                                            |
------------------------------------------------------------------------------*/
IMultiLineEdit* Dialog :: mleWithId( unsigned long ulId )
{
  IMultiLineEdit*
    pMLE = (IMultiLineEdit *)IWindow::windowWithOwner( ulId, this );

  if ( !pMLE )
  {
    pMLE = new IMultiLineEdit( ulId, this );
    pMLE->setAutoDeleteObject( true );
  }

  return( pMLE );
}


/*------------------------------------------------------------------------------
| Dialog::numericSpinButton                                                    |
------------------------------------------------------------------------------*/
Dialog& Dialog :: numericSpinButton( INumericSpinButton* pNumericSpinButton )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::numericSpinButtonWithId                                              |
------------------------------------------------------------------------------*/
INumericSpinButton* Dialog :: numericSpinButtonWithId( unsigned long ulId )
{
  INumericSpinButton*
    pNumericSpinButton =
            (INumericSpinButton *)IWindow::windowWithOwner( ulId, this );

  if ( !pNumericSpinButton )
  {
    pNumericSpinButton = new INumericSpinButton( ulId, this );
    pNumericSpinButton->setAutoDeleteObject( true );
  }

  return( pNumericSpinButton );
}


/*------------------------------------------------------------------------------
| Dialog::textSpinButton                                                       |
------------------------------------------------------------------------------*/
Dialog& Dialog :: textSpinButton( ITextSpinButton* pTextSpinButton )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::textSpinButtonWithId                                                 |
------------------------------------------------------------------------------*/
ITextSpinButton* Dialog :: textSpinButtonWithId( unsigned long ulId )
{
  ITextSpinButton*
    pTextSpinButton = (ITextSpinButton *)IWindow::windowWithOwner( ulId, this );

  if ( !pTextSpinButton )
  {
    pTextSpinButton = new ITextSpinButton( ulId, this );
    pTextSpinButton->setAutoDeleteObject( true );
  }

  return( pTextSpinButton );
}


/*------------------------------------------------------------------------------
| Dialog::container                                                            |
------------------------------------------------------------------------------*/
Dialog& Dialog :: container( IContainerControl* pContainer )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::containerWithId                                                      |
------------------------------------------------------------------------------*/
IContainerControl* Dialog :: containerWithId( unsigned long ulId )
{
  IContainerControl*
    pContainer = (IContainerControl *)IWindow::windowWithOwner( ulId, this );

  if ( !pContainer )
  {
    pContainer = new IContainerControl( ulId, this );
    pContainer->setAutoDeleteObject( true );
  }

  return( pContainer );
}


/*------------------------------------------------------------------------------
| Dialog::progressIndicator                                                    |
------------------------------------------------------------------------------*/
Dialog& Dialog :: progressIndicator( IProgressIndicator* pProgressIndicator )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::progressIndicatorWithId                                              |
------------------------------------------------------------------------------*/
IProgressIndicator* Dialog :: progressIndicatorWithId( unsigned long ulId )
{
  IProgressIndicator*
    pProgressIndicator =
             (IProgressIndicator *)IWindow::windowWithOwner( ulId, this );

  if ( !pProgressIndicator )
  {
    pProgressIndicator = new IProgressIndicator( ulId, this );
    pProgressIndicator->setAutoDeleteObject( true );
  }

  return( pProgressIndicator );
}


/*------------------------------------------------------------------------------
| Dialog::slider                                                               |
------------------------------------------------------------------------------*/
Dialog& Dialog :: slider( ISlider* pSlider )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::sliderWithId                                                         |
------------------------------------------------------------------------------*/
ISlider* Dialog :: sliderWithId( unsigned long ulId )
{
  ISlider*
    pSlider = (ISlider *)IWindow::windowWithOwner( ulId, this );

  if ( !pSlider )
  {
    pSlider = new ISlider( ulId, this );
    pSlider->setAutoDeleteObject( true );
  }

  return( pSlider );
}


/*------------------------------------------------------------------------------
| Dialog::notebook                                                             |
------------------------------------------------------------------------------*/
Dialog& Dialog :: notebook( INotebook* pNotebook )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::notebookWithId                                                       |
------------------------------------------------------------------------------*/
INotebook* Dialog :: notebookWithId( unsigned long ulId )
{
  INotebook*
    pNotebook = (INotebook *)IWindow::windowWithOwner( ulId, this );

  if ( !pNotebook )
  {
    pNotebook = new INotebook( ulId, this );
    pNotebook->setAutoDeleteObject( true );
  }

  return( pNotebook );
}


/*------------------------------------------------------------------------------
| Dialog::circularSlider                                                       |
------------------------------------------------------------------------------*/
Dialog& Dialog :: circularSlider( ICircularSlider* pCircularSlider )
{
  return( *this );
}


/*------------------------------------------------------------------------------
| Dialog::circularSliderWithId                                                 |
------------------------------------------------------------------------------*/
ICircularSlider* Dialog :: circularSliderWithId( unsigned long ulId )
{
  ICircularSlider*
    pCircularSlider = (ICircularSlider *)IWindow::windowWithOwner( ulId, this );

  if ( !pCircularSlider )
  {
    pCircularSlider = new ICircularSlider( ulId, this );
    pCircularSlider->setAutoDeleteObject( true );
  }

  return( pCircularSlider );
}

