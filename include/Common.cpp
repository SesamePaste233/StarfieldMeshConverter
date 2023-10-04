#include "Common.h"

using namespace array_ops;



const std::vector<FloatArray> array_ops::organizeData(const std::vector<float>& plain)
{
	std::vector<FloatArray> organized;
	organized.resize(plain.size() / 3);
	std::memcpy(organized.data(), plain.data(), plain.size() * sizeof(float));
	return organized;
}
const std::vector<float> array_ops::flattenData(const std::vector<FloatArray>& organized)
{
	std::vector<float> plain;
	plain.resize(organized.size() * 3);
	std::memcpy(plain.data(), organized.data(), organized.size() * sizeof(FloatArray));
	return plain;
}

size_t array_ops::normalizeByAttributes(const std::vector<float>& plainAttributes, std::vector<float>& plainValues)
{
	std::vector<FloatArray> attributes = organizeData(plainAttributes);
	std::vector<FloatArray> values = organizeData(plainValues);

	// Create a map to store sum and count for each attribute
	std::unordered_map<FloatArray, std::pair<FloatArray, int>> attributeData;

	// Iterate through the attributes and indices
	for (int i = 0; i < attributes.size(); ++i) {
		FloatArray attribute = attributes[i];
		FloatArray value = values[i];

		// Check if the attribute exists in the map
		if (attributeData.find(attribute) == attributeData.end()) {
			// If not, initialize it with the current value and count
			attributeData[attribute] = std::make_pair(value, 1);
		}
		else {
			// If it exists, update the sum and count
			attributeData[attribute].first += value;
			attributeData[attribute].second += 1;
		}
	}

	// Calculate the average values
	size_t num_normalized = 0;
	std::unordered_map<FloatArray, FloatArray> averageValues;
	for (const auto& pair : attributeData) {
		int count = pair.second.second;
		FloatArray attribute = pair.first;
		FloatArray sum = pair.second.first;
		FloatArray average = sum;

		if (count > 1) {
			average.normalize();
			num_normalized += count - 1;
		}

		averageValues[attribute] = average;
	}

	// Replace the values with the average values
	for (int i = 0; i < values.size(); ++i) {
		FloatArray attribute = attributes[i];
		values[i] = averageValues[attribute];
	}

	plainValues = flattenData(values);

	return num_normalized;
}