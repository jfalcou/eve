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
  struct prime_ceil_t : strict_elementwise_callable<prime_ceil_t, Options>
  {
    template<unsigned_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    {
      return EVE_DISPATCH_CALL_PT(T, v);
    }

    template<unsigned_value T, floating_scalar_value U>
    EVE_FORCEINLINE constexpr as_wide_as_t<U, T> operator()(T v, as<U> target) const noexcept
    {
      return EVE_DISPATCH_CALL_PT((as_wide_as_t<U, T>), v, target);
    }

    template<unsigned_value T, unsigned_scalar_value U>
    EVE_FORCEINLINE constexpr as_wide_as_t<U, T> operator()(T v, as<U> target) const noexcept
    {
      return EVE_DISPATCH_CALL_PT((as_wide_as_t<U, T>), v, target);
    }

    EVE_CALLABLE_OBJECT(prime_ceil_t, prime_ceil_);
  };

  //================================================================================================
  //! @addtogroup combinatorial
  //! @{
  //!   @var prime_ceil
  //!   @brief `strict_elementwise_callable` object computing the smallest prime greater or equal to the input.
  //!
  //!   @groupheader{Header file}
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
  //!      constexpr auto prime_floor(unsigned_value auto x) -> decltype(x) noexcept; //1
  //!      template < integral_value T,  floating_scalar_value U>
  //!      constexpr as_wide_as_t<U, T> prime_floor(T x, as<U>)             noexcept; //2
  //!      template < integral_value T,  unsigned_scalar_value U>
  //!      constexpr as_wide_as_t<U, T> prime_floor(T x, as<U>)             noexcept; //2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `n`: unsigned argument. If `n` is greater than 104'729, returns 0.
  //!
  //!   **Return value**
  //!
  //!     1. The smallest prime greater or equal to `n`.
  //!     2. Same, but the element type of the result is deduced from U.
  //!
  //!  @groupheader{External references}
  //!   *  [Wikipedia: Prime number](https://en.wikipedia.org/wiki/Prime_number)
  //!
  //!   @groupheader{Example}
  //!   @godbolt{doc/combinatorial/prime_ceil.cpp}
  //================================================================================================
  inline constexpr auto prime_ceil = functor<prime_ceil_t>;
  //================================================================================================
  //! @}
  //================================================================================================

  namespace detail
  {
    template<callable_options O, unsigned_value T>
    constexpr EVE_FORCEINLINE T prime_ceil_(EVE_REQUIRES(cpu_), O const&, T n)
    {
      using elt_t = element_type_t<T>;
      n           = if_else(is_eqz(n), T(2), n);
      auto max_n  = (sizeof(elt_t) == 1) ? T(53) : (sizeof(elt_t) == 2 ? T(6541) : T(9999));

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

    template<unsigned_value T,  unsigned_scalar_value U, callable_options O>
    constexpr EVE_FORCEINLINE auto
    prime_ceil_(EVE_REQUIRES(cpu_), O const&, T n, as<U> const & target) noexcept
    {
      return convert(prime_ceil(convert(n, as<uint32_t>())), target);
    }

    template<unsigned_value T,  floating_scalar_value U, callable_options O>
    constexpr EVE_FORCEINLINE auto
    prime_ceil_(EVE_REQUIRES(cpu_), O const&, T n, as<U> const & target) noexcept
    {
      auto r = convert(prime_ceil(convert(n, as<uint32_t>())), target);
      return if_else(is_eqz(r), allbits, r);
    }
  }
}
