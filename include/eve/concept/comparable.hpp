//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <concepts>

namespace eve
{
  template<typename T, typename U>
  concept equality_comparable = requires(T t, U u)
  {
    { t == u } -> std::convertible_to<bool>;
    { u == t } -> std::convertible_to<bool>;
  };
  
  template<typename T, typename U>
  concept inequality_comparable = requires(T t, U u)
  {
    { t != u } -> std::convertible_to<bool>;
    { u != t } -> std::convertible_to<bool>;
  };
  
  template<typename T, typename U>
  concept is_less_comparable = requires(T t, U u)
  {
    { t < u } -> std::convertible_to<bool>;
    { u < t } -> std::convertible_to<bool>;
  };
  
  template<typename T, typename U>
  concept is_less_equal_comparable = requires(T t, U u)
  {
    { t <= u } -> std::convertible_to<bool>;
    { u <= t } -> std::convertible_to<bool>;
  };
  
  template<typename T, typename U>
  concept is_greater_comparable = requires(T t, U u)
  {
    { t > u } -> std::convertible_to<bool>;
    { u > t } -> std::convertible_to<bool>;
  };
  
  template<typename T, typename U>
  concept is_greater_equal_comparable = requires(T t, U u)
  {
    { t >= u } -> std::convertible_to<bool>;
    { u >= t } -> std::convertible_to<bool>;
  };
}
