/*
 * recordEntry.cpp
 *
 *  Created on: Sep 30, 2012
 *      Author: agata
 */

#include <cstdlib>
#include <string>
#include <stdint.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <limits.h>
#include <stdint.h>

#include "ns3/ptr.h"
#include "ovnis-constants.h"
#include "recordEntry.h"

using namespace std;

namespace ovnis {

RecordEntry::RecordEntry() {
	reset();
}

void RecordEntry::reset() {
	for (int i = 0; i < LOCAL_MEMORY_SIZE; ++i) {
		senders[i] = "";
		times[i] = 0;
		values[i] = 0;
	}
	count = 0;
}

void RecordEntry::add(long packetId, string senderId, double time, double value) {
	times[count%LOCAL_MEMORY_SIZE] = time;
	values[count%LOCAL_MEMORY_SIZE] = value;
	senders[count%LOCAL_MEMORY_SIZE] = senderId;
	packetIds[count%LOCAL_MEMORY_SIZE] = packetId;
	++count;
}

void RecordEntry::printValues() {
	cout << "[";
	for (int i = 0; i < LOCAL_MEMORY_SIZE; ++i) {
		cout << times[i] << "," << values[i] << " ";
	}
	cout << "]";
}

double RecordEntry::getLatestValue() {
	return values[(count-1+LOCAL_MEMORY_SIZE)%LOCAL_MEMORY_SIZE];
}

double RecordEntry::getLatestTime() {
	return times[(count-1+LOCAL_MEMORY_SIZE)%LOCAL_MEMORY_SIZE];
}

string RecordEntry::getLatestSenderId() {
	return senders[(count-1+LOCAL_MEMORY_SIZE)%LOCAL_MEMORY_SIZE];
}

long RecordEntry::getLatestPacketId() {
	return packetIds[(count-1+LOCAL_MEMORY_SIZE)%LOCAL_MEMORY_SIZE];
}

double RecordEntry::computeAverageValue() {
	double sum = 0;
	double count = 0;
	for (int i = 0; i < LOCAL_MEMORY_SIZE; ++i) {
		sum += values[i];
		if (values[i] != 0) {
			++count;
		}
	}
	return sum/count;
}

RecordEntry::~RecordEntry() {
}

} /* namespace ovnis */