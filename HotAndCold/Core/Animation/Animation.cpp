#include "Animation.h"

Animation::Animation(const std::string& name, const std::vector<SDL_Rect>& frameRects, float frameTime, bool loop)
    : name(name), frames(frameRects), frameTime(frameTime), loop(loop) {
}

const std::string& Animation::GetName() const {
    return name;
}

const std::vector<SDL_Rect>& Animation::GetFrames() const {
    return frames;
}

const SDL_Rect& Animation::GetFrame(size_t index) const {
    return frames.at(index);
}

size_t Animation::GetFrameCount() const {
    return frames.size();
}

float Animation::GetFrameTime() const {
    return frameTime;
}

bool Animation::IsLooping() const {
    return loop;
}
