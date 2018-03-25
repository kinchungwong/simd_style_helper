#pragma once
#include "simd_style_helper_types.h"
#include "simd_style_helper_traits.h"
#include "simd_style_helper_loadstore.h"
#include "simd_style_helper_align.h"

//
// NOTE: Even though these types are not defined in experimental namespace,
// they are still technically experimental.
//
// The design of this 3x3 grid of vectors class was fraught with mistakes 
// in the past. The details of these classes are subject to change, as 
// new mistakes are found and fixed.
//

namespace simd_style_helper
{
	struct Row1x3_U8x48
	{
		union
		{
			V128I v128[3u];
			U8x16 u8x16[3u];
			U8 u8[16u * 3u];
			struct
			{
				U8x16 left;
				U8x16 center;
				U8x16 right;
			} namedSixteen;
		};
	};

	struct Grid3x3_U8x48x3
	{
		union
		{
			V128I v128[3u * 3u];
			Row1x3_U8x48 rows[3u];
			U8x16 u8x16[3u * 3u];
			U8 u8[16u * 3u * 3u];
			struct
			{
				Row1x3_U8x48 top;
				Row1x3_U8x48 mid;
				Row1x3_U8x48 bot;
			} namedRow;
		};
	};

	template <int colOffset>
	U8x16 ExtractAroundCenter(const Row1x3_U8x48& input)
	{
		static_assert((colOffset >= -16) && (colOffset <= +16), "colOffset");
		constexpr size_t colIndex = (size_t)(colOffset + 16);
		U8x16 result;
		result.v128 = ExtractWithByteOffset<colIndex>(input.v128);
		return result;
	}

	template <int rowOffset, int colOffset>
	U8x16 ExtractAroundCenter(const Grid3x3_U8x48x3& input)
	{
		static_assert((rowOffset >= -1) && (rowOffset <= +1), "rowOffset");
		constexpr size_t rowIndex = (size_t)(rowOffset + 1);
		return ExtractAroundCenter<colOffset>(input.rows[rowIndex]);
	}
}
