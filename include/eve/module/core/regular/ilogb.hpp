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
#include <eve/module/core/constant/mantissamask.hpp>
#include <eve/module/core/constant/exponentmask.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/sub.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_normal.hpp>

namespace eve
{
  template<typename Options>
  struct ilogb_t : elementwise_callable<ilogb_t, Options>
  {
    template<floating_value T>
    constexpr EVE_FORCEINLINE as_integer_t<T> operator()(T v) const noexcept
    {
      return this->behavior(as<as_integer_t<T>>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(ilogb_t, ilogb_);
  };

//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var ilogb
//!   @brief `elementwise_callable` object computing the integral IEEE ilogb of the floating value.
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
//!      template < floating_value T> constexpr as_integer_t<T> ilogb(T x)  noexcept;
//!
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::floating_value).
//!
//!    **Return value**
//!
//!      The spirit of the value of the std::ilogb is returned. In particular:
//!        *  `zero` and `nan` return `valmin(as<as_integer_t<T>>())`.
//!        *  `inf` and  `minf `return `valmax(as<as_integer_t<T>>())`.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/ilogb.cpp}
//================================================================================================
  inline constexpr auto ilogb = functor<ilogb_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<floating_value T, callable_options O>
    constexpr auto  ilogb_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
    {
      auto z = bit_and(exponentmask(as<T>()), a);
      auto x = (z >> nbmantissabits(eve::as<T>()));
      x = sub(x, maxexponent(eve::as<T>()));
      return if_else(is_eqz(a)||is_not_finite(a), valmin(as(x)), x);
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/ilogb.hpp>
#endif
