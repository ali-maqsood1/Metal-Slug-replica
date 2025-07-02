#include "GameObject.h"

GameObject::GameObject() : isActive(false) {}

GameObject::GameObject(float x, float y, float width, float height, bool active) {
    rect = { x, y, width, height };
    isActive = active;
}

Rectangle GameObject::GetRect() const { return rect; }

bool GameObject::IsActive() const { return isActive; }

void GameObject::SetActive(bool active) { 
    isActive = active; 
}
void GameObject::SetPosition(float x, float y) { 
    rect.x = x; rect.y = y; 
}