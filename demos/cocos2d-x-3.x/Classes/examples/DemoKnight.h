﻿#ifndef DEMO_KNIGHT_H
#define DEMO_KNIGHT_H

#include "Demo.h"

class DemoKnight : public DemoBase
{
public:
    CREATE_FUNC(DemoKnight);
    DemoKnight();
    ~DemoKnight();
    virtual std::string title();
    virtual std::string subtitle();
    virtual void update(float dt) override;
    
private:
    dragonBones::DBCCArmature *_armature;
    dragonBones::DBCCArmature *_armArmature;
    
    bool _isLeft;
    bool _isRight;
    bool _isJump;
    int _moveDir;
    int _weaponIndex;
    float _speedX;
    float _speedY;
    
    bool _isAttacking;
    bool _isComboAttack;
    int _hitCount;
    
    std::vector<std::string> _weaponList;
    std::vector<int> _weaponLevelList;
    std::vector<cocos2d::Node*> _arrowList;
    
protected:
    virtual void demoInit() override;
    virtual void addInteraction() override;
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    cocos2d::EventListenerKeyboard *_keyboardListener;
    virtual void keyPressHandler(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    virtual void keyReleaseHandler(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
#endif
    inline std::string getWeaponName(const std::string &name, int level)
    {
        char weapon[512];
        sprintf(weapon, "knightFolder/%s_%d", name.c_str(), level);
        return std::string(weapon);
    }

    void jump();    
    void move(int dir, bool isDown);    
    void armReady();    
    void updateAnimation();    
    void changeWeapon();    
    void upgradeWeaponLevel();    
    void attack();    
    void armAnimationHandler(cocos2d::EventCustom *event);    
    void createArrow(float r, const cocos2d::Point &point);    
    void updateArrows();    
    void updateSpeed();
};
#endif  // DEMO_KNIGHT_H