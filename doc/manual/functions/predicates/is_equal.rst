.. _function-is_equal:

is_equal
============

**Required header** ``#include <eve/function/is_equal.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_equal( Value lhs, Value rhs ) noexcept
   }


This function object compares for equality two :ref:`Values <concept-value>`  of the same type.

Infix notation can be used with operator '=='.

.. seealso:: modules :py:mod:`zipfile`, :py:mod:`tarfile`

Parameters
----------

  - ``lhs``, ``rhs`` : values to compare

Return value
------------

The logical  equal of ``arg0`` and ``arg1`` for every elements of each parameter.

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_equal.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_equal.txt
  :literal:

