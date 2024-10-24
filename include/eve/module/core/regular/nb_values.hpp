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
#include <eve/module/core/regular/signnz.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/is_ltz.hpp>

#include <eve/module/core/detail/next_kernel.hpp>

namespace eve
{
 template<typename Options>
  struct nb_values_t : elementwise_callable<nb_values_t, Options>
  {
    template<value T, value U>
    EVE_FORCEINLINE constexpr as_integer_t<common_value_t<T, U>, unsigned> operator()(T a, U b) const noexcept
    {
      return this->behavior(as<as_integer_t<common_value_t<T, U>, unsigned>>{}, eve::current_api, this->options(), a, b);
    }

    EVE_CALLABLE_OBJECT(nb_values_t, nb_values_);
  };

//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var nb_values
//!   @brief `elementwise_callable` object computing the number of values representable in the type between the
//!   [arguments](@ref eve::value).
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
//!      // Regular overloads
//!      constexpr auto nb_values(eve::value auto x, eve::value auto y)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto nb_values[conditional_expr auto c](eve::value auto x, eve::value auto y) noexcept; // 2
//!      constexpr auto nb_values[logical_value auto m](eve::value auto x, eve::value auto y)    noexcept; // 2
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
//!      1. Returns the number of values representable in the type in the interval `[x, y[`
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//================================================================================================
  inline constexpr auto nb_values = functor<nb_values_t>;
//================================================================================================
//!  @godbolt{doc/core/nb_values.cpp}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    constexpr auto nb_values_(EVE_REQUIRES(cpu_), O const&, T a, T b)
    {
      using ui_t = as_integer_t<T, unsigned>;
      if constexpr( floating_value<T> )
      {
        auto aa = eve::detail::bitinteger(a);
        auto bb = eve::detail::bitinteger(b);
        auto z  = if_else(is_unordered(a, b), eve::valmax(as<ui_t>{}), bit_cast(dist(bb, aa), as<ui_t>{}));
        return inc[is_ltz(signnz(a) * signnz(b))](z);
      }
      else
      {
        return dist[saturated](bit_cast(a, as<ui_t>{}), bit_cast(b, as<ui_t>{}));
      }
    }
  }
}
