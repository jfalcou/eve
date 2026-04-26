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
  struct max_safe_integer_t : constant_callable<max_safe_integer_t, Options, lower_option, upper_option>
  {
    template<typename T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
    {
      if      constexpr(std::same_as<T, eve::float16_t>) return _::float16_from_bits(0x6800);
      else if constexpr(std::same_as<T, float>  ) return T(0x1p+24-1);
      else if constexpr(std::same_as<T, double> ) return T(0x1p+53-1);
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(max_safe_integer_t, max_safe_integer_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var max_safe_integer
//!   @brief Computes the greatest floating point representing an integer such that n != n+1.
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
//!     template<eve::floating_value T> constexpr T max_safe_integer(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::max_safe_integer(as<T>())` is semantically equivalent to:
//!        * `T(2047.0f)` if `eve::element_type_t<T>` is float16.
//!        * `T(16777215.0f)` if `eve::element_type_t<T>` is float.
//!        * `T(9007199254740991.0)` if `eve::element_type_t<T>` is double.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/max_safe_integer.cpp}
//!
//================================================================================================
  inline constexpr auto max_safe_integer = functor<max_safe_integer_t>;
//================================================================================================
//! @}
//================================================================================================
}
