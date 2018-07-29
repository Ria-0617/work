#pragma once
#include "cinder/app/AppNative.h"

namespace MyFanc {
	template<typename T>
	void Clamp(T& value, T minValue, T maxValue) {
		value = value > maxValue ? maxValue : (value < minValue ? minValue : value);
	}

	template<typename T,typename U>
	inline void Clamp(T& value, U minValue, U maxValue) {
		value.x = value.x > maxValue ? maxValue : (value.x < minValue ? minValue : value.x);
		value.y = value.y > maxValue ? maxValue : (value.y < minValue ? minValue : value.y);
		value.z = value.z > maxValue ? maxValue : (value.z < minValue ? minValue : value.z);
	}

	template<typename T, typename U>
	inline void MoveLimit(T& value, U limitValue, U moveValue) {
		value.x += value.x > limitValue ? -moveValue : (value.x < -limitValue ? moveValue : 0);
		value.y += value.y > limitValue ? -moveValue : (value.y < -limitValue ? moveValue : 0);
		value.z += value.z > limitValue ? -moveValue : (value.z < -limitValue ? moveValue : 0);
	}

	template<typename T>
	inline void Console(T show) {
		ci::app::console() << show << std::endl;
	}

	inline ci::Vec3f ToRadians(const ci::Vec3f& degrees) {
		return degrees * (float)M_PI / 180.f;
	}

	inline ci::Vec3f ToDegrees(const ci::Vec3f& radians) {
		return radians * 180.f / (float)M_PI;
	}

	inline bool OutCircleCollider(ci::Vec3f pos, float radius, ci::Vec3f pos2, float radius2) {
		return pos.distance(pos2) > radius + radius2 ? true : false;
	}
}

