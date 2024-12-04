#include "Laser.h"
#include "util.h"
#include "GameState.h"
#include <iostream>
#include <sgg/graphics.h>

// Constructor
Laser::Laser(float pos_x, float pos_y, float width, float height, const std::string& texture)
    : GameObject("Laser"), Box(pos_x, pos_y, width, height), m_texture(texture), m_is_active(false), m_speed(0.0f) {
}

// Copy constructor
Laser::Laser(const Laser& other)
    : GameObject(other), // Call base class copy constructor
    Box(other), // Call Box copy constructor
    m_texture(other.m_texture),
    m_is_active(other.m_is_active),
    m_speed(other.m_speed),
    m_initial_pos_x(other.m_initial_pos_x),
    m_initial_pos_y(other.m_initial_pos_y) {
}

// Copy assignment operator
/* Ο τελεστής αντιγραφής ανάθεσης χρησιμοποιείται
για να αναθέσει τις τιμές από ένα υπάρχον αντικείμενο Laser
σε ένα άλλο υπάρχον αντικείμενο Laser*/
Laser& Laser::operator=(const Laser& other) {
    if (this != &other) {
        GameObject::operator=(other);
        Box::operator=(other);
        m_texture = other.m_texture;
        m_is_active = other.m_is_active;
        m_speed = other.m_speed;
        m_initial_pos_x = other.m_initial_pos_x;
        m_initial_pos_y = other.m_initial_pos_y;
    }
    return *this;
}

// Move constructor
/*Ο κατασκευαστής μετακίνησης χρησιμοποιείται για να δημιουργήσει ένα νέο αντικείμενο Laser μεταφέροντας (stealing) πόρους
από ένα προσωρινόαντικείμενο Laser (other). Αυτό είναι πιο αποδοτικό από την αντιγραφή,
αφού αποφεύγει την αναπαραγωγή των δεδομένων*/
Laser::Laser(Laser&& other) noexcept
    : GameObject(std::move(other)),
    Box(std::move(other)),
    m_laser_brush(std::move(other.m_laser_brush)),
    m_laser_brush_debug(std::move(other.m_laser_brush_debug)),
    m_texture(std::move(other.m_texture)),
    m_is_active(other.m_is_active),
    m_speed(other.m_speed) {
}

// Move assignment operator
/* Ο τελεστής μετακίνησης ανάθεσης χρησιμοποιείται για να μεταφέρει (move) τους πόρους
από ένα υπάρχον αντικείμενο Laser σε ένα άλλο υπάρχον αντικείμενο Laser*/
Laser& Laser::operator=(Laser&& other) noexcept {
    if (this != &other) {
        GameObject::operator=(std::move(other));
        Box::operator=(std::move(other));
        m_laser_brush = std::move(other.m_laser_brush);
        m_laser_brush_debug = std::move(other.m_laser_brush_debug);
        m_texture = std::move(other.m_texture);
        m_is_active = other.m_is_active;
        m_speed = other.m_speed;
    }
    return *this;
}

void Laser::init() {
    m_laser_brush.outline_opacity = 0.0f;
    m_laser_brush.texture = m_state->getFullAssetPath(m_texture);

    m_laser_brush_debug.fill_opacity = 0.1f;
    SETCOLOR(m_laser_brush_debug.fill_color, 1.0f, 0.0f, 0.0f);
    SETCOLOR(m_laser_brush_debug.outline_color, 1.0f, 0.0f, 0.0f);
}

void Laser::update(float dt) {
    if (!m_active) return;  // Skip update if the laser is inactive
    move(dt);
}

void Laser::draw() {

    graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_laser_brush);

    if (m_state->m_debugging) {
        graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_laser_brush_debug);
    }

}

void Laser::move(float dt) {
    m_pos_y += m_laser_speed * (dt / 1000.0f);  // Move to the bottom
}

void Laser::reset() {
    m_pos_x = m_initial_pos_x;
    m_pos_y = m_initial_pos_y;
}

void Laser::setTexture(const std::string& texture) {
    m_texture = texture;
    m_laser_brush.texture = m_state->getFullAssetPath(m_texture);
}

std::string Laser::getTexture() {
    return m_texture;
}
