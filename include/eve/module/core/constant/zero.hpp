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
  struct zero_t : constant_callable<zero_t, Options, downward_option, upward_option>
  {
    template<typename T>
    static EVE_FORCEINLINE T value(eve::as<T> const&, auto const&)
    {
      return T(0);
    }

    template<typename T>
    requires(plain_scalar_value<element_type_t<T>>)
      EVE_FORCEINLINE T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(zero_t, zero_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var zero
//!   @brief Computes the constant 0
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
//!      T zero(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::zero(as<T>())` is semantically equivalent to  `T(0)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/zero.cpp}
//! @}
//================================================================================================
inline constexpr auto zero = functor<zero_t>;

// Required for if_else optimisation detections
using callable_zero_ = tag_t<zero>;
}
