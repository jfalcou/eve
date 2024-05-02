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
    template<value T,  value U>
    EVE_FORCEINLINE constexpr as_integer_t<common_value_t<T, U>, unsigned> operator()(T a, U b) const noexcept
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(nb_values_t, nb_values_);
  };

//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var nb_values
//!   @brief Computes the  number of values representable in the type between the
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
//!      template< eve::value T, eve::value U >
//!      as_integer_t<common_value_t<T, U>, unsigned> nb_values(T x, T y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!      Returns the number of values representable in the type in the interval `[x, y[`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/nb_values.cpp}
//================================================================================================
  inline constexpr auto nb_values = functor<nb_values_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr auto nb_values_(EVE_REQUIRES(cpu_), O const&, T a, T b)
    {
      using ui_t = as_integer_t<T, unsigned>;
      if constexpr( floating_value<T> )
      {
        auto aa = eve::detail::bitinteger(a);
        auto bb = eve::detail::bitinteger(b);
        auto z  = if_else(is_unordered(a, b), eve::valmax(eve::as<ui_t>()), bit_cast(dist(bb, aa), as<ui_t>()));
        return inc[is_ltz(signnz(a) * signnz(b))](z);
      }
      else
      {
        return dist[saturated](bit_cast(a, as<ui_t>()), bit_cast(b, as<ui_t>()));
      }
    }
  }
}
