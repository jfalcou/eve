//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/function/patterns/slide_right.hpp>
#include <eve/detail/function/patterns/slide_left.hpp>
#include <eve/detail/function/patterns/unpack.hpp>
#include <eve/patterns.hpp>

namespace eve::detail
{
  template<typename Target, typename Wide, typename P>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(vmx_), any_match const&
                                  , as_<Target> , P const& p
                                  , Wide const& v
                                  )
  {
    using bytes_t     = typename Target::template rebind<std::uint8_t,fixed<16>>;

    Target that = vec_perm( v.storage(), v.storage()
                          , as_bytes<Wide>(p,as_<bytes_t>()).storage()
                          );

    return process_zeros(that,p);
  }

  template<typename Target, typename Wide, typename P>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(vmx_), zero_match const&
                                  , as_<Target> , P const&
                                  , Wide const& v
                                  )
  {
    return Target{vec_xor(v.storage(),v.storage())};
  }

  template<typename Target, typename Wide, std::ptrdiff_t I0, std::ptrdiff_t... I>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(vmx_), broadcast_match const&
                                  , as_<Target> , pattern_<I0,I...> const&
                                  , Wide const& v
                                  )
  {
    return Target{vec_splat(v.storage(),I0)};
  }

  template<typename Wide, typename Target, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(vmx_), slide_left const&
                                  , as_<Target>, Pattern const&, Wide const& v
                                  )
  {
    using e_t = element_type_t<Wide>;

    if constexpr( std::same_as<e_t, double> )
    {
      return Target{v[1],0};
    }
    else
    {
      constexpr auto c   = Pattern::size(cardinal_v<Wide>);
      constexpr auto sft = Pattern{}(0,c);
      constexpr auto s   = (sizeof(e_t) * sft) << 3;

      __vector unsigned char shift = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,s};

      return Target( vec_slo(v.storage(), shift) );
    }
  }

  template<typename Wide, typename Target, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(vmx_), slide_right const&
                                  , as_<Target>, Pattern const&, Wide const& v
                                  )
  {
    using e_t = element_type_t<Wide>;

    if constexpr( std::same_as<e_t, double> )
    {
      return Target{0,v[0]};
    }
    else
    {
      constexpr auto c   = Pattern::size(cardinal_v<Wide>);
      constexpr auto sft = c - Pattern{}(c-1,c) - 1;
      constexpr auto s   = (sizeof(e_t) * sft) << 3;

      __vector unsigned char shift = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,s};

      return Target( vec_sro(v.storage(), shift) );
    }
  }

  template<typename Wide, typename Target, shuffle_pattern Pattern>
  EVE_FORCEINLINE Target  do_swizzle( EVE_SUPPORTS(vmx_), unpack_match const&
                                    , as_<Target>, Pattern const&, Wide const& r
                                    )
  {
    using e_t = element_type_t<Wide>;

    // Type-agnostic bit-shifting
    [[maybe_unused]] constexpr auto shifter = []<typename N>(auto v, N const&)
    {
      if constexpr( N::value != 0)
      {
        constexpr auto offset = N::value << 3;
        __vector unsigned char s = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,offset};
        return Wide{vec_slo( v.storage(), s )};
      }
      else
      {
        return v;
      }
    };

    constexpr Pattern p{};

    constexpr auto p0     = p(0,Wide::static_size);
    constexpr auto p1     = p(1,Wide::static_size);

    // ---- Variants of unpacklo
    if constexpr( unpack_match::is_low(p, as_<Wide>()) )
    {
      constexpr auto shift  = p0 == -1 ? p1 : p0;

      constexpr std::integral_constant<std::size_t, sizeof(e_t)*shift> shifting = {};
      auto sr = shifter(r, shifting );

            if constexpr( p0 == -1) return vec_mergeh(Target(0).storage(),sr.storage());
      else  if constexpr( p1 == -1) return vec_mergeh(sr.storage(),Target(0).storage());
      else                          return vec_mergeh(sr.storage(),sr.storage());
    }
    else
    {
      constexpr auto shift  = (p0 == -1 ? p1 : p0) - Wide::static_size/2;

      constexpr std::integral_constant<std::size_t, sizeof(e_t)*shift> shifting = {};
      auto sr = shifter(r, shifting );

            if constexpr( p0 == -1) return vec_mergel(Target(0).storage(),sr.storage());
      else  if constexpr( p1 == -1) return vec_mergel(sr.storage(),Target(0).storage());
      else                          return vec_mergel(sr.storage(),sr.storage());
    }
  }
}
