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
  struct minlogdenormal_t : constant_callable<minlogdenormal_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>) return T{-0x1.9fe36ap+6};
      else                                  return T{-0x1.74910d52d3052p+9};
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return EVE_DISPATCH_CALL_PT(T, v);
    }
    
    EVE_CALLABLE_OBJECT(minlogdenormal_t, minlogdenormal_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var minlogdenormal
  //!   @brief Callable object computing the least value for which eve::exp is not denormal.
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
  //!      T minlogdenormal(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::minlogdenormal(as<T>())` returns  the least value for which
  //!      eve::exp is not zero.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/minlogdenormal.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto minlogdenormal = functor<minlogdenormal_t>;
}
