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
  struct rayleigh_skewness_t : constant_callable<rayleigh_skewness_t, Options, lower_option, upper_option>
  {
    template<typename T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.4320fp-1};
        else if constexpr (Opts::contains(lower)) return T{0x1.4320eep-1};
        else                                      return T{0x1.4320fp-1};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.4320efa6fa904p-1};
        else if constexpr (Opts::contains(lower)) return T{0x1.4320efa6fa903p-1};
        else                                      return T{0x1.4320efa6fa904p-1};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(rayleigh_skewness_t, rayleigh_skewness_);
  };

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var rayleigh_skewness
//!   @brief Callable object computing the Rayleigh skewness value :
//!   \f$2\sqrt\pi(\pi-3)/(4-\pi^{3/2})\f$.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T >
//!      T rayleigh_skewness(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::rayleigh_skewness(as<T>())` returns the Rayleigh skewness.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/rayleigh_skewness.cpp}
//! @}
//================================================================================================
inline constexpr auto rayleigh_skewness = functor<rayleigh_skewness_t>;
}
