//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/as_wide.hpp>
#include <eve/detail/meta.hpp>

namespace eve
{
  namespace detail
  {
    template < typename T > struct down
    {
      using v_t = eve::element_type_t<T>;

      static constexpr auto sd = [](){
        if constexpr (std::same_as<v_t, double>)
        {
          return float{};
        }
        else if constexpr( std::same_as<v_t, std::uint8_t> ||
                           std::same_as<v_t, float>        ||
                           std::same_as<v_t, std::int8_t > )
        {
          return v_t{};
        }
        else if constexpr (std::signed_integral<v_t>)
        {
          using sd_t = typename eve::detail::make_integer<sizeof(v_t) / 2, signed>::type;
          return sd_t{};
        }
        else if constexpr(std::unsigned_integral<v_t>)
        {
          using sd_t = typename eve::detail::make_integer<sizeof(v_t) / 2, unsigned>::type;
          return sd_t{};
        }
        else
          return T{};
      };

      using type = eve::as_wide_as_t<decltype(sd()), T>;
    };

    template <typename T> struct up
    {
      using v_t = eve::element_type_t<T>;

      static constexpr auto ud = [](){
        if constexpr (std::same_as<v_t, float>)
        {
          return double{};
        }
        else if constexpr (arithmetic_scalar_value<v_t> && (sizeof(v_t) == 8))
        {
          return v_t{};
        }
        else if constexpr(std::signed_integral<v_t>)
        {
          using ud_t = typename eve::detail::make_integer<sizeof(v_t) * 2, signed>::type;
          return ud_t{};
        }
        else if constexpr(std::unsigned_integral<v_t>)
        {
          using ud_t = typename eve::detail::make_integer<sizeof(v_t) * 2, unsigned>::type;
          return ud_t{};
        }
        else
          return T{};
      };

      using type = eve::as_wide_as_t<decltype(ud()), T>;
    };
  }


  template <typename T> using downgrade_t = typename detail::down<T>::type;
  template <typename T> using upgrade_t   = typename detail::up<T>::type;

  template <typename T> downgrade_t<T> downgrade(T const& a){ return convert(a, as<element_type_t<downgrade_t<T>>>()); }
  template <typename T>   upgrade_t<T>   upgrade(T const& a){ return convert(a, as<element_type_t<upgrade_t  <T>>>()); }

  namespace detail
  {
    template < integral_simd_value T > struct split_down
    {
      static constexpr auto spd = [](){
        using v_t = eve::element_type_t<T>;
        if constexpr(sizeof(v_t) == 1)
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
      using type = decltype(spd());
    };
  }

  template < typename T > using split_down_t = typename detail::split_down<T>::type;

}
