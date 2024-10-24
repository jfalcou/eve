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
  struct rsqrt_pio_2_t : constant_callable<rsqrt_pio_2_t, Options, lower_option, upper_option>
  {
    template<typename T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.988454p-1};
        else if constexpr (Opts::contains(lower)) return T{0x1.988452p-1};
        else                                      return T{0x1.988454p-1};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.9884533d436511p-1};
        else if constexpr (Opts::contains(lower)) return T{0x1.9884533d4365p-1};
        else                                      return T{0x1.9884533d43651p-1};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(rsqrt_pio_2_t, rsqrt_pio_2_);
  };

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var rsqrt_pio_2
//!   @brief Callable object computing the constant \f$(\pi/2)^{-1/2}\f$.
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
//!      T rsqrt_pio_2(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::rsqrt_pio_2(as<T>())` returns the inverse of  \f$\sqrt{\pi/2}\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/rsqrt_pio_2.cpp}
//! @}
//================================================================================================
inline constexpr auto rsqrt_pio_2 = functor<rsqrt_pio_2_t>;
}
