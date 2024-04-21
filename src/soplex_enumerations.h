
#ifndef _SOPLEX_C_ENUMERATIONS_H_
#define _SOPLEX_C_ENUMERATIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

   /// boolean parameters
   // copied from soplex .h
   typedef enum
   {
      /// should lifting be used to reduce range of nonzero matrix coefficients?
      LIFTING = 0,

      /// should LP be transformed to equality form before a rational solve?
      EQTRANS = 1,

      /// should dual infeasibility be tested in order to try to return a dual solution even if primal infeasible?
      TESTDUALINF = 2,

      /// should a rational factorization be performed after iterative refinement?
      RATFAC = 3,

      /// should cycling solutions be accepted during iterative refinement?
      ACCEPTCYCLING = 4,

      /// apply rational reconstruction after each iterative refinement?
      RATREC = 5,

      /// round scaling factors for iterative refinement to powers of two?
      POWERSCALING = 6,

      /// continue iterative refinement with exact basic solution if not optimal?
      RATFACJUMP = 7,

      /// use bound flipping also for row representation?
      ROWBOUNDFLIPS = 8,

      /// use persistent scaling?
      PERSISTENTSCALING = 9,

      /// perturb the entire problem or only the relevant bounds of s single pivot?
      FULLPERTURBATION = 10,

      /// re-optimize the original problem to get a proof (ray) of infeasibility/unboundedness?
      ENSURERAY = 11,

      /// try to enforce that the optimal solution is a basic solution
      FORCEBASIC = 12,

      // enable presolver SingletonCols in PaPILO?
      SIMPLIFIER_SINGLETONCOLS = 13,

      // enable presolver ConstraintPropagation in PaPILO?
      SIMPLIFIER_CONSTRAINTPROPAGATION = 14,

      // enable presolver ParallelRowDetection in PaPILO?
      SIMPLIFIER_PARALLELROWDETECTION = 15,

      // enable presolver ParallelColDetection in PaPILO?
      SIMPLIFIER_PARALLELCOLDETECTION = 16,

      // enable presolver SingletonStuffing in PaPILO?
      SIMPLIFIER_SINGLETONSTUFFING = 17,

      // enable presolver DualFix in PaPILO?
      SIMPLIFIER_DUALFIX = 18,

      // enable presolver FixContinuous in PaPILO?
      SIMPLIFIER_FIXCONTINUOUS = 19,

      // enable presolver DominatedCols in PaPILO?
      SIMPLIFIER_DOMINATEDCOLS = 20,

      // enable iterative refinement ?
      ITERATIVE_REFINEMENT = 21,

      /// adapt tolerances to the multiprecision used
      ADAPT_TOLS_TO_MULTIPRECISION = 22,

      /// enable precision boosting ?
      PRECISION_BOOSTING = 23,

      /// boosted solver start from last basis
      BOOSTED_WARM_START = 24,

      /// try different settings when solve fails
      RECOVERY_MECHANISM = 25,

      /// number of boolean parameters
      BOOLPARAM_COUNT = 26
   } SoPlex_BoolParamEnum;


   /// integer parameters
   // copied from soplex.h
   typedef enum
   {
      /// objective sense
      OBJSENSE = 0,

      /// type of computational form, i.e., column or row representation
      REPRESENTATION = 1,

      /// type of algorithm, i.e., primal or dual
      ALGORITHM = 2,

      /// type of LU update
      FACTOR_UPDATE_TYPE = 3,

      /// maximum number of updates without fresh factorization
      FACTOR_UPDATE_MAX = 4,

      /// iteration limit (-1 if unlimited)
      ITERLIMIT = 5,

      /// refinement limit (-1 if unlimited)
      REFLIMIT = 6,

      /// stalling refinement limit (-1 if unlimited)
      STALLREFLIMIT = 7,

      /// display frequency
      DISPLAYFREQ = 8,

      /// verbosity level
      VERBOSITY = 9,

      /// type of simplifier
      SIMPLIFIER = 10,

      /// type of scaler
      SCALER = 11,

      /// type of starter used to create crash basis
      STARTER = 12,

      /// type of pricer
      PRICER = 13,

      /// type of ratio test
      RATIOTESTER = 14,

      /// mode for synchronizing real and rational LP
      SYNCMODE = 15,

      /// mode for reading LP files
      READMODE = 16,

      /// mode for iterative refinement strategy
      SOLVEMODE = 17,

      /// mode for a posteriori feasibility checks
      CHECKMODE = 18,

      /// type of timer
      TIMER = 19,

      /// mode for hyper sparse pricing
      HYPER_PRICING = 20,

      /// minimum number of stalling refinements since last pivot to trigger rational factorization
      RATFAC_MINSTALLS = 21,

      /// maximum number of conjugate gradient iterations in least square scaling
      LEASTSQ_MAXROUNDS = 22,

      /// mode for solution polishing
      SOLUTION_POLISHING = 23,

      /// print condition number during the solve
      PRINTBASISMETRIC = 24,

      /// type of timer for statistics
      STATTIMER = 25,

      // maximum number of digits for the multiprecision type
      MULTIPRECISION_LIMIT = 26,

      ///@todo precision-boosting find better parameter name
      /// after how many simplex pivots do we store the advanced and stable basis, 1 = every iterations
      STORE_BASIS_SIMPLEX_FREQ = 27,

      /// number of integer parameters
      INTPARAM_COUNT = 28
   } SoPlex_IntParamEnum;

   /// values for parameter OBJSENSE
   // copied from soplex.h
   typedef enum
   {
      /// minimization
      OBJSENSE_MINIMIZE = -1,

      /// maximization
      OBJSENSE_MAXIMIZE = 1
   } SoPlex_SenseEnum;

   /// values for parameter REPRESENTATION
   typedef enum
   {
      /// automatic choice according to number of rows and columns
      REPRESENTATION_AUTO = 0,

      /// column representation Ax - s = 0, lower <= x <= upper, lhs <= s <= rhs
      REPRESENTATION_COLUMN = 1,

      /// row representation (lower,lhs) <= (x,Ax) <= (upper,rhs)
      REPRESENTATION_ROW = 2
   } SoPlex_RepresentationEnum;

   /// values for parameter ALGORITHM
   typedef enum
   {
      /// primal simplex algorithm, i.e., entering for column and leaving for row representation
      ALGORITHM_PRIMAL = 0,

      /// dual simplex algorithm, i.e., leaving for column and entering for row representation
      ALGORITHM_DUAL = 1
   } SoPlex_AlgorithmEnum;

   /// values for parameter FACTOR_UPDATE_TYPE
   typedef enum
   {
      /// product form update
      FACTOR_UPDATE_TYPE_ETA = 0,

      /// Forrest-Tomlin type update
      FACTOR_UPDATE_TYPE_FT = 1
   } SoPlex_FactorEnum;

   /// values for parameter VERBOSITY
   typedef enum
   {
      /// only error output
      VERBOSITY_ERROR = 0,

      /// only error and warning output
      VERBOSITY_WARNING = 1,

      /// only error, warning, and debug output
      VERBOSITY_DEBUG = 2,

      /// standard verbosity level
      VERBOSITY_NORMAL = 3,

      /// high verbosity level
      VERBOSITY_HIGH = 4,

      /// full verbosity level
      VERBOSITY_FULL = 5
   } SoPlex_VerbosityEnum;

   /// values for parameter SIMPLIFIER
   typedef enum
   {
      /// disabling presolving
      SIMPLIFIER_OFF = 0,

      /// using internal presolving methods
      SIMPLIFIER_INTERNAL = 3,

      /// using the presolve lib papilo
      SIMPLIFIER_PAPILO = 2,

      /// SoPlex chooses automatically (currently always "internal")
      SIMPLIFIER_AUTO = 1
   } SoPlex_SimplifierEmnum;

   /// values for parameter SCALER
   typedef enum
   {
      /// no scaler
      SCALER_OFF = 0,

      /// equilibrium scaling on rows or columns
      SCALER_UNIEQUI = 1,

      /// equilibrium scaling on rows and columns
      SCALER_BIEQUI = 2,

      /// geometric mean scaling on rows and columns, max 1 round
      SCALER_GEO1 = 3,

      /// geometric mean scaling on rows and columns, max 8 rounds
      SCALER_GEO8 = 4,

      /// least square scaling
      SCALER_LEASTSQ = 5,

      /// geometric mean scaling (max 8 rounds) followed by equilibrium scaling (rows and columns)
      SCALER_GEOEQUI = 6
   } SoPlex_ScalarEnum;

   /// values for parameter STARTER
   typedef enum
   {
      /// slack basis
      STARTER_OFF = 0,

      /// greedy crash basis weighted by objective, bounds, and sides
      STARTER_WEIGHT = 1,

      /// crash basis from a greedy solution
      STARTER_SUM = 2,

      /// generic solution-based crash basis
      STARTER_VECTOR = 3
   } SoPlex_StarterEnum;

   /// values for parameter PRICER
   typedef enum
   {
      /// automatic pricer
      PRICER_AUTO = 0,

      /// Dantzig pricer
      PRICER_DANTZIG = 1,

      /// partial multiple pricer based on Dantzig pricing
      PRICER_PARMULT = 2,

      /// devex pricer
      PRICER_DEVEX = 3,

      /// steepest edge pricer with initialization to unit norms
      PRICER_QUICKSTEEP = 4,

      /// steepest edge pricer with exact initialization of norms
      PRICER_STEEP = 5
   } SoPlex_PricerEnum;

   /// values for parameter RATIOTESTER
   typedef enum
   {
      /// textbook ratio test without stabilization
      RATIOTESTER_TEXTBOOK = 0,

      /// standard Harris ratio test
      RATIOTESTER_HARRIS = 1,

      /// modified Harris ratio test
      RATIOTESTER_FAST = 2,

      /// bound flipping ratio test for long steps in the dual simplex
      RATIOTESTER_BOUNDFLIPPING = 3
   } SoPlex_RatioTestEnum;

   /// values for parameter SYNCMODE
   typedef enum
   {
      /// store only real LP
      SYNCMODE_ONLYREAL = 0,

      /// automatic sync of real and rational LP
      SYNCMODE_AUTO = 1,

      /// user sync of real and rational LP
      SYNCMODE_MANUAL = 2
   } SoPlex_SyncModeEnum;

   /// values for parameter READMODE
   typedef enum
   {
      /// standard floating-point parsing
      READMODE_REAL = 0,

      /// rational parsing
      READMODE_RATIONAL = 1
   } SoPlex_ReadModeEnum;

   /// values for parameter SOLVEMODE
   typedef enum
   {
      /// apply standard floating-point algorithm
      SOLVEMODE_REAL = 0,

      /// decide depending on tolerances whether to apply iterative refinement
      SOLVEMODE_AUTO = 1,

      /// force iterative refinement
      SOLVEMODE_RATIONAL = 2
   } SoPlex_SolveModeEnum;

   /// values for parameter CHECKMODE
   typedef enum
   {
      /// floating-point check
      CHECKMODE_REAL = 0,

      /// decide according to READMODE
      CHECKMODE_AUTO = 1,

      /// rational check
      CHECKMODE_RATIONAL = 2
   } SoPlex_CheckModeEnum;

   /// values for parameter TIMER
   enum
   {
      /// disable timing
      TIMER_OFF = 0,

      /// cpu or user time
      TIMER_CPU = 1,

      /// wallclock time
      TIMER_WALLCLOCK = 2
   } SoPlex_TimerEnum;

   /// values for parameter HYPER_PRICING
   typedef enum
   {
      /// never
      HYPER_PRICING_OFF = 0,

      /// decide according to problem size
      HYPER_PRICING_AUTO = 1,

      /// always
      HYPER_PRICING_ON = 2
   } SoPlex_HyperPricingEnum;

   /// values for parameter SOLUTION_POLISHING
   typedef enum
   {
      /// no solution polishing
      POLISHING_OFF = 0,

      /// maximize number of basic slack variables, i.e. more variables on bounds
      POLISHING_INTEGRALITY = 1,

      /// minimize number of basic slack variables, i.e. more variables between bounds
      POLISHING_FRACTIONALITY = 2
   } SoPlex_PolishEnum;

   /// real parameters
   typedef enum
   {
      /// primal feasibility tolerance
      FEASTOL = 0,

      /// dual feasibility tolerance
      OPTTOL = 1,

      /// general zero tolerance
      EPSILON_ZERO = 2,

      /// zero tolerance used in factorization
      EPSILON_FACTORIZATION = 3,

      /// zero tolerance used in update of the factorization
      EPSILON_UPDATE = 4,

      /// pivot zero tolerance used in factorization
      EPSILON_PIVOT = 5,

      /// infinity threshold
      INFTY = 6,

      /// time limit in seconds (INFTY if unlimited)
      TIMELIMIT = 7,

      /// lower limit on objective value
      OBJLIMIT_LOWER = 8,

      /// upper limit on objective value
      OBJLIMIT_UPPER = 9,

      /// working tolerance for feasibility in floating-point solver during iterative refinement
      FPFEASTOL = 10,

      /// working tolerance for optimality in floating-point solver during iterative refinement
      FPOPTTOL = 11,

      /// maximum increase of scaling factors between refinements
      MAXSCALEINCR = 12,

      /// lower threshold in lifting (nonzero matrix coefficients with smaller absolute value will be reformulated)
      LIFTMINVAL = 13,

      /// upper threshold in lifting (nonzero matrix coefficients with larger absolute value will be reformulated)
      LIFTMAXVAL = 14,

      /// sparse pricing threshold (\#violations < dimension * SPARSITY_THRESHOLD activates sparse pricing)
      SPARSITY_THRESHOLD = 15,

      /// threshold on number of rows vs. number of columns for switching from column to row representations in auto mode
      REPRESENTATION_SWITCH = 16,

      /// geometric frequency at which to apply rational reconstruction
      RATREC_FREQ = 17,

      /// minimal reduction (sum of removed rows/cols) to continue simplification
      MINRED = 18,

      /// refactor threshold for nonzeros in last factorized basis matrix compared to updated basis matrix
      REFAC_BASIS_NNZ = 19,

      /// refactor threshold for fill-in in current factor update compared to fill-in in last factorization
      REFAC_UPDATE_FILL = 20,

      /// refactor threshold for memory growth in factorization since last refactorization
      REFAC_MEM_FACTOR = 21,

      /// accuracy of conjugate gradient method in least squares scaling (higher value leads to more iterations)
      LEASTSQ_ACRCY = 22,

      /// objective offset
      OBJ_OFFSET = 23,

      /// minimal Markowitz threshold to control sparsity/stability in LU factorization
      MIN_MARKOWITZ = 24,

      /// minimal modification threshold to apply presolve reductions
      SIMPLIFIER_MODIFYROWFAC = 25,

      /// factor by which the precision of the floating-point solver is multiplied
      PRECISION_BOOSTING_FACTOR = 26,

      /// number of real parameters
      REALPARAM_COUNT = 27
   } SoPlex_RealParamEnum;

#ifdef SOPLEX_WITH_RATIONALPARAM
   /// rational parameters
   typedef enum
   {
      /// number of rational parameters
      RATIONALPARAM_COUNT = 0
   } SoPlex_RationalParamEnum;
#endif


typedef enum 
{
   ON_UPPER,      ///< variable set to its upper bound.
   ON_LOWER,      ///< variable set to its lower bound.
   FIXED,         ///< variable fixed to identical bounds.
   ZERO,          ///< free variable fixed to zero.
   BASIC,         ///< variable is basic.
   UNDEFINED      ///< nothing known about basis status (possibly due to a singular basis in transformed problem)
} SoPlex_VarStatusEnum;


typedef enum 
{
   ERROR          = -15, ///< an error occured.
   NO_RATIOTESTER = -14, ///< No ratiotester loaded
   NO_PRICER      = -13, ///< No pricer loaded
   NO_SOLVER      = -12, ///< No linear solver loaded
   NOT_INIT       = -11, ///< not initialised error
   ABORT_CYCLING  = -8,  ///< solve() aborted due to detection of cycling.
   ABORT_TIME     = -7,  ///< solve() aborted due to time limit.
   ABORT_ITER     = -6,  ///< solve() aborted due to iteration limit.
   ABORT_VALUE    = -5,  ///< solve() aborted due to objective limit.
   SINGULAR       = -4,  ///< Basis is singular, numerical troubles?
   NO_PROBLEM     = -3,  ///< No Problem has been loaded.
   REGULAR        = -2,  ///< LP has a usable Basis (maybe LP is changed).
   RUNNING        = -1,  ///< algorithm is running
   UNKNOWN        =  0,  ///< nothing known on loaded problem.
   OPTIMAL        =  1,  ///< LP has been solved to optimality.
   UNBOUNDED      =  2,  ///< LP has been proven to be primal unbounded.
   INFEASIBLE     =  3,  ///< LP has been proven to be primal infeasible.
   INForUNBD      =  4,   ///< LP is primal infeasible or unbounded.
   OPTIMAL_UNSCALED_VIOLATIONS =  5   ///< LP has beed solved to optimality but unscaled solution contains violations.
} SoPlex_StatusEnum;




#ifdef __cplusplus
}
#endif

#endif /* _SOPLEX_C_ENUMERATIONS_H_ */