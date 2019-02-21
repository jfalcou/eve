.. _function-is_equal_with_equal_nans:

is_equal_with_equal_nans
========================

**Required header** ``#include <eve/function/is_not_equal_with_equal_nans.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_not_equal_with_equal_nans( Value lhs, Value rhs ) noexcept
   }

This function returns :ref:`False <constant-true_>` or :ref:`True <constant-false_>`
according its parameters  :ref:`Values <concept-value>` are equal or both  :ref:`Nans <constant-nan>`, or are not equal.

 
.. seealso::  :ref:`is_not_equal <function-is_not_equal>`

Parameters
----------

  - ``lhs``, ``rhs`` : values to compare of the same type

Return value
------------

The logical negation of the  equality between ``lhs`` and ``rhs`` for every elements of each parameter (considering  :ref:`Nans <constant-nan>` are equal).

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_not_equal_with_equal_nans.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_not_equal_with_equal_nans.txt
  :literal:

