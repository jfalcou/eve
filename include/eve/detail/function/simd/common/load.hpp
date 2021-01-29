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
  template<typename Pack, typename Iterator>
  EVE_FORCEINLINE auto piecewise_load(eve::as_<Pack> const &, Iterator ptr) noexcept
  {
    auto impl = [&](auto... I)
    {
      auto deref = [&](auto p, auto const &i) { std::advance(p, i); return *p; };
      return Pack(deref(ptr, static_cast<std::ptrdiff_t>(I))...);
    };

    return apply<Pack::size()>(impl);
  }

  //================================================================================================
  // Emulation
  //================================================================================================
  template<typename Wide, typename Iterator>
  EVE_FORCEINLINE auto load(eve::as_<Wide> const& tgt, Iterator i) noexcept
  {
    auto const get = [](auto p)
    {
      if constexpr( !std::input_iterator<Iterator> )  return p.get();
      else                                            return p;
    };

    return piecewise_load(tgt, get(i));
  }

  //================================================================================================
  // Aggregation
  //================================================================================================
  template<typename T, typename N, typename Pointer>
  EVE_FORCEINLINE auto load(eve::as_<wide<T,N,aggregated_>> const &, Pointer ptr) noexcept
  {
    wide<T,N,aggregated_> that;

    auto cast = []<typename Ptr, typename Sub>(Ptr ptr, as_<Sub>)
    {
      using a_p = eve::aligned_ptr<const T, Sub::static_alignment>;
      if constexpr (std::is_pointer_v<Ptr>) return ptr;
      else                                  return a_p{ptr.get()};
    };

    that.storage().apply
    (
      [&]<typename... Sub>(Sub&... v)
      {
        int offset = 0;
        (((v = Sub(cast(ptr, as_<Sub>{}) + offset), offset += Sub::static_size), ...));
      }
    );

    return that.storage();
  }

  //================================================================================================
  // Common case for iterator based load
  //================================================================================================
  template<std::input_iterator Iterator, typename Pack>
  EVE_FORCEINLINE Pack load(eve::as_<Pack> const &tgt, Iterator b, Iterator) noexcept
  {
    return piecewise_load(tgt,b);
  }

}
