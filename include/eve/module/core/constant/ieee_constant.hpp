//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>

#include <type_traits>

namespace eve
{
  namespace _
  {
    struct real16 { constexpr real16(auto v) : value(v) {} eve::float16_t value; };
    struct real32 { constexpr real32(auto v) : value(v) {} float  value; };
    struct real64 { constexpr real64(auto v) : value(v) {} double value; };
  }

//================================================================================================
//! @addtogroup eve_core_constants
//! @{
//!   @brief Builds a floating-point constant from the exact representation it must take in each
//!          precision.
//!
//!   @groupheader{Header file}
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
//!     template<auto D, auto F, floating_value T>
//!     constexpr T ieee_constant(as<T> target) noexcept;                    // 1
//!
//!     template<auto D, auto F, auto F16, floating_value T>
//!     constexpr T ieee_constant(as<T> target) noexcept;                    // 2
//!   }
//!   @endcode
//!
//!   **Template Parameters**
//!
//!     * `D`:   value used when the element type of `T` is `double`.
//!     * `F`:   value used when the element type of `T` is `float`.
//!     * `F16`: value used when the element type of `T` is [float16](@ref eve::float16_t).
//!
//!   **Parameters**
//!
//!     * `target`: [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!     1. `T(D)` if the element type of `T` is `double`, `T(F)` otherwise. A `float16` result is
//!        therefore built from `F`, which costs a conversion.
//!     2. `T(D)`, `T(F)` or `T(F16)` depending on the element type of `T`, so `float16` gets its
//!        own exact value.
//!
//!   @note Each value is meant to be written in hexadecimal floating-point notation, which pins the
//!         bit pattern exactly. A decimal literal would leave the last bits to the compiler's
//!         conversion, and the constant would differ between precisions.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/constant/ieee_constant.cpp}
//================================================================================================

  template<eve::_::real64 BD, eve::_::real32 BF, floating_value T>
  constexpr T ieee_constant(eve::as<T>)
  {
    using e_t = eve::element_type_t<T>;
    if constexpr(std::same_as<double,e_t>) return T(BD.value);
    else return T(BF.value);
  }

  template<eve::_::real64 BD, eve::_::real32 BF, eve::_::real32 BF16, floating_value T>
  constexpr T ieee_constant(eve::as<T>)
  {
    using e_t = eve::element_type_t<T>;
    if constexpr(std::same_as<double,e_t>) return T(BD.value);
    else if constexpr(std::same_as<float,e_t>)  return T(BF.value);
    else if constexpr(std::same_as<eve::float16_t,e_t>)  return T(BF16.value);
  }

//================================================================================================
//! @}
//================================================================================================
}
