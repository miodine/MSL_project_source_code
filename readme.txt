Microprocessor System Laboratory - final project source code and documentation. 

I. 
Embedded App project library and main.c copied from the STM32CubeIDE file are stored in the 
'Source_code' folder. The main.c file can be found in that directory, and to access the library modules
navigate to 'Soucre_code\library\control_code_files', where all the modules (in form of .c/.h file pairs)
can be found. 

To see the doxygen-generated documentation for that module (for ease of navigation), please execute:
'Soucre_code\library\doxygen_output\html\index.html'.


II.
All the STM32CubeIDE files can be found in 'STM32CubeIDE_files' folder.

III. 
Desktop App files can be found in 'DesktopApp' folder, the 'serial_comunication.py' is a side module,
and 'python_UI.py' is the main file to be run. If ever to be tested, the app will prompt you
to write the serial port to which the NUCLEO board is connected (UART settings must be the 
same as for the LAB04 file, but the app will also prompt you about that as well - with the
exact specifications). The necessary modules for the app:
a. PyQt5 (QtCore, QtGui, QtWidgets - better to install the entire thing)
b. datetime
c. sys
d. qdarkstyle 
e. numpy
f. serial (download 'pyserial' - discrepancy in module, and pip name)
g. threading
h. matplotlib

Some of those should be pre-installed with python by default, rest can be downloaded using 'pip'. 
I tried to name the functions/variables/classes in such a way, that it would be clear what do they do. 
Conventions are not consistent (but for the most part I tried to stick with snake_case). 
