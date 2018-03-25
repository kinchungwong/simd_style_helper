#pragma once
#include "simd_style_helper_types.h"
#include "simd_style_helper_traits.h"

//
// A template wrapper around PALIGNR (_mm_alignr_epi8)
//

namespace simd_style_helper
{
	// 
	// Given one or more (typically two or more) V128 registers, treat their 
	// concatenation as an array of bytes (in the same layout as if all 
	// registers are dumped into an array of V128 in memory), and then extract
	// a consecutive section of 16 bytes starting at the specified byte offset.
	//
	// The byte offset is a template parameter (compile-time constant), so
	// that it can use SIMD instructions which contain a hard-coded constant 
	// offset.
	//
	// Internally, this is implemented by reading one or two V128 registers
	// (aligned, which permits compiler and CPU hardware optimizations), 
	// and then optionally use PALIGNR to splice and extract the result.
	// 
	template <size_t byteOffset, size_t vcount>
	V128I ExtractWithByteOffset(const V128I(&va)[vcount])
	{
		static_assert((byteOffset + 16u) <= (16u * vcount),
			"ExtractWithByteOffset: offset plus range exceeds array bounds.");
		constexpr size_t vindex_lower = (byteOffset / 16u);
		constexpr size_t vindex_upper = (vindex_lower + 1u);
		constexpr size_t align_param = (byteOffset % 16u);
		//
		// TODO
		// Need implement constexpr-if alternative for pre-C++17 compiler configs.
		//
		if /*constexpr*/ (align_param == 0u)
		{
			return va[vindex_lower];
		}
		else
		{
			const V128I left = va[vindex_lower];
			const V128I right = va[vindex_upper];
#if 1
			// SSSE3
			return _mm_alignr_epi8(right, left, align_param);
#else
			// SSE2 - disabled because we assume both SSE4.1 and SSSE3
			return _mm_or_si128(
				_mm_srli_si128(left, align_param),
				_mm_slli_si128(right, 16u - align_param));
#endif
		}
	}

	template <size_t elemOffset>
	U16x8 ExtractAt(const U16x16& input)
	{
		constexpr byteOffset = elemOffset * sizeof(U16);
		U16x8 result;
		result.v128 = ExtractWithByteOffset<byteOffset>(input.v128);
		return result;
	}

	template <size_t elemOffset>
	I16x8 ExtractAt(const I16x16& input)
	{
		constexpr byteOffset = elemOffset * sizeof(I16);
		I16x8 result;
		result.v128 = ExtractWithByteOffset<byteOffset>(input.v128);
		return result;
	}

	template <size_t elemOffset>
	U32x4 ExtractAt(const U32x16& input)
	{
		constexpr byteOffset = elemOffset * sizeof(U32);
		U32x4 result;
		result.v128 = ExtractWithByteOffset<byteOffset>(input.v128);
		return result;
	}

	template <size_t elemOffset>
	I32x4 ExtractAt(const I32x16& input)
	{
		constexpr byteOffset = elemOffset * sizeof(I32);
		I32x4 result;
		result.v128 = ExtractWithByteOffset<byteOffset>(input.v128);
		return result;
	}
}
