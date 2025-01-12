# Rust DMA Base
  A simple tool that reads memory using a DMA card and prints out information about the local player, nearby players, NPCs, and animals.

## Showcase

All dictionaries automatically update and so does the information about each entity within it.
```
Local Player Dictionary:
2404756922368, BasePlayer LocalPlayer 6 Position: (593.798, 3.70077, 1266.54) Distance: 0

Player Dictionary:
2404785543168, BasePlayer assets/prefabs/player/player.prefab 6 Position: (709.837, 8.44316, 1280.47) Distance: 116.97
2393507401728, BasePlayer assets/prefabs/player/player.prefab 6 Position: (436.22, 0.924625, 1024.45) Distance: 288.864
2393467222016, BasePlayer assets/prefabs/player/player.prefab 6 Position: (598.622, 8.50341e-08, 1117.33) Distance: 149.333 (Player is sleeping)
2405062840320, BasePlayer assets/prefabs/player/player.prefab 6 Position: (460.862, -1.48414, 1295.87) Distance: 136.232
2404770918400, BasePlayer assets/prefabs/player/player.prefab 6 Position: (712.267, 7.13636, 1283.03) Distance: 119.662
2387972032512, BasePlayer assets/prefabs/player/player.prefab 6 Position: (709.863, 10.6726, 1286.05) Distance: 117.9
2393365833728, BasePlayer assets/prefabs/player/player.prefab 6 Position: (828.896, 18.0835, 1037.08) Distance: 328.831
2378871136256, BasePlayer assets/prefabs/player/player.prefab 6 Position: (525.303, 0, 1374.17) Distance: 127.635 (Player is sleeping)
2387972157440, BasePlayer assets/prefabs/player/player.prefab 6 Position: (511.989, 2.14448, 1279.7) Distance: 82.8753 (Player is sleeping)
2393507403776, BasePlayer assets/prefabs/player/player.prefab 6 Position: (514.48, 0.73698, 1278.34) Distance: 80.2453 (Player is sleeping)
2387933626368, BasePlayer assets/prefabs/player/player.prefab 6 Position: (842.224, 16.9676, 1259.93) Distance: 248.868 (Player is sleeping)
2393450706944, BasePlayer assets/prefabs/player/player.prefab 6 Position: (518.611, 0.0778262, 1091.58) Distance: 190.463 (Player is sleeping)
2393365831680, BasePlayer assets/prefabs/player/player.prefab 6 Position: (830.154, 18.2684, 1035.88) Distance: 330.571
2393450704896, BasePlayer assets/prefabs/player/player.prefab 6 Position: (731.406, -0.108317, 1139.41) Distance: 187.378 (Player is sleeping)
2393408679936, BasePlayer assets/prefabs/player/player.prefab 6 Position: (647.402, 6.47063, 1236.89) Distance: 61.3195 (Player is sleeping)
2393404010496, BasePlayer assets/prefabs/player/player.prefab 6 Position: (829.328, 17.3406, 1036.02) Distance: 329.845 (Player is sleeping)
2387933628416, BasePlayer assets/prefabs/player/player.prefab 6 Position: (500.419, 0, 1350.43) Distance: 125.581 (Player is sleeping)
2404770920448, BasePlayer assets/prefabs/player/player.prefab 6 Position: (695.974, 0.994733, 1421.2) Distance: 185.391

NPC Dictionary:
2393408681984, ScientistNPC assets/rust.ai/agents/npcplayer/humannpc/scientist/scientistnpc_junkpile_pistol.prefab 6

NPA Dictionary:
2404680996160, Bear assets/rust.ai/agents/bear/bear.prefab 0
2391993555584, Boar assets/rust.ai/agents/boar/boar.prefab 0
```

## Instructions
* [Installation](./Installation.md)

## Credits
* [PCILeech](https://github.com/ufrisk/pcileech)
* [MemProcFS](https://github.com/ufrisk/MemProcFS)
* [IL2CPP Dumper](https://github.com/Perfare/Il2CppDumper)
* [DMALibrary](https://github.com/Metick/DMALibrary/tree/Master)
