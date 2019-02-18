.. _concept-vectorized:

Vectorized
==========

A type is :ref:`concept-vectorized` if it represents a type which operations are performed in accordance
with the SIMD execution model.

Requirements
------------

:ref:`concept-vectorized` types satisfy DefaultConstructible_, Destructible_, CopyConstructible_,
CopyAssignable_, MoveConstructible_ and MoveAssignable_ while lvalues of :ref:`concept-vectorized`
types satisfy Swappable_.

.. warning::  :ref:`concept-vectorized` does not refine EqualityComparable_ (and hence Regular)
  because ``operator==`` returns a :ref:`concept-logicalvalue` type instead of straight
  ``bool``.

For any :ref:`concept-vectorized` type ``V``, the following expressions are valid:

+------------------------+----------------------------------------------+--------------------------------------------------------------------------+
| Expression             | Type                                         | Note                                                                     |
+========================+==============================================+==========================================================================+
| ``V::storage_type``    | native storage type                          | architecture dependent                                                   |
+------------------------+----------------------------------------------+--------------------------------------------------------------------------+
| ``V::value_type``      | ``T``                                        | satisfies :ref:`concept-vectorizable`                                    |
+------------------------+----------------------------------------------+--------------------------------------------------------------------------+
| ``V::reference``       | reference to ``T``                           |                                                                          |
+------------------------+----------------------------------------------+--------------------------------------------------------------------------+
| ``V::const_reference`` | reference to ``T const``                     |                                                                          |
+------------------------+----------------------------------------------+--------------------------------------------------------------------------+
| ``V::iterator``        | iterator pointing to ``T``                   | RandomAccessIterator_ convertible to ``const_iterator``                  |
+------------------------+----------------------------------------------+--------------------------------------------------------------------------+
| ``V::const_iterator``  | const iterator pointing to ``T``             |                                                                          |
+------------------------+----------------------------------------------+--------------------------------------------------------------------------+
| ``V::difference_type`` | signed integer type                          |                                                                          |
+------------------------+----------------------------------------------+--------------------------------------------------------------------------+
| ``V::size_type``       | signed integer type                          |                                                                          |
+------------------------+----------------------------------------------+--------------------------------------------------------------------------+
| ``V::static_alignment``| constant expression of unsigned integer type | The value of the preferred alignment for ``V``                           |
+------------------------+----------------------------------------------+--------------------------------------------------------------------------+
| ``V::static_size``     | constant expression of unsigned integer type | The number of :ref:`concept-vectorizable` stored in an instance of ``V`` |
+------------------------+----------------------------------------------+--------------------------------------------------------------------------+


For any given ``a`` and ``b`` of type ``V``, the following expressions are valid:

+-----------------------------+---------------------------+--------------------------------------------------+-------------+
| Expression                  | Return type               | Semantics                                        | Complexity  |
+=============================+===========================+==================================================+=============+
| ``std::begin(a)``           | ``(const_)iterator``      | Iterator to the first element of ``a``           | Constant    |
+-----------------------------+---------------------------+--------------------------------------------------+-------------+
| ``std::end(a)``             | ``(const_)iterator``      | Iterator to one past the last element of ``a``   | Constant    |
+-----------------------------+---------------------------+--------------------------------------------------+-------------+
| ``std::cbegin(a)``          | ``const_iterator``        | ``std::begin(const_cast<const V&>(a))``          | Constant    |
+-----------------------------+---------------------------+--------------------------------------------------+-------------+
| ``std::cend(a)``            | ``const_iterator``        | ``std::end(const_cast<const V&>(a))``            | Constant    |
+-----------------------------+---------------------------+--------------------------------------------------+-------------+
| ``a.swap(b)``               | ``void``                  | Exchanges the values of ``a`` and ``b``          | Constant    |
+-----------------------------+---------------------------+--------------------------------------------------+-------------+
| ``swap(a, b)``              | ``void``                  | ``a.swap(b)``                                    | Constant    |
+-----------------------------+---------------------------+--------------------------------------------------+-------------+
| ``a.size()``                | ``size_type``             | ``std::distance(a.begin(), a.end())``            | Constant    |
+-----------------------------+---------------------------+--------------------------------------------------+-------------+
| ``a.empty()``               | ``bool``                  | ``a.size() == 0``                                | Constant    |
+-----------------------------+---------------------------+--------------------------------------------------+-------------+
| ``a.storage()``             | ``storage_type``          | Returns the internal native data stored in ``a`` | Constant    |
+-----------------------------+---------------------------+--------------------------------------------------+-------------+
| ``operator storage_type()`` | ``storage_type``          | ``return a.storage()``                           | Constant    |
+-----------------------------+---------------------------+--------------------------------------------------+-------------+

Example
-------

  - ``eve::wide<short>``
  - ``eve::wide<eve::logical<float>>``

.. _Destructible: https://en.cppreference.com/w/cpp/named_req/Destructible
.. _DefaultConstructible: https://en.cppreference.com/w/cpp/named_req/DefaultConstructible
.. _CopyConstructible: https://en.cppreference.com/w/cpp/named_req/CopyConstructible
.. _CopyAssignable: https://en.cppreference.com/w/cpp/named_req/CopyAssignable
.. _MoveConstructible: https://en.cppreference.com/w/cpp/named_req/MoveConstructible
.. _MoveAssignable: https://en.cppreference.com/w/cpp/named_req/MoveAssignable
.. _Swappable: https://en.cppreference.com/w/cpp/named_req/Swappable
.. _EqualityComparable: https://en.cppreference.com/w/cpp/named_req/EqualityComparable
.. _RandomAccessIterator: https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
