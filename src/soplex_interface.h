
#ifndef _SOPLEX_C_INTERFACE_H_
#define _SOPLEX_C_INTERFACE_H_

/* the enums are used in headers */
#include "soplex_enumerations.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __cplusplus
#include <stdbool.h>
#endif

/** this is type of numerator and denominator used to interface rational solver */
/* it may not match type used internally */
typedef signed long long SoPlex_RatIntType;

/** creates new SoPlex struct **/
void* SoPlex_create();

/** frees SoPlex struct **/
void SoPlex_free(void* soplex);

/** reads LP file in LP or MPS format according to READMODE parameter; returns true on success **/
bool SoPlex_readInstanceFile(void* soplex, const char* filename);

/** reads basis information from filename and returns true on success **/
bool SoPlex_readBasisFile(void* soplex, const char* filename);

/** reads settings from filename and returns true on success **/
bool SoPlex_readSettingsFile(void* soplex, const char* filename);


/** writes real LP to file; LP or MPS format is chosen from the extension in \p filename; returns true on success */
bool SoPlex_writeInstanceFileReal(void* soplex, const char* filename);

/** writes rational LP to file; LP or MPS format is chosen from the extension in \p filename; returns true on success */
bool SoPlex_writeInstanceFileReal(void* soplex, const char* filename);

/** writes dual of real LP to file; LP or MPS format is chosen from the extension in \p filename; returns true on success */
bool SoPlex_writeDualFileReal(void* soplex, const char* filename);

/** writes basis information to \p filename; returns true on success */
bool SoPlex_writeBasisFile(void* soplex, const char* filename);

/** writes internal LP, basis information, and parameter settings */
void SoPlex_writeStateFileReal(void* soplex, const char* filename);

/** writes internal LP, basis information, and parameter settings */
void SoPlex_writeStateFileRational(void* soplex, const char* filename);



/** clears the (floating point) LP **/
void SoPlex_clearLPReal(void* soplex);

/** returns number of rows **/
int SoPlex_numRows(void* soplex);

/** returns number of columns **/
int SoPlex_numCols(void* soplex);

/** enables rational solving mode  **/
void SoPlex_setRational(void* soplex);


/** sets boolean parameter value **/
bool SoPlex_setBoolParam(void* soplex, SoPlex_BoolParamEnum paramcode, bool paramvalue);

/** sets integer parameter value **/
bool SoPlex_setIntParam(void* soplex, SoPlex_IntParamEnum paramcode, int paramvalue);

/** sets real parameter value **/
bool SoPlex_setRealParam(void* soplex, SoPlex_RealParamEnum paramcode, double paramvalue);

/** returns value of boolean parameter **/
bool SoPlex_getBoolParam(void* soplex, SoPlex_BoolParamEnum paramcode);

/** returns value of integer parameter **/
int SoPlex_getIntParam(void* soplex, SoPlex_IntParamEnum paramcode);

/** returns value of real parameter **/
double SoPlex_getRealParam(void* soplex, SoPlex_RealParamEnum paramcode);


/** adds a single (floating point) column **/
void SoPlex_addColReal(void* soplex, double* colentries, int colsize, int nnonzeros, double objval,
                       double lb, double ub);

/** removes a single (floating point) column **/
void SoPlex_removeColReal(void* soplex, int colidx);

/** adds a single rational column **/
void SoPlex_addColRational(void* soplex, SoPlex_RatIntType* colnums, SoPlex_RatIntType* coldenoms, int colsize, int nnonzeros,
                           SoPlex_RatIntType objvalnum, SoPlex_RatIntType objvaldenom, 
                           SoPlex_RatIntType lbnum, SoPlex_RatIntType lbdenom, 
                           SoPlex_RatIntType ubnum, SoPlex_RatIntType ubdenom);

/** removes a single (floating point) column **/
void SoPlex_removeColRational(void* soplex, int colidx);

/** adds a single (floating point) row **/
void SoPlex_addRowReal(void* soplex, double* rowentries, int rowsize, int nnonzeros, double lb,
                       double ub);

/** removes a single (floating point) row **/
void SoPlex_removeRowReal(void* soplex, int rowidx);

/** adds a single rational row **/
void SoPlex_addRowRational(void* soplex, SoPlex_RatIntType* rownums, SoPlex_RatIntType* rowdenoms, int rowsize, int nnonzeros,
                           SoPlex_RatIntType lbnum, SoPlex_RatIntType lbdenom, SoPlex_RatIntType ubnum, SoPlex_RatIntType ubdenom);

/** removes a single (floating point) row **/
void SoPlex_removeRowRational(void* soplex, int rowidx);

/** gets primal solution **/
void SoPlex_getPrimalReal(void* soplex, double* primal, int dim);

/** Returns rational primal solution in a char pointer.
*   The caller needs to ensure the char array is freed.
**/
char* SoPlex_getPrimalRationalString(void* soplex, int dim);

/** gets dual solution **/
void SoPlex_getDualReal(void* soplex, double* dual, int dim);

/** gets reduced cost vector **/
void SoPlex_getRedCostReal(void* soplex, double* rc, int dim);

/** optimizes the given LP and returns solver status **/
int SoPlex_optimize(void* soplex, volatile bool* interrupt);

/** returns the current solver status **/
int SoPlex_getStatus(void* soplex);

/** returns the time spent in last call to solve **/
double SoPlex_getSolvingTime(void* soplex);

/** returns the number of iteration in last call to solve **/
int SoPlex_getNumIterations(void* soplex);

/** changes objective function vector to obj **/
void SoPlex_changeObjReal(void* soplex, double* obj, int dim);

/** changes rational objective function vector to obj **/
void SoPlex_changeObjRational(void* soplex, SoPlex_RatIntType* objnums, SoPlex_RatIntType* objdenoms, int dim);

/** changes left-hand side vector for constraints to lhs **/
void SoPlex_changeLhsReal(void* soplex, double* lhs, int dim);

/** changes left-hand side of a row to lhs **/
void SoPlex_changeRowLhsReal(void* soplex, int rowidx, double lhs);

/** changes rational left-hand side vector for constraints to lhs **/
void SoPlex_changeLhsRational(void* soplex, SoPlex_RatIntType* lhsnums, SoPlex_RatIntType* lhsdenoms, int dim);

/** changes right-hand side vector for constraints to rhs **/
void SoPlex_changeRhsReal(void* soplex, double* rhs, int dim);

/** changes right-hand side of a row to rhs **/
void SoPlex_changeRowRhsReal(void* soplex, int rowidx, double rhs);

/** changes rational right-hand side vector for constraints to rhs **/
void SoPlex_changeRhsRational(void* soplex, SoPlex_RatIntType* rhsnums, SoPlex_RatIntType* rhsdenoms, int dim);

/** changes both sides for constraints to given lhs and rhs **/
void SoPlex_changeRangeReal(void* soplex, double* lhs, double* rhs, int dim);

/** changes both sides of a row to given lhs and rhs **/
void SoPlex_changeRowRangeReal(void* soplex, int rowidx, double lhs, double rhs);

/** returns the objective value if a primal solution is available **/
double SoPlex_objValueReal(void* soplex);

/** Returns the rational objective value (as a string) if a primal solution is available.
*   The caller needs to ensure the char array is freed.
**/
char* SoPlex_objValueRationalString(void* soplex);

/** changes vectors of column bounds to lb and ub **/
void SoPlex_changeBoundsReal(void* soplex, double* lb, double* ub, int dim);

/** changes bounds of a column to lb and ub **/
void SoPlex_changeVarBoundsReal(void* soplex, int colidx, double lb, double ub);

/** changes rational bounds of a column to lbnum/lbdenom and ubnum/ubdenom **/
void SoPlex_changeVarBoundsRational(void* soplex, int colidx, SoPlex_RatIntType lbnum, SoPlex_RatIntType lbdenom, 
                                    SoPlex_RatIntType ubnum, SoPlex_RatIntType ubdenom);

/** changes vector of lower bounds to lb **/
void SoPlex_changeLowerReal(void* soplex, double* lb, int dim);

/** changes lower bound of column to lb **/
void SoPlex_changeVarLowerReal(void* soplex, int colidx, double lb);

/** gets lower bound vector of columns into lb **/
void SoPlex_getLowerReal(void* soplex, double* lb, int dim);

/** gets objective vector into obj **/
void SoPlex_getObjReal(void* soplex, double* obj, int dim);

/** changes vector of upper bounds to ub **/
void SoPlex_changeUpperReal(void* soplex, double* ub, int dim);

/** changes upper bound of column to ub **/
void SoPlex_changeVarUpperReal(void* soplex, int colidx, double ub);

/** gets upper bound vector of columns into ub **/
void SoPlex_getUpperReal(void* soplex, double* ub, int dim);


/** is stored primal solution feasible? */
bool SoPlex_isPrimalFeasible(void* soplex);

/** is a solution available (not neccessarily feasible)? */
bool SoPlex_hasSol(void* soplex);

/** is a primal unbounded ray available? */
bool SoPlex_hasPrimalRay(void* soplex);

/** is stored dual solution feasible? */
bool SoPlex_isDualFeasible(void* soplex);

/** is Farkas proof of infeasibility available? */
bool SoPlex_hasDualFarkas(void* soplex);

/** returns status of row */
SoPlex_VarStatusEnum SoPlex_basisRowStatus(void* soplex, int rowidx);

/** returns status of column */
SoPlex_VarStatusEnum SoPlex_basisColStatus(void* soplex, int colidx);

/** get non-zero entries and indices of row i **/
void SoPlex_getRowVectorReal(void* soplex, int i, int* nnonzeros, long* indices, double* coefs);

/** get non-zero entries and indices of rational row i **/
void SoPlex_getRowVectorRational(void* soplex, int i, int* nnonzeros, long* indices, SoPlex_RatIntType* coefsnum,
                                 SoPlex_RatIntType* coefsdenom);

/** get lower and upper bounds of row i **/
void SoPlex_getRowBoundsReal(void* soplex, int i, double* lb, double* ub);

/** get rational lower and upper bounds of row i **/
void SoPlex_getRowBoundsRational(void* soplex, int i, SoPlex_RatIntType* lbnum, SoPlex_RatIntType* lbdenom, 
                                SoPlex_RatIntType* ubnum, SoPlex_RatIntType* ubdenom);

#ifdef __cplusplus
}
#endif

#endif /* _SOPLEX_C_INTERFACE_H_ */
