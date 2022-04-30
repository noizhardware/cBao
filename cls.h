#ifndef _CLS_H_
#define _CLS_H_

#define CLS_VERSION "2022d30-1640"

/*** TODO
 https://docs.microsoft.com/en-US/windows/console/console-virtual-terminal-sequences
*/

/*** INCLUDES */
#ifdef __linux__
	/* linux code goes here */
#elif _WIN32
	/*  windows code goes here */
	#include <windows.h>
	#include <wchar.h>
#else

#endif
/* INCLUDES end. */

#ifdef __cplusplus
	extern "C" {
#endif

/*** DEFINES */
/* DEFINES end. */

/*** TYPEDEFS */
/* TYPEDEFS end. */

/*** GLOBALS */
/* GLOBALS end. */

/*** FUNCTION DECLARATIONS */
	int cls();
/* FUNCTION DECLARATIONS end. */

/*** FUNCTION DEFINITIONS */
#ifdef __linux__
	/* linux code goes here */
#elif _WIN32
	/*  windows code goes here */
	int cls(){
		HANDLE hStdOut;
		DWORD mode;
		DWORD originalMode;
		DWORD written;
		PCWSTR sequence;
	
		hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
		/* Fetch existing console mode so we correctly add a flag and not turn off others*/
		mode = 0;
		if (!GetConsoleMode(hStdOut, &mode))
		{
			return GetLastError();
		}
	
		/*Hold original mode to restore on exit to be cooperative with other command-line apps.*/
		originalMode = mode;
		mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	
		/* Try to set the mode.*/
		if (!SetConsoleMode(hStdOut, mode))
		{
			return GetLastError();
		}
	
		/* Write the sequence for clearing the display.*/
		written = 0;
		sequence = L"\x1b[2J";
		if (!WriteConsoleW(hStdOut, sequence, (DWORD)wcslen(sequence), &written, NULL))
		{
			/* If we fail, try to restore the mode on the way out.*/
			SetConsoleMode(hStdOut, originalMode);
			return GetLastError();
		}
		
		/* Write the sequence for repositioning cursor on upper left.*/
		written = 0;
		sequence = L"\x1b[0;0H";
		if (!WriteConsoleW(hStdOut, sequence, (DWORD)wcslen(sequence), &written, NULL))
		{
			/* If we fail, try to restore the mode on the way out.*/
			SetConsoleMode(hStdOut, originalMode);
			return GetLastError();
		}
		
	
		/* To also clear the scroll back, emit L"\x1b[3J" as well.*/
		/* 2J only clears the visible window and 3J only clears the scroll back.*/
	
		/* Restore the mode on the way out to be nice to other command-line applications.*/
		SetConsoleMode(hStdOut, originalMode);
		return 0;
	}/* cls win */
#else

#endif
/* FUNCTION DEFINITIONS end. */

#ifdef __cplusplus
	}
#endif
#endif /* _CLS_H_ */
