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
  struct lambert_t : elementwise_callable<lambert_t, Options>
  {
    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE constexpr
    kumi::tuple<T, T>
    operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(lambert_t, lambert_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var lambert
//!   @brief Computes the inverse of the function \f$ x \rightarrow xe^x \f$
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_ordered_value T >
//!      kumi::tuple<T, T> lambert(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   A tuple of the two branch values of the Lambert functionis returned with the following
//!   considerations:
//!
//!     * The branches are not defined for input less than \f$e^{-1}\f$ in that case the values
//!       returned are NaN.
//!     * If the inputs are positive, only one branch exist and the two returned values are equal.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/lambert.cpp}
//! @}
//================================================================================================
inline constexpr auto lambert = functor<lambert_t>;
}

#include <eve/module/special/regular/impl/lambert.hpp>
