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


* [1] Computes the element-wise geatest representable element strictly less than the first parameter
* [2] Computes the element-wise  n-th geatest representable element strictly less than the first parameter
* [3] Computes the element-wise m-th geatest representable element strictly less than the first parameter
* [4] Computes the geatest representable element strictly less than the first parameter
* [5] Computes the geatest  n-th geatest representable element strictly less than the first parameter


.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,5] A value with the same type as the first parameter.

Notes
******

  - the second parameter elements are to be positive integral values.

  - If the second parameter is 0 the first parameter is returned.

Options
*******

  with :ref:`saturated_ <feature-decorator>` options and integral input ``prev(Valmin,n)`` is ``Valmin``

Example
*******

.. include:: ../../../../test/doc/core/prev.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/prev.txt
  :literal:
