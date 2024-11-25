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
#include <bit>

namespace eve
{
  template<typename Options>
  struct allbits_t : constant_callable<allbits_t, Options, lower_option, upper_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr T value(as<T>, auto const&)
    {
      if      constexpr (std::integral<T>       )  return ~T{0};
      else if constexpr (std::same_as<T, double>)  return T{std::bit_cast<double>(~0ULL)};
      else if constexpr (std::same_as<T, float >)  return T{std::bit_cast<float>(~0U)};
    }

    template<plain_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(allbits_t, allbits_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var allbits
//!   @brief Computes a constant with all bits set.
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
//!     template<eve::plain_value T> constexpr T allbits(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!   **Return value**
//!
//!   The call `eve::allbits(as<T>())` returns a value of type `T` with all bits set.
//!
//!   @groupheader{Example}
//!   @godbolt{doc/core/constant/allbits.cpp}
//================================================================================================
inline constexpr auto allbits = functor<allbits_t>;
//================================================================================================
//! @}
//================================================================================================

// Required for if_else optimisation detections
using callable_allbits_ = tag_t<allbits>;
}
