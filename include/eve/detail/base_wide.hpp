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

#include <eve/detail/abi.hpp>
#include <eve/detail/alias.hpp>
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
    static constexpr std::size_t native = alignof(Storage);
    static constexpr std::size_t limit  = Size::value * sizeof(Type);
    static constexpr std::size_t value  = limit < native ? limit : native;
  };

  template<typename Size, typename Type, typename Storage>
  struct wide_align<Size, Type, Storage, ::eve::aggregated_>
  {
    static constexpr std::size_t value = Storage::value_type::static_alignment;
  };
}

