#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}
int greedy(int val, int* coins, int n) {
    qsort(coins, n, sizeof(int), compare);
    int max = 0;
    int count = 0;
   for (int i = 0; i < n; i++) {
        max = coins[i];
        while (val >= max) {
            val -= max;
            count++;
        }
        if (val == 0) {
            break;
        }
    }
    if (val != 0) {
        return -1;
    }
    return count;
}


int divide_and_conquer(int val, int* coins, int n, int* table) {
  if (val == 0) return 0;
  if (table[val] != INT_MAX) return table[val];

  int min = INT_MAX;
  for (int i = 0; i < n; i++) {
    if (coins[i] <= val) {
      int res = divide_and_conquer(val - coins[i], coins, n, table);
      if (res != -1 && res < min) {
        min = res + 1;
      }
    }
  }

  table[val] = (min == INT_MAX) ? -1 : min;
  return table[val];
}

int dyn_prog(int val, int* coins, int n, int* table, int* sol) {
  for (int i = 1; i <= val; i++) {
    int from;
    for (int j = 0; j < n; j++) {
      int count = 0;
      if (coins[j] > i) {
        continue;
      } else {
        if (table[i - coins[j]] != -1) {
          count = table[i - coins[j]] + 1;
        } else {
          count = -1;
        }
      }
      from = (i - coins[j]);
      if (table[i] == -1) {
        table[i] = count;
        sol[i] = from;
      }
      if (count >= 0) {
        if (table[i] > count) {
          table[i] = count;
          sol[i] = from;
        }
      }
    }
  }
  if (table[val] <= 0)
    return -1;
  return table[val];
}

void print_sol(int val, int* sol) {
  int coin;
  while ( sol[val] >= 0){
      if(sol[val] ==0){
          coin = val;
          printf("%d\n",coin);
          break;
      }
      else{
          printf("%d, ",val - sol[val]);
          val = sol[val];
      }
  }
  return;
  
}

int main(int argc, char** argv) {
  int n = argc - 2;
  int val;
  sscanf(argv[argc-1], "%d", &val);
  int coins[n];
  
  for(int i=0; i < n; i++) {
    sscanf(argv[i+1], "%d", &coins[i]);
  }

  printf("Making change for %d.\n", val);

  int res;

  res = greedy(val, coins, n);

  if(res != -1) {
	printf("Greedy found change using %d coins.\n", res);
  } else {
	printf("Greedy could not find change.\n");
  }

  int table[val+1];

  for(int i=0; i < val+1; i++) {
	table[i] = -1;
  }
  table[0] = 0;
  
  res = divide_and_conquer(val, coins, n, table);
  
  if(res != -1) {
	printf("Divide & conquer found change using %d coins.\n", res);
  } else {
	printf("Divide & conquer could not find change.\n");
  }

  int sol[val+1];
  for(int i=0; i < val+1; i++) {
	table[i] = -1;
	sol[i] = -1;
  }
  table[0] = 0;
  sol[0] = 0;
  
  res = dyn_prog(val, coins, n, table, sol);
  
  if(res != -1) {
	printf("Dynamic programming found change using %d coins.\n", res);
	print_sol(val, sol);
  } else {
	printf("Dynamic programming could not find change.\n");
  }
}
