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
  struct twotonmb_t : constant_callable<twotonmb_t, Options, lower_option, upper_option>
  {
    template<typename T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>) return T{0x1p+23f};
      else                                  return T{0x1p+52};
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(twotonmb_t, twotonmb_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var twotonmb
//!   @brief Computes the  2 power of the number of mantissa bits of a floating value.
//!
//!   **Defined in Header**
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
//!     template<eve::floating_value T> constexpr T twotonmb(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!       The call `eve::twotonmb(as<T>())` is semantically equivalent to
//!      `eve::exp2 (T(eve::nbmantissabits (as<eve::element_type_t<T>>())))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/twotonmb.cpp}
//!
//================================================================================================
 inline constexpr auto twotonmb = functor<twotonmb_t>;

//================================================================================================
//! @}
//================================================================================================
}
