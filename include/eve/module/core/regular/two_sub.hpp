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
#include <eve/module/core.hpp>

namespace eve
{
  template<typename Options>
  struct two_sub_t : elementwise_callable<two_sub_t, Options, mag_option, raw_option, pedantic_option>
  {
    template<eve::floating_value T, eve::floating_value U>
    constexpr EVE_FORCEINLINE zipped<common_value_t<T, U>, common_value_t<T, U>>
    operator()(T a, U b) const noexcept
    {
      return EVE_DISPATCH_CALL(a, b);
    }

    EVE_CALLABLE_OBJECT(two_sub_t, two_sub_);
  };

//================================================================================================
//! @addtogroup core_accuracy
//! @{
//!   @var two_sub
//!   @brief Computes the [elementwise](@ref glossary_elementwise)
//!   pair of  sub and error,
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
//!      // Regular overload
//!      constexpr auto two_sub(floating_value auto x, floating_value auto y)            noexcept; //1
//!      constexpr auto two_sub[raw](floating_value auto x, floating_value auto y)       noexcept; //2
//!
//!      // Semantic options
//!      constexpr auto two_sub[pedantic](floating_value auto x, floating_value auto y)  noexcept; //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [floating arguments](@ref eve::value).
//!
//!   **Return value**
//!
//!     Computes [elementwise](@ref glossary_elementwise) a pair of values `[a,e]` such that:
//!
//!     * `a` is `x+y`
//!     * `e` is a value such that `a`\f$\oplus\f$`e` is equal to `x`\f$\oplus\f$`y`
//!        where \f$\oplus\f$ adds its two parameters with infinite precision.
//!
//!     1. classical alogoritm  (6 fps)
//!     2. 'fast' algorithm but only valid if  |x| <  |y| (2 fps) (your responsability)
//!     3. take care of overflow
//!
//!  @groupheader{External references}
//!   *  [On the Computation of Correctly-Rounded Sums](https://www.vinc17.net/research/papers/rr_ccrsums2.pdf)
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/two_sub.cpp}
//!
//! @}
//================================================================================================
inline constexpr auto two_sub = functor<two_sub_t>;

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    EVE_FORCEINLINE auto
    two_sub_(EVE_REQUIRES(cpu_), O const& , T a , U b) noexcept
    {
      auto r0 = a - b;
      T err;
      if constexpr(O::contains(raw)) // 2fp, this does not work if |a| <  |b| (or if radix is not 2, not our case)
      {
        err =   (a-r0) -b;
      }
      else //6fp always okq
      {
        auto z  = r0 - a;
        err = a - (r0 - z) - (z +b);
      }
      if constexpr( eve::platform::supports_infinites && O::contains(pedantic))
        err = if_else(is_infinite(r0), eve::zero, err);
      return eve::zip(r0, err);
    }
  }
}
