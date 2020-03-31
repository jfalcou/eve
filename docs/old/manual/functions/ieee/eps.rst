.. _function-eps:

###
eps
###

**Required header:** ``#include <eve/function/eps.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ eps = {};
   }

Function object computing the distance from ``abs(x)`` to the next representable value.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the  distance from ``abs(x)`` to the next representable :ref:`wide <type-wide>`.
* [2] Computes to the next representable value.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter. 

Notes
*****

  - eps(T(1)) is the constant Eps<T>()


.. seealso::  :ref:`ulpdist <function-ulpdist>`

Example
*******

.. include:: ../../../../test/doc/core/eps.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/eps.txt
  :literal:
