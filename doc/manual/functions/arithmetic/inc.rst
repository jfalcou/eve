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

Function object returning  a :ref:`Value <concept-value>` incremented by 1 

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise  :ref:`Value <concept-value>` plus 1.

.. rubric:: Parameter

* Instance of a :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.

Options
*******

  - With the :ref:`saturated_ <feature-decorator>` decorator, provides (no surprise) the saturated operation.
  
  - :ref:`masked <feature-maskable>` call is allowed: ``inc[cond](a)`` is equivalent to ``if_else(cond, inc(a), a)``
    but can be subject to optimization.

.. seealso::  :ref:`inc <function-inc>`

Example
*******

.. include:: ../../../../test/doc/core/inc.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/inc.txt
  :literal:
