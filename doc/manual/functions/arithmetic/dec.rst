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

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise absolute value of the :ref:`Value <concept-value>`.

.. rubric:: Parameter

* Instance of a :ref:`Value <concept-value>`.

.. rubric:: Return value

* A value with the same type as the parameter.

Options
*******

  - :ref:`saturated_ <feature-decorator>` decorator provides (no surprise) the saturated operation.
  
  - :ref:`masked call <feature-maskable>` is allowed: ``dec[cond](x)`` is equivalent to ``if_else(cond, dec(x), x)``, 
    but can be subject to optimization.

.. seealso::  :ref:`inc <function-inc>`, :ref:`oneminus <function-oneminus>`

Example
*******

.. include:: ../../../../test/doc/core/dec.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/dec.txt
  :literal:
