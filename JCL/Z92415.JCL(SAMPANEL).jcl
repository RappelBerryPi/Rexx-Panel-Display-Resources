//SAMPANEL JOB 1,NOTIFY=&SYSUID
//***************************************************/
//COBRUN  EXEC IGYWCL
//COBOL.SYSIN  DD DSN=&SYSUID..CBL(SAMPANEL),DISP=SHR
//LKED.SYSLMOD DD DSN=&SYSUID..LOAD(SAMPANEL),DISP=SHR
//***************************************************/
