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
  struct mantissamask_t : constant_callable<mantissamask_t, Options, downward_option, upward_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr auto value(eve::as<T> const&, auto const&)
    {
      using i_t = as_uinteger_t<T>;

      if      constexpr(std::same_as<T, float>  ) return i_t(0x807FFFFFU);
      else if constexpr(std::same_as<T, double> ) return i_t(0x800FFFFFFFFFFFFFULL);
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr as_uinteger_t<T> operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(mantissamask_t, mantissamask_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var mantissamask
//!   @brief Computes the mask to extract the mantissa bits of an ieee floating value.
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
//!     template<eve::floating_value T> constexpr eve::as_uinteger_t<T> mantissamask(as<T> x);
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::mantissamask(as<T>())` returns [elementwise](@ref glossary_elementwise), the
//!      integral mask to extract the mantissa bits of an ieee floating value. The element values
//!      are:
//!        - 0x807FFFFFU if the [element type](@ref eve::element_type) is float
//!        - 0x800FFFFFFFFFFFFFULL if the [element type](@ref eve::element_type) is double
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/mantissamask.cpp}
//! @}
//================================================================================================
  inline constexpr auto mantissamask = functor<mantissamask_t>;
}
