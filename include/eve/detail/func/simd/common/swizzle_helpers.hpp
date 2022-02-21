//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/func/bit_cast.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
  //----------------------------------------------------------------------------------------------
  // Handle Zeroing
  template<typename Pack, typename Pattern>
  EVE_FORCEINLINE auto process_zeros( Pack const& v, Pattern p ) noexcept
  {
    constexpr auto sz = cardinal_v<Pack>;
    using type = typename Pack::value_type;

    if constexpr( p.has_zeros() )
    {
      // Turn pattern into 0/~0 then mask
      auto const impl = [=](auto... i)
                        {
                          using i_t = as_integer_t<type,unsigned>;
                          constexpr i_t nz = ~i_t(0), zz = i_t(0);
                          return Pack(bit_cast((p(i,sz) == na_ ? zz : nz),as<type>())...);
                        };

      return v & apply<sz>(impl);
    }
    else
    {
      return v;
    }
  }

  //----------------------------------------------------------------------------------------------
  // Pattern to Index wide conversion
  template<simd_value Wide, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto as_indexes(Pattern const&)
  {
    using i_t = as_integer_t<Wide>;
    using c_t = cardinal_t<Wide>;

    return  []<std::size_t... I>(std::index_sequence<I...>)
    {
      Pattern q;
      return i_t{q(I,c_t::value)...};
    }(std::make_index_sequence<c_t::value>{});
  }

  //----------------------------------------------------------------------------------------------
  // Index to bytes conversion
  template<typename Pack, typename Shuffler, std::size_t... I>
  EVE_FORCEINLINE constexpr auto as_bytes_impl(Shuffler p, std::index_sequence<I...> const &)
  {
    constexpr auto sz = Shuffler::size();
    constexpr auto b = sizeof(typename Pack::value_type);

    return values< (p(I/b,sz) == na_ ? 0xFF : p(I/b,sz)*b+I%b)... >{};
  }

  template<typename Pack, typename Shuffler, typename Bytes>
  EVE_FORCEINLINE constexpr auto as_bytes(Shuffler p, as<Bytes> const&) noexcept
  {
    constexpr auto bytes = as_bytes_impl<Pack>(p, std::make_index_sequence<Bytes::size()>{});
    return apply( [](auto... v) { return Bytes{ std::uint8_t(v)... }; }, bytes);
  }
}
