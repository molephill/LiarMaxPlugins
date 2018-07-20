#include "Matrices.h"

const float DEG2RAD = 3.141593f / 180.0f;
const float RAD2DEG = 180.0f / 3.141593f;
const float EPSILON = 0.00001f;

namespace Liar
{
	///////////////////////////////////////////////////////////////////////////////
	// transpose 2x2 matrix
	///////////////////////////////////////////////////////////////////////////////
	Matrix2& Matrix2::Transpose()
	{
		std::swap(m1, m2);
		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////
	// return the determinant of 2x2 matrix
	///////////////////////////////////////////////////////////////////////////////
	float Matrix2::GetDeterminant() const
	{
		return m0 * m3 - m1 * m2;
	}

	///////////////////////////////////////////////////////////////////////////////
	// inverse of 2x2 matrix
	// If cannot find inverse, set identity matrix
	///////////////////////////////////////////////////////////////////////////////
	Matrix2& Matrix2::Invert()
	{
		float determinant = GetDeterminant();
		if (fabs(determinant) <= EPSILON)
		{
			return Identity();
		}

		float tmp = m1;   // copy the first element
		float invDeterminant = 1.0f / determinant;
		m0 = invDeterminant * m3;
		m1 = -invDeterminant * m1;
		m2 = -invDeterminant * m2;
		m3 = invDeterminant * tmp;

		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////
	// retrieve rotation angle in degree from rotation matrix, R
	// R = | c -s |
	//     | s  c |
	// angle = atan(s / c)
	///////////////////////////////////////////////////////////////////////////////
	float Matrix2::GetAngle() const
	{
		// angle between -pi ~ +pi (-180 ~ +180)
		return RAD2DEG * atan2f(m1, m0);
	}

	void Matrix2::SetRow(int index, const float row[2])
	{
		SetRowElement(index, row[0], row[1]);
	}

	void Matrix2::SetRow(int index, const std::vector<float>& row)
	{
		SetRowElement(index, row[0], row[1]);
	}

	void Matrix2::SetRow(int index, const Liar::Vector2D& row)
	{
		SetRowElement(index, row.x, row.y);
	}

	void Matrix2::SetCol(int index, const float row[2])
	{
		SetColElement(index, row[0], row[1]);
	}

	void Matrix2::SetCol(int index, const std::vector<float>& row)
	{
		SetColElement(index, row[0], row[1]);
	}

	void Matrix2::SetCol(int index, const Liar::Vector2D& row)
	{
		SetColElement(index, row.x, row.y);
	}

	void Matrix2::SetRowElement(int index, float v1, float v2)
	{
		if (index == 0)
		{
			m0 = v1;
			m2 = v2;
		}
		else
		{
			m1 = v1;
			m3 = v2;
		}
	}

	void Matrix2::SetColElement(int index, float v1, float v2)
	{
		if (index == 0)
		{
			m0 = v1;
			m1 = v2;
		}
		else
		{
			m2 = v1;
			m3 = v2;
		}
	}

	void Matrix2::GetRawData(std::vector<float>& out)
	{
		out = { m0, m1, m2, m3 };
	}

	// add rhs
	void Matrix2::Add(const Liar::Matrix2& rhs)
	{
		m0 += rhs.m0;
		m1 += rhs.m1;
		m2 += rhs.m2;
		m3 += rhs.m3;
	}

	// subtract rhs
	void Matrix2::Sub(const Liar::Matrix2& rhs)
	{
		m0 -= rhs.m0;
		m1 -= rhs.m1;
		m2 -= rhs.m2;
		m3 -= rhs.m3;
	}

	// multiplication: M3 = M1 * M2
	void Matrix2::Mul(const Liar::Matrix2& rhs)
	{
		float t0 = m0, t1 = m1, t2 = m2, t3 = m3;
		m0 = t0 * rhs.m0 + t2 * rhs.m1;
		m1 = t1 * rhs.m0 + t3 * rhs.m1;
		m2 = t0 * rhs.m2 + t2 * rhs.m3;
		m3 = t1 * rhs.m2 + t3 * rhs.m3;
	}

	// multiplication: M1' = M1 * M2
	void Matrix2::Mul(Liar::Vector2D& rhs)
	{
		float tx = rhs.x, ty = rhs.y;
		rhs.x = m0 * tx + m2 * ty;
		rhs.y = m1 * tx + m3 * ty;
	}

	// multiplication: M1' = M1 * M2
	void Matrix2::Mul(const Liar::Vector2D& rhs, Liar::Vector2D& out)
	{
		out.x = m0 * rhs.x + m2 * rhs.y;
		out.y = m1 * rhs.x + m3 * rhs.y;
	}

	void Matrix2::Mul(float v)
	{
		m0 *= v; m1 *= v;
		m2 *= v; m3 *= v;
	}


	///////////////////////////////////////////////////////////////////////////////
	// transpose 3x3 matrix
	///////////////////////////////////////////////////////////////////////////////
	Matrix3& Matrix3::Transpose()
	{
		float tmp = m1;
		tmp = m1; m1 = m3; m3 = tmp;
		tmp = m2; m2 = m6; m6 = tmp;
		tmp = m5; m5 = m7; m7 = tmp;
		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////
	// return determinant of 3x3 matrix
	///////////////////////////////////////////////////////////////////////////////
	float Matrix3::GetDeterminant() const
	{
		return  m0 * (m4 * m8 - m5 * m7) -
				m1 * (m3 * m8 - m5 * m6) +
				m2 * (m3 * m7 - m4 * m6);
	}

	///////////////////////////////////////////////////////////////////////////////
	// inverse 3x3 matrix
	// If cannot find inverse (det=0), set identity matrix
	// M^-1 = adj(M) / det(M)
	//        | m4m8-m5m7  m5m6-m3m8  m3m7-m4m6 |
	//      = | m7m2-m8m1  m0m8-m2m6  m6m1-m7m0 | / det(M)
	//        | m1m5-m2m4  m2m3-m0m5  m0m4-m1m3 |
	///////////////////////////////////////////////////////////////////////////////
	Matrix3& Matrix3::Invert()
	{
		float determinant, invDeterminant;
		float tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8;

		tmp0 = m4 * m8 - m5 * m7;
		tmp1 = m7 * m2 - m8 * m1;
		tmp2 = m1 * m5 - m2 * m4;
		tmp3 = m5 * m6 - m3 * m8;
		tmp4 = m0 * m8 - m2 * m6;
		tmp5 = m2 * m3 - m0 * m5;
		tmp6 = m3 * m7 - m4 * m6;
		tmp7 = m6 * m1 - m7 * m0;
		tmp8 = m0 * m4 - m1 * m3;

		// check determinant if it is 0
		determinant = m0 * tmp0 + m1 * tmp3 + m2 * tmp6;
		if (fabs(determinant) <= EPSILON)
		{
			return Identity(); // cannot inverse, make it idenety matrix
		}

		// divide by the determinant
		invDeterminant = 1.0f / determinant;
		m0 = invDeterminant * tmp0;
		m1 = invDeterminant * tmp1;
		m2 = invDeterminant * tmp2;
		m3 = invDeterminant * tmp3;
		m4 = invDeterminant * tmp4;
		m5 = invDeterminant * tmp5;
		m6 = invDeterminant * tmp6;
		m7 = invDeterminant * tmp7;
		m8 = invDeterminant * tmp8;

		return *this;
	}



	///////////////////////////////////////////////////////////////////////////////
	// retrieve angles in degree from rotation matrix, M = Rx*Ry*Rz
	// Rx: rotation about X-axis, pitch
	// Ry: rotation about Y-axis, yaw(heading)
	// Rz: rotation about Z-axis, roll
	//    Rx           Ry          Rz
	// |1  0   0| | Cy  0 Sy| |Cz -Sz 0|   | CyCz        -CySz         Sy  |
	// |0 Cx -Sx|*|  0  1  0|*|Sz  Cz 0| = | SxSyCz+CxSz -SxSySz+CxCz -SxCy|
	// |0 Sx  Cx| |-Sy  0 Cy| | 0   0 1|   |-CxSyCz+SxSz  CxSySz+SxCz  CxCy|
	//
	// Pitch: atan(-m[7] / m[8]) = atan(SxCy/CxCy)
	// Yaw  : asin(m[6]) = asin(Sy)
	// Roll : atan(-m[3] / m[0]) = atan(SzCy/CzCy)
	///////////////////////////////////////////////////////////////////////////////
	Vector3D Matrix3::GetAngle() const
	{
		Liar::Vector3D vec;
		GetAngle(vec);
		return vec;
	}

	void Matrix3::GetAngle(Liar::Vector3D& out) const
	{
		float pitch, yaw, roll;         // 3 angles

										// find yaw (around y-axis) first
										// NOTE: asin() returns -90~+90, so correct the angle range -180~+180
										// using z value of forward vector
		yaw = RAD2DEG * asinf(m6);
		if (m8 < 0)
		{
			if (yaw >= 0) yaw = 180.0f - yaw;
			else         yaw = -180.0f - yaw;
		}

		// find roll (around z-axis) and pitch (around x-axis)
		// if forward vector is (1,0,0) or (-1,0,0), then m[0]=m[4]=m[9]=m[10]=0
		if (m0 > -EPSILON && m0 < EPSILON)
		{
			roll = 0;  //@@ assume roll=0
			pitch = RAD2DEG * atan2f(m1, m4);
		}
		else
		{
			roll = RAD2DEG * atan2f(-m3, m0);
			pitch = RAD2DEG * atan2f(-m7, m8);
		}
		out.x = pitch;
		out.y = yaw;
		out.z = roll;
	}

	void Matrix3::Add(const Liar::Matrix3& rhs)
	{
		m0 += rhs.m0;
		m1 += rhs.m1;
		m2 += rhs.m2;
		m3 += rhs.m1;
		m4 += rhs.m4;
		m5 += rhs.m5;
		m6 += rhs.m6;
		m7 += rhs.m7;
		m8 += rhs.m8;
	}

	void Matrix3::Sub(const Liar::Matrix3& rhs)
	{
		m0 -= rhs.m0;
		m1 -= rhs.m1;
		m2 -= rhs.m2;
		m3 -= rhs.m1;
		m4 -= rhs.m4;
		m5 -= rhs.m5;
		m6 -= rhs.m6;
		m7 -= rhs.m7;
		m8 -= rhs.m8;
	}

	void Matrix3::Mul(const Liar::Matrix3& rhs)
	{
		float t0 = m0, t1 = m1, t2 = m2, t3 = m3, t4 = m4, t5 = m5, t6 = m6, t7 = m7, t8 = m8;
		m0 = t0 * rhs.m0 + t3 * rhs.m1 + t6 * rhs.m2;
		m1 = t1 * rhs.m0 + t4 * rhs.m1 + t7 * rhs.m2;
		m2 = t2 * rhs.m0 + t5 * rhs.m1 + t8 * rhs.m2;
		m3 = t0 * rhs.m3 + t3 * rhs.m4 + t6 * rhs.m5;
		m4 = t1 * rhs.m3 + t4 * rhs.m4 + t7 * rhs.m5;
		m5 = t2 * rhs.m3 + t5 * rhs.m4 + t8 * rhs.m5;
		m6 = t0 * rhs.m6 + t3 * rhs.m7 + t6 * rhs.m8;
		m7 = t1 * rhs.m6 + t4 * rhs.m7 + t7 * rhs.m8;
		m8 = t2 * rhs.m6 + t5 * rhs.m7 + t8 * rhs.m8;
	}

	void Matrix3::Mul(Liar::Vector3D& rhs)
	{
		float tx = rhs.x, ty = rhs.y, tz = rhs.z;
		rhs.x = tx*m0 + ty*m1 + tz*m2;
		rhs.y = tx*m3 + ty*m4 + tz*m5;
		rhs.z = tx*m6 + ty*m7 + tz*m8;
	}

	void Matrix3::Mul(const Liar::Vector3D& rhs, Liar::Vector3D& out)
	{
		out.x = rhs.x*m0 + rhs.y*m1 + rhs.z*m2;
		out.y = rhs.x*m3 + rhs.y*m4 + rhs.z*m5;
		out.z = rhs.x*m6 + rhs.y*m7 + rhs.z*m8;
	}

	//=============================================================================

	void Matrix3::SetRow(int index, const float row[3])
	{
		SetRowElement(index, row[0], row[1], row[2]);
	}

	void Matrix3::SetRow(int index, const std::vector<float>& row)
	{
		SetRowElement(index, row[0], row[1], row[2]);
	}

	void Matrix3::SetRow(int index, const Liar::Vector3D& row)
	{
		SetRowElement(index, row.x, row.y, row.z);
	}

	void Matrix3::SetCol(int index, const float row[3])
	{
		SetColElement(index, row[0], row[1], row[2]);
	}

	void Matrix3::SetCol(int index, const std::vector<float>& row)
	{
		SetColElement(index, row[0], row[1], row[2]);
	}

	void Matrix3::SetCol(int index, const Liar::Vector3D& row)
	{
		SetColElement(index, row.x, row.y, row.z);
	}

	void Matrix3::SetRowElement(int index, float v1, float v2, float v3)
	{
		if (index == 0)
		{
			m0 = v1;
			m3 = v2;
			m6 = v3;
		}
		else if(index == 1)
		{
			m1 = v1;
			m4 = v2;
			m7 = v3;
		}
		else
		{
			m2 = v1;
			m5 = v2;
			m8 = v3;
		}
	}

	void Matrix3::SetColElement(int index, float v1, float v2, float v3)
	{
		if (index == 0)
		{
			m0 = v1;
			m1 = v2;
			m2 = v3;
		}
		else if(index == 1)
		{
			m3 = v1;
			m4 = v2;
			m5 = v3;
		}
		else
		{
			m6 = v1;
			m7 = v2;
			m8 = v3;
		}
	}

	void Matrix3::GetRawData(std::vector<float>& out)
	{
		out = { m0, m1, m2, m3, m4, m5, m6, m7, m8 };
	}


	///////////////////////////////////////////////////////////////////////////////
	// transpose 4x4 matrix
	///////////////////////////////////////////////////////////////////////////////
	Matrix4& Matrix4::Transpose()
	{
		float tmp = m0;
		tmp = m0; m0 = m4; m4 = tmp;
		tmp = m2; m2 = m8; m8 = tmp;
		tmp = m3; m3 = m12; m12 = tmp;
		tmp = m6; m6 = m9; m9 = tmp;
		tmp = m7; m7 = m13; m13 = tmp;
		tmp = m11; m11 = m14; m14 = tmp;

		return *this;
	}

	void Matrix4::SetRow(int index, const float row[4])
	{
		SetRowElement(index, row[0], row[1], row[2], row[3]);
	}

	void Matrix4::SetRow(int index, const std::vector<float>& row)
	{
		SetRowElement(index, row[0], row[1], row[2], row[3]);
	}

	void Matrix4::SetRow(int index, const Liar::Vector4D& row)
	{
		SetRowElement(index, row.x, row.y, row.z, row.w);
	}

	void Matrix4::SetRow(int index, const Liar::Vector3D& row)
	{
		float v4 = 0.0f;
		if (index == 0)
		{
			v4 = m12;
		}
		else if (index == 1)
		{
			v4 = m13;
		}
		else if (index == 2)
		{
			v4 = m14;
		}
		else
		{
			v4 = m15;
		}
		SetRowElement(index, row.x, row.y, row.z, v4);
	}

	void Matrix4::SetCol(int index, const float row[4])
	{
		SetColElement(index, row[0], row[1], row[2], row[3]);
	}

	void Matrix4::SetCol(int index, const std::vector<float>& row)
	{
		SetColElement(index, row[0], row[1], row[2], row[3]);
	}

	void Matrix4::SetCol(int index, const Liar::Vector4D& row)
	{
		SetColElement(index, row.x, row.y, row.z, row.w);
	}

	void Matrix4::SetCol(int index, const Liar::Vector3D& row)
	{
		float v4 = 0.0f;
		if (index == 0)
		{
			v4 = m3;
		}
		else if (index == 1)
		{
			v4 = m7;
		}
		else if (index == 2)
		{
			v4 = m11;
		}
		else
		{
			v4 = m15;
		}
		SetColElement(index, row.x, row.y, row.z, v4);
	}

	void Matrix4::SetRowElement(int index, float v1, float v2, float v3, float v4)
	{
		if (index == 0)
		{
			m0 = v1;
			m4 = v2;
			m8 = v3;
			m12 = v4;
		}
		else if (index == 1)
		{
			m1 = v1;
			m5 = v2;
			m9 = v3;
			m13 = v4;
		}
		else if(index == 2)
		{
			m2 = v1;
			m6 = v2;
			m10 = v3;
			m14 = v4;
		}
		else
		{
			m3 = v1;
			m7 = v2;
			m11 = v3;
			m15 = v4;
		}
	}

	void Matrix4::SetColElement(int index, float v1, float v2, float v3, float v4)
	{
		if (index == 0)
		{
			m0 = v1;
			m1 = v2;
			m2 = v3;
			m3 = v4;
		}
		else if (index == 1)
		{
			m4 = v1;
			m5 = v2;
			m6 = v3;
			m7 = v4;
		}
		else if(index == 2)
		{
			m8 = v1;
			m9 = v2;
			m10 = v3;
			m11 = v4;
		}
		else
		{
			m12 = v1;
			m13 = v2;
			m14 = v3;
			m15 = v4;
		}
	}

	void Matrix4::GetRawData(std::vector<float>& out)
	{
		out = { m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15 };
	}

	///////////////////////////////////////////////////////////////////////////////
	// inverse 4x4 matrix
	///////////////////////////////////////////////////////////////////////////////
	Matrix4& Matrix4::Invert()
	{
		// If the 4th row is [0,0,0,1] then it is affine matrix and
		// it has no projective transformation.
		if (m3 == 0 && m7 == 0 && m11 == 0 && m15 == 1)
			this->InvertAffine();
		else
		{
			this->InvertGeneral();
			/*@@ invertProjective() is not optimized (slower than generic one)
			if(fabs(m[0]*m[5] - m[1]*m[4]) > EPSILON)
			this->invertProjective();   // inverse using matrix partition
			else
			this->invertGeneral();      // generalized inverse
			*/
		}

		return *this;
	}



	///////////////////////////////////////////////////////////////////////////////
	// compute the inverse of 4x4 Euclidean transformation matrix
	//
	// Euclidean transformation is translation, rotation, and reflection.
	// With Euclidean transform, only the position and orientation of the object
	// will be changed. Euclidean transform does not change the shape of an object
	// (no scaling). Length and angle are reserved.
	//
	// Use inverseAffine() if the matrix has scale and shear transformation.
	//
	// M = [ R | T ]
	//     [ --+-- ]    (R denotes 3x3 rotation/reflection matrix)
	//     [ 0 | 1 ]    (T denotes 1x3 translation matrix)
	//
	// y = M*x  ->  y = R*x + T  ->  x = R^-1*(y - T)  ->  x = R^T*y - R^T*T
	// (R is orthogonal,  R^-1 = R^T)
	//
	//  [ R | T ]-1    [ R^T | -R^T * T ]    (R denotes 3x3 rotation matrix)
	//  [ --+-- ]   =  [ ----+--------- ]    (T denotes 1x3 translation)
	//  [ 0 | 1 ]      [  0  |     1    ]    (R^T denotes R-transpose)
	///////////////////////////////////////////////////////////////////////////////
	Matrix4& Matrix4::InvertEuclidean()
	{
		// transpose 3x3 rotation matrix part
		// | R^T | 0 |
		// | ----+-- |
		// |  0  | 1 |
		float tmp;
		tmp = m1;  m1 = m4;  m4 = tmp;
		tmp = m2;  m2 = m8;  m8 = tmp;
		tmp = m6;  m6 = m9;  m9 = tmp;

		// compute translation part -R^T * T
		// | 0 | -R^T x |
		// | --+------- |
		// | 0 |   0    |
		float x = m12;
		float y = m13;
		float z = m14;
		m12 = -(m0 * x + m4 * y + m8 * z);
		m13 = -(m1 * x + m5 * y + m9 * z);
		m14 = -(m2 * x + m6 * y + m10 * z);

		// last row should be unchanged (0,0,0,1)

		return *this;
	}



	///////////////////////////////////////////////////////////////////////////////
	// compute the inverse of a 4x4 affine transformation matrix
	//
	// Affine transformations are generalizations of Euclidean transformations.
	// Affine transformation includes translation, rotation, reflection, scaling,
	// and shearing. Length and angle are NOT preserved.
	// M = [ R | T ]
	//     [ --+-- ]    (R denotes 3x3 rotation/scale/shear matrix)
	//     [ 0 | 1 ]    (T denotes 1x3 translation matrix)
	//
	// y = M*x  ->  y = R*x + T  ->  x = R^-1*(y - T)  ->  x = R^-1*y - R^-1*T
	//
	//  [ R | T ]-1   [ R^-1 | -R^-1 * T ]
	//  [ --+-- ]   = [ -----+---------- ]
	//  [ 0 | 1 ]     [  0   +     1     ]
	///////////////////////////////////////////////////////////////////////////////
	Matrix4& Matrix4::InvertAffine()
	{
		// R^-1
		Matrix3 r(m0, m1, m2, m4, m5, m6, m8, m9, m11);
		r.Invert();
		m0 = r.m0;  m1 = r.m1;  m2 = r.m2;
		m4 = r.m3;  m5 = r.m4;  m6 = r.m5;
		m8 = r.m6;  m9 = r.m7;  m10 = r.m8;

		// -R^-1 * T
		float x = m12;
		float y = m13;
		float z = m14;
		m12 = -(r.m0 * x + r.m3 * y + r.m6 * z);
		m13 = -(r.m1 * x + r.m4 * y + r.m7 * z);
		m14 = -(r.m2 * x + r.m5 * y + r.m8 * z);

		// last row should be unchanged (0,0,0,1)
		//m[3] = m[7] = m[11] = 0.0f;
		//m[15] = 1.0f;

		return *this;
	}



	///////////////////////////////////////////////////////////////////////////////
	// inverse matrix using matrix partitioning (blockwise inverse)
	// It devides a 4x4 matrix into 4 of 2x2 matrices. It works in case of where
	// det(A) != 0. If not, use the generic inverse method
	// inverse formula.
	// M = [ A | B ]    A, B, C, D are 2x2 matrix blocks
	//     [ --+-- ]    det(M) = |A| * |D - ((C * A^-1) * B)|
	//     [ C | D ]
	//
	// M^-1 = [ A' | B' ]   A' = A^-1 - (A^-1 * B) * C'
	//        [ ---+--- ]   B' = (A^-1 * B) * -D'
	//        [ C' | D' ]   C' = -D' * (C * A^-1)
	//                      D' = (D - ((C * A^-1) * B))^-1
	//
	// NOTE: I wrap with () if it it used more than once.
	//       The matrix is invertable even if det(A)=0, so must check det(A) before
	//       calling this function, and use invertGeneric() instead.
	///////////////////////////////////////////////////////////////////////////////
	Matrix4& Matrix4::InvertProjective()
	{
		// partition
		Matrix2 a(m0, m1, m4, m5);
		Matrix2 b(m8, m9, m12, m13);
		Matrix2 c(m2, m3, m6, m7);
		Matrix2 d(m10, m11, m14, m15);

		// pre-compute repeated parts
		a.Invert();             // A^-1
		Matrix2 ab = a * b;     // A^-1 * B
		Matrix2 ca = c * a;     // C * A^-1
		Matrix2 cab = ca * b;   // C * A^-1 * B
		Matrix2 dcab = d - cab; // D - C * A^-1 * B

		// check determinant if |D - C * A^-1 * B| = 0
		//NOTE: this function assumes det(A) is already checked. if |A|=0 then,
		//      cannot use this function.
		float determinant = dcab.m0 * dcab.m3 - dcab.m1 * dcab.m2;
		if (fabs(determinant) <= EPSILON)
		{
			return Identity();
		}

		// compute D' and -D'
		Matrix2 d1 = dcab;      //  (D - C * A^-1 * B)
		d1.Invert();            //  (D - C * A^-1 * B)^-1
		Matrix2 d2 = -d1;       // -(D - C * A^-1 * B)^-1

		// compute C'
		Matrix2 c1 = d2 * ca;   // -D' * (C * A^-1)

		// compute B'
		Matrix2 b1 = ab * d2;   // (A^-1 * B) * -D'

		// compute A'
		Matrix2 a1 = a - (ab * c1); // A^-1 - (A^-1 * B) * C'

									// assemble inverse matrix
		m0 = a1.m0;  m4 = a1.m2; /*|*/ m8 = b1.m0;  m12 = b1.m2;
		m1 = a1.m1;  m5 = a1.m3; /*|*/ m9 = b1.m1;  m13 = b1.m3;
		/*-----------------------------+-----------------------------*/
		m2 = c1.m0;  m6 = c1.m2; /*|*/ m10 = d1.m0;  m14 = d1.m2;
		m3 = c1.m1;  m7 = c1.m3; /*|*/ m11 = d1.m1;  m15 = d1.m3;

		return *this;
	}



	///////////////////////////////////////////////////////////////////////////////
	// compute the inverse of a general 4x4 matrix using Cramer's Rule
	// If cannot find inverse, return indentity matrix
	// M^-1 = adj(M) / det(M)
	///////////////////////////////////////////////////////////////////////////////
	Matrix4& Matrix4::InvertGeneral()
	{
		// get cofactors of minor matrices
		float cofactor0 = GetCofactor(m5, m6, m7, m9, m10, m11, m13, m14, m5);
		float cofactor1 = GetCofactor(m4, m6, m7, m8, m10, m11, m12, m14, m15);
		float cofactor2 = GetCofactor(m4, m5, m7, m8, m9, m11, m12, m13, m15);
		float cofactor3 = GetCofactor(m4, m5, m6, m8, m9, m10, m12, m13, m14);

		// get determinant
		float determinant = m0 * cofactor0 - m1 * cofactor1 + m2 * cofactor2 - m3 * cofactor3;
		if (fabs(determinant) <= EPSILON)
		{
			return Identity();
		}

		// get rest of cofactors for adj(M)
		float cofactor4 = GetCofactor(m1, m2, m3, m9, m10, m11, m13, m14, m15);
		float cofactor5 = GetCofactor(m0, m2, m3, m8, m10, m11, m12, m14, m15);
		float cofactor6 = GetCofactor(m0, m1, m3, m8, m9, m11, m12, m13, m15);
		float cofactor7 = GetCofactor(m0, m1, m2, m8, m9, m10, m12, m13, m14);

		float cofactor8 = GetCofactor(m1, m2, m3, m5, m6, m7, m13, m14, m15);
		float cofactor9 = GetCofactor(m0, m2, m3, m4, m6, m7, m12, m14, m15);
		float cofactor10 = GetCofactor(m0, m1, m3, m4, m5, m7, m12, m13, m15);
		float cofactor11 = GetCofactor(m0, m1, m2, m4, m5, m6, m12, m13, m14);

		float cofactor12 = GetCofactor(m1, m2, m3, m5, m6, m7, m9, m10, m11);
		float cofactor13 = GetCofactor(m0, m2, m3, m4, m6, m7, m8, m10, m11);
		float cofactor14 = GetCofactor(m0, m1, m3, m4, m5, m7, m8, m9, m11);
		float cofactor15 = GetCofactor(m0, m1, m2, m4, m5, m6, m8, m9, m10);

		// build inverse matrix = adj(M) / det(M)
		// adjugate of M is the transpose of the cofactor matrix of M
		float invDeterminant = 1.0f / determinant;
		m0 = invDeterminant * cofactor0;
		m1 = -invDeterminant * cofactor4;
		m2 = invDeterminant * cofactor8;
		m3 = -invDeterminant * cofactor12;

		m4 = -invDeterminant * cofactor1;
		m5 = invDeterminant * cofactor5;
		m6 = -invDeterminant * cofactor9;
		m7 = invDeterminant * cofactor13;

		m8 = invDeterminant * cofactor2;
		m9 = -invDeterminant * cofactor6;
		m10 = invDeterminant * cofactor10;
		m11 = -invDeterminant * cofactor14;

		m12 = -invDeterminant * cofactor3;
		m13 = invDeterminant * cofactor7;
		m14 = -invDeterminant * cofactor11;
		m15 = invDeterminant * cofactor15;

		return *this;
	}



	///////////////////////////////////////////////////////////////////////////////
	// return determinant of 4x4 matrix
	///////////////////////////////////////////////////////////////////////////////
	float Matrix4::GetDeterminant() const
	{
		return  m0 * GetCofactor(m5, m6, m7, m9, m10, m11, m13, m14, m15) -
				m1 * GetCofactor(m4, m6, m7, m8, m10, m11, m12, m14, m15) +
				m2 * GetCofactor(m4, m5, m7, m8, m9, m11, m12, m13, m15) -
				m3 * GetCofactor(m4, m5, m6, m8, m9, m10, m12, m13, m14);
	}



	///////////////////////////////////////////////////////////////////////////////
	// compute cofactor of 3x3 minor matrix without sign
	// input params are 9 elements of the minor matrix
	// NOTE: The caller must know its sign.
	///////////////////////////////////////////////////////////////////////////////
	float Matrix4::GetCofactor(float m0, float m1, float m2,
					float m3, float m4, float m5,
					float m6, float m7, float m8) const
	{
		return m0 * (m4 * m8 - m5 * m7) -
			m1 * (m3 * m8 - m5 * m6) +
			m2 * (m3 * m7 - m4 * m6);
	}



	///////////////////////////////////////////////////////////////////////////////
	// translate this matrix by (x, y, z)
	///////////////////////////////////////////////////////////////////////////////
	Matrix4& Matrix4::Translate(const Vector3D& v)
	{
		return Translate(v.x, v.y, v.z);
	}

	Matrix4& Matrix4::Translate(float x, float y, float z)
	{
		m0 += m3 * x;   m4 += m7 * x;   m8 += m11 * x;   m12 += m15 * x;
		m1 += m3 * y;   m5 += m7 * y;   m9 += m11 * y;   m13 += m15 * y;
		m2 += m3 * z;   m6 += m7 * z;   m10 += m11 * z;   m14 += m15 * z;

		return *this;
	}



	///////////////////////////////////////////////////////////////////////////////
	// uniform scale
	///////////////////////////////////////////////////////////////////////////////
	Matrix4& Matrix4::Scale(float s)
	{
		return Scale(s, s, s);
	}

	Matrix4& Matrix4::Scale(float x, float y, float z)
	{
		m0 *= x;   m4 *= x;   m8 *= x;   m12 *= x;
		m1 *= y;   m5 *= y;   m9 *= y;   m13 *= y;
		m2 *= z;   m6 *= z;   m10 *= z;   m14 *= z;
		return *this;
	}



	///////////////////////////////////////////////////////////////////////////////
	// build a rotation matrix with given angle(degree) and rotation axis, then
	// multiply it with this object
	///////////////////////////////////////////////////////////////////////////////
	Matrix4& Matrix4::Rotate(float angle, const Vector3D& axis)
	{
		return Rotate(angle, axis.x, axis.y, axis.z);
	}

	Matrix4& Matrix4::Rotate(float angle, float x, float y, float z)
	{
		float c = cosf(angle * DEG2RAD);    // cosine
		float s = sinf(angle * DEG2RAD);    // sine
		float c1 = 1.0f - c;                // 1 - c
		float   tm0 = m0, tm4 = m4, tm8 = m8, tm12 = m12,
				tm1 = m1, tm5 = m5, tm9 = m9, tm13 = m13,
				tm2 = m2, tm6 = m6, tm10 = m10, tm14 = m14;

		// build rotation matrix
		float r0 = x * x * c1 + c;
		float r1 = x * y * c1 + z * s;
		float r2 = x * z * c1 - y * s;
		float r4 = x * y * c1 - z * s;
		float r5 = y * y * c1 + c;
		float r6 = y * z * c1 + x * s;
		float r8 = x * z * c1 + y * s;
		float r9 = y * z * c1 - x * s;
		float r10 = z * z * c1 + c;

		// multiply rotation matrix
		m0 = r0 * tm0 + r4 * tm1 + r8 * tm2;
		m1 = r1 * tm0 + r5 * tm1 + r9 * tm2;
		m2 = r2 * tm0 + r6 * tm1 + r10* tm2;
		m4 = r0 * tm4 + r4 * tm5 + r8 * tm6;
		m5 = r1 * tm4 + r5 * tm5 + r9 * tm6;
		m6 = r2 * tm4 + r6 * tm5 + r10* tm6;
		m8 = r0 * tm8 + r4 * tm9 + r8 * tm10;
		m9 = r1 * tm8 + r5 * tm9 + r9 * tm10;
		m10 = r2 * tm8 + r6 * tm9 + r10* tm10;
		m12 = r0 * tm12 + r4 * tm13 + r8 * tm14;
		m13 = r1 * tm12 + r5 * tm13 + r9 * tm14;
		m14 = r2 * tm12 + r6 * tm13 + r10* tm14;

		return *this;
	}

	Matrix4& Matrix4::RotateX(float angle)
	{
		float c = cosf(angle * DEG2RAD);
		float s = sinf(angle * DEG2RAD);
		float	tm1 = m1, tm2 = m2,
				tm5 = m5, tm6 = m6,
				tm9 = m9, tm10 = m10,
				tm13 = m13, tm14 = m14;

		m1 = tm1 * c + tm2 *-s;
		m2 = tm1 * s + tm2 * c;
		m5 = tm5 * c + tm6 *-s;
		m6 = tm5 * s + tm6 * c;
		m9 = tm9 * c + tm10*-s;
		m10 = tm9 * s + tm10* c;
		m13 = tm13* c + tm14*-s;
		m14 = tm13* s + tm14* c;

		return *this;
	}

	Matrix4& Matrix4::RotateY(float angle)
	{
		float c = cosf(angle * DEG2RAD);
		float s = sinf(angle * DEG2RAD);
		float	tm0 = m0, tm2 = m2,
				tm4 = m4, tm6 = m6,
				tm8 = m8, tm10 = m10,
				tm12 = m12, tm14 = m14;

		m0 = tm0 * c + tm2 * s;
		m2 = tm0 *-s + tm2 * c;
		m4 = tm4 * c + tm6 * s;
		m6 = tm4 *-s + tm6 * c;
		m8 = tm8 * c + tm10* s;
		m10 = tm8 *-s + tm10* c;
		m12 = tm12* c + tm14* s;
		m14 = tm12*-s + tm14* c;

		return *this;
	}

	Matrix4& Matrix4::RotateZ(float angle)
	{
		float c = cosf(angle * DEG2RAD);
		float s = sinf(angle * DEG2RAD);
		float	tm0 = m0, tm1 = m1,
				tm4 = m4, tm5 = m5,
				tm8 = m8, tm9 = m9,
				tm12 = m12, tm13 = m13;

		m0 = tm0 * c + tm1 *-s;
		m1 = tm0 * s + tm1 * c;
		m4 = tm4 * c + tm5 *-s;
		m5 = tm4 * s + tm5 * c;
		m8 = tm8 * c + tm9 *-s;
		m9 = tm8 * s + tm9 * c;
		m12 = tm12* c + tm13*-s;
		m13 = tm12* s + tm13* c;

		return *this;
	}



	///////////////////////////////////////////////////////////////////////////////
	// rotate matrix to face along the target direction
	// NOTE: This function will clear the previous rotation and scale info and
	// rebuild the matrix with the target vector. But it will keep the previous
	// translation values.
	// NOTE: It is for rotating object to look at the target, NOT for camera
	///////////////////////////////////////////////////////////////////////////////
	Matrix4& Matrix4::LookAt(const Vector3D& target)
	{
		return LookAt(target.x, target.y, target.z);
	}

	Matrix4& Matrix4::LookAt(const Vector3D& target, const Vector3D& upVec)
	{
		return LookAt(target.x, target.y, target.z, upVec.x, upVec.y, upVec.z);
	}

	Matrix4& Matrix4::LookAt(float tx, float ty, float tz)
	{
		//// compute forward vector and normalize
		//Vector3D position = Vector3D(m12, m13, m14);
		//Vector3D forward = target - position;
		//forward.Normalize();
		//Vector3D up;             // up vector of object
		//Vector3D left;           // left vector of object

		//						// compute temporal up vector
		//						// if forward vector is near Y-axis, use up vector (0,0,-1) or (0,0,1)
		//if (fabs(forward.x) < EPSILON && fabs(forward.z) < EPSILON)
		//{
		//	// forward vector is pointing +Y axis
		//	if (forward.y > 0)
		//		up.Set(0, 0, -1);
		//	// forward vector is pointing -Y axis
		//	else
		//		up.Set(0, 0, 1);
		//}
		//else
		//{
		//	// assume up vector is +Y axis
		//	up.Set(0, 1, 0);
		//}

		//// compute left vector
		//left = up.Cross(forward);
		//left.Normalize();

		//// re-compute up vector
		//up = forward.Cross(left);
		////up.normalize();

		//// NOTE: overwrite rotation and scale info of the current matrix
		//this->SetCol(0, left);
		//this->SetCol(1, up);
		//this->SetCol(2, forward);

		// compute forward vector and normalize
		Liar::Vector3D* forward = new Liar::Vector3D(m12, m13, m14);
		forward->Negative();
		forward->Add(tx, ty, tz);
		forward->Normalize();

		Liar::Vector3D* tmp = new Liar::Vector3D();

		// compute temporal up vector
		// if forward vector is near Y-axis, use up vector (0,0,-1) or (0,0,1)
		if (fabs(forward->x) < EPSILON && fabs(forward->z) < EPSILON)
		{
			// forward vector is pointing +Y axis
			if (forward->y > 0)
				tmp->Set(0.0, 0.0, -1.0f);
			// forward vector is pointing -Y axis
			else
				tmp->Set(0.0f, 0.0f, 1.0f);
		}
		else
		{
			// assume up vector is +Y axis
			tmp->Set(0.0f, 1.0f, 0.0f);
		}

		this->SetCol(2, *forward);

		// compute left vector
		tmp->CrossC(*forward);
		tmp->Normalize();

		// re-compute up vector
		forward->CrossC(*tmp);
		//up.normalize();

		// NOTE: overwrite rotation and scale info of the current matrix
		this->SetCol(0, *tmp);
		this->SetCol(1, *forward);

		delete tmp;
		delete forward;

		return *this;
	}

	Matrix4& Matrix4::LookAt(float tx, float ty, float tz, float ux, float uy, float uz)
	{
		//// compute forward vector and normalize
		//Vector3D position = Vector3D(m12, m13, m14);
		//Vector3D forward = target - position;
		//forward.Normalize();

		//// compute left vector
		//Vector3D left = upVec.Cross(forward);
		//left.Normalize();

		//// compute orthonormal up vector
		//Vector3D up = forward.Cross(left);
		//up.Normalize();

		//// NOTE: overwrite rotation and scale info of the current matrix
		//this->SetCol(0, left);
		//this->SetCol(1, up);
		//this->SetCol(2, forward);

		// compute forward vector and normalize
		Liar::Vector3D* forward = new Liar::Vector3D(tx, ty, tz);
		forward->Sub(m12, m13, m14);
		forward->Normalize();

		// compute left vector
		Liar::Vector3D* left = new Liar::Vector3D(ux, uy, uz);
		left->CrossC(*forward);
		left->Normalize();

		this->SetCol(0, *left);
		this->SetCol(2, *forward);

// compute orthonormal up vector
forward->CrossC(*left);
forward->Normalize();

// NOTE: overwrite rotation and scale info of the current matrix
this->SetCol(1, *forward);

delete forward;
delete left;

return *this;
	}



	///////////////////////////////////////////////////////////////////////////////
	// return 3x3 matrix containing rotation only
	///////////////////////////////////////////////////////////////////////////////
	Matrix3 Matrix4::GetRotationMatrix() const
	{
		Matrix3 mat(m0, m1, m2,
			m4, m5, m6,
			m8, m9, m10);
		return mat;
	}

	void Matrix4::GetRotationMatrix(Liar::Matrix3& v) const
	{
		v.Set(m0, m1, m2, m4, m5, m6, m8, m9, m10);
	}


	/*@@
	///////////////////////////////////////////////////////////////////////////////
	// skew with a given angle on the axis
	///////////////////////////////////////////////////////////////////////////////
	Matrix4& Matrix4::skew(float angle, const Vector3& axis)
	{
	float t = tanf(angle * DEG2RAD);    // tangent
	m[0] += m[1] * t;
	m[4] += m[5] * t;
	m[8] += m[9] * t;
	m[12]+= m[13]* t;
	return *this;
	}
	*/



	///////////////////////////////////////////////////////////////////////////////
	// retrieve angles in degree from rotation matrix, M = Rx*Ry*Rz
	// Rx: rotation about X-axis, pitch
	// Ry: rotation about Y-axis, yaw(heading)
	// Rz: rotation about Z-axis, roll
	//    Rx           Ry          Rz
	// |1  0   0| | Cy  0 Sy| |Cz -Sz 0|   | CyCz        -CySz         Sy  |
	// |0 Cx -Sx|*|  0  1  0|*|Sz  Cz 0| = | SxSyCz+CxSz -SxSySz+CxCz -SxCy|
	// |0 Sx  Cx| |-Sy  0 Cy| | 0   0 1|   |-CxSyCz+SxSz  CxSySz+SxCz  CxCy|
	//
	// Pitch: atan(-m[9] / m[10]) = atan(SxCy/CxCy)
	// Yaw  : asin(m[8]) = asin(Sy)
	// Roll : atan(-m[4] / m[0]) = atan(SzCy/CzCy)
	///////////////////////////////////////////////////////////////////////////////
	Vector3D Matrix4::GetAngle() const
	{
		float pitch = 0.0f, yaw = 0.0f, roll = 0.0f;         // 3 angles
		GetAngle(pitch, yaw, roll);

		return Vector3D(pitch, yaw, roll);
	}

	void Matrix4::GetAngle(Liar::Vector3D& out) const
	{
		float pitch = 0.0f, yaw = 0.0f, roll = 0.0f;         // 3 angles
		GetAngle(pitch, yaw, roll);
		out.Set(pitch, yaw, roll);
	}

	void Matrix4::GetAngle(float& pitch, float& yaw, float& roll) const
	{
		// find yaw (around y-axis) first
		// NOTE: asin() returns -90~+90, so correct the angle range -180~+180
		// using z value of forward vector

		yaw = RAD2DEG * asinf(m8);
		if (m10 < 0)
		{
			if (yaw >= 0) yaw = 180.0f - yaw;
			else         yaw = -180.0f - yaw;
		}

		// find roll (around z-axis) and pitch (around x-axis)
		// if forward vector is (1,0,0) or (-1,0,0), then m[0]=m[4]=m[9]=m[10]=0
		if (m0 > -EPSILON && m0 < EPSILON)
		{
			roll = 0;  //@@ assume roll=0
			pitch = RAD2DEG * atan2f(m1, m5);
		}
		else
		{
			roll = RAD2DEG * atan2f(-m4, m0);
			pitch = RAD2DEG * atan2f(-m9, m0);
		}
	}

}