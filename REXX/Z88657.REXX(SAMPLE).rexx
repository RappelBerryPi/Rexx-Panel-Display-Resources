/******************************** REXX ********************************/
/* PROGRAMMER:    RappelBerryPi                                       */
/* CREATION DATE: 11/16/2021                                          */
/* UPDATED:       11/16/2021                                          */
/**********************************************************************/
PARSE ARG LIST .


ListFirstChar = substr(List,1,1)
FALSE = 0
TRUE = 1

select 
    when ListFirstChar = "L" Then do
        TRACE IR
    end
    when ListFirstChar = "T" Then do
        trace ?R
    end
    otherwise do
        trace o
    end
end

do FOREVER
    ADDRESS ISPEXEC
    "DISPLAY PANEL(SAMPLE)" /* you can also set cursor and message variables*/
    if (RC = 8) then do /* RC 8 = PF3*/
        leave
    end
    say "You entered:" input /* input defined on the panel*/
end
exit 0