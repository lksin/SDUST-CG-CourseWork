#pragma once
// Vector.h: interface for the CVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR_H__801E7260_C628_439D_8624_9EFB0450A93C__INCLUDED_)
#define AFX_VECTOR_H__801E7260_C628_439D_8624_9EFB0450A93C__INCLUDED_

/*
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000*/
#include <math.h>
struct CVector
{
	double x, y, z;
	float ComputeLength(void)
	{
		return  (double)sqrt(x * x + y * y + z * z);
	};
	CVector operator+ (const CVector& v)
	{
		return CVector(v.x + x, v.y + y, v.z + z);
	};
	CVector  operator- (const CVector& v)
	{
		return CVector(x - v.x, y - v.y, z - v.z);
	};
	CVector  operator- ()
	{
		return CVector(-x, -y, -z);
	};
	CVector  operator* (const double scalar)
	{
		return CVector(x * scalar, y * scalar, z * scalar);
	};
	CVector  operator* (const CVector& v)
	{
		return CVector(x * v.x, y * v.y, z * v.z);
	};
	CVector  operator/ (const CVector& v)
	{
		return CVector(x / v.x, y / v.y, z / v.z);
	};
	CVector  operator/ (const double scalar)
	{
		return CVector(x / scalar, y / scalar, z / scalar);
	};
	/*	CVector  &operator= (const CVector &v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			return *this;
		};*/
	CVector()
	{
		x = 0; y = 0; z = 0;
	}
	CVector(double x, double y, double z)
	{
		this->x = x; this->y = y; this->z = z;
	};
	CVector(double* pXYZ)
	{
		this->x = *pXYZ; this->y = *(pXYZ + 1); this->z = *(pXYZ + 2);
	};

};

void ComputeNormal(CVector* v1, CVector* v2, CVector* v3);

double DotProduct(const CVector& v1, const CVector& v2);

CVector CrossProduct(const CVector& v1, const CVector& v2);


double Magnitude(CVector vNormal);

CVector Normalize(CVector vVector);

bool PntFrontOrBack(const CVector& vPnt, const CVector& vPtStart, const CVector& vDrct);

bool PntFrontOrBack2(const CVector& vPnt, const CVector& vPtStart, const CVector& vDrct);

double Dist(const CVector& v1, const CVector& v2);

#endif // !defined(AFX_VECTOR_H__801E7260_C628_439D_8624_9EFB0450A93C__INCLUDED_)
