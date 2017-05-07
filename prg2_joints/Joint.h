#pragma once

#include <array>
#include <vector>
#include <initializer_list>
#include <iostream>

class Joint {
	protected:
		float x, y, z;
	public:
		Joint(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

		inline float getX() const { return x; }
		inline float getY() const { return y; }
		inline float getZ() const { return z; }

		void setX(float X) { x = X; }
		void setY(float Y) { y = Y; }
		void setZ(float Z) { z = Z; }

		static float getAngle(const Joint& j1, const Joint& j2, const Joint& j3);
		static float toDegrees(float rad) { return rad * 180 / acos(-1.0f); }
};

class JointSet : public Joint {
	private:
		std::vector<Joint*> m_connected = {};
	protected:
	public:
		JointSet(float x, float y, float z) : Joint(x, y, z) {}

		const std::vector<Joint*>& getConnectedJoints() const { return m_connected; }
		void bind(std::initializer_list<Joint*> joints) { m_connected.insert(m_connected.end(), joints.begin(), joints.end()); }
		void bind(Joint *joint) { m_connected.emplace_back(joint); }
		void clear() { m_connected.clear(); }
		unsigned int size() const { return m_connected.size(); }
		bool boundTo(Joint *joint) const { return std::find(m_connected.begin(), m_connected.end(), joint) != m_connected.end(); }
		Joint* getJoint(unsigned int index) { return (index < m_connected.size() ? m_connected[index] : nullptr); }

		static void hook(JointSet *A, JointSet *B) {
			if (!A->boundTo(B)) A->bind(B);
			if (!B->boundTo(A)) B->bind(A);
		}

		static void hook(JointSet *A, std::initializer_list<JointSet*> sets) {
			for (JointSet *set : sets) hook(A, set);
		}
};

// DEPRECATED
template <unsigned int SIZE> class JointGroup__ : public Joint {
	private:
		std::array<Joint*, SIZE> connectedJoints = { nullptr };
	public:
		JointGroup__(float x, float y, float z) : Joint(x, y, z) {}

		const std::array<Joint*, SIZE>& getConnectedJoints() const { return connectedJoints; }
		void bind(const std::array<Joint*, SIZE>& joints) { connectedJoints = joints; }
		Joint* getJoint(unsigned int position) { return (position < SIZE ? connectedJoints[position] : nullptr); }

		bool addJoint(Joint *joint) {
			for (unsigned int i = 0; i < SIZE; i++) {
				if (connectedJoints[i] == nullptr) {
					connectedJoints[i] = joint;
					return true;
				}
			}

			return false;
		}

		bool isJoined(Joint *joint) const {
			for (unsigned int i = 0; i < SIZE; i++) {
				if (connectedJoints[i] == joint) return true;
			}

			return false;
		}

		void bind(Joint *joint, unsigned int position) {
			if (position < SIZE) {
				connectedJoints[i] = joint;
			}
		}
};

// DEPRECATED
template <unsigned int SIZE_A, unsigned int SIZE_B> void join(JointGroup__<SIZE_A> *jointGroup1, JointGroup__<SIZE_B> *jointGroup2) {
	if (!jointGroup1->isJoined(jointGroup2)) jointGroup1->addJoint(jointGroup2);
	if (!jointGroup2->isJoined(jointGroup1)) jointGroup2->addJoint(jointGroup1);
}