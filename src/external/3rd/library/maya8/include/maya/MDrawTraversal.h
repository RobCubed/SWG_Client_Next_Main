#ifndef _MDrawTraversal
#define _MDrawTraversal
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
// CLASS:    MDrawTraversal
//
// ****************************************************************************
//
// CLASS DESCRIPTION (MDrawTraversal)
//
//  MDrawTraversal is a utility class to traverse through the current scene dag
//  and provide a means of accessing a list of visible objects with respect
//  to a given view and view volumne specification.
//
// ****************************************************************************

#if defined __cplusplus

// ****************************************************************************
// INCLUDED HEADER FILES


#include <maya/MStatus.h>

// *****************************************************************************

// DECLARATIONS

class MDagPath;
class MPoint;
class MMatrix;

// *****************************************************************************

// CLASS DECLARATION (MDrawTraversal)

/// A scene drawing traverser (OpenMayaUI)
/**

Scene draw traversal class.

*/
class OPENMAYAUI_EXPORT MDrawTraversal 
{
public:

	/// Item status enum
	enum {
		/// Check if item is active
		kActiveItem,
		/// Check if item is templated
		kTemplateItem				
	};

    ///
    MDrawTraversal();
    ///
    virtual ~MDrawTraversal();
	///
    virtual MStatus		traverse();
	///
	virtual bool		filterNode( const MDagPath &traversalItem );

	///
	MStatus				setFrustum( const MDagPath & cameraPath, unsigned int portWidth, 
									unsigned int portHeight );
	///
    MStatus				setOrthoFrustum(double left,      double right,
                             			double bottom,    double top,
                             			double nearpt,      double farpt,
                             			const MMatrix & worldXform);
	///
    MStatus				setPerspFrustum(double fovX,      double aspectXY,
                            			double nearDist,  double farDist,
                             			const MMatrix & worldXform);
	///
	MStatus				setFrustum(double left,      double right,
									double bottom,    double top,
									double nearpt,      double farpt,
                             	const MMatrix & worldXform);
	///
    MStatus				setFrustum (const MPoint& nearBottomLeft,
									const MPoint& nearBottomRight,
									const MPoint& nearTopLeft,
									const MPoint& nearTopRight,
									const MPoint& farBottomLeft,
									const MPoint& farBottomRight,
									const MPoint& farTopLeft,
									const MPoint& farTopRight,
									const MMatrix &worldXform);
	///
	bool				frustumValid() const;

	///
	void				setLeafLevelCulling( bool cullAtLeafLevel );
	///
	bool				leafLevelCulling() const;
	
	///
	void				enableFiltering( bool val );
	///
	bool				filteringEnabled() const;

	//
	// Traversed list methods
	//
	///
	unsigned int		numberOfItems() const;
	///
	MStatus				itemPath(unsigned int itemNumber, MDagPath &path) const;
	///
	bool				itemHasStatus(unsigned int itemNumber, unsigned int test) const;


protected:
	// 
	bool				fLeafLevelCulling;
	bool				fFrustumValid;
	bool				fFilteringEnabled;
private:
	void	*fPtr;
};

#endif /* __cplusplus */
#endif /* MDrawTraversal */
