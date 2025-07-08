

多武器战斗系统 (MultiWeaponCombatProject)

视频demo链接：https://www.bilibili.com/video/BV1LmG7ztEBx/?spm_id_from=333.1387.homepage.video_card.click&vd_source=c096d37a6e7624ca39a2afef5c3f64d2

一个基于C++实现的回合制战斗游戏，具有武器切换派生动作、属性克制系统和背包管理功能


游戏概述
这是一个回合制战斗游戏，玩家需要使用不同武器对抗三种类型的敌人。游戏的核心机制包括武器切换产生的派生伤害、属性克制系统以及动态的背包管理系统。

核心技术
•	面向对象设计: 使用C++类封装游戏逻辑，清晰的继承结构
•	多线程编程: 主线程负责计时，游戏线程处理战斗逻辑
•	Windows API: 实现背包选择的GUI界面
•	STL容器: 使用vector、map等管理游戏数据
•	设计模式: 策略模式处理不同武器类型，观察者模式管理游戏状态

项目亮点

1. 武器派生动作系统
   不同武器间的切换会产生额外伤害，增加了策略深度：
   cpp
   // 派生动作配置 - 武器切换伤害加成
   ds.add("能量剑", "重锤", 0.38);    // 能量剑→重锤: +38%伤害
   ds.add("激光枪", "重锤", 0.5);     // 激光枪→重锤: +50%伤害
   ds.add("重锤", "能量剑", 0.25);    // 重锤→能量剑: +25%伤害

// 派生伤害计算
if (change == 1) {
    int adda = round(a * addatt);
    a = a + adda;  // 基础伤害 + 派生伤害
}

2. 属性克制系统
   每种武器对特定敌人类型有额外伤害：
   cpp
   // 武器克制关系
   if (currentEnemy->getType().compare("外星感染生物") == 0 && 
    currentWeapon->getName().compare("能量剑") == 0) {
    a += currentWeapon->getCompatibilityBonus();  // +100伤害
   }
   else if (currentEnemy->getType().compare("变异人类") == 0 && 
         currentWeapon->getName().compare("重锤") == 0) {
    a += currentWeapon->getCompatibilityBonus();  // +300伤害
   }
   else if (currentEnemy->getType().compare("机械生命体") == 0 && 
         currentWeapon->getName().compare("激光枪") == 0) {
    a += currentWeapon->getCompatibilityBonus();  // +500伤害
   }

3. 动态背包系统
   使用Windows API实现可视化道具选择：
   cpp
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

// GUI道具选择窗口
void createWindow(std::map<std::string, int>& bag) {
    // 根据背包内容动态创建按钮
    for (auto& item : bag) {
        std::string text = item.first + "x" + to_string(item.second);
        CreateWindow("BUTTON", text.c_str(), WS_VISIBLE | WS_CHILD, 
                    x, 10, 120, 30, hwnd, (HMENU)itemID, NULL, NULL);
    }
}


游戏数据配置
玩家属性
cpp
Player(int initialHealth) : health(100), maxhealth(100), grade(1) {}

| 敌人类型     | 血量 | 攻击力 | 经验值 |
| ------------ | ---- | ------ | ------ |
| 外星感染生物 | 400  | 10     | 50     |
| 变异人类     | 800  | 20     | 75     |
| 机械生命体   | 1000 | 30     | 100    |


| 武器名称 | 基础伤害 | 冷却时间 | 克制敌人     | 额外伤害 |
| -------- | -------- | -------- | ------------ | -------- |
| 能量剑   | 50       | 10秒     | 外星感染生物 | +100     |
| 重锤     | 20       | 5秒      | 变异人类     | +300     |
| 激光枪   | 80       | 20秒     | 机械生命体   | +500     |

// 武器初始化
Weapon w1("能量剑", 50, 10);
w1.setCompatibilityBonus(100);
w1.setFeature("快速攻击武器");

Weapon w2("重锤", 20, 5);
w2.setCompatibilityBonus(300);
w2.setFeature("重击型武器");

Weapon w3("激光枪", 80, 20);
w3.setCompatibilityBonus(500);
w3.setFeature("穿透性武器");





| 道具名称                                  | 效果        | 获取方式         |
| ----------------------------------------- | ----------- | ---------------- |
| 能量盾                                    | 抵挡70%伤害 | 击杀怪物随机掉落 |
| 药水                                      | 攻击力+20   | 击杀怪物随机掉落 |
| 医药箱                                    | 恢复满血    | 击杀怪物随机掉落 |
| // 道具效果实现                           |             |                  |
| void Player::useProp(std::string& name) { |             |                  |

    if (name.compare("EnergyShield") == 0) {
        shield = 100;  // 护盾值
    }
    else if (name.compare("potion") == 0) {
        stackeddamage = 20;  // 攻击力加成
    }
    else if (name.compare("Medical") == 0) {
        health = maxhealth;  // 恢复满血
    }

}



武器派生动作表

| 当前武器 → 切换武器 | 派生伤害加成 |
| ------------------- | ------------ |
| 能量剑 → 重锤       | +38%         |
| 能量剑 → 激光枪     | +38%         |
| 重锤 → 能量剑       | +25%         |
| 重锤 → 激光枪       | +25%         |
| 激光枪 → 重锤       | +50%         |
| 激光枪 → 能量剑     | +50%         |

架构设计
cpp// 核心类结构
class GameController {
    Player* currentPlayer;
    Enemy* currentEnemy;
    Weapon* currentWeapon;
    DerivativeSystem ds;  // 派生动作系统
    

    string playerAttack(Player& pl, Enemy& target);
    int executePlayerAction();
    int updateGameState();

};

class Player {
    std::vector<Weapon> weaponInventory;  // 武器库
    std::map<std::string, int> bag;       // 背包系统
    

    int attack();
    int takeDamage(int amount);
    void changeWeapon(const std::string& weaponName);

};

class DerivativeSystem {
    std::map<std::pair<std::string, std::string>, double> derivativeActionMapping;
    

    double performDerivativeAction(std::string from, std::string to);

};




创新点
派生动作机制: 武器切换不仅仅是数值变化，还能产生战术收益
平衡性设计: 低伤害武器通过高克制伤害和低冷却保持竞争力
多线程架构: 游戏逻辑与计时系统分离，确保流畅体验
混合UI: 控制台+Windows GUI的组合界面


游戏流程
1.初始化: 玩家100血量，装备能量剑
2.战斗循环:
选择武器（可触发派生动作）
攻击敌人（可触发属性克制）
敌人反击
重复直到一方血量归零
3.奖励阶段: 获得经验值、道具掉落
4.进程: 升级提升血量上限，面对更强敌人

技术特色
内存管理: 合理使用智能指针和RAII原则
异常安全: 完善的边界检查和错误处理
代码复用: 模板和泛型编程提高代码质量
性能优化: STL容器的高效使用
