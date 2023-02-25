#include "api.h"
#include "pros/motors.hpp"

using namespace std;

class Drive {
    public:
        int leftDrive[3] = {};
        int rightDrive[3] = {};
        float ratio = 0;
        float wheelsize = 0;
        int IMUport = 0;
        void setTank(int left, int right);
        void SetTurnPid(double target, int TurnSpeed);
        void SetDrivePid(double target, int DriveSpeed);
        void Wait();
    private:
        void CheckTurn();
        void CheckDrive();
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
        static void lcdInit();
        static inline int selected = 0;
        static inline int hue = 227;
};

class auton {
    public:
        static void AddAuton(Auton auton);
        static void AutonSelector();
        static void RunAuton();
};