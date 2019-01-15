/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the class library                   */
/*       SoPlex --- the Sequential object-oriented simPlex.                  */
/*                                                                           */
/*    Copyright (C) 1996-2018 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*  SoPlex is distributed under the terms of the ZIB Academic Licence.       */
/*                                                                           */
/*  You should have received a copy of the ZIB Academic License              */
/*  along with SoPlex; see the file COPYING. If not email to soplex@zib.de.  */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file  updatevector.h
 * @brief Dense VectorBase<R> with semi-sparse VectorBase<R> for updates
 */

#ifndef _UPDATEVECTOR_H_
#define _UPDATEVECTOR_H_

#include <assert.h>


#include "soplex/spxdefines.h"
#include "soplex/dvector.h"
#include "soplex/ssvector.h"

namespace soplex
{

/**@brief   Dense VectorBase<R> with semi-sparse VectorBase<R> for updates
   @ingroup Algebra

    In many algorithms vectors are updated in every iteration, by
    adding a multiple of another VectorBase<R> to it, i.e., given a VectorBase<R> \c
    x, a scalar \f$\alpha\f$ and another VectorBase<R> \f$\delta\f$, the
    update to \c x constists of substituting it by \f$x \leftarrow x +
    \alpha\cdot\delta\f$.

    While the update itself can easily be expressed with methods of
    the class Vector, it is often desirable to save the last update
    VectorBase<R> \f$\delta\f$ and value \f$\alpha\f$. This is provided by
    class UpdateVector.

    UpdateVectors are derived from DVectorBase<R> and provide additional
    methods for saving and setting the multiplicator \f$\alpha\f$ and
    the update VectorBase<R> \f$\delta\f$. Further, it allows for efficient
    sparse updates, by providing an IdxSet idx() containing the
    nonzero indices of \f$\delta\f$.
*/
  template <class R>
  class UpdateVector : public DVectorBase<R>
{
private:

   //------------------------------------
   /**@name Data */
   //@{
   R     theval;      ///< update multiplicator
   SSVectorBase<R> thedelta;    ///< update vector
   //@}

public:

   //------------------------------------
   /**@name Constructors / destructors */
   //@{
   /// default constructor.
   explicit
   UpdateVector<R>(int p_dim /*=0*/, R p_eps /*=1e-16*/)
      : DVectorBase<R> (p_dim)
      , theval (0)
      , thedelta(p_dim, p_eps)
   {
      assert(isConsistent());
   }
   ///
   ~UpdateVector<R>()
   {}
   /// copy constructor
   UpdateVector<R>( const UpdateVector<R>& );
   /// assignment from DVector
   UpdateVector<R>& operator=(const DVectorBase<R>& rhs)
   {
      if ( this != & rhs )
        DVectorBase<R>::operator=(rhs);

      assert(isConsistent());

      return *this;
   }
   /// assignment from Vector
   UpdateVector<R>& operator=(const VectorBase<R>& rhs)
   {
      if ( this != & rhs )
        DVectorBase<R>::operator=(rhs);

      assert(isConsistent());

      return *this;
   }
   /// assignment
   UpdateVector<R>& operator=(const UpdateVector<R>& rhs);
   //@}

   //------------------------------------
   /**@name Access */
   //@{
   /// update multiplicator \f$\alpha\f$, writeable
   R& value()
   {
      return theval;
   }
   /// update multiplicator \f$\alpha\f$
   R value() const
   {
      return theval;
   }

   /// update VectorBase<R> \f$\delta\f$, writeable
   SSVectorBase<R>& delta()
   {
      return thedelta;
   }
   /// update VectorBase<R> \f$\delta\f$
   const SSVectorBase<R>& delta() const
   {
      return thedelta;
   }

   /// nonzero indices of update VectorBase<R> \f$\delta\f$
   const IdxSet& idx() const
   {
      return thedelta.indices();
   }
   //@}

   //------------------------------------
   /**@name Modification */
   //@{
   /// Perform the update
   /**  Add \c value() * \c delta() to the UpdateVector<R>. Only the indices
    *  in idx() are affected. For all other indices, delta() is asumed
    *  to be 0.
    */
   void update()
   {
      multAdd(theval, thedelta);
   }

   /// clear VectorBase<R> and update vector
   void clear()
   {
     DVectorBase<R>::clear();
      clearUpdate();
   }

   /// clear \f$\delta\f$, \f$\alpha\f$
   void clearUpdate()
   {
      thedelta.clear();
      theval = 0;
   }

   /// reset dimension
   void reDim(int newdim)
   {
     DVectorBase<R>::reDim(newdim);
      thedelta.reDim(newdim);
   }
   //@}

   //------------------------------------
   /**@name Consistency check */
   //@{
   ///
   bool isConsistent() const;
   //@}
};


} // namespace soplex
#endif // _UPDATEVECTOR_H_
