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
#include <eve/detail/assert_utils.hpp>

namespace eve
{
  template<typename Options>
  struct shr_t : strict_elementwise_callable<shr_t, Options>
  {
    template<integral_value T, integral_value N>
    requires(eve::same_lanes_or_scalar<T, N>)
    EVE_FORCEINLINE constexpr as_wide_as_t<T, N> operator()(T t0, N s) const noexcept
    {
      EVE_ASSERT(detail::assert_good_shift<T>(s),
                 "[eve::shr] Shifting by " << s << " is out of the range [0, "
                 << sizeof(element_type_t<T>) * 8 << "[.");
      return EVE_DISPATCH_CALL(t0, s);
    }

    template<integral_value T, std::ptrdiff_t S>
    EVE_FORCEINLINE constexpr T operator()(T t0, index_t<S> s) const noexcept
    {
      EVE_ASSERT(detail::assert_good_shift<T>(s),
                 "[eve::shr] Shifting by " << S << " is out of the range [0, "
                 << sizeof(element_type_t<T>) * 8 << "[.");
      return EVE_DISPATCH_CALL(t0, s);
    }

    EVE_CALLABLE_OBJECT(shr_t, shr_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var shr
//!   @brief Computes the arithmetic right shift operation.
//!
//!   @groupheader{Header file}
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
//!      template< eve::value T , integral_value N >
//!      T shr(T x, N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value) to be shifted.
//!
//!     * `n`:   [shift](@ref eve::integral_value).
//!
//!    **Return value**
//!
//!      The [elementwise](@ref glossary_elementwise) arithmetic right shift of the first
//!         parameter by the second one is returned.
//!
//!      The call `shr(x, n)` is equivalent to `x << n` if `x`  is an  [simd value](@ref
//!          eve::simd_value).
//!
//!      The types must share the same cardinal or be scalar and if `N` is the size in bits  of
//!      the element type of `T`, all  [elements](@ref glossary_elementwise) of n must belong to the
//!      interval: `[0, N[` or the result is undefined.
//!
//!    @note
//!      Although the infix notation with `<<` is supported, the `<<` operator on
//!      standard scalar types is the original one and so can not be overloaded on standard floating
//!      parameters due to **C++** limitations.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/shr.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::shr[mask](x, ...)` provides a masked
//!     version of `shr` which is
//!     equivalent to `if_else(mask, shr(x, ...), x)`
//!
//! @}
//================================================================================================
  inline constexpr auto shr = functor<shr_t>;

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    EVE_FORCEINLINE constexpr auto
    shr_(EVE_REQUIRES(cpu_), O const &, T const& a, U const& s) noexcept
    {
      if constexpr( scalar_value<T> && scalar_value<U> )
        return static_cast<T>(a >> s);
      else if constexpr( scalar_value<T> )
        return as_wide_t<T, cardinal_t<U>>(a) >> s;
      else
        return a >> s;
    }

    template<typename T, std::ptrdiff_t S, callable_options O>
    EVE_FORCEINLINE constexpr auto
    shr_(EVE_REQUIRES(cpu_), O const &, T const& a, index_t<S> const& s) noexcept
    {
      return a >> s;
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/shr.hpp>
#endif
