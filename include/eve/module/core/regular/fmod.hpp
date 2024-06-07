//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/rem.hpp>

namespace eve
{
  template<typename Options>
  struct fmod_t : elementwise_callable<fmod_t, Options>
  {
    template<eve::floating_value T0, floating_value T1>
    requires(eve::same_lanes_or_scalar<T0, T1>)
    EVE_FORCEINLINE constexpr common_value_t<T0, T1> operator()(T0 t0, T1 t1) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1);
    }

    EVE_CALLABLE_OBJECT(fmod_t, fmod_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var fmod
//!   @brief Alias of eve::rem[to_nearest2] only for floating values.
//! @}
//================================================================================================
  inline constexpr auto fmod = functor<fmod_t>;

  namespace detail
  {
    template<typename T> EVE_FORCEINLINE constexpr auto
    fmod_(EVE_REQUIRES(cpu_), T const& a, T const& b) noexcept
    {
      return rem[to_nearest2](a, b);
    }

  }
}
