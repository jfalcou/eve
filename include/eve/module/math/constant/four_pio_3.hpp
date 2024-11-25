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
  struct four_pio_3_t : constant_callable<four_pio_3_t, Options, lower_option, upper_option>
  {
    template<typename T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.0c1524p+2};
        else if constexpr (Opts::contains(lower)) return T{0x1.0c1522p+2};
        else                                      return T{0x1.0c1524p+2};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.0c152382d7366p+2};
        else if constexpr (Opts::contains(lower)) return T{0x1.0c152382d7365p+2};
        else                                      return T{0x1.0c152382d7366p+2};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(four_pio_3_t, four_pio_3_);
  };

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var four_pio_3
//!   @brief Callable object computing the constant \f$4\pi/3\f$.
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
//!      T four_pio_3(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::four_pio_3(as<T>())` returns  \f$4\pi/3\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/four_pio_3.cpp}
//! @}
//================================================================================================
inline constexpr auto four_pio_3 = functor<four_pio_3_t>;
}
