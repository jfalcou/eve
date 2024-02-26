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
  struct factorial_t : elementwise_callable<factorial_t, Options>
  {
    template<eve::integral_value T>
    EVE_FORCEINLINE constexpr
    as_wide_as_t<double, T >
    operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE constexpr
    T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(factorial_t, factorial_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var factorial
//!   @brief Computes \f$\displaystyle n! = \prod_{i=1}^n i\f$.
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
//!      template< eve::integral_value N >
//!      as_wide_as<N, double> factorial(N x) noexcept;
//!
//!      template< eve::floating_ordered_value T >
//!      T factorial(N x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  must be of integral type or flint.
//!
//!   **Return value**
//!
//!  The value of \f$ n!\f$ is returned.
//!
//!  @warning
//!    This function will overflow as soon as the input is greater than 171 for integral or double
//!    entries and if the entry is greater than 34 for float.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/factorial.cpp}
//! @}
//================================================================================================
inline constexpr auto factorial = functor<factorial_t>;
}

#include <eve/module/special/regular/impl/factorial.hpp>
