tankwars
========

OpenGL Tank Game for a CPSC 314 Project
Team: Jonathan Clark & Theo Ng

Part 1:
What: We created a tank vs. turret galaga type game. The main features include:
-3d models with textures
-3d quaternion camera
-smooth keyboard movement (tank)
-skybox
-lighting
-heightmap (unfortunately unfinished, so just flat)
-on screen controls
-Particles
-Bounding Box Collision (red boxes)
-Turret AI (includes vector math to compute how to attack)
-FPS Counter

How: Most of the features implemented were from tutorials either from NeHe at gamedev.net or swiftless, along with a lot of help from stackoverflow. 
The architecture of the was created by us.  There is an object manager and abstracted gameobject to control rendering and updating game objects.

HowTo:
Controls:
W, S, A, D + Mouse for moving camera.
Spacebar: shoot bullets
Up, Left, Down, Right: move tank
Esc: quit
Tab: wireframe mode

The goal is to kill the turrets before they kill you!  Crates are radioactive so don't touch them or they will hurt you!

Sources:
nehe.gamedev.net
swiftless.com

