//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/eps.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/convert.hpp>

namespace eve
{
  template<typename Value>
  struct almost_t
  {
    constexpr almost_t() {}
    constexpr explicit almost_t(Value v) : value_(v) {}
    constexpr almost_t(almost_t const& v) : value_(v.value_) {}

    /// ID type associated to the keyword
    using id_type = almost_mode;

    template<typename T> static constexpr bool accept() { return true; }

    std::ostream& show(std::ostream& os, auto const& v) const
    {
      return os << "almost by " << v.value_;
    }

    using tag_type          = almost_t<default_tolerance>;
    using keyword_type      = almost_t<default_tolerance>;
    using stored_value_type = almost_t<Value>;

    template<eve::value Type>
    constexpr auto operator=(Type v) const noexcept { return almost_t<Type>{v}; }

    template<typename T>
    constexpr auto operator=(almost_t<T> const& v) const noexcept
    {
      return v;
    }

    constexpr auto operator()(keyword_type const&) const noexcept { return *this; }

    template<typename T> constexpr auto value(T const&) const
    {
      if constexpr(std::same_as<Value,default_tolerance>) return 3 * eps(as<T>{});
      else if constexpr(integral_value<Value>)            return value_;
      else                                                return convert(value_,as_element<T>{});
    }

    Value value_;
  };

  inline constexpr almost_t<default_tolerance> almost2 = {};

  inline constexpr auto as_option(almost_type const&) { return almost2; }
}
