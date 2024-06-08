//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/regular/expx2.hpp>

namespace eve
{

  template<typename Options>
  struct expmx2_t : elementwise_callable<expmx2_t, Options>
  {
    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(expmx2_t, expmx2_);
  };
//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var expmx2
//!
//! @brief Callable object computing \f$e^{-x^2}\f$.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< value T>
//!      T expmx2(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!
//! **Parameters**
//!
//!    `x`:   [floating real value](@ref eve::value).
//!
//! **Return value**
//!
//!   Returns the [elementwise](@ref glossary_elementwise) exponential of minus the square of `x`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/expmx2.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::expmx2[mask](x, ...)` provides a masked version of `eve::expmx2` which is
//!     equivalent to `if_else (mask, expmx2(x, ...), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/math/masked/expmx2.cpp}
//!  @}
//================================================================================================
  inline constexpr auto expmx2 = functor<expmx2_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    expmx2_(EVE_REQUIRES(cpu_), O const&, T a0) noexcept
    {
      if constexpr( has_native_abi_v<T> )
        return rec[pedantic2](eve::expx2(a0));
      else
        return apply_over(expmx2, a0);
    }
  }
}
