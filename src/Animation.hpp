#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstddef>

enum class AnimationState {
    Idle,
    Walk,
    Attack
};

class Animation {
private:
    std::vector<sf::IntRect> frames;

    std::size_t currentFrame = 0;
    float frameDuration = 0.1f;
    float elapsedTime = 0.0f;

    bool looping = true;
    bool finished = false;

public:
    Animation() = default;

    Animation(
        int row,
        int startCol,
        int frameCount,
        int frameWidth,
        int frameHeight,
        float durationPerFrame,
        bool loop = true
    )
        : frameDuration(durationPerFrame),
          looping(loop)
    {
        for (int i = 0; i < frameCount; ++i) {
            int x = (startCol + i) * frameWidth;
            int y = row * frameHeight;

            frames.emplace_back(x, y, frameWidth, frameHeight);
        }
    }

    void update(float deltaTime) {
        if (frames.empty() || (finished && !looping))
            return;

        elapsedTime += deltaTime;

        while (elapsedTime >= frameDuration) {
            elapsedTime -= frameDuration;
            ++currentFrame;

            if (currentFrame >= frames.size()) {
                if (looping) {
                    currentFrame = 0;
                } else {
                    currentFrame = frames.size() - 1;
                    finished = true;
                    break;
                }
            }
        }
    }

    void applyToSprite(sf::Sprite& sprite) const {
        if (!frames.empty()) {
            sprite.setTextureRect(frames[currentFrame]);
        }
    }

    void reset() {
        currentFrame = 0;
        elapsedTime = 0.0f;
        finished = false;
    }

    bool isFinished() const {
        return finished;
    }
};