# Pacman
Implementation of a Pacman Game in C++


1. Die Spielfläche besteht aus einem Raster in dem sich Pac Man und die vier Gespenster bewegen.  

2. Die Spielfläche ist begrenzt. 

3. Die Spielfläche kann Rasterpunkte enthalten, die von Pac Man und den Gespenstern nicht betreten werden können. Entsprechende Rasterpunkte sollen als solche erkennbar sein. 

4. Alle Rasterpunkte, die betreten werden können, enthalten eine Münze. Betritt Pac Man einen Rasterpunkt das erste Mal, sammelt er die Münze ein. Die Münze verschwindet und der Spieler bekommt 10 Punkte. 

5. Auf den betretbaren Rasterpunkten soll zufällig Obst erscheinen. Wenn Pac Man einen Rasterpunkt mit Obst betritt und das Obst frisst bekommt der Spieler 100 Punkte. 

6. Wenn sich Pac Man und ein Gespenst in einem Rasterpunkt treffen wird Pac Man gefressen und das Spiel ist vorbei.

7. Wenn alle Münzen eingesammelt sind ist das Spiel vorbei.  

8. Pac Man wird durch den Spieler über die Tastatur gesteuert. Die Gespenster bewegen sich selbständig. 

9. Es gibt ein Leaderboard in dem nach jedem Spiel der Spieler mit Punktestand eingetragen wird. Das Leaderboard wird auf der Festplatte gespeichert und beim Start des Spiels sowie nach jedem Spiel angezeigt. 


TODO
Controls Menü
highscore speicherung
Option to play with both awsd and arrow keys
UML Diagramm updaten

Optional: 
Level switch screen
Restore Health from level 4 onwards when eating a fruit 

Wer hat was gemacht?
Thea:
GameObjects (Gameobjects, Figuren, Pacman, Ghosts, Fruits, Lives)
Controls (check_collision, controller, ghost_controller, player_controller)
Board (board, check_position, level)
utils



Helen:
GameObjects (Points)
Display (scoreBoard, start_screen, UserManager)
Soundsystem
UML Diagramm







