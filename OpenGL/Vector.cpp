// Vector.cpp: implementation of the CVector class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "framework.h"
#include "OpenGL.h"
#include "Vector.h"

/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif*/


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------//
//- float ComputeDotProduct(CVector3*, CVector3*) ----------------------//
//------------------------------------------------------------------//
//- Description: Returns the dot product of two vectors (this stuff-//
//-              is pretty self explanatory, eh?).				   -//
//------------------------------------------------------------------//
double DotProduct(const CVector& v1, const CVector& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
};

//------------------------------------------------------------------//
//- CVector3 ComputeCrossProduct(CVector3*, CVector3*) -------------------//
//------------------------------------------------------------------//
//- Description: Returns the cross product of two vectors.		   -//
//------------------------------------------------------------------//
CVector CrossProduct(const CVector& v1, const CVector& v2)
{
	CVector result(0.0f, 0.0f, 0.0f);

	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);

	return result;
};



/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the magnitude of a vector
/////
/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

double Magnitude(CVector vNormal)
{
	// Here is the equation:  magnitude = sqrt(V.x^2 + V.y^2 + V.z^2) : Where V is the vector
	return (double)sqrt((vNormal.x * vNormal.x) +
		(vNormal.y * vNormal.y) +
		(vNormal.z * vNormal.z));
}


/////////////////////////////////////// NORMALIZE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns a normalize vector (A vector exactly of length 1)
/////
/////////////////////////////////////// NORMALIZE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

CVector Normalize(CVector vVector)
{
	// Get the magnitude of our normal
	double magnitude = Magnitude(vVector);

	// Now that we have the magnitude, we can divide our vector by that magnitude.
	// That will make our vector a total length of 1.  
	vVector = vVector / magnitude;

	// Finally, return our normalized vector
	return vVector;
}
bool SameSign(double f1, double f2)
{
	return f1 < 0 && f2 < 0 || f1>0 && f2>0 || f1 == 0 && f2 == 0 ? true : false;
}
//判断点vPnt是否在射线(起点是vPtStart,方向是vDrct)上
bool PntFrontOrBack(const CVector& vPnt, const CVector& vPtStart, const CVector& vDrct)
{
	return SameSign(vPnt.x - vPtStart.x, vDrct.x) &&
		SameSign(vPnt.y - vPtStart.y, vDrct.y) &&
		SameSign(vPnt.z - vPtStart.z, vDrct.z) ? true : false;
}
bool PntFrontOrBack2(const CVector& vPnt, const CVector& vPtStart, const CVector& vDrct)
{
	return SameSign(vPnt.x - vPtStart.x, vDrct.x) &&
		//	SameSign(vPnt.y-vPtStart.y,vDrct.y)&&
		SameSign(vPnt.z - vPtStart.z, vDrct.z) ? true : false;
}
double Dist(const CVector& v1, const CVector& v2)
{
	return double(sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y) + (v1.z - v2.z) * (v1.z - v2.z)));
}


void ComputeNormal(CVector* v1, CVector* v2, CVector* v3)
{
	CVector vVector1 = *v2 - *v1;
	CVector vVector2 = *v3 - *v1;

	// Get the cross product of our 2 vectors to get the normal to the polygon
	CVector vNormal = CrossProduct(vVector1, vVector2);

	// Now we normalize the normal so that it has a length of 1.0
	vNormal = Normalize(vNormal);

	// Finally, we assign the normal to the polygon
	//	*polygon->vNormal = vNormal;
}