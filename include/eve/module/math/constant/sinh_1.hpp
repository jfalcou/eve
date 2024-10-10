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
  struct sinh_1_t : constant_callable<sinh_1_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.2cd9fep+0};
        else if constexpr (Opts::contains(lower)) return T{0x1.2cd9fcp+0};
        else                                      return T{0x1.2cd9fcp+0};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.2cd9fc44eb983p+0};
        else if constexpr (Opts::contains(lower)) return T{0x1.2cd9fc44eb982p+0};
        else                                      return T{0x1.2cd9fc44eb982p+0};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(sinh_1_t, sinh_1_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var sinh_1
  //!   @brief Callable object computing the constant \f$\sinh(1)\f$.
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
  //!      T sinh_1(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::sinh_1(as<T>{})` returns the hyperbolic sine of 1.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/sinh_1.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto sinh_1 = functor<sinh_1_t>;
}
