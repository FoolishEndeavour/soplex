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
#pragma ident "@(#) $Id: lpcolset.cpp,v 1.4 2001/12/25 16:03:24 bzfkocht Exp $"

#include <assert.h>

#include "lpcolset.h"
#include "spxmessage.h"

namespace soplex
{

void LPColSet::add
(
   Key& p_key,
   double p_obj,
   double p_lower,
   const SVector& p_colVector,
   double p_upper
)
{
   SVSet::add(p_key, p_colVector);
   if (num() > low.dim())
   {
      low.reDim (num());
      up.reDim (num());
      object.reDim (num());
   }
   low [num() - 1] = p_lower;
   up [num() - 1] = p_upper;
   object[num() - 1] = p_obj;
}

void LPColSet::add(const LPColSet& p_set)
{
   int i = num();

   SVSet::add(p_set);
   if (num() > low.dim())
   {
      low.reDim (num());
      up.reDim (num());
      object.reDim (num());
   }

   for (int j = 0; i < num(); ++i, ++j)
   {
      low [i] = p_set.lower(j);
      up [i] = p_set.upper(j);
      object[i] = p_set.obj(j);
   }
}

void LPColSet::add(Key nkey[], const LPColSet& p_set)
{
   int i = num();
   add(p_set);

   for (int j = 0; i < num(); ++i, ++j)
      nkey[j] = key(i);
}

SVector& LPColSet::create(Key& nkey, int nonzeros, double p_obj, double lhs, double rhs)
{
   if (num() + 1 > low.dim())
   {
      low.reDim (num() + 1);
      up.reDim (num() + 1);
      object.reDim (num() + 1);
   }
   low [num()] = lhs;
   up [num()] = rhs;
   object[num()] = p_obj;

   return *SVSet::create(nkey, nonzeros);
}


/*      \SubSection{Shrinking}
 */
void LPColSet::remove(int i)
{
   SVSet::remove(i);
   low[i] = low[num()];
   up[i] = up[num()];
   object[i] = object[num()];
   low.reDim (num());
   up.reDim (num());
   object.reDim(num());
}

void LPColSet::remove(int perm[])
{
   int i;
   int j = num();
   SVSet::remove(perm);
   for (i = 0; i < j; ++i)
   {
      if (perm[i] >= 0 && perm[i] != i)
      {
         low[perm[i]] = low[i];
         up[perm[i]] = up[i];
         object[perm[i]] = object[i];
      }
   }
   low.reDim (num());
   up.reDim (num());
   object.reDim(num());
}

void LPColSet::remove(int nums[], int n, int* perm)
{
   SVSet::remove(nums, n, perm);
   int i;
   int j = num();
   for (i = 0; i < j; ++i)
   {
      if (perm[i] >= 0 && perm[i] != i)
      {
         low[perm[i]] = low[i];
         up[perm[i]] = up[i];
         object[perm[i]] = object[i];
      }
   }
   low.reDim (num());
   up.reDim (num());
   object.reDim(num());
}

void LPColSet::clear()
{
   SVSet::clear();
   low.reDim (num());
   up.reDim (num());
   object.reDim(num());
}

int LPColSet::isConsistent() const
{
   if (low.dim() != object.dim())
      return SPXinconsistent("LPColSet");
   if (low.dim() != up.dim())
      return SPXinconsistent("LPColSet");
   if (low.dim() != num())
      return SPXinconsistent("LPColSet");

   return low.isConsistent() && up.isConsistent() && SVSet::isConsistent();
}
} // namespace soplex

//-----------------------------------------------------------------------------
//Emacs Local Variables:
//Emacs mode:c++
//Emacs c-basic-offset:3
//Emacs tab-width:8
//Emacs indent-tabs-mode:nil
//Emacs End:
//-----------------------------------------------------------------------------
