#pragma once

namespace simd_style_helper
{
	//
	// This class is needed because the caller specifies the output type 
	// (and the amount of data to load from memory) upon assigning it to
	// the destination variable.
	//
	// It is not needed for Store(), because the data type is passed in 
	// as one of the arguments, together with the address and offset.
	//
	class LoadHelper
	{
	public:
		LoadHelper(const void* ptr)
			: m_ptr(ptr)
		{
			// TODO debug assert not null
		}

		LoadHelper operator+ (size_t byteOffset) const
		{
			// The cast is only used for offsetting, not for 
			// actual reading from memory, therefore no violation of 
			// strict aliasing.
			return LoadHelper((const uint8_t*)m_ptr + byteOffset);
		}

		operator V128I () const
		{
			return V128I
			{
				_mm_loadu_si128((const __m128i*)m_ptr)
			};
		}

		operator V128F () const
		{
			return V128F
			{
				_mm_loadu_ps((const float*)m_ptr)
			};
		}

		operator V128D () const
		{
			return V128D
			{
				_mm_loadu_pd((const double*)m_ptr)
			};
		}

		operator U8x16 () const
		{
			return U8x16
			{
				this->operator V128I()
			};
		}

		operator I8x16 () const
		{
			return I8x16
			{
				this->operator V128I()
			};
		}

		operator U16x8 () const
		{
			return U16x8
			{
				this->operator V128I()
			};
		}

		operator I16x8 () const
		{
			return I16x8
			{
				this->operator V128I()
			};
		}

		operator U16x16 () const
		{
			return U16x16
			{
				this->operator V128I(),
				(this->operator+(16u)).operator V128I()
			};
		}

		operator I16x16 () const
		{
			return I16x16
			{
				this->operator V128I(),
				(this->operator+(16u)).operator V128I()
			};
		}

		operator U32x4 () const
		{
			return U32x4
			{
				this->operator V128I()
			};
		}

		operator I32x4 () const
		{
			return I32x4
			{
				this->operator V128I()
			};
		}

		operator U32x16 () const
		{
			return U32x16
			{
				this->operator V128I(),
				(this->operator+(16u)).operator V128I(),
				(this->operator+(32u)).operator V128I(),
				(this->operator+(48u)).operator V128I()
			};
		}

		operator I32x16 () const
		{
			return I32x16
			{
				this->operator V128I(),
				(this->operator+(16u)).operator V128I(),
				(this->operator+(32u)).operator V128I(),
				(this->operator+(48u)).operator V128I()
			};
		}

		operator F32x4 () const
		{
			return F32x4
			{
				this->operator V128F()
			};
		}

		operator F32x16 () const
		{
			return F32x16
			{
				this->operator V128F(),
				(this->operator+(16u)).operator V128F(),
				(this->operator+(32u)).operator V128F(),
				(this->operator+(48u)).operator V128F(),
			};
		}

	public:
		void const * m_ptr;
	};

	template <typename ReturnType>
	ReturnType Load(const void* ptr)
	{
		return LoadHelper(ptr).operator ReturnType();
	}

	template <typename ReturnType>
	ReturnType Load(const void* ptr, size_t byteOffset)
	{
		return (LoadHelper(ptr) + byteOffset).operator ReturnType();
	}

	//
	// The following multi-V128 stores are hand-unrolled
	// to make sure they are actually unrolled after compilation.
	//
	// The hand-unrolled overloads only support powers-of-two.
	//
	// For compilers that support forced unrolling directive,
	// replace the following overloads with a template
	// on the size of the array (i.e. number of V128 vectors)
	//

	inline void Store(void* ptr, const V128I& v128i)
	{
		_mm_storeu_si128((__m128i*)ptr, v128i);
	}

	inline void Store(void* ptr, const V128F& v128f)
	{
		_mm_storeu_ps((float*)ptr, v128f);
	}

	inline void Store(void* ptr, const V128D& v128d)
	{
		_mm_storeu_pd((double*)ptr, v128d);
	}

	inline void Store(void* ptr, const V128I(&v128i)[1u])
	{
		_mm_storeu_si128((__m128i*)ptr, v128i[0u]);
	}

	inline void Store(void* ptr, const V128I(&v128i)[2u])
	{
		uint8_t* ptr1 = ((uint8_t*)ptr) + 16u;
		_mm_storeu_si128((__m128i*)ptr, v128i[0u]);
		_mm_storeu_si128((__m128i*)ptr1, v128i[1u]);
	}

	inline void Store(void* ptr, const V128I(&v128i)[4u])
	{
		uint8_t* ptr1 = ((uint8_t*)ptr) + 16u;
		uint8_t* ptr2 = ((uint8_t*)ptr) + 32u;
		uint8_t* ptr3 = ((uint8_t*)ptr) + 48u;
		_mm_storeu_si128((__m128i*)ptr, v128i[0u]);
		_mm_storeu_si128((__m128i*)ptr1, v128i[1u]);
		_mm_storeu_si128((__m128i*)ptr2, v128i[2u]);
		_mm_storeu_si128((__m128i*)ptr3, v128i[3u]);
	}

	inline void Store(void* ptr, const V128I(&v128i)[8u])
	{
		uint8_t* ptr1 = ((uint8_t*)ptr) + 16u;
		uint8_t* ptr2 = ((uint8_t*)ptr) + 32u;
		uint8_t* ptr3 = ((uint8_t*)ptr) + 48u;
		uint8_t* ptr4 = ((uint8_t*)ptr) + 64u;
		uint8_t* ptr5 = ((uint8_t*)ptr) + 80u;
		uint8_t* ptr6 = ((uint8_t*)ptr) + 96u;
		uint8_t* ptr7 = ((uint8_t*)ptr) + 112u;
		_mm_storeu_si128((__m128i*)ptr, v128i[0u]);
		_mm_storeu_si128((__m128i*)ptr1, v128i[1u]);
		_mm_storeu_si128((__m128i*)ptr2, v128i[2u]);
		_mm_storeu_si128((__m128i*)ptr3, v128i[3u]);
		_mm_storeu_si128((__m128i*)ptr4, v128i[4u]);
		_mm_storeu_si128((__m128i*)ptr5, v128i[5u]);
		_mm_storeu_si128((__m128i*)ptr6, v128i[6u]);
		_mm_storeu_si128((__m128i*)ptr7, v128i[7u]);
	}

	//
	// Type-specific (named struct) stores
	//

	inline void Store(void* ptr, const U8x16& data)
	{
		Store(ptr, data.v128);
	}

	inline void Store(void* ptr, const I8x16& data)
	{
		Store(ptr, data.v128);
	}

	inline void Store(void* ptr, const U16x8& data)
	{
		Store(ptr, data.v128);
	}

	inline void Store(void* ptr, const I16x8& data)
	{
		Store(ptr, data.v128);
	}

	inline void Store(void* ptr, const U16x16& data)
	{
		Store(ptr, data.v128);
	}

	inline void Store(void* ptr, const I16x16& data)
	{
		Store(ptr, data.v128);
	}

	inline void Store(void* ptr, const U32x4& data)
	{
		Store(ptr, data.v128);
	}

	inline void Store(void* ptr, const I32x4& data)
	{
		Store(ptr, data.v128);
	}

	inline void Store(void* ptr, const U32x16& data)
	{
		Store(ptr, data.v128);
	}

	inline void Store(void* ptr, const I32x16& data)
	{
		Store(ptr, data.v128);
	}

	inline void Store(void* ptr, const F32x4& data)
	{
		Store(ptr, data.v128f);
	}

	inline void Store(void* ptr, const F32x16& data)
	{
		float* ptr1 = ((float*)ptr) + 4u;
		float* ptr2 = ((float*)ptr) + 8u;
		float* ptr3 = ((float*)ptr) + 12u;
		Store(ptr, data.v128f[0u]);
		Store(ptr1, data.v128f[1u]);
		Store(ptr2, data.v128f[2u]);
		Store(ptr3, data.v128f[3u]);
	}

	inline void Store(void* ptr, const U64x2& data)
	{
		Store(ptr, data.v128);
	}

	inline void Store(void* ptr, const I64x2& data)
	{
		Store(ptr, data.v128);
	}

	inline void Store(void* ptr, const U64x16& data)
	{
		Store(ptr, data.v128);
	}

	inline void Store(void* ptr, const I64x16& data)
	{
		Store(ptr, data.v128);
	}

	inline void Store(void* ptr, const F64x2& data)
	{
		Store(ptr, data.v128d);
	}

	inline void Store(void* ptr, const F64x16& data)
	{
		double* ptr1 = ((double*)ptr) + 2u;
		double* ptr2 = ((double*)ptr) + 4u;
		double* ptr3 = ((double*)ptr) + 6u;
		double* ptr4 = ((double*)ptr) + 8u;
		double* ptr5 = ((double*)ptr) + 10u;
		double* ptr6 = ((double*)ptr) + 12u;
		double* ptr7 = ((double*)ptr) + 14u;
		Store(ptr, data.v128d[0u]);
		Store(ptr1, data.v128d[1u]);
		Store(ptr2, data.v128d[2u]);
		Store(ptr3, data.v128d[3u]);
		Store(ptr4, data.v128d[4u]);
		Store(ptr5, data.v128d[5u]);
		Store(ptr6, data.v128d[6u]);
		Store(ptr7, data.v128d[7u]);
	}
}
