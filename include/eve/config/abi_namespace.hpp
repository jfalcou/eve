//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/config/options.hpp>

#include <string_view>

//==================================================================================================
//! @addtogroup eve_arch
//! @{
//!   @def EVE_ABI_NAMESPACE
//!   @brief Expands to an identifier that is unique to the current compilation configuration.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   The identifier depends on the instruction sets and **EVE** options used to compile, for example
//!   `He` for `-mavx2 -mf16c -DNDEBUG`. It is kept short on purpose and is not meant to be read.
//!
//!   **EVE** uses it as the name of an inline namespace, so that multiple versions of the same code,
//!   compiled with different configurations, can be linked into one binary without causing ODR
//!   violations. ODR violations can still come from other namespaces, but **EVE**'s own symbols
//!   mostly shouldn't cause them.
//!
//!   You can choose the name yourself by defining `EVE_ABI_NAMESPACE` before including **EVE**.
//!   If you give the same name to translation units compiled with different options, keeping them
//!   apart is then up to you.
//!
//!   To protect your own code that depends on compilation options in the same way, put it in an
//!   inline namespace named after the same macro:
//!
//!   @code
//!   namespace mylib::inline EVE_ABI_NAMESPACE
//!   {
//!     float sum(float const* data, std::size_t size);
//!   }
//!   @endcode
//! @}
//==================================================================================================
#if defined(EVE_DOXYGEN_INVOKED)
#  define EVE_ABI_NAMESPACE
#elif !defined(EVE_ABI_NAMESPACE)

#  include <eve/config/abi_namespace_impl.hpp>

#endif

//==================================================================================================
//! @addtogroup eve_arch
//! @{
//!   @def EVE_NAMESPACE
//!   @brief Opens the namespace that holds all of **EVE**, `eve::EVE_ABI_NAMESPACE`, for customization
//!   purposes.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   `EVE_NAMESPACE` expands to `namespace eve::inline EVE_ABI_NAMESPACE`. On recent compilers, you can
//!   simply reopen `namespace eve` or `namespace eve::_`. If your compiler doesn't implement
//!   [CWG 2061](https://cplusplus.github.io/CWG/issues/2061.html), use `EVE_NAMESPACE` or
//!   `EVE_NAMESPACE::_` instead as a workaround.
//! @}
//==================================================================================================
#if defined(EVE_DOXYGEN_INVOKED)
#  define EVE_NAMESPACE namespace eve
#else
#  define EVE_NAMESPACE EVE_ABI_CHECK namespace eve::inline EVE_ABI_NAMESPACE
#endif

#define EVE_ABI_STRING_(x) #x
#define EVE_ABI_STRING(x)  EVE_ABI_STRING_(x)

// Just `namespace eve`, spelled out so that it doesn't read as a forgotten EVE_NAMESPACE: what is
// declared there keeps the same ABI under every set of compilation options.
#define EVE_ABI_INDEPENDENT_NAMESPACE namespace eve

EVE_ABI_INDEPENDENT_NAMESPACE
{
  // Whether the ABI namespace is spelled with these letters, which no macro can replace
  constexpr bool abi_namespace_matches(std::string_view actual, std::string_view api, auto... digits)
  {
    char const tail[] = { digits... };
    return actual.starts_with(api) && actual.substr(api.size()) == std::string_view(tail, sizeof...(digits));
  }
}

// A macro named like the ABI namespace, or like a part of it, changes the name: stop right there
#if defined(EVE_ABI_EXPECTED)
#  define EVE_ABI_CHECK                                                                             \
  static_assert( ::eve::abi_namespace_matches(EVE_ABI_STRING(EVE_ABI_NAMESPACE), EVE_ABI_EXPECTED)  \
               , "[EVE] - A macro named like the ABI namespace changes it, see EVE_ABI_NAMESPACE");
#else
#  define EVE_ABI_CHECK
#endif

// Nested namespaces other than eve::_ put the ABI namespace last, so that they can also hold parts
// that are independent of the compilation options.
#if defined(EVE_DOXYGEN_INVOKED)
#  define EVE_ALGO_NAMESPACE         namespace eve::algo
#  define EVE_ALGO_VIEWS_NAMESPACE   namespace eve::algo::views
#  define EVE_VIEWS_NAMESPACE        namespace eve::views
#  define EVE_PLATFORM_NAMESPACE     namespace eve::platform
#  define EVE_EXPERIMENTAL_NAMESPACE namespace eve::experimental
#else
#  define EVE_ALGO_NAMESPACE         EVE_ABI_CHECK namespace eve::algo::inline EVE_ABI_NAMESPACE
#  define EVE_ALGO_VIEWS_NAMESPACE   EVE_ABI_CHECK namespace eve::algo::views::inline EVE_ABI_NAMESPACE
#  define EVE_VIEWS_NAMESPACE        EVE_ABI_CHECK namespace eve::views::inline EVE_ABI_NAMESPACE
#  define EVE_PLATFORM_NAMESPACE     EVE_ABI_CHECK namespace eve::platform::inline EVE_ABI_NAMESPACE
#  define EVE_EXPERIMENTAL_NAMESPACE EVE_ABI_CHECK namespace eve::experimental::inline EVE_ABI_NAMESPACE
#endif

EVE_NAMESPACE
{
  // Name of the ABI namespace for the current compilation options
  inline constexpr std::string_view current_abi_namespace = EVE_ABI_STRING(EVE_ABI_NAMESPACE);
}
