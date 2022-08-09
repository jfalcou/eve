//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>

#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/soa_ptr.hpp>
#include <eve/traits/as_wide.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup memory
  //! @{
  //================================================================================================
  //! @brief A stack buffer for a simd-value
  //!
  //! @tparam T simd value type
  //!
  //! Use `ptr()` member function to get a pointer compatible with T to operate with.
  //================================================================================================

  template <simd_value T>
  struct alignas( sizeof(element_type_t<T>) * T::size() ) stack_buffer
  {
    auto ptr()       { return eve::as_aligned(buff.data(), lane<T::size()>); }
    auto ptr() const { return eve::as_aligned(buff.data(), lane<T::size()>); }

    private:
      std::array<element_type_t<T>, T::size()> buff;
  };

  template <simd_value T>
    requires product_type<element_type_t<T>>
  struct stack_buffer<T>
  {
    auto ptr()       { return kumi::apply([](auto& ...buff) { return soa_ptr{buff.ptr()... }; }, buffs); }
    auto ptr() const { return kumi::apply([](auto& ...buff) { return soa_ptr{buff.ptr()... }; }, buffs); }

   private:
    static auto compute_buffs_type()
    {
      return kumi::map([]<typename WideField>(WideField) { return stack_buffer<WideField>{}; }, T{});
    }

    decltype(compute_buffs_type()) buffs;
  };

  //================================================================================================
  //! @}
  //================================================================================================
}
