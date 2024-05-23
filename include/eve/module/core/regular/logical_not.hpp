//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/traits/as_logical.hpp>


namespace eve
{
  template<typename Options>
  struct logical_not_t : elementwise_callable<logical_not_t, Options>
  {
    template<logical_value T>
    constexpr EVE_FORCEINLINE auto operator()(T a) const  noexcept -> as_logical_t<decltype(!a)>
    { return EVE_DISPATCH_CALL(a); }

    constexpr EVE_FORCEINLINE bool operator()(bool a) const  noexcept
    { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(logical_not_t, logical_not_);
  };

//================================================================================================
//! @addtogroup core_logical
//! @{
//!   @var logical_not
//!   @brief Computes the logical NOT of its argument.
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
//!      template< eve::value T >
//!      eve::as_logical_t<T> logical_or(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!     The call `logical_not(x)` is semantically equivalent to `is_eqz(x)`.
//!     Infix notation can be used with `!x`.
//!
//!    @note
//!      Although the infix notation with `!` is supported, the `!` operator on
//!      standard scalar types is the original one and so will return bool instead of
//!      eve::logical_value.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/logical_not.cpp}
//! @}
//================================================================================================
  inline constexpr auto logical_not = functor<logical_not_t>;

  namespace detail
  {
    template<value T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    logical_not_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      return as_logical_t<T>(!a);
    }

    template<callable_options O>
    EVE_FORCEINLINE constexpr auto
    logical_not_(EVE_REQUIRES(cpu_), O const &, bool a) noexcept
    {
      return !a;
    }
  }
}
