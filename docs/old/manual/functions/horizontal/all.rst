.. _function-all:

###
all
###

**Required header:** ``#include <eve/function/all.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ all = {};
   }

Function object computing a boolean value equal to true if and only if all the elements of a :ref:`Value <concept-value>` are non zero.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes a boolean value equal to true if and only if all the elements of a :ref:`Value <concept-value>` are non zero.
* [2] Computes a boolean value equal to true if and only if s has a non zero value.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A bool value

.. seealso::  :ref:`any <function-any>`,  :ref:`none <function-none>`,  :ref:`nbtrue <function-nbtrue>`

Example
*******

.. include:: ../../../../test/doc/core/all.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/all.txt
  :literal:
