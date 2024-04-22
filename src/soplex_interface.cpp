#include "soplex.h"
#include "soplex_enumerations.h"
#include "soplex_interface.h"
#include <iostream>

using namespace soplex;

/** creates new SoPlex struct **/
void* SoPlex_create()
{
   SoPlex* so = new SoPlex();
   return so;
}

/** frees SoPlex struct **/
void SoPlex_free(void* soplex)
{
   SoPlex* so = (SoPlex*)(soplex);
   delete so;
}

/** reads LP file in LP or MPS format according to READMODE parameter; returns true on success **/
bool SoPlex_readInstanceFile(void* soplex, const char* filename)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->readFile(filename);
}

/** reads basis information from filename and returns true on success **/
bool SoPlex_readBasisFile(void* soplex, const char* filename)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->readBasisFile(filename);
}

/** reads settings from filename and returns true on success **/
bool SoPlex_readSettingsFile(void* soplex, const char* filename)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->loadSettingsFile(filename);
}


/** writes real LP to file; LP or MPS format is chosen from the extension in \p filename; returns true on success */
bool SoPlex_writeInstanceFileReal(void* soplex, const char* filename)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->writeFileReal(filename);
}

/** writes rational LP to file; LP or MPS format is chosen from the extension in \p filename; returns true on success */
bool SoPlex_writeInstanceFileRational(void* soplex, const char* filename)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->writeFileRational(filename);
}

/** writes dual of real LP to file; LP or MPS format is chosen from the extension in \p filename; returns true on success */
bool SoPlex_writeDualFileReal(void* soplex, const char* filename)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->writeDualFileReal(filename);
}

/** writes basis information to \p filename; returns true on success */
bool SoPlex_writeBasisFile(void* soplex, const char* filename)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->writeBasisFile(filename);
}

/** writes internal LP, basis information, and parameter settings */
void SoPlex_writeStateFileReal(void* soplex, const char* filename)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->writeStateReal(filename);
}

/** writes internal LP, basis information, and parameter settings */
void SoPlex_writeStateFileRational(void* soplex, const char* filename)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->writeStateRational(filename);
}



/** clears the (floating point) LP **/
void SoPlex_clearLPReal(void* soplex)
{
   SoPlex* so = (SoPlex*)(soplex);
   so->clearLPReal();
}

/** returns number of rows **/
int SoPlex_numRows(void* soplex)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->numRows();
}

/** returns number of columns **/
int SoPlex_numCols(void* soplex)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->numCols();
}

/** enables rational solving mode **/
void SoPlex_setRational(void* soplex)
{
#ifndef SOPLEX_WITH_BOOST
   throw SPxException("Rational functions cannot be used when built without Boost.");
#endif
   /* coverity[unreachable] */
   SoPlex* so = (SoPlex*)(soplex);
   so->setIntParam(SoPlex::READMODE, SoPlex::READMODE_RATIONAL);
   so->setIntParam(SoPlex::SOLVEMODE, SoPlex::SOLVEMODE_RATIONAL);
   so->setIntParam(SoPlex::CHECKMODE, SoPlex::CHECKMODE_RATIONAL);
   so->setIntParam(SoPlex::SYNCMODE, SoPlex::SYNCMODE_AUTO);
   so->setRealParam(SoPlex::FEASTOL, 0.0);
   so->setRealParam(SoPlex::OPTTOL, 0.0);
}

/** sets boolean parameter value **/
bool SoPlex_setBoolParam(void* soplex, SoPlex_BoolParamEnum paramcode, bool paramvalue)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->setBoolParam((SoPlex::BoolParam)paramcode, paramvalue);
}

/** sets integer parameter value **/
bool SoPlex_setIntParam(void* soplex, SoPlex_IntParamEnum paramcode, int paramvalue)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->setIntParam((SoPlex::IntParam)paramcode, paramvalue);
}

/** sets real parameter value **/
bool SoPlex_setRealParam(void* soplex, SoPlex_RealParamEnum paramcode, double paramvalue)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->setRealParam((SoPlex::RealParam)paramcode, paramvalue);
}

/** returns value of boolean parameter **/
bool SoPlex_getBoolParam(void* soplex, SoPlex_BoolParamEnum paramcode)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->boolParam((SoPlex::BoolParam)paramcode);
}

/** returns value of integer parameter **/
int SoPlex_getIntParam(void* soplex, SoPlex_IntParamEnum paramcode)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->intParam((SoPlex::IntParam)paramcode);
}

/** returns value of real parameter **/
double SoPlex_getRealParam(void* soplex, SoPlex_RealParamEnum paramcode)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->realParam((SoPlex::RealParam)paramcode);
}

/** adds a single (floating point) column **/
void SoPlex_addColReal(void* soplex, double* colentries, int colsize, int nnonzeros, double objval,
                       double lb, double ub)
{
   SoPlex* so = (SoPlex*)(soplex);
   DSVector col(nnonzeros);

   /* add nonzero entries to column vector */
   for(int i = 0; i < colsize; ++i)
   {
      if(colentries[i] != 0.0)
         col.add(i, colentries[i]);
   }

   so->addColReal(LPCol(objval, col, ub, lb));
}

/** removes a single (floating point) column **/
void SoPlex_removeColReal(void* soplex, int colidx)
{
   SoPlex* so = (SoPlex*)(soplex);
   so->removeColReal(colidx);
}

/** adds a single rational column **/
void SoPlex_addColRational(void* soplex, SoPlex_RatIntType* colnums, SoPlex_RatIntType* coldenoms, int colsize, int nnonzeros,
                           SoPlex_RatIntType objvalnum, SoPlex_RatIntType objvaldenom, SoPlex_RatIntType lbnum, SoPlex_RatIntType lbdenom, SoPlex_RatIntType ubnum, SoPlex_RatIntType ubdenom)
{
#ifndef SOPLEX_WITH_BOOST
   throw SPxException("Rational functions cannot be used when built without Boost.");
#endif
   /* coverity[unreachable] */
   SoPlex* so = (SoPlex*)(soplex);
   DSVectorRational col(nnonzeros);

   /* get rational lower bound */
   Rational lower(lbnum, lbdenom);

   /* get rational upper bound */
   Rational upper(ubnum, ubdenom);

   /* get rational objective value */
   Rational objval(objvalnum, objvaldenom);

   /* add nonzero entries to column vector */
   for(int i = 0; i < colsize; ++i)
   {
      if(colnums[i] != 0)
      {
         /* get rational nonzero entry */
         Rational colentry(colnums[i], coldenoms[i]);
         col.add(i, colentry);
      }
   }

   so->addColRational(LPColRational(objval, col, upper, lower));
}

/** removes a single (floating point) column **/
void SoPlex_removeColRational(void* soplex, int colidx)
{
#ifndef SOPLEX_WITH_BOOST
   throw SPxException("Rational functions cannot be used when built without Boost.");
#endif
   /* coverity[unreachable] */
   SoPlex* so = (SoPlex*)(soplex);
   so->removeColRational(colidx);
}

/** adds a single (floating point) row **/
void SoPlex_addRowReal(void* soplex, double* rowentries, int rowsize, int nnonzeros, double lb,
                       double ub)
{
   SoPlex* so = (SoPlex*)(soplex);
   DSVector row(nnonzeros);

   /* add nonzero entries to row vector */
   for(int i = 0; i < rowsize; ++i)
   {
      if(rowentries[i] != 0.0)
         row.add(i, rowentries[i]);
   }

   so->addRowReal(LPRow(lb, row, ub));
}

/** removes a single (floating point) row **/
void SoPlex_removeRowReal(void* soplex, int rowidx)
{
   SoPlex* so = (SoPlex*)(soplex);
   so->removeRowReal(rowidx);
}

/** adds a single rational row **/
void SoPlex_addRowRational(void* soplex, SoPlex_RatIntType* rownums, SoPlex_RatIntType* rowdenoms, int rowsize, int nnonzeros,
                           SoPlex_RatIntType lbnum, SoPlex_RatIntType lbdenom, SoPlex_RatIntType ubnum, SoPlex_RatIntType ubdenom)
{
#ifndef SOPLEX_WITH_BOOST
   throw SPxException("Rational functions cannot be used when built without Boost.");
#endif
   /* coverity[unreachable] */
   SoPlex* so = (SoPlex*)(soplex);
   DSVectorRational row(nnonzeros);

   /* get rational lower bound */
   Rational lower(lbnum, lbdenom);

   /* get rational upper bound */
   Rational upper(ubnum, ubdenom);

   /* add nonzero entries to row vector */
   for(int i = 0; i < rowsize; ++i)
   {
      if(rownums[i] != 0)
      {
         /* get rational nonzero entry */
         Rational rowentry(rownums[i], rowdenoms[i]);
         row.add(i, rowentry);
      }
   }

   so->addRowRational(LPRowRational(lower, row, upper));
}

/** removes a single (floating point) row **/
void SoPlex_removeRowRational(void* soplex, int rowidx)
{
#ifndef SOPLEX_WITH_BOOST
   throw SPxException("Rational functions cannot be used when built without Boost.");
#endif
   /* coverity[unreachable] */
   SoPlex* so = (SoPlex*)(soplex);
   so->removeRowRational(rowidx);
}

/** gets primal solution **/
void SoPlex_getPrimalReal(void* soplex, double* primal, int dim)
{
   SoPlex* so = (SoPlex*)(soplex);
   so->getPrimalReal(primal, dim);
}

/** Returns rational primal solution in a char pointer.
*   The caller needs to ensure the char array is freed.
**/
char* SoPlex_getPrimalRationalString(void* soplex, int dim)
{
#ifndef SOPLEX_WITH_BOOST
   throw SPxException("Rational functions cannot be used when built without Boost.");
#endif
   /* coverity[unreachable] */
   SoPlex* so = (SoPlex*)(soplex);
   VectorRational primal(dim);
   std::string primalstring;
   char* rawstring;
   long unsigned int stringlength;

   so->getPrimalRational(primal);

   for(int i = 0; i < dim; ++i)
   {
      primalstring.append(primal[i].str());
      primalstring.append(" ");
   }

   stringlength = strlen(primalstring.c_str()) + 1;
   rawstring = new char[stringlength];
   strncpy(rawstring, primalstring.c_str(), stringlength);
   return rawstring;
}

/** gets dual solution **/
void SoPlex_getDualReal(void* soplex, double* dual, int dim)
{
   SoPlex* so = (SoPlex*)(soplex);
   so->getDualReal(dual, dim);
}

/** gets reduced cost vector **/
void SoPlex_getRedCostReal(void* soplex, double* rc, int dim)
{
   SoPlex* so = (SoPlex*)(soplex);
   so->getRedCostReal(rc, dim);
}

/** optimizes the given LP **/
int SoPlex_optimize(void* soplex)
{
   bool interruption = false;
   SoPlex* so = (SoPlex*)(soplex);
   return so->optimize(&interruption);
}
int SoPlex_optimize2(void* soplex, volatile bool* interrupt)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->optimize(interrupt);
}

/** returns the current solver status **/
int SoPlex_getStatus(void* soplex)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->status();
}

/** returns the time spent in last call to solve **/
double SoPlex_getSolvingTime(void* soplex)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->solveTime();
}

/** returns the number of iteration in last call to solve **/
int SoPlex_getNumIterations(void* soplex)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->numIterations();
}

/** changes objective function vector to obj **/
void SoPlex_changeObjReal(void* soplex, double* obj, int dim)
{
   SoPlex* so = (SoPlex*)(soplex);
   Vector objective(dim, obj);
   so->changeObjReal(objective);
}

/** changes rational objective function vector to obj **/
void SoPlex_changeObjRational(void* soplex, SoPlex_RatIntType* objnums, SoPlex_RatIntType* objdenoms, int dim)
{
#ifndef SOPLEX_WITH_BOOST
   throw SPxException("Rational functions cannot be used when built without Boost.");
#endif
   /* coverity[unreachable] */
   SoPlex* so = (SoPlex*)(soplex);
   Rational* objrational = new Rational [dim];

   /* create rational objective vector */
   for(int i = 0; i < dim; ++i)
   {
      Rational objentry(objnums[i], objdenoms[i]);
      objrational[i] = objentry;
   }

   VectorRational objective(dim, objrational);
   so->changeObjRational(objective);
}

/** changes left-hand side vector for constraints to lhs **/
void SoPlex_changeLhsReal(void* soplex, double* lhs, int dim)
{
   SoPlex* so = (SoPlex*)(soplex);
   Vector lhsvec(dim, lhs);
   so->changeLhsReal(lhsvec);
}

/** changes left-hand side of a row to lhs **/
void SoPlex_changeRowLhsReal(void* soplex, int rowidx, double lhs)
{
   SoPlex* so = (SoPlex*)(soplex);
   so->changeLhsReal(rowidx, lhs);
}

/** changes rational left-hand side vector for constraints to lhs **/
void SoPlex_changeLhsRational(void* soplex, SoPlex_RatIntType* lhsnums, SoPlex_RatIntType* lhsdenoms, int dim)
{
#ifndef SOPLEX_WITH_BOOST
   throw SPxException("Rational functions cannot be used when built without Boost.");
#endif
   /* coverity[unreachable] */
   SoPlex* so = (SoPlex*)(soplex);
   Rational* lhsrational = new Rational [dim];

   /* create rational lhs vector */
   for(int i = 0; i < dim; ++i)
   {
      Rational lhsentry(lhsnums[i], lhsdenoms[i]);
      lhsrational[i] = lhsentry;
   }

   VectorRational lhs(dim, lhsrational);
   so->changeLhsRational(lhs);
}

/** changes right-hand side vector for constraints to rhs **/
void SoPlex_changeRhsReal(void* soplex, double* rhs, int dim)
{
   SoPlex* so = (SoPlex*)(soplex);
   Vector rhsvec(dim, rhs);
   so->changeRhsReal(rhsvec);
}

/** changes right-hand side of a row to rhs **/
void SoPlex_changeRowRhsReal(void* soplex, int rowidx, double rhs)
{
   SoPlex* so = (SoPlex*)(soplex);
   so->changeRhsReal(rowidx, rhs);
}

/** changes both sides for constraints to given lhs and rhs **/
void SoPlex_changeRangeReal(void* soplex, double* lhs, double* rhs, int dim)
{
   SoPlex* so = (SoPlex*)(soplex);
   Vector lhsvec(dim, lhs);
   Vector rhsvec(dim, rhs);
   so->changeRangeReal(lhsvec, rhsvec);
}

/** changes both sides of a row to given lhs and rhs **/
void SoPlex_changeRowRangeReal(void* soplex, int rowidx, double lhs, double rhs)
{
   SoPlex* so = (SoPlex*)(soplex);
   so->changeRangeReal(rowidx, lhs, rhs);
}

/** changes rational right-hand side vector for constraints to rhs **/
void SoPlex_changeRhsRational(void* soplex, SoPlex_RatIntType* rhsnums, SoPlex_RatIntType* rhsdenoms, int dim)
{
#ifndef SOPLEX_WITH_BOOST
   throw SPxException("Rational functions cannot be used when built without Boost.");
#endif
   /* coverity[unreachable] */
   SoPlex* so = (SoPlex*)(soplex);
   Rational* rhsrational = new Rational [dim];

   /* create rational rhs vector */
   for(int i = 0; i < dim; ++i)
   {
      Rational rhsentry(rhsnums[i], rhsdenoms[i]);
      rhsrational[i] = rhsentry;
   }

   VectorRational rhs(dim, rhsrational);
   so->changeRhsRational(rhs);
}


/** is stored primal solution feasible? */
bool SoPlex_isPrimalFeasible(void* soplex)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->isPrimalFeasible();
}

/** is a solution available (not neccessarily feasible)? */
bool SoPlex_hasSol(void* soplex)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->hasSol();
}

/** is a primal unbounded ray available? */
bool SoPlex_hasPrimalRay(void* soplex)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->hasPrimalRay();
}

/** is stored dual solution feasible? */
bool SoPlex_isDualFeasible(void* soplex)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->isDualFeasible();
}

/** is Farkas proof of infeasibility available? */
bool SoPlex_hasDualFarkas(void* soplex)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->hasDualFarkas();
}


/** returns the objective value if a primal solution is available **/
double SoPlex_objValueReal(void* soplex)
{
   SoPlex* so = (SoPlex*)(soplex);
   return so->objValueReal();
}

/** Returns the rational objective value (as a string) if a primal solution is available.
*   The caller needs to ensure the char array is freed.
**/
char* SoPlex_objValueRationalString(void* soplex)
{
#ifndef SOPLEX_WITH_BOOST
   throw SPxException("Rational functions cannot be used when built without Boost.");
#endif
   /* coverity[unreachable] */
   long unsigned int stringlength;
   char* value;
   std::string objstring;
   SoPlex* so = (SoPlex*)(soplex);

   objstring = so->objValueRational().str();
   stringlength = strlen(objstring.c_str()) + 1;
   value = new char[stringlength];
   strncpy(value, objstring.c_str(), stringlength);
   return value;
}

/** changes vectors of column bounds to lb and ub **/
void SoPlex_changeBoundsReal(void* soplex, double* lb, double* ub, int dim)
{
   SoPlex* so = (SoPlex*)(soplex);
   Vector lbvec(dim, lb);
   Vector ubvec(dim, ub);
   so->changeBoundsReal(lbvec, ubvec);
}

/** changes bounds of a column to lb and ub **/
void SoPlex_changeVarBoundsReal(void* soplex, int colidx, double lb, double ub)
{
   SoPlex* so = (SoPlex*)(soplex);
   so->changeBoundsReal(colidx, lb, ub);
}

/** changes rational bounds of a column to lbnum/lbdenom and ubnum/ubdenom **/
void SoPlex_changeVarBoundsRational(void* soplex, int colidx, SoPlex_RatIntType lbnum, SoPlex_RatIntType lbdenom, SoPlex_RatIntType ubnum,
                                    SoPlex_RatIntType ubdenom)
{
#ifndef SOPLEX_WITH_BOOST
   throw SPxException("Rational functions cannot be used when built without Boost.");
#endif
   /* coverity[unreachable] */
   SoPlex* so = (SoPlex*)(soplex);

   /* get rational lower bound */
   Rational lower(lbnum, lbdenom);

   /* get rational upper bound */
   Rational upper(ubnum, ubdenom);

   so->changeBoundsRational(colidx, lower, upper);
}

/** changes vector of lower bounds to lb **/
void SoPlex_changeLowerReal(void* soplex, double* lb, int dim)
{
   SoPlex* so = (SoPlex*)(soplex);
   Vector lbvec(dim, lb);
   so->changeLowerReal(lbvec);
}

/** changes lower bound of column to ub **/
void SoPlex_changeVarLowerReal(void* soplex, int colidx, double lb)
{
   SoPlex* so = (SoPlex*)(soplex);
   so->changeLowerReal(colidx, lb);
}

/** gets lower bound vector of columns into lb **/
void SoPlex_getLowerReal(void* soplex, double* lb, int dim)
{
   SoPlex* so = (SoPlex*)(soplex);
   Vector lbvec(dim);

   so->getLowerReal(lbvec);

   for(int i = 0; i < dim; ++i)
      lb[i] = lbvec[i];
}

/** gets objective vector into obj **/
void SoPlex_getObjReal(void* soplex, double* obj, int dim)
{
   SoPlex* so = (SoPlex*)(soplex);
   Vector objvec(dim);

   so->getObjReal(objvec);

   for(int i = 0; i < dim; ++i)
      obj[i] = objvec[i];
}

/** changes vector of upper bounds to ub **/
void SoPlex_changeUpperReal(void* soplex, double* ub, int dim)
{
   SoPlex* so = (SoPlex*)(soplex);
   Vector ubvec(dim, ub);
   so->changeUpperReal(ubvec);
}

/** changes upper bound of column to ub **/
void SoPlex_changeVarUpperReal(void* soplex, int colidx, double ub)
{
   SoPlex* so = (SoPlex*)(soplex);
   so->changeUpperReal(colidx, ub);
}

/** gets upper bound vector of columns into ub **/
void SoPlex_getUpperReal(void* soplex, double* ub, int dim)
{
   SoPlex* so = (SoPlex*)(soplex);
   Vector ubvec(dim);

   so->getUpperReal(ubvec);

   for(int i = 0; i < dim; ++i)
      ub[i] = ubvec[i];
}

/** returns status of row */
SoPlex_VarStatusEnum SoPlex_basisRowStatus(void* soplex, int rowidx)
{
   SoPlex* so = (SoPlex*)(soplex);

   return (SoPlex_VarStatusEnum)(so->basisRowStatus(rowidx));
}

/** returns status of column */
SoPlex_VarStatusEnum SoPlex_basisColStatus(void* soplex, int colidx)
{
   SoPlex* so = (SoPlex*)(soplex);

   return (SoPlex_VarStatusEnum)(so->basisColStatus(colidx));
}

/** get non-zero entries and indices of row i **/
void SoPlex_getRowVectorReal(void* soplex, int i, int* nnonzeros, long* indices, double* coefs)
{
   SoPlex* so = (SoPlex*)(soplex);
   DSVector row;

   so->getRowVectorReal(i, row);

   *nnonzeros = row.size();

   for(int j = 0; j < *nnonzeros; ++j)
   {
      coefs[j] = row.value(j);
      indices[j] = row.index(j);
   }
}

/** get non-zero entries and indices of rational row i **/
void SoPlex_getRowVectorRational(void* soplex, int i, int* nnonzeros, long* indices, SoPlex_RatIntType* coefsnum,
                                 SoPlex_RatIntType* coefsdenom)
{
#ifndef SOPLEX_WITH_BOOST
   throw SPxException("Rational functions cannot be used when built without Boost.");
#else
   SoPlex* so = (SoPlex*)(soplex);
   LPRowRational lprow;
   SVectorRational row;

   so->getRowRational(i, lprow);
   row = lprow.rowVector();

   *nnonzeros = row.size();

   for(int j = 0; j < *nnonzeros; ++j)
   {
      coefsnum[j] = (SoPlex_RatIntType) numerator(row.value(j));
      coefsdenom[j] = (SoPlex_RatIntType) denominator(row.value(j));
      indices[j] = row.index(j);
   }

#endif
}

/** get lower and upper bounds of row i **/
void SoPlex_getRowBoundsReal(void* soplex, int i, double* lb, double* ub)
{
   SoPlex* so = (SoPlex*)(soplex);

   *lb = so->lhsReal(i);
   *ub = so->rhsReal(i);
}

/** get rational lower and upper bounds of row i **/
void SoPlex_getRowBoundsRational(void* soplex, int i, SoPlex_RatIntType* lbnum, SoPlex_RatIntType* lbdenom, SoPlex_RatIntType* ubnum,
                                 SoPlex_RatIntType* ubdenom)
{
#ifndef SOPLEX_WITH_BOOST
   throw SPxException("Rational functions cannot be used when built without Boost.");
#else
   SoPlex* so = (SoPlex*)(soplex);

   *lbnum = (SoPlex_RatIntType) numerator(so->lhsRational(i));
   *lbdenom = (SoPlex_RatIntType) denominator(so->lhsRational(i));
   *ubnum = (SoPlex_RatIntType) numerator(so->rhsRational(i));
   *ubdenom = (SoPlex_RatIntType) denominator(so->rhsRational(i));
#endif
}
