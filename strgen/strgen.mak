#*******************************************************************************
# FILE NAME: strgen.mak                                                        *
#                                                                              *
# DESCRIPTION:                                                                 *
#   Make file for class:                                                       *
#     strgen- Sample of using IStringGenerator class                           *
# ---------------------------------------------------------------------------- *
# Warning: This file was generated by the VisualAge C++ Visual Builder.        *
# Modifications to this source file will be lost when the part is regenerated. *
#******************************************************************************/
PARTCPPFLAGS=-Ftstrgen -Gm+ -Tdp -Gd+ -I.
APPCPPFLAGS=-Ftstrgen -Gm+ -Tdp -Gd+ -I.

all:   strgen

strgen:   strgen.exe

strgen.exe:   strgen.o strgen.obj Customer.obj \
        strgen.res
          icc $(PARTCPPFLAGS) /B"strgen.o /pmtype:pm" \
             strgen.obj Customer.obj \
             /Festrgen.exe /Fmstrgen.map \
             os2386.lib
          rc strgen.res strgen.exe

strgen.obj:   strgen.cpp {$(INCLUDE)}strgen.hpp {$(INCLUDE)}strgen.h \
        {$(INCLUDE)}strgen.hpv strgen.cpv {$(INCLUDE)}Customer.hpp {$(INCLUDE)}Customer.h \
        {$(INCLUDE)}Customer.h
          ICC -c $(PARTCPPFLAGS)  strgen.cpp

strgen.o:   strgen.app strgen.hpp
          ICC -c $(APPCPPFLAGS) -Fostrgen.o strgen.app

Customer.obj:   Customer.cpp {$(INCLUDE)}Customer.hpp {$(INCLUDE)}Customer.h \
        {$(INCLUDE)}customer.hpv customer.cpv
          ICC -c $(PARTCPPFLAGS)  Customer.cpp

strgen.res:   strgen.rcx strgen.rci {$(INCLUDE)}strgen.h \
        Customer.rci {$(INCLUDE)}Customer.h
          ICC -c /Pc+ /Pe+ /I. strgen.rcx
          - erase strgen.rc 2> nul
          rename strgen.i strgen.rc > nul
          rc -r strgen.rc

