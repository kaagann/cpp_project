#include "Character.h"
#include "Collisions.h"
#include "Resources.h"
#include "RockHead.h"
#include "fmt/ostream.h"
#include "fmt/printf.h"

const float movementSpeed = 100.0f;
const float gravity = 400.0f;

extern void LoadMap(const std::string& mapFile);


void Character::Begin() {
    health = defaultHealth;
    runAnimation = Animation(1.2f, {
        AnimFrame(1.1f, Resources::textures["run.png"]),
        AnimFrame(1.0f, Resources::textures["run1.png"]),
        AnimFrame(0.9f, Resources::textures["run2.png"]),
        AnimFrame(0.8f, Resources::textures["run3.png"]),
        AnimFrame(0.7f, Resources::textures["run4.png"]),
        AnimFrame(0.6f, Resources::textures["run5.png"]),
        AnimFrame(0.5f, Resources::textures["run6.png"]),
        AnimFrame(0.4f, Resources::textures["run7.png"]),
        AnimFrame(0.3f, Resources::textures["run8.png"]),
        AnimFrame(0.2f, Resources::textures["run9.png"]),
        AnimFrame(0.1f, Resources::textures["run10.png"]),
        AnimFrame(0.0f, Resources::textures["run11.png"]),
    });

    idleAnimation = Animation(1.1f, {
        AnimFrame(1.0f, Resources::textures["idle.png"]),
        AnimFrame(0.9f, Resources::textures["idle1.png"]),
        AnimFrame(0.8f, Resources::textures["idle2.png"]),
        AnimFrame(0.7f, Resources::textures["idle3.png"]),
        AnimFrame(0.6f, Resources::textures["idle4.png"]),
        AnimFrame(0.5f, Resources::textures["idle5.png"]),
        AnimFrame(0.4f, Resources::textures["idle6.png"]),
        AnimFrame(0.3f, Resources::textures["idle7.png"]),
        AnimFrame(0.2f, Resources::textures["idle8.png"]),
        AnimFrame(0.1f, Resources::textures["idle9.png"]),
        AnimFrame(0.0f, Resources::textures["idle10.png"]),
    });

    hitAnimation = Animation(0.7f, {
        AnimFrame(0.6f, Resources::textures["hit.png"]),
        AnimFrame(0.5f, Resources::textures["hit1.png"]),
        AnimFrame(0.4f, Resources::textures["hit2.png"]),
        AnimFrame(0.3f, Resources::textures["hit3.png"]),
        AnimFrame(0.2f, Resources::textures["hit4.png"]),
        AnimFrame(0.1f, Resources::textures["hit5.png"]),
        AnimFrame(0.0f, Resources::textures["hit6.png"]),
    });

    dJumpAnimation = Animation(0.6f, {
        AnimFrame(0.5f, Resources::textures["djump.png"]),
        AnimFrame(0.4f, Resources::textures["djump1.png"]),
        AnimFrame(0.3f, Resources::textures["djump2.png"]),
        AnimFrame(0.2f, Resources::textures["djump3.png"]),
        AnimFrame(0.1f, Resources::textures["djump4.png"]),
        AnimFrame(0.0f, Resources::textures["djump5.png"]),
    });

    shape.setSize(sf::Vector2f(16.0f, 32.0f));
    shape.setOrigin(8.0f, 16.0f); // Merkezden döndürme ve konumlandırma
    shape.setFillColor(sf::Color::Green); // Görünürlük için renk
    shape.setPosition(position);
    textureToDraw = Resources::textures["idle1.png"];
}

void Character::ResetJumpCount() {
    jumpCount = 0;
}


bool CheckCollision(float x, float y, float width, float height) {
    auto CELL_SIZE = 16.0f;
    int tileColumnStart = (int)(x / CELL_SIZE);
    int tileColumnEnd = (int)((x + width) / CELL_SIZE) + 1;
    int tileRowStart = (int)(y / CELL_SIZE);
    int tileRowEnd = (int)((y + height) / CELL_SIZE) + 1;

    for (int column = tileColumnStart; column < tileColumnEnd; column++) {
        for (int row = tileRowStart; row < tileRowEnd; row++) {
            if (Collisions::mapGrid[column][row]) {
                return true;
            }
        }
    }

    return false;
}

Object* CheckCollectableCollision(float x, float y, float width, float height) {
    auto CELL_SIZE = 16.0f;
    int tileColumnStart = (int)(x / CELL_SIZE);
    int tileColumnEnd = (int)((x + width) / CELL_SIZE) + 1;
    int tileRowStart = (int)(y / CELL_SIZE);
    int tileRowEnd = (int)((y + height) / CELL_SIZE) + 1;

    for (int column = tileColumnStart; column < tileColumnEnd; column++) {
        for (int row = tileRowStart; row < tileRowEnd; row++) {
            if (Collisions::objects[column][row] != nullptr) {
                if (Collisions::objects[column][row]->type == Object::COLLECTABLE || Collisions::objects[column][row]->type == Object::JUMP_BUFF) {
                    Object* obj = Collisions::objects[column][row];
                    Collisions::objects[column][row] = nullptr;
                    return obj;
                } else if (Collisions::objects[column][row]) {
                    return Collisions::objects[column][row];
                }
            }
        }
    }

    return nullptr;
}


void Character::Update(float deltaTime) {
    float move = movementSpeed * deltaTime;

    sf::Vector2f newPosition = position;

    runAnimation.Update(deltaTime);
    idleAnimation.Update(deltaTime);
    hitAnimation.Update(deltaTime);
    dJumpAnimation.Update(deltaTime);

    bool isMoving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        newPosition.x -= move;
        facingLeft = true;
        isMoving = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        newPosition.x += move;
        facingLeft = false;
        isMoving = true;
    }

    // Zıplama kontrolü
    bool jumpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    if (jumpKeyPressed && !jumpPressed && (isGrounded || jumpCount < maxJumpCount)) {
        fmt::print("jump count: {}\n", jumpCount);
        velocity.y = -jumpVelocity;
        jumpCount++; // Zıplama sayacını artır
        isGrounded = false;
        jumpPressed = true; // Zıplama tuşunun basıldığını işaretle
    }

    if (!jumpKeyPressed) {
        jumpPressed = false; // Zıplama tuşunun bırakıldığını işaretle
    }

    // Yerçekimini uygula
    velocity.y += gravity * deltaTime;
    newPosition.y += velocity.y * deltaTime;

    // Çarpışma kontrolleri (yatay)
    if (CheckCollision(newPosition.x - shape.getSize().x / 2, position.y - shape.getSize().y / 2, shape.getSize().x, shape.getSize().y)) {
        // Çarpışma varsa yatay pozisyonu geri al
        newPosition.x = position.x;
    }

    // Çarpışma kontrolleri (dikey)
    if (CheckCollision(position.x - shape.getSize().x / 2, newPosition.y - shape.getSize().y / 2, shape.getSize().x, shape.getSize().y)) {
        // Çarpışma varsa dikey pozisyonu geri al
        newPosition.y = position.y;
        velocity.y = 0; // Zıplama hızını sıfırla
        isGrounded = true;
        jumpCount = 0; // Zıplama sayacını sıfırla
    } else {
        isGrounded = false;
    }

    // Yeni pozisyonu güncelle
    position = newPosition;
    shape.setPosition(position);

    Object* collidedObject = CheckCollectableCollision(newPosition.x - shape.getSize().x / 2, newPosition.y - shape.getSize().y / 2, shape.getSize().x, shape.getSize().y);
    if (collidedObject != nullptr) {
        if (collidedObject->type == Object::COLLECTABLE) {
            fmt::print("Collectable item alındı!");
        } else if (collidedObject->type == Object::TRAP) {
            health -= 1; // Canı 1 azalt
            isHit = true;
            hitTime = 0.0f; // Hit süresini başlat
            fmt::print("Tuzak: Can azaldı, kalan can: {}\n", health);
        } else if (collidedObject->type == Object::ROCK_HEAD) {
            auto rockHead = dynamic_cast<RockHead*>(collidedObject);
            if (rockHead && position.y < rockHead->GetBounds().top) {
                int column = static_cast<int>(rockHead->position.x / 16.0f);
                int row = static_cast<int>(rockHead->position.y / 16.0f);
                delete rockHead;
                Collisions::objects[column][row] = nullptr; // RockHead'i sil
            }
        } else if (collidedObject->type == Object::END_POINT) {
            //chapter passed
            LoadMap("../assets/textures/map.png");
        }
    }

    if (isHit) {
        hitTime += deltaTime;
        if (hitTime < hitDuration) {
            textureToDraw = hitAnimation.GetTexture();
        } else {
            isHit = false;
        }
    } else {
        if (jumpCount == 2) {
            textureToDraw = dJumpAnimation.GetTexture();
        } else if (velocity.y < 0) {
            textureToDraw = Resources::textures["jump.png"];
        } else if (velocity.y > 0.2f && !isGrounded) {
            textureToDraw = Resources::textures["fall.png"];
        } else if (isMoving) {
            textureToDraw = runAnimation.GetTexture();
        } else {
            textureToDraw = idleAnimation.GetTexture();
        }
    }
}


void Character::Draw(Renderer &renderer) {
    renderer.Draw(textureToDraw, position, sf::Vector2f(facingLeft ? -32.0f : 32.0f, 32.0f), angle);
}

sf::FloatRect Character::GetBounds() {
    return sf::FloatRect(position.x - shape.getSize().x / 2, position.y - shape.getSize().y / 2, shape.getSize().x, shape.getSize().y);
}

int Character::GetCherryCount() {
    return cherryCount;
}

int Character::GetHealth() {
    return health;
}

void Character::Reset() {
    health = defaultHealth;
    cherryCount = 0;
    isGrounded = false;
    isHit = false;
    hitTime = 0.0f;
    if (jumpBuffActive)
        jumpVelocity /= 1.2;
    jumpBuffActive = false;
    jumpBuffTime = 0.0f;
    velocity = sf::Vector2f(0.0f, 0.0f);
    isDead = false;
}
