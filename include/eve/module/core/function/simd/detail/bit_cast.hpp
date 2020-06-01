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

#include <eve/as.hpp>
#include <eve/function/definition/bit_cast.hpp>
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

    return bit_cast(v0, as_<type>()).storage();
  }

  // Arithmetic -> Logical with different storage case
  template<typename In, typename Out>
  EVE_FORCEINLINE auto a2l_cast_(In const &v0, Out const &) noexcept
  {
    using type      = typename Out::type;
    using local_tgt = wide<typename type::value_type::value_type,
                           typename type::cardinal_type,
                           typename type::abi_type>;

    auto that = bit_cast(v0, as_<local_tgt>());
    return type((typename type::storage_type)(that.storage()));
  }

  // Logical -> Arithmetic with isomorphic storage case
  template<typename In, typename Out>
  EVE_FORCEINLINE auto l2a_isocast_(In const &v0, Out const &) noexcept
  {
    using type = wide<typename In::value_type::value_type, typename In::cardinal_type>;
    return bit_cast(type{v0.storage()}, as_<typename Out::type>());
  }

  // Logical -> Arithmetic with different storage case
  template<typename In, typename Out>
  EVE_FORCEINLINE typename Out::type l2a_cast_(In const &v0, Out const &) noexcept
  {
    using type = wide<typename Out::type::value_type, typename Out::type::cardinal_type>;
    return (typename type::storage_type)(v0.storage());
  }

  // Logical -> Logical with isomorphic storage case
  template<typename In, typename Out>
  EVE_FORCEINLINE auto l2l_isocast_(In const &v0, Out const &) noexcept
  {
    using type = wide<typename In::value_type::value_type, typename In::cardinal_type>;

    if constexpr(std::is_same_v<In, typename Out::type>)
      return v0;
    else
      return bit_cast(type{v0.storage()}, as_<typename Out::type>()).storage();
  }

  // Logical -> Logical with different storage case
  template<typename In, typename Out>
  EVE_FORCEINLINE auto l2l_cast_(In const &v0, Out const &) noexcept
  {
    using type = wide<typename In::value_type::value_type, typename In::cardinal_type>;

    if constexpr(std::is_same_v<In, typename Out::type>)
      return v0;
    else
      return bit_cast(bit_cast(v0,as_<type>()), as_<typename Out::type>());
  }
}

