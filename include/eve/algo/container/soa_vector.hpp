//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/copy.hpp>
#include <eve/algo/equal.hpp>
#include <eve/algo/fill.hpp>
#include <eve/algo/mismatch.hpp>
#include <eve/algo/views/convert.hpp>
#include <eve/algo/container/detail/soa_storage.hpp>
#include <eve/memory/aligned_allocator.hpp>
#include <eve/product_type.hpp>
#include <eve/traits.hpp>
#include <eve/assert.hpp>

#include <cstddef>
#include <memory>

namespace eve::algo
{
  struct no_init_t {};

  //! Markup to trigger construction of container without initialisation of content
  inline constexpr no_init_t no_init = {};

  //================================================================================================
  //! @addtogroup memory
  //! @{
  //!   @brief SIMD-aware container for product types
  //!
  //!   **Required header:** `#include <eve/memory/soa_vector.hpp>`
  //!
  //!   soa_vector is a container similar to `std::vector` but optimized to store
  //!   [product types](eve::product_type) using a Structure Of Array layout compatible with SIMD
  //!   processing.
  //!
  //!   @tparam Type  Value type stored inside `eve::soa_vector`
  //! @}
  //================================================================================================
  template< eve::product_type Type
          , eve::simd_allocator Allocator = eve::aligned_allocator<unsigned char, eve::fixed<64>>
          >
  struct soa_vector
  {
    private:
    using storage_type        = detail::soa_storage<Type,Allocator>;
    using const_storage_type  = detail::soa_storage<Type,Allocator> const;

    public:
    //!=============================================================================================
    //! @name Member types
    //! @{
    //==============================================================================================
    //! Type of data stored in the container
    using value_type = Type;

    //!   @brief pointer and iterator types.
    //!   pointer*  - are eve::algo::views::zip_iterator over fields (no conversion to type, just flat fields)
    //!   iterator* - are a pointer, converter to the Type.
    //!   They all satisfy eve::algo::relaxed_iterator but not std::iterator

    using iterator               = decltype(views::convert(storage_type{}.data() , as<value_type>{}));
    using const_iterator         = decltype(views::convert(std::declval<storage_type const>().data(), as<value_type>{}));
    using iterator_aligned       = decltype(views::convert(storage_type{}.data_aligned(), as<value_type>{}));
    using const_iterator_aligned = decltype(views::convert(std::declval<storage_type const>().data_aligned(), as<value_type>{}));

    using pointer               = iterator;
    using const_pointer         = const_iterator;
    using pointer_aligned       = iterator_aligned;
    using const_pointer_aligned = const_iterator_aligned;

    using size_type = std::size_t;

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Constructors
    //! @{
    //==============================================================================================

    //! Constructs an empty container with a custom `Allocator`.
    explicit soa_vector(Allocator a) : storage(a), size_{} {}

    //! Constructs an empty container.
    explicit soa_vector() : soa_vector(Allocator{}) {}

    //! Constructs the container with `n` default-inserted instances of `Type` and a custom `Allocator`.
    explicit soa_vector(size_type n, Allocator a) : soa_vector(n, value_type{}, a) {}

    //! Constructs the container with `n` default-inserted instances of `Type`.
    explicit soa_vector(size_type n) : soa_vector(n, value_type{}, Allocator{}) {}

    //! Constructs the container with `n` default-inserted instances of `Type` and a custom `Allocator`.
    soa_vector(no_init_t, size_type n, Allocator a) : storage(a,n), size_{n} {}

    //! Constructs the container with `n` default-inserted instances of `Type`.
    soa_vector(no_init_t, size_type n) : soa_vector(no_init,n,Allocator{}) {}

    //! Constructs the container with `n` copies of elements with `value` value and a custom `Allocator`.
    soa_vector(size_type n, value_type v, Allocator a) : soa_vector(no_init,n,a) { fill(v);  }

    //! Constructs the container with `n` copies of elements with `value` value.
    soa_vector(size_type n, value_type v) : soa_vector(n,v,Allocator{}) {}

    //! Constructs the container with the contents of the initializer list `l`.
    soa_vector( std::initializer_list<Type> l, Allocator a)
              : storage(a, l.size()), size_{l.size()}
    {
      auto ptr = l.begin();
      for(size_type i = 0; i < size(); ++i)
      {
        eve::write(*ptr++, begin()+i);
      }
    }

    //! Constructs the container with the contents of the initializer list `l`.
    soa_vector( std::initializer_list<Type> l ) : soa_vector(l,Allocator{}) {}

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Capacity
    //! @{
    //==============================================================================================
    //! Returns the number of elements in the container
    EVE_FORCEINLINE size_type size()  const noexcept { return size_; }

    //! Returns the number of elements that the container has currently allocated space for
    EVE_FORCEINLINE size_type capacity()  const noexcept { return storage.capacity(); }

    //! Requests the removal of unused capacity.
    EVE_FORCEINLINE void shrink_to_fit() { grow(size(), size()); }

    //! Checks if the container has no elements
    EVE_FORCEINLINE bool empty() const noexcept { return !size(); }

    //! @brief Increase the capacity of the vector to a value that's greater or equal to `n`.
    //! If `n` is greater than the current capacity(), new storage is allocated and all iterators,
    //! including the past-the-end iterator, and all references to the elements are invalidated.
    //! Otherwise, the method does nothing.
    //! @warning reserve() does not change the size of the vector.
    //! @param n New capacity of the `eve::soa_vector`
    void reserve(size_type n)
    {
      if(n > capacity())
      {
        // Grow capacity to n
        auto const sz = size_;
        grow(n, size());
        size_ = sz;
     }
    }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Modifiers
    //! @{
    //==============================================================================================
    //! @brief Clear the contents of the container.
    void clear() { size_ = 0; }

    //! @brief Removes an element from the container.
    //! Has the same invalidation semantics as std::vector.
    //! end() iterator is not a valid pos.
    iterator erase(const_iterator pos)
    {
      auto idx = pos - cbegin();
      return erase_impl(idx,idx+1);
    }

    //! @brief Removes the elements in the range [first, last)
    //! Empty range is OK, does nothing
    iterator erase(const_iterator f, const_iterator l)
    {
      return erase_impl(f - cbegin(),l - cbegin());
    }

    //! @brief Appends the given element value to the end of the container.
    //! If the new size() is greater than capacity() then all iterators and references (including
    //! the past-the-end iterator) are invalidated. Otherwise only the past-the-end iterator is
    //! invalidated.
    //! @param value [Value](@eve::vectorizable) to append
    EVE_FORCEINLINE void push_back(value_type const& value) noexcept
    {
      if(size_ != capacity()) eve::write(value, begin()+size_);
      else                    push_slow_path(value);
      size_++;
    }

    //! @brief Removes the last element of the container.
    //! Calling pop_back on an empty container results in undefined behavior.
    //! Iterators and references to the last element, as well as the end() iterator, are invalidated.
    EVE_FORCEINLINE void pop_back() noexcept
    {
      EVE_ASSERT(!empty(), "soa_vector::pop_back() was called on empty container");
      size_--;
    }

    //! @brief Resizes the container to contain count elements.
    //!
    //! If the current size is greater than `n`, the container is reduced to its first `n` elements.
    //! If the current size is less than `n`, additional elements are appended. Those elements are
    //! either default-inserted or copied if `value` is provided.
    //! @param n      new size of the container
    //! @param value  the value to initialize the new elements with
    void resize(size_type n, value_type value)
    {
      auto sz = size_;
      if(n > capacity())
      {
        // Grow twice or up to n per resize
        grow(std::max(2*size(), n), size());
      }

      // If needed, fill with new data
      if(n > sz) fill(sz, capacity(), value );
      size_ = n;
    }

    void resize(size_type n) { resize(n, value_type{}); }

    //! @brief Exchanges the contents of the container with those of `other`.
    //! Does not invoke any move, copy, or swap operations on individual elements.
    //! All iterators and references remain valid. The past-the-end iterator is invalidated.
    void swap(soa_vector& other) noexcept
    {
      storage.swap(other.storage);
      std::swap(size_, other.size_);
    }

    //! @brief Swaps the contents of `lhs` and `rhs` by calling `lhs.swap(rhs)`.
    friend EVE_FORCEINLINE void swap(soa_vector &lhs, soa_vector &rhs) noexcept { lhs.swap(rhs); }

    Allocator get_allocator() { return storage.get_allocator(); }

    //==============================================================================================
    //! @}
    //==============================================================================================

    public:
    //==============================================================================================
    //! @name Element access
    //! @{
    //==============================================================================================
    //! Returns a zipped aligned pointer to the beginning
    EVE_FORCEINLINE auto data_aligned() { return begin_aligned(); }

    //! Returns a zipped aligned pointer to the beginning
    EVE_FORCEINLINE auto data_aligned()  const  { return begin_aligned(); }

    //! Returns a zipped pointer to the beginning
    EVE_FORCEINLINE auto data() { return begin(); }

    //! Returns a constant zipped pointer to the beginning
    EVE_FORCEINLINE auto data() const { return begin(); }

    //! @brief Returns the value of the `i`th element of the container
    //! @param i Index of the value to retrieve
    EVE_FORCEINLINE value_type get(size_type i) const { return eve::read(begin() + i); }

    //! @brief Modify the value of the `i`th element of the container
    //! @param i Index of the value to write
    //! @param v Value to write
    EVE_FORCEINLINE void set(size_type i, value_type const& v)
    {
      return eve::write(v, begin() + i);
    }

    //! @brief Fill the soa_vector with a given value
    void fill(value_type v) { eve::algo::fill ( *this, v ); }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Iterators
    //! @{
    //==============================================================================================
    //! Returns an aligned iterator to the beginning
    EVE_FORCEINLINE auto begin_aligned() -> iterator_aligned
    {
      return views::convert(storage.data_aligned(), eve::as<Type>{});
    }

    //! Returns an aligned iterator to the beginning
    EVE_FORCEINLINE auto begin_aligned()  const -> const_iterator_aligned
    {
      return views::convert(storage.data_aligned(), eve::as<Type>{});
    }

    //! Returns a constant aligned iterator to the beginning
    EVE_FORCEINLINE auto cbegin_aligned() const -> const_iterator_aligned { return begin_aligned(); }

    //! Returns an iterator to the beginning
    EVE_FORCEINLINE auto begin() -> iterator
    {
      return views::convert(storage.data(), eve::as<Type>{});
    }

    //! Returns an iterator to the beginning
    EVE_FORCEINLINE auto begin()  const -> const_iterator
    {
      return views::convert(storage.data(), eve::as<Type>{});
    }

    //! Returns a constant iterator to the beginning
    EVE_FORCEINLINE auto cbegin() const -> const_iterator { return begin(); }

    //! Returns an iterator to the end
    EVE_FORCEINLINE auto end()  -> iterator  { return begin() + size(); }

    //! Returns an iterator to the end
    EVE_FORCEINLINE auto end()  const -> const_iterator { return begin() + size(); }

    //! Returns a constant iterator to the end
    EVE_FORCEINLINE auto cend() const -> const_iterator { return end(); }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Comparisons and ordering
    //! @{
    //==============================================================================================
    friend bool operator==(soa_vector const& lhs, soa_vector const& rhs)
    {
      if( lhs.size() != rhs.size() ) return false;
      return eve::algo::equal(lhs, rhs.begin_aligned());
    }

    friend bool operator!=(soa_vector const& lhs, soa_vector const& rhs)
    {
      return !(lhs == rhs);
    }

    //==============================================================================================
    //! @}
    //==============================================================================================

    friend std::ostream& operator<<(std::ostream& os, soa_vector const& v)
    {
      os << "{ ";
      for(std::size_t i=0; i<v.size();++i) os << v.get(i) << " ";
      os << '}';
      return os;
    }

    template <typename Traits, typename Self>
    requires std::same_as<std::remove_reference_t<Self>, soa_vector>
    EVE_FORCEINLINE friend auto tagged_dispatch(algo::preprocess_range_, Traits tr, Self& self)
    {
      return algo::preprocess_range(tr, algo::as_range(self.begin_aligned(), self.end()));
    }

  private:

    void grow(std::size_t new_capacity, std::size_t old_size)
    {
      soa_vector that(no_init, new_capacity, get_allocator());
      eve::algo::copy(*this, that.begin_aligned());
      *this = std::move(that);
      size_ = old_size;
    }

    void fill(std::size_t first, std::size_t last, value_type const& v)
    {
      eve::algo::fill(algo::as_range(begin() + first, begin() + last), v );
    }

    iterator erase_impl(std::ptrdiff_t f_idx, std::ptrdiff_t l_idx)
    {
      std::ptrdiff_t sz = l_idx - f_idx;
      eve::algo::copy_backward( algo::as_range(begin() + l_idx, end())
                              , algo::as_range(begin() + f_idx, end() - sz)
                              );
      size_ -= sz;
      return begin() + f_idx;
    }

    void push_slow_path(value_type const& value)
    {
      grow(2*size_+1, size());
      eve::write(value, begin()+size_);
    }

    storage_type  storage;
    std::size_t   size_;
  };
}
