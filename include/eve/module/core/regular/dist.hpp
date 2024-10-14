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
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/inf.hpp>

namespace eve
{
 template<typename Options>
  struct dist_t : elementwise_callable<dist_t, Options, saturated_option,  pedantic_option,
                                               upper_option, lower_option, strict_option>
  {
    template<value T,  value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    EVE_FORCEINLINE constexpr common_value_t<T, U> operator()(T a, U b) const noexcept
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(dist_t, dist_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var dist
//!   @brief `elementwise_callable` object computing the distance of its arguments.
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
//!      // Regular overloads
//!      constexpr auto dist(eve::value auto x, eve::value auto y)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto dist[conditional_expr auto c](eve::value auto x, eve::value auto y) noexcept; // 2
//!      constexpr auto dist[logical_value auto m](eve::value auto x, eve::value auto y)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto dist[saturated](eve::value auto x, eve::value auto y)               noexcept; // 3
//!      constexpr auto dist[pedantic](eve::value auto x, eve::value auto y)                noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [values](@ref value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of the distance of the arguments is returned,  i.e. `abs (x-y)`.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. The call `dist[saturated](x, y)` computes a saturated distance.
//!         Contrary to the non decorated case, it guarantees
//!         that the result is always defined. If \f$|x-y|\f$ is not representable,
//!         [the greatest representable positive value](@ref valmax) is returned.
//!      4. `dist[pedantic](x, y)`computes a distance wich is `NaN` if and only
//!          if one of the parameters is a `NaN`.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/dist.cpp}
//================================================================================================
  inline constexpr auto dist = functor<dist_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<value T, callable_options O>
    constexpr T dist_(EVE_REQUIRES(cpu_), O const& o, T a, T b)
    {
      T d = sub[o](eve::max(a, b), eve::min(a, b));
      if constexpr(O::contains(saturated) && signed_integral_value<T>)
        return if_else(is_ltz(d), valmax(eve::as(d)), d);
      else if constexpr(O::contains(pedantic) && floating_value<T>)
        return if_else(is_unordered(a, b), allbits, if_else(is_nan(d), inf(as(d)), d));
      else
        return d;
    }
  }
}

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/dist.hpp>
#endif
