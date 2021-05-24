//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/function/bit_cast.hpp>
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

  template<typename Wide, typename Pointer>
  EVE_FORCEINLINE auto aggregate_load(eve::as_<Wide> const &, Pointer ptr) noexcept
  {
    Wide that;

    auto cast = []<typename Ptr, typename Sub>(Ptr ptr, as_<Sub>)
    {
      using type = element_type_t<Wide>;
      using a_p = eve::aligned_ptr<const type, Sub::static_alignment>;
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
  // Emulation
  //================================================================================================
  template<typename T, typename N, typename Pointer>
  EVE_FORCEINLINE auto load(eve::as_<wide<T,N,emulated_>> const& tgt, Pointer i) noexcept
  {
    auto const get = [](auto p)
    {
      if constexpr( !std::input_iterator<Pointer> )  return p.get();
      else                                            return p;
    };

    return piecewise_load(tgt, get(i));
  }

  //================================================================================================
  // Aggregation
  //================================================================================================
  template<typename T, typename N, typename Pointer>
  EVE_FORCEINLINE auto load(eve::as_<wide<T,N,aggregated_>> const & tgt, Pointer ptr) noexcept
  {
    return aggregate_load(tgt,ptr);
  }

  //================================================================================================
  // Common case for iterator based load
  //================================================================================================
  template<std::input_iterator Iterator, typename Pack>
  EVE_FORCEINLINE Pack load(eve::as_<Pack> const &tgt, Iterator b, Iterator) noexcept
  {
    return piecewise_load(tgt,b);
  }

  //================================================================================================
  // Basic logical support
  //================================================================================================
  template<typename T, typename N, typename Ptr>
  EVE_FORCEINLINE
  auto load(eve::as_<logical<wide<T, N>>> const & tgt, Ptr p)
  requires( std::same_as<logical<T>, std::remove_cvref_t<decltype(*p)>> )
  {
    return  bit_cast
            ( [&]() -> wide<T, N>
              {
                using wtg = eve::as_<wide<T, N>>;
                if constexpr( !std::is_pointer_v<Ptr> )
                {
                  using ptr_t = typename Ptr::template rebind<T const>;
                  return load(wtg{}, ptr_t( (T const*)(p.get())) );
                }
                else
                {
                  return load(wtg{}, (T const*)(p));
                }
              }()
            , tgt
            );
  }

  template<typename T, typename N, typename Ptr>
  EVE_FORCEINLINE
  auto load(eve::as_<logical<wide<T, N, aggregated_>>> const & tgt, Ptr p)
  requires( std::same_as<logical<T>, std::remove_cvref_t<decltype(*p)>> )
  {
    return aggregate_load(tgt,p);
  }
}
