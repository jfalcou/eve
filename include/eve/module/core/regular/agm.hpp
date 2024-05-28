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
#include <eve/module/core/constant/eps.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/any.hpp>
#include <eve/module/core/regular/average.hpp>
#include <eve/module/core/regular/exponent.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/is_lez.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/ldexp.hpp>
#include <eve/module/core/regular/sign.hpp>
#include <eve/module/core/regular/sqrt.hpp>

namespace eve
{
  template<typename Options>
  struct agm_t : elementwise_callable<agm_t, Options>
  {
    template<eve::floating_value T,  floating_value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T a, U b) const
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(agm_t, agm_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var agm
//!   @brief Computes the arithmetic-geometric mean.
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
//!      template< eve::floating_value T, eve::floating_value U >
//!      eve::common_value_t<T, U> agm(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!      The value of the arithmetic-geometric mean is returned. No overflow can occur.
//!      The two parameters must share the same sign.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/agm.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::agm[mask](x, ...)` provides a masked version of `agm` which is
//!     equivalent to `if_else(mask, agm(x, ...), x)`
//!
//! @}
//================================================================================================
  inline constexpr auto agm = functor<agm_t>;

  namespace detail
  {

    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    agm_(EVE_REQUIRES(cpu_), O const &, T a,  T b) noexcept
    {
      auto ex = exponent(average(a, b));
      auto r     = nan(as<T>());
      auto null = is_eqz(a)||is_eqz(b);
      r = if_else(null, zero, r);
      auto infi = is_infinite(a) || is_infinite(b);
      r = if_else(infi, a+b, r);
      auto unord = is_unordered(a, b);
      auto done = is_lez(sign(a)*sign(b)) || unord || infi;
      a = if_else(done,  zero, a);
      b = if_else(done,  zero, b);
      a =  ldexp(a, -ex);
      b =  ldexp(b, -ex);
      auto c  = average(a, -b);
      while (eve::any(eve::abs(c) > T(2)*eps(as(c))))
      {
        auto an=average(a, b);
        auto bn=sqrt(a*b);
        c=average(a, -b);
        a=an;
        b=bn;
      }
      return if_else(done, r, ldexp(b, ex));
    }
  }
}
