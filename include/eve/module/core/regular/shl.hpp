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
  struct shl_t : strict_elementwise_callable<shl_t, Options>
  {
    template<integral_value T, integral_value N>
    requires(eve::same_lanes_or_scalar<T, N>)
    EVE_FORCEINLINE constexpr as_wide_as_t<T, N> operator()(T t0, N s) const noexcept
    {
      EVE_ASSERT(detail::assert_good_shift<T>(s),
                 "[eve::shl] Shifting by " << s << " is out of the range [0, "
                 << sizeof(element_type_t<T>) * 8 << "[.");
      return EVE_DISPATCH_CALL(t0, s);
    }

    template<integral_value T, std::ptrdiff_t N>
    EVE_FORCEINLINE constexpr T operator()(T t0, index_t<N> s) const noexcept
    {
      EVE_ASSERT(detail::assert_good_shift<T>(s),
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
//!      constexpr auto shl(integral_value auto x, integral_value auto n)              noexcept; // 1
//!      template< auto N >
//!      constexpr auto shl(integral_value auto x, index_t<N> auto n)                  noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto shl[conditional_expr auto c](/* any of the above overloads */) noexcept; // 3
//!      constexpr auto shl[logical_value auto m](/* any of the above overloads */)    noexcept; // 3
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
//!      1. The [elementwise](@ref glossary_elementwise) arithmetic left shift of the first
//!         parameter by the second one is returned. If `N`is the size in bits  of the element type of `x`, all
//!         [elements](@ref glossary_elementwise) of n must belong to the
//!         interval: `]0, N[` or the result is undefined.
//!      2. This call allows optimization for architectures that have an intrinsic requiring
//!         an immediate parameter
//!      3. [The operation is performed conditionnaly](@ref conditional)
//!
//!    @note
//!     Although the infix notation with `<<` is supported, the `<<` operator on
//!     standard scalar types is the original one and so can not be overloaded on standard floating
//!     parameters due to **C++** limitations.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/shl.cpp}
//================================================================================================
  inline constexpr auto shl = functor<shl_t>;
//================================================================================================
//! @}
//================================================================================================

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

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/shl.hpp>
#endif

#if defined(EVE_INCLUDE_RISCV_HEADER)
#  include <eve/module/core/regular/impl/simd/riscv/shl.hpp>
#endif
