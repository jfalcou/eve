//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_DETAIL_BITWISE_CAST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_DETAIL_BITWISE_CAST_HPP_INCLUDED

#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Reusable helper for logical casting

  // Arithmetic -> Logical with isomorphic storage case
  template<typename In, typename Out>
  EVE_FORCEINLINE auto a2l_isocast_(In const &v0, Out const &) noexcept
  {
    using tgt_t = typename Out::type;
    using type  = wide<typename tgt_t::value_type::value_type,
                      typename tgt_t::cardinal_type,
                      typename tgt_t::abi_type>;

    return bitwise_cast<type>(v0).storage();
  };

  // Arithmetic -> Logical with different storage case
  template<typename In, typename Out>
  EVE_FORCEINLINE auto a2l_cast_(In const &v0, Out const &) noexcept
  {
    using type      = typename Out::type;
    using local_tgt = wide<typename type::value_type::value_type,
                           typename type::cardinal_type,
                           typename type::abi_type>;

    auto that = bitwise_cast<local_tgt>(v0);
    return type((typename type::storage_type)(that.storage()));
  };

  // Logical -> Arithmetic with isomorphic storage case
  template<typename In, typename Out>
  EVE_FORCEINLINE auto l2a_isocast_(In const &v0, Out const &) noexcept
  {
    using type = wide<typename In::value_type::value_type, typename In::cardinal_type>;
    return bitwise_cast<typename Out::type>(type{v0.storage()});
  };

  // Logical -> Arithmetic with different storage case
  template<typename In, typename Out>
  EVE_FORCEINLINE auto l2a_cast_(In const &v0, Out const &) noexcept
  {
    using type = wide<typename In::value_type::value_type, typename In::cardinal_type>;

    type tmp((typename type::storage_type)(v0.storage()));
    return bitwise_cast<typename Out::type>(tmp);
  };

  // Logical -> Logical with isomorphic storage case
  template<typename In, typename Out>
  EVE_FORCEINLINE auto l2l_isocast_(In const &v0, Out const &) noexcept
  {
    using type = wide<typename In::value_type::value_type, typename In::cardinal_type>;

    if constexpr(std::is_same_v<In, typename Out::type>)
      return v0;
    else
      return bitwise_cast<typename Out::type>(type{v0.storage()}).storage();
  };

  // Logical -> Logical with different storage case
  template<typename In, typename Out>
  EVE_FORCEINLINE auto l2l_cast_(In const &v0, Out const &) noexcept
  {
    using type = wide<typename In::value_type::value_type, typename In::cardinal_type>;

    if constexpr(std::is_same_v<In, typename Out::type>)
      return v0;
    else
      return bitwise_cast<typename Out::type>(bitwise_cast<type>(v0));
  };
}

#endif
