       IDENTIFICATION DIVISION.
       PROGRAM-ID. SAMPANEL.
       AUTHOR. RAPPELBERRYPI.
       ENVIRONMENT DIVISION.
       INPUT-OUTPUT SECTION.
       DATA DIVISION.
       WORKING-STORAGE SECTION.

       01  Command   PIC X(8)               VALUE "DISPLAY ".
       01  PANEL     PIC X(13)              VALUE "SAMPLE".
       01  ISPLINK   PIC X(8)               VALUE "ISPLINK".
       01  I-VDEFINE PIC X(8)               VALUE "VDEFINE ".
       01  VARS.
           05 PAREN   PIC X(7)              VALUE "(INPUT)".
           05 I-CHAR  PIC X(8)              VALUE "CHAR    ".
           05 I-LEN   PIC 9(6) COMP         VALUE 50.
       01  RC        PIC S9(8) USAGE BINARY VALUE 0.
       01  INPUTS.
           05 INP   PIC X(50)              VALUE SPACES.

       PROCEDURE DIVISION.

       0000-MAIN.
           CALL ISPLINK USING I-VDEFINE, PAREN, INP, I-CHAR, I-LEN.
           PERFORM 1000-DISPLAY-PANEL UNTIL RC = 8.
           GOBACK.

       1000-DISPLAY-PANEL.
           CALL ISPLINK USING COMMAND, PANEL.
           MOVE RETURN-CODE TO RC.
           IF RC = 0
               DISPLAY "You entered: " INP
           END-IF.
      *https://www.ibm.com/docs/en/db2-for-zos/11?topic=sait-dsn8sc3
