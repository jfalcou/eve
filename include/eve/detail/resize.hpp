//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#include <eve/traits/updown.hpp>
#include <iostream>

namespace eve
{
  namespace detail
  {
    template < typename F, callable_options O, typename ... Ts>
    constexpr auto  resize_it(F f, O const & o, Ts ... ts) noexcept
    {
      if constexpr(O::contains(narrow))
      {
        using dw_t = down_t<element_type_t<decltype(f(ts...))>>;
        return convert(f[o.drop(narrow)](ts...), as<dw_t>());
      }
      else if constexpr(O::contains(widen))
      {
        using upw_t = up_t<element_type_t<common_value_t<Ts...>>>;
        return f[o.drop(widen)](convert(ts ,as< upw_t>())...);
      }
      else return f[o](ts...);
    }

    template < typename T,  typename O >
    constexpr auto resize_it(O const &, T a) noexcept
    {
      if constexpr(std::same_as<O, decltype(widen)>)
      {
        std::cout << "icitte" << std::endl;
        using upw_t = up_t<element_type_t<T>>;
        return convert(a, as< upw_t>());
      }
      else if constexpr(std::same_as<O, decltype(narrow)>)
      {
        using dw_t = down_t<element_type_t<T>>;
        return convert(a, as< dw_t>());
      }
      else return a;
    }


    template < typename T,  callable_options O >
    constexpr auto resize_it(O const &, T a) noexcept
    {
      if constexpr(O::contains(widen))
      {
        using upw_t = up_t<element_type_t<T>>;
        return convert(a, as< upw_t>());
      }
      else if constexpr(O::contains(narrow))
      {
        using dw_t = down_t<element_type_t<T>>;
        return convert(a, as< dw_t>());
      }
      else return a;
    }
  }
}
