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
  struct valmax_t : constant_callable<valmax_t, Options, downward_option, upward_option>
  {
    template<typename T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
    {
      using e_t = element_type_t<T>;
      return T(std::numeric_limits<e_t>::max());
    }

    template<eve::value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(valmax_t, valmax_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var valmax
//!   @brief Computes the  the greatest representable value.
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
//!      T valmax(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::valmax(as<T>())` is semantically equivalent to
//!      `T(std::numeric_limits<element_type_t<T>>::max())`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/valmax.cpp}
//! @}
//================================================================================================
  inline constexpr auto valmax = functor<valmax_t>;

// Required for if_else optimisation detections
using callable_valmax_ = tag_t<valmax>;
}
