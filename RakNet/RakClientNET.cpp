#include "Common.h"
#include "BitStreamNET.h"
#include "RakClientNET.h"

RakClientNET::RakClientNET() {
	_rakClient = RakNetworkFactory::GetRakClientInterface();
}

RakClientNET::~RakClientNET() {
	RakNetworkFactory::DestroyRakClientInterface(_rakClient);
}

int RakClientNET::Connect(String ^ address, int port) {
	char password[] = {
			0x03, 0x62, 0x57, 0x46, 0x79, 0x4D, 0x6A, 0x75, 0x62, 0x65, 0x33, 0x34, 0x37, 0x59, 0x4B, 0x50,
			0x6C, 0x57, 0x62, 0x5A, 0x65, 0x2B, 0x6F, 0x56, 0x66, 0x39, 0x70, 0x44, 0x35, 0x37, 0x30, 0x2B,
			0x69, 0x54, 0x30, 0x4B, 0x6D, 0x56, 0x4E, 0x33, 0x6C, 0x79, 0x4A, 0x61, 0x6E, 0x32, 0x35, 0x4F,
			0x46, 0x72, 0x77, 0x6A, 0x70, 0x6D, 0x4B, 0x4C, 0x57, 0x62, 0x43, 0x78, 0x4A, 0x33, 0x4E, 0x37,
			0x6A, 0x6C, 0x63, 0x64, 0x56, 0x57, 0x71, 0x49, 0x53, 0x54, 0x37, 0x53, 0x51, 0x72, 0x39, 0x56,
			0x67, 0x4B, 0x42, 0x59, 0x75, 0x42, 0x51, 0x4B, 0x49, 0x31, 0x58, 0x7A, 0x65, 0x64, 0x44, 0x79,
			0x43, 0x46, 0x64, 0x42, 0x48, 0x37, 0x51, 0x4D, 0x61, 0x4C, 0x79, 0x78, 0x51, 0x43, 0x33, 0x63,
			0x48, 0x4D, 0x4B, 0x2B, 0x66, 0x65, 0x4B, 0x72, 0x75, 0x43, 0x6F, 0x6A, 0x7A, 0x42, 0x67, 0x43,
			0x30, 0x41, 0x36, 0x49, 0x71, 0x39, 0x6D, 0x2F, 0x2B, 0x79, 0x38, 0x71, 0x66, 0x52, 0x58, 0x68,
			0x52, 0x45, 0x75, 0x38, 0x51, 0x4F, 0x32, 0x4C, 0x36, 0x46, 0x52, 0x31, 0x65, 0x74, 0x30, 0x6C,
			0x56, 0x48, 0x35, 0x74, 0x37, 0x66, 0x68, 0x75, 0x62, 0x65, 0x33, 0x34, 0x62, 0x6B, 0x33, 0x33,
			0x47, 0x70, 0x53, 0x43, 0x55, 0x30, 0x63, 0x45, 0x68, 0x4C, 0x47, 0x63, 0x39, 0x54, 0x46, 0x42,
			0x55, 0x63, 0x4D, 0x2B, 0x32, 0x39, 0x6F, 0x59, 0x4D, 0x52, 0x42, 0x59, 0x68, 0x79, 0x6D, 0x65,
			0x35, 0x4A, 0x41, 0x79, 0x69, 0x2F, 0x44, 0x66, 0x38, 0x6B, 0x71, 0x5A, 0x36, 0x39, 0x65, 0x63,
			0x62, 0x65, 0x38, 0x38, 0x32, 0x00
	};

	_rakClient->SetPassword(password);
	return _rakClient->Connect(StringToChar(address), port, 0, 0, 5);
}

void RakClientNET::Disconnect(bool timeOut) {
	return _rakClient->Disconnect(timeOut ? 500 : 0);
}

PacketNET ^RakClientNET::Receive() {
	Packet *packet = _rakClient->Receive();
	PacketNET ^packetNet = gcnew PacketNET;
	packetNet->ID = static_cast<PacketEnumNET>(255);
	packetNet->Data = IntPtr(nullptr);
	packetNet->Length = 0;

	if (packet == nullptr)
		return packetNet;

	if (packet->data == nullptr)
		return packetNet;

	RakNet::BitStream bitStream(packet->data, packet->length, false);

	Byte packetId;
	bitStream.Read(packetId);

	int length = packet->length;
	char *data = new char[length];
	memcpy(data, packet->data, length);
	_rakClient->DeallocatePacket(packet);

	packetNet->ID = static_cast<PacketEnumNET>(packetId);
	packetNet->Data = IntPtr(data);
	packetNet->Length = length;
	return packetNet;
}

void RakClientNET::FreePacket(PacketNET ^packet) {
	void *data = packet->Data.ToPointer();

	if (data != nullptr)
		delete[] data;
}

bool RakClientNET::Send(BitStreamNET ^data) {
	return _rakClient->Send(data->GetBitStream(), SYSTEM_PRIORITY, RELIABLE, NULL);
}

bool RakClientNET::RPC(RPCEnumNET id, BitStreamNET ^data) {
	int rpcId = static_cast<int>(id);
	return _rakClient->RPC(&rpcId, data->GetBitStream(), HIGH_PRIORITY, RELIABLE, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
}

RPCParamsNET ^RakClientNET::HandleRPCParams(IntPtr data, int length) {
	BYTE *packetData = static_cast<BYTE *>(data.ToPointer());
	int packetLength = length;

	RakNet::BitStream bitStream(packetData, packetLength, false);

	bitStream.IgnoreBits(8);
	/* if (packetId == ID_TIMESTAMP)
		bitStream.IgnoreBits(8 * (sizeof(RakNetTime) + sizeof(unsigned char))); */

	RPCParamsNET ^rpcParams = gcnew RPCParamsNET;
	rpcParams->ID = static_cast<RPCEnumNET>(255);
	rpcParams->Data = IntPtr(nullptr);
	rpcParams->Length = 0;

	bool nameIsEncoded;
	if (!bitStream.Read(nameIsEncoded))
		return rpcParams;

	int *uniqueIdentifier = 0;
	if (!stringCompressor->DecodeString((char *)&uniqueIdentifier, 256, &bitStream))
		return rpcParams;

	BYTE rpcId = reinterpret_cast<BYTE>(uniqueIdentifier);

	bool blockingCommand;
	if (!bitStream.Read(blockingCommand))
		return rpcParams;

	DWORD sizeBits;
	if (!bitStream.ReadCompressed(sizeBits))
		return rpcParams;

	bool networkIDIsEncoded;
	if (!bitStream.Read(networkIDIsEncoded))
		return rpcParams;

	if (sizeBits == 0) {
		rpcParams->ID = static_cast<RPCEnumNET>(rpcId);
		return rpcParams;
	} else {
		BYTE *rpcData = new BYTE[BITS_TO_BYTES(sizeBits)];
		if (rpcData == nullptr)
			return rpcParams;

		if (!bitStream.ReadBits(rpcData, sizeBits)) {
			delete[] rpcData;
			return rpcParams;
		}

		rpcParams->ID = static_cast<RPCEnumNET>(rpcId);
		rpcParams->Data = IntPtr(rpcData);
		rpcParams->Length = BITS_TO_BYTES(sizeBits);
		return rpcParams;
	}
}

void RakClientNET::FreeRPC(RPCParamsNET ^rpcParams) {
	void *data = rpcParams->Data.ToPointer();

	if (data != nullptr)
		delete[] data;
}

void RakClientNET::SetNickName(String ^ nickName) {
	if (nickName->Length < 26)
		_rakClient->SetNickName(StringToChar(nickName));
}

String ^ RakClientNET::GetNickName() {
	return CharToString(_rakClient->GetNickName());
}

String ^RakClientNET::DumpMemory(IntPtr data, int length) {
	BYTE *dumpData = static_cast<BYTE *>(data.ToPointer());
	int dumpLength = length;

	return CharToString(DumpMem(dumpData, dumpLength));
}
