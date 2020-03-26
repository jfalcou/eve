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

Function object returning  a :ref:`Value <concept-value>` decremented by 1 

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise  :ref:`Value <concept-value>` minus 1.

Parameter
**********


* ``x``: Instance of a :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.

Notes
*******

  - With the :ref:`saturated_ <feature-decorator>`, provides (no surprise) the saturated operation.
  
  - :ref:`masked <feature-maskable>` call is allowed: ``dec[cond](x)`` is equivalent to ``if_else(cond, dec(x), x)``, 
    but can be subject to optimization.

.. seealso::  :ref:`inc <function-inc>`, :ref:`oneminus <function-oneminus>`

Example
*******

.. include:: ../../../../test/doc/core/dec.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/dec.txt
  :literal:
