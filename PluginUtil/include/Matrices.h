#pragma once

///////////////////////////////////////////////////////////////////////////////
// Matrice.h
// =========
// NxN Matrix Math classes
//
// The elements of the matrix are stored as column major order.
// | 0 2 |    | 0 3 6 |    |  0  4  8 12 |
// | 1 3 |    | 1 4 7 |    |  1  5  9 13 |
//            | 2 5 8 |    |  2  6 10 14 |
//                         |  3  7 11 15 |
//
// Dependencies: Vector2D, Vector3D, Vector4D
///////////////////////////////////////////////////////////////////////////////

#include <Vectors.h>

#include <iostream>
#include <iomanip>
#include <vector>

namespace Liar
{
	class Matrix2
	{
	public:
		Matrix2();
		Matrix2(const float src[4]);
		Matrix2(const std::vector<float>&);
		Matrix2(float m0, float m1, float m2, float m3);

	public:
		void Set(const float src[4]);
		void Set(const std::vector<float>&);
		void Set(float, float, float, float);

		void				SetRow(int, const float src[2]);
		void				SetRow(int, const std::vector<float>&);
		void				SetRow(int, const Liar::Vector2D&);

		void				SetCol(int, const float src[2]);
		void				SetCol(int, const std::vector<float>&);
		void				SetCol(int, const Liar::Vector2D&);

		void				GetRawData(std::vector<float>&);						// return v[0] = m0, v[1] = m1, v[2] = m2, v[3] = m3

	public:
		void				Add(const Liar::Matrix2&);
		void				Sub(const Liar::Matrix2&);
		void				Mul(const Liar::Matrix2&);
		void				Mul(Liar::Vector2D&);
		void				Mul(const Liar::Vector2D&, Liar::Vector2D&);
		void				Mul(float v);

	public:
		float			   GetDeterminant() const;
		float			   GetAngle() const;                       // retrieve angle (degree) from matrix

		Liar::Matrix2&	   Identity();
		Liar::Matrix2&	   Transpose();
		Liar::Matrix2&	   Invert();

		// operators
		Liar::Matrix2     operator+(const Liar::Matrix2& rhs) const;    // add rhs
		Liar::Matrix2     operator-(const Liar::Matrix2& rhs) const;    // subtract rhs
		Liar::Matrix2&    operator+=(const Liar::Matrix2& rhs);         // add rhs and update this object
		Liar::Matrix2&    operator-=(const Liar::Matrix2& rhs);         // subtract rhs and update this object
		Liar::Vector2D    operator*(const Liar::Vector2D& rhs) const;    // multiplication: v' = M * v
		Liar::Matrix2     operator*(const Liar::Matrix2& rhs) const;    // multiplication: M3 = M1 * M2
		Liar::Matrix2&    operator*=(const Liar::Matrix2& rhs);         // multiplication: M1' = M1 * M2
		bool        operator==(const Liar::Matrix2& rhs) const;   // exact compare, no epsilon
		bool        operator!=(const Liar::Matrix2& rhs) const;   // exact compare, no epsilon

															// friends functions
		friend Liar::Matrix2 operator-(const Liar::Matrix2& m);                     // unary operator (-)
		friend Liar::Matrix2 operator*(float scalar, const Liar::Matrix2& m);       // pre-multiplication
		friend Liar::Vector2D operator*(const Liar::Vector2D& vec, const Matrix2& m); // pre-multiplication
		friend std::ostream& operator<<(std::ostream& os, const Liar::Matrix2& m);

	private:
		void SetRowElement(int index, float v1, float v2);
		void SetColElement(int, float, float);


	public:
		float m0, m2;
		float m1, m3;
	};

	///////////////////////////////////////////////////////////////////////////
	// 3x3 matrix
	///////////////////////////////////////////////////////////////////////////
	class Matrix3
	{
	public:
		Matrix3();
		Matrix3(const float src[9]);
		Matrix3(const std::vector<float>&);
		Matrix3(float m0, float m1, float m2,           // 1st column
				float m3, float m4, float m5,           // 2nd column
				float m6, float m7, float m8);          // 3rd column

	public:
		void				Set(const float src[9]);
		void				Set(const std::vector<float>&);
		void				Set(float m0, float m1, float m2,   // 1st column
								float m3, float m4, float m5,   // 2nd column
								float m6, float m7, float m8);  // 3rd column

		void				SetRow(int, const float src[3]);
		void				SetRow(int, const std::vector<float>&);
		void				SetRow(int, const Liar::Vector3D&);

		void				SetCol(int, const float src[3]);
		void				SetCol(int, const std::vector<float>&);
		void				SetCol(int, const Liar::Vector3D&);

		void				GetRawData(std::vector<float>&);

	public:
		void				Add(const Liar::Matrix3&);
		void				Sub(const Liar::Matrix3&);
		void				Mul(const Liar::Matrix3&);
		void				Mul(Liar::Vector3D&);
		void				Mul(const Liar::Vector3D&, Liar::Vector3D&);
		void				Mul(float v);

	public:
		float				GetDeterminant() const;
		Liar::Vector3D		GetAngle() const;
		void				GetAngle(Liar::Vector3D&) const;

		Liar::Matrix3&	   Identity();
		Liar::Matrix3&	   Transpose();
		Liar::Matrix3&	   Invert();

		// operators
		Liar::Matrix3     operator+(const Liar::Matrix3& rhs) const;    // add rhs
		Liar::Matrix3     operator-(const Liar::Matrix3& rhs) const;    // subtract rhs
		Liar::Matrix3&    operator+=(const Liar::Matrix3& rhs);         // add rhs and update this object
		Liar::Matrix3&    operator-=(const Liar::Matrix3& rhs);         // subtract rhs and update this object
		Liar::Vector3D     operator*(const Liar::Vector3D& rhs) const;    // multiplication: v' = M * v
		Liar::Matrix3     operator*(const Liar::Matrix3& rhs) const;    // multiplication: M3 = M1 * M2
		Liar::Matrix3&    operator*=(const Liar::Matrix3& rhs);         // multiplication: M1' = M1 * M2
		bool        operator==(const Liar::Matrix3& rhs) const;   // exact compare, no epsilon
		bool        operator!=(const Liar::Matrix3& rhs) const;   // exact compare, no epsilon

															// friends functions
		friend Liar::Matrix3 operator-(const Liar::Matrix3& m);                     // unary operator (-)
		friend Liar::Matrix3 operator*(float scalar, const Liar::Matrix3& m);       // pre-multiplication
		friend Liar::Vector3D operator*(const Liar::Vector3D& vec, const Liar::Matrix3& m); // pre-multiplication
		friend std::ostream& operator<<(std::ostream& os, const Liar::Matrix3& m);

	private:
		void SetRowElement(int, float, float, float);
		void SetColElement(int, float, float, float);

	public:
		float m0, m3, m6;
		float m1, m4, m7;
		float m2, m5, m8;
	};


	///////////////////////////////////////////////////////////////////////////
	// 4x4 matrix
	///////////////////////////////////////////////////////////////////////////
	class Matrix4
	{
		Matrix4();  // init with identity
		Matrix4(const float src[16]);
		Matrix4(const std::vector<float>&);
		Matrix4(float m00, float m01, float m02, float m03, // 1st column
				float m04, float m05, float m06, float m07, // 2nd column
				float m08, float m09, float m10, float m11, // 3rd column
				float m12, float m13, float m14, float m15);// 4th column

	public:
		void					Set(const float src[16]);
		void					Set(const std::vector<float>&);
		void					Set(float m00, float m01, float m02, float m03, // 1st column
									float m04, float m05, float m06, float m07, // 2nd column
									float m08, float m09, float m10, float m11, // 3rd column
									float m12, float m13, float m14, float m15);// 4th column

		void					SetRow(int, const float row[4]);
		void					SetRow(int, const std::vector<float>&);
		void					SetRow(int, const Liar::Vector4D&);
		void					SetRow(int, const Liar::Vector3D&);

		void					SetCol(int, const float row[4]);
		void					SetCol(int, const std::vector<float>&);
		void					SetCol(int, const Liar::Vector4D&);
		void					SetCol(int, const Liar::Vector3D&);

		void					GetRawData(std::vector<float>&);

	public:
		void					GetTranspose(std::vector<float>&);
		float					GetDeterminant() const;
		Liar::Matrix3			GetRotationMatrix() const;
		void					GetRotationMatrix(Liar::Matrix3&) const;
		Liar::Vector3D			GetAngle() const;
		void					GetAngle(Liar::Vector3D&) const;
		void					GetAngle(float&, float&, float&) const;

	public:
		Liar::Matrix4&    Identity();
		Liar::Matrix4&    Transpose();                            // transpose itself and return reference
		Liar::Matrix4&    Invert();                               // check best inverse method before inverse
		Liar::Matrix4&    InvertEuclidean();                      // inverse of Euclidean transform matrix
		Liar::Matrix4&    InvertAffine();                         // inverse of affine transform matrix
		Liar::Matrix4&    InvertProjective();                     // inverse of projective matrix using partitioning
		Liar::Matrix4&    InvertGeneral();                        // inverse of generic matrix

															// transform matrix
		Liar::Matrix4&    Translate(float x, float y, float z);   // translation by (x,y,z)
		Liar::Matrix4&    Translate(const Liar::Vector3D& v);            //
		Liar::Matrix4&    Rotate(float angle, const Liar::Vector3D& axis); // rotate angle(degree) along the given axix
		Liar::Matrix4&    Rotate(float angle, float x, float y, float z);
		Liar::Matrix4&    RotateX(float angle);                   // rotate on X-axis with degree
		Liar::Matrix4&    RotateY(float angle);                   // rotate on Y-axis with degree
		Liar::Matrix4&    RotateZ(float angle);                   // rotate on Z-axis with degree
		Liar::Matrix4&    Scale(float scale);                     // uniform scale
		Liar::Matrix4&    Scale(float sx, float sy, float sz);    // scale by (sx, sy, sz) on each axis
		Liar::Matrix4&    LookAt(float tx, float ty, float tz);   // face object to the target direction
		Liar::Matrix4&    LookAt(float tx, float ty, float tz, float ux, float uy, float uz);
		Liar::Matrix4&    LookAt(const Liar::Vector3D& target);
		Liar::Matrix4&    LookAt(const Liar::Vector3D& target, const Liar::Vector3D& up);
		//@@Matrix4&    skew(float angle, const Vector3& axis); //

		// operators
		Liar::Matrix4     operator+(const Liar::Matrix4& rhs) const;    // add rhs
		Liar::Matrix4     operator-(const Liar::Matrix4& rhs) const;    // subtract rhs
		Liar::Matrix4&    operator+=(const Liar::Matrix4& rhs);         // add rhs and update this object
		Liar::Matrix4&    operator-=(const Liar::Matrix4& rhs);         // subtract rhs and update this object
		Liar::Vector4D     operator*(const Liar::Vector4D& rhs) const;    // multiplication: v' = M * v
		Liar::Vector3D     operator*(const Liar::Vector3D& rhs) const;    // multiplication: v' = M * v
		Liar::Matrix4     operator*(const Liar::Matrix4& rhs) const;    // multiplication: M3 = M1 * M2
		Liar::Matrix4&    operator*=(const Liar::Matrix4& rhs);         // multiplication: M1' = M1 * M2
		bool        operator==(const Liar::Matrix4& rhs) const;   // exact compare, no epsilon
		bool        operator!=(const Liar::Matrix4& rhs) const;   // exact compare, no epsilon

															// friends functions
		friend Liar::Matrix4 operator-(const Liar::Matrix4& m);                     // unary operator (-)
		friend Liar::Matrix4 operator*(float scalar, const Matrix4& m);       // pre-multiplication
		friend Liar::Vector3D operator*(const Liar::Vector3D& vec, const Liar::Matrix4& m); // pre-multiplication
		friend Liar::Vector4D operator*(const Liar::Vector4D& vec, const Liar::Matrix4& m); // pre-multiplication
		friend std::ostream& operator<<(std::ostream& os, const Liar::Matrix4& m);

	private:
		void SetRowElement(int, float, float, float, float);
		void SetColElement(int, float, float, float, float);
		float       GetCofactor(float m0, float m1, float m2,
					float m3, float m4, float m5,
					float m6, float m7, float m8) const;

	public:
		float m0, m4, m8,	m12;
		float m1, m5, m9,	m13;
		float m2, m6, m10,	m14;
		float m3, m7, m11,  m15;
	};


	///////////////////////////////////////////////////////////////////////////
	// inline functions for Matrix2
	///////////////////////////////////////////////////////////////////////////
	inline Matrix2::Matrix2()
	{
		// initially identity matrix
		Identity();
	}

	inline Matrix2::Matrix2(const float src[4])
	{
		Set(src);
	}

	inline Matrix2::Matrix2(const std::vector<float>& src)
	{
		Set(src);
	}

	inline Matrix2::Matrix2(float m0, float m1, float m2, float m3)
	{
		Set(m0, m1, m2, m3);
	}

	inline void Matrix2::Set(const float src[4])
	{
		m0 = src[0];  m1 = src[1];  m2 = src[2];  m3 = src[3];
	}

	inline void Matrix2::Set(const std::vector<float>& src)
	{
		m0 = src[0];  m1 = src[1];  m2 = src[2];  m3 = src[3];
	}

	inline void Matrix2::Set(float vm0, float vm1, float vm2, float vm3)
	{
		m0 = vm0;  m1 = vm1;  m2 = vm2;  m3 = vm3;
	}

	inline Matrix2& Matrix2::Identity()
	{
		m0 = m3 = 1.0f;
		m1 = m2 = 0.0f;
		return *this;
	}

	inline Matrix2 Matrix2::operator+(const Matrix2& rhs) const
	{
		return Matrix2(m0 + rhs.m0, m1 + rhs.m1, m2 + rhs.m2, m3 + rhs.m3);
	}

	inline Matrix2 Matrix2::operator-(const Matrix2& rhs) const
	{
		return Matrix2(m0 - rhs.m0, m1 - rhs.m1, m2 - rhs.m2, m3 - rhs.m3);
	}

	inline Matrix2& Matrix2::operator+=(const Matrix2& rhs)
	{
		m0 + rhs.m0, m1 + rhs.m1, m2 + rhs.m2, m3 + rhs.m3;
		return *this;
	}

	inline Matrix2& Matrix2::operator-=(const Matrix2& rhs)
	{
		m0 - rhs.m0, m1 - rhs.m1, m2 - rhs.m2, m3 - rhs.m3;
		return *this;
	}

	inline Vector2D Matrix2::operator*(const Liar::Vector2D& rhs) const
	{
		return Liar::Vector2D(m0 * rhs.x + m2 * rhs.y, m1 * rhs.x + m3 * rhs.y);
	}

	inline Matrix2 Matrix2::operator*(const Liar::Matrix2& rhs) const
	{
		return Liar::Matrix2(m0 * rhs.m0 + m2 * rhs.m1, m1 * rhs.m0 + m3 * rhs.m1,
							 m0 * rhs.m2 + m2 * rhs.m3, m1 * rhs.m2 + m3 * rhs.m3);
	}

	inline Matrix2& Matrix2::operator*=(const Matrix2& rhs)
	{
		float t0 = m0, t1 = m1, t2 = m2, t3 = m3;
		m0 = t0 * rhs.m0 + t2 * rhs.m1;
		m1 = t1 * rhs.m0 + t3 * rhs.m1;
		m2 = t0 * rhs.m2 + t2 * rhs.m3;
		m3 = t1 * rhs.m2 + t3 * rhs.m3;
		return *this;
	}

	inline bool Matrix2::operator==(const Matrix2& rhs) const
	{
		return m0 == rhs.m0 && m1 == rhs.m1 && m2 == rhs.m2 && m3 == rhs.m3;
	}

	inline bool Matrix2::operator!=(const Matrix2& rhs) const
	{
		return m0 != rhs.m0 || m1 != rhs.m1 || m2 != rhs.m2 || m3 != rhs.m3;
	}

	inline Matrix2 operator-(const Matrix2& rhs)
	{
		return Liar::Matrix2(-rhs.m0, -rhs.m1, -rhs.m2, -rhs.m3);
	}

	inline Matrix2 operator*(float s, const Matrix2& rhs)
	{
		return Matrix2(s*rhs.m0, s*rhs.m1, s*rhs.m2, s*rhs.m3);
	}

	inline Liar::Vector2D operator*(const Liar::Vector2D& v, const Matrix2& rhs)
	{
		return Liar::Vector2D(v.x*rhs.m0 + v.y*rhs.m1, v.x*rhs.m2 + v.y*rhs.m3);
	}

	inline std::ostream& operator<<(std::ostream& os, const Matrix2& m)
	{
		os << std::fixed << std::setprecision(5);
		os << "[" << std::setw(10) << m.m0 << " " << std::setw(10) << m.m2 << "]\n"
			<< "[" << std::setw(10) << m.m1 << " " << std::setw(10) << m.m3 << "]\n";
		os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
		return os;
	}
	// END OF MATRIX2 INLINE //////////////////////////////////////////////////////




	///////////////////////////////////////////////////////////////////////////
	// inline functions for Matrix3
	///////////////////////////////////////////////////////////////////////////
	inline Matrix3::Matrix3()
	{
		// initially identity matrix
		Identity();
	}

	inline Matrix3::Matrix3(const float src[9])
	{
		Set(src);
	}

	inline Matrix3::Matrix3(const std::vector<float>& src)
	{
		Set(src);
	}

	inline Matrix3::Matrix3(float m0, float m1, float m2,
							float m3, float m4, float m5,
							float m6, float m7, float m8)
	{
		Set(m0, m1, m2, m3, m4, m5, m6, m7, m8);
	}



	inline void Matrix3::Set(const float src[9])
	{
		m0 = src[0];  m1 = src[1];  m1 = src[2];
		m3 = src[3];  m4 = src[4];  m5 = src[5];
		m6 = src[6];  m7 = src[7];  m8 = src[8];
	}

	inline void Matrix3::Set(const std::vector<float>& src)
	{
		m0 = src[0];  m1 = src[1];  m1 = src[2];
		m3 = src[3];  m4 = src[4];  m5 = src[5];
		m6 = src[6];  m7 = src[7];  m8 = src[8];
	}

	inline void Matrix3::Set(float mv0, float mv1, float mv2,
								float mv3, float mv4, float mv5,
								float mv6, float mv7, float mv8)
	{
		m0 = mv0;  m1 = mv1;  m2 = mv2;
		m3 = mv3;  m4 = mv4;  m5 = mv5;
		m6 = mv6;  m7 = mv7;  m8 = mv8;
	}

	inline Matrix3& Matrix3::Identity()
	{
		m0 = m4 = m8 = 1.0f;
		m1 = m2 = m3 = m5 = m6 = m7 = 0.0f;
		return *this;
	}

	inline Matrix3 Matrix3::operator+(const Matrix3& rhs) const
	{
		return Matrix3( m0 + rhs.m0, m1 + rhs.m1, m2 + rhs.m2,
						m3 + rhs.m1, m4 + rhs.m4, m5 + rhs.m5,
						m6 + rhs.m6, m7 + rhs.m7, m8 + rhs.m8);
	}

	inline Matrix3 Matrix3::operator-(const Matrix3& rhs) const
	{
		return Matrix3( m0 - rhs.m0, m1 - rhs.m1, m2 - rhs.m2,
						m3 - rhs.m1, m4 - rhs.m4, m5 - rhs.m5,
						m6 - rhs.m6, m7 - rhs.m7, m8 - rhs.m8);
	}

	inline Matrix3& Matrix3::operator+=(const Matrix3& rhs)
	{
		m0 += rhs.m0; m1 += rhs.m1; m2 += rhs.m2;
		m3 += rhs.m1; m4 += rhs.m4; m5 += rhs.m5;
		m6 += rhs.m6; m7 += rhs.m7; m8 += rhs.m8;
		return *this;
	}

	inline Matrix3& Matrix3::operator-=(const Matrix3& rhs)
	{
		m0 -= rhs.m0; m1 -= rhs.m1; m2 -= rhs.m2;
		m3 -= rhs.m1; m4 -= rhs.m4; m5 -= rhs.m5;
		m6 -= rhs.m6; m7 -= rhs.m7; m8 -= rhs.m8;
		return *this;
	}

	inline Vector3D Matrix3::operator*(const Vector3D& rhs) const
	{
		return Vector3D(m0 * rhs.x + m3 * rhs.y + m6 * rhs.z,
						m1 * rhs.x + m4 * rhs.y + m7 * rhs.z,
						m2 * rhs.x + m5 * rhs.y + m8 * rhs.z);
	}

	inline Matrix3 Matrix3::operator*(const Matrix3& rhs) const
	{
		return Matrix3( m0 * rhs.m0 + m3 * rhs.m1 + m6 * rhs.m2,	m1 * rhs.m0 + m4 * rhs.m1 + m7 * rhs.m2,	m2 * rhs.m0 + m5 * rhs.m1 + m8 * rhs.m2,
						m0 * rhs.m3 + m3 * rhs.m4 + m6 * rhs.m5,	m1 * rhs.m3 + m4 * rhs.m4 + m7 * rhs.m5,	m2 * rhs.m3 + m5 * rhs.m4 + m8 * rhs.m5,
						m0 * rhs.m6 + m3 * rhs.m7 + m6 * rhs.m8,	m1 * rhs.m6 + m4 * rhs.m7 + m7 * rhs.m8,	m2 * rhs.m6 + m5 * rhs.m7 + m8 * rhs.m8);
	}

	inline Matrix3& Matrix3::operator*=(const Matrix3& rhs)
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
		return *this;
	}

	inline bool Matrix3::operator==(const Matrix3& rhs) const
	{
		return ( m0 == rhs.m0) && (m1 == rhs.m1) && (m2 == rhs.m2) &&
				(m3 == rhs.m3) && (m4 == rhs.m4) && (m5 == rhs.m5) &&
				(m6 == rhs.m6) && (m7 == rhs.m7) && (m8 == rhs.m8);
	}

	inline bool Matrix3::operator!=(const Matrix3& rhs) const
	{
		return ( m0 != rhs.m0) || (m1 != rhs.m1) || (m2 != rhs.m2) ||
				(m3 != rhs.m3) || (m4 != rhs.m4) || (m5 != rhs.m5) ||
				(m6 != rhs.m6) || (m7 != rhs.m7) || (m8 != rhs.m8);
	}

	inline Matrix3 operator-(const Matrix3& rhs)
	{
		return Matrix3(-rhs.m0, -rhs.m1, -rhs.m2, -rhs.m3, -rhs.m4, -rhs.m5, -rhs.m6, -rhs.m7, -rhs.m8);
	}

	inline Matrix3 operator*(float s, const Matrix3& rhs)
	{
		return Matrix3(s*rhs.m0, s*rhs.m1, s*rhs.m2, s*rhs.m3, s*rhs.m4, s*rhs.m5, s*rhs.m6, s*rhs.m7, s*rhs.m8);
	}

	inline Vector3D operator*(const Vector3D& v, const Matrix3& rhs)
	{
		return Vector3D(v.x*rhs.m0 + v.y*rhs.m1 + v.z*rhs.m2,
						v.x*rhs.m3 + v.y*rhs.m4 + v.z*rhs.m5,
						v.x*rhs.m6 + v.y*rhs.m7 + v.z*rhs.m8);
	}

	inline std::ostream& operator<<(std::ostream& os, const Matrix3& m)
	{
		os << std::fixed << std::setprecision(5);
		os << "[" << std::setw(10) << m.m0 << " " << std::setw(10) << m.m3 << " " << std::setw(10) << m.m6 << "]\n"
			<< "[" << std::setw(10) << m.m1 << " " << std::setw(10) << m.m4 << " " << std::setw(10) << m.m7 << "]\n"
			<< "[" << std::setw(10) << m.m2 << " " << std::setw(10) << m.m5 << " " << std::setw(10) << m.m8 << "]\n";
		os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
		return os;
	}
	// END OF MATRIX3 INLINE //////////////////////////////////////////////////////




	///////////////////////////////////////////////////////////////////////////
	// inline functions for Matrix4
	///////////////////////////////////////////////////////////////////////////
	inline Matrix4::Matrix4()
	{
		// initially identity matrix
		Identity();
	}

	inline Matrix4::Matrix4(const float src[16])
	{
		Set(src);
	}

	inline Matrix4::Matrix4(const std::vector<float>& src)
	{
		Set(src);
	}

	inline Matrix4::Matrix4(float m00, float m01, float m02, float m03,
							float m04, float m05, float m06, float m07,
							float m08, float m09, float m10, float m11,
							float m12, float m13, float m14, float m15)
	{
		Set(m00, m01, m02, m03, m04, m05, m06, m07, m08, m09, m10, m11, m12, m13, m14, m15);
	}

	inline void Matrix4::Set(const float src[16])
	{
		m0 = src[0];  m1 = src[1];  m2 = src[2];  m3 = src[3];
		m4 = src[4];  m5 = src[5];  m6 = src[6];  m7 = src[7];
		m8 = src[8];  m9 = src[9];  m10 = src[10]; m11 = src[11];
		m12 = src[12]; m13 = src[13]; m14 = src[14]; m15 = src[15];
	}

	inline void Matrix4::Set(const std::vector<float>& src)
	{
		m0 = src[0];  m1 = src[1];  m2 = src[2];  m3 = src[3];
		m4 = src[4];  m5 = src[5];  m6 = src[6];  m7 = src[7];
		m8 = src[8];  m9 = src[9];  m10 = src[10]; m11 = src[11];
		m12 = src[12]; m13 = src[13]; m14 = src[14]; m15 = src[15];
	}

	inline void Matrix4::Set(float m00, float m01, float m02, float m03,
		float m04, float m05, float m06, float m07,
		float m08, float m09, float mv10, float mv11,
		float mv12, float mv13, float mv14, float mv15)
	{
		m0 = m00;  m1 = m01;  m2 = m02;  m3 = m03;
		m4 = m04;  m5 = m05;  m6 = m06;  m7 = m07;
		m8 = m08;  m9 = m09;  m10 = mv10;  m11 = mv11;
		m12 = mv12;  m13 = mv13;  m14 = mv14;  m15 = mv15;
	}

	inline void Matrix4::GetTranspose(std::vector<float>& out)
	{
		out = { m0, m4, m8, m12, m1, m5, m9, m13, m2, m6, m10, m14, m3, m7, m11, m15 };
	}

	inline Matrix4& Matrix4::Identity()
	{
		m0 = m5 = m10 = m15 = 1.0f;
		m1 = m2 = m3 = m4 = m6 = m7 = m8 = m9 = m11 = m12 = m13 = m14 = 0.0f;
		return *this;
	}

	inline Matrix4 Matrix4::operator+(const Matrix4& rhs) const
	{
		return Matrix4( m0 + rhs.m0,	m1 + rhs.m1,	m2 + rhs.m2,	m3 + rhs.m3,
						m4 + rhs.m4,	m5 + rhs.m5,	m6 + rhs.m6,	m7 + rhs.m7,
						m8 + rhs.m8,	m9 + rhs.m9,	m10 + rhs.m10,	m11 + rhs.m11,
						m12 + rhs.m12,  m13 + rhs.m13,  m14 + rhs.m14,  m15 + rhs.m15);
	}



	inline Matrix4 Matrix4::operator-(const Matrix4& rhs) const
	{
		return Matrix4( m0 - rhs.m0, m1 - rhs.m1, m2 - rhs.m2, m3 - rhs.m3,
						m4 - rhs.m4, m5 - rhs.m5, m6 - rhs.m6, m7 - rhs.m7,
						m8 - rhs.m8, m9 - rhs.m9, m10 - rhs.m10, m11 - rhs.m11,
						m12 - rhs.m12, m13 - rhs.m13, m14 - rhs.m14, m15 - rhs.m15);
	}



	inline Matrix4& Matrix4::operator+=(const Matrix4& rhs)
	{
		m0 += rhs.m0; m1 += rhs.m1; m2 += rhs.m2; m3 += rhs.m3;
		m4 += rhs.m4; m5 += rhs.m5; m6 += rhs.m6; m7 += rhs.m7;
		m8 += rhs.m8; m9 += rhs.m9; m10 += rhs.m10; m11 += rhs.m11;
		m12 += rhs.m12; m13 += rhs.m13; m14 += rhs.m14; m15 += rhs.m15;
		return *this;
	}

	inline Matrix4& Matrix4::operator-=(const Matrix4& rhs)
	{
		m0 -= rhs.m0; m1 -= rhs.m1; m2 -= rhs.m2; m3 -= rhs.m3;
		m4 -= rhs.m4; m5 -= rhs.m5; m6 -= rhs.m6; m7 -= rhs.m7;
		m8 -= rhs.m8; m9 -= rhs.m9; m10 -= rhs.m10; m11 -= rhs.m11;
		m12 -= rhs.m12; m13 -= rhs.m13; m14 -= rhs.m14; m15 -= rhs.m15;
		return *this;
	}

	inline Vector4D Matrix4::operator*(const Vector4D& rhs) const
	{
		return Vector4D(m0 * rhs.x + m4 * rhs.y + m8 * rhs.z + m12 * rhs.w,
						m1 * rhs.x + m5 * rhs.y + m9 * rhs.z + m13 * rhs.w,
						m2 * rhs.x + m6 * rhs.y + m10 * rhs.z + m14 * rhs.w,
						m3 * rhs.x + m7 * rhs.y + m11 * rhs.z + m15 * rhs.w);
	}

	inline Vector3D Matrix4::operator*(const Vector3D& rhs) const
	{
		return Vector3D(m0 * rhs.x + m4 * rhs.y + m8 * rhs.z + m12,
						m1 * rhs.x + m5 * rhs.y + m9 * rhs.z + m13,
						m2 * rhs.x + m6 * rhs.y + m10 * rhs.z + m14);
	}

	inline Matrix4 Matrix4::operator*(const Matrix4& n) const
	{
		return Matrix4(	m0 * n.m0  + m4 * n.m1  + m8 * n.m2  + m12 * n.m3,  m1 * n.m0  + m5 * n.m1  + m9 * n.m2  + m13 * n.m3,  m2 * n.m0  + m6 * n.m1  + m10 * n.m2  + m14 * n.m3,  m3 * n.m0  + m7 * n.m1  + m11 * n.m2  + m15 * n.m3,
						m0 * n.m4  + m4 * n.m5  + m8 * n.m6  + m12 * n.m7,  m1 * n.m4  + m5 * n.m5  + m9 * n.m6  + m13 * n.m7,  m2 * n.m4  + m6 * n.m5  + m10 * n.m6  + m14 * n.m7,  m3 * n.m4  + m7 * n.m5  + m11 * n.m6  + m15 * n.m7,
						m0 * n.m8  + m4 * n.m9  + m8 * n.m10 + m12 * n.m11, m1 * n.m8  + m5 * n.m9  + m9 * n.m10 + m13 * n.m11, m2 * n.m8  + m6 * n.m9  + m10 * n.m10 + m14 * n.m11, m3 * n.m8  + m7 * n.m9  + m11 * n.m10 + m15 * n.m11,
						m0 * n.m12 + m4 * n.m13 + m8 * n.m14 + m12 * n.m15, m1 * n.m12 + m5 * n.m13 + m9 * n.m14 + m13 * n.m15, m2 * n.m12 + m6 * n.m13 + m10 * n.m14 + m14 * n.m15, m3 * n.m12 + m7 * n.m13 + m11 * n.m14 + m15 * n.m15);
	}

	inline Matrix4& Matrix4::operator*=(const Matrix4& n)
	{
		float t0 = m0, t1 = m1, t2 = m2, t3 = m3, t4 = m4, t5 = m5, t6 = m6, t7 = m7, t8 = m8, t9 = m9, t10 = m10, t11 = m11, t12 = m12, t13 = m13, t14 = m14, t15 = m15;
		m0 = t0 * n.m0 + t4 * n.m1 + t8 * n.m2 + t12 * n.m3;
		m1 = t1 * n.m0 + t5 * n.m1 + t9 * n.m2 + t13 * n.m3;
		m2 = t2 * n.m0 + t6 * n.m1 + t10 * n.m2 + t14 * n.m3;
		m3 = t3 * n.m0 + t7 * n.m1 + t11 * n.m2 + t15 * n.m3;
		m4 = t0 * n.m4 + t4 * n.m5 + t8 * n.m6 + t12 * n.m7;
		m5 = t1 * n.m4 + t5 * n.m5 + t9 * n.m6 + t13 * n.m7;
		m6 = t2 * n.m4 + t6 * n.m5 + t10 * n.m6 + t14 * n.m7;
		m7 = t3 * n.m4 + t7 * n.m5 + t11 * n.m6 + t15 * n.m7;
		m8 = t0 * n.m8 + t4 * n.m9 + t8 * n.m10 + t12 * n.m11;
		m9 = t1 * n.m8 + t5 * n.m9 + t9 * n.m10 + t13 * n.m11;
		m10 = t2 * n.m8 + t6 * n.m9 + t10 * n.m10 + t14 * n.m11;
		m11 = t3 * n.m8 + t7 * n.m9 + t11 * n.m10 + t15 * n.m11;
		m12 = t0 * n.m12 + t4 * n.m13 + t8 * n.m14 + t12 * n.m15;
		m13 = t1 * n.m12 + t5 * n.m13 + t9 * n.m14 + t13 * n.m15;
		m14 = t2 * n.m12 + t6 * n.m13 + t10 * n.m14 + t14 * n.m15;
		m15 = t3 * n.m12 + t7 * n.m13 + t11 * n.m14 + t15 * n.m15;
		return *this;
	}

	inline bool Matrix4::operator==(const Matrix4& n) const
	{
		return ( m0 == n.m0) && (m1 == n.m1) && (m2 == n.m2) && (m3 == n.m3) &&
				(m4 == n.m4) && (m5 == n.m5) && (m6 == n.m6) && (m7 == n.m7) &&
				(m8 == n.m8) && (m9 == n.m9) && (m10 == n.m10) && (m11 == n.m11) &&
				(m12 == n.m12) && (m13 == n.m13) && (m14 == n.m14) && (m15 == n.m15);
	}

	inline bool Matrix4::operator!=(const Matrix4& n) const
	{
		return (m0 != n.m0) || (m1 != n.m1) || (m2 != n.m2) || (m3 != n.m3) ||
				(m4 != n.m4) || (m5 != n.m5) || (m6 != n.m6) || (m7 != n.m7) ||
				(m8 != n.m8) || (m9 != n.m9) || (m10 != n.m10) || (m11 != n.m11) ||
				(m12 != n.m12) || (m13 != n.m13) || (m14 != n.m14) || (m15 != n.m15);
	}

	inline Matrix4 operator-(const Matrix4& rhs)
	{
		return Matrix4(-rhs.m0, -rhs.m1, -rhs.m2, -rhs.m3, -rhs.m4, -rhs.m5, -rhs.m6, -rhs.m7, -rhs.m8, -rhs.m9, -rhs.m10, -rhs.m11, -rhs.m12, -rhs.m13, -rhs.m14, -rhs.m15);
	}

	inline Matrix4 operator*(float s, const Matrix4& rhs)
	{
		return Matrix4(s*rhs.m0, s*rhs.m1, s*rhs.m2, s*rhs.m3, s*rhs.m4, s*rhs.m5, s*rhs.m6, s*rhs.m7, s*rhs.m8, s*rhs.m9, s*rhs.m10, s*rhs.m11, s*rhs.m12, s*rhs.m13, s*rhs.m14, s*rhs.m15);
	}

	inline Vector4D operator*(const Vector4D& v, const Matrix4& m)
	{
		return Vector4D(v.x*m.m0 + v.y*m.m1 + v.z*m.m2 + v.w*m.m3, v.x*m.m4 + v.y*m.m5 + v.z*m.m6 + v.w*m.m7, v.x*m.m8 + v.y*m.m9 + v.z*m.m10 + v.w*m.m11, v.x*m.m12 + v.y*m.m13 + v.z*m.m14 + v.w*m.m15);
	}

	inline Vector3D operator*(const Vector3D& v, const Matrix4& m)
	{
		return Vector3D(v.x*m.m0 + v.y*m.m1 + v.z*m.m2, v.x*m.m4 + v.y*m.m5 + v.z*m.m6, v.x*m.m8 + v.y*m.m9 + v.z*m.m10);
	}

	inline std::ostream& operator<<(std::ostream& os, const Matrix4& m)
	{
		os << std::fixed << std::setprecision(5);
		os << "[" << std::setw(10) << m.m0 << " " << std::setw(10) << m.m4 << " " << std::setw(10) << m.m8 << " " << std::setw(10) << m.m12 << "]\n"
			<< "[" << std::setw(10) << m.m1 << " " << std::setw(10) << m.m5 << " " << std::setw(10) << m.m9 << " " << std::setw(10) << m.m13 << "]\n"
			<< "[" << std::setw(10) << m.m2 << " " << std::setw(10) << m.m6 << " " << std::setw(10) << m.m10 << " " << std::setw(10) << m.m14 << "]\n"
			<< "[" << std::setw(10) << m.m3 << " " << std::setw(10) << m.m7 << " " << std::setw(10) << m.m11 << " " << std::setw(10) << m.m15 << "]\n";
		os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
		return os;
	}

}

