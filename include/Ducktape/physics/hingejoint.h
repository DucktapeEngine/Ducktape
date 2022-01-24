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

#ifndef HINGEJOINT_H
#define HINGEJOINT_H

#include <Ducktape/engine/behaviourscript.h>
#include <box2d/box2d.h>
#include <Ducktape/physics/rigidbody.h>
#include <Ducktape/engine/entity.h>
#include <Ducktape/physics/physics.h>

namespace DT
{
	class HingeJoint2D : public BehaviourScript
	{
	private:
		b2RevoluteJoint *joint;
		Rigidbody2D *rb;
		Rigidbody2D *connectedRigidbody = nullptr;

	public:
		HingeJoint2D();

		void tick();
		void onDestroy();

		/**
		 * @brief Get the Anchor A position of the joint.
		 * 
		 * @return Vector2 The Anchor A position of the joint.
		 */
		Vector2 getAnchorA();

		/**
		 * @brief Get the Anchor B position of the joint.
		 * 
		 * @return Vector2 The Anchor B position of the joint.
		 */
		Vector2 getAnchorB();

		/**
		 * @brief Get the rigidbody connected to the joint.
		 * 
		 * @return Rigidbody2D* The rigidbody connected to the joint.
		 */
		Rigidbody2D *getConnectedRigidbody();

		/**
		 * @brief Set the connected rigidbody of the joint.
		 * 
		 * @param rb The rigidbody to connect to the joint.
		 */
		void setConnectedRigidbody(Rigidbody2D *rb);

		/**
		 * @brief Get the reference angle of the joint.
		 * 
		 * @return float The reference angle of the joint.
		 */
		float getReferenceAngle();

		/**
		 * @brief Get the joint angle.
		 * 
		 * @return float The joint angle.
		 */
		float getJointAngle();

		/**
		 * @brief Get the joint speed.
		 * 
		 * @return float The joint speed.
		 */
		float getJointSpeed();

		/**
		 * @brief Get if limit is enabled.
		 * 
		 * @return bool If limit is enabled.
		 */
		bool getLimitEnabled();

		/**
		 * @brief Set if limit is enabled.
		 * 
		 * @param flag If limit is enabled.
		 */
		void setLimitEnabled(bool flag);

		/**
		 * @brief Get the lower limit.
		 * 
		 * @return float The lower limit.
		 */
		float getLowerLimit();

		/**
		 * @brief Get the upper limit.
		 * 
		 * @param limit The upper limit.
		 */
		float getUpperLimit();

		/**
		 * @brief Set the lower limit.
		 * 
		 * @param val The lower limit.
		 */
		void setLowerLimit(float val);

		/**
		 * @brief Set the upper limit.
		 * 
		 * @param val The upper limit.
		 */
		void setUpperLimit(float val);

		/**
		 * @brief Get if motor is enabled.
		 * 
		 * @return bool If motor is enabled.
		 */
		bool getMotorEnabled();

		/**
		 * @brief Set if motor is enabled.
		 * 
		 * @param flag If motor is enabled.
		 */
		void setMotorEnabled(bool flag);

		/**
		 * @brief Get the motor speed.
		 * 
		 * @return float The motor speed.
		 */
		float getMotorSpeed();

		/**
		 * @brief Get the motor speed.
		 * 
		 * @return float The motor speed.
		 */
		void setMotorSpeed(float speed);

		/**
		 * @brief Set the max motor torque.
		 * 
		 * @param torque The max motor torque.
		 */
		void setMaxMotorTorque(float torque);

		/**
		 * @brief Get the max motor torque.
		 * 
		 * @return float The max motor torque.
		 */
		float getMaxMotorTorque();
	};
}

#endif