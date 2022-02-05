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

#ifndef DUCKTAPE_PHYSICS_DISTANCEJOINT2D_H_
#define DUCKTAPE_PHYSICS_DISTANCEJOINT2D_H_

#include <box2d/box2d.h>

#include <Ducktape/engine/behaviourscript.h>
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
		void Constructor();

		void Tick();
		void OnDestroy();

		/**
		 * @brief Get the Anchor A position of the joint
		 * 
		 * @return Vector2 The Anchor A position of the joint
		 */
		Vector2 GetAnchorA();

		/**
		 * @brief Get the Anchor B position of the joint
		 * 
		 * @return Vector2 The Anchor B position of the joint
		 */
		Vector2 GetAnchorB();
		
		/**
		 * @brief Get the rigidbody connected to the joint
		 * 
		 * @return Rigidbody2D* The rigidbody connected to the joint
		 */
		Rigidbody2D *GetConnectedRigidbody();

		/**
		 * @brief Set the connected rigidbody of the joint
		 * 
		 * @param rb The rigidbody to connect to the joint
		 */
		void SetConnectedRigidbody(Rigidbody2D *rb);

		/**
		 * @brief Get the length of the joint
		 * 
		 * @return float The length of the joint
		 */
		float GetLength();

		/**
		 * @brief Set the length of the joint
		 * 
		 * @param length The length of the joint
		 */
		void SetLength(float length);

		/**
		 * @brief Get the minimum length of the joint
		 * 
		 * @return float The minimum length of the joint
		 */
		float GetMinLength();

		/**
		 * @brief Set the minimum length of the joint
		 * 
		 * @param minLength The minimum length of the joint
		 */
		void SetMinLength(float minLength);

		/**
		 * @brief Get the maximum length of the joint
		 * 
		 * @return float The maximum length of the joint
		 */
		float GetMaxLength();

		/**
		 * @brief Set the maximum length of the joint
		 * 
		 * @param maxLength The maximum length of the joint
		 */
		void SetMaxLength(float maxLength);

		/**
		 * @brief Get the current length of the joint
		 * 
		 * @return float The current length of the joint
		 */
		float GetCurrentLength();

		/**
		 * @brief Get the stiffness of the joint
		 * 
		 * @return float The stiffness of the joint
		 */
		float GetStiffness();

		/**
		 * @brief Set the stiffness of the joint
		 * 
		 * @param stiffness The stiffness of the joint
		 */
		void SetStiffness(float stiffness);

		/**
		 * @brief Get the damping of the joint
		 * 
		 * @return float The damping of the joint
		 */
		float GetDamping();

		/**
		 * @brief Set the damping of the joint
		 * 
		 * @param damping The damping of the joint
		 */
		void SetDamping(float damping);
	};
}

#endif