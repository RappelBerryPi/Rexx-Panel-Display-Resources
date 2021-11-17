# Rexx-Panel-Display-Resources
This is a sample set of rexx programs and panel definitions that can be used to display panels. This is a very light
introduction into using ISPF services on a ZOS mainframe. All code was developed on the Open Mainframe initiative. Open
to the public. More information about the Open Mainframe project can be found at https://www.openmainframeproject.org/

## Setup
Make sure that you change all the references to my ID on the open mainframe project's LPAR should be changed to your
userID. Also, Rather than using my actual name I'm going to change it to my Github name.

## Other setup
The @Logon dataset is useful but it has to be run outside of the ISPF context as the libraries that it tries to
concatenate are used by ISPF. as such, PF3 out to a TSO terminal and then run the @LOGON command. I gave an example in a
PNG.

Finally, make sure that all of the PDS are allocated before attempting to concatenate them, There's no checks inside of
the concatenate program as of today that checks for the existence of any / all of the PDS in the concatenation.


## Note about calling concat
The parameters don't actually need quotes, I chose to add them to let you know how to run it if you feel the need to
have quotes.