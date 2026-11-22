//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/deps/kumi.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/soa_ptr.hpp>
#include <eve/traits/as_wide.hpp>


EVE_NAMESPACE
{
  //================================================================================================
  //! @addtogroup eve_memory
  //! @{
  //================================================================================================
  //! @brief An uninitialized stack buffer for `N` consecutive registers of a simd value.
  //!
  //! @tparam T simd value type
  //! @tparam N number of registers (defaults to 1)
  //!
  //! Uses `ptr()` member function to get a pointer compatible with T to operate with.
  //! The pointer is aligned on `T`'s width and points to `N * T::size()` elements.
  //================================================================================================
  template <simd_value T, std::ptrdiff_t N = 1>
  struct alignas( sizeof(element_type_t<T>) * T::size() ) stack_buffer
  {
    static_assert(N > 0, "stack_buffer needs at least one register");
    static constexpr std::ptrdiff_t registers = N;

    auto ptr()       { return eve::as_aligned(buff.data(), lanes_t<T::size()>{}); }
    auto ptr() const { return eve::as_aligned(buff.data(), lanes_t<T::size()>{}); }

    private:
      std::array<element_type_t<T>, T::size() * N> buff;
  };

  template <simd_value T, std::ptrdiff_t N>
    requires eve::product_type<element_type_t<T>>
  struct stack_buffer<T, N>
  {
    static constexpr std::ptrdiff_t registers = N;

    auto ptr()       { return kumi::apply([](auto& ...buff) { return soa_ptr{buff.ptr()... }; }, buffs); }
    auto ptr() const { return kumi::apply([](auto& ...buff) { return soa_ptr{buff.ptr()... }; }, buffs); }

   private:
    static auto compute_buffs_type()
    {
      return kumi::map([]<typename WideField>(WideField) { return stack_buffer<WideField, N>{}; }, T{});
    }

    decltype(compute_buffs_type()) buffs;
  };

  //================================================================================================
  //! @}
  //================================================================================================
}
