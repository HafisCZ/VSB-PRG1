#include <iostream>

#include "Joint.h"

int main(int argc, char** argv) {
	std::vector<JointSet> sets;
	sets.emplace_back(0.0f, 0.0f, 0.0f);	// [00] head
	sets.emplace_back(-2.0f, 0.0f, -1.0f);	// [01] left hand
	sets.emplace_back(2.0f, 0.0f, -1.0f);	// [02] right hand
	sets.emplace_back(-2.0f, 0.0f, -5.0f);	// [03] left foot
	sets.emplace_back(2.0f, 0.0f, -5.0f);	// [04] right foot
	sets.emplace_back(0.0f, 0.0f, -2.0f);	// [05] body
	sets.emplace_back(-1.0f, 0.0f, -1.0f);	// [06] left arm
	sets.emplace_back(1.0f, 0.0f, -1.0f);	// [07] right arm
	sets.emplace_back(-1.0f, 0.0f, -4.0f);	// [08] left leg
	sets.emplace_back(1.0f, 0.0f, -4.0f);	// [09] right leg
	sets.emplace_back(0.0f, 0.0f, -3.0f);	// [10] lower
	sets.emplace_back(0.0f, 0.0f, -1.0f);	// [11] upper
	
	JointSet::hook(&sets[11], {&sets[0], &sets[7], &sets[6], &sets[5]});
	JointSet::hook(&sets[5], &sets[10]);
	JointSet::hook(&sets[10], {&sets[8], &sets[9]});
	JointSet::hook(&sets[8], &sets[3]);
	JointSet::hook(&sets[9], &sets[4]);
	JointSet::hook(&sets[6], &sets[1]);
	JointSet::hook(&sets[7], &sets[2]);

	std::cout << Joint::toDegrees(Joint::getAngle(*sets[11].getJoint(0), sets[11], *sets[11].getJoint(2)));

	std::cin.get();
	return 0;
}