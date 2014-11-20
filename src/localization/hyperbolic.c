#include "hyperbolic.h"

void ComputePositions(float tdoa_12, float tdoa_13, float tdoa_32, float tdoa_34, float *x, float *y, float *z)
{

	float R12, R13, R32, R34 ;
	float A, B, C, D, E, F, G, H, I, J, K, L, M, N, O ; 
	
	R12 = tdoa_12 * speedSound ;
	R13 = tdoa_13 * speedSound ;
	R32 = tdoa_32 * speedSound ;
	R34 = tdoa_34 * speedSound ;
	
	A = (R13 * x21 - R12 * x31) / (R12 * y31 - R13 * y21) ;
	B = (R13 * z21 - R12 * z31) / (R12 * y31 - R13 * y21) ;
	C = (R13 * (R12*R12 + x1*x1 - x2*x2 + y1*y1 - y2*y2 + z1*z1 - z2*z2) - R12 * (R13*R13 + x1*x1 - x3*x3  + y1*y1 - y3*y3 +z1*z1 -z3*z3)) / (2*(R12*y31 - R13*y21)) ;

	D = (R34 * x23 - R32 * x43) / (R32 * y43 - R34 * y23) ;
	E = (R34 * z23 - R32 * z43) / (R32 * y43 - R34 * y23) ;
	F = (R34 * (R32*R32 + x3*x3 - x2*x2 + y3*y3 - y2*y2 + z3*z3 - z2*z2) - R32 * (R34*R34 + x3*x3 - x4*x4  + y3*y3 - y4*y4 +z3*z3 -z4*z4)) / (2*(R32*y43 - R34*y23)) ;

	G = (E - B) / (A - D) ;
	H = (F - C) / (A - D) ;

	I = A*G + B ;
	J = A*H + C ;

	K = R13*R13 + x1*x1 -x3*x3 + y1*y1 -y3*y3 + z1*z1 -z3*z3 + 2*x31*H + 2*y31*J ;
	L = 2*(x31*G + y31*I + 2*z31) ;
	
	M = 4*R13*R13*(G*G + I*I + 1) - L*L ;
	N = 8*R13*R13*(G*(x1-H) + I*(y1-J)+z1) + 2*L*K ;
	O = 4*R13*R13*((x1-H)*(x1-H) + (y1-J)*(y1-J) + z1*z1) - K*K ;

	*z = N/(2*M) + sqrt((N/(2*M))*(N/(2*M)) - O/M) ;
	*x = G*(*z) + H ;
	*y = I*(*z) + J ;
}
