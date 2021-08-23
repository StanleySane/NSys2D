#if !defined(_STD_AFX_MY_H_)
#define _STD_AFX_MY_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//	методы поиска собств.форм и значений
typedef enum{EVM_JACOBY = 0, EVM_QR_ELM, EVM_QR_DIR, EVM_QR_ORT}	EV_METHOD;
//	ошибки поиска собств.значений
typedef enum{ EVE_NOERR = 0, EVE_NOSOLUT, EVE_DIMERR } EV_EXCEPT;

//наименьшее число в ЭВМ, для которого выполняется
//условие: 1+MACHEPS>1.
#define MACHEPS 1e-250
#define MACH_EPS 5.24e-20
//наименьшее положительное число
#define ETA 1.7e-308
#define ZERO 1e-300
#define TOL (ETA/MACH_EPS)

typedef enum{ BME_NOERR = 0, BME_NULLONDIAG, BME_DIMERR } SBM_EXCEPT;
typedef enum{ BMC_SOLVE = 0, BMC_GETDET }	SBM_ERRCONTROL;
typedef enum{ BMI_FULL = 0, BMI_ONE }	SBM_ITERAT;

typedef struct _det_
{
//представление определителя в виде mant*2^power.
	double mant;
	int power;
}	DETERMINANT;

#include<vector>
typedef std::vector<int>	ARRAY;
typedef std::vector<double>	DOUBLE_ARRAY;

#endif //_STD_AFX_MY_H_