//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_SPEC_HPP_INCLUDED
#define EVE_ARCH_SPEC_HPP_INCLUDED

#if !defined(EVE_NO_SIMD)
#  include <eve/arch/x86/spec.hpp>
#  include <eve/arch/ppc/spec.hpp>
#  include <eve/arch/arm/spec.hpp>
#endif

#include <eve/arch/cpu/spec.hpp>
#include <eve/arch/tags.hpp>
#include <type_traits>

//==================================================================================================
// constexpr object wrapper around EVE_CURRENT_API for if constexpr usage
namespace eve
{
  template<typename API>
  struct current_api_
  {
  };

  // Is same API ?
  template<typename API, typename Tag>
  inline constexpr bool operator==(current_api_<API> const &, Tag const &)
  {
    return std::is_same_v<API, Tag>;
  }

  template<typename API, typename Tag>
  inline constexpr bool operator==(Tag const &, current_api_<API> const &)
  {
    return std::is_same_v<API, Tag>;
  }

  template<typename API, typename Tag>
  inline constexpr bool operator!=(current_api_<API> const &, Tag const &)
  {
    return !std::is_same_v<API, Tag>;
  }

  template<typename API, typename Tag>
  inline constexpr bool operator!=(Tag const &, current_api_<API> const &)
  {
    return !std::is_same_v<API, Tag>;
  }

  // API version ordering ?
  template<typename API, typename Tag>
  inline constexpr bool operator<(current_api_<API> const &, Tag const &)
  {
    return API::order < Tag::order;
  }

  template<typename API, typename Tag>
  inline constexpr bool operator<(Tag const &, current_api_<API> const &)
  {
    return Tag::order < API::order;
  }

  template<typename API, typename Tag>
  inline constexpr bool operator>(current_api_<API> const &, Tag const &)
  {
    return API::order > Tag::order;
  }

  template<typename API, typename Tag>
  inline constexpr bool operator>(Tag const &, current_api_<API> const &)
  {
    return Tag::order > API::order;
  }

  template<typename API, typename Tag>
  inline constexpr bool operator<=(current_api_<API> const &a, Tag const &t)
  {
    return !(a > t);
  }

  template<typename API, typename Tag>
  inline constexpr bool operator<=(Tag const &t, current_api_<API> const &a)
  {
    return !(t > a);
  }

  template<typename API, typename Tag>
  inline constexpr bool operator>=(current_api_<API> const &a, Tag const &t)
  {
    return !(a < t);
  }

  template<typename API, typename Tag>
  inline constexpr bool operator>=(Tag const &t, current_api_<API> const &a)
  {
    return !(t < a);
  }

  inline constexpr current_api_<EVE_CURRENT_API> current_api = {};
}

#endif
