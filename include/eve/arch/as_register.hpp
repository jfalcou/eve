//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/arch/spec.hpp>

#include <eve/arch/cpu/as_register.hpp>

#include <type_traits>
#include <utility>

#if !defined(EVE_NO_SIMD)
#  if defined(EVE_INCLUDE_X86_HEADER)
#    include <eve/arch/x86/as_register.hpp>
#  elif defined(EVE_INCLUDE_POWERPC_HEADER)
#    include <eve/arch/ppc/as_register.hpp>
#  elif defined(EVE_INCLUDE_ARM_SVE_HEADER)
#    include <eve/arch/arm/sve/as_register.hpp>
#  elif defined(EVE_INCLUDE_ARM_NEON_HEADER)
#    include <eve/arch/arm/neon/as_register.hpp>
#  elif defined(EVE_INCLUDE_RISCV_HEADER)
#    include <eve/arch/riscv/as_register.hpp>
#  endif
#endif

namespace eve
{
  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!
  //! @typedef as_register_t
  //! @brief Find proper register type for Type/Lanes/ABI triplet
  //!
  //! Computes the correct register to use to efficiently store `Lanes` elements of type `Type` in
  //! the given ABI and returns it's type.
  //!
  //! @tparam Type  Type of the element to store
  //! @tparam Lanes Number of elements to store
  //! @tparam ABI Current ABI of the plateform
  //! 
  //! @}
  //================================================================================================
#if defined (EVE_DOXYGEN_INVOKED)
  template<typename Type, width_type N, typename ABI>
  using as_register_t = /* Implementation defined */;
#else
  // GCC 16 emits -Wignored-attributes when a SIMD register type (e.g. `__m128`) is used directly
  // as a template argument, due to the `may-alias` attribute. `declval` removes it.
  template<typename T, width_type N, typename ABI>
  using as_register_t = std::remove_cvref_t<decltype(std::declval<decltype(_::as_register<T, N, ABI>)>())>;
#endif

  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!
  //! @typedef as_logical_register_t
  //! @brief Find proper logical register type for Type/Lanes/ABI triplet
  //!
  //! Computes the correct logical register to use to efficiently store `Lanes` elements of type `Type` in
  //! the given ABI and returns it's type.
  //!
  //! @tparam Type  Type of the element to store
  //! @tparam Lanes Number of elements to store
  //! @tparam ABI Current ABI of the plateform
  //! 
  //! @}
  //================================================================================================
#if defined (EVE_DOXYGEN_INVOKED)
  template<typename Type, width_type N, typename ABI>
  using as_logical_register_t = /* Implementation defined */;
#else
  template<typename T, width_type N, typename ABI>
  using as_logical_register_t = std::remove_cvref_t<decltype(std::declval<decltype(_::as_logical_register<T, N, ABI>)>())>;
#endif
}