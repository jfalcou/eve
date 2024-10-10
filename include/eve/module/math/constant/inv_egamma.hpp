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
  struct inv_egamma_t : constant_callable<inv_egamma_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.bb8228p+0};
        else if constexpr (Opts::contains(lower)) return T{0x1.bb8226p+0};
        else                                      return T{0x1.bb8226p+0};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.bb8226f502bf8p+0};
        else if constexpr (Opts::contains(lower)) return T{0x1.bb8226f502bf7p+0};
        else                                      return T{0x1.bb8226f502bf8p+0};
      }
    }
    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(inv_egamma_t, inv_egamma_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var inv_egamma
  //!   @brief Callable object computing the inverse of the [Euler-Mascheroni constant](@ref
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
  //!      T inv_egamma(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::inv_egamma(as<T>{})` returns the inverse of the [Euler-Mascheroni constant](@ref
  //!       eve::egamma).
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/inv_egamma.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto inv_egamma = functor<inv_egamma_t>;
}
