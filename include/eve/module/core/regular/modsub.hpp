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

namespace eve
{
  template<typename Options>
  struct modsub_t : strict_tuple_callable<modsub_t, Options, modular_option>
  {

    template<eve::floating_value T0, eve::floating_value T1>
    requires(eve::same_lanes_or_scalar<T0, T1>)
      EVE_FORCEINLINE common_value_t<T0, T1>
    constexpr operator()(T0 x0, T1 x1, unsigned int p)  const noexcept
    {
      using O = decltype(this->options());
      if constexpr(O::contains(modular))
      {
        EVE_ASSERT(eve::all(eve::is_flint(x0)), "x0 is not a floating integer");
        EVE_ASSERT(eve::all(eve::is_flint(x1)), "x1 is not a floating integer");
      }
      else
      {
        EVE_ASSERT(eve::all(eve::is_flint(x0) && is_gez(x1)), "x0 is not a floating positive integer");
        EVE_ASSERT(eve::all(eve::is_flint(x1) && is_gez(x1)), "x1 is not a floating positive integer");
      }
      return EVE_DISPATCH_CALL(x0, x1, p);
    }

    EVE_CALLABLE_OBJECT(modsub_t, modsub_);
  };

//================================================================================================
//! @subtogroup core_arithmetic
//! @{
//!   @var modsub
//!   @brief tuple_callable` computing the difference of its arguments modulo p.
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
//!      constexpr auto modsub(auto x0, auto x1, auto p) noexcept;
//!
//!      // semantic modifyier
//!      constexpr auto modsub(auto x0, auto x1, auto p) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x0`, `x1` : flint  arguments.
//!     * `p`: unsigned int prime value
//!
//!    **Return value**
//!
//!      1. The value of the difference of the arguments modulo p is returned.
//!         x1 and x2 are supposed to be flint postitive and less than p.
//!      2. Same, but x1 and x2 are only supposed to be flint and are reduced first modulo p.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/modsub.cpp}
//================================================================================================
  inline constexpr auto modsub = functor<modsub_t>;
//================================================================================================
//! @}
//================================================================================================

}

namespace eve::detail
{
  template<typename T0, typename T1, callable_options O>
  constexpr auto modsub_(EVE_REQUIRES(cpu_), O const&, T0 const& x,  T1 const & y, unsigned int ip) noexcept
  {
    using r_t = eve::common_value_t<T0, T1>;
    auto p = r_t(ip);
    if (O::contains(modular))
    {
      return eve::rem(x-y, p);
    }
    else
    {
      auto s = x-y;
      s = eve::sub[s >= p](s, p);
      return eve::add[is_ltz(s)](s, p);
    }
  }
}
