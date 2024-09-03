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
#include <eve/traits/bit_value.hpp>
#include <eve/module/core/regular/is_equal.hpp>


namespace eve
{
  template<typename Options>
  struct is_bit_equal_t : strict_elementwise_callable<is_bit_equal_t, Options>
  {
    template <typename T, typename U > using  b_t = bit_value_t<T, U>;
    template <typename T, typename U > using  ui_t = as_integer_t<b_t<T, U>, unsigned>;

    template<value T, value U>
    constexpr EVE_FORCEINLINE auto  operator()(T a, U b)  const
      -> decltype(is_equal(bit_cast(b_t<T, U>(a), as<ui_t<T, U>>()), bit_cast(b_t<T, U>(b), as<ui_t<T, U>>())))
    {
      return EVE_DISPATCH_CALL(a, b);
    }

    template<value T, value U>
    constexpr EVE_FORCEINLINE auto  operator()(logical<T> a, logical<U> b)  const
      -> decltype(is_equal(a, b))
    {
      return EVE_DISPATCH_CALL(a, b);
    }

    EVE_CALLABLE_OBJECT(is_bit_equal_t, is_bit_equal_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_bit_equal
//!   @brief `elementwise callable` returning a logical true  if and only if the element bits
//!   are all equal.
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
//!      // Regular overload
//!      constexpr auto is_bit_equal(value auto x, value auto y) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_bit_equal[conditional_expr auto c](value auto x, value auto y) noexcept; // 2
//!      constexpr auto is_bit_equal[logical_value auto m](value auto x, value auto y) noexcept;    // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!      1. Returns the logical value containing the [elementwise](@ref glossary_elementwise) bit equality
//!        test result between `x` and `y`.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_bit_equal.cpp}
//================================================================================================
  inline constexpr auto is_bit_equal = functor<is_bit_equal_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    EVE_FORCEINLINE constexpr auto
    is_bit_equal_(EVE_REQUIRES(cpu_),O const & o, T const& a, U const& b) noexcept
    {
      using b_t =  bit_value_t<T, U>;
      using ui_t = as_integer_t<b_t, unsigned>;
      return is_equal(bit_cast(b_t(a), as<ui_t>()), bit_cast(b_t(b), as<ui_t>()));
    }

    template<typename T, typename U, callable_options O>
    EVE_FORCEINLINE constexpr auto
    is_bit_equal_(EVE_REQUIRES(cpu_),O const & o, logical<T> const& a, logical<U> const& b) noexcept
    {
      return is_equal(a, b);
    }
  }
}
