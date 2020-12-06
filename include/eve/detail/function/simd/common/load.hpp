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
#include <eve/detail/abi.hpp>
#include <eve/memory/aligned_ptr.hpp>

#include <iterator>

namespace eve::detail
{
  //================================================================================================
  // Emulation
  //================================================================================================
  template<typename Pack, typename Iterator>
  EVE_FORCEINLINE Pack load(eve::as_<Pack> const &, eve::emulated_ const &, Iterator ptr) noexcept
  {
    auto impl = [&](auto... I) {
      auto deref = [&](auto p, auto const &i) {
        std::advance(p, i);
        return *p;
      };
      return Pack(deref(ptr, static_cast<std::ptrdiff_t>(I))...);
    };

    return apply<Pack::size()>(impl);
  }

  template<typename T, typename Pack, std::size_t N>
  EVE_FORCEINLINE Pack load(eve::as_<Pack> const &     tgt,
                            eve::emulated_ const &mode,
                            aligned_ptr<T, N>     ptr) noexcept
  {
    return load(tgt, mode, ptr.get());
  }

  template<typename T, typename Pack, std::size_t N>
  EVE_FORCEINLINE Pack load(eve::as_<Pack> const &     tgt,
                            eve::emulated_ const &mode,
                            aligned_ptr<T const, N>     ptr) noexcept
  {
    return load(tgt, mode, ptr.get());
  }

  template<typename Iterator, typename ABI, typename Pack>
  EVE_FORCEINLINE Pack load(eve::as_<Pack> const &tgt, ABI const &, Iterator b, Iterator) noexcept
  {
    return load(tgt, eve::emulated_ {}, b);
  }

  //================================================================================================
  // Aggregation
  //================================================================================================
  template<typename Pack, typename Pointer>
  EVE_FORCEINLINE Pack load(eve::as_<Pack> const &, eve::aggregated_ const &, Pointer ptr) noexcept
  {
    Pack that;

    that.storage().apply
    (
      [&]<typename... Sub>(Sub&... v)
      {
        int offset = 0;
        (((v = Sub(ptr + offset), offset += Sub::static_size), ...));
      }
    );

    return that.storage();
  }
}

