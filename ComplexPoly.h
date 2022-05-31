#ifndef COMPLEXPOLY_C_COMPLEXPOLY_H
#define COMPLEXPOLY_C_COMPLEXPOLY_H

#include "Complex.h"

struct ComplexPoly;
typedef struct ComplexPoly ComplexPoly;

extern ComplexPoly* new_ComplexPoly(int t_size);
extern ComplexPoly* copy_ComplexPoly(ComplexPoly *copy);
extern void free_ComplexPoly(ComplexPoly *poly);

int resize_ComplexPoly(ComplexPoly *poly, int t_size);
int size(ComplexPoly *poly);

void fit(ComplexPoly *poly);

Complex* get_coefficient(ComplexPoly *poly, int pos);
int set_coefficient(ComplexPoly *poly, int pos, Complex *num);

int equal_ComplexPoly(ComplexPoly *poly1, ComplexPoly *poly2);

ComplexPoly* fft(ComplexPoly *poly);
ComplexPoly* inverse_fft(ComplexPoly *poly);

ComplexPoly* scale(ComplexPoly *poly, int t_size);
ComplexPoly* recip(ComplexPoly *poly);

ComplexPoly* neg_ComplexPoly(ComplexPoly *poly);
ComplexPoly* plus_ComplexPoly(ComplexPoly *poly1, ComplexPoly *poly2);
ComplexPoly* minus_ComplexPoly(ComplexPoly *poly1, ComplexPoly *poly2);
ComplexPoly* scalar_mul_ComplexPoly(ComplexPoly *poly, double num);
ComplexPoly* mul_ComplexPoly(ComplexPoly *poly1, ComplexPoly *poly2);
ComplexPoly* div_ComplexPoly(ComplexPoly *poly1, ComplexPoly *poly2);
ComplexPoly* mod_ComplexPoly(ComplexPoly *poly1, ComplexPoly *poly2);

Complex* value(ComplexPoly *poly, Complex *x);
ComplexPoly* derivative(ComplexPoly *poly);
Complex* root_Newton(ComplexPoly *poly, Complex *x);

void fprint_ComplexPoly(ComplexPoly *poly, char *file_name, int column, int precision);
void print_ComplexPoly(ComplexPoly *poly);
void input_ComplexPoly(ComplexPoly *poly);
void inputs_ComplexPoly(ComplexPoly *poly, char *buff, int buff_size);

ComplexPoly* generate(int size, double lower_bound, double upper_bound);
#endif //COMPLEXPOLY_C_COMPLEXPOLY_H
