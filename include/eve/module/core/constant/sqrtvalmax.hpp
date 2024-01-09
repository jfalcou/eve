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
  struct sqrtvalmax_t : constant_callable<sqrtvalmax_t, Options, downward_option, upward_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, auto const&)
    {
      using e_t = element_type_t<T>;

           if constexpr( std::same_as<e_t, float> )         return T(0x1.fffffep+63);
      else if constexpr( std::same_as<e_t, double> )        return T(0x1.fffffffffffffp+511);
      else if constexpr( std::same_as<e_t, std::uint8_t> )  return T(15);
      else if constexpr( std::same_as<e_t, std::uint16_t> ) return T(255);
      else if constexpr( std::same_as<e_t, std::uint32_t> ) return T(65535);
      else if constexpr( std::same_as<e_t, std::uint64_t> ) return T(4294967296ULL);
      else if constexpr( std::same_as<e_t, std::int8_t> )   return T(11);
      else if constexpr( std::same_as<e_t, std::int16_t> )  return T(181);
      else if constexpr( std::same_as<e_t, std::int32_t> )  return T(46340);
      else if constexpr( std::same_as<e_t, std::int64_t> )  return T(3037000499LL);
    }

    template<typename T>
    requires(plain_scalar_value<element_type_t<T>>)
      EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sqrtvalmax_t, sqrtvalmax_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var sqrtvalmax
//!   @brief Computes the the greatest value less than the square root of eve::valmax.
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
//!      T sqrtvalmax(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::sqrtvalmax(as<T>())` is the greatest number of the type whose  square
//!      is less or equal to `eve::valmax(as<T>())`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/sqrtvalmax.cpp}
//! @}
//================================================================================================
  inline constexpr auto sqrtvalmax = functor<sqrtvalmax_t>;
}
