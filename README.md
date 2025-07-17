# 多武器战斗系统 (MultiWeaponCombatProject)

视频演示链接：https://www.bilibili.com/video/BV1LmG7ztEBx/?spm_id_from=333.1387.homepage.video_card.click&vd_source=c096d37a6e7624ca39a2afef5c3f64d2

一个基于C++实现的回合制战斗游戏，具有武器切换派生动作、属性克制系统、武器冷却机制和背包管理功能。

## 游戏概述

这是一个回合制战斗游戏，玩家需要使用不同武器对抗三种类型的敌人。游戏的核心机制包括武器切换产生的派生伤害、属性克制系统、武器冷却时间管理以及动态的背包管理系统。

## 核心技术特色

- **面向对象设计**: 使用C++类封装游戏逻辑，清晰的继承结构
- **多线程编程**: 主线程负责计时，游戏线程处理战斗逻辑
- **Windows API**: 实现背包选择的GUI界面
- **STL容器**: 使用vector、map等管理游戏数据
- **设计模式**: 策略模式处理不同武器类型，观察者模式管理游戏状态

## 项目核心亮点

### 1. 武器派生动作系统
不同武器间的切换会产生额外伤害，增加了策略深度：

```cpp
// 派生动作配置 - 武器切换伤害加成
ds.add("Energy Sword", "Heavy Hammer", 0.38);    // 能量剑→重锤: +38%伤害
ds.add("Laser Gun", "Heavy Hammer", 0.5);        // 激光枪→重锤: +50%伤害
ds.add("Heavy Hammer", "Energy Sword", 0.25);    // 重锤→能量剑: +25%伤害

// 派生伤害计算
if (change == 1) {
    int adda = round(a * addatt);
    a = a + adda;  // 基础伤害 + 派生伤害
}
```

### 2. 武器冷却时间系统
每种武器都有独立的冷却时间，增加了战术选择的复杂性：

```cpp
class Weapon {
    int cooldownTime;    // 冷却时间(秒)
    int lastUseTime;     // 上次使用时间
    
    int coolOk(int currentTime) {
        int remaining = cooldownTime - (currentTime - lastUseTime);
        return remaining > 0 ? remaining : 0;
    }
};
```

### 3. 属性克制系统
每种武器对特定敌人类型有额外伤害：

```cpp
// 武器克制关系
if (currentEnemy->getType().compare("Alien Infected") == 0 && 
    currentWeapon->getName().compare("Energy Sword") == 0) {
    a += currentWeapon->getCompatibilityBonus();  // +100伤害
}
else if (currentEnemy->getType().compare("Mutant Human") == 0 && 
         currentWeapon->getName().compare("Heavy Hammer") == 0) {
    a += currentWeapon->getCompatibilityBonus();  // +300伤害
}
```

### 4. 动态背包系统
使用Windows API实现可视化道具选择：

```cpp
// 背包物品管理
class Player {
    std::map<std::string, int> bag;  // 道具名称→数量映射
    
    void joinBag(std::string name) {
        auto it = bag.find(name);
        if (it != bag.end()) {
            it->second++;  // 已有道具数量+1
        } else {
            bag[name] = 1;  // 新道具
        }
    }
};
```

## 游戏数据配置

### 武器属性表

| 武器名称 | 基础伤害 | 冷却时间 | 克制敌人     | 额外伤害 | 特性         |
|----------|----------|----------|--------------|----------|--------------|
| 能量剑   | 50       | 10秒     | 外星感染生物 | +100     | 快速攻击武器 |
| 重锤     | 20       | 5秒      | 变异人类     | +300     | 重击型武器   |
| 激光枪   | 80       | 20秒     | 机械生命体   | +500     | 穿透性武器   |

### 敌人属性表

| 敌人类型     | 血量 | 攻击力 | 经验值 |
|--------------|------|--------|--------|
| 外星感染生物 | 400  | 10     | 50     |
| 变异人类     | 800  | 20     | 75     |
| 机械生命体   | 1000 | 30     | 100    |

### 武器派生动作表

| 当前武器 → 切换武器 | 派生伤害加成 |
|---------------------|--------------|
| 能量剑 → 重锤       | +38%         |
| 能量剑 → 激光枪     | +38%         |
| 重锤 → 能量剑       | +25%         |
| 重锤 → 激光枪       | +25%         |
| 激光枪 → 重锤       | +50%         |
| 激光枪 → 能量剑     | +50%         |

### 道具系统

| 道具名称 | 效果        | 获取方式         |
|----------|-------------|------------------|
| 能量盾   | 抵挡70%伤害 | 击杀怪物随机掉落 |
| 药水     | 攻击力+20   | 击杀怪物随机掉落 |
| 医药箱   | 恢复满血    | 击杀怪物随机掉落 |

## 架构设计

```cpp
// 核心类结构
class GameController {
    Player* currentPlayer;
    Enemy* currentEnemy;
    Weapon* currentWeapon;
    DerivativeSystem ds;  // 派生动作系统
    int nowTime;          // 当前游戏时间
    
    string playerAttack(Player& pl, Enemy& target);
    int executePlayerAction();
    int updateGameState();
};

class Player {
    std::vector<Weapon> weaponInventory;  // 武器库
    std::map<std::string, int> bag;       // 背包系统
    int health, maxhealth, grade;         // 血量、最大血量、等级
    
    int attack();
    int takeDamage(int amount);
    void changeWeapon(const std::string& weaponName);
};

class DerivativeSystem {
    std::map<std::pair<std::string, std::string>, double> derivativeActionMapping;
    
    double performDerivativeAction(std::string from, std::string to);
};
```

## 创新特点

1. **派生动作机制**: 武器切换不仅仅是数值变化，还能产生战术收益
2. **平衡性设计**: 低伤害武器通过高克制伤害和低冷却保持竞争力
3. **多线程架构**: 游戏逻辑与计时系统分离，确保流畅体验
4. **混合UI**: 控制台+Windows GUI的组合界面
5. **冷却管理**: 武器使用时机的策略性选择

## 游戏流程

1. **初始化**: 玩家100血量，装备能量剑
2. **战斗循环**:
   - 选择武器（注意冷却时间，可触发派生动作）
   - 攻击敌人（可触发属性克制）
   - 敌人反击
   - 重复直到一方血量归零
3. **奖励阶段**: 获得经验值、道具掉落
4. **进程**: 升级提升血量上限，面对更强敌人

---

# MultiWeapon Combat System

Video Demo: https://www.bilibili.com/video/BV1LmG7ztEBx/?spm_id_from=333.1387.homepage.video_card.click&vd_source=c096d37a6e7624ca39a2afef5c3f64d2

A turn-based combat game implemented in C++ featuring weapon switching derivative actions, attribute restraint system, weapon cooldown mechanics, and inventory management.

## Game Overview

This is a turn-based combat game where players use different weapons to fight against three types of enemies. The core mechanics include derivative damage from weapon switching, attribute restraint system, weapon cooldown management, and dynamic inventory system.

## Core Technical Features

- **Object-Oriented Design**: Clean inheritance structure using C++ classes
- **Multithreading**: Main thread handles timing, game thread processes combat logic
- **Windows API**: GUI interface for inventory selection
- **STL Containers**: Efficient data management using vector, map, etc.
- **Design Patterns**: Strategy pattern for weapon types, Observer pattern for game state

## Key Project Highlights

### 1. Weapon Derivative Action System
Weapon switching generates additional damage, adding strategic depth:

```cpp
// Derivative action configuration - weapon switch damage bonus
ds.add("Energy Sword", "Heavy Hammer", 0.38);    // Energy Sword→Heavy Hammer: +38% damage
ds.add("Laser Gun", "Heavy Hammer", 0.5);        // Laser Gun→Heavy Hammer: +50% damage
ds.add("Heavy Hammer", "Energy Sword", 0.25);    // Heavy Hammer→Energy Sword: +25% damage

// Derivative damage calculation
if (change == 1) {
    int adda = round(a * addatt);
    a = a + adda;  // Base damage + derivative damage
}
```

### 2. Weapon Cooldown System
Each weapon has independent cooldown time, adding tactical complexity:

```cpp
class Weapon {
    int cooldownTime;    // Cooldown time (seconds)
    int lastUseTime;     // Last use time
    
    int coolOk(int currentTime) {
        int remaining = cooldownTime - (currentTime - lastUseTime);
        return remaining > 0 ? remaining : 0;
    }
};
```

### 3. Attribute Restraint System
Each weapon deals extra damage to specific enemy types:

```cpp
// Weapon restraint relationships
if (currentEnemy->getType().compare("Alien Infected") == 0 && 
    currentWeapon->getName().compare("Energy Sword") == 0) {
    a += currentWeapon->getCompatibilityBonus();  // +100 damage
}
else if (currentEnemy->getType().compare("Mutant Human") == 0 && 
         currentWeapon->getName().compare("Heavy Hammer") == 0) {
    a += currentWeapon->getCompatibilityBonus();  // +300 damage
}
```

### 4. Dynamic Inventory System
Visual item selection using Windows API:

```cpp
// Inventory management
class Player {
    std::map<std::string, int> bag;  // Item name → quantity mapping
    
    void joinBag(std::string name) {
        auto it = bag.find(name);
        if (it != bag.end()) {
            it->second++;  // Increment existing item
        } else {
            bag[name] = 1;  // New item
        }
    }
};
```

## Game Data Configuration

### Weapon Attributes

| Weapon Name  | Base Damage | Cooldown | Effective Against | Bonus Damage | Feature           |
|--------------|-------------|----------|-------------------|--------------|-------------------|
| Energy Sword | 50          | 10s      | Alien Infected    | +100         | Fast Attack       |
| Heavy Hammer | 20          | 5s       | Mutant Human      | +300         | Heavy Strike      |
| Laser Gun    | 80          | 20s      | Mechanical Life   | +500         | Piercing Weapon   |

### Enemy Attributes

| Enemy Type      | HP   | Attack | EXP |
|-----------------|------|--------|-----|
| Alien Infected  | 400  | 10     | 50  |
| Mutant Human    | 800  | 20     | 75  |
| Mechanical Life | 1000 | 30     | 100 |

### Weapon Derivative Actions

| Current Weapon → Switch To | Derivative Damage Bonus |
|----------------------------|-------------------------|
| Energy Sword → Heavy Hammer | +38%                   |
| Energy Sword → Laser Gun   | +38%                   |
| Heavy Hammer → Energy Sword | +25%                   |
| Heavy Hammer → Laser Gun   | +25%                   |
| Laser Gun → Heavy Hammer   | +50%                   |
| Laser Gun → Energy Sword   | +50%                   |

### Item System

| Item Name    | Effect           | Acquisition Method    |
|--------------|------------------|-----------------------|
| Energy Shield| Blocks 70% damage| Random monster drop   |
| Potion       | Attack +20       | Random monster drop   |
| Medical Kit  | Restore full HP  | Random monster drop   |

## Architecture Design

```cpp
// Core class structure
class GameController {
    Player* currentPlayer;
    Enemy* currentEnemy;
    Weapon* currentWeapon;
    DerivativeSystem ds;  // Derivative action system
    int nowTime;          // Current game time
    
    string playerAttack(Player& pl, Enemy& target);
    int executePlayerAction();
    int updateGameState();
};

class Player {
    std::vector<Weapon> weaponInventory;  // Weapon inventory
    std::map<std::string, int> bag;       // Inventory system
    int health, maxhealth, grade;         // HP, max HP, level
    
    int attack();
    int takeDamage(int amount);
    void changeWeapon(const std::string& weaponName);
};

class DerivativeSystem {
    std::map<std::pair<std::string, std::string>, double> derivativeActionMapping;
    
    double performDerivativeAction(std::string from, std::string to);
};
```

## Innovation Features

1. **Derivative Action Mechanism**: Weapon switching provides tactical benefits beyond stat changes
2. **Balance Design**: Low-damage weapons remain competitive through high restraint damage and low cooldown
3. **Multithreaded Architecture**: Game logic separated from timing system for smooth experience
4. **Hybrid UI**: Console + Windows GUI combination interface
5. **Cooldown Management**: Strategic timing choices for weapon usage

## Game Flow

1. **Initialization**: Player starts with 100 HP, equipped with Energy Sword
2. **Combat Loop**:
   - Select weapon (considering cooldown time, may trigger derivative actions)
   - Attack enemy (may trigger attribute restraint)
   - Enemy counterattack
   - Repeat until one side reaches zero HP
3. **Reward Phase**: Gain experience points and item drops
4. **Progression**: Level up increases max HP, face stronger enemies

## How to Run

1. Clone the repository
2. Compile with Visual Studio (C++17 or later)
3. Run the executable
4. Use keyboard controls:
   - `1`, `2`, `3`: Switch weapons
   - `Space`: Attack
   - `4`: Use items
   - `5`: Skip turn
   - `ESC`: Exit game
