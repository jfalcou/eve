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
  //  ============================================================================================
  // mod

   struct default_mod
  {
    friend std::ostream& operator<<(std::ostream& os, default_mod const&) { return os << "1"; }
  };

  template<typename Value>
  struct mod_t
  {
    constexpr mod_t() {}
    constexpr explicit mod_t(Value v) : value_(v) {}
    constexpr mod_t(mod_t const& v) : value_(v.value_) {}
    constexpr mod_t& operator=(mod_t const& v) { value_ = v.value_; return *this; }

    /// ID type associated to the keyword
    using id_type = mod_mode;

    template<typename T> static constexpr bool accept() { return true; }

    std::ostream& show(std::ostream& os, auto const& v) const
    {
      return os << "mod by " << v.value_;
    }

    using tag_type          = mod_t<default_mod>;
    using keyword_type      = mod_t<default_mod>;
    using stored_value_type = mod_t<Value>;

    template<eve::value Type>
    constexpr auto operator=(Type v) const noexcept { return mod_t<Type>{v}; }

    template<typename T>
    constexpr auto operator=(mod_t<T> const& v) const noexcept
    {
      return v;
    }

    constexpr auto operator()(keyword_type const&) const noexcept { return *this; }

    template<typename T> constexpr auto value(T const&) const
    {
      using type = element_type_t<T>;
      if constexpr(std::same_as<Value,default_mod>) return eve::one(as<type>{});
      else                                          return type(value_);
    }

    Value value_;
  };

  inline constexpr mod_t<default_mod> mod = {};

}
