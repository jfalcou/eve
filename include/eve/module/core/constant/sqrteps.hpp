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
  struct sqrteps_t : constant_callable<sqrteps_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if constexpr (Opts::contains(upper))       return T{0x1.6a09e8p-12f};
        else                                       return T{0x1.6a09e6p-12f};
      }
      else if constexpr (std::same_as<T, double> ) return T{0x1p-26};
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(sqrteps_t, sqrteps_);
  };

  //================================================================================================
  //! @addtogroup core_constants
  //! @{
  //!   @var sqrteps
  //!   @brief Computes the square root of the machine epsilon.
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
  //!     template<eve::floating_value T> constexpr T sqrteps(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::sqrteps(as<T>())` is semantically equivalent to
  //!      `eve::sqrt (eve::eps (as<T>()))`
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/constant/sqrteps.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto sqrteps = functor<sqrteps_t>;
}
