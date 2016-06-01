//==============================================================================
// matrix4.cpp
//==============================================================================
//  Copyright (C) DejaTools, LLC.  All rights reserved.
//==============================================================================

//==============================================================================
//  INCLUDES
//==============================================================================

#include "stdafx.h"
#include "matrix4.h"

//==============================================================================
//  DEFINES
//==============================================================================

#define M( Column, Row )   m_Cell[ Column ][ Row ]

//==============================================================================
//
// Construct the matrix.
//
//==============================================================================

matrix4::matrix4( const vector3& Axis, float Angle )
{
    float c = cos( Angle );
    float s = sin( Angle );
    float t = 1 - c;
    float x = Axis.x;
    float y = Axis.y;
    float z = Axis.z;

    M(0,0) = t*x*x + c;
    M(0,1) = t*x*y + z*s;
    M(0,2) = t*x*z - y*s;
    M(1,0) = t*x*y - z*s;
    M(1,1) = t*y*y + c;
    M(1,2) = t*y*z + x*s;
    M(2,0) = t*x*z + y*s;
    M(2,1) = t*y*z - x*s;
    M(2,2) = t*z*z + c;
    M(0,3) = M(1,3) = M(2,3) = M(3,0) = M(3,1) = M(3,2) = 0.0f;
    M(3,3) = 1.0f;
}

//==============================================================================
//
// matrix4 multiply
//
//==============================================================================

matrix4 operator * ( const matrix4& L, const matrix4& R )
{
    matrix4 Result;

    for( int i = 0; i < 4; i++ )
    {
        Result.M(i,0) = (L.M(0,0)*R.M(i,0)) + (L.M(1,0)*R.M(i,1)) + (L.M(2,0)*R.M(i,2)) + (L.M(3,0)*R.M(i,3));
        Result.M(i,1) = (L.M(0,1)*R.M(i,0)) + (L.M(1,1)*R.M(i,1)) + (L.M(2,1)*R.M(i,2)) + (L.M(3,1)*R.M(i,3));
        Result.M(i,2) = (L.M(0,2)*R.M(i,0)) + (L.M(1,2)*R.M(i,1)) + (L.M(2,2)*R.M(i,2)) + (L.M(3,2)*R.M(i,3));
        Result.M(i,3) = (L.M(0,3)*R.M(i,0)) + (L.M(1,3)*R.M(i,1)) + (L.M(2,3)*R.M(i,2)) + (L.M(3,3)*R.M(i,3));
    }

    return( Result );
}

//==============================================================================
