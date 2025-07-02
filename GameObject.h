#pragma once
#include <raylib.h>

class GameObject {
protected:
    Rectangle rect;
    bool isActive;

public:
    GameObject();
    GameObject(float x, float y, float width, float height, bool active = false);

    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;

    Rectangle GetRect() const;
    bool IsActive() const;
    void SetActive(bool active);
    void SetPosition(float x, float y);
};