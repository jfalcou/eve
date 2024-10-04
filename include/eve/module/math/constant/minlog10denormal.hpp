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
  struct minlog10denormal_t : constant_callable<minlog10denormal_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr(std::same_as<T, float>) return T{-0x1.693c6cp+5};
      else                                 return T{-0x1.439b7422d1bfbp+8};
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return EVE_DISPATCH_CALL_PT(T, v);
    }

    EVE_CALLABLE_OBJECT(minlog10denormal_t, minlog10denormal_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var minlog10denormal
  //!   @brief Callable object computing the least value for which eve::exp10 is not zero.
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
  //!      T minlog10denormal(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::minlog10denormal(as<T>())` returns the least value for which
  //!      eve::exp10 is not denormal.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/minlog10denormal.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto minlog10denormal = functor<minlog10denormal_t>;
}
