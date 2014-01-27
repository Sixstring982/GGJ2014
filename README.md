GGJ2014
=======
CALL OF THE OCEAN "FORE": Underwater Warfare
=======

Global Game Jam 2014 pseudo-text-based submarine battles!

How To Play
-----------

You're the capatain of an aquadic warcraft and a more or less capable crew. Each operation is different but you seem to always finding yourself surrounded by enemy vessles. 

Your goal is to get your ship and crew to safety. You do this by blowing up the things that are shooting at you. To destroy an enemy ship you must fire a torpedo while you are aimed at the enemy ship. Below is an example of the commands you might use to shoot a torpedo at an enemy.

        sonar list contacts
        helm list heading
        
It takes a tick for each of these commands to complete. Again, your crew isn't necessarily great at what they do. Let's say you have 1 contact at 180 and your heading is 090. 

        helm rotate 180
        weapons prep
        
Your ship will turn at a rate of 15 degrees per tick so make sure to turn the right direction (clockwise is implicit but counterclocwise needs to be specified). Weapons prep takes 1 tick so after that's done (and while we're turning) we can finish setting up a torpedo.

        weapons upgrade booster

You have three ways you can upgrade a prepped torpedo: booster, warhead, and homing. The booster makes the torpedo reach its target quicker, the warhead increases the chance of destroying a target and homing lets you hit a target while still being +_ 15 degrees off its heading. Upgrades take 5 ticks and are not necessary to fire a torpedo.

        weapons load
        
After upgrades you can load the torpedo into the bay. Once a torpedo is finished loading it is ready to be fired. You do not have to wait until firing a torpedo before prepping another, you can prep the next one as soon as the previous one is loaded.

        weapons fire
        
Finally you can fire your torpedo. You probably want to be pointed at the target before firing otherwis you probably won't hit anything. Torpedos travel at 20 meters per tick so if they're far away you're in for a bit of a wait. Meanwhile, you can check your its progress with "weapons status". You can also start the process over if there was another contact encountered. Once the torpedo reaches its destination distance you will be notified if your attack was sucessful or a failure. 

If you manage to destoy all enemy vessles in the vicinity you're in for a treat. Subsequent levels are obtained by clearing enemies and there are a total of four. Each tick in level 1 (where the game starts) completes in 5 seconds. For level 2 the ticks complete in 3 seconds, level 3 in 2 seconds and the last level in 1 second. The game ends when the ship must be abandoned due to fatal damage or if all the enemies in level 4 are destroyed. Good luck.


INSTALLATION
------------

*NIX:

    #cd GGJ14
    #make
    #./build/sub

ANYTHING other than *NIX:

    to do: get linux

SYSTEM REQUIREMENTS
--------------------
Minimum system requirements: 

        10 Mhz CPU 
        4K RAM 
        2 MB free hard drive space 
        800x600 display or printer attached to std output 
        Keyboard
