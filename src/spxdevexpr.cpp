/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the class library                   */
/*       SoPlex --- the Sequential object-oriented simPlex.                  */
/*                                                                           */
/*    Copyright (C) 1997-1999 Roland Wunderling                              */
/*                  1997-2001 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*  SoPlex is distributed under the terms of the ZIB Academic Licence.       */
/*                                                                           */
/*  You should have received a copy of the ZIB Academic License              */
/*  along with SoPlex; see the file COPYING. If not email to soplex@zib.de.  */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma ident "@(#) $Id: spxdevexpr.cpp,v 1.4 2001/11/27 10:31:30 bzfbleya Exp $"

/*      \Section{Complex Methods}
 */

/*  Import system include files
 */
#include <stdlib.h>
#include <iostream>


/*  and class header files
 */
#include "spxdevexpr.h"

namespace soplex
{


//@ ----------------------------------------------------------------------------
/*  \Section{Miscellanous Methods}
 */
void SPxDevexPR::load(SoPlex* base)
{
   thesolver = base;
   setRep(base->rep());
   assert(isConsistent());
}

int SPxDevexPR::isConsistent() const
{
   if (thesolver != 0)
   {
      if (penalty.dim() != thesolver->coDim()
           || coPenalty.dim() != thesolver->dim())
      {
         std::cerr << "ERROR: inconsistency detected in class SPxDevex\n";
         return 0;
      }
   }
   return 1;
}

void SPxDevexPR::setType(SoPlex::Type tp)
{
   int i;
   if (tp == SoPlex::ENTER)
   {
      for (i = penalty.dim(); --i >= 0;)
         penalty[i] = 2;
      for (i = coPenalty.dim(); --i >= 0;)
         coPenalty[i] = 2;
   }
   else
   {
      for (i = coPenalty.dim(); --i >= 0;)
         coPenalty[i] = 1;
   }
   assert(isConsistent());
}

/**@todo suspicious: Shouldn't the relation between dim, coDim, Vecs, and CoVecs be influenced by the representation ?
 */
void SPxDevexPR::setRep(SoPlex::Representation rep)
{
   if (thesolver)
   {
      addedVecs(thesolver->coDim());
      addedCoVecs(thesolver->dim());
      assert(isConsistent());
   }
}

int SPxDevexPR::selectLeave()
{
   double val;
   return selectLeave(val);
}

int SPxDevexPR::selectLeave(double& best, int start, int incr)
{
   double x;

   const double* fTest = thesolver->fTest().get_const_ptr();
   const double* cpen = coPenalty.get_const_ptr();
   double bstX = 0;
   int bstI = -1;
   int end = coPenalty.dim();

   for (; start < end; start += incr)
   {
      if (fTest[start] < -theeps)
      {
         x = fTest[start] * fTest[start] / cpen[start];
         if (x > bstX)
         {
            bstX = x;
            bstI = start;
            last = cpen[start];
         }
      }
   }

   best = bstX;
   return bstI;
}

void SPxDevexPR::left4(int n, SoPlex::Id id)
{
   left4(n, id, 0, 1);
}

void SPxDevexPR::left4(int n, SoPlex::Id id, int start, int incr)
{
   if (id.isValid())
   {
      int i, j;
      double x;
      const double* rhoVec = thesolver->fVec().delta().values();
      double rhov_1 = 1 / rhoVec[n];
      double beta_q = thesolver->coPvec().delta().length2()
                      * rhov_1 * rhov_1;

      assert(rhoVec[n] >= theeps || -rhoVec[n] >= theeps);

      //  Update #coPenalty# vector
      const IdxSet& rhoIdx = thesolver->fVec().idx();
      int len = thesolver->fVec().idx().size();
      for (i = len - 1 - start; i >= 0; i -= incr)
      {
         j = rhoIdx.index(i);
         x = rhoVec[j] * rhoVec[j] * beta_q;
         // if(x > coPenalty[j])
         coPenalty[j] += x;
      }

      coPenalty[n] = beta_q;
   }
}

SoPlex::Id SPxDevexPR::selectEnter()
{
   double val;
   return selectEnter(val);
}

SoPlex::Id SPxDevexPR::selectEnter(
   double& best,
   int start1,
   int incr1,
   int start2,
   int incr2
)
{
   double x;

   const double* test = thesolver->test().get_const_ptr();
   const double* cTest = thesolver->coTest().get_const_ptr();
   const double* cpen = coPenalty.get_const_ptr();
   const double* pen = penalty.get_const_ptr();
   double bstX1 = 0;
   double bstX2 = 0;
   int bstI1 = -1;
   int bstI2 = -1;
   int end1 = coPenalty.dim();
   int end2 = penalty.dim();

   assert(end1 == thesolver->coTest().dim());
   assert(end2 == thesolver->test().dim());

   for (; start1 < end1; start1 += incr1)
   {
      if (cTest[start1] < -theeps)
      {
         x = cTest[start1] * cTest[start1] / cpen[start1];
         if (x > bstX1)
         {
            bstX1 = x;
            bstI1 = start1;
            last = cpen[start1];
         }
      }
   }

   for (; start2 < end2; start2 += incr2)
   {
      if (test[start2] < -theeps)
      {
         x = test[start2] * test[start2] / pen[start2];
         if (x > bstX2)
         {
            bstX2 = x;
            bstI2 = start2;
            last = pen[start2];
         }
      }
   }

   if (bstI2 >= 0)
   {
      best = bstX2;
      return thesolver->id(bstI2);
   }

   if (bstI1 >= 0)
   {
      best = bstX1;
      return thesolver->coId(bstI1);
   }

   SoPlex::Id none;
   return none;
}

void SPxDevexPR::entered4(SoPlex::Id id, int n)
{
   entered4(id, n, 0, 1, 0, 1);
}

/**@todo suspicious: the pricer should be informed, that variable id has entered the basis at position n, but the id is not used here (this is true
                     for all pricers)
*/
void SPxDevexPR::entered4(SoPlex::Id /*id*/, int n,
                          int start1, int incr1, int start2, int incr2)
{
   if (n >= 0 && n < thesolver->dim())
   {
      const double* pVec = thesolver->pVec().delta().values();
      const IdxSet& pIdx = thesolver->pVec().idx();
      const double* coPvec = thesolver->coPvec().delta().values();
      const IdxSet& coPidx = thesolver->coPvec().idx();
      double xi_p = 1 / thesolver->fVec().delta()[n];
      int i, j;

      assert(thesolver->fVec().delta()[n] > thesolver->epsilon()
              || thesolver->fVec().delta()[n] < -thesolver->epsilon());

      xi_p = xi_p * xi_p * last;

      for (j = coPidx.size() - 1 - start1; j >= 0; j -= incr1)
      {
         i = coPidx.index(j);
         coPenalty[i] += xi_p * coPvec[i] * coPvec[i];
         if (coPenalty[i] <= 1 || coPenalty[i] > 1e+6)
         {
            setType(SoPlex::ENTER);
            return;
         }
      }

      for (j = pIdx.size() - 1 - start2; j >= 0; j -= incr2)
      {
         i = pIdx.index(j);
         penalty[i] += xi_p * pVec[i] * pVec[i];
         if (penalty[i] <= 1 || penalty[i] > 1e+6)
         {
            setType(SoPlex::ENTER);
            return;
         }
      }
   }
}

void SPxDevexPR::addedVecs (int n)
{
   int init = (thesolver->type() == SoPlex::ENTER) + 1;
   penalty.reDim (thesolver->coDim());
   n -= penalty.dim();
   for (int i = penalty.dim(); --i >= n;)
      penalty[i] = init;
}

void SPxDevexPR::addedCoVecs(int n)
{
   int init = (thesolver->type() == SoPlex::ENTER) + 1;
   coPenalty.reDim(thesolver->dim());
   n -= coPenalty.dim();
   for (int i = coPenalty.dim(); --i >= n;)
      coPenalty[i] = init;
}

void SPxDevexPR::removedVec(int /*i*/)
{}


void SPxDevexPR::removedCoVec(int /*i*/)
{}


void SPxDevexPR::removedCoVecs(const int * /*perm[]*/)
{}


void SPxDevexPR::removedVecs(const int * /*perm[]*/)
{}
} // namespace soplex

//-----------------------------------------------------------------------------
//Emacs Local Variables:
//Emacs mode:c++
//Emacs c-basic-offset:3
//Emacs tab-width:8
//Emacs indent-tabs-mode:nil
//Emacs End:
//-----------------------------------------------------------------------------
