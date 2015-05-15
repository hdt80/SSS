 Event name | Event ID | Args | Sender | Receiver 
------------|----------|------|--------|----------
Spawn enemy | 0 | 0 - Enemy type (int), 1 - # Spawning (int), 2 - Enemy HP (int) | Master Controller | Nav, Wep
Collision | 1 | 0 - What side we got hit (String) | Nav | Eng
We fire | 2 | 0 - Shot type (int), 1 - Our X (int), 2 - Out Y (int), 3 - Out Z (int) | Wep | Nav
Minigame done | 3 | 0 - What station (String), 1 - What was fixed/Reward (String) | Station | Server
Power change | 4 | 0 - Station ID (String), 1 - New power level (int) | Eng | Server, Nav, Wep
Enemy despawn | 5 | 0 - Enemy ID (int) | Nav | Wep
Change max power | 7 | 0 - Power cell (String), 1 - Relative power change (int) | Server | Eng
Ship movements | 8 | 0 - Ship ID (int), 1 - x (int), 2 - y (int), 3 - z (int) | Server | Nav, Wep
