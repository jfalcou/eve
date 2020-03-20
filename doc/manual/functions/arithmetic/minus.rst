.. _function-minus:

###########
minus
###########

**Required header:** ``#include <eve/function/minus.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ minus = {};
   }

Function object computing the opposite  of a :ref:`Value <concept-value>`.
Infix notation: `-` can be used.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise  opposite of the :ref:`wide <type-wide>`.
* [2] Computes the opposite of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter. 

Notes
*****

  - minus on floating point types  changes the bit of sign.

  - conditional call is allowed: ``minus[cond](a)`` is equivalent (but optimized) to ``if_else(cond, minus(a), a)``

  - take care that the infix notation on scalar can imply C++ promotion as it is the original operator.



.. seealso::  :ref:`plus <function-plus>`

Example
*******

.. include:: ../../../../test/doc/core/minus.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/minus.txt
  :literal:
