//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/implementation.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_compress
  //! @{
  //!    @var compress
  //!    @brief A low level function to compress one simd value based on a mask.
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!    @note this is very low level function, most likely you are looking for
  //!    eve::compress_copy or eve::compress_store.
  //!
  //!    @note
  //!      * FIX-1647: eve::compress doesn't support `wide<tuple>` yet.
  //!      * the mask type can be any logical with the same cardinal.
  //!
  //!    Compression in simd is moving selected elements to the front of the simd_value.
  //!    Unfortunately, not for all `simd_value`, not for all plaftorms that can be done
  //!    efficiently. So the operation splits the input into chunks for which it's possible.
  //!
  //!    The function perfoms the following steps:
  //!      1) splits the simd_value and mask into chunks, that can be processed in one go.
  //!         This depends on what instructions are availiable.
  //!      2) Each chunk, gets shuffled in a way that moves selected elements (mask == true) to
  //!         the front. The tail of the resulting value is unspecified.
  //!         [a, b, c, d], (false, true, false, true) -> [b, d, _, _]
  //!      3) For each chunk we also compute how many elements are selected. (in the example - 2).
  //!      4) Both shuffled chunk and a number are put in a `kumi::tuple<simd_value, std::ptrdiff_t>`
  //!         TODO: there is a bug where sometimes it's an `int` and not `std::ptrdiff_t`.
  //!      5) Those chunks are combined together in another tuple.
  //!
  //!   List of people who's work was instrumental for building this:
  //!    - `@aqrit` user on Stack Overflow
  //!    - Peter Cordes
  //!
  //!    Throughout the code of compress there are references to what was taken from where
  //!    as well as explanations.
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!    @code
  //!    namespace eve
  //!    {
  //!       template <simd_value T, logical_simd_value L>
  //!       auto compress(T x, L m);                       // (1)
  //!
  //!       template <relative_conditional_expr C,
  //!                 simd_value T,
  //!                 logical_simd_value L>
  //!       auto compress[C ignore](T x, L m)              // (2)
  //!    }
  //!    @endcode
  //!
  //!   **Parameters**
  //!
  //!     * x - simd_value to compress
  //!     * m - mask which markes selected elements as true
  //!     * ignore - optional eve::relative_conditional_expr, passed in `[]`.
  //!                Ignored elements are treated as not selected.
  //!
  //!  **Return value**
  //!
  //!    1. `kumi::tuple<kumi::tuple<simd_value, std::ptrdiff_t>, ...>` - tuple of compressed chunks,
  //!        constructed as described earlier.
  //!    2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/compress/compress.cpp}
  //!
  //================================================================================================
  EVE_MAKE_CALLABLE(compress_, compress);
  //================================================================================================
  //!  @}
  //================================================================================================
}

#include <eve/module/core/compress/simd/common/compress.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/compress/simd/x86/compress.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/compress/simd/arm/sve/compress.hpp>
#endif

#if defined(EVE_INCLUDE_RISCV_HEADER)
#  include <eve/module/core/compress/simd/riscv/compress.hpp>
#endif
