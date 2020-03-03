.. _function-inc:

###
inc
###

**Required header:** ``#include <eve/function/inc.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ inc = {};
   }

Function object increment by 1 a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise  increment of the :ref:`wide <type-wide>`.
* [2] Computes the increment of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter. *TODO*

Options
*******

  - :ref:`:ref:`saturated_ <feature-decorator>` <feature-decorator>` decorator provides (no surprise) the saturated operation.
  
  - conditional call is allowed: ``inc[cond](a)`` is equivalent (but potentially optimized) to ``if_else(cond, inc(a), a)``

.. seealso::  :ref:`inc <function-inc>`

Example
*******

.. include:: ../../../../test/doc/core/inc.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/inc.txt
  :literal:
