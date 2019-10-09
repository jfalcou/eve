.. _function-prev:

####
prev
####

**Required header:** ``#include <eve/function/prev.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ prev = {};
   }

    This function object returns the  (`n`-th if the second parameter is present) greatest representable 
    element strictly less than the parameter


Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>              wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T, typename U, typename N>  wide<T,N> operator()( wide<T,N> const& v, U const & n) noexcept;
   template<typename T, typename U, typename N>  wide<T,N> operator()( wide<T,N> const& v, wide<U,N> const & m) noexcept;
   template<typename T> constexpr T                        operator()( T s ) noexcept;
   template<typename T> constexpr T                        operator()( T s, U n) noexcept;

* [1-3] Computes the element-wise prev (n-th) value of the :ref:`wide <type-wide>`.
* [4-5] Computes the prev (n-th) value of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Notes
******

  - the second parameter elements are to be positive integral values.

Options
*******

  with saturated_ options and integral input ``prev(Valmin,n)`` is ``Valmin``

Example
*******

.. include:: ../../../../test/doc/prev.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/prev.txt
  :literal:
