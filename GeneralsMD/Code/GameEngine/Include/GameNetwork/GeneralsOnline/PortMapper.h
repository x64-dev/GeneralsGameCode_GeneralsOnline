#pragma once

//#define DISABLE_UPNP 1
//#define DISABLE_NATPMP 1
//#define DISABLE_PCP 1

#define NATPMP_STATICLIB 1
#pragma comment(lib, "iphlpapi.lib")

#include "GameNetwork/GeneralsOnline/Vendor/libplum/plum.h"

#include "GameNetwork/GeneralsOnline/Vendor/libnatpmp/natpmp.h"
#include "GameNetwork/GeneralsOnline/Vendor/miniupnpc/miniupnpc.h"
#include "GameNetwork/GeneralsOnline/Vendor/miniupnpc/miniupnpctypes.h"
#include "GameNetwork/GeneralsOnline/Vendor/miniupnpc/upnperrors.h"
#include "GameNetwork/GeneralsOnline/Vendor/miniupnpc/upnpcommands.h"
#include <functional>
#include <thread>

enum ECapabilityState : uint8_t
{
	UNDETERMINED,
	UNSUPPORTED,
	SUPPORTED
};

class PortMapper
{
public:
	~PortMapper()
	{
		CleanupPorts();
	}

	void Tick();
	void StartNATCheck();

	enum class EMappingTech
	{
		NONE = -1,
		PCP,
		UPNP,
		NATPMP,
#if !defined(GENERALS_ONLINE_PORT_MAP_FIREWALL_OVERRIDE_PORT)
		MANUAL
#endif
	};

	void DetermineLocalNetworkCapabilities(std::function<void(void)> callbackDeterminedCaps);

	void ForwardPort_UPnP();
	void ForwardPort_NATPMP();
	void ForwardPort_PCP();

	void CleanupPorts();

	ECapabilityState HasDirectConnect()
	{
		return m_directConnect;
	}

	bool HasPortOpen() const { return m_bPortMapper_AnyMappingSuccess.load(); }
	EMappingTech GetPortMappingTechnologyUsed() const { return m_bPortMapper_MappingTechUsed.load(); }
	int GetOpenPort() const { return m_PreferredPort.load(); }

	void UPnP_RemoveAllMappingsToThisMachine();

	void StorePCPOutcome(bool bSucceeded);

private:

	void RemovePortMapping_UPnP();
	void RemovePortMapping_NATPMP();
	void RemovePortMapping_PCP();

private:
	std::function<void(void)> m_callbackDeterminedCaps = nullptr;
	ECapabilityState m_directConnect = ECapabilityState::UNDETERMINED;

	std::atomic<uint16_t> m_PreferredPort = 0;

	SOCKET m_NATSocket = INVALID_SOCKET;
	bool m_bNATCheckInProgress = false;

	std::atomic<bool> m_bPortMapperWorkComplete = false;

	const int m_probeTimeout = 3000;
	int64_t m_probeStartTime = -1;
	static const int m_probesExpected = 5;
	bool m_probesReceived[m_probesExpected];

	// TODO_NGMP: Do we need to refresh this periodically? or just do it on login. It would be kinda weird if the local network device changed during gameplay...
	struct UPNPDev* m_pCachedUPnPDevice = nullptr;

	int64_t m_timeStartPortMapping = -1;
	std::thread* m_backgroundThread_UPNP = nullptr;
	std::thread* m_backgroundThread_NATPMP = nullptr;
	std::thread* m_backgroundThread_PCP = nullptr;
	bool m_bNATCheckStarted = false;
	std::atomic<bool> m_bPortMapper_AnyMappingSuccess = false;
	std::atomic<bool> m_bPortMapper_NATPMP_Complete = false;
	std::atomic<bool> m_bPortMapper_UPNP_Complete = false;
	std::atomic<bool> m_bPortMapper_PCP_Complete = false;
	std::atomic<EMappingTech> m_bPortMapper_MappingTechUsed = EMappingTech::NONE;

	int m_PCPMappingHandle = -1;
};

// TODO_PORT: What if everything fails? does it still return?