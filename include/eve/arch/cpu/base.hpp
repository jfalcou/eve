//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/function/friends.hpp>
#include <eve/detail/function/lookup.hpp>
#include <eve/detail/function/slice.hpp>
#include <eve/detail/function/subscript.hpp>

namespace eve::detail
{
  // Storage-only element of wide/logical
  template<typename Storage> struct wide_storage
  {
    using storage_type = Storage;

    wide_storage() {}
    wide_storage(storage_type const &r) : data_(r) {}

    EVE_FORCEINLINE storage_type const& storage() const & noexcept { return data_; }
    EVE_FORCEINLINE storage_type &      storage() &       noexcept { return data_; }
    EVE_FORCEINLINE storage_type        storage() &&      noexcept { return data_; }

    EVE_FORCEINLINE operator storage_type const& () const &  noexcept { return data_; }
    EVE_FORCEINLINE operator storage_type&       () &        noexcept { return data_; }
    EVE_FORCEINLINE operator storage_type        () &&       noexcept { return data_; }

    private:
    Storage data_;
  };

  // Size-only element of wide/logical
  template<typename Size> struct wide_cardinal
  {
    using cardinal_type = Size;
    using size_type     = std::ptrdiff_t;

    static constexpr size_type  static_size  = Size::value;

    static EVE_FORCEINLINE constexpr size_type size()     noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr size_type max_size() noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr bool      empty()    noexcept { return false; }
  };

  // Common operations on wide/logical
  template<typename Derived> struct wide_ops
  {
    //==============================================================================================
    // Misc.
    static EVE_FORCEINLINE constexpr auto alignment() noexcept
    {
      return Derived::static_alignment;
    }

    EVE_FORCEINLINE Derived& operator=(scalar_value auto v) noexcept
    {
      Derived that(v);
      swap(that);
      return self();
    }

    EVE_FORCEINLINE void swap(Derived& other) noexcept
    {
      std::swap(self().storage(), other.storage());
    }

    //==============================================================================================
    // Shape related functions
    EVE_FORCEINLINE auto slice() const requires(cardinal_v<Derived> > 1)
    {
      return detail::slice(self());
    }

    EVE_FORCEINLINE auto slice(auto s) const requires(cardinal_v<Derived> > 1)
    {
      return detail::slice(self(), s);
    }

    template<typename Index>
    EVE_FORCEINLINE auto operator[](wide<Index,cardinal_t<Derived>> const& idx) const noexcept
    {
      return lookup(self(),idx);
    }

    //==============================================================================================
    // Value access functions
    EVE_FORCEINLINE void set(std::size_t i, scalar_value auto v) noexcept
    {
      detail::insert(self(), i, v);
    }

    EVE_FORCEINLINE auto operator[](std::size_t i) const noexcept
    {
      return detail::extract(self(), i);
    }

    EVE_FORCEINLINE auto back()  const noexcept { return (*this)[cardinal_v<Derived>-1]; }
    EVE_FORCEINLINE auto front() const noexcept { return (*this)[0]; }

    //==============================================================================================
    // Common hidden friend operators
    friend EVE_FORCEINLINE auto operator!(wide_ops const& v) noexcept
    {
      return detail::self_lognot(v.self());
    }

    private:
    EVE_FORCEINLINE Derived&        self()        { return static_cast<Derived&>(*this); }
    EVE_FORCEINLINE Derived const&  self() const  { return static_cast<Derived const&>(*this); }
  };
}
