.. _function-none:

####
none
####

**Required header:** ``#include <eve/function/none.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ none = {};
   }

Function object computing a boolean value equal to true if and only if all of the elements of a :ref:`Value <concept-value>` are zero.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes a boolean value equal to true if and only if none of the elements of a :ref:`Value <concept-value>` are non zero.
* [2] Computes a boolean value equal to true if and only if s is has a zero value.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A bool value

.. seealso::  :ref:`any <function-all>`,  :ref:`all <function-any>`,  :ref:`nbtrue <function-nbtrue>`

Example
*******

.. include:: ../../../../test/doc/core/none.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/none.txt
  :literal:
