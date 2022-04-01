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
#include <eve/algo/views/convert.hpp>
#include <eve/algo/container/detail/soa_storage2.hpp>
#include <eve/memory/aligned_allocator.hpp>
#include <eve/product_type.hpp>
#include <eve/traits.hpp>
#include <eve/assert.hpp>

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
    public:

    using storage_t = detail::soa_storage<Type,Allocator>;

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

    using pointer               = decltype(storage_t{}.data());
    using const_pointer         = decltype(std::declval<storage_t const>().data());
    using pointer_aligned       = decltype(storage_t{}.data_aligned());
    using const_pointer_aligned = decltype(std::declval<storage_t const>().data_aligned());

    using iterator               = decltype(views::convert(pointer{}              , as<value_type>{}));
    using const_iterator         = decltype(views::convert(const_pointer{}        , as<value_type>{}));
    using iterator_aligned       = decltype(views::convert(pointer_aligned{}      , as<value_type>{}));
    using const_iterator_aligned = decltype(views::convert(const_pointer_aligned{}, as<value_type>{}));

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Constructors
    //! @{
    //==============================================================================================

    //! Constructs an empty container.
    explicit soa_vector(Allocator a = Allocator{}) : storage(a), size_{} {}

    //! Constructs the container with `n` default-inserted instances of `Type`.
    explicit  soa_vector(std::size_t n, Allocator a = Allocator{})
            : soa_vector(n, value_type{}, a)
    {}

    //! Constructs the container with `n` default-inserted instances of `Type`.
    soa_vector(no_init_t, std::size_t n, Allocator a = Allocator{})
            : storage(a,n), size_{n}
    {}

    //! Constructs the container with `n` copies of elements with `value` value.
    soa_vector(std::size_t n, value_type v, Allocator a = Allocator{})
              : soa_vector(no_init,n,a)
    {
      fill(v);
    }

    //! Constructs the container with the contents of the initializer list `l`.
    soa_vector( std::initializer_list<Type> l, Allocator a = Allocator{})
              : storage(a, l.size()), size_{l.size()}
    {
      auto ptr = l.begin();
      for(std::size_t i = 0;i < size(); ++i)
      {
        eve::write(*ptr++, begin()+i);
      }
    }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Capacity
    //! @{
    //==============================================================================================
    //! Returns the number of elements in the container
    EVE_FORCEINLINE std::size_t size()  const noexcept { return size_; }

    //! Returns the number of elements that the container has currently allocated space for
    EVE_FORCEINLINE std::size_t capacity()  const noexcept { return storage.capacity_; }

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
    void reserve(std::size_t n)
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
    iterator erase(const_iterator pos) { return erase(pos, pos+1); }

    //! @brief Removes the elements in the range [first, last)
    //! Empty range is OK, does nothing
    iterator erase(const_iterator f, const_iterator l)
    {
      EVE_ASSERT(!empty(), "soa_vector::erase() was called on empty container");

      std::ptrdiff_t distance_f = f - cbegin();
      std::ptrdiff_t distance_l = l - cbegin();
      std::ptrdiff_t sz         = distance_l - distance_f;

      eve::algo::copy_backward( algo::as_range(l, cend())
                              , algo::as_range(begin() + distance_l - sz, end() - sz)
                              );
      size_ -= sz;
      return begin() + distance_f;
    }

    //! @brief Appends the given element value to the end of the container.
    //! If the new size() is greater than capacity() then all iterators and references (including
    //! the past-the-end iterator) are invalidated. Otherwise only the past-the-end iterator is
    //! invalidated.
    //! @param value [Value](@eve::vectorizable) to append
    EVE_FORCEINLINE void push_back(value_type const& value) noexcept
    {
      if(size_ == capacity())
      {
        // Grow twice per push_back
        grow(2*size_+1, size());
      }

      eve::write(value, begin()+size_);
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
    void resize(std::size_t n, value_type value = {})
    {
      auto sz = size_;
      if(n > capacity())
      {
        // Grow twice per resize
        grow(2*n, size());
      }

      // If needed, fill with new data
      if(n > sz) fill(sz, n, value );
      size_ = n;
    }

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
    EVE_FORCEINLINE auto data_aligned()         { return storage.data_aligned(); }

    //! Returns a zipped aligned pointer to the beginning
    EVE_FORCEINLINE auto data_aligned()  const  { return storage.data_aligned(); }

    //! Returns a zipped pointer to the beginning
    EVE_FORCEINLINE auto data()       { return  storage.data(); }

    //! Returns a constant zipped pointer to the beginning
    EVE_FORCEINLINE auto data() const { return  storage.data(); }

    //! @brief Returns the value of the `i`th element of the container
    //! @param i Index of the value to retrieve
    EVE_FORCEINLINE value_type get(std::size_t i) const { return eve::read(begin() + i); }

    //! @brief Modify the value of the `i`th element of the container
    //! @param i Index of the value to write
    //! @param v Value to write
    EVE_FORCEINLINE void set(std::size_t i, value_type const& v)
    {
      return eve::write(v, begin() + i);
    }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Iterators
    //! @{
    //==============================================================================================
    //! Returns an aligned iterator to the beginning
    EVE_FORCEINLINE auto begin_aligned() -> iterator_aligned { return views::convert(data_aligned(), eve::as<Type>{}); }

    //! Returns an aligned iterator to the beginning
    EVE_FORCEINLINE auto begin_aligned()  const -> const_iterator_aligned { return views::convert(data_aligned(), eve::as<Type>{}); }

    //! Returns a constant aligned iterator to the beginning
    EVE_FORCEINLINE auto cbegin_aligned() const -> const_iterator_aligned { return begin_aligned(); }

    //! Returns an iterator to the beginning
    EVE_FORCEINLINE auto begin() -> iterator { return views::convert(data(), eve::as<Type>{}); }

    //! Returns an iterator to the beginning
    EVE_FORCEINLINE auto begin()  const -> const_iterator { return views::convert(data(), eve::as<Type>{}); }

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
      for(std::size_t i=0;i<v.size();++i) os << v.get(i) << " ";
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
      this->operator=(std::move(that));
      size_ = old_size;
    }

    void fill(std::size_t first, std::size_t last, value_type v)
    {
      eve::algo::fill(algo::as_range(begin() + first, begin() + last), v );
    }

    void fill(value_type v) { eve::algo::fill(*this, v ); }

    storage_t   storage;
    std::size_t size_;
  };
}
