
DISCLAIMER
----------

Nothing in this package should be taken to imply any plans are in place
to offer the part described in this document.  The interfaces and functions
supplied by this sample part interface file may change before this type of
support appears in the product, if it ever appears in VisualAge C++.

Support will be provided only as time allows.

We are however interested in feedback and comments.  Please provide
comments in Section 4 of OS2DF1 forum on CompuServe.

FILES
-----

  VB3STA.ZIP   - Contains all these files except itself. Use
                 PKUNZIP2 VB3STA.ZIP to unpack into current directory.
  README.TXT   - This file.
  I3STATBX.VBE - A part information file for the IBM Open Class I3StateCheckBox
                 class.  This is a visual part that re-uses the icon for the
                 regular check box part.


USING THE SAMPLE
----------------

1) Bring up the Visual Builder and import I3STATBX.VBE using the
   "File->Import part information" menu option.  I3StateCheckBox will appear
   in the visual parts list and Visual Builder will create a VBB file for
   this new part.  You can either add this part to a category on the
   palette, or you can add it to the free-form surface using the
   "Options->Add part" menu option on the Composition Editor.

2) This part is derived from ISettingButton, so in addition to the common
   attributes/actions/events it shares with radio buttons and regular check
   boxes, it adds

    - a "halftone" attribute that indicates the halftone state of the button
    - a "selectHalftone" action that sets the halftone state of the button



IBM VisualAge C++ Visual Builder development

