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
  concept less_comparable = requires(T t, U u)
  {
    { t < u } -> std::convertible_to<bool>;
    { u < t } -> std::convertible_to<bool>;
  };
  
  template<typename T, typename U>
  concept less_equal_comparable = requires(T t, U u)
  {
    { t <= u } -> std::convertible_to<bool>;
    { u <= t } -> std::convertible_to<bool>;
  };
  
  template<typename T, typename U>
  concept greater_comparable = requires(T t, U u)
  {
    { t > u } -> std::convertible_to<bool>;
    { u > t } -> std::convertible_to<bool>;
  };
  
  template<typename T, typename U>
  concept greater_equal_comparable = requires(T t, U u)
  {
    { t >= u } -> std::convertible_to<bool>;
    { u >= t } -> std::convertible_to<bool>;
  };
}
