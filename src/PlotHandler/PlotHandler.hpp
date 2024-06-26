#ifndef _PLOTHANDLER_HPP
#define _PLOTHANDLER_HPP

#include <chrono>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "Plot.hpp"
#include "PlotHandlerBase.hpp"
#include "ScrollingBuffer.hpp"
#include "TargetMemoryHandler.hpp"
#include "spdlog/spdlog.h"

class PlotHandler : public PlotHandlerBase
{
   public:
	typedef struct Settings
	{
		uint32_t samplePeriod = 10;
		uint32_t maxPoints = 10000;
		uint32_t maxViewportPoints = 5000;
	} Settings;

	typedef struct
	{
		uint32_t debugProbe = 0;
		std::string serialNumber = "";
		std::string device = "";
	} DebugProbeSettings;

	PlotHandler(std::atomic<bool>& done, std::mutex* mtx, spdlog::logger* logger);
	virtual ~PlotHandler();

	std::string getLastReaderError() const;
	bool writeSeriesValue(Variable& var, double value);

	Settings getSettings() const;
	void setSettings(const Settings& newSettings);
	void setDebugProbe(std::shared_ptr<IDebugProbe> probe, const std::string& serialNumber);
	void setTargetDevice(const std::string& deviceName);

	DebugProbeSettings probeSettings{};

   private:
	void dataHandler();

   private:
	std::unique_ptr<TargetMemoryHandler> varReader;
	std::chrono::time_point<std::chrono::steady_clock> start;
	Settings settings{};
};

#endif