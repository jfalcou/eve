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
  struct extreme_value_skewness_t : constant_callable<extreme_value_skewness_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.23b95cp+0};
        else if constexpr (Opts::contains(lower)) return T{0x1.23b95ap+0};
        else                                      return T{0x1.23b95cp+0};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.23b95bd431d32p+0};
        else if constexpr (Opts::contains(lower)) return T{0x1.23b95bd431d31p+0};
        else                                      return T{0x1.23b95bd431d31p+0};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(extreme_value_skewness_t, extreme_value_skewness_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var extreme_value_skewness
  //!   @brief Callable object computing the extreme value distribution skewness :
  //!   \f$12\sqrt6\zeta(3)/\pi^3\f$.
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
  //!      T extreme_value_skewness(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::extreme_value_skewness(as<T>())` returns   \f$12\sqrt6\zeta(3)/\pi^3\f$.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/extreme_value_skewness.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto extreme_value_skewness = functor<extreme_value_skewness_t>;
}
