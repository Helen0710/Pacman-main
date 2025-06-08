#include "instructions.h"
#include "raylib.h"
#include <algorithm>

Instructions::Instructions(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight) {}

void Instructions::draw() {
    ClearBackground(BLACK);

    // Titel: PAC-MAN (zentriert)
    const char* title = "PAC-MAN";
    int titleFontSize = 50;
    int titleWidth = MeasureText(title, titleFontSize);
    DrawText(title, (screenWidth - titleWidth) / 2, 40, titleFontSize, YELLOW);

    // Untertitel: Spielanleitung
    const char* subtitle = "SPIELANLEITUNG";
    int subtitleFontSize = 30;
    int subtitleWidth = MeasureText(subtitle, subtitleFontSize);
    DrawText(subtitle, (screenWidth - subtitleWidth) / 2, 100, subtitleFontSize, YELLOW);

    // Spielanleitungstext
    const int fontSize = 20;
    const int marginX = 30;
    int posY = 160;

    const char* lines[] = {
        "Herzlichen Wilkommen bei Pacman.", 
        "Ein Labyrinthspiel mit dem Ziel, so viele Puntke wie möglich einzusammeln",
        "Das Problem? Die Geister! Sie werden dich jagen.", 
        "Mit jedem Level das du bewältigst, in dem du alle Punkte ", 
        "auf dem Spielfeld eingesammlt hast, werden die Geister schneller und schneller", 
        "Um ihnen zu entkommen bewegst du Pacman mit den Pfeiltasten über das Spielfeld.",
        "Am Anfang eines jeden Spiels musst du deinen Namen eingeben.",
        "Dieser wird dann in der Highscore-Liste gespeichert.",
        "Für das einsammeln von Punkten bekommst du 10 Punkte.", 
        "Nach einer bestimmten Zeit werden immer wieder Früchte autauchen.", 
        "Für das einsammeln von Früchten bekommst du je nach Frucht zwischen",
        "100 und 5000 Punkten. Umso mehr Punkte du hast umso höher stehst du im Ranking.", 
        "Zu deinem Mitspielern.", 
        "Den Highscore kannst du dir unter dem Menüpunkt Controls ansehen.",
        

    };

    for (const char* line : lines) {
        DrawText(line, marginX, posY, fontSize, WHITE);
        posY += 30;
    }

    // Zurück-Hinweis
    const char* backHint = "Drücke ENTER, um zum Hauptmenü zurückzukehren.";
    int hintWidth = MeasureText(backHint, fontSize);
    DrawText(backHint, (screenWidth - hintWidth) / 2, screenHeight - 50, fontSize, YELLOW);
}

void Instructions::update(bool& backToMenu) {
    if (IsKeyPressed(KEY_ENTER)) {
        backToMenu = true;
    }
}
