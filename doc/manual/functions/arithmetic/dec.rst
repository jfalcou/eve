.. _function-dec:

###
dec
###

**Required header:** ``#include <eve/function/dec.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ dec = {};
   }

Function object decrement by 1 a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise  decrement of the :ref:`wide <type-wide>`.
* [2] Computes the decrement of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter. *TODO*


.. seealso::  :ref:`inc <function-inc>`

Example
*******

.. include:: ../../../../test/doc/core/dec.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/dec.txt
  :literal:
