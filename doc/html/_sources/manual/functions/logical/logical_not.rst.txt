.. _function-logical_not:

###########
logical_not
###########

**Required header:** ``#include <eve/function/logical_not.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ logical_not = {};
   }

Function object performing a logical NOT between two :ref:`Values <concept-value>` (of same type if they are both :ref:`wide <type-wide>` instances).

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>              logical<wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T            > constexpr    as_logical_t<T>    operator()( T s) noexcept;

* [1] Performs a logical NOT on each element ofthe :ref:`wide <type-wide>` instance.
* [2] Performs a logical NOT on the scalar.

.. rubric:: Parameters

* **v**: Instance of a :ref:`type-wide` .
* **s**: Scalar value.s.

.. rubric:: Return value

* [1,2] A value with the same type as the . parameter.

*******
Options
*******

*******
Example
*******

.. include:: ../../../../test/doc/core/logical_not.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/logical_not.txt
  :literal:
