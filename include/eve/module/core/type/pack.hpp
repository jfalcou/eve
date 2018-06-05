//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_TYPE_PACK_HPP_INCLUDED
#define EVE_MODULE_CORE_TYPE_PACK_HPP_INCLUDED

#include <eve/arch/spec.hpp>
#include <eve/arch/limits.hpp>
#include <eve/ext/as_pack.hpp>
#include <eve/module/core/detail/pack.hpp>
#include <eve/module/core/type/logical.hpp>

namespace eve { namespace ext
{
  // Wrapper for SIMD registers holding arithmetic types
  template<typename Type, typename Size>
  struct as_pack< Type, Size
                , std::enable_if_t<   std::is_arithmetic_v<Type>
                                  &&  (Size::value <= expected_cardinal_v<Type>)
                                  >
                >
  {
    using abi_type  = ext::abi_of_t<Type,Size::value>;
    using type      = eve::detail::pack<Type,Size,abi_type>;
  };

  // Wrapper for SIMD registers holding logical type
  template<typename Type, typename Size>
  struct as_pack< logical<Type>, Size
                , std::enable_if_t<   std::is_arithmetic_v<Type>
                                  &&  (Size::value <= expected_cardinal_v<Type>)
                                  >
                >
  {
    using abi_type  = ext::abi_of_t<logical<Type>,Size::value>;
    using type      = eve::detail::pack<logical<Type>,Size,abi_type>;
  };
} }

#endif
