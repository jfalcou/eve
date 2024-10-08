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
  struct sqrtsmallestposval_t : constant_callable<sqrtsmallestposval_t, Options, lower_option, upper_option>
  {
    template<plain_value T>
    static EVE_FORCEINLINE constexpr T value(as<T>, auto const&)
    {
      if      constexpr (std::integral<T>       ) return T{1};
      else if constexpr (std::same_as<T, float> ) return T{0x1p-63};
      else if constexpr (std::same_as<T, double>) return T{0x1p-511};
    }

    template<plain_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(sqrtsmallestposval_t, sqrtsmallestposval_);
  };

  //================================================================================================
  //! @addtogroup core_constants
  //! @{
  //!   @var sqrtsmallestposval
  //!   @brief Computes the square root of the eve::smallestposval.
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
  //!     template< eve::plain_value T> constexpr T sqrtsmallestposval(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::sqrtsmallestposval(as<T>())` is semantically equivalent to
  //!      `eve::sqrt (eve::smallestposval(as<T>())`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/constant/sqrtsmallestposval.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto sqrtsmallestposval = functor<sqrtsmallestposval_t>;
}
