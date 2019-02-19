.. _function-sub:

sub
===

**Required header** ``#include <eve/function/sub.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr Value sub( Value lhs, Value rhs ) noexcept
   }

Function object for performing substraction over two :ref:`concept-value` of the same type.

Parameters
----------

  - ``lhs``, ``rhs`` : values to substract

Return value
------------

The difference between  ``lhs`` and ``rhs`` for every elements of each parameter.

Options
-------


Example
-------

.. include:: ../../../../test/doc/sub.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/sub.txt
  :literal:
