//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <type_traits>

namespace eve
{
  template<floating_value T>
  class valder
  {
    using elt_t = element_type_t<T>;
    using value_t = T;
    using type_t = valder<T>;
    valder()
      : v_(zero(as<T>())), d_(zero(as<T>()))
    {};
    valder(const T& a)
      : v_(a), d_(zero(as<T>()))
    {};
    valder(const T& v, const T& d)
      : v_(v), d_(d)
    {};
    valder(const value_t& a)
      : v_(a.val()), d_(a.der())
    {};
    value_t val() const { return v_; }
    value_t der() const { return d_; }
    value_t& val(const value_t & v) { return v_ = v; }
    value_t& der(const value_t & d) { return d_ = d; }
    value_t& val(const scalar_value & v) { return v_ = T(v); }
    value_t& der(const scalar_value & d) { return d_ = T(d); }
    auto apply_over(Obj f)
    {
      if constexpr(has_emulated_abi_v<T> )
      {
        return map(f, *this);
      }
      else if constexpr(has_aggregated_abi_v<T>)
      {
        auto  [lov, hiv] = val_.slice();
        auto  [lod, hid] = der_.slice();
        auto  [xhi, ehi] = f(valder(hiv, hid));
        auto  [xlo, elo] = f(valder(lov, lod));
        return valder(eve::combine(xlo, xhi), eve::combine(elo, ehi));
      }
      else return f(v);
    }

  private:
    value_t v_, d_;
  };
  template<typename T> struct  is_ad_value : std::false_type {};
  template<typename T> struct  is_ad_value<valder<T> : std::true_type {};
  template<typename T> using  is_ad_value_t = typename is_ad_value<T>::type

  template<typename T> constexpr bool is_ad_value_v<T> =  is_ad_value_t<T>::value;



  template<floating_real_value T>
  EVE_FORCEINLINE auto val(T const & u)
  {
    return u;
  }
  template<floating_real_value T>
  EVE_FORCEINLINE auto der(T const & u)
  {
    return zero(as(u));
  }

  template<ad_value T>
  EVE_FORCEINLINE auto val(T const & u)
  {
    return u.val();
  }
  template<ad_value T>
  EVE_FORCEINLINE auto der(T const & u)
  {
    return u.der();
  }

  template<floating_real_value T>
  inline std::ostream& operator<<(std::ostream& os, valder<T> const& v)
  {
    os << "[\n";
    os << " value      ->\n" << val(v) << "  ";
    os << "\n";
    os << " diff ->\n" << der(v) << "  ";
    os << "\n]";

    return os;
  }
}
