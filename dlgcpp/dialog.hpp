#include <iframe.hpp>
#include <imousevt.hpp>
#include <istring.hpp>

class IGraphicPushButton;
class IPushButton;
class ICheckBox;
class I3StateCheckBox;
class IRadioButton;
class IScrollBar;
class IListBox;
class IEntryField;
class IStaticText;
class IGroupBox;
class IIconControl;
class IBitmapControl;
class IComboBox;
class IMultiLineEdit;
class INumericSpinButton;
class ITextSpinButton;
class IContainerControl;
class IProgressIndicator;
class ISlider;
class INotebook;
class ICircularSlider;


/*******************************************************************************
* Dialog Class                                                                 *
*******************************************************************************/
class Dialog : public IFrameWindow {
typedef IFrameWindow
  Inherited;
public:
/*------------------------------- Constructors -------------------------------*/
virtual
  ~Dialog ( );

/*------------------------------- Control Access -----------------------------*/
virtual IGraphicPushButton
 *graphicPushButtonWithId  ( unsigned long identifier );

virtual IPushButton
 *pushButtonWithId         ( unsigned long identifier );

virtual ICheckBox
 *checkBoxWithId           ( unsigned long identifier );

virtual I3StateCheckBox
 *threeStateCheckBoxWithId ( unsigned long identifier );

virtual IRadioButton
 *radioButtonWithId        ( unsigned long identifier );

virtual IScrollBar
 *scrollBarWithId          ( unsigned long identifier );

virtual IListBox
 *listBoxWithId            ( unsigned long identifier );

virtual IEntryField
 *entryFieldWithId         ( unsigned long identifier );

virtual IStaticText
 *staticTextWithId         ( unsigned long identifier );

virtual IGroupBox
 *groupBoxWithId           ( unsigned long identifier );

virtual IIconControl
 *iconControlWithId        ( unsigned long identifier );

virtual IBitmapControl
 *bitmapControlWithId      ( unsigned long identifier );

virtual IComboBox
 *comboBoxWithId           ( unsigned long identifier );

virtual IMultiLineEdit
 *mleWithId                ( unsigned long identifier );

virtual INumericSpinButton
 *numericSpinButtonWithId  ( unsigned long identifier );

virtual ITextSpinButton
 *textSpinButtonWithId     ( unsigned long identifier );

virtual IContainerControl
 *containerWithId          ( unsigned long identifier );

virtual IProgressIndicator
 *progressIndicatorWithId  ( unsigned long identifier );

virtual ISlider
 *sliderWithId             ( unsigned long identifier );

virtual INotebook
 *notebookWithId           ( unsigned long identifier );

virtual ICircularSlider
 *circularSliderWithId     ( unsigned long identifier );

protected:
/*------------------------------- Constructors -------------------------------*/
  Dialog  ( unsigned long id,
            IWindow*      owner );

/*------------------------------ Implementation ------------------------------*/
Dialog
 &createControlsFromTemplate ( );

/*------------------------------ Control Creation ----------------------------*/
virtual Dialog
 &customControl      ( unsigned long       identifier,
                       const IString&      className ),
 &graphicPushButton  ( IGraphicPushButton* aGraphicPushButton ),
 &pushButton         ( IPushButton*        aPushButton ),
 &checkBox           ( ICheckBox*          aCheckBox ),
 &threeStateCheckBox ( I3StateCheckBox*    a3StateCheckBox ),
 &radioButton        ( IRadioButton*       aRadioButton ),
 &customButton       ( unsigned long       identifier ),
 &scrollBar          ( IScrollBar*         aScrollBar ),
 &listBox            ( IListBox*           aListBox ),
 &entryField         ( IEntryField*        anEntryField ),
 &staticText         ( IStaticText*        aStaticText ),
 &groupBox           ( IGroupBox*          aGroupBox ),
 &iconControl        ( IIconControl*       anIcon ),
 &bitmapControl      ( IBitmapControl*     aBitmap ),
 &comboBox           ( IComboBox*          aComboBox ),
 &mle                ( IMultiLineEdit*     aMLE ),
 &numericSpinButton  ( INumericSpinButton* aNumericSpinButton ),
 &textSpinButton     ( ITextSpinButton*    aTextSpinButton ),
 &container          ( IContainerControl*  aContainer ),
 &progressIndicator  ( IProgressIndicator* aProgressIndicator ),
 &slider             ( ISlider*            aSlider ),
 &notebook           ( INotebook*          aNotebook ),
 &circularSlider     ( ICircularSlider*    aCircularSlider );

private:
/*--------------------------------- Private ----------------------------------*/
unsigned long
  ulId;

}; //Dialog

