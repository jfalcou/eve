//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_EXT_BASE_WIDE_HPP_INCLUDED
#define EVE_EXT_BASE_WIDE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/alias.hpp>
#include <iterator>
#include <cstddef>

namespace eve::detail
{
  template<typename Pack, typename ABI>
  struct target_type
  {
    using type = typename Pack::value_type;
  };

  template<typename Pack>
  struct target_type<Pack, ::eve::emulated_>
  {
    using type = typename Pack::storage_type;
  };

  template<typename Pack>
  struct target_type<Pack, ::eve::aggregated_>
  {
    using type = Pack;
  };

  template<typename Size, typename Type, typename Storage, typename ABI>
  struct wide_align
  {
    static constexpr std::size_t base   = alignof(Type);
    static constexpr std::size_t native = alignof(Storage);
    static constexpr std::size_t limit  = Size::value * sizeof(Type);
    static constexpr std::size_t value  = limit < native ? base : native;
  };

  template<typename Size, typename Type, typename Storage>
  struct wide_align<Size, Type, Storage, ::eve::aggregated_>
  {
    static constexpr std::size_t value = Storage::value_type::static_alignment;
  };

  template<typename Type, typename Storage, typename ABI>
  struct wide_iterator
  {
    static EVE_FORCEINLINE auto begin(Storage &s) noexcept
    {
      return reinterpret_cast<detail::alias_t<Type> *>(&s);
    }

    static EVE_FORCEINLINE auto begin(Storage const &s) noexcept
    {
      return reinterpret_cast<detail::alias_t<Type> const *>(&s);
    }
  };

  template<typename Type, typename Storage>
  struct wide_iterator<Type, Storage, ::eve::aggregated_>
  {
    static EVE_FORCEINLINE auto begin(Storage &s) noexcept { return s.lo.begin(); }
    static EVE_FORCEINLINE auto begin(Storage const &s) noexcept { return s.lo.begin(); }
  };
}

#endif
