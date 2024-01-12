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
  struct lfactorial_t : elementwise_callable<lfactorial_t, Options>
  {
    template<eve::integral_value T>
    EVE_FORCEINLINE
    as_wide_as_t<double, T >
    operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE
    T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(lfactorial_t, lfactorial_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var lfactorial
//!   @brief Computes the natural logarithm of the factorial of unsigned integer values
//!   \f$\displaystyle \log n! = \sum_{i=1}^n \log i\f$.
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
//!      template< eve::ordered_value N >
//!      auto lfactorial(N x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [integer or flint argument](@ref eve::ordered_value).
//!
//!   **Return value**
//!
//!   The value of \f$ \log n!\f$ is returned with the following considerations:
//!     * If the entry is an [integral value](eve::integral_value), the result
//!       [element type](eve::element_type) is always double to try to avoid overflow.
//!     * If the entry is a [floating point value](eve::floating_point_value)
//!       which must be a flint,  the result is of the same type as the entry.
//!     * If `n` elements are nor integer nor flint the result is undefined.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/lfactorial.cpp}
//! @}
//================================================================================================
inline constexpr auto lfactorial = functor<lfactorial_t>;
}

#include <eve/module/special/regular/impl/lfactorial.hpp>
