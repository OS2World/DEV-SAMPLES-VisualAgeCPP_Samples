.SUFFIXES:

.SUFFIXES: .c .cpp .cxx .rc

driver.EXE:  \
  driver.OBJ \
  drivhdr.OBJ \
  dialog.OBJ \
  driver.res \
  driver.MAK
   ICC.EXE @<<
 /B" /pmtype:pm"
 /Fe"driver.EXE"
driver.OBJ
drivhdr.OBJ
dialog.OBJ
<<
   rc Driver.Res driver.Exe

{.}.rc.res:
   RC -r   .\$*.RC

{.}.c.obj:
   ICC.EXE /Gm /Gd /C   .\$*.c

{.}.cpp.obj:
   ICC.EXE /Gm /Gd /C   .\$*.cpp

{.}.cxx.obj:
   ICC.EXE /Gm /Gd /C   .\$*.cxx

!include driver.DEP
