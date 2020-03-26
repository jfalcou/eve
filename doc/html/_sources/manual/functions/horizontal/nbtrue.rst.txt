.. _function-nbtrue:

######
nbtrue
######

**Required header:** ``#include <eve/function/nbtrue.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ nbtrue = {};
   }

Function object computing an int value equal to numnber the elements of a :ref:`Value <concept-value>` which are non zero.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes a int value equal to the number of elements of a :ref:`Value <concept-value>` are non zero.
* [2] Computes a int value equal to 1 if s is has a non zero value else 0.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A bool value

.. seealso::  :ref:`all <function-all>`,  :ref:`none <function-none>`,  :ref:`any <function-any>`

Example
*******

.. include:: ../../../../test/doc/core/nbtrue.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/nbtrue.txt
  :literal:
