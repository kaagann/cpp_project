#include "RockHead.h"
#include "Resources.h"
#include "Collisions.h"

bool CheckMapCollision(float x, float y, float width, float height) {
    auto CELL_SIZE = 16.0f;
    int tileColumnStart = static_cast<int>(x / CELL_SIZE);
    int tileColumnEnd = static_cast<int>((x + width) / CELL_SIZE);
    int tileRowStart = static_cast<int>(y / CELL_SIZE);
    int tileRowEnd = static_cast<int>((y + height) / CELL_SIZE);

    for (int column = tileColumnStart; column <= tileColumnEnd; column++) {
        for (int row = tileRowStart; row <= tileRowEnd; row++) {
            if (Collisions::mapGrid[column][row]) {
                return true;
            }
        }
    }

    return false;
}

void RockHead::Begin() {
    velocity = sf::Vector2f(speed, 0.0f); // Başlangıçta sağa doğru hareket
    shape.setSize(sf::Vector2f(32.0f, 32.0f));
    shape.setOrigin(16.0f, 16.0f); // Merkezden döndürme ve konumlandırma
    shape.setFillColor(sf::Color::Green); // Görünürlük için renk
    shape.setPosition(position);

    // Başlangıç pozisyonunu Collisions::objects matrisine ekleyin
    int column = static_cast<int>(position.x / 16.0f);
    int row = static_cast<int>(position.y / 16.0f);
    Collisions::objects[column][row] = this;
}

void RockHead::Update(float deltaTime) {
    int oldColumn = static_cast<int>(position.x / 16.0f);
    int oldRow = static_cast<int>(position.y / 16.0f);

    // Geçici değişken
    Object* tempObject = Collisions::objects[oldColumn][oldRow];

    sf::Vector2f newPosition = position + velocity * deltaTime;

    // Yatay duvar kontrolü
    if (CheckMapCollision(newPosition.x - 12.0f, position.y - 16.0f, 24.0f, 12.0f)) {
        // Yön değiştir
        velocity.x = -velocity.x;
        newPosition = position + velocity * deltaTime; // Yeniden hesapla
    }

    position = newPosition;
    shape.setPosition(position); // Şeklin pozisyonunu güncelle

    // Yeni pozisyonu Collisions::objects matrisine ekleyin
    int newColumn = static_cast<int>(position.x / 16.0f);
    int newRow = static_cast<int>(position.y / 16.0f);

    if (newColumn != oldColumn || newRow != oldRow) {
        // Eski hücredeki nesneyi yedekle
        Object* previousObject = Collisions::objects[newColumn][newRow];

        // Eski hücreyi boşalt ve geçici nesneyi yerleştir
        Collisions::objects[oldColumn][oldRow] = tempObject == this ? nullptr : tempObject;
        Collisions::objects[newColumn][newRow] = this;

        // Yedeklenen nesneyi eski pozisyona geri koy
        if (previousObject && previousObject != this) {
            Collisions::objects[oldColumn][oldRow] = previousObject;
        }
    }
}

void RockHead::Render(Renderer &renderer) {
    renderer.Draw(Resources::textures["rockHeadIdle.png"], position, sf::Vector2f(24.0f, 24.0f));
}

sf::FloatRect RockHead::GetBounds() const {
    auto size = sf::Vector2f(24.0f, 24.0f);
    return sf::FloatRect(position.x - size.x / 2, position.y - size.y / 2, size.x, size.y);
}
