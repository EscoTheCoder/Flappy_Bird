#include "Kills.h"
#include "GameState.h"
#include "box.h"
#include "util.h"
#include <iostream>
#include <sgg/graphics.h>



Kills::Kills(float pos_x, float pos_y, float width, float height, const std::string& texture) :
    GameObject("Coin_Score"), Box(pos_x, pos_y, width, height), m_texture(texture) {
}


Kills::Kills(Kills&& other) noexcept :
    GameObject(std::move(other)), Box(std::move(other)),
    m_coin_score_brush(std::move(other.m_coin_score_brush)),
    m_coin_score_brush_debug(std::move(other.m_coin_score_brush_debug)),
    m_texture(std::move(other.m_texture)) {
    // Reset other's state if necessary
}

Kills& Kills::operator=(Kills&& other) noexcept {
    if (this != &other) {
        GameObject::operator=(std::move(other));
        Box::operator=(std::move(other));
        m_coin_score_brush = std::move(other.m_coin_score_brush);
        m_coin_score_brush_debug = std::move(other.m_coin_score_brush_debug);
        m_texture = std::move(other.m_texture);
        // Reset other's state if necessary
    }
    return *this;
}

void Kills::init() {
    m_coin_score_brush.outline_opacity = 0.0f;
    m_coin_score_brush.texture = m_state->getFullAssetPath(m_texture);

    m_coin_score_brush_debug.fill_opacity = 0.1f;
    SETCOLOR(m_coin_score_brush_debug.fill_color, 1.0f, 0.0f, 0.0f);
    SETCOLOR(m_coin_score_brush_debug.outline_color, 1.0f, 0.0f, 0.0f);

    // Αποθηκεύουμε την αρχική θέση κατά την αρχικοποίηση
    m_initial_pos_x = m_pos_x;
    m_initial_pos_y = m_pos_y;
}

void Kills::update(float dt) {
    move(dt);
}

void Kills::draw() {
    graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_coin_score_brush);

    if (m_state->m_debugging) {
        graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_coin_score_brush_debug);
    }
}

void Kills::reset() {
    // Επαναφορά της θέσης του σωλήνα στην αρχική κατάσταση
    m_pos_x = m_initial_pos_x;
    m_pos_y = m_initial_pos_y;
}

void Kills::move(float dt) {
    m_pos_x -= m_coin_score_speed * (dt / 1000.0f);
}

void Kills::setTexture(const std::string& texture) {
    m_texture = texture;
    m_coin_score_brush.texture = m_state->getFullAssetPath(m_texture);
}

std::string Kills::getTexture() {
    return m_texture;
}