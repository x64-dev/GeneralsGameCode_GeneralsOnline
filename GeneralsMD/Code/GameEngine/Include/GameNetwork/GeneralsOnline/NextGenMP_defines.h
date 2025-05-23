#pragma once

#if !defined(GENERALS_ONLINE)
#define GENERALS_ONLINE
#endif

//#define USE_ENCRYPTED_SERVICE_TOKENS 1

//#define GENERALS_ONLINE_GAMETYPE_GENERALS
#define GENERALS_ONLINE_GAMETYPE_ZEROHOUR

//#define GENERALS_ONLINE_BRANCH_JMARSHALL
#define GENERALS_ONLINE_BRANCH_SUPERHACKERS

#define RTS_MULTI_INSTANCE 1

#define ALLOW_NON_PROFILED_LOGIN 1

#define NATPMP_STATICLIB 1

#define GENERALS_ONLINE_VERSION 1
#define GENERALS_ONLINE_NET_VERSION 1
#define GENERALS_ONLINE_SERVICE_VERSION 1

// annoying game assertions, we'll catch real things in the debugger
#define DISABLE_DEBUG_CRASHING 1

//#define GENERALS_ONLINE_TEST_MAP_TRANSFER 1

//#define NETWORK_CONNECTION_DEBUG 1

//#define GENERALS_ONLINE_RUN_FAST 1

#define GENERALS_ONLINE_HIGH_FPS_SERVER 1
#define GENERALS_ONLINE_HIGH_FPS_LIMIT 60

// useful for testing release builds with multiple logins
//#define GENERALS_ONLINE_DONT_SAVE_CREDENTIALS 1

#if !_DEBUG
#define GENERALS_ONLINE_USE_SENTRY 1
#endif

// NOTE: This is temporary until we work out why this causes mismatch when some players set it and others dont
#if !_DEBUG
#define GENERALS_ONLINE_DISABLE_QUICKSTART_FUNCTIONALITY 1
#endif