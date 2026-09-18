//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/as_wide.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  namespace _
  {
    template<value T> consteval auto down()
    {
      using v_t = eve::element_type_t<T>;
      if constexpr( std::same_as<v_t, float>)
      {
        return eve::float16_t();
      }
      else if constexpr( std::same_as<v_t, double>)
      {
        return float();
      }
      else if constexpr( (sizeof(v_t) == 1) || (floating_scalar_value<v_t> && (sizeof(v_t) <= 4)))
      {
        return v_t();
      }
      else if constexpr(std::signed_integral<v_t>)
      {
        using sd_t = typename eve::_::make_integer<sizeof(v_t)/2, signed>::type;
        return sd_t();
      }
      else if constexpr(std::unsigned_integral<v_t>)
      {
        using sd_t = typename eve::_::make_integer<sizeof(v_t)/2, unsigned>::type;
        return sd_t();
      }
      else
        return T{};
    };
    
    template<value T> consteval auto up()
    {
      using v_t = eve::element_type_t<T>;
      if constexpr( std::same_as<v_t, float>)
      {
        return double();
      }
      else if constexpr( std::same_as<v_t, eve::float16_t>)
      {
        return float();
      }
      else if constexpr( arithmetic_scalar_value<v_t> && sizeof(v_t) >= 8)
      {
        return v_t();
      }
      else if constexpr(std::signed_integral<v_t>)
      {
        using ud_t = typename eve::_::make_integer<sizeof(v_t)*2, signed>::type;
        return ud_t();
      }
      else if constexpr(std::unsigned_integral<v_t>)
      {
        using ud_t = typename eve::_::make_integer<sizeof(v_t)*2, unsigned>::type;
        return ud_t();
      }
      else
        return T{};
    };
  }

  template <typename T> using downgrade_t = eve::as_wide_as_t<decltype(_::down<T>())>; 
  template <typename T> using upgrade_t   = eve::as_wide_as_t<decltype(  _::up<T>())>; 

  template <typename T> downgrade_t<T> downgrade(T const & a){return convert(a, as<element_type_t<downgrade_t<T>>>()); }
  template <typename T>   upgrade_t<T>   upgrade(T const & a){return convert(a, as<element_type_t<upgrade_t  <T>>>()); }

  namespace _
  {
    template<typename O, typename T>
    consteval auto upgrade_if()
    {
      if constexpr ( requires { _::up<T>() })
      {
        if constexpr ( O::contains(eve::widen) )  return upgrade_t<T>();
        else                                      return T{};
      }
    }
  }

  template<typename O, typename T> using upgrade_if_t = decltype(_::upgrade_if<O,T>());

  namespace _
  {
    template <simd_value T> consteval auto split_down
    {
      using v_t = eve::element_type_t<T>;
      constexpr auto lowerN = integral_value<T> ? 1 : 2;
      if constexpr(sizeof(v_t) == lowerN)
      {
        return T();
      }
      else
      {
        using d_t = eve::downgrade_t<v_t>;
        constexpr auto N = cardinal_v<T>;
        constexpr auto N2 = N*2;
        using spd_t = wide<d_t, fixed<N2>>;
        return spd_t();
      }
    };
  }

  template <typename T> using split_down_t = decltype(_::split_down<T>());

}
