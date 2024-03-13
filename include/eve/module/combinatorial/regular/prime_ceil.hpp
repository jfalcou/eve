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
#include <eve/module/combinatorial/regular/nth_prime.hpp>
#include <eve/module/core.hpp>

namespace eve
{
  template<typename Options>
  struct prime_ceil_t : elementwise_callable<prime_ceil_t, Options>
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

    EVE_CALLABLE_OBJECT(prime_ceil_t, prime_ceil_);
  };

//================================================================================================
//! @addtogroup combinatorial
//! @{
//!   @var prime_ceil
//!   @brief Returns the smallest prime greater or equal to the input.
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
//!      constexpr N prime_ceil(N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  unsigned argument. If `n` is greater than 104'729, behavior is undefined.
//!
//!   **Return value**
//!   The smallest prime greater or equal to `n`.
//!   The result type is the same as the input one unless a converter is applied (see below).
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/combinatorial/regular/prime_ceil.cpp}
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
//!    @godbolt{doc/combinatorial/conversion/prime_ceil.cpp}
//! @}
//================================================================================================
  inline constexpr auto prime_ceil = functor<prime_ceil_t>;

  namespace detail
  {
    template<unsigned_value T, callable_options O>
    constexpr EVE_FORCEINLINE T
    prime_ceil_(EVE_REQUIRES(cpu_), O const&, T n)
    {
      using elt_t = element_type_t<T>;
      n           = if_else(is_eqz(n), T(2), n);
      auto max_n  = (sizeof(elt_t) == 1) ? T(53) : (sizeof(elt_t) == 2 ? T(6541) : T(9999));
      if constexpr( has_native_abi_v<T> )
      {
        auto first  = T(0);
        auto last   = max_n;
        auto toobig = n > nth_prime(max_n);
        n           = if_else(toobig, zero, n);
        while( eve::any(inc(first) < last) )
        {
          T    mid  = average(first, last);
          auto pmid = nth_prime(mid);
          auto test = pmid >= n;
          last      = if_else(test, mid, last);
          first     = if_else(test, first, mid);
        }
        auto tmp = nth_prime(first);
        auto t   = tmp >= n;
        return if_else(toobig, zero, if_else(t, tmp, nth_prime(last)));
      }
      else return apply_over(prime_ceil, n);
    }

    template<unsigned_value T,  unsigned_scalar_value U, callable_options O>
    constexpr EVE_FORCEINLINE auto
    prime_ceil_(EVE_REQUIRES(cpu_), O const&, T n, as<U> const & target) noexcept
    {
      return convert(prime_ceil(uint32(n)), target);
    }

    template<unsigned_value T,  floating_scalar_value U, callable_options O>
    constexpr EVE_FORCEINLINE auto
    prime_ceil_(EVE_REQUIRES(cpu_), O const&, T n, as<U> const & target) noexcept
    {
      auto r = convert(prime_ceil(uint32(n)), target);
      return if_else(is_eqz(r), allbits, r);
    }
  }
}
