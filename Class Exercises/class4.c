#include <stdio.h>

int x;
int y;
int result;

int main(int argc, char **argv)
{
  printf("Enter decimal x: ");
  scanf("%d", &x);

  printf("Enter decimal y: ");
  scanf("%d", &y);

  // Add a conditional with both true and false branches, and
  // dependent on the values of x and y here ...
  int a = 5;
  if (a == 5)
	printf("true");
  else
	printf("false");

  // Outside of the conditional, leave the following code so
  // that we can see where sequential execution continues after
  // the conditional.

  printf("result = (0x%8.8x)\n", result);
  return 0;
}

