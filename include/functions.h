using namespace vex;
#include <atomic>

void intakeStore(bool sort, bool blue = true);
void outtake();
void intakeScoreTop(bool sort, bool blue = true);
void intakeScoreMid(double speed = 100);

static bool intakeCommand = false;
static bool isAuto = true;

int autoIntake(void* isBlue);

void distanceReset(int quadrant);