#include <icmdhdr.hpp>
#include <iselhdr.hpp>
#include <iobservr.hpp>

class SampleDialog;
class MyFrame;

/*******************************************************************************
* SampleCommandHandler Class                                                   *
*******************************************************************************/
class SampleCommandHandler : public ICommandHandler {
typedef ICommandHandler
  Inherited;
public:
/*------------------------------- Constructors -------------------------------*/
  SampleCommandHandler  ( SampleDialog& dialogue );

virtual
  ~SampleCommandHandler ( );

/*----------------------------- Event Processing -----------------------------*/
Boolean
  command ( ICommandEvent& event );

private:
/*--------------------------------- Private ----------------------------------*/
SampleDialog
 &sampleDialog;
};


/*******************************************************************************
* SampleSelectHandler Class                                                    *
*******************************************************************************/
class SampleSelectHandler : public ISelectHandler {
typedef ISelectHandler
  Inherited;
public:
/*------------------------------- Constructors -------------------------------*/
  SampleSelectHandler  ( SampleDialog& dialogue );

virtual
  ~SampleSelectHandler ( );

/*----------------------------- Event Processing -----------------------------*/
Boolean
  selected ( IControlEvent& event );

private:
/*--------------------------------- Private ----------------------------------*/
SampleDialog
 &sampleDialog;
};


/*******************************************************************************
* SampleObserver Class                                                         *
*******************************************************************************/
class SampleObserver : public IObserver {
typedef IObserver
  Inherited;
public:
/*------------------------------- Constructors -------------------------------*/
  SampleObserver  ( SampleDialog& dialogue );

virtual
  ~SampleObserver ( );

/*----------------------------- Event Dispatching ----------------------------*/
virtual SampleObserver
 &dispatchNotificationEvent  ( const INotificationEvent& event );

private:
/*--------------------------------- Private ----------------------------------*/
SampleDialog
 &sampleDialog;
};


/*******************************************************************************
* MyFrameCommandHandler Class                                                  *
*******************************************************************************/
class MyFrameCommandHandler : public ICommandHandler {
typedef ICommandHandler
  Inherited;
public:
/*------------------------------- Constructors -------------------------------*/
  MyFrameCommandHandler  ( MyFrame& aFrame );

virtual
  ~MyFrameCommandHandler ( );

/*----------------------------- Event Processing -----------------------------*/
Boolean
  command ( ICommandEvent& event );

private:
/*--------------------------------- Private ----------------------------------*/
MyFrame
 &myFrame;
};

