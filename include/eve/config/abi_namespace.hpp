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
//!   `abi_O` for `-march=haswell -DNDEBUG`. It is kept short on purpose and is not meant to be read.
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
#  define EVE_NAMESPACE namespace eve::inline EVE_ABI_NAMESPACE
#endif

namespace eve
{
  // Name of the ABI namespace for the current compilation options
#define EVE_ABI_STRING_(x) #x
#define EVE_ABI_STRING(x)  EVE_ABI_STRING_(x)
  inline constexpr std::string_view current_abi_namespace = EVE_ABI_STRING(EVE_ABI_NAMESPACE);
#undef EVE_ABI_STRING
#undef EVE_ABI_STRING_
}
