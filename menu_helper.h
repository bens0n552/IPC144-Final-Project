/* DIGITAL SIGNATURE(S):
   ====================

   List the student author(s) of this code below:

   Fullname                    Seneca Email Address
   --------------------------- ----------------------------
   1) Le Minh Nhat Dang        lmndang@myseneca.ca
   2) Benson Zhao Lang Li      eisik1@myseneca.ca
   3) Emre Isik                bli113@myseneca.ca

   +--------------------------------------------------------+
   |                   FILE: main.c                         |
   +--------------------------------------------------------+
   |           2  0  2  0  ~  W  I  N  T  E  R              |
   |                 I  P  C  :  B  T  P                    |
   |                 1  4  4  :  1  0  0                    |
   |              FINAL ASSESSMENT PART - 2                 |
   |                                                        |
   |     S  E  N  E  C  A            C  O  L  L  E  G  E    |
   +--------------------------------------------------------+ */

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

