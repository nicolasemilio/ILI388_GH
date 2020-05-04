#include <list>
#include <vector>
#include <set>
#include <queue>
#include <iostream>
#include <sstream>
#include <string.h>
#include <algorithm>

#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
#include "time.h"

using namespace std;

#define outputfile "salida.txt"
#define outputfileRates "valores_tasas.txt"
#define CantOperadores 2
#define PI 3.141592654

#define Optimof1 0.0000000001
#define Optimof4 0.000001
#define Optimof5 0.0001
#define Optimof6 0.001

#define CRUZAMIENTO 0
#define MUTACION 1 

#define BITFLIP 1
#define INORDER 2

#define UNPUNTO 1
#define DOSPUNTOS 2

#define ROULETTE 1
#define TOURNAMENT 2
#define RANKING 3

#define TAM 100
#define AMAX 10000000

