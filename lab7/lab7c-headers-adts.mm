.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.SIZE 12 14
.TITLE CMPS-012M Spring\~2014 Lab\~7 "Header files and ADTs"
.RCS "$Id: lab7c-headers-adts.mm,v 1.17 2014-05-06 20:32:50-07 - - $"
.PWD
.URL
.H 1 "Overview"
This lab will introduce you to header
.=V ( .h )
files,
also known as
.V= #include
files,
which are C's equivalent of interfaces,
and implementation files
.=V ( .c )
which are C's equivalent of implementation files.
C has no keyword
.V= private ,
but its equivalent is to put hidden information only in
implementation files.
.P
In this program you will use separate compilation to implement a
simple queue of lines in C.
.H 1 "Subdirectory cbox"
Sample code has been provided.
First, study the trivial
.V= cbox
application which shows how to do separate compilation using
header files and implementation files.
Inspect the following files\(::
.nr FILE_Pi \w'\f[CB]Makefile\f[R]\0\0'
.VL \n[FILE_Pi]u
.V=LI cbox.h
The interface to the
.V= cbox
ADT showing the constructor, destructor, accessors, and mutators.
In Java these would be the public functions.
.V=LI cbox.c
The implemention of the ADT, showing the private functions and fields.
Note that the 
.V= struct 
fields are thus hidden from the client.
.V=LI main.c
Shows how to create and access an ADT.
The application itself is trivial.
.V=LI Makefile
Builds each object
.=V ( .o )
file and then links them into an executable image.
Note how it creates dependencies by editing itself.
.LE
.H 1 "Subdirectory queue"
Provides a simple queueing application,
where each line of the input is read into a queue.
The queue is then printed and the program stops.
The idea of a
.E= stub
is introduced.
Incomplete code is just represented by a print statement which must
eventually be replaced by actual code.
The following command
will tell you where all of the stub calls are\(::
.V= "grep STUB *.[hc]"
.P
You must implement
.V= new_queue ,
.V= insert_queue ,
.V= remove_queue .
your implementation must be done via the several files,
whose object modules are linked together into a single executable.
Remove any complaints
.V= valgrind
may have about
memory access or memory leaks.
Run
.V= checksource .
.H 1 "What to Submit"
The
.V= Makefile
and all source code, but no object files or executable binaries.
Do a build in your own directory to verify that it works.
Look in the submit volume to verify that there are no missing files.
If you do pair programming,
also follow the instructions in
.V= /afs/cats.ucsc.edu/courses/cmps012b-wm/Syllabus/pair-programming/ .
.FINISH
