/*******************************************************************************
* FILE NAME: strgen.hpp                                                        *
*                                                                              *
* DESCRIPTION:                                                                 *
*   Declaration of the class:                                                  *
*     strgen- Sample of using IStringGenerator class                           *
* ---------------------------------------------------------------------------- *
* Warning: This file was generated by the VisualAge C++ Visual Builder.        *
* Modifications to this source file will be lost when the part is regenerated. *
*******************************************************************************/
#ifndef _STRGEN_
#define _STRGEN_  

class strgen;

#ifndef _IFRAME_
#include <iframe.hpp>
#endif

class ICanvas;
#ifndef _CUSTOMER_
#include "Customer.hpp"
#endif

#ifndef _IVSEQ_H_
#include <ivseq.h>
#endif

template <class Element,class Collection> class ICollectionViewListBox;
class IStaticText;
class Customer;
template <class Element> class IVSequence;
#ifndef _IRECT_
#include <irect.hpp>
#endif

#ifndef _ISTRING_
#include <istring.hpp>
#endif

#ifndef _ISTRGEN_
#include "istrgen.hpp"
#endif

class strgenConn0;
class strgenConn1;
class strgenConn2;
#include "strgen.h"


/*----------------------------------------------------------------------------*/
/* Align classes on four byte boundary.                                       */
/*----------------------------------------------------------------------------*/
#pragma pack(4)

//*****************************************************************************
// Class definition for strgen
//*****************************************************************************
class strgen : public IFrameWindow {
public:
   //---------------------------------------------------------------------------
   // Constructors / destructors
   //---------------------------------------------------------------------------
   strgen(
      unsigned long id = WND_strgen,
      IWindow* parent = IWindow::desktopWindow(),
      IWindow* owner = 0,
      const IRectangle& rect = defaultFramingSpec(),
      const IFrameWindow::Style& style = IFrameWindow::defaultStyle ( ),
      const char* title = defaultTitle());

   virtual  ~strgen();

   //---------------------------------------------------------------------------
   // public member functions
   //---------------------------------------------------------------------------
   static const IRectangle defaultFramingSpec();
   static IString defaultTitle();
   virtual strgen & initializePart();
   strgen * getFrameWindow() { return this; };

   //---------------------------------------------------------------------------
   // public member data
   //---------------------------------------------------------------------------
   static const INotificationId readyId;

protected:
   //---------------------------------------------------------------------------
   // protected member functions
   //---------------------------------------------------------------------------
   Boolean makeConnections();

private:
   //---------------------------------------------------------------------------
   // private member data
   //---------------------------------------------------------------------------
   ICanvas * iCanvas;
   ICollectionViewListBox< Customer*, IVSequence< Customer* > > * iCollectionViewListBox1;
   IStaticText * iStaticText1;
   Customer * iCustomer1;
   Customer * iCustomer2;
   IVSequence< Customer* > * iVSequence1;
   strgenConn0 * conn0;
   strgenConn1 * conn1;
   strgenConn2 * conn2;
   static unsigned long partWindowId;


#include "strgen.hpv"
};   //strgen


/*----------------------------------------------------------------------------*/
/* Resume compiler default packing.                                           */
/*----------------------------------------------------------------------------*/
#pragma pack()

#endif
