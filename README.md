# Rust DMA Base
  A simple tool that reads memory using a DMA card and prints out information about the local player, nearby players, NPCs, and animals.

## Showcase

All dictionaries automatically update and so does the information about each entity within it.
```
Local Player Dictionary:
2333852524544, BasePlayer LocalPlayer 6 Position: (-1266.9, 5.53523, 886.926) Position on screen : (0, 0) Distance: 0

Player Dictionary:
2321684840448, BasePlayer assets/prefabs/player/player.prefab 6 Position: (-1017.64, 1.13512, 626.688) Position on screen : (1133.01, 695.966) Distance: 360.38
2334246170624, BasePlayer assets/prefabs/player/player.prefab 6 Position: (-1324.35, 3.9035, 741.067) Position on screen : (2264.33, 708.322) Distance: 156.774
2334241968128, BasePlayer assets/prefabs/player/player.prefab 6 Position: (-1231.79, 32.8274, 735.586) Position on screen : (1533.52, 555.636) Distance: 157.738
2334241695744, BasePlayer assets/prefabs/player/player.prefab 6 Position: (-1314.47, 1.09815, 722.298) Position on screen : (2090.8, 721.541) Distance: 171.42 (Player is sleeping)
2331191613440, BasePlayer assets/prefabs/player/player.prefab 6 Position: (-1143.42, -0.636481, 697.151) Position on screen : (1269.8, 708.355) Distance: 226.499 (Player is sleeping)
2331771019264, BasePlayer assets/prefabs/player/player.prefab 6 Position: (-1248.7, 2.24958, 692.708) Position on screen : (1645.64, 703.765) Distance: 195.098 (Player is sleeping)
2334278916096, BasePlayer assets/prefabs/player/player.prefab 6 Position: (-1025.26, 2.15851, 1068.61) Position on screen : (0, 0) Distance: 302.344 (Player is sleeping)
2321684842496, BasePlayer assets/prefabs/player/player.prefab 6 Position: (-1157.9, -0.518829, 677.325) Position on screen : (1340.08, 707.056) Distance: 236.326 (Player is sleeping)

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
