#include "pch.h"
#include "memory.h"
#include "CheatFunction.h"
#include "EntityInfo.h"
#include <dwmapi.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include <thread>
#include <Offsets.h>

uint64_t gameAssemblyBase;
std::unordered_map<uint64_t, entityInfo> globalEntityDict;

#define LODWORD(x) (*((uint32_t*)&(x)))
#define HIDWORD(x) ((uint32_t)(((uint64_t)(x) >> 32) & 0xFFFFFFFF))
#define COERCE_FLOAT(value) (*reinterpret_cast<float*>(&value))
#define _DWORD uint32_t
#define _OWORD uint32_t
#define __int128 uint64_t

uint32_t rotateRight(uint32_t Value, uint32_t Count) {
	uint32_t ValueMask = (8 * sizeof(Value) - 1);
	Count &= ValueMask;
	return (Value >> Count) | (Value << ((ValueMask + 1 - Count) & ValueMask));
}

bool testBITD(uint32_t Value, uint32_t BitPosition) {
	return (Value & (1 << BitPosition)) != 0;
}

uintptr_t decryptIl2cppHandle(uint32_t ptr) {
	// IDA -> Strings -> "il2cpp_gchandle_get_target" -> F5 -> il2cpp_gchandle_get_target_0
	uint64_t rdi_1 = ptr >> 3;
	uint64_t rcx_1 = (ptr & 7) - 1;
	uint64_t baseAddr = gameAssemblyBase + il2cppGCHandleBase + 0x28 * rcx_1;
	uint32_t limit = TargetProcess.Read<uint32_t>(baseAddr + 0x10);
	if (rdi_1 < limit) {
		uint64_t objAddr = TargetProcess.Read<uint64_t>(baseAddr);
		uint64_t bitMask = TargetProcess.Read<uint64_t>(objAddr + ((rdi_1 >> 5) << 2));
		if (testBITD(bitMask, rdi_1 & 0x1f)) {
			uint64_t objectArray = TargetProcess.Read<uint64_t>(baseAddr + 0x8) + (rdi_1 << 3);
			return TargetProcess.Read<BYTE>(baseAddr + 0x14) > 1
				? TargetProcess.Read<uint64_t>(objectArray)
				: ~TargetProcess.Read<uint64_t>(objectArray);
		}
	}
	return 0;
}

uint64_t decryptNet(uintptr_t a1) {

	int* v17; // rdx
	int v18; // r8d
	int v19; // eax
	signed __int64 v20; // rcx
	__int128 v36; // [rsp+68h] [rbp+20h] OVERLAPPED BYREF

	v17 = (int*)&v36;
	v18 = 2;
	v36 = TargetProcess.Read<__int128>(a1 + 24);
	do
	{
		v19 = *v17++;
		*(v17 - 1) = ((((v19 + 2088045315) << 20) | ((unsigned int)(v19 + 2088045315) >> 12)) + 62779575) ^ 0xEA3B039;
		--v18;
	} while (v18);
	signed __int64 v9 = *reinterpret_cast<signed __int64*>(&v36);
	return decryptIl2cppHandle(v9);

}

uint64_t decryptBasePlayer(uint64_t a1) {
	int* v4; // rdx
	int v5; // r8d
	unsigned int v6; // ecx
	int v7; // eax
	signed __int64 v8; // rcx
	__int128 v24;

	v4 = (int*)&v24;
	v5 = 2;
	v24 = TargetProcess.Read<_OWORD>(a1 + 24);
	do
	{
		v6 = *v4;
		v7 = *v4++;
		*(v4 - 1) = (((v7 << 12) | (v6 >> 20)) ^ 0xB0B6B6C3) - 610664064;
		--v5;
	} while (v5);
	v8 = v24;
	return decryptIl2cppHandle(v8);
}

uint64_t decryptUlongKey(uint64_t a1) {
	int* v4; // rdx
	int v5; // r8d
	unsigned int v6; // ecx
	int v7; // eax
	signed __int64 v8; // rcx
	uint64_t v24; // [rsp+20h] [rbp-28h] BYREF
	v4 = (int*)&v24;
	v5 = 2;
	memcpy(&v24, &a1, sizeof(a1));
	do
	{
		v6 = *v4;
		v7 = *v4++;
		*(v4 - 1) = (((v7 << 12) | (v6 >> 20)) ^ 0xB0B6B6C3) - 610664064;
		--v5;
	} while (v5);
	v8 = v24;
	return v8;

}

uint64_t decryptInventoryPointer(uint64_t pointer)
{
	auto il2cpp_object = decryptIl2cppHandle((std::int32_t)decryptUlongKey(TargetProcess.Read<std::uint64_t>(pointer + 0x18)));
	return il2cpp_object;
}

struct Vec3 {
	float x, y, z;
};

Vec3 getPos(uint64_t basePlayerAddress) {
	uint64_t playerModel = TargetProcess.Read<uint64_t>(basePlayerAddress + PlayerModelOffset);
	Vec3 playerModelPosition = TargetProcess.Read<Vec3>(playerModel + PlayerModelPositionOffset);

	return playerModelPosition;
}

std::unordered_map<uint64_t, entityInfo> createEntityDictionary(uint64_t gameAssemblyBase) {
	std::unordered_map<uint64_t, entityInfo> dict;

	uint64_t baseNetworkable = TargetProcess.Read<uint64_t>(gameAssemblyBase + BaseNetworkableOffset);
	//printf("baseNet: %llx\n", baseNet);
	if (!baseNetworkable) {
		printf("Failed to Read baseNet\n");
		return dict;
	}

	uint64_t staticBaseNet = TargetProcess.Read<uint64_t>(baseNetworkable + staticBaseNetOffset);
	//printf("staticBaseNet: %llx\n", staticBaseNet);
	if (!staticBaseNet) {
		printf("Failed to Read staticBaseNet\n");
		return dict;
	}

	uint64_t wrapperPtr = TargetProcess.Read<uint64_t>(staticBaseNet + 0x28);
	//printf("wrapperPtr: %llx\n", wrapperPtr);
	if (!wrapperPtr) {
		printf("Failed to Read wrapperPtr\n");
		return dict;
	}

	uint64_t wrapper = decryptNet(wrapperPtr);
	//printf("Wrapper: %llx\n", wrapper);
	if (!wrapper) {
		printf("Failed to decrypt wrapper\n");
		return dict;
	}

	uint64_t parentStatic = TargetProcess.Read<uint64_t>(wrapper + 0x10);
	//printf("Parent static: %llx\n", parentStatic);
	if (!parentStatic) {
		printf("Failed to read parent static\n");
		return dict;
	}

	auto parentClass = decryptNet(parentStatic);
	//printf("Parent class: %llx\n", parentClass);
	if (!parentClass) {
		printf("Failed to Decrypt parent class\n");
		return dict;
	}
	uint64_t objectDictionary = TargetProcess.Read<uint64_t>(parentClass + 0x18);

	auto entityListSize = TargetProcess.Read<uint32_t>(objectDictionary + 0x18);
	auto entityListBase = TargetProcess.Read<uint64_t>(objectDictionary + 0x10);

	//printf("entitylist base : %llx\n", entityListBase);
	//printf("entitylist size : %lx\n", entityListSize);


	auto scatter = TargetProcess.CreateScatterHandle();

	std::vector<uint64_t> Entitys(entityListSize);
	for (int i = 0; i < entityListSize; i++) {
		if (!entityListBase)
			continue;

		TargetProcess.AddScatterReadRequest(scatter, entityListBase + 0x20 + (i * 0x8), &Entitys[i], sizeof(uint64_t));
	}
	TargetProcess.ExecuteReadScatter(scatter);

	std::vector<uint64_t> baseMonoObjects(entityListSize);
	for (int i = 0; i < entityListSize; i++) {
		if (!Entitys[i])
			continue;

		TargetProcess.AddScatterReadRequest(scatter, Entitys[i] + 0x10, &baseMonoObjects[i], sizeof(uint64_t));
	}
	TargetProcess.ExecuteReadScatter(scatter);

	std::vector<uint64_t> objectUnks(entityListSize);
	for (int i = 0; i < entityListSize; i++) {
		if (!Entitys[i])
			continue;

		TargetProcess.AddScatterReadRequest(scatter, Entitys[i], &objectUnks[i], sizeof(uint64_t));
	}
	TargetProcess.ExecuteReadScatter(scatter);

	std::vector<uint64_t> namePtrs(entityListSize);
	for (int i = 0; i < entityListSize; i++) {
		if (!objectUnks[i])
			continue;

		TargetProcess.AddScatterReadRequest(scatter, objectUnks[i] + 0x10, &namePtrs[i], sizeof(uint64_t));
	}
	TargetProcess.ExecuteReadScatter(scatter);

	std::vector<uint64_t> objects(entityListSize);
	for (int i = 0; i < entityListSize; i++) {
		if (!baseMonoObjects[i])
			continue;

		TargetProcess.AddScatterReadRequest(scatter, baseMonoObjects[i] + 0x30, &objects[i], sizeof(uint64_t));
	}
	TargetProcess.ExecuteReadScatter(scatter);

	std::vector<uint64_t> prefabs(entityListSize);
	for (int i = 0; i < entityListSize; i++) {
		if (!objects[i])
			continue;

		TargetProcess.AddScatterReadRequest(scatter, objects[i] + 0x60, &prefabs[i], sizeof(uint64_t));
	}
	TargetProcess.ExecuteReadScatter(scatter);

	std::vector<WORD> tags(entityListSize);
	for (int i = 0; i < entityListSize; i++) {
		if (!objects[i])
			continue;

		TargetProcess.AddScatterReadRequest(scatter, objects[i] + 0x54, &tags[i], sizeof(WORD));
	}
	TargetProcess.ExecuteReadScatter(scatter);

	std::vector<char> classBuff(0x200 * entityListSize);
	for (int i = 0; i < entityListSize; i++) {
		if (!namePtrs[i])
			continue;

		TargetProcess.AddScatterReadRequest(scatter, namePtrs[i], &classBuff[i * 0x200], 0x200);

	}

	std::vector<char> prefabBuff(256 * entityListSize, 0);

	for (int i = 0; i < entityListSize; i++) {
		if (!prefabs[i])
			continue;

		TargetProcess.AddScatterReadRequest(scatter, prefabs[i], &prefabBuff[i * 256], 256);
	}


	TargetProcess.ExecuteReadScatter(scatter);

	for (int i = 0; i < entityListSize; i++) {
		if (!Entitys[i] || !baseMonoObjects[i] || !objectUnks[i] || !namePtrs[i] || !objects[i])
			continue;

		std::string className(reinterpret_cast<char*>(&classBuff[i * 0x200]));

		std::string prefabName = "";
		if (prefabs[i]) {
			prefabName = std::string(&prefabBuff[i * 256]);
		}

		WORD tag = tags[i];
		dict[Entitys[i]] = { className, prefabName, tag };
	}

	return dict;
}

uint32_t getPlayerFlags(uint64_t basePlayerAddress) {
	return TargetProcess.Read<uint32_t>(basePlayerAddress + PlayerFlagsOffset);
}

std::unordered_map<uint64_t, entityInfo> createPlayerDictionary(const std::unordered_map<uint64_t, entityInfo>& inputDict) {
	std::unordered_map<uint64_t, entityInfo> dict;
	for (const auto& pair : inputDict) {
		if (pair.second.className == "BasePlayer" && pair.second.prefabName != "LocalPlayer") {
			dict[pair.first] = pair.second;
		}
	}
	return dict;
};

std::unordered_map<uint64_t, entityInfo> createLocalPlayerDictionary(const std::unordered_map<uint64_t, entityInfo>& inputDict) {
	std::unordered_map<uint64_t, entityInfo> dict;
	for (const auto& pair : inputDict) {
		if (pair.second.prefabName == "LocalPlayer") {
			dict[pair.first] = pair.second;
		}
	}
	return dict;
};

std::unordered_map<uint64_t, entityInfo> createNPCDictionary(const std::unordered_map<uint64_t, entityInfo>& inputDict) {
	std::unordered_map<uint64_t, entityInfo> dict;
	for (const auto& pair : inputDict) {
		if (pair.second.className == "BanditGuard" || pair.second.className == "ScientistNPC" || pair.second.className == "TunnelDweller" || pair.second.className == "UnderwaterDweller") {
			dict[pair.first] = pair.second;
		}
	}
	return dict;
};

std::unordered_map<uint64_t, entityInfo> createNPADictionary(const std::unordered_map<uint64_t, entityInfo>& inputDict) {
	std::unordered_map<uint64_t, entityInfo> dict;
	for (const auto& pair : inputDict) {
		if (pair.second.className == "Boar" || pair.second.className == "Stag" || pair.second.className == "Bear" || pair.second.className == "Wolf2" || pair.second.className == "RidableHorse") {
			dict[pair.first] = pair.second;
		}
	}
	return dict;
};

void filterEntityDictionary(
	const std::unordered_map<uint64_t, entityInfo>& inputDict,
	std::unordered_map<uint64_t, entityInfo>& localPlayerDict,
	std::unordered_map<uint64_t, entityInfo>& playerDict,
	std::unordered_map<uint64_t, entityInfo>& npcDict,
	std::unordered_map<uint64_t, entityInfo>& npaDict
) {
	// Clear all output dictionaries first
	localPlayerDict.clear();
	playerDict.clear();
	npcDict.clear();
	npaDict.clear();

	// Iterate over the input dictionary once and sort based on the className and prefabName
	for (const auto& pair : inputDict) {
		const entityInfo& entity = pair.second;

		// Sort by prefabName first for quick classification
		if (entity.prefabName == "LocalPlayer") {
			localPlayerDict[pair.first] = entity;
		}
		else if (entity.className == "BasePlayer" && entity.prefabName != "LocalPlayer") {
			playerDict[pair.first] = entity;
		}
		else if (entity.className == "BanditGuard" || entity.className == "ScientistNPC" ||
			entity.className == "TunnelDweller" || entity.className == "UnderwaterDweller") {
			npcDict[pair.first] = entity;
		}
		else if (entity.className == "Boar" || entity.className == "Stag" || entity.className == "Bear" ||
			entity.className == "Wolf2" || entity.className == "RidableHorse") {
			npaDict[pair.first] = entity;
		}
	}
}


float calculateDistance(const Vec3& pos1, const Vec3& pos2) {
	return sqrtf(powf(pos2.x - pos1.x, 2) + powf(pos2.y - pos1.y, 2) + powf(pos2.z - pos1.z, 2));
}



void printEntityDictionary(const std::unordered_map<uint64_t, entityInfo>& dict, const std::string& name, const Vec3& localPlayerPos) {
	std::cout << name << ":\n";
	for (const auto& pair : dict) {
		std::cout << pair.first << ", " << pair.second;

		if (pair.second.className == "BasePlayer") {
			Vec3 position = getPos(pair.first);
			uint32_t flags = getPlayerFlags(pair.first);

			std::cout << " Position: (" << position.x << ", " << position.y << ", " << position.z << ")";

			float distance = calculateDistance(localPlayerPos, position);
			std::cout << " Distance: " << distance;

			if (flags == 16) {
				std::cout << " (Player is sleeping)";
			}
		}

		std::cout << std::endl;
	}
	std::cout << "\n";
}

void updateAndPrintEntityDictionariesWithPos(uint64_t gameAssemblyBase) {
	std::unordered_map<uint64_t, entityInfo> entityDictionary = createEntityDictionary(gameAssemblyBase);

	// Initialize filtered dictionaries
	std::unordered_map<uint64_t, entityInfo> localPlayerDictionary;
	std::unordered_map<uint64_t, entityInfo> playerDictionary;
	std::unordered_map<uint64_t, entityInfo> NPCDictionary;
	std::unordered_map<uint64_t, entityInfo> NPADictionary;

	// Filter the entity dictionary
	filterEntityDictionary(entityDictionary, localPlayerDictionary, playerDictionary, NPCDictionary, NPADictionary);

	auto lastUpdateTime = std::chrono::steady_clock::now();
	auto lastPosUpdateTime = std::chrono::steady_clock::now();

	while (true) {
		auto now = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed = now - lastUpdateTime;
		std::chrono::duration<double> posElapsed = now - lastPosUpdateTime;

		// Update position and print every 0.1 seconds
		if (posElapsed.count() >= 0.1) {
			system("cls");

			// Assuming we have at least one local player, get the position from the first entry
			if (!localPlayerDictionary.empty()) {
				Vec3 localPlayerPos = getPos(localPlayerDictionary.begin()->first);

				// Print filtered dictionaries with position
				printEntityDictionary(localPlayerDictionary, "Local Player Dictionary", localPlayerPos);
				printEntityDictionary(playerDictionary, "Player Dictionary", localPlayerPos);
				printEntityDictionary(NPCDictionary, "NPC Dictionary", localPlayerPos);
				printEntityDictionary(NPADictionary, "NPA Dictionary", localPlayerPos);
			}

			lastPosUpdateTime = now;
		}

		// Update every 5 seconds
		if (elapsed.count() >= 5.0) {
			// Re-fetch and re-filter the entity dictionary
			entityDictionary = createEntityDictionary(gameAssemblyBase);
			filterEntityDictionary(entityDictionary, localPlayerDictionary, playerDictionary, NPCDictionary, NPADictionary);

			lastUpdateTime = now;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}


void main()
{
	while (!TargetProcess.Init("RustClient.exe", true, false))
	{
		std::cout << "Failed to initialize memory read. Retrying\n";
		Sleep(10);
	}

	gameAssemblyBase = TargetProcess.GetBaseAddress("GameAssembly.dll");

	updateAndPrintEntityDictionariesWithPos(gameAssemblyBase);
}
