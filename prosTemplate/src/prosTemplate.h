#include "api.h"
#include "display/lv_core/lv_obj.h"
#include "pros/motors.hpp"

using namespace std;

class Drive {
    public:
        int leftDrive[3] = {};
        int rightDrive[3] = {};
        float ratio = 0;
        float wheelsize = 0;
        float motorRPM = 600;
        int IMUport = 0;
        void setTank(int left, int right);
        void SetTurnPid(double target, int TurnSpeed);
        void SetDrivePid(double target, int DriveSpeed);
        void Wait();
    private:
        void CheckTurn(void* param);
        void CheckDrive(void* param);
};

class Auton {
    public:
        std::string name;
        std::function<void()> auton;
    Auton(std::string name, std::function<void()> auton);
};

class prosTemplate {
    public:
        static inline int autonCount = 0;
        static Auton autons[];
        static const int delay = 20;
        static inline int selected = 0;
        static inline int hue = 227;
        class lcd {
            private:
                static inline lv_obj_t * canvas = nullptr;
            public:
                static void Init();
                static void print(std::int16_t line, const char *fmt);
                static void clear();
        };
};

class auton {
    public:
        static void AddAuton(Auton auton);
        static void AutonSelector();
        static void RunAuton();
};