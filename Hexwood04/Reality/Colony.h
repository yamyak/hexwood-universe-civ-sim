#pragma once

#include "Object.h"
#include "../Constants.h"

#include <atomic>
#include <map>

using namespace Constants;

class Planet;
class Empire;

class Colony : public Object
{
public:
	inline Colony() : m_planet(nullptr), m_age(0), m_current_period(CivilizationPeriod::PREHISTORY), m_empire(nullptr) {};
	Colony(Planet* planet, Empire* empire, std::map<CivilizationPeriod, int> period_lengths,
		std::map<CivilizationPeriod, std::map<ResourceType, float>> rates);
	Colony(Colony* colony);
	~Colony();

	void Run(std::mutex& mutex, std::queue<Object*>& queue);
	void SetPlanet(Planet* planet);
	Empire* GetEmpire();
	Planet* GetPlanet();

private:
	std::map<CivilizationPeriod, int> m_period_lengths;
	std::map<CivilizationPeriod, std::map<ResourceType, float>> m_consumption_rates;
	static std::atomic<int> m_global_id;
	Planet* m_planet;
	Empire* m_empire;
	CivilizationPeriod m_current_period;
	int m_age;

	bool FindNextColonyLocation(bool& planet, Object*& obj);
	bool DeepSkySearch(Object*& obj);
};

