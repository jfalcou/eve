//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::algo
{
  template < typename T >
  struct is_soa_vector : std::false_type {};

  template < typename T >
  struct is_soa_vector<eve::algo::soa_vector<T>> : std::true_type {};

  template < typename T >
  using is_soa_vector_t =  typename is_soa_vector<T>::type;

  template < typename T >
  static inline constexpr bool is_soa_vector_v =  is_soa_vector<T>::value;
}
