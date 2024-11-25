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
  struct two_o_3_t : constant_callable<two_o_3_t, Options, lower_option, upper_option>
  {
    template<typename T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.555556p-1};
        else if constexpr (Opts::contains(lower)) return T{0x1.555554p-1};
        else                                      return T{0x1.555556p-1};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.5555555555556p-1};
        else if constexpr (Opts::contains(lower)) return T{0x1.5555555555555p-1};
        else                                      return T{0x1.5555555555555p-1};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(two_o_3_t, two_o_3_);
  };

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var two_o_3
//!   @brief Callable object computing the constant \f$2/3\f$.
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
//!      T two_o_3(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::two_o_3(as<T>())` returns two third.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/two_o_3.cpp}
//! @}
//================================================================================================
inline constexpr auto two_o_3 = functor<two_o_3_t>;
}
