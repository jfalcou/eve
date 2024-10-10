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
  struct sqrt_pio_2_t : constant_callable<sqrt_pio_2_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.40d932p+0};
        else if constexpr (Opts::contains(lower)) return T{0x1.40d93p+0};
        else                                      return T{0x1.40d932p+0};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.40d931ff62706p+0};
        else if constexpr (Opts::contains(lower)) return T{0x1.40d931ff62705p+0};
        else                                      return T{0x1.40d931ff62706p+0};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(sqrt_pio_2_t, sqrt_pio_2_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var sqrt_pio_2
  //!   @brief Callable object computing the constant \f$\sqrt{\pi/2}\f$.
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
  //!      T sqrt_pio_2(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::sqrt_pio_2(as<T>{})` returns the square root of \f$\pi/2\f$.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/sqrt_pio_2.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto sqrt_pio_2 = functor<sqrt_pio_2_t>;
}
