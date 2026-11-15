//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include <eve/config/abi_namespace_impl.hpp>

#define EVE_ABI_CASE_STRING_(x) #x
#define EVE_ABI_CASE_STRING(x)  EVE_ABI_CASE_STRING_(x)
constexpr std::string_view tag = EVE_ABI_CASE_STRING(EVE_ABI_NAMESPACE);
constexpr bool             ok  = eve::abi_namespace_matches(tag, EVE_ABI_EXPECTED);
#undef EVE_ABI_CASE_STRING
#undef EVE_ABI_CASE_STRING_
