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
  struct prime_floor_t : strict_elementwise_callable<prime_floor_t, Options>
  {
    template<eve::unsigned_value T>
    constexpr EVE_FORCEINLINE
    T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    template<eve::integral_value T, floating_scalar_value U>
    EVE_FORCEINLINE constexpr eve::as_wide_as_t<U, T> operator()(T v, eve::as<U> target ) const noexcept
    {
      return EVE_DISPATCH_CALL(v, target);
    }

    template<eve::integral_value T, unsigned_scalar_value U>
    EVE_FORCEINLINE constexpr eve::as_wide_as_t<U, T> operator()(T v, eve::as<U> target ) const noexcept
    {
      return EVE_DISPATCH_CALL(v, target);
    }

    EVE_CALLABLE_OBJECT(prime_floor_t, prime_floor_);
  };

//================================================================================================
//! @addtogroup combinatorial
//! @{
//!   @var prime_floor
//!   @brief Returns the the greatest prime less or equal to the input.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/combinatorial.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::unsigned_value N >
//!      constexpr N prime_floor(N n) noexcept ;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  unsigned argument. If `n` is greater than 104'729, behavior is undefined.
//!
//!   **Return value**
//!   The greatest prime less or equal to `n`.
//!   The result type is the same as the input one unless a converter is applied (see below).
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/combinatorial/regular/prime_floor.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Optimized Conversion Call
//!
//!     The converters eve::float_,  eve::double_, eve::floating_ can be applied to
//!     produce a floating point output.
//!
//!    **Example**
//!
//!    @godbolt{doc/combinatorial/conversion/prime_floor.cpp}
//! @}
//================================================================================================
  inline constexpr auto prime_floor = functor<prime_floor_t>;

  namespace detail
  {
    template<unsigned_value T, callable_options O>
    constexpr EVE_FORCEINLINE T
    prime_floor_(EVE_REQUIRES(cpu_), O const&, T n) noexcept
    {
      using elt_t = element_type_t<T>;

      auto constexpr maxi =
        (sizeof(elt_t) == 1) ? (53u) : ((sizeof(elt_t) == 2) ? (6541u) : (10000u));
      auto constexpr next =
        (sizeof(elt_t) == 1) ? (255u) : ((sizeof(elt_t) == 2) ? (65535u) : (104742u));
      auto first = T(0);
      auto last  = T(maxi);
      while( eve::any(inc(first) < last) )
      {
        auto mid  = average(first, last);
        auto pmid = convert(nth_prime(mid), as<elt_t>());
        auto test = pmid <= n;
        first     = if_else(test, mid, first);
        last      = if_else(test, last, mid);
      }
      auto z = nth_prime(first);
      z      = if_else(
        (((last == T(maxi)) && (n < T(next))) || (first < T(maxi - 1))) && (n >= 2), z, zero);
      return z;
    }

    template<unsigned_value T,  unsigned_scalar_value U, callable_options O>
    constexpr EVE_FORCEINLINE auto
    prime_floor_(EVE_REQUIRES(cpu_), O const&, T n, as<U> const & target) noexcept
    {
      return convert(prime_floor(uint32(n)), target);
    }

    template<unsigned_value T,  floating_scalar_value U, callable_options O>
    constexpr EVE_FORCEINLINE auto
    prime_floor_(EVE_REQUIRES(cpu_), O const&, T n, as<U> const & target) noexcept
    {
      auto r = convert(prime_floor(uint32(n)), target);
      return if_else(is_eqz(r), allbits, r);
    }
  }
}
