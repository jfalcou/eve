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
  struct signmask_t : constant_callable<signmask_t, Options, downward_option, upward_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, auto const&)
    {
      using e_t = eve::element_type_t<T>;

         if constexpr( std::same_as<e_t, float> )     return T(-0x0p+0f);
    else if constexpr( std::same_as<e_t, double> )    return T(-0x0p+0);
    else if constexpr( std::same_as<e_t, uint8_t> )   return T(0x80U);
    else if constexpr( std::same_as<e_t, uint16_t> )  return T(0x8000U);
    else if constexpr( std::same_as<e_t, uint32_t> )  return T(0x80000000U);
    else if constexpr( std::same_as<e_t, uint64_t> )  return T(0x8000000000000000ULL);
    else if constexpr( std::same_as<e_t, int8_t> )    return T(-128);
    else if constexpr( std::same_as<e_t, int16_t> )   return T(-32768);
    else if constexpr( std::same_as<e_t, int32_t> )   return T(-2147483648LL);
    else if constexpr( std::same_as<e_t, int64_t> )   return T(-9223372036854775807LL - 1);
  }

    template<typename T>
    requires(plain_scalar_value<element_type_t<T>>)
      EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(signmask_t, signmask_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var signmask
//!   @brief Computes a value in which the most significant bit is the only bit set.
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
//!      template< eve::value T >
//!      T signmask(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::signmask(as<T))` returns a value of type T for which each element has
//!      all its bits unset except the highest.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/signmask.cpp}
//! @}
//================================================================================================
  inline constexpr auto signmask = functor<signmask_t>;
}
