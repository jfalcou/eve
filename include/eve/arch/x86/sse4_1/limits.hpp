//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SSSE4_1_LIMITS_HPP_INCLUDED
#define EVE_ARCH_X86_SSSE4_1_LIMITS_HPP_INCLUDED

#include <eve/arch/x86/sse4_1/tags.hpp>
#include <eve/arch/x86/sse2/limits.hpp>

namespace eve
{
  template<> struct limits<eve::sse4_1_> : limits<eve::sse2_> {};
}

#endif
