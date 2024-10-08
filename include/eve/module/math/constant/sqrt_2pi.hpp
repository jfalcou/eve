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
  struct sqrt_2pi_t : constant_callable<sqrt_2pi_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.40d932p+1};
        else if constexpr (Opts::contains(lower)) return T{0x1.40d93p+1};
        else                                      return T{0x1.40d932p+1};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.40d931ff62706p+1};
        else if constexpr (Opts::contains(lower)) return T{0x1.40d931ff62705p+1};
        else                                      return T{0x1.40d931ff62706p+1};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(sqrt_2pi_t, sqrt_2pi_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var sqrt_2pi
  //!   @brief Callable object computing the constant \f$\sqrt{2\pi}\f$.
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
  //!      T sqrt_2pi(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::sqrt_2pi(as<T>())` returns athe square root of \f$2\pi\f$.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/sqrt_2pi.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto sqrt_2pi = functor<sqrt_2pi_t>;
}
