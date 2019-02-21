.. _function-is_not_real:

is_not_real
============

**Required header** ``#include <eve/function/is_not_real.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_not_real( Value lhs ) noexcept
   }


This function ever returns :ref:`False <constant-false_>` for real inputs
This is the restriction to real inputs of the complex function.


.. seealso::  :ref:`Smallestposval <constant-Smallestposval>`, :ref:`abs <constant-abs>`

Parameters
----------

  - ``lhs``  : values to test.

Return value
------------

Semantically equivalent to ``False(as(lhs))`` for real inputs.

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_not_real.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_not_real.txt
  :literal:

