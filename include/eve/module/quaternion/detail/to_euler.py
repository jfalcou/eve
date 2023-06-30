#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Mar 14 11:36:03 2022

@author: Evandro Bernardes
"""

import re
import math
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
rc('text', usetex=True)

#%%
def _elementary_basis_index(axis):
    if axis == 'x': return 0
    elif axis == 'y': return 1
    elif axis == 'z': return 2

# My algorithm
def _compute_euler_from_quat(quat, seq, extrinsic=False):

    if not extrinsic:
        seq = seq[::-1]

    i = _elementary_basis_index(seq[0])
    j = _elementary_basis_index(seq[1])
    k = _elementary_basis_index(seq[2])

    is_proper = i == k

    if is_proper:
        k = 3 - i - j # get third axis

    # Step 0
    # Check if permutation is even (+1) or odd (-1)
    sign = int((i-j)*(j-k)*(k-i)/2)

    num_rotations = quat.shape[0]
    angles = np.empty((num_rotations, 3))
    eps = 1e-7

    for ind in range(num_rotations):
        _angles = angles[ind, :]

        if is_proper:
            a = quat[ind, 3]
            b = quat[ind, i]
            c = quat[ind, j]
            d = quat[ind, k] * sign
        else:
            a = quat[ind, 3] - quat[ind, j]
            b = quat[ind, i] + quat[ind, k] * sign
            c = quat[ind, j] + quat[ind, 3]
            d = quat[ind, k] * sign - quat[ind, i]

        n2 = a**2 + b**2 + c**2 + d**2

        # Step 3
        # Compute second angle...
        # _angles[1] = 2*np.arccos(np.sqrt((a**2 + b**2) / n2))
        _angles[1] = np.arccos(2*(a**2 + b**2) / n2 - 1)

        # ... and check if equalt to is 0 or pi, causing a singularity
        safe1 = abs(_angles[1]) >= eps
        safe2 = abs(_angles[1] - np.pi) >= eps
        safe = safe1 and safe2

        # Step 4
        # compute first and third angles, according to case
        if safe:
            half_sum = np.arctan2(b, a) # == (alpha+gamma)/2
            half_diff = np.arctan2(-d, c) # == (alpha-gamma)/2

            _angles[0] = half_sum + half_diff
            _angles[2] = half_sum - half_diff

        else:
            # _angles[0] = 0

            if not extrinsic:
                # For intrinsic, set first angle to zero so that after reversal we
                # ensure that third angle is zero
                # 6a
                if not safe:
                    _angles[0] = 0
                if not safe1:
                    half_sum = np.arctan2(b, a)
                    _angles[2] = 2 * half_sum
                # 6c
                if not safe2:
                    half_diff = np.arctan2(-d, c)
                    _angles[2] = -2 * half_diff
            else:
                # For extrinsic, set third angle to zero
                # 6b
                if not safe:
                    _angles[2] = 0
                if not safe1:
                    half_sum = np.arctan2(b, a)
                    _angles[0] = 2 * half_sum
                # 6c
                if not safe2:
                    half_diff = np.arctan2(-d, c)
                    _angles[0] = 2 * half_diff

        for i_ in range(3):
            if _angles[i_] < -np.pi:
                _angles[i_] += 2 * np.pi
            elif _angles[i_] > np.pi:
                _angles[i_] -= 2 * np.pi

        # for Tait-Bryan angles
        if not is_proper:
            _angles[2] *= sign
            _angles[1] -= np.pi / 2

        if not extrinsic:
            # reversal
            _angles[0], _angles[2] = _angles[2], _angles[0]

        # Step 8
        if not safe:
            print("Gimbal lock detected. Setting third angle to zero "
                          "since it is not possible to uniquely determine "
                          "all angles.")

    return angles

#%%
def euler_from_quat(r, seq, degrees=False):

    if len(seq) != 3:
        raise ValueError("Expected 3 axes, got {}.".format(seq))

    intrinsic = (re.match(r'^[XYZ]{1,3}$', seq) is not None)
    extrinsic = (re.match(r'^[xyz]{1,3}$', seq) is not None)
    if not (intrinsic or extrinsic):
        raise ValueError("Expected axes from `seq` to be from "
                         "['x', 'y', 'z'] or ['X', 'Y', 'Z'], "
                         "got {}".format(seq))

    if any(seq[i] == seq[i+1] for i in range(2)):
        raise ValueError("Expected consecutive axes to be different, "
                         "got {}".format(seq))

    seq = seq.lower()

    quat = r.as_quat()

    if quat.ndim == 1:
        quat = quat[None, :]

    angles = _compute_euler_from_quat(quat, seq, extrinsic)
    angles = np.asarray(angles)

    if degrees:
        angles = np.rad2deg(angles)

    return angles[0] if r.single else angles
