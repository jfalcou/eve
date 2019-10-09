.. _function-nextafter:

#########
nextafter
#########

**Required header:** ``#include <eve/function/nextafter.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ nextafter = {};
   }

    This function object called with x and y returns the  the next representable value of x in the
    direction of y. is returned. If x equals y, then x is returned.


Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename U, typename N>  wide<T,N> operator()( wide<T,N> const& x, wide<T,N> const& y) noexcept;
   template<typename T> constexpr T                        operator()( T s, T t) noexcept;

* [1-3] Computes the element-wise nextafter (n-th) value of the :ref:`wide <type-wide>`.
* [4-5] Computes the nextafter (n-th) value of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.


Example
*******

.. include:: ../../../../test/doc/nextafter.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/nextafter.txt
  :literal:
