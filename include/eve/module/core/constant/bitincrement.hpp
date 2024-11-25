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
  struct bitincrement_t : constant_callable<bitincrement_t, Options, lower_option, upper_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr T value(as<T>, auto const&)
    {
      if      constexpr (std::integral<T>       ) return T{1};
      else if constexpr (std::same_as<T, float> ) return T{0x1p-149};
      else if constexpr (std::same_as<T, double>) return T{0x0.0000000000001p-1022};
    }

    template<plain_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(bitincrement_t, bitincrement_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var bitincrement
//!   @brief Computes a constant with only the least significant bit set.
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
//!     template< eve::plain_value T > constexpr T bitincrement(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!   **Return value**
//!
//!   The call `eve::bitincrement(as<T>())` returns a value of type `T` with only the least significant
//!   bit set.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/core/constant/bitincrement.cpp}
//!
//================================================================================================
inline constexpr auto bitincrement = functor<bitincrement_t>;
//================================================================================================
//! @}
//================================================================================================
}
