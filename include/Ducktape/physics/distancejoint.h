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

#ifndef DISTANCEJOINT2D_H
#define DISTANCEJOINT2D_H

#include <Ducktape/engine/behaviourscript.h>
#include <box2d/box2d.h>
#include <Ducktape/physics/rigidbody.h>
#include <Ducktape/engine/entity.h>
#include <Ducktape/physics/physics.h>

namespace DT
{
	class DistanceJoint2D : public BehaviourScript
	{
	private:
		b2DistanceJoint *joint;
		Rigidbody2D *rb;
		Rigidbody2D *connectedRigidbody = nullptr;

	public:
		DistanceJoint2D();

		void tick();
		void onDestroy();

		/**
		 * @brief Get the Anchor A position of the joint
		 * 
		 * @return Vector2 The Anchor A position of the joint
		 */
		Vector2 getAnchorA();

		/**
		 * @brief Get the Anchor B position of the joint
		 * 
		 * @return Vector2 The Anchor B position of the joint
		 */
		Vector2 getAnchorB();
		
		/**
		 * @brief Get the rigidbody connected to the joint
		 * 
		 * @return Rigidbody2D* The rigidbody connected to the joint
		 */
		Rigidbody2D *getConnectedRigidbody();

		/**
		 * @brief Set the connected rigidbody of the joint
		 * 
		 * @param rb The rigidbody to connect to the joint
		 */
		void setConnectedRigidbody(Rigidbody2D *rb);

		/**
		 * @brief Get the length of the joint
		 * 
		 * @return float The length of the joint
		 */
		float getLength();

		/**
		 * @brief Set the length of the joint
		 * 
		 * @param length The length of the joint
		 */
		void setLength(float length);

		/**
		 * @brief Get the minimum length of the joint
		 * 
		 * @return float The minimum length of the joint
		 */
		float getMinLength();

		/**
		 * @brief Set the minimum length of the joint
		 * 
		 * @param minLength The minimum length of the joint
		 */
		void setMinLength(float minLength);

		/**
		 * @brief Get the maximum length of the joint
		 * 
		 * @return float The maximum length of the joint
		 */
		float getMaxLength();

		/**
		 * @brief Set the maximum length of the joint
		 * 
		 * @param maxLength The maximum length of the joint
		 */
		void setMaxLength(float maxLength);

		/**
		 * @brief Get the current length of the joint
		 * 
		 * @return float The current length of the joint
		 */
		float getCurrentLength();

		/**
		 * @brief Get the stiffness of the joint
		 * 
		 * @return float The stiffness of the joint
		 */
		float getStiffness();

		/**
		 * @brief Set the stiffness of the joint
		 * 
		 * @param stiffness The stiffness of the joint
		 */
		void setStiffness(float stiffness);

		/**
		 * @brief Get the damping of the joint
		 * 
		 * @return float The damping of the joint
		 */
		float getDamping();

		/**
		 * @brief Set the damping of the joint
		 * 
		 * @param damping The damping of the joint
		 */
		void setDamping(float damping);
	};
}

#endif