//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve
{
  namespace detail
  {
    template < typename T > struct down
    {
      using v_t = eve::element_type_t<T>;

      static constexpr auto sd = [](){
        if constexpr( std::same_as<v_t, double>)
        {
          return float();
        }
        else if constexpr( std::same_as<v_t, std::uint8_t> ||
                           std::same_as<v_t, float>        ||
                           std::same_as<v_t, std::int8_t > )
        {
          return v_t();
        }
        else if constexpr(std::signed_integral<v_t>)
        {
          using sd_t = eve::detail::make_integer<sizeof(v_t)/2, signed>::type;
          return sd_t();
        }
        else if constexpr(std::unsigned_integral<v_t>)
        {
          using sd_t = eve::detail::make_integer<sizeof(v_t)/2, unsigned>::type;
          return sd_t();
        }
      };
      using type = eve::as_wide_as_t<decltype(sd()), T>;
    };

    template < typename T > struct up
    {
      using v_t = eve::element_type_t<T>;

      static constexpr auto ud = [](){
        if constexpr( std::same_as<v_t, float>)
        {
          return double();
        }
        else if constexpr( std::same_as<v_t, std::uint64_t> ||
                           std::same_as<v_t, double>        ||
                           std::same_as<v_t, std::int64_t > )
        {
          return v_t();
        }
        else if constexpr(std::signed_integral<v_t>)
        {
          using ud_t = eve::detail::make_integer<sizeof(v_t)*2, signed>::type;
          return ud_t();
        }
        else if constexpr(std::unsigned_integral<v_t>)
        {
          using ud_t = eve::detail::make_integer<sizeof(v_t)*2, unsigned>::type;
          return ud_t();
        }
      };
      using type = eve::as_wide_as_t<decltype(ud()), T>;
    };
  }

  template < typename T > using down_t = detail::down<T>::type;
  template < typename T > using up_t = detail::up<T>::type;
}
