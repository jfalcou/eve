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
  struct inf_t : constant_callable<inf_t, Options, lower_option, upper_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, auto const&)
    {
      if constexpr (std::same_as<T, detail::f16>) return detail::f16_from_bits(0x7C00);
      else                                        return std::numeric_limits<T>::infinity();
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(inf_t, inf_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var inf
//!   @brief Computes the infinity ieee value.
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
//!     template<eve::floating_value T> constexpr T inf(as<T> x);
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::inf(as<T>())` is semantically equivalent to
//!      `T(std::numeric_limits<eve::element_type_t<T>>::``infinity())`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/inf.cpp}
//!
//================================================================================================
  inline constexpr auto inf = functor<inf_t>;
//================================================================================================
//! @}
//================================================================================================
}
