.. _function-is_not_less:

is_not_less
============

**Required header** ``#include <eve/function/is_not_less.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_not_less( Value lhs, Value rhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` or :ref:`False <constant-false_>`
according its first parameter is not less than the second.

.. seealso::  :ref:`is_greater_equal <function-is_greater_equal>`

Parameters
----------

  - ``lhs``, ``rhs`` : values to compare of the same type

Return value
------------

The logical values ``lhs`` not less than ``rhs`` for every elements of each parameter.
The return value can differ from those of :ref:`is_greater_equal <function-is_greater_equal>` only in case of :ref:`Nans <constant-nan>` 
in floating point parameters.


Options
-------


Example
-------

.. include:: ../../../../test/doc/is_not_less.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_not_less.txt
  :literal:

