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

namespace eve
{
  template<typename Options>
  struct gcd_t : elementwise_callable<gcd_t, Options, raw_option>
  {
    template<value T, value U>
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T v, U w) const noexcept
      requires (same_lanes_or_scalar<T, U>)
    {
      return this->behavior(as<common_value_t<T, U>>{}, eve::current_api, this->options(), v, w);
    }

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
  //!      template <value T0, value T1> constexpr common_value_t<T0, T1> gcd(T0 p, T1 n) noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto gcd[conditional_expr auto c](value auto p, value auto n)        noexcept; // 2
  //!      constexpr auto gcd[logical_value auto m](value auto p, value auto n)           noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `p`, `n`: [values](@ref value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //!    **Return value**
  //!
  //!      1. If both p and n are zero, returns zero. Otherwise, returns the greatest common divisor of |p|
  //!         and |n|.
  //!      2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!    @warning  `p` and `n` can be of any [values](@ref eve::value) type, but when the types are not
  //!      integral the greatest common divisor is defined only if `p` and `n` elements are
  //!      [flint](@ref eve::is_flint). If any of the arguments is not flint the result is undefined.
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
    template<callable_options O, typename T>
    constexpr auto gcd_(EVE_REQUIRES(cpu_), O const&, T a, T b)
    {
      a = eve::abs(a);
      b = eve::abs(b);
      if constexpr(O::contains(raw))
      {
        if constexpr (scalar_value<T>)
        {
          while( b )
          {
            auto r = rem(a, b);
            a      = b;
            b      = r;
          }
          return a;
        }
        else
        {
          auto test = is_nez(b);
          T    r(0);
          while (eve::any(test))
          {
            r    = rem(a, b);
            a    = if_else(test, b, a);
            test = is_nez(r) && test;
            b    = r;
          }
          return a;
        }
      }
      else
      {
        if constexpr (integral_scalar_value<T>)
        {
          while( b )
          {
            auto r = a % b;
            a      = b;
            b      = r;
          }
          return a;
        }
        else if constexpr (integral_simd_value<T>)
        {
          using elt_t = element_type_t<T>;
          if constexpr (sizeof(elt_t) == 8)
          {
            auto test = is_nez(b);
            T    r(0);
            while( eve::any(test) )
            {
              b    = if_else(test, b, allbits);
              r    = a % b;
              a    = if_else(test, b, a);
              test = test && is_nez(r);
              b    = r;
            }
            return a;
          }
          else
          {
            if constexpr (sizeof(elt_t) == 4)
            {
              auto r = gcd[raw](convert(a, as<double>()), convert(b, as<double>()));
              if constexpr( std::is_signed_v<elt_t> ) return convert(r, int_from<T>());
              else                                    return convert(r, uint_from<T>());
            }
            else if constexpr (sizeof(elt_t) <= 2)
            {
              auto r = gcd[raw](convert(a, as<float>()), convert(b, as<float>()));
              if constexpr( std::is_signed_v<elt_t> ) return convert(r, int_from<T>());
              else                                    return convert(r, uint_from<T>());
            }
          }
        }
        else if constexpr (floating_value<T>)
        {
          EVE_ASSERT(eve::all(is_flint(a) && is_flint(b)), "gcd: some entries are not flint");
          if constexpr (scalar_value<T>)
          {
            while( b )
            {
              auto r = rem(a, b);
              a      = b;
              b      = r;
            }
            return a;
          }
          else
          {
            auto test = is_nez(b);
            T    r(0);
            while (eve::any(test))
            {
              r    = rem(a, b);
              a    = if_else(test, b, a);
              test = is_nez(r) && test;
              b    = r;
            }
            return a;
          }
        }
      }
    }
  }
}
