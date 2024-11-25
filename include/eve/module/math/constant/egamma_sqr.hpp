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
  struct egamma_sqr_t : constant_callable<egamma_sqr_t, Options, lower_option, upper_option>
  {
    template<typename T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.552c98p-2};
        else if constexpr (Opts::contains(lower)) return T{0x1.552c96p-2};
        else                                      return T{0x1.552c98p-2};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.552c97fa03696p-2};
        else if constexpr (Opts::contains(lower)) return T{0x1.552c97fa03695p-2};
        else                                      return T{0x1.552c97fa03695p-2};
      }
    }

    template<floating_value T>
    constexpr EVE_FORCEINLINE T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(egamma_sqr_t, egamma_sqr_);
  };

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var egamma_sqr
//!   @brief Callable object computing the square of the [Euler-Mascheroni constant](@ref
//!   eve::egamma).
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
//!      T egamma_sqr(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::egamma_sqr(as<T>())` returns the square of the [Euler-Mascheroni constant](@ref
//!      eve::egamma).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/egamma_sqr.cpp}
//! @}
//================================================================================================
inline constexpr auto egamma_sqr = functor<egamma_sqr_t>;
}
