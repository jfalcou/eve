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
#include <eve/as_element.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core.hpp>
#include <numeric>

namespace eve
{
template<typename Options>
struct gcd_t : elementwise_callable<gcd_t, Options>
{
  template<eve::value T, value U>
  requires (same_lanes_or_scalar<T, U>)
  constexpr EVE_FORCEINLINE
  common_value_t<T, U> operator()(T v, U w) const noexcept
  { return EVE_DISPATCH_CALL(v, w); }

  EVE_CALLABLE_OBJECT(gcd_t, gcd_);
};

//================================================================================================
//! @addtogroup combinatorial
//! @{
//!   @var gcd
//!   @brief `elementwise_callable` object computing the greatest common divisor of the inputs.
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
//!      // Regular overload
//!      template <integral_value T0, integral_value T1> constexpr common_value_t<T0, T1> gcd(T0 p, T1 n) noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto gcd[conditional_expr auto c](integral_value auto p, integral_value auto n)        noexcept; // 2
//!      constexpr auto gcd[logical_value auto m](integral_value auto p, integral_value auto n)           noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `p`, `n`: [integral values](@ref eve::integral_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!      1. If both p and n are zero, returns zero. Otherwise, returns the greatest common divisor of |p|
//!         and |n|.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wikipedia: Least common multiple](https://en.wikipedia.org/wiki/Greatest_common_divisor)
//!   *  [C++ standard reference: lcm](https://en.cppreference.com/w/cpp/numeric/gcd)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/combinatorial/gcd.cpp}
//================================================================================================
  inline constexpr auto gcd = functor<gcd_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr auto gcd_(EVE_REQUIRES(cpu_), O const&, T a, T b)
    {
      a = eve::abs(a);
      b = eve::abs(b);
      auto internal_gcd = []( auto aa,  auto bb)
      {
        using r_t =  decltype(aa);
        auto test = is_nez(bb);
        r_t r(0);
        while( eve::any(test) )
        {
          if constexpr(integral_value<r_t>)
          {
            bb  = if_else(test, bb, allbits);
          }
          r = rem(aa, bb);
          if constexpr(scalar_value<r_t>)
          {
            aa = bb;
            test = is_nez(r);
          }
          else
          {
            aa = if_else(test, bb, aa);
            test = is_nez(r) && test;
          }
          bb = r;
        }
        return aa;
      };

      if constexpr(integral_scalar_value<T>)
      {
        return std::gcd(a, b);
      }
      else
      {
        using elt_t = element_type_t<T>;
        if constexpr(  floating_value<T> || (sizeof(elt_t) == 8))
        {
          return internal_gcd(a, b);
        }
        else
        {
          if constexpr( sizeof(elt_t) == 4 )
          {
            auto r = internal_gcd(convert(a, as<double>()), convert(b, as<double>()));
            if constexpr( std::is_signed_v<elt_t> ) return convert(r, int_from<T>());
            else                                    return convert(r, uint_from<T>());
          }
          else if constexpr( sizeof(elt_t) <= 2 )
          {
            auto r = internal_gcd(convert(a, as<float>()), convert(b, as<float>()));
            if constexpr( std::is_signed_v<elt_t> ) return convert(r, int_from<T>());
            else                                    return convert(r, uint_from<T>());
          }
        }
      }
    }
  }
}
