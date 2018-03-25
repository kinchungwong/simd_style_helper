#pragma once

namespace simd_style_helper
{
    using U8 = uint8_t;
    using I8 = int8_t;
    using U16 = uint16_t;
    using I16 = int16_t;
    using U32 = uint32_t;
    using I32 = int32_t;
    using F32 = float;
    using U64 = uint64_t;
    using I64 = int64_t;
    using F64 = double;
    using V128I = __m128i;
    using V128F = __m128;
    using V128D = __m128d;

    struct V128
    {
        union
        {
            V128I vi;
            V128F vf;
            V128D vd;
        };
    };

    struct U8x16
    {
        union
        {
            V128I v128;
            U8 u8[16u];
        };
    };

    struct I8x16
    {
        union
        {
            V128I v128;
            I8 i8[16u];
        };
    };

    struct U16x8
    {
        union
        {
            V128I v128;
            U16 u16[8u];
        };
    };

    struct I16x8
    {
        union
        {
            V128I v128;
            I16 i16[8u];
        };
    };

    struct U16x16
    {
        union
        {
            V128I v128[2u];
            U16 u16[16u];
        };
    };

    struct I16x16
    {
        union
        {
            V128I v128[2u];
            I16 i16[16u];
        };
    };

    struct U32x4
    {
        union
        {
            V128I v128;
            U32 u32[4u];
        };
    };

    struct I32x4
    {
        union
        {
            V128I v128;
            I32 i32[4u];
        };
    };

    struct U32x16
    {
        union
        {
            V128I v128[4u];
            U32 u32[16u];
        };
    };

    struct I32x16
    {
        union
        {
            V128I v128[4u];
            I32 i32[16u];
        };
    };

    struct F32x4
    {
        union
        {
            V128F v128f;
            V128 v128;
            F32 f32[4u];
        };
    };

    struct F32x16
    {
        union
        {
            V128F v128f[4u];
            V128 v128[4u];
            F32 f32[16u];
        };
    };

    struct U64x2
    {
        union
        {
            V128I v128;
            U64 u64[2u];
        };
    };

    struct I64x2
    {
        union
        {
            V128I v128;
            I64 i64[2u];
        };
    };

    struct U64x16
    {
        union
        {
            V128I v128[8u];
            U64 u64[16u];
        };
    };

    struct I64x16
    {
        union
        {
            V128I v128[8u];
            I64 i64[16u];
        };
    };

    struct F64x2
    {
        union
        {
            V128D v128d;
            V128 v128;
            F64 f64[2u];
        };
    };

    struct F64x16
    {
        union
        {
            V128D v128d[8u];
            V128 v128[8u];
            F64 f64[16u];
        };
    };

    static_assert(sizeof(V128I) == 16u, "V128I");
    static_assert(sizeof(V128F) == 16u, "V128F");
    static_assert(sizeof(V128D) == 16u, "V128D");
    static_assert(sizeof(U8x16) == 16u, "U8x16");
    static_assert(sizeof(U8x16::u8) == 16u, "U8x16::u8[]");
    static_assert(sizeof(I8x16) == 16u, "I8x16");
    static_assert(sizeof(I8x16::i8) == 16u, "I8x16::i8[]");
    static_assert(sizeof(U16x8) == 16u, "U16x8");
    static_assert(sizeof(U16x8::u16) == 16u, "U16x8::u16[]");
    static_assert(sizeof(I16x8) == 16u, "I16x8");
    static_assert(sizeof(I16x8::i16) == 16u, "I16x8::i16[]");
    static_assert(sizeof(U16x16) == 32u, "U16x16");
    static_assert(sizeof(U16x16::u16) == 32u, "U16x16::u16[]");
    static_assert(sizeof(I16x16) == 32u, "I16x16");
    static_assert(sizeof(I16x16::i16) == 32u, "I16x16::i16[]");
    static_assert(sizeof(U32x4) == 16u, "U32x4");
    static_assert(sizeof(U32x4::u32) == 16u, "U32x4::u32[]");
    static_assert(sizeof(I32x4) == 16u, "I32x4");
    static_assert(sizeof(I32x4::i32) == 16u, "I32x4::i32[]");
    static_assert(sizeof(U32x16) == 64u, "U32x16");
    static_assert(sizeof(U32x16::u32) == 64u, "U32x16::u32[]");
    static_assert(sizeof(I32x16) == 64u, "I32x16");
    static_assert(sizeof(I32x16::i32) == 64u, "I32x16::i32[]");
    static_assert(sizeof(F32x4) == 16u, "F32x4");
    static_assert(sizeof(F32x4::f32) == 16u, "F32x4::f32[]");
    static_assert(sizeof(F32x16) == 64u, "F32x16");
    static_assert(sizeof(F32x16::f32) == 64u, "F32x16::f32[]");
    static_assert(sizeof(U64x2) == 16u, "U64x2");
    static_assert(sizeof(U64x2::u64) == 16u, "U64x2::u64[]");
    static_assert(sizeof(I64x2) == 16u, "I64x2");
    static_assert(sizeof(I64x2::i64) == 16u, "I64x2::i64[]");
    static_assert(sizeof(U64x16) == 128u, "U64x16");
    static_assert(sizeof(U64x16::u64) == 128u, "U64x16::u64[]");
    static_assert(sizeof(I64x16) == 128u, "I64x16");
    static_assert(sizeof(I64x16::i64) == 128u, "I64x16::i64[]");
    static_assert(sizeof(F64x2) == 16u, "F64x2");
    static_assert(sizeof(F64x2::f64) == 16u, "F64x2::f64[]");
    static_assert(sizeof(F64x16) == 128u, "F64x16");
    static_assert(sizeof(F64x16::f64) == 128u, "F64x16::f64[]");
}
