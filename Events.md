Event name       | Event ID | Args

Spawn enemy      | 0 | 0 - Enemy type (int), 1 - # Spawning (int), 2 - Enemy HP (int)

Collision        | 1 | 0 - What side we got hit (String) [Top, bottom, front, back, left, right]

We fire          | 2 | 0 - Shot type (int) [Bullet, missle, etc.], 1 - Our X (int), 2 - Out Y (int), 3 - Out Z (int)

Minigame done    | 3 | 0 - What station (String), 1 - What was fixed/Reward (String)

Power change     | 4 | 0 - Station ID (String), 1 - New power level (int)

Enemy despawn    | 5 | 0 - Enemy ID (int)

Enemy fires      | 6 | 0 - Enemy ID (int), 1 - Shot type (int), 2 - X (int), 3 - Y (int), 4 - Z (int)

Change max power | 7 | 0 - Power cell (String), 1 - Relative power change (int)
