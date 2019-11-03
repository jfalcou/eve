//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_CPU_AS_REGISTER_HPP_INCLUDED
#define EVE_ARCH_CPU_AS_REGISTER_HPP_INCLUDED

#include <eve/ext/as_register.hpp>
#include <eve/ext/as_wide.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/detail/meta/tools.hpp>
#include <eve/forward.hpp>
#include <array>

namespace eve::ext
{
  template<typename Type, typename Cardinal>
  struct as_register<Type, Cardinal, eve::emulated_>
  {
    using type = std::array<Type, Cardinal::value>;
  };

  template<typename Type, typename Cardinal>
  struct as_register<Type, Cardinal, eve::aggregated_>
  {
    struct type
    {
      static constexpr auto small_size  = expected_cardinal_v<Type>;
      static constexpr auto replication = Cardinal::value/small_size;

      using value_type    = as_wide_t<Type, fixed<expected_cardinal_v<Type>>>;
      using segment_type  = std::array<value_type,replication>;
      segment_type        segments;

      template<typename Func> void apply(Func const& f) noexcept
      {
        detail::apply<replication>( [&](auto const&... I) { f(segments[I]...); } );
      }

      template<typename Func> void apply(Func const& f) const noexcept
      {
        detail::apply<replication>( [&](auto const&... I) { f(segments[I]...); } );
      }
    };
  };
}

#endif
