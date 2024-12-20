class InputHandler
{
public:
    bool keys[1024];
    bool firstMouse;
    float mouseSensitivity;
    float lastX;
    float lastY;
    float yaw;
    float pitch;

    InputHandler()
        : firstMouse(true),
          lastX(800.0f / 2.0),
          lastY(600.0 / 2.0),
          yaw(-90.0f),
          pitch(0.0f),
          mouseSensitivity(1.f)
    {
        for (int i = 0; i < 1024; i++)
        {
            keys[i] = false;
        }
    }

    void setKeyUp(int key)
    {
        keys[key] = false;
    }

    void setKeyDown(int key)
    {
        keys[key] = true;
    }

    bool isKeyDown(int key)
    {
        return keys[key];
    }

    bool isKeyUp(int key)
    {
        return !keys[key];
    }
};
