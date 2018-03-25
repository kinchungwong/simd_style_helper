#pragma once

//
// Experimental namespace.
//

namespace simd_style_helper
{
	namespace experimental
	{
		class MemoryToVecHelper
		{
		public:
			MemoryToVecHelper(const void* ptr)
				: m_ptr(ptr)
			{
			}

			//
			// TODO: restrict type T of std::vector<T> to be arithmetic types (U8, I8, ... )
			// TODO: modify this class to prevent read past bounds. 
			// (a new size limit field needs to be added)
			//
			template <typename T>
			MemoryToVecHelper(const std::vector<T>& stdvec)
				: m_ptr(stdvec.data())
			{
			}

			template <size_t vcount>
			void operator >> (V128I(&va)[vcount]) const
			{
				const void* ptr = m_ptr;
				for (size_t vindex = 0u; vindex < vcount; ++vindex)
				{
					va[vindex] = Load<V128I>(ptr, vindex * 16u);
				}
			}

		private:
			void const * m_ptr;
		};
	}
}

namespace simd_style_helper
{
	namespace experimental
	{
		class PackedScalar_U8x16
		{
		public:
			PackedScalar_U8x16(const U8(&values)[16u])
			{
				m_packed = Load<U8x16>(&values[0u]);
			}

			template <size_t index>
			U8 Get() const
			{
				static_assert((index >= 0u) && (index <= 15u), "Invalid Get<> element index.");
				return _mm_extract_epi8(m_packed.v128, index);
			}

			U8 Get(size_t index) const
			{
				if (index > 15u)
				{
					throw std::exception("Invalid Get() element index at runtime.");
				}
				return m_packed.u8[index];
			}

			template <size_t index>
			U8x16 SplatFrom() const
			{
				//
				// Requires:
				// .... SSSE3
				// .... PSHUFB (_mm_shuffle_epi8)
				//
				// This function shifts the wanted byte into index zero, 
				// and then splat the value from index zero to the entire vector.
				//
				static_assert((index >= 0u) && (index <= 15u), "Invalid SplatFrom<> element index.");
				__m128i zero = _mm_setzero_si128();
				__m128i shifted = _mm_srli_si128(m_packed.v128, index);
				U8x16 result;
				result.v128 = _mm_shuffle_epi8(shifted, zero);
				return result;
			}

		private:
			U8x16 m_packed;
		};
	}
}

namespace simd_style_helper
{
	namespace experimental
	{
		//
		// This function computes 16 output pixels (unsigned 8-bit) from 
		// the convolution of a 3-by-3 filter coefficients with 
		// 16 input pixels and their surrounding neighbors.
		//
		// ---
		//
		// To remain SIMD friendly, the function is given access to 
		// three rows of 48 input pixels total. Only the center 16 input 
		// pixels and their immediate neighbors (plus/minus one) are used
		// in computation.
		//
		// --- 
		//
		// The dynamic performance of this implementation is achieved
		// by minimizing memory I/O while it is executing. For the remaining
		// cases where memory I/O cannot be avoided, this implementation 
		// soughts to guarantee alignment, which slightly reduces its 
		// overhead by allowing store-to-load forwarding.
		//
		// Refer to (*** TODO link needed ***) for this methodology.
		// 
		// ---
		// 
		// (The following is a copy of that text which explains memory I/O 
		// performance hierarchy with emphasis on image filtering.)
		//
		// * CPU SIMD registers,
		// * Heavily reused aligned memory space from stack space
		//   * The aligned local stack space is created when entering 
		//     a function's prologue, and cleaned up in the epilogue.
		//   * SIMD values can be loaded ans saved using the aligned 
		//     instructions MOVDQA(_mm_load_si128)
		//   * Because they are located on the stack space, their 
		//     addresses are hard - coded relative to the stack pointer.
		//   * Example: (from MSVC disassembly)
		// * Heavily reused row buffers
		//   * Dynamically - sized memory pool for row buffers
		// * Consecutive reading and writing of rows from / to 2D matrices(images)
		// * Unpredictable memory access
		//
		// --- 
		//
		// The filter coefficients are themselves stored as unsigned 8-bit,
		// and they must all sum up to 256. Note that no single coefficient 
		// can take on the value of 256, as that value overflows the type.
		//
		// The filter coefficients are packed into a SIMD vector, stored 
		// contiguously starting with the lower element index.
		//
		// ---
		//
		// This function is marked CODEGEN_NEVER_INLINE because its 
		// function pointer needs to be taken. The use of its function pointer
		// is part of the strategy to reduce binary code bloat. 
		//
		// Basically, there can be multiple implementations of Convolve33, 
		// each of which takes advantage on various kinds of symmetries
		// of the packed coefficients, in order to minimize the unique 
		// instances of 16-bit multiplications (which is the true bottleneck
		// after memory I/O). 
		//
		// The function pointer of these implementations decopule them from
		// the image-wide row processing loop which will call these 
		// implementations.
		//
		// ---
		//
		__declspec(noinline) inline
		U8x16 Convolve33_Demo(const Grid3x3_U8x48x3& grid, const PackedScalar_U8x16& packedCoefs)
		{
			enum : int
			{
				top = -1,
				mid = 0,
				bot = 1,
				left = -1,
				cent = 0,
				rght = 1
			};
			U16x16 sum;
			sum.v128[0u] = _mm_setzero_si128();
			sum.v128[1u] = _mm_setzero_si128();
			sum = Add_Saturate(sum, Multiply_Widen(packedCoefs.SplatFrom<0u>(), ExtractAroundCenter<top, left>(grid)));
			sum = Add_Saturate(sum, Multiply_Widen(packedCoefs.SplatFrom<1u>(), ExtractAroundCenter<top, cent>(grid)));
			sum = Add_Saturate(sum, Multiply_Widen(packedCoefs.SplatFrom<2u>(), ExtractAroundCenter<top, rght>(grid)));
			sum = Add_Saturate(sum, Multiply_Widen(packedCoefs.SplatFrom<3u>(), ExtractAroundCenter<mid, left>(grid)));
			sum = Add_Saturate(sum, Multiply_Widen(packedCoefs.SplatFrom<4u>(), ExtractAroundCenter<mid, cent>(grid)));
			sum = Add_Saturate(sum, Multiply_Widen(packedCoefs.SplatFrom<5u>(), ExtractAroundCenter<mid, rght>(grid)));
			sum = Add_Saturate(sum, Multiply_Widen(packedCoefs.SplatFrom<6u>(), ExtractAroundCenter<bot, left>(grid)));
			sum = Add_Saturate(sum, Multiply_Widen(packedCoefs.SplatFrom<7u>(), ExtractAroundCenter<bot, cent>(grid)));
			sum = Add_Saturate(sum, Multiply_Widen(packedCoefs.SplatFrom<8u>(), ExtractAroundCenter<bot, rght>(grid)));
			U8x16 result = NarrowToUnsigned_Saturate(DivideBy_256_Rounded(sum));
			return result;
		}
	}
}
