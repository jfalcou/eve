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
  struct maxlog_t : constant_callable<maxlog_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>) return T{0x1.61814ap+6};
      else                                  return T{0x1.62b7d369a5aa7p+9};
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(maxlog_t, maxlog_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var maxlog
  //!   @brief Callable object computing the greatest positive value for which eve::exp is finite.
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
  //!      T maxlog(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::maxlog(as<T>())` returns the greatest positive value for
  //!      which eve::exp is finite.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/maxlog.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto maxlog = functor<maxlog_t>;
}
