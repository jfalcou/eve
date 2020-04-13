//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_COMMON_ARITHMETIC_COMPOUNDS_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_COMMON_ARITHMETIC_COMPOUNDS_HPP_INCLUDED

#include <eve/concept/stdconcepts.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/abi.hpp>

// TODO: std:bitcast instead
#include <eve/module/core/function/generic/bit_cast.hpp>

namespace eve::detail
{
  //================================================================================================
  // +=
  //================================================================================================
  template<scalar_value T, value U, typename N, typename ABI>
  EVE_FORCEINLINE decltype(auto) self_add( wide<T,N,ABI>& self, U const& other )
  requires( scalar_value<U> || std::same_as<wide<T,N,ABI>,U> )
  {
    using type = wide<T, N, ABI>;

    if constexpr( scalar_value<U> )               return self_add(self, type{other});
    else if constexpr( std::same_as<type,U> )
    {
      if constexpr(is_emulated_v<ABI>)
      {
        apply<N::value>( [&](auto... I) { ((get<I>(self) += get<I>(other)),...); } );
        return self;
      }
      else if constexpr(is_aggregated_v<ABI>)
      {
        using st_t = typename type::storage_type;
        st_t::for_each( [&](auto const&... I)
                        {
                          ((self.storage().segments[I] += other.storage().segments[I]),...);
                        }
                      );
        return self;
      }
    }
  }

  //================================================================================================
  // -=
  //================================================================================================
  template<scalar_value T, value U, typename N, typename ABI>
  EVE_FORCEINLINE decltype(auto) self_sub( wide<T,N,ABI>& self, U const& other )
  requires( scalar_value<U> || std::same_as<wide<T,N,ABI>,U> )
  {
    using type = wide<T, N, ABI>;

    if constexpr( scalar_value<U> )               return self_sub(self, type{other});
    else if constexpr( std::same_as<type,U> )
    {
      if constexpr(is_emulated_v<ABI>)
      {
        apply<N::value>( [&](auto... I) { ((get<I>(self) -= get<I>(other)),...); } );
        return self;
      }
      else if constexpr(is_aggregated_v<ABI>)
      {
        using st_t = typename type::storage_type;
        st_t::for_each( [&](auto const&... I)
                        {
                          ((self.storage().segments[I] -= other.storage().segments[I]),...);
                        }
                      );
        return self;
      }
    }
  }

  //================================================================================================
  // *=
  //================================================================================================
  template<scalar_value T, value U, typename N, typename ABI>
  EVE_FORCEINLINE decltype(auto) self_mul( wide<T,N,ABI>& self, U const& other )
  requires( scalar_value<U> || std::same_as<wide<T,N,ABI>,U> )
  {
    using type = wide<T, N, ABI>;

    if constexpr( scalar_value<U> )               return self_mul(self, type{other});
    else if constexpr( std::same_as<type,U> )
    {
      if constexpr(is_emulated_v<ABI>)
      {
        apply<N::value>( [&](auto... I) { ((get<I>(self) *= get<I>(other)),...); } );
        return self;
      }
      else if constexpr(is_aggregated_v<ABI>)
      {
        using st_t = typename type::storage_type;
        st_t::for_each( [&](auto const&... I)
                        {
                          ((self.storage().segments[I] *= other.storage().segments[I]),...);
                        }
                      );
        return self;
      }
    }
  }

  //================================================================================================
  // /=
  //================================================================================================
  template<scalar_value T, value U, typename N, typename ABI>
  EVE_FORCEINLINE decltype(auto) self_div( wide<T,N,ABI>& self, U const& other )
  requires( scalar_value<U> || std::same_as<wide<T,N,ABI>,U> )
  {
    using type = wide<T, N, ABI>;

    if constexpr( scalar_value<U> )               return self_div(self, type{other});
    else if constexpr( std::same_as<type,U> )
    {
      if constexpr(is_emulated_v<ABI>)
      {
        apply<N::value>( [&](auto... I) { ((get<I>(self) /= get<I>(other)),...); } );
        return self;
      }
      else if constexpr(is_aggregated_v<ABI>)
      {
        using st_t = typename type::storage_type;
        st_t::for_each( [&](auto const&... I)
                        {
                          ((self.storage().segments[I] /= other.storage().segments[I]),...);
                        }
                      );
        return self;
      }
    }
  }
}

#endif
