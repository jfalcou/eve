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

namespace eve
{
template<typename Options>
struct two_add_t : elementwise_callable<two_add_t, Options>
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
//!      constexpr auto two_add(floating_value auto x, floating_value auto y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [floating arguments](@ref eve::floating_value).
//!
//!   **Return value**
//!
//!     Computes [elementwise](@ref glossary_elementwise) a pair of values `[a,e]` such that:
//!       * `a` is `x+y`
//!       * `e` is a value such that `a`\f$\oplus\f$`e` is equal to `x`\f$\oplus\f$`y`,
//!          where \f$\oplus\f$ adds its two parameters with infinite precision.
//!
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
    auto z  = r0 - a;
    auto r1 = a - (r0 - z) + (b - z);

    if constexpr( eve::platform::supports_infinites )
      r1 = if_else(is_infinite(r0), eve::zero, r1);

    return eve::zip(r0, r1);
  }
}}
