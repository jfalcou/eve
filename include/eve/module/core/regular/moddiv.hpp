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
  struct moddiv_t : strict_tuple_callable<moddiv_t, Options>
  {

    template<eve::floating_value T0, eve::floating_value T1>
    requires(eve::same_lanes_or_scalar<T0, T1>)
      EVE_FORCEINLINE common_value_t<T0, T1>
    constexpr operator()(T0 x0, T1 x1, unsigned int p)  const noexcept
    {
      EVE_ASSERT(eve::all(eve::is_flint(x0)), "x0 is not a floating integer");
      EVE_ASSERT(eve::all(eve::is_flint(x1)), "x1 is not a floating integer");
      return EVE_DISPATCH_CALL(x0, x1, p);
    }

    EVE_CALLABLE_OBJECT(moddiv_t, moddiv_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var moddiv
//!   @brief tuple_callable` computing the division of its arguments modulo p.
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
//!      constexpr auto moddiv(auto x0, auto x1, value auto p) noexcept;
//!
//!      // semantic modifyier
//!      constexpr auto modadd(auto x0, auto x1, auto p) noexcept;
///!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x0`, `x1` : flint  arguments.
//!     * `p`: unsigned int prime value
//!
//!    **Return value**
//!
//!      1. The value of the product of the arguments modulo p is returned.
//!         x1 and x2 are supposed to be flint postitive and less than p.
//!      2. Same, but x1 and x2 are only supposed to be flint and are reduced first modulo p.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/moddiv.cpp}
//================================================================================================
  inline constexpr auto moddiv = functor<moddiv_t>;
//================================================================================================
//! @}
//================================================================================================
}

namespace eve::detail
{
  template<typename T0, typename T1, callable_options O>
  constexpr auto  moddiv_(EVE_REQUIRES(cpu_), O const&, T0 x, T1 y, unsigned int ip) noexcept
  {
    return modmul(x, modrec(y, ip), ip);
  }
}
