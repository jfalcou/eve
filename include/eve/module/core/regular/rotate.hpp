//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once


#include <eve/arch.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/pattern.hpp>

#include <array>

namespace eve
{
//================================================================================================
//! @addtogroup core
//! @{
//!    @var rotate
//!    @brief rotates two halves of the register by a chosen number of elements.
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template<simd_value T, std::ptrdiff_t M>
//!      T rotate(T x, index<N> const &) noexcept;
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` : simd value to rotate
//!     * `M` : position of the middle.
//!             In std::rotate(f, m, l) -> this is std::distance(f, m);
//!
//!    **Return value**
//!
//!    Return T which is a permutation of x such
//!    that elements x[M: T::size()) come first followed by x[0:M)
//!    and the relative order in those halves is preserved.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/rotate.cpp}
//!
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(rotate_, rotate);

template<std::ptrdiff_t M, std::ptrdiff_t N>
inline constexpr auto rotate_pattern = fix_pattern<N>(
  [](auto i, auto) {
    if (i < N - M) return M + i;
    else           return i + M - N;
  }
);

namespace detail
{
  template<std::ptrdiff_t N, std::ptrdiff_t... I>
  inline constexpr auto is_rotate = []() -> std::ptrdiff_t
  {
    std::array actual  = {I...};
    if (actual.size() != N) return 0;

    std::ptrdiff_t rotation = actual[0];
    for ( auto x : actual ) {
      if (x != rotation) {
        return 0;
      }
      rotation = (rotation + 1) % actual.size();
    }

    return rotation;
  }();
}

}

#include <eve/module/core/regular/impl/rotate.hpp>
