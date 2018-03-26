# simd_style_helper

C++ headers, templates, and inline methods for easy-to-understand explicit SIMD programming (initially MSVC and x86-64, will expand to others)

## Status

The code will be converted into using OpenCV universal intrinsics.

Next, the direction will be to focus on what enhancements could be brought into OpenCV universal intrinsics 
(and remain compatible with it), instead of introducing a different explicit-SIMD coding style.

However, I anticipate that the "row of pixels" and "grid of pixels", backed by an array of SIMD vectors 
(using the union type-punning trick), will bring many benefits, and help reduce the amount of explicit-SIMD
source code that needs to be maintained in algorithms.

A stretch goal is to find a forward path toward 256-bit and 512-bit (AVX256, AVX512) without requiring
complete rewrite of most algorithms already on universal intrinsics.

