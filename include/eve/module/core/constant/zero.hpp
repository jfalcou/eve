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
  struct zero_t : constant_callable<zero_t, Options, lower_option, upper_option>
  {
    struct fill_zero
    {
      constexpr EVE_FORCEINLINE auto operator()(auto& m) const { return m = functor<zero_t>(as(m)); }
    };

    template<typename T>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, auto const&)
    {
      if constexpr( kumi::product_type<T> )
      {
        // Can't just T{kumi::map} because that may not work for scalar product types
        T res;
        kumi::for_each(fill_zero{}, res);
        return res;
      }
      else return T(0);
    }

    template<eve::value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

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
//!      template< eve::plain_value T >
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
//!
//================================================================================================
  inline constexpr auto zero = functor<zero_t>;

  // Required for if_else optimisation detections
  using callable_zero_ = tag_t<zero>;
//================================================================================================
//! @}
//================================================================================================
}
//
