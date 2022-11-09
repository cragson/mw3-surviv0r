# MW3 Surviv0r
An external cheat for the survival mode in Call of Duty Modern Warfare 3 (Steam), written in C++.

![](https://i.imgur.com/gd9hFj7.png)

As usual I reversed an old game and had quite some fun, which ended in me writing this cheat for MW3. The process of writing the cheat would be much more fun, if this cheat would be internal but as my framework osmium was designed for external cheats, I had to implement most features externally. This was and is a challenge for myself, especially as the cheat isn't as cpu efficient as I would wish it is. Also there are some bugs which still exist and needs to be fixed - let's see if I got any motivation in the future.
Please take these things into consideration before using the cheat, thank you.

## Does this cheat work for Plutonium/ whatever custom version?
I don't know. I reversed and wrote the cheat for the current version of MW3 from Steam. It will work there.

## Is this cheat VAC secure?
As this cheat uses osmium to read/write memory, there are no special measures implemented to prevent getting detected by VAC. So please use it only in the Solo mode for Survival mode or implement a bypass yourself.

## Where can I download the cheat?
You can clone the repository right here, make sure to use `git clone ... --recursive` because I use [osmium](https://github.com/cragson/mw3-surviv0r) as a submodule.

Also make sure to have a look at the installation guide from osmium for preparing the Visual Studio project the correct way: https://github.com/cragson/osmium#installation--setup and https://github.com/cragson/osmium#compilation

If I upload a binary in the future, I will add a download link here. 

## What features does the cheat have?
- Aimbot -> enable, fov
- Visuals -> Player ESP(box + healthbar + distance), Weapon ESP, Crosshair
- Other -> Godmode. Infinite Ammo, Increased Speed, Increased FoV, Decreased Gravity, Superjump, Weak Enemies, Teleport Enemies to Player

## How do I start the cheat the correct way?
- Start the game (in windowed mode)
- Wait until you are in the main screen
- Start the cheat
- Wait until a green box appears with "Not ingame"

![](https://i.imgur.com/vOmv2pY.png)

You can only open the menu ingame!

## How do I open the menu and use it?
Press INSERT to open/close the menu
You can navigate from the main menu into sub menus with TAB(open) and SHIFT(close)
Also you can use the arrow keys to go up or down in the menu
To enable/disable/increase/decrease use the left and right arrow keys

## How do I save settings?
Currently there is no feature for this implemented, so you need to reconfigure the cheat on every restart

## Here is a quick video preview of the cheat (v1.4):  
[![](https://img.youtube.com/vi/tspD0qbgIf8/0.jpg)](https://www.youtube.com/watch?v=tspD0qbgIf8)

## Also here are some screenshots of the menu:

![](https://i.imgur.com/47Gpogb.png)
![](https://i.imgur.com/hsKCi4G.png)
![](https://i.imgur.com/5SS9xcN.png)
![](https://i.imgur.com/N8MJn8f.png)

## Known issues (d06545f0b51f895c65a9775d8a77e92b1af59fcf)
- Increased CPU usage by using Aimbot, Weak Enemies, Player ESP
- int/float values can be negative in the menu, which will cause undefined behaviour
- Aimbot may not be as accurate as expected because the Aimpoint for e.g. dogs or enemies in last stand is not as correct as it should be
- Overlay won't intitialize properly if the cheat is started before the game
- Some features still not use the entity_manager, e.g. (Weak Enemies, Teleport Enemies, Aimbot). Need to think of a efficient and fast way to implement the filtering multi-threaded.

If you need some changes in the cheat: Clone the repo, change the source yourself and compile it. Feel free to open a pull request - I would really appreciate that! 
Also I need to thank [@King-OrgY](https://www.unknowncheats.me/forum/members/149706.html) for his amazing work he has done in the past, some posts from him really helped me in understanding the engine better.

If you encounter any problems during the installation & compilation, make sure to open an issue - I will do my best to assist you.
