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
#include <eve/module/core.hpp>

namespace eve
{
  template<typename Options>
  struct significants_t : strict_elementwise_callable<significants_t, Options>
  {
    template<floating_value T0, value T1>
    EVE_FORCEINLINE constexpr as_wide_as_t<T0, T1> operator()(T0 t0, T1 n) const noexcept
    {
      EVE_ASSERT(eve::all(is_flint(n)), "eve::significants - The value n is not flint");
      EVE_ASSERT(eve::all(is_gez(n))  , "eve::significants - Some n are not positive");
      return EVE_DISPATCH_CALL(t0, n);
    }

    EVE_CALLABLE_OBJECT(significants_t, significants_);
  };

//================================================================================================
//! @addtogroup math_exp
//! @{
//!   @var significants
//!   @brief Computes the rounding to n significants digits of the first input.
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
//!      template< eve::value T, eve::value N >
//!      eve::common_value_t<T, N> significants(T x, N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:  [floating argument](@ref eve::floating_value).
//!
//!     * `n` :  [value argument](@ref eve::integral_value). Must be positive and integral or flint.
//!
//!    **Return value**
//!
//!      Computes  [elementwise](@ref glossary_elementwise) the rounding to n
//!      significants digits of `x`.
//!      With null n the result is a NaN.
//!
//! @warning
//!   Floating numbers are not stored in decimal form. So if you try significants with
//!   a not exactly representable number the result can be not exactly what you expect.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/significants.cpp}
//! @}
//================================================================================================
inline constexpr auto significants = functor<significants_t>;

namespace detail
{
  template<floating_value T, value U, callable_options O>
  EVE_FORCEINLINE constexpr auto
  significants_(EVE_REQUIRES(cpu_), O const &, T const& a, U const& n) noexcept
  {
    using r_t = as_wide_as_t<T, U>;
    if constexpr(integral_value<U>)
    {
      return significants(r_t(a), convert(n, as_element<T>()));
    }
    else
    {
      EVE_ASSERT(eve::all(is_flint(n)), "eve::significants - The value n is not flint");
      EVE_ASSERT(eve::all(is_gez(n))  , "eve::significants - Some n are not positive");
      auto e      = floor(inc(log10(eve::abs(a)) - n));
      auto factor = exp10(abs(e));
      auto rfactor = rec[pedantic2](factor);
      auto tmp    = if_else(is_gez(e), nearest(a*rfactor)*factor, nearest(a*factor)*rfactor);
      tmp         = if_else(is_eqz(a), a, tmp);
      return if_else(is_nez(n), tmp, allbits);
    }
  }
}
}
