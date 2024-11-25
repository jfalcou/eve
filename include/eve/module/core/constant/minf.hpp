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
  struct minf_t : constant_callable<minf_t, Options, lower_option, upper_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr T value(as<T>, auto const&)
    {
      return  T{-std::numeric_limits<T>::infinity()};
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(minf_t, minf_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var minf
//!   @brief Computes the -infinity ieee value.
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
//!      template<floating_value> constexpr T minf(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!    The call `eve::minf(as<T>())` is semantically equivalent to
//!    T(-std::numeric_limits<eve::element_type_t<T>>::``infinity())`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/minf.cpp}
//!
//================================================================================================
  inline constexpr auto minf = functor<minf_t>;
//================================================================================================
//! @}
//================================================================================================
}
