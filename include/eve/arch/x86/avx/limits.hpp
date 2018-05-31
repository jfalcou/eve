//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_AVX_LIMITS_HPP_INCLUDED
#define EVE_ARCH_X86_AVX_LIMITS_HPP_INCLUDED

#include <eve/arch/x86/avx/tags.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>
#include <cstdint>

namespace eve
{
  template<> struct limits<eve::avx_>
  {
    using parent = eve::sse2_;

    template<typename Sign>
    using largest_integer = std::conditional_t< std::is_same_v<Sign,unsigned>
                                              , std::uint64_t
                                              , std::int64_t
                                              >;

    template<typename Sign>
    using smallest_integer  = std::conditional_t< std::is_same_v<Sign,unsigned>
                                                , std::uint8_t
                                                , std::int8_t
                                                >;

    using largest_real  = double;
    using smallest_real = float;

    static constexpr std::size_t bits   = 256;
    static constexpr std::size_t bytes  = 32;

    using supported_types = detail::types < float,double
                                          , std::int8_t , std::int16_t , std::int32_t , std::int64_t
                                          , std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t
                                          >;
  };
}

#endif
