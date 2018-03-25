#pragma once

namespace simd_style_helper
{
    template <typename VT>
    struct Info;

    template <>
    struct Info<U8x16>
    {
        using ElemType = U8;
        enum : size_t { ElemCount = 16u };
        enum : size_t { V128Count = 1u };
    };

    template <>
    struct Info<I8x16>
    {
        using ElemType = I8;
        enum : size_t { ElemCount = 16u };
        enum : size_t { V128Count = 1u };
    };

    template <>
    struct Info<U16x8>
    {
        using ElemType = U16;
        enum : size_t { ElemCount = 8u };
        enum : size_t { V128Count = 1u };
    };

    template <>
    struct Info<I16x8>
    {
        using ElemType = I16;
        enum : size_t { ElemCount = 8u };
        enum : size_t { V128Count = 1u };
    };

    template <>
    struct Info<U16x16>
    {
        using ElemType = U16;
        enum : size_t { ElemCount = 16u };
        enum : size_t { V128Count = 2u };
    };

    template <>
    struct Info<I16x16>
    {
        using ElemType = I16;
        enum : size_t { ElemCount = 16u };
        enum : size_t { V128Count = 2u };
    };

    template <>
    struct Info<U32x4>
    {
        using ElemType = U32;
        enum : size_t { ElemCount = 4u };
        enum : size_t { V128Count = 1u };
    };

    template <>
    struct Info<I32x4>
    {
        using ElemType = I32;
        enum : size_t { ElemCount = 4u };
        enum : size_t { V128Count = 1u };
    };

    template <>
    struct Info<U32x16>
    {
        using ElemType = U32;
        enum : size_t { ElemCount = 16u };
        enum : size_t { V128Count = 4u };
    };

    template <>
    struct Info<I32x16>
    {
        using ElemType = I32;
        enum : size_t { ElemCount = 16u };
        enum : size_t { V128Count = 4u };
    };
}
