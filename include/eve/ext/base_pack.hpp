//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_EXT_BASE_PACK_HPP_INCLUDED
#define EVE_EXT_BASE_PACK_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/alias.hpp>
#include <iterator>
#include <cstddef>

namespace eve { namespace detail
{
  template<typename Pack, typename ABI> struct target_type
  {
    using type = typename Pack::value_type;
  };

  template<typename Pack> struct target_type<Pack,::eve::emulated_>
  {
    using type = typename Pack::storage_type;
  };

  template<typename Pack> struct target_type<Pack,::eve::aggregated_>
  {
    using type = Pack;
  };

  template<typename Storage, typename ABI>
  struct pack_align
  {
    static constexpr std::size_t value = alignof(Storage);
  };

  template<typename Storage> struct pack_align<Storage,::eve::aggregated_>
  {
    static constexpr std::size_t value = Storage::value_type::static_alignment;
  };

  template<typename Type, typename Storage, typename ABI> struct pack_iterator
  {
    static EVE_FORCEINLINE auto begin(Storage& s) noexcept
    {
      return reinterpret_cast<detail::alias_t<Type>*>(&s);
    }

    static EVE_FORCEINLINE auto begin(Storage const& s) noexcept
    {
      return reinterpret_cast<detail::alias_t<Type> const*>(&s);
    }
  };

  template<typename Type, typename Storage>
  struct pack_iterator<Type,Storage,::eve::aggregated_>
  {
    static EVE_FORCEINLINE auto begin(Storage& s)       noexcept { return s[0].begin(); }
    static EVE_FORCEINLINE auto begin(Storage const& s) noexcept { return s[0].begin(); }
  };
} }

#endif
