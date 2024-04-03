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
#include <eve/module/core/regular/is_eqz.hpp>

namespace eve
{
  template<typename Options>
  struct is_imag_t : elementwise_callable<is_imag_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_imag_t, is_imag_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_imag
//!   @brief Returns a logical true  if and only if the element value is imaginary.
//!
//!   For real entries 0 is the only imaginary number: its real part is 0!
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
//!      template< eve::floating_value T >
//!      eve::as_logical<T> is_imag(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    Returns [elementwise](@ref glossary_elementwise) `x == 0` for real entries.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_imag.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_imag[mask](x)` provides a masked version of `eve::is_imag` which is
//!     equivalent to `if_else (mask, is_imag(x), eve::false( eve::as(x)))`.
//!
//! @}
//================================================================================================
 inline constexpr auto is_imag = functor<is_imag_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_imag_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      return is_eqz(a);
    }
  }
}
