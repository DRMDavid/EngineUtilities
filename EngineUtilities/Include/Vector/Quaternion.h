#pragma once

#include "../Utilities/EngineMath.h"
#include "Cvector3.h"

/**
 * @class CQuaternion
 * @brief Represents a quaternion used for 3D rotations.
 */
class CQuaternion {
public:
  float x, y, z, w;

  /**
   * @brief Default constructor initializes to identity quaternion.
   */
  CQuaternion() : x(0), y(0), z(0), w(1) {}

  /**
   * @brief Parameterized constructor.
   * @param x X component.
   * @param y Y component.
   * @param z Z component.
   * @param w W component.
   */
  CQuaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

  /**
   * @brief Quaternion multiplication.
   * @param q Another quaternion.
   * @return Result of quaternion multiplication.
   */
  CQuaternion operator*(const CQuaternion& q) const {
    return CQuaternion(
      w * q.x + x * q.w + y * q.z - z * q.y,
      w * q.y - x * q.z + y * q.w + z * q.x,
      w * q.z + x * q.y - y * q.x + z * q.w,
      w * q.w - x * q.x - y * q.y - z * q.z
    );
  }

  /**
   * @brief Scalar multiplication.
   * @param scalar Scalar value.
   * @return Scaled quaternion.
   */
  CQuaternion operator*(float scalar) const {
    return CQuaternion(x * scalar, y * scalar, z * scalar, w * scalar);
  }

  /**
   * @brief Quaternion addition.
   * @param q Another quaternion.
   * @return Sum of quaternions.
   */
  CQuaternion operator+(const CQuaternion& q) const {
    return CQuaternion(x + q.x, y + q.y, z + q.z, w + q.w);
  }

  /**
   * @brief Quaternion subtraction.
   * @param q Another quaternion.
   * @return Difference of quaternions.
   */
  CQuaternion operator-(const CQuaternion& q) const {
    return CQuaternion(x - q.x, y - q.y, z - q.z, w - q.w);
  }

  /**
   * @brief Normalizes the quaternion in-place.
   */
  void normalize() {
    float mag = EngineMathLib::sqrt(x * x + y * y + z * z + w * w);
    if (mag > 0.0f) {
      x /= mag;
      y /= mag;
      z /= mag;
      w /= mag;
    }
  }

  /**
   * @brief Returns a normalized copy of the quaternion.
   * @return Normalized quaternion.
   */
  CQuaternion normalized() const {
    CQuaternion q = *this;
    q.normalize();
    return q;
  }

  /**
   * @brief Returns the conjugate of the quaternion.
   * @return Conjugated quaternion.
   */
  CQuaternion conjugate() const {
    return CQuaternion(-x, -y, -z, w);
  }

  /**
   * @brief Rotates a 3D vector by this quaternion.
   * @param v The vector to rotate.
   * @return Rotated vector.
   */
  CVector3 rotate(const CVector3& v) const {
    CQuaternion vecQuat(v.x, v.y, v.z, 0.0f);
    CQuaternion resQuat = (*this) * vecQuat * conjugate();
    return CVector3(resQuat.x, resQuat.y, resQuat.z);
  }

  /**
   * @brief Creates a quaternion from an axis and angle.
   * @param axis Axis of rotation (must be normalized).
   * @param angleRad Angle in radians.
   * @return Quaternion representing the rotation.
   */
  static CQuaternion fromAxisAngle(const CVector3& axis, float angleRad) {
    float halfAngle = angleRad * 0.5f;
    float s = EngineMathLib::sin(halfAngle);
    float c = EngineMathLib::cos(halfAngle);
    return CQuaternion(axis.x * s, axis.y * s, axis.z * s, c);
  }

  /**
   * @brief Performs spherical linear interpolation (SLERP) between two quaternions.
   * @param a Start quaternion.
   * @param b End quaternion.
   * @param t Interpolation factor [0, 1].
   * @return Interpolated quaternion.
   */
  static CQuaternion slerp(const CQuaternion& a, const CQuaternion& b, float t) {
    float dot = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;

    CQuaternion bAdjusted = b;

    if (dot < 0.0f) {
      dot = -dot;
      bAdjusted = b * -1.0f;
    }

    if (dot > 0.9995f) {
      return (a + (bAdjusted  - a) * t).normalized();
    }

    float theta_0 = EngineMathLib::acos(dot);
    float theta = theta_0 * t;

    float sin_theta = EngineMathLib::sin(theta);
    float sin_theta_0 = EngineMathLib::sin(theta_0);

    float s0 = EngineMathLib::cos(theta) - dot * sin_theta / sin_theta_0;
    float s1 = sin_theta / sin_theta_0;

    return (a * s0 + bAdjusted * s1).normalized();
  }

  /**
   * @brief Outputs the quaternion to a stream.
   * @param os Output stream.
   * @param q Quaternion to output.
   * @return Output stream.
   */
  friend std::ostream& operator<<(std::ostream& os, const CQuaternion& q) {
    os << "CQuaternion(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
    return os;
  }
};
