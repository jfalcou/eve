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
  template<value T, kumi::product_type V>
  EVE_FORCEINLINE auto if_else_(EVE_SUPPORTS(cpu_), T const& cond, V const& t, V const& f )
  {
    return V{ kumi::map([&](auto const& v, auto const& f) { return if_else(cond,v,f); }, t, f) };
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

            if constexpr(has_emulated_abi_v<T>)    return map(if_else, cond, r_t(t), r_t(f));
      else  if constexpr(has_aggregated_abi_v<T>)  return aggregate(if_else, cond, r_t(t), r_t(f));
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
  EVE_FORCEINLINE auto if_else_(EVE_SUPPORTS(cpu_), C const& cond, U const& t, V const& f )
  requires(    compatible_values<U, V>
            || (!kumi::product_type<U> && value<U> && std::is_invocable_v<V, as<U>>)
            || (!kumi::product_type<V> && value<V> && std::is_invocable_v<U, as<V>>)
          )
  {
    using r_t = std::conditional_t< simd_value<U>, U, V>;

    if constexpr( C::is_complete )
    {
      using v_t = typename r_t::type;
      if constexpr(C::is_inverted) return v_t(t); else return v_t(f);
    }
    else
    {
      auto const condition  = cond.mask(eve::as<r_t>());
      if constexpr( C::is_inverted )  { return if_else(condition, f, t ); }
      else                            { return if_else(condition, t, f ); }
    }
  }

  template<conditional_expr C, typename U, typename V>
  EVE_FORCEINLINE auto if_else_(EVE_SUPPORTS(cpu_), C const& cond, U const& t, V const& f )
  requires(    (kumi::product_type<U> && std::is_invocable_v<V, as<kumi::element_t<0,U>>>)
            || (kumi::product_type<U> && std::is_invocable_v<U, as<kumi::element_t<0,V>>>)
          )
  {
    using r_t = std::conditional_t< simd_value<U>, U, V>;

    if constexpr( C::is_complete )
    {
      using v_t = typename r_t::type;
      if constexpr(C::is_inverted) return v_t(t); else return v_t(f);
    }
    else
    {
      auto const condition  = cond.mask(eve::as<kumi::element_t<0, typename r_t::type>>());
      if constexpr( C::is_inverted )  { return if_else(condition, f, t ); }
      else                            { return if_else(condition, t, f ); }
    }
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,t,constant)
  template<value T, value U, typename Constant>
  requires( ( kumi::product_type<U> && std::is_invocable_v<Constant, as<kumi::element_t<0,U>>> )
          || std::is_invocable_v<Constant, as<U>>
          )
  EVE_FORCEINLINE constexpr auto if_else_ ( EVE_SUPPORTS(cpu_)
                                          , T const& cond, U const& u, Constant const& v
                                          ) noexcept
  {
    using tgt = as<U>;

          if constexpr(scalar_value<T>)       return static_cast<bool>(cond) ? u : v(tgt{});
    else  if constexpr(current_api >= avx512) return if_else(cond, u, v(tgt{}));
    else  if constexpr( kumi::product_type<U> )
    {
      if constexpr( tag_dispatchable<tag::if_else_,T,U,Constant> )
      {
        return tagged_dispatch(tag::if_else_{}, cond, u, v);
      }
      else
      {
        auto cst = U{ kumi::map([&]<typename M>(M const& e) { return v(as(e)); }, u) };
        return if_else(cond, u, cst);
      }
    }
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
  template<value T, value U, typename Constant>
  requires( ( kumi::product_type<U> && std::is_invocable_v<Constant, as<kumi::element_t<0,U>>> )
          || std::is_invocable_v<Constant, as<U>>
          )
  EVE_FORCEINLINE constexpr auto if_else_ ( EVE_SUPPORTS(cpu_)
                                          , T const& cond, Constant const& v, U const& u
                                          ) noexcept
  {
    using tgt = as<U>;

          if constexpr(scalar_value<T>)       return static_cast<bool>(cond) ? v(tgt{}) : u;
    else  if constexpr(current_api >= avx512) return if_else(cond, v(tgt{}), u);
    else  if constexpr( kumi::product_type<U> )
    {
      if constexpr( tag_dispatchable<tag::if_else_,T,Constant,U> )
      {
        return tagged_dispatch(tag::if_else_{}, cond, v, u);
      }
      else
      {
        auto cst = U{ kumi::map([&]<typename M>(M const& e) { return v(as(e)); }, u) };
        return if_else(cond, cst, u);
      }
    }
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
