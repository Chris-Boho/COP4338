#include <stdio.h>
/* print Fahrenheit-Kelvin table
for fahr = 0, 20, ..., 300 */
void main()
{
     int fahr;
     double kel;
     int lower, upper, step;
     lower = 0; /* lower limit of temperature scale */
     upper = 300; /* upper limit */
     step = 10; /* step size */
     fahr = lower;

     while (fahr <= upper) {
          kel = 5 * (fahr + 459.67) / 9;
          printf("%d\t%6.1f\n", fahr, kel);
          fahr = fahr + step;
     }
}
