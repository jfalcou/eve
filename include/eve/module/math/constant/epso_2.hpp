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
  struct epso_2_t : constant_callable<epso_2_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr(std::same_as<T, float>)  return T{0x1p-24};
      else                                  return T{0x1p-53};
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return EVE_DISPATCH_CALL_PT(T, v);
    }

    EVE_CALLABLE_OBJECT(epso_2_t, epso_2_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var epso_2
  //!   @brief Callable object computing the half of the machine epsilon.
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
  //!      T epso_2(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::epso_2(as<T>())` returns the half of the machine epsilon.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/epso_2.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto epso_2 = functor<epso_2_t>;
}
