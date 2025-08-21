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
  struct default_tolerance
  {
    friend std::ostream& operator<<(std::ostream& os, default_tolerance const&) { return os << "3 * eps"; }
  };

  // ===============================================================================================
  //almost

  template<typename Value>
  struct almost_t
  {
    constexpr almost_t() {}
    constexpr explicit almost_t(Value v) : value_(v) {}
    constexpr almost_t(almost_t const& v) : value_(v.value_) {}
    constexpr almost_t& operator=(almost_t const& v) { value_ = v.value_; return *this; }

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

    template<eve::scalar_value Type>
    constexpr auto operator=(Type v) const noexcept { return almost_t<Type>{v}; }

    template<typename T>
    constexpr auto operator=(almost_t<T> const& v) const noexcept
    {
      return v;
    }

    constexpr auto operator()(keyword_type const&) const noexcept { return *this; }

    template<typename T> constexpr auto value(T const&) const
    {
      using type = element_type_t<T>;
      if constexpr(std::same_as<Value,default_tolerance>) return 3 * eps(as<type>{});
      else if constexpr(integral_value<Value>)            return value_;
      else                                                return type{value_};
    }

    Value value_;
  };

  inline constexpr almost_t<default_tolerance> almost = {};

  //  ============================================================================================
  // definitely

  template<typename Value>
  struct definitely_t
  {
    constexpr definitely_t() {}
    constexpr explicit definitely_t(Value v) : value_(v) {}
    constexpr definitely_t(definitely_t const& v) : value_(v.value_) {}
    constexpr definitely_t& operator=(definitely_t const& v) { value_ = v.value_; return *this; }

    /// ID type associated to the keyword
    using id_type = definitely_mode;

    template<typename T> static constexpr bool accept() { return true; }

    std::ostream& show(std::ostream& os, auto const& v) const
    {
      return os << "definitely by " << v.value_;
    }

    using tag_type          = definitely_t<default_tolerance>;
    using keyword_type      = definitely_t<default_tolerance>;
    using stored_value_type = definitely_t<Value>;

    template<eve::scalar_value Type>
    constexpr auto operator=(Type v) const noexcept { return definitely_t<Type>{v}; }

    template<typename T>
    constexpr auto operator=(definitely_t<T> const& v) const noexcept
    {
      return v;
    }

    constexpr auto operator()(keyword_type const&) const noexcept { return *this; }

    template<typename T> constexpr auto value(T const&) const
    {
      using type = element_type_t<T>;
      if constexpr(std::same_as<Value,default_tolerance>) return 3 * eps(as<type>{});
      else if constexpr(integral_value<Value>)            return value_;
      else                                                return type{value_};
    }

    Value value_;
  };

  inline constexpr definitely_t<default_tolerance> definitely = {};


  //  ============================================================================================
  // threshold

  template<typename Value>
  struct threshold_t
  {
    constexpr threshold_t() {}
    constexpr explicit threshold_t(Value v) : value_(v) {}
    constexpr threshold_t(threshold_t const& v) : value_(v.value_) {}
    constexpr threshold_t& operator=(threshold_t const& v) { value_ = v.value_; return *this; }

    /// ID type associated to the keyword
    using id_type = threshold_mode;

    template<typename T> static constexpr bool accept() { return true; }

    std::ostream& show(std::ostream& os, auto const& v) const
    {
      return os << "threshold by " << v.value_;
    }

    using tag_type          = threshold_t<default_tolerance>;
    using keyword_type      = threshold_t<default_tolerance>;
    using stored_value_type = threshold_t<Value>;

    template<eve::scalar_value Type>
    constexpr auto operator=(Type v) const noexcept { return threshold_t<Type>{v}; }

    template<typename T>
    constexpr auto operator=(threshold_t<T> const& v) const noexcept
    {
      return v;
    }

    constexpr auto operator()(keyword_type const&) const noexcept { return *this; }

    template<typename T> constexpr auto value(T const&) const
    {
      using type = element_type_t<T>;
      if constexpr(std::same_as<Value,default_tolerance>) return eps(as<type>{});
      else                                                return type{value_};
    }

    Value value_;
  };

  inline constexpr threshold_t<default_tolerance> threshold = {};


  //  ============================================================================================
  // mod

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
      using type = T; //element_type_t<T>;
      if constexpr(std::same_as<Value,default_mod>) return eve::one(as<type>{});
      else                                          return type(value_);
    }

    Value value_;
  };

  inline constexpr mod_t<default_mod> mod = {};

}
