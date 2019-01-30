#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

public enum struct RPCEnumNET {
	RPC_ServerCommand = 6,
	RPC_SetInteriorId,
	RPC_MapMarker,
	RPC_VehicleDestroyed,
	RPC_ServerJoin,
	RPC_ServerQuit,
	RPC_InitGame,
	RPC_ConnectionRejected,
	RPC_ClientMessage,
	RPC_Weather = 19,
	RPC_ScrSetPlayerSkin,
	RPC_ScrSetPlayerName,
	RPC_ScrSetPlayerPos,
	RPC_ScrSetPlayerPosFindZ,
	RPC_ScrSetPlayerHealth,
	RPC_ScrPutPlayerInVehicle,
	RPC_ScrRemovePlayerFromVehicle,
	RPC_ScrSetPlayerColor,
	RPC_ScrDisplayGameText,
	RPC_ScrForceSpawnSelection,
	RPC_ScrInitMenu = 31,
	RPC_ScrShowMenu,
	RPC_ScrHideMenu,
	RPC_ScrSetPlayerWantedLevel,
	RPC_ScrShowTextDraw,
	RPC_ScrHideTextDraw,
	RPC_ScrEnableStuntBonus,
	RPC_ScrEditTextDraw,
	RPC_ScrAddGangZone,
	RPC_PlayAudioStream = 45,
	RPC_ScrCreateObject = 48,
	RPC_ScrSetObjectPos,
	RPC_ScrSetObjectRotation,
	RPC_ScrDestroyObject,
	RPC_ScrCreateExplosion = 54,
	RPC_ClickTextDraw = 58,
	RPC_PlayerGiveDamage = 60,
	RPC_ScrEditObject = 62,
	RPC_ScrSelectObject,
	RPC_ConnectionPong = 65,
	RPC_ScrWorldPlayerAdd = 69,
	RPC_ScrSetPlayerDrunkHandling = 72,
	RPC_ScrDialogBox = 77,
	RPC_DialogResponse,
	RPC_ClickPlayer,
	RPC_ScrVehicleParams,
	RPC_ClientJoin,
	RPC_ScrRemoveGangZone,
	RPC_ScrFlashGangZone,
	RPC_ScrStopFlashGangZone,
	RPC_ScrSetSpecialAction = 87,
	RPC_ScrSetFightingStyle,
	RPC_ScrSetPlayerVelocity,
	RPC_ScrTogglePlayerSpectating = 97,
	RPC_ScrSetPlayerSpectating,
	RPC_ScrPlayerSpectatePlayer,
	RPC_ScrPlayerSpectateVehicle,
	RPC_RequestClass,
	RPC_RequestSpawn,
	RPC_EnterVehicle,
	RPC_ExitVehicle,
	RPC_UpdateScoresPingsIPs,
	RPC_ScrSetCameraPos = 107,
	RPC_ScrSetCameraLookAt,
	RPC_ScrSetVehiclePos,
	RPC_ScrSetCameraBehindPlayer = 112,
	RPC_ScrTogglePlayerControllable,
	RPC_ScrPlaySound,
	RPC_ScrSetPlayerFacingAngle = 117,
	RPC_ScrResetMoney,
	RPC_ScrResetPlayerWeapons,
	RPC_ScrGivePlayerWeapon,
	RPC_ScrSetPlayerArmour = 123,
	RPC_ScrSetSpawnInfo = 125,
	RPC_ScrSetPlayerTeam,
	RPC_ScrWorldPlayerRemove,
	RPC_ScrWorldVehicleAdd,
	RPC_ScrRespawnVehicle,
	RPC_ScrWorldPlayerDeath,
	RPC_DamageVehicle,
	RPC_GameModeRestart = 136,
	RPC_Chat = 138,
	RPC_ScrRemoveComponent = 140,
	RPC_PickedUpPickup = 142,
	RPC_MenuSelect,
	RPC_MenuQuit,
	RPC_Spawn = 150,
	RPC_Death,
	RPC_NPCJoin,
	RPC_ScrDeathMessage,
	RPC_ScrSetMapIcon,
	RPC_ScrDisableMapIcon,
	RPC_ScrSetGravity = 157,
	RPC_ScrSetVehicleHealth,
	ID_ERROR = 255
};

public enum class PacketEnumNET {
	ID_INTERNAL_PING = 4,
	ID_PING,
	ID_PING_OPEN_CONNECTIONS,
	ID_CONNECTED_PONG,
	ID_PAD1,
	ID_PAD11,
	ID_PAD12,
	ID_REQUEST_STATIC_DATA,
	ID_CONNECTION_REQUEST,
	ID_PAD2,
	ID_SECURED_CONNECTION_RESPONSE,
	ID_SECURED_CONNECTION_CONFIRMATION,
	ID_RPC_MAPPING,
	ID_PAD3,
	ID_PAD5,
	ID_PAD6,
	ID_DETECT_LOST_CONNECTIONS,
	ID_OPEN_CONNECTION_REQUEST,
	ID_OPEN_CONNECTION_REPLY,
	ID_PAD4,
	ID_RPC,
	ID_RPC_REPLY,
	ID_BROADCAST_PINGS,
	ID_SET_RANDOM_NUMBER_SEED,
	ID_CONNECTION_REQUEST_ACCEPTED,
	ID_CONNECTION_ATTEMPT_FAILED,
	ID_NEW_INCOMING_CONNECTION,
	ID_NO_FREE_INCOMING_CONNECTIONS,
	ID_DISCONNECTION_NOTIFICATION,
	ID_CONNECTION_LOST,
	ID_RSA_PUBLIC_KEY_MISMATCH,
	ID_CONNECTION_BANNED,
	ID_INVALID_PASSWORD,
	ID_MODIFIED_PACKET,
	ID_TIMESTAMP,
	ID_PONG,
	ID_RECEIVED_STATIC_DATA,
	ID_REMOTE_DISCONNECTION_NOTIFICATION,
	ID_REMOTE_CONNECTION_LOST,
	ID_REMOTE_NEW_INCOMING_CONNECTION,
	ID_REMOTE_EXISTING_CONNECTION,
	ID_REMOTE_STATIC_DATA,
	// ...
	ID_ADVERTISE_SYSTEM = 51,
	ID_CONNECTED_NOTIFY = 69,

	ID_UNOCCUPIED_SYNC = 110,

	ID_SPECTATOR_SYNC = 113,
	ID_TRAILER_SYNC,
	ID_PASSENGER_SYNC,
	ID_PLAYER_SYNC,
	ID_AIM_SYNC,
	ID_VEHICLE_SYNC,
	ID_RCON_COMMAND,
	ID_RCON_RESPONCE,
	ID_STATS_UPDATE,
	ID_WEAPONS_UPDATE,
	ID_MARKERS_SYNC,

	ID_ERROR = 255
};

public ref struct PacketNET {
	PacketEnumNET ID;
	IntPtr Data;
	int Length;
};

public ref struct RPCParamsNET {
	RPCEnumNET ID;
	IntPtr Data;
	int Length;
};

public ref class RakClientNET {
private:
	RakClientInterface * _rakClient;

	char *StringToChar(String^ string) {
		return static_cast<char *>(Marshal::StringToHGlobalAnsi(string).ToPointer());
	}

	String ^CharToString(char *ch) {
		return gcnew String(ch);
		/* String ^str;
		for (int i = 0; ch[i] != 0; i++)
			str += wchar_t(ch[i]);
		return str; */
	}

public:
	RakClientNET();
	~RakClientNET();

	int Connect(String ^address, int port);
	void Disconnect(bool timeOut);

	PacketNET ^Receive();
	void FreePacket(PacketNET ^packet);
	bool Send(BitStreamNET ^data);

	RPCParamsNET ^HandleRPCParams(IntPtr data, int length);
	void FreeRPC(RPCParamsNET ^rpcParams);
	bool RPC(RPCEnumNET id, BitStreamNET ^data);

	void SetNickName(String ^nickName);
	String ^GetNickName();

	String ^DumpMemory(IntPtr data, int length);
};