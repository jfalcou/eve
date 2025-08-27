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
  struct valmin_t : constant_callable<valmin_t, Options, lower_option, upper_option>
  {
    template<typename T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
    {
      if constexpr (std::same_as<T, eve::float16_t>) return detail::float16_from_bits(0xFBFF);
      else                                        return std::numeric_limits<T>::lowest();
    }

    template<plain_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(valmin_t, valmin_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var valmin
//!   @brief Computes the the lowest representable value.
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
//!     template<eve::plain_value T> constexpr T valmin(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::valmin(as<T>())` is semantically equivalent to
//!     `T(std::numeric_limits<element_type_t<T>>::``lowest())`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/valmin.cpp}
//!
//================================================================================================
  inline constexpr auto valmin = functor<valmin_t>;

// Required for if_else optimisation detections
using callable_valmin_ = tag_t<valmin>;
//================================================================================================
//! @}
//================================================================================================
}
