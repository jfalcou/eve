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
  struct one_t : constant_callable<one_t, Options, lower_option, upper_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr T value(as<T>, auto const&)
    {
      return T{1};
    }

    template<plain_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(one_t, one_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var one
//!   @brief Computes the constant \f$1\f$.
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
//!     template<eve::plain_value T> constexpr T one(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::one(as<T>())` is semantically equivalent to `T(1)`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/one.cpp}
//! @}
//================================================================================================
inline constexpr auto one = functor<one_t>;

// Required for if_else optimisation detections
using callable_one_ = tag_t<one>;
}
