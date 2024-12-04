#include "Enemy.h"
#include "GameState.h"
#include "util.h"
#include <iostream>
#include <sgg/graphics.h>

Enemy::Enemy(float pos_x, float pos_y, float width, float height, const std::string& texture) :
    GameObject("Enemy"), Box(pos_x, pos_y, width, height), m_texture(texture) {
}

Enemy::Enemy(Enemy&& other) noexcept :
    GameObject(std::move(other)), Box(std::move(other)),
    m_enemy_brush(std::move(other.m_enemy_brush)),
    m_enemy_brush_debug(std::move(other.m_enemy_brush_debug)),
    m_texture(std::move(other.m_texture)) {
    // Reset other's state if necessary
}

Enemy& Enemy::operator=(Enemy&& other) noexcept {
    if (this != &other) {
        GameObject::operator=(std::move(other));
        Box::operator=(std::move(other));
        m_enemy_brush = std::move(other.m_enemy_brush);
        m_enemy_brush_debug = std::move(other.m_enemy_brush_debug);
        m_texture = std::move(other.m_texture);
        // Reset other's state if necessary
    }
    return *this;
}

void Enemy::init() {
    m_enemy_brush.outline_opacity = 0.0f;
    m_enemy_brush.texture = m_state->getFullAssetPath(m_texture);

    // Increased debug opacity for better visibility
    m_enemy_brush_debug.fill_opacity = 0.5f;  // Make it more visible
    SETCOLOR(m_enemy_brush_debug.fill_color, 1.0f, 0.0f, 0.0f);  // Red color
    SETCOLOR(m_enemy_brush_debug.outline_color, 1.0f, 0.0f, 0.0f);
}

void Enemy::update(float dt) {
    move(dt);
}

void Enemy::draw() {
    // Drawing enemy at full size (not half)
    graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_enemy_brush);

    // Only draw debug rectangle if debugging is enabled
    if (m_state->m_debugging) {
        // Draw the debug rectangle at full size
        graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_enemy_brush_debug);
    }
}

void Enemy::move(float dt) {
    m_pos_x -= m_enemy_speed * (dt / 1000.0f);
}

void Enemy::setTexture(const std::string& texture) {
    m_texture = texture;
    m_enemy_brush.texture = m_state->getFullAssetPath(m_texture);
}

std::string Enemy::getTexture() {
    return m_texture;
}
