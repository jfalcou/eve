//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/generator.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/bit_andnot.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/bit_ornot.hpp>
#include <eve/function/bit_select.hpp>
#include <eve/function/minus.hpp>
#include <eve/function/convert.hpp>
#include <eve/traits/common_compatible.hpp>

namespace eve::detail
{
  // Local helper for product_type if_else implementation
  template<typename T, kumi::product_type U, kumi::product_type V>
  EVE_FORCEINLINE auto tuple_select(T const& cond, U const& t, V const& f )
  {
    using r_t = std::conditional_t< simd_value<U>, U, V>;
    return r_t{ kumi::map([&](auto const& v, auto const& f) { return if_else(cond,v,f); }, t, f) };
  }

  template<scalar_value T, value U, value V>
  EVE_FORCEINLINE auto if_else_(EVE_SUPPORTS(cpu_), T const & cond, U const & t, V const & f )
  requires compatible_values<U, V>
  {
          if constexpr(simd_value<U> && simd_value<V>)  return  cond ? t : f;
    else  if constexpr(simd_value<U>)                   return  cond ? t : U(f);
    else  if constexpr(simd_value<V>)                   return  cond ? V(t) : f;
    else                                                return  cond ? t : f;
  }

  template<simd_value T, value U, value V>
  EVE_FORCEINLINE auto if_else_(EVE_SUPPORTS(cpu_), T const & cond, U const & t, V const & f )
  requires compatible_values<U, V>
  {
    if constexpr( !is_logical_v<T> )
    {
      return if_else(to_logical(cond),t,f);
    }
    else
    {
      using e_t = element_type_t<common_compatible_t<U, V>>;
      using r_t = as_wide_t<e_t, cardinal_t<T>>;

            if constexpr(kumi::product_type<U> || kumi::product_type<V>) return tuple_select(cond,t,f);
      else  if constexpr(has_emulated_abi_v<T>  ) return map(if_else, cond, r_t(t), r_t(f));
      else  if constexpr(has_aggregated_abi_v<T>) return aggregate(if_else, cond, r_t(t), r_t(f));
      else  if constexpr(std::same_as<logical<e_t>,element_type_t<T>>)
      {
        if constexpr( std::same_as<U,V> ) return  bit_select(cond.mask(),r_t(t), r_t(f));
        else                              return  if_else(cond, r_t(t), r_t(f));
      }
      else return  if_else(convert(cond, as<as_logical_t<e_t>>()), r_t(t), r_t(f));
    }
  }

  //------------------------------------------------------------------------------------------------
  // Supports if_else(conditional_expr,a,b)
  template<conditional_expr C, typename U, typename V>
  EVE_FORCEINLINE auto
  if_else_(EVE_SUPPORTS(cpu_), C const& cond, U const& t, V const& f )
  requires( compatible_values<U, V> || value<U> || value<V> )
  {
    using r_t = std::conditional_t< simd_value<U>, U, V>;

    if constexpr( C::is_complete )
    {
      if constexpr(C::is_inverted) return r_t(t); else return r_t(f);
    }
    else
    {
      auto const condition  = cond.mask(eve::as<r_t>());
      if constexpr( C::is_inverted )  { return if_else(condition, f, t ); }
      else                            { return if_else(condition, t, f ); }
    }
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,t,constant)
  template<value T, value U, generator<U> Constant>
  EVE_FORCEINLINE constexpr auto if_else_ ( EVE_SUPPORTS(cpu_)
                                          , T const& cond, U const& u, Constant const& v
                                          ) noexcept
  {
    using tgt = as<U>;

          if constexpr(scalar_value<T>)       return static_cast<bool>(cond) ? u : v(tgt{});
    else  if constexpr( kumi::product_type<U> )
    {
      auto cst = U{ kumi::map([&]<typename M>(M const& e) { return v(as(e)); }, u) };
      return if_else(cond, u, cst);
    }
    else  if constexpr(current_api >= avx512) return if_else(cond, u, v(tgt{}));
    else
    {
      using cvt = as<as_logical_t<element_type_t<U>>>;

      if constexpr( std::same_as<Constant, callable_zero_> )
      {
        return bit_and(u, bit_mask(convert(cond, cvt{})));
      }
      else if constexpr( std::same_as<Constant, callable_allbits_> )
      {
        return bit_ornot(u, bit_mask(convert(cond, cvt{})));
      }
      else if constexpr(integral_value<U>)
      {
        if constexpr( std::same_as<Constant, callable_one_> )
        {
          return -bit_ornot(minus(u), bit_mask(convert(cond, cvt{})));
        }
        else if constexpr( std::same_as<Constant, callable_mone_> )
        {
          return bit_ornot(u, bit_mask(convert(cond, cvt{})));
        }
        else
        {
          return if_else(cond, u, v(tgt{}));
        }
      }
      else
      {
        return if_else(cond, u, v(tgt{}));
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,constant, t)
  template<value T, value U, generator<U> Constant>
  EVE_FORCEINLINE constexpr auto if_else_ ( EVE_SUPPORTS(cpu_)
                                          , T const& cond, Constant const& v, U const& u
                                          ) noexcept
  {
    using tgt = as<U>;

          if constexpr(scalar_value<T>)       return static_cast<bool>(cond) ? v(tgt{}) : u;
    else  if constexpr( kumi::product_type<U> )
    {
      auto cst = U{ kumi::map([&]<typename M>(M const& e) { return v(as(e)); }, u) };
      return if_else(cond, cst, u);
    }
    else  if constexpr(current_api >= avx512) return if_else(cond, v(tgt{}), u);
    else
    {
      using cvt = as<as_logical_t<element_type_t<U>>>;

      if constexpr( std::same_as<Constant, callable_zero_> )
      {
        return bit_andnot(u, bit_mask(convert(cond, cvt{})));
      }
      else if constexpr( std::same_as<Constant, callable_allbits_> )
      {
        return bit_or(u, bit_mask(convert(cond, cvt{})));
      }
      else if constexpr(integral_value<U>)
      {
        if constexpr( std::same_as<Constant, callable_one_> )
        {
          return -bit_or(-u, bit_mask(convert(cond, cvt{})));
        }
        else if constexpr( std::same_as<Constant, callable_mone_> )
        {
          return bit_or(u, bit_mask(convert(cond, cvt{})));
        }
        else
        {
          return if_else(cond, v(tgt{}), u);
        }
      }
      else
      {
        return if_else(cond, v(tgt{}), u);
      }
    }
  }
}
