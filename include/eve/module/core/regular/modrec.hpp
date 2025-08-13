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
#include <eve/module/core/regular/modpow.hpp>

namespace eve
{
  template<typename Options>
  struct modrec_t : strict_tuple_callable<modrec_t, Options>
  {

    template<eve::floating_value T0>
    requires(eve::same_lanes_or_scalar<T0>)
      EVE_FORCEINLINE T0
    constexpr operator()(T0 x0, unsigned int p)  const noexcept
    {
      EVE_ASSERT(eve::all(eve::is_flint(x0)), "x0 is not a floating integer");
      EVE_ASSERT(eve::all(eve::is_flint(x1)), "x1 is not a floating integer");
      return EVE_DISPATCH_CALL(x0, p);
    }

    EVE_CALLABLE_OBJECT(modrec_t, modrec_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var modrec
//!   @brief tuple_callable` computing x^y mod p.
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
//!      constexpr auto modrec(auto x0, auto p) noexcept;
//!
//!      // semantic modifyier
//!      constexpr auto modadd(auto x0, auto p) noexcept;
///!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x0`: flint  arguments.
//!     * `p`: unsigned int prime value
//!
//!    **Return value**
//!
//!      1. The value of the product of the arguments modulo p is returned.
//!         x1 is supposed to be flint postitive and less than p.
//!      2. Same, but x1 and x2 are only supposed to be flint and are reduced first modulo p.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/modrec.cpp}
//================================================================================================
  inline constexpr auto modrec = functor<modrec_t>;
//================================================================================================
//! @}
//================================================================================================
}

namespace eve::detail
{
  template<typename T0, callable_options O>
  constexpr auto  modrec_(EVE_REQUIRES(cpu_), O const&, T0 a0, unsigned int ip) noexcept
  {
    return modpow(a0, ip-2, ip);
  }
}
