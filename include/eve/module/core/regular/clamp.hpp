//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/swap_if.hpp>

namespace eve
{

  template<typename Options>
  struct clamp_t : elementwise_callable<clamp_t, Options>
  {
    template<value T,  value U,  value V>
    constexpr EVE_FORCEINLINE common_value_t<T, U, V>
    operator()(T a, U lo, V hi) const noexcept
    {
      return EVE_DISPATCH_CALL(a, lo, hi);
    }

    EVE_CALLABLE_OBJECT(clamp_t, clamp_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var clamp
//!   @brief Computes the largest integer not greater than the input.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::ordered_value T, eve::ordered_value U,  eve::value V>
//!      auto clamp(T x, U lo, V hi) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` : value to clamp.
//!
//!     * `lo`, `hi`: [the boundary values](@ref eve::value) to clamp `x` to.
//!
//!    **Return value**
//!       let l = min(lo, hi) and h =  max(lo, hi)
//!       Each [element](@ref glossary_elementwise)  of the result contains:
//!          *  `l`, if `x` is less than `l`.
//!          *  `h`, if `h` is less than `x`.
//!          *  otherwise `x`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/clamp.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::clamp[mask](x, ...)` provides a masked version of `eve::clamp` which is
//!     equivalent to `if_else (mask, clamp(x, ...), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/clamp.cpp}
//!
//! @}
//================================================================================================
  inline constexpr auto clamp = functor<clamp_t>;

  namespace detail
  {
    template<typename T, typename U, typename V, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<T, U, V>
    clamp_(EVE_REQUIRES(cpu_), O const &, T const &a, U const & lo,  V const & hi) noexcept
    {
      using r_t = common_value_t<T, U, V>;
      auto l = r_t(lo);
      auto h = r_t(hi);
      auto aa = r_t(a);
      swap_if(l > h, l, h);
      return eve::min(eve::max(aa, l), h);
    }
  }
}
