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


Klassen:
Game (verwaltet Spuelfeld, Spieler, Gegener, Punkte, Leaderboard)
(Leaderboard )
Score
Player

Steuerung

(Board: Größe, Positionen)

GameObjects(Form, Farbe, Position){
    
    Figures(alles was sich bewegt){
        PacMan
        Ghosts
    }

    Item(alles was man einsammeln kann){
        Fruits
        Coins
    }    
}






Rollenverteilung
Thea? - Spiellogik & Spielfluss
- Spielfeld generieren und darstellen ##done
- zufällige Platzierung von unbetretbaren Feldern ##done 
- Pac-Man Bewegung und Steuerung über Tastatur
- Bewegung Geister



Helen? - Gegner KI & Speicherung
- Leaderboard: Einlesen, Speichern, Anzeigen
- Platzieren und Verwalten von Obst
- Scoring (Kollisionserkennung)



