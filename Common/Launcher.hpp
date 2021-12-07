#pragma once

class CLauncher 
{
public:
    CLauncher() = default;
    CLauncher(CLauncher &other) = delete;
    void operator=(const CLauncher &other) = delete;
    ~CLauncher() = default;
    int Execute();
protected:
    bool Load();
    int Run();
    void Cleanup();
private:
    //counters
    int m_updateCounter = 0;
    int m_frameCounter = 0;
    int m_framesPerSecondCounter = 0;
    int m_elapsedFrames = 0;
    int m_elapsedTime = 0;
};

