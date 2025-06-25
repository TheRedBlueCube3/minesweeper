// SPDX-FileCopyrightText: 2025 thorium1256
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

struct Vector2
{
    /**
     * The position vector.
     */
    int x, y;

    /**
     * The Vector2 initializer.
     */
    Vector2(int x = 0, int y = 0);

    /**
     * Addition.
     */
    Vector2 operator+(const Vector2 &other) const;
    /**
     * Subtraction.
     */
    Vector2 operator-(const Vector2 &other) const;
    /**
     * Multiplication (by scalar).
     */
    Vector2 operator*(float scalar) const;
    /**
     * Division (by scalar).
     */
    Vector2 operator/(float scalar) const;

    /**
     * Addition.
     */
    Vector2 &operator+=(const Vector2 &other);
    /**
     * Subtraction.
     */
    Vector2 &operator-=(const Vector2 &other);
    /**
     * Multiplication (by scalar).
     */
    Vector2 &operator*=(float scalar);
    /**
     * Division (by scalar).
     */
    Vector2 &operator/=(float scalar);
};