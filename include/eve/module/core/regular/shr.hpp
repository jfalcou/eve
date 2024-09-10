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
#include <eve/module/core/regular/if_else.hpp>

namespace eve
{
  template<typename Options>
  struct shr_t : strict_elementwise_callable<shr_t, Options>
  {
    template<integral_value T, integral_value S>
    EVE_FORCEINLINE constexpr as_wide_as_t<T, S> operator()(T t0, S s) const noexcept
      requires(eve::same_lanes_or_scalar<T, S>)
    {
      EVE_ASSERT(detail::assert_shift<T>(this->options(), s),
                 "[eve::shr] Shifting by " << s << " is out of the range [0, "
                 << sizeof(element_type_t<T>) * 8 << "[.");
      return EVE_DISPATCH_CALL(t0, s);
    }

    template<integral_value T, std::ptrdiff_t S>
    EVE_FORCEINLINE constexpr T operator()(T t0, index_t<S> s) const noexcept
    {
      constexpr int l = sizeof(element_type_t<T>) * 8;
      static_assert((S < l) && (S >= 0), "[eve::shr] Shift value is out of range.");

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
//!      // Regular overloads
//!      constexpr auto shr(integral_value auto x, integral_value auto n)              noexcept; // 1
//!      template< auto N >
//!      constexpr auto shr(integral_value auto x, index_t<N> auto n)                  noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto shr[conditional_expr auto c](/* any of the above overloads */) noexcept; // 3
//!      constexpr auto shr[logical_value auto m](/* any of the above overloads */)    noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::integral_value) to be shifted.
//!     * `n`: [shift](@ref eve::integral_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      1. The [elementwise](@ref glossary_elementwise) arithmetic right shift of the first
//!         parameter by the second one is returned. If `N`is the size in bits  of the element type of `x`, all
//!         [elements](@ref glossary_elementwise) of n must belong to the
//!         interval: `]0, N[` or the result is undefined.
//!      2. This call allows optimization for architectures that have an intrinsic requiring
//!         an immediate parameter
//!      3. [The operation is performed conditionnaly](@ref conditional)
//!
//!    @note
//!      Although the infix notation with `<<` is supported, the `<<` operator on
//!      standard scalar types is the original one and so can not be overloaded on standard floating
//!      parameters due to **C++** limitations.
//!    @warning
//!     The behavior of this function is undefined if the shift value is out of the range [0, N[, where
//!     N is the number of bits of the input type. Use [eve::rshr](@ref eve::rshr) for a relative right shift
//!     that accepts negative shift values.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/shr.cpp}
//================================================================================================
  inline constexpr auto shr = functor<shr_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, conditional_expr C, typename T, std::ptrdiff_t S>
    EVE_FORCEINLINE constexpr auto shr_(EVE_REQUIRES(cpu_), C const& cx, O const&, T a, index_t<S>) noexcept
    {
      return shr(a, if_else(cx, S, zero)); 
    }

    template<callable_options O, conditional_expr C, typename T, typename U>
    EVE_FORCEINLINE constexpr auto shr_(EVE_REQUIRES(cpu_), C const& cx, O const&, T a, U s) noexcept
    {
      return shr(a, if_else(cx, s, zero)); 
    }

    template<callable_options O, typename T, typename U>
    EVE_FORCEINLINE constexpr auto shr_(EVE_REQUIRES(cpu_), O const&, T const& a, U const& s) noexcept
    {
      // S >> S case: perform the operation using the default operator
      if constexpr (scalar_value<T> && scalar_value<U>) return static_cast<T>(a >> s);
      // S >> W case: broadcast the scalar & rerun
      else if constexpr (scalar_value<T>)               return shr(as_wide_as_t<T, U>{a}, s);
      // W >> S case: broadcast the scalar & rerun
      else if constexpr (scalar_value<U>)               return shr(a, as_wide_as_t<U, T>{s});
      // W >> W case: all backends rejected the op, generic fallback
      else                                              return map([]<typename V>(V v, auto b) { return static_cast<V>(v >> b); }, a, s);
    }

    template<callable_options O, typename T, std::ptrdiff_t S>
    EVE_FORCEINLINE constexpr auto shr_(EVE_REQUIRES(cpu_), O const&, T v, index_t<S> const&) noexcept
    {
      if constexpr (S == 0) return v;
      else                  return shr(v, S);
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/shr.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/shr.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/shr.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/shr.hpp>
#endif
