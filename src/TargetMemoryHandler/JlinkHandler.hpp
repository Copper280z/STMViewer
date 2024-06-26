#ifndef _JLINKHANDLER_HPP
#define _JLINKHANDLER_HPP

#include <string>
#include <vector>

#include "IDebugProbe.hpp"
#include "JlinkDynamicLibraryLoader.hpp"
#include "spdlog/spdlog.h"

class JlinkHandler : public IDebugProbe
{
   public:
	JlinkHandler(spdlog::logger* logger);
	bool startAcqusition(const std::string& serialNumber, const std::string& device = "") override;
	bool stopAcqusition() override;
	bool isValid() const override;

	bool readMemory(uint32_t address, uint32_t* value) override;
	bool writeMemory(uint32_t address, uint8_t* buf, uint32_t len) override;

	std::string getLastErrorMsg() const override;
	std::vector<std::string> getConnectedDevices() override;

	bool requiresAlignedAccessOnRead() override
	{
		return false;
	}

   private:
	DynamicLibraryLoader dynamicLibraryLoader;
	JlinkFunctions jlinkFunctions;
	bool isRunning = false;
	bool isLoaded = false;
	std::string lastErrorMsg = "";
	spdlog::logger* logger;
};

#endif