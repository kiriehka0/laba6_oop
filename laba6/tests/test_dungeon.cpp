#include <gtest/gtest.h>
#include "../include/dungeon_editor.h"
#include <fstream>
#include <filesystem>

class DungeonEditorTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::ofstream file("log.txt", std::ios::trunc);
    }
};

TEST_F(DungeonEditorTest, AddNPCValid) {
    DungeonEditor editor;
    EXPECT_TRUE(editor.addNPC("Orc", "TestOrc", 100, 100));
    EXPECT_TRUE(editor.addNPC("Knight", "TestKnight", 200, 200));
    EXPECT_TRUE(editor.addNPC("Bear", "TestBear", 300, 300));
    EXPECT_EQ(editor.getNPCCount(), 3);
}

TEST_F(DungeonEditorTest, AddNPCInvalidCoordinates) {
    DungeonEditor editor;
    EXPECT_FALSE(editor.addNPC("Orc", "TestOrc", 600, 100)); 
    EXPECT_FALSE(editor.addNPC("Knight", "TestKnight", 100, -50)); 
    EXPECT_EQ(editor.getNPCCount(), 0);
}

TEST_F(DungeonEditorTest, AddNPCInvalidType) {
    DungeonEditor editor;
    EXPECT_FALSE(editor.addNPC("Dragon", "TestDragon", 100, 100));
    EXPECT_EQ(editor.getNPCCount(), 0);
}

TEST_F(DungeonEditorTest, SaveAndLoad) {
    DungeonEditor editor;
    editor.addNPC("Orc", "Grommash", 100, 100);
    editor.addNPC("Knight", "Arthur", 200, 200);
    
    EXPECT_TRUE(editor.saveToFile("test_save.txt"));
    
    DungeonEditor editor2;
    EXPECT_TRUE(editor2.loadFromFile("test_save.txt"));
    EXPECT_EQ(editor2.getNPCCount(), 2);
    
    std::remove("test_save.txt");
}

TEST_F(DungeonEditorTest, BattleRules) {
    auto orc = std::make_unique<Orc>("TestOrc", 100, 100);
    auto bear = std::make_unique<Bear>("TestBear", 101, 101);
    
    EXPECT_TRUE(orc->canAttack(*bear));
    EXPECT_FALSE(bear->canAttack(*orc));
    auto knight = std::make_unique<Knight>("TestKnight", 102, 102);
    EXPECT_TRUE(bear->canAttack(*knight));
    EXPECT_FALSE(knight->canAttack(*bear));
    EXPECT_TRUE(knight->canAttack(*orc));
    EXPECT_FALSE(orc->canAttack(*knight));
}

TEST_F(DungeonEditorTest, BattleRange) {
    DungeonEditor editor;
    editor.addNPC("Orc", "Orc1", 100, 100);
    editor.addNPC("Bear", "Bear1", 400, 400); 
    
    EXPECT_EQ(editor.getNPCCount(), 2);
    editor.startBattle(50);
    EXPECT_EQ(editor.getNPCCount(), 2);
}

TEST_F(DungeonEditorTest, BattleSameType) {
    DungeonEditor editor;
    editor.addNPC("Orc", "Orc1", 100, 100);
    editor.addNPC("Orc", "Orc2", 101, 101);
    
    EXPECT_EQ(editor.getNPCCount(), 2);
    
    editor.startBattle(50);
    
    EXPECT_EQ(editor.getNPCCount(), 2);
}

TEST_F(DungeonEditorTest, LogFileCreated) {
    DungeonEditor editor;
    editor.addNPC("Orc", "Orc1", 100, 100);
    editor.addNPC("Bear", "Bear1", 101, 101);
    
    editor.startBattle(50);
    
    std::ifstream logFile("log.txt");
    EXPECT_TRUE(logFile.is_open());
    
    std::string firstLine;
    std::getline(logFile, firstLine);
    EXPECT_FALSE(firstLine.empty());
}

TEST_F(DungeonEditorTest, DistanceCalculation) {
    auto npc1 = std::make_unique<Orc>("Test1", 0, 0);
    auto npc2 = std::make_unique<Orc>("Test2", 3, 4);
    
    EXPECT_FLOAT_EQ(npc1->distanceTo(*npc2), 5.0f);
}

TEST_F(DungeonEditorTest, MultipleBattles) {
    DungeonEditor editor;
    
    editor.addNPC("Orc", "Orc1", 100, 100);
    editor.addNPC("Bear", "Bear1", 101, 101);
    editor.addNPC("Knight", "Knight1", 102, 102);
    
    EXPECT_EQ(editor.getNPCCount(), 3);
    
    editor.startBattle(50);
    
    EXPECT_LE(editor.getNPCCount(), 2);
}
