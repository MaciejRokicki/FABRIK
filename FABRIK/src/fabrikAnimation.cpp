#include "headers/fabrikAnimation.h"

FabrikAnimation::FabrikAnimation(
        std::vector<Object*>* targets,
        std::vector<Vector3*> frames, 
        bool playOnStart,
        double timePerFrame, 
        std::function<void()> frameUpdate, 
        bool loop, 
        bool mirror) {
    this->targets = targets;
    this->frames = frames;
    this->stopped = !playOnStart;
    this->timePerFrame = timePerFrame;
    this->frameUpdate = frameUpdate;
    this->loop = loop;

    if (mirror) {
        MirrorFrames();
    }
}

FabrikAnimation::FabrikAnimation(
        std::vector<Object*>* targets,
        Vector3** positions,
        int positionCount,
        int framesPerPosition,
        bool playOnStart,
        double timePerFrame,
        std::function<void()> frameUpdate,
        bool loop,
        bool mirror) {
    this->targets = targets;
    this->stopped = !playOnStart;
    this->timePerFrame = timePerFrame;
    this->frameUpdate = frameUpdate;
    this->loop = loop;

    for (int i = 1; i < positionCount; i++) {
        GenerateFrames(targets->size(), positions[i-1], positions[i], framesPerPosition);
    }

    if (mirror) {
        MirrorFrames();
    }
}

void FabrikAnimation::Play(double deltaTime) {
    if (!stopped) {
        time += deltaTime;

        if (time > timePerFrame) {
            NextFrame();

            if (currentFrame == frames.size() - 1) {
                if (loop) {
                    Reset();
                }
                else {
                    stopped = true;
                }
            }

            time = 0.0;
        }
    }
}

void FabrikAnimation::PauseResume() {
    stopped = !stopped;
}

void FabrikAnimation::Reset() {
    currentFrame = -1;
    NextFrame();
}

void FabrikAnimation::NextFrame() {
    currentFrame++;

    if (currentFrame > frames.size() - 1) {
        currentFrame = frames.size() - 1;
    }

    for (int i = 0; i < targets->size(); i++) {
        targets->at(i)->Translate(frames[currentFrame][i]);
    }

    frameUpdate();
}

void FabrikAnimation::PreviousFrame() {
    currentFrame--;

    if (currentFrame < 0) {
        currentFrame = 0;
    }

    for (int i = 0; i < targets->size(); i++) {
        targets->at(i)->Translate(frames[currentFrame][i]);
    }

    frameUpdate();
}

void FabrikAnimation::GenerateFrames(int targetsCount, Vector3* startPosition, Vector3* endPosition, int frames) {
    Vector3* diffVectors = new Vector3[targetsCount];

    for (int i = 0; i < targetsCount; i++) {
        diffVectors[i] = endPosition[i] - startPosition[i];
    }

    for (int i = 0; i < frames; i++) {
        Vector3* newVectors = new Vector3[targetsCount];

        for (int j = 0; j < targetsCount; j++) {
            newVectors[j] = startPosition[j] + diffVectors[j] / frames * i;
        }

        this->frames.push_back(newVectors);
    }
}

void FabrikAnimation::MirrorFrames() {
    for (int i = frames.size() - 2; i > 1; i--) {
        frames.push_back(new Vector3[targets->size()]{
            frames[i][0],
            frames[i][1],
            frames[i][2],
            frames[i][3],
            frames[i][4]
            });
    }
}