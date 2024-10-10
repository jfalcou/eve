//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/common_value.hpp>
#include <eve/concept/properly_convertible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/fma.hpp>

namespace eve::detail
{
  template<typename T, typename U, typename V, callable_options O>
  EVE_FORCEINLINE constexpr auto fam_(EVE_REQUIRES(cpu_), O const& o, T const& a, U const& b, V const& c)
  {
     // PROMOTE ---------------------
    if constexpr(O::contains(promote))
    {
     using er_t = common_type_t<element_type_t<T>, element_type_t<U>, element_type_t<V>>;
      constexpr auto tgt = as{as<er_t>{}};
      return fam[o.drop(promote)](convert(a, tgt), convert(b, tgt), convert(c,tgt));
    }
    // OTHERS ---------------------
    else
    {
      using r_t = common_value_t<T, U, V>;
      return fam[o](r_t(a), r_t(b), r_t(c));
    }
  }

  // PROMOTE may mix values of different types, making automatic masking from the default behaviors unwieldy
  // We catch the mask + PROMOTE case and handle it properly
  // No special provision is made for PEDANTIC as it is handled in the second pass without issues.
  template<typename T, typename U, typename V, conditional_expr C, callable_options O>
  EVE_FORCEINLINE constexpr auto
  fam_(EVE_REQUIRES(cpu_), C const& mask, O const& o, T const& a, U const& b, V const& c)
  {
    // PROMOTE ---------------------
    if constexpr(O::contains(promote))
    {
      using er_t = common_type_t<element_type_t<T>, element_type_t<U>, element_type_t<V>>;
      constexpr auto tgt = as{as<er_t>{}};

      return fam[o.drop(promote)](convert(a, tgt), convert(b, tgt), convert(c,tgt));
    }
    // OTHERS ---------------------
    else
    {
      using r_t = common_value_t<T, U, V>;
      // Drop the mask key to prevent circular calls
      auto opt = o.drop(condition_key);
      return detail::mask_op(mask, detail::return_2nd, r_t(a), fam[opt](r_t(a), r_t(b), r_t(c)));
    }
  }

  template<callable_options O, typename T>
  EVE_FORCEINLINE constexpr auto fam_(EVE_REQUIRES(cpu_), O const& o, T const& a, T const& b, T const& c)
  {
    // PROMOTE ---------------------
    // We promote before going pedantic in case it changes the behavior
    if constexpr(O::contains(promote)) return fam[o.drop(promote)](a,b,c);
    // PEDANTIC ---------------------
    else if constexpr(O::contains(pedantic))
    {
      if constexpr( std::same_as<element_type_t<T>, float> )
      {
        constexpr auto tgt = as<double>{};
        return convert(convert(a,tgt) + convert(b,tgt) * convert(c,tgt), as_element(a));
      }
      else if constexpr( std::same_as<element_type_t<T>, double> )
      {
        if constexpr(scalar_value<T>)
        {
          return std::fma(c, b, a);
        }
        else
        {
          auto stdfam = [](auto x, auto y, auto z){
            return std::fma(y, z, x);
          };
          return map(stdfam, a, b, c);
        }
      }
      else if constexpr( std::is_integral_v<element_type_t<T>> )
      {
        // Pedantic fam has to ensure "no intermediate overflow".
        // This is done in the case of signed integers by trans-typing to unsigned type
        // to perform the computations in a guarantee 2-complement environment
        // since signed integer overflows in C++ produce "undefined results"
        constexpr auto tgt = as<as_integer_t<T, unsigned>>{};
        return bit_cast(fam(bit_cast(a,tgt), bit_cast(b,tgt), bit_cast(c,tgt)), as<T>{});
      }
      else
      {
        return fam(a, b, c);
      }
    }
    // REGULAR UPPER LOWER---------------------
    else
      return fma[o](b, c, a);
  }
}
