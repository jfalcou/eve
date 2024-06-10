# EVE FP16 support proposal

## Introduction

We propose to implement support for the IEEE-754 half-precision floating-point format (aka FP16) in the EVE library in three steps.

There is no standard fp16 type in C++ as of yet, the only way to represent it is to either use platform-specific intrinsics types, such as `_Float16` on x86 and `float16_t` on ARM, or use a custom 16-bit type on which specialized operations are implemented.

To unify the representation of fp16 across architectures and compilers, we propose to implement it as a `struct` with a single 16-bits wide field, for example:
```c++
struct fp16_t {
    uint16_t value;
};
```

This will allow us to implement the necessary operators on this type to allow interop with the platform-specific fp16 types.

## Step 1. Transparent types
This step consists of making `eve::wide` support transparent types (see definitions below). The goal of this step is to prepare for the end goal: being able to express `eve::wide<fp16_t>`.

```c++
template <>
struct transparent_trait<fp16_t> {
    using type = uint16_t;
};
```

This allows us to instantiate objects of type `eve::wide<fp16_t>`, and to use many of the `eve::wide` methods on them, such as `get`, `set`, `operator==`, etc.

## Step 2. Internal function rework

This step consists of reworking internal functions such as `as_register` to allow for users to extends the list of supported types, for example for transparent types:

```c++
// example for x86
template <typename Size>
constexpr auto as_register(as<wide<fp16_t>>, Size, x86_abi) {
    constexpr auto width = sizeof(Type) * Size::value;

    if constexpr (current_api >= avx512fp16) {
        if      constexpr (size <= 16) return __m128h{}
        else if constexpr (size == 32) return __m256h{}
        else if constexpr (size == 64) return __m512h{}
    } else {
        if      constexpr (size <= 16) return __m128i{}
    }
}
```

## Step 3. FP16 Support in EVE

Finally, once the groundwork is laid, we can then add the fp16 type to EVE, implement the necessary operators for interop with platform-specific fp16 types and implement the necessary intrinsics in the backends.

## Open questions & research

### FP16 codegen

Consider the following C++ code targeting a F16C capable x86 CPU:
```c++
#include <immintrin.h>

_Float16 test(_Float16 a, _Float16 b) {
    return a + b;
}
```
The codegen when compiling using Clang 18 is the following:
```x86asm
vpextrw     eax, xmm0, 0
vpextrw     ecx, xmm1, 0
vmovd       xmm0, ecx
vmovd       xmm1, eax
vcvtph2ps   xmm0, xmm0 
vcvtph2ps   xmm1, xmm1
vaddss      xmm0, xmm1, xmm0
vcvtps2ph   xmm0, xmm0, 4
vmovd       eax, xmm0 
vpinsrw     xmm0, xmm0, eax, 0
ret
```
We can observe that a lot of the instructions produced (mostly the function prelude and epilogue) consists of clearing the highest 112 bits of the xmm vectors. While apparently due to the ABI imposed upon the compiler, this indicates that, while usefull, the compilers' native support for fp16 scalar operations cannot be fully relied upon codegen-wise when optimizing for maximum performance. As such, it is possible that a hand-written implementation for fp16 support in EVE could be beneficial in the long term, although optional.

## Definitions & Name bikeshedding

### Transparent
From `#[repr(transparent)]` from Rust, also used in C++ (see transparent comparators). Refers to an enum, or to a struct which has a single member of non-zero size, and for which the layout in memory is guaranteed to be the same as that of that member.

Exemple:

Enums are considered transparent types by default:
```c++
enum class E: int { };

static_assert(transparent_value<E>);
```

Structs which can satisfy the definition of a transparent type can implement the transparent trait:
```c++
struct S { int v; }

template <> struct transparent_trait<S> { using type = int; }
```
For any transparent type `T`, this assertion must hold (ie. the memory layout of `T` and `transparent_trait<T>::type` must be the same):
```c++
static_assert((sizeof(T) == sizeof(transparent_trait<T>::type)) && (alignof(T) == alignof(transparent_trait<T>::type)));
```