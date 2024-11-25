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
  struct two_pi_t : constant_callable<two_pi_t, Options, lower_option, upper_option>
  {
    template<typename T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.921fb6p+2};
        else if constexpr (Opts::contains(lower)) return T{0x1.921fb4p+2};
        else                                      return T{0x1.921fb6p+2};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.921fb54442d19p+2};
        else if constexpr (Opts::contains(lower)) return T{0x1.921fb54442d18p+2};
        else                                      return T{0x1.921fb54442d18p+2};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(two_pi_t, two_pi_);
  };

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var two_pi
//!   @brief Callable object computing the constant \f$2\pi\f$.
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
//!      T two_pi(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::two_pi(as<T>())` returns \f$2\pi\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/two_pi.cpp}
//! @}
//================================================================================================
inline constexpr auto two_pi = functor<two_pi_t>;
}
