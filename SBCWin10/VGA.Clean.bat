@ECHO OFF

CLS

REM Delete Garbage Files 
del *.aps 
del *.ilk 
del *.map 
del *.ncb 
del *.opt 
del *.plg 
del *.pbi 
del *.pbo 
del *.pbt 
del *.pdb 
del *.tmp 
del *._xe 

REM Delete Garbage Directories 
rmdir /Q /S .vs 
rmdir /Q /S DEBUG 
rmdir /Q /S Release 