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
  struct sqrt_e_t : constant_callable<sqrt_e_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.a6129ap+0};
        else if constexpr (Opts::contains(lower)) return T{0x1.a61298p+0};
        else                                      return T{0x1.a61298p+0};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.a61298e1e069cp+0};
        else if constexpr (Opts::contains(lower)) return T{0x1.a61298e1e069bp+0};
        else                                      return T{0x1.a61298e1e069cp+0};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(sqrt_e_t, sqrt_e_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var sqrt_e
  //!   @brief Callable object computing the constant \f$\sqrt{e}\f$.
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
  //!      T sqrt_e(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::sqrt_e(as<T>{})` returns  the square root of the
  //!      basis of the natural logarithms.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/sqrt_e.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto sqrt_e = functor<sqrt_e_t>;
}
