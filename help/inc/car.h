#ifndef _CAR_H_
#define _CAR_H_

typedef struct Car
{
  char *mark;
  unsigned int year;
  double mas;
  double speed;
} s_car;

struct Car* init_car(char *mark, unsigned int year, double mass, double speed);
struct Car* free_car(struct Car *car);

#endif /* _CAR_H_ */
