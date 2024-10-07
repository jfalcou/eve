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
#include <eve/module/core/constant/false.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/bit_cast.hpp>

namespace eve
{
  template<typename Options>
  struct logical_xor_t : strict_elementwise_callable<logical_xor_t, Options>
  {
    template<logical_value T, logical_value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE auto operator()(T a, U b) const noexcept -> decltype(logical_and(a, b))
    { return EVE_DISPATCH_CALL_PT((decltype(logical_and(a, b))), a, b); }

    template<logical_value U>
    constexpr EVE_FORCEINLINE U operator()(bool a, U b) const noexcept
    { return EVE_DISPATCH_CALL_PT(U, a, b); }

    template<logical_value T>
    constexpr EVE_FORCEINLINE T operator()(T a, bool b) const noexcept
    { return EVE_DISPATCH_CALL_PT(T, a, b); }

    constexpr EVE_FORCEINLINE bool operator()(bool a, bool b) const noexcept
    { return EVE_DISPATCH_CALL_PT(bool, a, b); }

    EVE_CALLABLE_OBJECT(logical_xor_t, logical_xor_);
  };

//================================================================================================
//! @addtogroup core_logical
//! @{
//!   @var logical_xor
//!   @brief Computes the logical XOR of its arguments.
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
//!      constexpr auto logical_xor(auto logical_value x, auto logical_value y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::logical_value).
//!
//!    **Return value**
//!
//!      Returns the logical XOR of the two parameters following the
//!      [logical operations semantic](@ref glossary_logical).
//!
//!      The call `logical_xor(x, y)` is semantically equivalent to `(x && !y) || (!x && y)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/logical_or.cpp}
//================================================================================================
  inline constexpr auto logical_xor = functor<logical_xor_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T, typename U>
    EVE_FORCEINLINE auto logical_xor_(EVE_REQUIRES(cpu_),
                                      O const & ,
                                      logical<T> const& a,
                                      logical<U> const& b) noexcept
    {
      constexpr auto scT =  scalar_value<T>;
      constexpr auto scU =  scalar_value<U>;
      if constexpr(scT && scU)
        return as_logical_t<T> {a.value() != b.value()};
      else if  constexpr(scT && !scU)
       return logical_xor(b, as_logical_t<U>(a.value()));
      else if  constexpr(!scT && scU)
       return logical_xor(a, as_logical_t<T>(b.value()));
      else if constexpr(cardinal_v<T> == cardinal_v<U>)
      {
        return bit_cast ( a.bits() != convert(b, as<logical<element_type_t<T>>>()).bits()
                        , as<logical<T>>()
                        );
      }
    }

    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr
    auto logical_xor_(EVE_REQUIRES(cpu_), O const & , T a, bool b) noexcept
    {
      return T(b) !=  a;
    }

    template<typename U, callable_options O>
    EVE_FORCEINLINE constexpr
    auto logical_xor_(EVE_REQUIRES(cpu_), O const & , bool a, U b) noexcept
    {
      return U(a) !=  b;
    }

    template<callable_options O>
    EVE_FORCEINLINE constexpr
    auto logical_xor_(EVE_REQUIRES(cpu_), O const & , bool a, bool b) noexcept
    {
      return a!=b;
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/logical_xor.hpp>
#endif
