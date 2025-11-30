#ifndef NPCS_H
#define NPCS_H

#include <string>
#include <memory>
#include <vector>


class NPCVisitor;

// Базовый класс для всех NPC
class NPC {
protected:
    std::string name;
    float x, y;

public:
    NPC(const std::string& name, float x, float y);
    virtual ~NPC() = default;
    
    virtual std::string getType() const = 0;
    virtual void accept(NPCVisitor& visitor) = 0;
    
    std::string getName() const;
    float getX() const;
    float getY() const;
    
    float distanceTo(const NPC& other) const;
    bool isInRange(const NPC& other, float range) const;
    
    virtual bool canAttack(const NPC& other) const = 0;
    virtual bool canBeAttackedBy(const NPC& other) const = 0;
};

// Конкретные классы NPC
class Orc : public NPC {
public:
    Orc(const std::string& name, float x, float y);
    std::string getType() const override;
    void accept(NPCVisitor& visitor) override;
    bool canAttack(const NPC& other) const override;
    bool canBeAttackedBy(const NPC& other) const override;
};

class Knight : public NPC {
public:
    Knight(const std::string& name, float x, float y);
    std::string getType() const override;
    void accept(NPCVisitor& visitor) override;
    bool canAttack(const NPC& other) const override;
    bool canBeAttackedBy(const NPC& other) const override;
};

class Bear : public NPC {
public:
    Bear(const std::string& name, float x, float y);
    std::string getType() const override;
    void accept(NPCVisitor& visitor) override;
    bool canAttack(const NPC& other) const override;
    bool canBeAttackedBy(const NPC& other) const override;
};

// Visitor для обработки NPC
class NPCVisitor {
public:
    virtual ~NPCVisitor() = default;
    virtual void visit(Orc& orc) = 0;
    virtual void visit(Knight& knight) = 0;
    virtual void visit(Bear& bear) = 0;
};

#endif
