/*
MIT License

Copyright (c) 2022 Ducktape

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef DUCKTAPE_PHYSICS_HINGEJOINT_H_
#define DUCKTAPE_PHYSICS_HINGEJOINT_H_

#include <box2d/box2d.h>

#include <Ducktape/engine/behaviourscript.h>
#include <Ducktape/physics/rigidbody.h>
#include <Ducktape/engine/entity.h>
#include <Ducktape/physics/physics.h>

namespace DT
{
	/**
	 * @brief This component allows an `Entity` controlled by `RigidBody2D` physics to be attached to a point in space around which it can rotate.
	 */
	class HingeJoint2D : public BehaviourScript
	{
	private:
		b2RevoluteJoint *joint;
		Rigidbody2D *rb;
		Rigidbody2D *connectedRigidbody = nullptr;

	public:
		void Constructor();

		void Tick();
		void OnDestroy();

		/**
		 * @brief Get the Anchor A position of the joint.
		 *
		 * @return Vector2 The Anchor A position of the joint.
		 */
		Vector2 GetAnchorA();

		/**
		 * @brief Get the Anchor B position of the joint.
		 *
		 * @return Vector2 The Anchor B position of the joint.
		 */
		Vector2 GetAnchorB();

		/**
		 * @brief Get the rigidbody connected to the joint.
		 *
		 * @return Rigidbody2D* The rigidbody connected to the joint.
		 */
		Rigidbody2D *GetConnectedRigidbody();

		/**
		 * @brief Set the connected rigidbody of the joint.
		 *
		 * @param rb The rigidbody to connect to the joint.
		 */
		void SetConnectedRigidbody(Rigidbody2D *rb);

		/**
		 * @brief Get the reference angle of the joint.
		 *
		 * @return float The reference angle of the joint.
		 */
		float GetReferenceAngle();

		/**
		 * @brief Get the joint angle.
		 *
		 * @return float The joint angle.
		 */
		float GetJointAngle();

		/**
		 * @brief Get the joint speed.
		 *
		 * @return float The joint speed.
		 */
		float GetJointSpeed();

		/**
		 * @brief Get if limit is enabled.
		 *
		 * @return bool If limit is enabled.
		 */
		bool GetLimitEnabled();

		/**
		 * @brief Set if limit is enabled.
		 *
		 * @param flag If limit is enabled.
		 */
		void SetLimitEnabled(bool flag);

		/**
		 * @brief Get the lower limit.
		 *
		 * @return float The lower limit.
		 */
		float GetLowerLimit();

		/**
		 * @brief Get the upper limit.
		 *
		 * @param limit The upper limit.
		 */
		float GetUpperLimit();

		/**
		 * @brief Set the lower limit.
		 *
		 * @param val The lower limit.
		 */
		void SetLowerLimit(float val);

		/**
		 * @brief Set the upper limit.
		 *
		 * @param val The upper limit.
		 */
		void SetUpperLimit(float val);

		/**
		 * @brief Get if motor is enabled.
		 *
		 * @return bool If motor is enabled.
		 */
		bool GetMotorEnabled();

		/**
		 * @brief Set if motor is enabled.
		 *
		 * @param flag If motor is enabled.
		 */
		void SetMotorEnabled(bool flag);

		/**
		 * @brief Get the motor speed.
		 *
		 * @return float The motor speed.
		 */
		float GetMotorSpeed();

		/**
		 * @brief Get the motor speed.
		 *
		 * @param speed The motor speed.
		 */
		void SetMotorSpeed(float speed);

		/**
		 * @brief Set the max motor torque.
		 *
		 * @param torque The max motor torque.
		 */
		void SetMaxMotorTorque(float torque);

		/**
		 * @brief Get the max motor torque.
		 *
		 * @return float The max motor torque.
		 */
		float GetMaxMotorTorque();
	};
}

#endif