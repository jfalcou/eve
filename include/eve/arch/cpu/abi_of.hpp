//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_CPU_ABI_OF_HPP_INCLUDED
#define EVE_ARCH_CPU_ABI_OF_HPP_INCLUDED

#include <eve/arch/cpu/tags.hpp>

namespace eve { namespace ext
{
  template<typename Type, int Cardinal, typename EnableIf>
  struct abi_of
  {
    using type = ::eve::emulated_;
  };
} }

#endif
