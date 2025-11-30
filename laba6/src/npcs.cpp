#include "../include/npcs.h"
#include <cmath>
#include <iostream>

// Реализация базового класса NPC
NPC::NPC(const std::string& name, float x, float y) 
    : name(name), x(x), y(y) {}

std::string NPC::getName() const { return name; }
float NPC::getX() const { return x; }
float NPC::getY() const { return y; }

float NPC::distanceTo(const NPC& other) const {
    float dx = x - other.x;
    float dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

bool NPC::isInRange(const NPC& other, float range) const {
    return distanceTo(other) <= range;
}

// Реализация Orc
Orc::Orc(const std::string& name, float x, float y) : NPC(name, x, y) {}

std::string Orc::getType() const { return "Orc"; }

void Orc::accept(NPCVisitor& visitor) {
    visitor.visit(*this);
}

bool Orc::canAttack(const NPC& other) const {
    // Орки атакуют только медведей
    return other.getType() == "Bear";
}

bool Orc::canBeAttackedBy(const NPC& other) const {
    // Орков могут атаковать только рыцари
    return other.getType() == "Knight";
}

// Реализация Knight
Knight::Knight(const std::string& name, float x, float y) : NPC(name, x, y) {}

std::string Knight::getType() const { return "Knight"; }

void Knight::accept(NPCVisitor& visitor) {
    visitor.visit(*this);
}

bool Knight::canAttack(const NPC& other) const {
    // Рыцари атакуют только орков
    return other.getType() == "Orc";
}

bool Knight::canBeAttackedBy(const NPC& other) const {
    // Рыцарей могут атаковать только медведи
    return other.getType() == "Bear";
}

// Реализация Bear
Bear::Bear(const std::string& name, float x, float y) : NPC(name, x, y) {}

std::string Bear::getType() const { return "Bear"; }

void Bear::accept(NPCVisitor& visitor) {
    visitor.visit(*this);
}

bool Bear::canAttack(const NPC& other) const {
    // Медведи атакуют только рыцарей
    return other.getType() == "Knight";
}

bool Bear::canBeAttackedBy(const NPC& other) const {
    // Медведей могут атаковать только орки
    return other.getType() == "Orc";
}
