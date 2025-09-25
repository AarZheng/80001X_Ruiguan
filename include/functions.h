using namespace vex;
#include <atomic>

void intakeStore(bool sort, bool blue = true);
void outtake();
void intakeScoreTop();
void intakeScoreMid();

static bool intakeCommand = false;
static bool isAuto = true;

int autoIntake(void* isBlue);