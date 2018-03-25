#pragma once

//
// Mathematical and conversion for Experimental types. 
//
// It may be harder to use than the non-template types.
// 
// It may not make its way to the library.
// 
// Experimental stuff are in namespace "simd_style_helper::experimental"
//
// This header file consists of basic math operations, as well as 
// narrowing and widening. This is because many basic math operations
// depend on narrowing and widening, and narrowing-with-saturation
// also depend on some basic math operations. Thus, they must be 
// declared in the same header file.
// 

namespace simd_style_helper
{
	//
	// Widen and Narrow between 8 and 16
	//

	U16x16 Widen(const U8x16& input);
	I16x16 WidenToSigned(const U8x16& input);

	U8x16 NarrowToUnsigned_Saturate(const U16x16& input);
	U8x16 NarrowToUnsigned_Saturate(const I16x16& input);
	I8x16 NarrowToSigned_Saturate(const U16x16& input);
	I8x16 NarrowToSigned_Saturate(const I16x16& input);

	U8x16 NarrowToUnsigned_TakeLower(const U16x16& input);
	U8x16 NarrowToUnsigned_TakeLower(const I16x16& input);
	I8x16 NarrowToSigned_TakeLower(const U16x16& input);
	I8x16 NarrowToSigned_TakeLower(const I16x16& input);

	//
	// Widen and Narrow between 16 and 32
	//

	U32x16 Widen(const U16x16& input);
	I32x16 WidenToSigned(const U16x16& input);

	U16x16 NarrowToUnsigned_Saturate(const U32x16& input);
	U16x16 NarrowToUnsigned_Saturate(const I32x16& input);
	I16x16 NarrowToSigned_Saturate(const U32x16& input);
	I16x16 NarrowToSigned_Saturate(const I32x16& input);

	U16x16 NarrowToUnsigned_TakeLower(const U32x16& input);
	U16x16 NarrowToUnsigned_TakeLower(const I32x16& input);
	I16x16 NarrowToSigned_TakeLower(const U32x16& input);
	I16x16 NarrowToSigned_TakeLower(const I32x16& input);

	//
	// Addition, input is 8
	//

	U8x16 Add_Saturate(const U8x16& first, const U8x16& second);
	U8x16 Add_TakeLower(const U8x16& first, const U8x16& second);

	I8x16 Add_Saturate(const I8x16& first, const I8x16& second);
	I8x16 Add_TakeLower(const I8x16& first, const I8x16& second);

	//
	// Addition, input is 16
	//

	U16x16 Add_Saturate(const U16x16& first, const U16x16& second);
	U16x16 Add_TakeLower(const U16x16& first, const U16x16& second);

	I16x16 Add_Saturate(const I16x16& first, const I16x16& second);
	I16x16 Add_TakeLower(const I16x16& first, const I16x16& second);

	//
	// Addition, input is 32
	//

	U32x16 Add_Saturate(const U32x16& first, const U32x16& second);
	U32x16 Add_TakeLower(const U32x16& first, const U32x16& second);

	I32x16 Add_Saturate(const I32x16& first, const I32x16& second);
	I32x16 Add_TakeLower(const I32x16& first, const I32x16& second);

	// 
	// Multiplication, input is 8
	//

	U8x16 Multiply_Saturate(const U8x16& first, const U8x16& second);
	U8x16 Multiply_TakeLower(const U8x16& first, const U8x16& second);
	U16x16 Multiply_Widen(const U8x16& first, const U8x16& second);

	I8x16 Multiply_Saturate(const I8x16& first, const I8x16& second);
	I8x16 Multiply_TakeLower(const I8x16& first, const I8x16& second);
	I16x16 Multiply_Widen(const I8x16& first, const I8x16& second);

	// 
	// Multiplication, input is 16
	//

	U16x16 Multiply_Saturate(const U16x16& first, const U16x16& second);
	U16x16 Multiply_TakeLower(const U16x16& first, const U16x16& second);
	U32x16 Multiply_Widen(const U16x16& first, const U16x16& second);

	I16x16 Multiply_Saturate(const I16x16& first, const I16x16& second);
	I16x16 Multiply_TakeLower(const I16x16& first, const I16x16& second);
	I32x16 Multiply_Widen(const I16x16& first, const I16x16& second);

	// 
	// Multiplication, input is 32
	//

	U32x16 Multiply_Saturate(const U32x16& first, const U32x16& second);
	U32x16 Multiply_TakeLower(const U32x16& first, const U32x16& second);

	I32x16 Multiply_Saturate(const I32x16& first, const I32x16& second);
	I32x16 Multiply_TakeLower(const I32x16& first, const I32x16& second);

	//
	// Division by special constants, input is 16
	//

	U16x16 DivideBy_255_Floor(const U16x16& input);
	U16x16 DivideBy_256_Floor(const U16x16& input);

	U16x16 DivideBy_255_Rounded(const U16x16& input);
	U16x16 DivideBy_256_Rounded(const U16x16& input);

	//
	// Division by special constants, input is 32
	//

	U32x16 DivideBy_255_Floor(const U32x16& input);
	U32x16 DivideBy_256_Floor(const U32x16& input);
	U32x16 DivideBy_65535_Floor(const U32x16& input);
	U32x16 DivideBy_65536_Floor(const U32x16& input);

	U32x16 DivideBy_255_Rounded(const U32x16& input);
	U32x16 DivideBy_256_Rounded(const U32x16& input);
	U32x16 DivideBy_65535_Rounded(const U32x16& input);
	U32x16 DivideBy_65536_Rounded(const U32x16& input);
}
