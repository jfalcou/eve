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
struct minlog10_t : constant_callable<minlog10_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      return Constant<T, 0xc217b818U>(); //T(-0x1.2f703p+5);
    }
    else
    {
      return  Constant<T, 0xc0733a7146f72a42ULL>(); //T(-0x1.33a7146f72a42p+8);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(minlog10_t, minlog10_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var minlog10
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
//!      template< eve::value T >
//!      T minlog10(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::minlog10(as<T>())` returns  the least value for which
//!      eve::exp10 is not zero.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/minlog10.cpp}
//! @}
//================================================================================================
inline constexpr auto minlog10 = functor<minlog10_t>;
}
