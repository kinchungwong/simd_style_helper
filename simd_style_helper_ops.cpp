#include "stdafx.h"
#include "simd_style_helper_types.h"
#include "simd_style_helper_ops.h"

//
// Only some functions are fully implemented.
// This will be improved later.
//

namespace simd_style_helper
{
	//
	// Widen and Narrow between 8 and 16
	//

	U16x16 Widen(const U8x16& input)
	{
		const V128I zero = _mm_setzero_si128();
		U16x16 output;
		output.v128[0u] = _mm_unpacklo_epi8(input.v128, zero);
		output.v128[1u] = _mm_unpackhi_epi8(input.v128, zero);
		return output;
	}

	I16x16 WidenToSigned(const U8x16& input)
	{
		U16x16 unsignedResult = Widen(input);
		I16x16 result;
		result.v128[0u] = unsignedResult.v128[0u];
		result.v128[1u] = unsignedResult.v128[1u];
		return result;
	}

	U8x16 NarrowToUnsigned_Saturate(const U16x16& input)
	{
		// note: _mm_packus_epi16 cannot be used, input value above 32768 
		// are interpreted as negative, which saturate to zero, as opposed 
		// to saturating at 255
		//
		// Currently requires 
		// .... SSE4.1
		// .... _mm_min_epu16
		//
		const V128I clampValue = _mm_set1_epi16(32767);
		const V128I lowerEightClamped = _mm_min_epu16(input.v128[0u], clampValue);
		const V128I upperEightClamped = _mm_min_epu16(input.v128[1u], clampValue);
		U8x16 result;
		result.v128 = _mm_packus_epi16(lowerEightClamped, upperEightClamped);
		return result;
	}

	//U8x16 NarrowToUnsigned_Saturate(const I16x16& input);
	//I8x16 NarrowToSigned_Saturate(const U16x16& input);
	//I8x16 NarrowToSigned_Saturate(const I16x16& input);

	//U8x16 NarrowToUnsigned_TakeLower(const U16x16& input);
	//U8x16 NarrowToUnsigned_TakeLower(const I16x16& input);
	//I8x16 NarrowToSigned_TakeLower(const U16x16& input);
	//I8x16 NarrowToSigned_TakeLower(const I16x16& input);


	//
	// Widen and Narrow between 16 and 32
	//

	U32x16 Widen(const U16x16& input)
	{
		const V128I zero = _mm_setzero_si128();
		U32x16 output;
		output.v128[0u] = _mm_unpacklo_epi16(input.v128[0u], zero);
		output.v128[1u] = _mm_unpackhi_epi16(input.v128[0u], zero);
		output.v128[2u] = _mm_unpacklo_epi16(input.v128[1u], zero);
		output.v128[3u] = _mm_unpackhi_epi16(input.v128[1u], zero);
		return output;
	}

	//I32x16 WidenToSigned(const U16x16& input);

	U16x16 NarrowToUnsigned_Saturate(const U32x16& input)
	{
		//
		// Clamping is necessary because the pack instruction treat its input as signed.
		// 
		// Currently requires 
		// .... SSE4.1
		// .... _mm_min_epu32
		//
		// TODO: using a throwaway array (such as "clampedValues[]")
		// may unnecessarily constrain compiler rescheduling.
		//
		// https://llvm.org/docs/Passes.html#sroa-scalar-replacement-of-aggregates
		//
		const V128I clampValue = _mm_set1_epi32(65535);
		V128I clampedValues[] =
		{
			_mm_min_epu32(input.v128[0u], clampValue),
			_mm_min_epu32(input.v128[1u], clampValue),
			_mm_min_epu32(input.v128[2u], clampValue),
			_mm_min_epu32(input.v128[3u], clampValue),
		};
		U16x16 result;
		result.v128[0u] = _mm_packus_epi32(clampedValues[0u], clampedValues[1u]);
		result.v128[1u] = _mm_packus_epi32(clampedValues[2u], clampedValues[3u]);
		return result;
	}

	//U16x16 NarrowToUnsigned_Saturate(const I32x16& input);
	//I16x16 NarrowToSigned_Saturate(const U32x16& input);
	//I16x16 NarrowToSigned_Saturate(const I32x16& input);

	//U16x16 NarrowToUnsigned_TakeLower(const U32x16& input);
	//U16x16 NarrowToUnsigned_TakeLower(const I32x16& input);
	//I16x16 NarrowToSigned_TakeLower(const U32x16& input);
	//I16x16 NarrowToSigned_TakeLower(const I32x16& input);

	//
	// Addition, input is 8
	//

	U8x16 Add_Saturate(const U8x16& first, const U8x16& second)
	{
		U8x16 result;
		result.v128 = _mm_adds_epu8(first.v128, second.v128);
		return result;
	}

	U8x16 Add_TakeLower(const U8x16& first, const U8x16& second)
	{
		U8x16 result;
		result.v128 = _mm_add_epi8(first.v128, second.v128);
		return result;
	}

	I8x16 Add_Saturate(const I8x16& first, const I8x16& second)
	{
		I8x16 result;
		result.v128 = _mm_adds_epi8(first.v128, second.v128);
		return result;
	}

	I8x16 Add_TakeLower(const I8x16& first, const I8x16& second)
	{
		// same as Add_TakeLower(U8x16)
		I8x16 result;
		result.v128 = _mm_add_epi8(first.v128, second.v128);
		return result;
	}

	//
	// Addition, input is 16
	//

	U16x16 Add_Saturate(const U16x16& first, const U16x16& second)
	{
		U16x16 result;
		result.v128[0u] = _mm_adds_epu16(first.v128[0u], second.v128[0u]);
		result.v128[1u] = _mm_adds_epu16(first.v128[1u], second.v128[1u]);
		return result;
	}

	U16x16 Add_TakeLower(const U16x16& first, const U16x16& second)
	{
		U16x16 result;
		result.v128[0u] = _mm_add_epi16(first.v128[0u], second.v128[0u]);
		result.v128[1u] = _mm_add_epi16(first.v128[1u], second.v128[1u]);
		return result;
	}

	I16x16 Add_Saturate(const I16x16& first, const I16x16& second)
	{
		I16x16 result;
		result.v128[0u] = _mm_adds_epi16(first.v128[0u], second.v128[0u]);
		result.v128[1u] = _mm_adds_epi16(first.v128[1u], second.v128[1u]);
		return result;
	}

	I16x16 Add_TakeLower(const I16x16& first, const I16x16& second)
	{
		// Same as Add_TakeLower(U16x16)
		I16x16 result;
		result.v128[0u] = _mm_add_epi16(first.v128[0u], second.v128[0u]);
		result.v128[1u] = _mm_add_epi16(first.v128[1u], second.v128[1u]);
		return result;
	}

	//
	// Addition, input is 32
	//

	//U32x16 Add_Saturate(const U32x16& first, const U32x16& second);
	//U32x16 Add_TakeLower(const U32x16& first, const U32x16& second);

	//I32x16 Add_Saturate(const I32x16& first, const I32x16& second);
	//I32x16 Add_TakeLower(const I32x16& first, const I32x16& second);

	// 
	// Multiplication, input is 8
	//

	//U8x16 Multiply_Saturate(const U8x16& first, const U8x16& second);
	//U8x16 Multiply_TakeLower(const U8x16& first, const U8x16& second);

	U16x16 Multiply_Widen(const U8x16& first, const U8x16& second)
	{
		U16x16 firstWiden = Widen(first);
		U16x16 secondWiden = Widen(second);
		return Multiply_TakeLower(firstWiden, secondWiden);
	}

	//I8x16 Multiply_Saturate(const I8x16& first, const I8x16& second);
	//I8x16 Multiply_TakeLower(const I8x16& first, const I8x16& second);
	//I16x16 Multiply_Widen(const I8x16& first, const I8x16& second);

	// 
	// Multiplication, input is 16
	//

	//U16x16 Multiply_Saturate(const U16x16& first, const U16x16& second);

	U16x16 Multiply_TakeLower(const U16x16& first, const U16x16& second)
	{
		U16x16 result;
		result.v128[0u] = _mm_mullo_epi16(first.v128[0u], second.v128[0u]);
		result.v128[1u] = _mm_mullo_epi16(first.v128[1u], second.v128[1u]);
		return result;
	}

	//U32x16 Multiply_Widen(const U16x16& first, const U16x16& second);

	//I16x16 Multiply_Saturate(const I16x16& first, const I16x16& second);
	
	I16x16 Multiply_TakeLower(const I16x16& first, const I16x16& second)
	{
		// Same as Multiply_TakeLower(U16x16)
		I16x16 result;
		result.v128[0u] = _mm_mullo_epi16(first.v128[0u], second.v128[0u]);
		result.v128[1u] = _mm_mullo_epi16(first.v128[1u], second.v128[1u]);
		return result;
	}

	//I32x16 Multiply_Widen(const I16x16& first, const I16x16& second);

	// 
	// Multiplication, input is 32
	//

	//U32x16 Multiply_Saturate(const U32x16& first, const U32x16& second);
	//U32x16 Multiply_TakeLower(const U32x16& first, const U32x16& second);

	//I32x16 Multiply_Saturate(const I32x16& first, const I32x16& second);
	//I32x16 Multiply_TakeLower(const I32x16& first, const I32x16& second);

	//
	// Division by special constants, input is 16
	//

	//U16x16 DivideBy_255_Floor(const U16x16& input);

	U16x16 DivideBy_256_Floor(const U16x16& input)
	{
		U16x16 result;
		result.v128[0u] = _mm_srli_epi16(input.v128[0u], 8);
		result.v128[1u] = _mm_srli_epi16(input.v128[1u], 8);
		return result;
	}

	//U16x16 DivideBy_255_Rounded(const U16x16& input);

	U16x16 DivideBy_256_Rounded(const U16x16& input)
	{
		const __m128i roundingBias = _mm_set1_epi16(128);
		U16x16 result;
		result.v128[0u] = _mm_srli_epi16(_mm_adds_epu16(input.v128[0u], roundingBias), 8);
		result.v128[1u] = _mm_srli_epi16(_mm_adds_epu16(input.v128[1u], roundingBias), 8);
		return result;
	}

	//
	// Division by special constants, input is 32
	//

	//U32x16 DivideBy_255_Floor(const U32x16& input);
	//U32x16 DivideBy_256_Floor(const U32x16& input);
	//U32x16 DivideBy_65535_Floor(const U32x16& input);
	//U32x16 DivideBy_65536_Floor(const U32x16& input);

	//U32x16 DivideBy_255_Rounded(const U32x16& input);
	//U32x16 DivideBy_256_Rounded(const U32x16& input);
	//U32x16 DivideBy_65535_Rounded(const U32x16& input);
	//U32x16 DivideBy_65536_Rounded(const U32x16& input);
}
