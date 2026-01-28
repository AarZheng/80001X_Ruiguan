using namespace vex;
#include <atomic>

void intakeStore(bool sort, bool blue = true);
void outtake(bool slowed = false);
void intakeScoreTop(bool sort, bool blue = true);
void intakeScoreMid(double speed = 100);

static bool intakeCommand = false;
static bool isAuto = true;
static bool wrongTopBall = false;

int autoIntake(void* isBlue);
int autoScore(void* isBlue);
int agitatorAntiJam();

void distanceReset(int quadrant);
void antiJamUpdate(motor &m);

static uint32_t ejectEndTime = 0;