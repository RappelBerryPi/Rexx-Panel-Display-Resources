
/******************************** REXX ********************************/
/* PROGRAMMER:    RappelBerryPi                                       */
/* CREATION DATE: 11/16/2021                                          */
/* UPDATED:       11/16/2021                                          */
/**********************************************************************/
PARSE ARG FILE PDS position LIST .


ListFirstChar = substr(List,1,1)
FALSE = 0
TRUE = 1
File = strip(file,, "'")
File = strip(file,, '"')
File = translate(file) /* upper case */

pds = strip(pds,, "'")
pds = strip(pds,, '"')
pds = translate(pds) /* upper case */

if (file = "HELP") Then do
    CALL ShowHelp
    exit 1
end 
if (file = "") Then do
    SAY "Please enter a FILE"
    CALL ShowHelp
    exit 1
end
if (pds = "") Then do
    SAY "Please enter a PDS"
    CALL ShowHelp
    exit 1
end
if (position = '') then do
   position = 1
end 

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

if \(datatype(position, 'N')) then do
    position = translate(position) /* upper case */
    select 
        when position = "FIRST" Then do
            position = 1
        end
        when position = "LAST" Then do
            position = -1
        end
        otherwise do
            SAY "Invalid position argument"
            CALL ShowHelp
            exit 1
        end
    end
end

ADDRESS TSO

capture = outtrap('datasets.')
"LISTA ST"
capture = outtrap('off')


concats.0 = 0

Found = FALSE
i = 1
j = 1

if (j = position) then do
    concats.j = "'"pds"'"
    j = j + 1
end

do i = 1 to datasets.0 while \Found
    if (length(datasets.i) < 9) then do
        iterate
    end
    if (substr(datasets.i,3,7) = FILE) then do
        Found = TRUE
        i = i - 1
        concats.j = "'"datasets.i"'"
        j = j + 1
        if (j = position) then do
            concats.j = "'"pds"'"
            j = j + 1
        end
    end
end
if (found) then do
    do while (i + 2 <= datasets.0)
        i = i + 2
        if (substr(datasets.i,1,3) = '   ') then do
            k = i - 1
            concats.j = "'"datasets.k"'"
            j = j + 1
            if (j = position) then do
                concats.j = "'"pds"'"
                j = j + 1
            end
            else do
                nop
            end
        end
        else do
            i = datasets.0
        end
    end
end

if position = -1 | position > j then do
    concats.j = "'"pds"'"
    j = j + 1
end
concats.0 = j - 1

dslist = concats.1

do i = 2 to concats.0
    dslist = dslist || "," || concats.i
end

"ALLOC FI("FILE") DA("dslist") SHR REUSE"
ZERRLM = FILE "updated to include" pds"."
ZERRSM = FILE "updated." 
ADDRESS ISPEXEC "SETMSG MSG(ISRZ003)"
exit 0

ShowHelp:
    SAY ""
    SAY ""
    SAY ""
    SAY ""
    SAY "USAGE: CONCAT 'FILE' 'PDS' 'POSITION' 'LIST'"
    SAY "  - "
    SAY "  - FILE - The name of the FILE that needs to have the PDS added to"
    SAY "  -        it. Examples include ISPPLIB, SYSPROC, etc."
    SAY "  - PDS  - The Fully qualified name of the PDS to be added to the"
    SAY "  -        FILE. Examples include '&USERID.ISPPLIB', '&USERID.REXX',"
    SAY "  -        '&USERID.ISPSLIB', etc."
    SAY "  - POSITION - The position to insert PDS in the FILE CONCAT."
    SAY "  -            Examples include 'FIRST', 'LAST', '2', -1, etc."
    SAY "  -            The Default Position is 'FIRST'."
    SAY "  - LIST - The trace option. Valid values are TRACE and LIST."
    SAY "  -        TRACE will allow you to do an interactive trace."
    SAY "  -        LIST simply lists the commands, inputs, and results."
    SAY ""
    SAY ""
    SAY ""