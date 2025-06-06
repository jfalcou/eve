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
#include <eve/traits/as_logical.hpp>
#include <eve/module/core/regular/bit_cast.hpp>

namespace eve
{
  template<typename Options>
  struct logical_not_t : strict_elementwise_callable<logical_not_t, Options>
  {
    template<value T>
    constexpr EVE_FORCEINLINE as_logical_t<T> operator()(T a) const noexcept
    {
      return EVE_DISPATCH_CALL(a);
    }

    constexpr EVE_FORCEINLINE bool operator()(bool a) const noexcept
    {
      return !a;
    }

    EVE_CALLABLE_OBJECT(logical_not_t, logical_not_);
  };

//================================================================================================
//! @addtogroup core_logical
//! @{
//!   @var logical_not
//!   @brief Computes the logical NOT of its argument.
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
//!      constexpr auto logical_not(auto logical_value x) noexcept;
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
//================================================================================================
  inline constexpr auto logical_not = functor<logical_not_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<value T, callable_options O>
    EVE_FORCEINLINE constexpr auto logical_not_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
      requires has_native_abi_v<T>
    {
      if      constexpr (scalar_value<T>)    return as_logical_t<T>(!a);
      else if constexpr (logical_value<T>)   return bit_cast(~(a.bits()), as{a});
      else                                   return !to_logical(a);
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/logical_not.hpp>
#endif

#if defined(EVE_INCLUDE_RISCV_HEADER)
#  include <eve/module/core/regular/impl/simd/riscv/logical_not.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/logical_not.hpp>
#endif
