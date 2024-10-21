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
  struct pi2_t : constant_callable<pi2_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.3bd3cep+3};
        else if constexpr (Opts::contains(lower)) return T{0x1.3bd3ccp+3};
        else                                      return T{0x1.3bd3ccp+3};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.3bd3cc9be45dfp+3};
        else if constexpr (Opts::contains(lower)) return T{0x1.3bd3cc9be45dep+3};
        else                                      return T{0x1.3bd3cc9be45dep+3};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(pi2_t, pi2_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var pi2
  //!   @brief Callable object computing the square of \f$\pi\f$.
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
  //!      T pi2(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::pi2(as<T>{})` returns the square of \f$\pi\f$.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/pi2.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto pi2 = functor<pi2_t>;
}
