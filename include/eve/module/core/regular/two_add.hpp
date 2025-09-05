//================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/zip.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/maxmag.hpp>
#include <eve/module/core/regular/minmag.hpp>

namespace eve
{
  template<typename Options>
  struct two_add_t : elementwise_callable<two_add_t, Options, raw_option, pedantic_option>
  {
    template<eve::floating_value T, eve::floating_value U>
    requires(eve::same_lanes_or_scalar<T, U>)
      constexpr EVE_FORCEINLINE
    zipped<common_value_t<T,U>,common_value_t<T,U>> operator()(T a, U b) const
    {
      return EVE_DISPATCH_CALL(a,b);
    }

    EVE_CALLABLE_OBJECT(two_add_t, two_add_);
  };

//================================================================================================
//! @addtogroup core_accuracy
//! @{
//!   @var two_add
//!   @brief Computes the [elementwise](@ref glossary_elementwise)
//!   pair of  sum and error,
//!
//!   @groupheader{Header file}
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
//!      constexpr auto two_add(floating_value auto x, floating_value auto y)      noexcept; //1
//!      constexpr auto two_add[raw](floating_value auto x, floating_value auto y) noexcept; //2
//!
//!      // Semantic options
//!      constexpr auto two_add[pedantic](floating_value auto x, floating_value auto y)  noexcept; //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [floating arguments](@ref eve::floating_value).
//!
//!   **Return value**
//!
//!       Computes [elementwise](@ref glossary_elementwise) a pair of values `[a,e]` such that:
//!         * `a` is `x+y`
//!         * `e` is a value such that `a`\f$\oplus\f$`e` is equal to `x`\f$\oplus\f$`y`,
//!            where \f$\oplus\f$ adds its two parameters with infinite precision.
//!
//!     1. classical alogoritm (6 fps)
//!     2. 'fast' algorithm but only valid if  |x| <  |y| (2 fps)
//!     3. take care of overflow
//!
//!  @groupheader{External references}
//!   *  [On the Computation of Correctly-Rounded Sums](https://www.vinc17.net/research/papers/rr_ccrsums2.pdf)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/two_add.cpp}
//================================================================================================
  inline constexpr auto two_add = functor<two_add_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE auto two_add_(EVE_REQUIRES(cpu_), O const&, T a, T b)
    {
      auto r0 = a + b;
      T err;
      if constexpr(O::contains(raw)) // 2fp, this does not work if |a| <  |b| (or if radix is not 2, not our case)
      {
        err =  b - (r0 - a);
      }
       else //6fp always ok
      {
        auto z  = r0 - a;
        err = a - (r0 - z) + (b - z);
      }
      if constexpr( eve::platform::supports_infinites && O::contains(pedantic))
        err = if_else(is_infinite(r0), eve::zero, err);
      return eve::zip(r0, err);
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/two_add.hpp>
#endif
