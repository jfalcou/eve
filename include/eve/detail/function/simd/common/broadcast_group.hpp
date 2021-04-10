//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
  template<simd_value Wide, std::ptrdiff_t Group, std::ptrdiff_t Index, std::ptrdiff_t Size>
  requires(   (Group >  0) && (Group <= std::min(cardinal_v<Wide>, Size))
          &&  (Index >= 0) && (Index < cardinal_v<Wide>/Group)
          )
  EVE_FORCEINLINE auto broadcast_group_ ( EVE_SUPPORTS(cpu_), Wide w
                                        , fixed<Group> g, index_t<Index> i, fixed<Size> sz
                                        )
  {
    using that_t        = as_wide_t<Wide,fixed<Size>>;
    using v_t           = eve::element_type_t<Wide>;
    constexpr auto card = cardinal_v<Wide>;

    [[maybe_unused]] auto const compute_half = [&](auto v, auto sz)
    {
      // If the beginning of the indexed group is beyond half the cardinal
      if constexpr(Index*Group >= card/2)
      {
        // We recompute the index and broadcast something from the upper slice of w
        return broadcast_group(v.slice(upper_), g , index<Index-card/(Group*2)>, sz);
      }
      else
      {
        // Else we broadcast somethign from the lower slice of w
        return broadcast_group(v.slice(lower_), g , i, sz);
      }
    };

    // If the output size is equal to the group size and the cardinal, we just return the input
    if constexpr(Size == Group && Size == card)
    {
      return w;
    }
    // If the output is aggregated, we do the replication
    else if constexpr(eve::has_aggregated_abi_v<that_t> )
    {
      auto const r = compute_half(w, lane<(card >= Size ? Size/2 : Size)>);
      return eve::combine(r,r);
    }
    // If the group size is equal to the cardinal, fill the output with copies of the input
    else if constexpr(Group == card)
    {
      auto r = broadcast_group(w, g , i, lane<Size/2>);
      return that_t(r,r);
    }
    // If the group size is equal to 1, we proceed to a regular broadcast
    else if constexpr(Group == 1)
    {
      return eve::broadcast(w, i, sz);
    }
    // If the input wide is not aggregated and we don't bcast more than 64 bits
    else if constexpr(!eve::has_aggregated_abi_v<Wide> && sizeof(v_t)*Group <= 8)
    {
      using outer_type  = eve::detail::make_integer_t<sizeof(v_t)*Group>;
      using w_t         = eve::as_wide_t<outer_type, fixed<card/Group>>;
      return bit_cast( eve::broadcast(bit_cast(w, as_<w_t>()), i), as_<that_t>() );
    }
    // Otherwise, we need to slice/bcast/combine recursively
    else
    {
      auto const r = compute_half(w, lane<(card >= Size ? Size/2 : Size)>);
      return eve::combine(r,r);
    }
  }

  template<simd_value Wide, std::ptrdiff_t Group, std::ptrdiff_t Index, std::ptrdiff_t Size>
  requires(   (Group >  0) && (Group <= std::min(cardinal_v<Wide>, Size))
          &&  (Index >= 0) && (Index < cardinal_v<Wide>/Group)
          )
  EVE_FORCEINLINE auto broadcast_group_ ( EVE_SUPPORTS(cpu_), logical<Wide> w
                                        , fixed<Group> g, index_t<Index> i, fixed<Size> sz
                                        )
  {
    using abi_t = typename logical<Wide>::abi_type;
    if constexpr( !abi_t::is_wide_logical )
    {
      // Reconstruct mask, swag then turn to mask again
      auto const m = w.mask();
      auto const bg = broadcast_group(m, g,i,sz);
      return to_logical(bg);
    }
    else
    {
      // Use the common implementation
      return bit_cast( broadcast_group(w.mask(),g,i,sz), as(w));
    }
  }

  template<simd_value Wide, std::ptrdiff_t Group, std::ptrdiff_t Index>
  requires(   (Group >  0) && (Group <= cardinal_v<Wide>)
          &&  (Index >= 0) && (Index < cardinal_v<Wide>/Group)
          )
  EVE_FORCEINLINE auto broadcast_group_ ( EVE_SUPPORTS(cpu_), Wide w
                                        , fixed<Group> g, index_t<Index> i
                                        )
  {
    return broadcast_group(w,g,i,cardinal_t<Wide>{});
  }
}
