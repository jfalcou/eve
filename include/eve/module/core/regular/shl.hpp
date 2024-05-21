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
  struct shl_t : strict_elementwise_callable<shl_t, Options>
  {
    template<integral_value T0, integral_value N>
    EVE_FORCEINLINE constexpr as_wide_as_t<T0, N> operator()(T0 t0, N s) const noexcept
    {
      EVE_ASSERT(assert_good_shift<T>(s),
                 "[eve::shl] Shifting by " << s << " is out of the range [0, "
                 << sizeof(element_type_t<T>) * 8 << "[.");
      return EVE_DISPATCH_CALL(t0, s);
    }

    template<integral_value T0, std::ptrdiff_t N>
    EVE_FORCEINLINE constexpr T0 operator()(T0 t0, index_t<N> s) const noexcept
    {
      EVE_ASSERT(assert_good_shift<T>(s),
                 "[eve::shl] Shifting by " << s << " is out of the range [0, "
                 << sizeof(element_type_t<T>) * 8 << "[.");
      return EVE_DISPATCH_CALL(t0, s);
    }

    EVE_CALLABLE_OBJECT(shl_t, shl_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var shl
//!   @brief Computes the arithmetic left shift operation.
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
//!      template< eve::integral_value T , integral_value N >
//!      T shl(T x, N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::integral_value) to be shifted.
//!     * `n`:   [shift](@ref eve::integral_value).
//!
//!    **Return value**
//!
//!      The [elementwise](@ref glossary_elementwise) arithmetic left shift of the first
//!      parameter by the second one is returned.
//!
//!      The call `shl(x, n)` is equivalent to `x << n` if `x`  is an  [simd value](@ref
//!      eve::simd_value).
//!
//!      The types must share the same cardinal or be scalar and if `N` is the size in bits  of
//!      the element type of `T`, all  [elements](@ref glossary_elementwise) of n must belong to the
//!      interval: `[0, N[` or the result is undefined.
//!
//!    @note
//!     Although the infix notation with `<<` is supported, the `<<` operator on
//!     standard scalar types is the original one and so can not be overloaded on standard floating
//!     parameters due to **C++** limitations.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/shl.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::shl[mask](x, ...)` provides a masked
//!     version of `shl` which is
//!     equivalent to `if_else(mask, shl(x, ...), x)`
//!
//! @}
//================================================================================================
  inline constexpr auto shl = functor<shl_t>;

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    EVE_FORCEINLINE constexpr auto
    shl_(EVE_REQUIRES(cpu_), O const &, T const& a, U const& s) noexcept
    {
      if constexpr( scalar_value<T> && scalar_value<U> )
        return static_cast<T>(a << s);
      else if constexpr( scalar_value<T> )
        return as_wide_t<T, cardinal_t<U>>(a) << s;
      else
        return a << s;
    }

    template<typename T, std::ptrdiff_t S, callable_options O>
    EVE_FORCEINLINE constexpr auto
    shl_(EVE_REQUIRES(cpu_), O const &, T const& a, index_t<S> const& s) noexcept
    {
      return a << s;
    }
  }
}
