#include "../include/dungeon_editor.h"
#include <iostream>

int main() {
    DungeonEditor editor;
    
    // Добавляем NPC
    editor.addNPC("Orc", "Grommash", 100, 100);
    editor.addNPC("Knight", "Arthur", 150, 150);
    editor.addNPC("Bear", "Baloo", 120, 120);
    editor.addNPC("Orc", "Thrall", 200, 200);
    editor.addNPC("Knight", "Lancelot", 50, 50);
    
    // Печатаем список
    std::cout << "Initial NPCs:" << std::endl;
    editor.printNPCs();
    
    // Сохраняем в файл
    editor.saveToFile("dungeon.txt");
    
    // Запускаем бой
    editor.startBattle(100);
    
    // Печатаем оставшихся NPC
    std::cout << "\nRemaining NPCs after battle:" << std::endl;
    editor.printNPCs();
    
    // Загружаем из файла
    DungeonEditor editor2;
    editor2.loadFromFile("dungeon.txt");
    std::cout << "\nLoaded NPCs:" << std::endl;
    editor2.printNPCs();
    
    return 0;
}
