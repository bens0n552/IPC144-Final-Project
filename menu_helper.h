#include "file_helper.h"

void clearKeyboard(void);

int getInt(void);

int getIntInRange(int min, int max);

int menu(void);

void managerSystem(void);

char getCategory(const struct RiderInfo info[], int realSize);

void displayAgeGroup(int age);

void displayTime(double start, double finish, int withdrew);

void displayWithdrawn(int withdrawnStatus);

void sortInfo(struct RiderInfo info[], int realSize);

void displayInfo(struct RiderInfo info[], int realSize);

void displayTopThreeRiders(struct RiderInfo info[], int realSize);

void displayLastThreeRiders(struct RiderInfo info[], int realSize);

void displayWinners(struct RiderInfo info[], int realSize);

