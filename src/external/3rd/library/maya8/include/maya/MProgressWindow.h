
#ifndef _MProgressWindow
#define _MProgressWindow
//
//-
// ==========================================================================
// Copyright (C) 1995 - 2006 Autodesk, Inc., and/or its licensors.  All 
// rights reserved.
// 
// The coded instructions, statements, computer programs, and/or related 
// material (collectively the "Data") in these files contain unpublished 
// information proprietary to Autodesk, Inc. ("Autodesk") and/or its 
// licensors,  which is protected by U.S. and Canadian federal copyright law 
// and by international treaties.
// 
// The Data may not be disclosed or distributed to third parties or be 
// copied or duplicated, in whole or in part, without the prior written 
// consent of Autodesk.
// 
// The copyright notices in the Software and this entire statement, 
// including the above license grant, this restriction and the following 
// disclaimer, must be included in all copies of the Software, in whole 
// or in part, and all derivative works of the Software, unless such copies 
// or derivative works are solely in the form of machine-executable object 
// code generated by a source language processor.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND. 
// AUTODESK DOES NOT MAKE AND HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED 
// WARRANTIES INCLUDING, BUT NOT LIMITED TO, THE WARRANTIES OF 
// NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, 
// OR ARISING FROM A COURSE OF DEALING, USAGE, OR TRADE PRACTICE. IN NO 
// EVENT WILL AUTODESK AND/OR ITS LICENSORS BE LIABLE FOR ANY LOST 
// REVENUES, DATA, OR PROFITS, OR SPECIAL, DIRECT, INDIRECT, OR 
// CONSEQUENTIAL DAMAGES, EVEN IF AUTODESK AND/OR ITS LICENSORS HAS 
// BEEN ADVISED OF THE POSSIBILITY OR PROBABILITY OF SUCH DAMAGES. 
// ==========================================================================
//+
//
// CLASS:    MProgressWindow
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MProgressWindow)
//
// The MProgressWindow class manages a window containing a status message, a 
// graphical progress gauge, and optionally a "Hit ESC to Cancel" label for 
// interruptable operations.
//
// Only a single progress window may be displayed at any time.  To reserve the 
// use of the progress window, use the reserve() method in this class.  Any 
// methods that change the state of the progress window will fail unless the 
// progress window has first been successfully reserved.
//
// The startProgress() and endProgress() functions show and hide the progress 
// window.  endProgress() also has the effect of unreserving the progress 
// window, allowing it to be reserved for another use.
//
// The MEL command "progressWindow" provides equivalent functionality to this 
// class.  Attempting to manipulate a progress window that is in use by MEL 
// will cause the methods in this class to fail.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES



#include <maya/MStatus.h>

// *****************************************************************************

// DECLARATIONS

class MString;
class MStatus;

// *****************************************************************************

// CLASS DECLARATION (MProgressWindow)

/// Create and manipulate progress windows. (OpenMayaUI)
/**
*/

#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYAUI_EXPORT MProgressWindow
{
public:

	///
	static bool reserve();
	///
	static MStatus startProgress();
	///
	static MStatus endProgress();

	///
	static MStatus setProgressRange(const int minValue, const int maxValue);
	///
	static MStatus setProgressMin(const int minValue);
	///
	static MStatus setProgressMax(const int maxValue);

	///
	static int progressMin();
	///
	static int progressMax();
	
	///
	static MStatus setProgress(const int progress);
	///
	static MStatus advanceProgress(const int amount);
	///
	static int progress();
	
	///
	static MStatus setTitle(const MString &title);
	///
	static MString title();
	
	///
	static MStatus setProgressStatus(const MString &progressStatus);
	///
	static MString progressStatus();
	
	///
	static MStatus setInterruptable(const bool value);
	///
	static bool isInterruptable();
	///
	static bool isCancelled();

protected:
	// No protected members
private:
	static const char* 		className();

	static bool reserved;
};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************

#endif /* __cplusplus */
#endif /* _MProgressWindow */
