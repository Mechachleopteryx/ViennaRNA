#ifndef __VIENNA_RNA_PACKAGE_DATA_STRUCTURES_H__
#define __VIENNA_RNA_PACKAGE_DATA_STRUCTURES_H__

#include <ViennaRNA/energy_const.h>
#include <ViennaRNA/model.h>


/**
 *  \file data_structures.h
 *  \brief All datastructures and typedefs shared among the Vienna RNA Package can be found here
 */

/* to use floats instead of doubles in pf_fold() comment next line */
#define LARGE_PF
#ifdef  LARGE_PF
#define FLT_OR_DBL double
#else
#define FLT_OR_DBL float
#endif

#ifndef NBASES
#define NBASES 8
#endif

/**
 *  \brief Maximum density of states discretization for subopt
 */
#define MAXDOS                1000

#define   VRNA_GQUAD_MAX_STACK_SIZE     7
#define   VRNA_GQUAD_MIN_STACK_SIZE     2
#define   VRNA_GQUAD_MAX_LINKER_LENGTH  15
#define   VRNA_GQUAD_MIN_LINKER_LENGTH  1
#define   VRNA_GQUAD_MIN_BOX_SIZE       ((4*VRNA_GQUAD_MIN_STACK_SIZE)+(3*VRNA_GQUAD_MIN_LINKER_LENGTH))
#define   VRNA_GQUAD_MAX_BOX_SIZE       ((4*VRNA_GQUAD_MAX_STACK_SIZE)+(3*VRNA_GQUAD_MAX_LINKER_LENGTH))


/**
 *  \brief fold_compound_type Single Sequence
 */
#define   VRNA_VC_TYPE_SINGLE     1

/**
 *  \brief fold_compound_type Sequence Alignment
 */
#define   VRNA_VC_TYPE_ALIGNMENT  2


/* the definitions below indicate which arrays should be allocated upon retrieval of a matrices data structure */
#define ALLOC_NOTHING     0
#define ALLOC_F           1
#define ALLOC_F5          2
#define ALLOC_F3          4
#define ALLOC_FC          8
#define ALLOC_C           16
#define ALLOC_FML         32
#define ALLOC_PROBS       256
#define ALLOC_AUX         512

#define ALLOC_CIRC        1024
#define ALLOC_HYBRID      2048
#define ALLOC_UNIQ        4096


#define ALLOC_MFE_DEFAULT         (ALLOC_F5 | ALLOC_C | ALLOC_FML)

#define ALLOC_PF_WO_PROBS         (ALLOC_F | ALLOC_C | ALLOC_FML)
#define ALLOC_PF_DEFAULT          (ALLOC_PF_WO_PROBS | ALLOC_PROBS | ALLOC_AUX)


/* the definitions below should be used for functions the return/receive/destroy fold compound data structures */

#define VRNA_OPTION_MFE       1

#define VRNA_OPTION_PF        2

#define VRNA_OPTION_HYBRID    4






/*
* ############################################################
* Here are the type definitions of various datastructures
* shared among the Vienna RNA Package
* ############################################################
*/

/**
 *  \brief this datastructure is used as input parameter in functions of PS_dot.h and others
 */
typedef struct plist {
  int i;
  int j;
  float p;
  int type;
} plist;

/**
 *  \brief this datastructure is used as input parameter in functions of PS_dot.c
 */
typedef struct cpair {
  int i,j,mfe;
  float p, hue, sat;
} cpair;

/**
 *  \brief this is a workarround for the SWIG Perl Wrapper RNA plot function
 *  that returns an array of type COORDINATE
 */
typedef struct {
  float X; /* X coords */
  float Y; /* Y coords */
} COORDINATE;

/**
 *  \brief  Stack of partial structures for backtracking
 */
typedef struct sect {
  int  i;
  int  j;
  int ml;
} sect;

/**
 *  \brief  Base pair
 */
typedef struct bondT {
   unsigned int i;
   unsigned int j;
} bondT;

/**
 *  \brief  Base pair with associated energy
 */
typedef struct bondTEn {
   int i;
   int j;
   int energy;
} bondTEn;


typedef struct{
  unsigned int allocated; /* flag keeper for fast evaluation which matrices have been allocated */
  unsigned int length;
  int     *c;   /* energy array, given that i-j pair */
  int     *f5;  /* energy of 5' end */
  int     *f3;  /* energy of 3' end */
  int     *fc;  /* energy from i to cutpoint (and vice versa if i>cut) */
  int     *fML; /* multi-loop auxiliary energy array */
  int     *fM1; /* second ML array, only for subopt */
  int     *fM2; /* fM2 = multiloop region with exactly two stems, extending to 3' end */
  int     *ggg; /* energies of g-quadruplexes */
  int     Fc;   /* parts of the exterior loop energies for circfolding */
  int     FcH;
  int     FcI;
  int     FcM;
} mfe_matricesT;

typedef struct{
  unsigned int allocated;
  unsigned int length;
  FLT_OR_DBL  *q;
  FLT_OR_DBL  *qb;
  FLT_OR_DBL  *qm;
  FLT_OR_DBL  *qm1;
  FLT_OR_DBL  *probs;
  FLT_OR_DBL  *q1k;
  FLT_OR_DBL  *qln;
  FLT_OR_DBL  *G;

  FLT_OR_DBL  qo;
  FLT_OR_DBL  *qm2;
  FLT_OR_DBL  qho;
  FLT_OR_DBL  qio;
  FLT_OR_DBL  qmo;

  FLT_OR_DBL  *scale;
  FLT_OR_DBL  *expMLbase;
} pf_matricesT;


/**
 *  \brief The datastructure that contains temperature scaled energy parameters.
 */
typedef struct{
  int id;
  int stack[NBPAIRS+1][NBPAIRS+1];
  int hairpin[31];
  int bulge[MAXLOOP+1];
  int internal_loop[MAXLOOP+1];
  int mismatchExt[NBPAIRS+1][5][5];
  int mismatchI[NBPAIRS+1][5][5];
  int mismatch1nI[NBPAIRS+1][5][5];
  int mismatch23I[NBPAIRS+1][5][5];
  int mismatchH[NBPAIRS+1][5][5];
  int mismatchM[NBPAIRS+1][5][5];
  int dangle5[NBPAIRS+1][5];
  int dangle3[NBPAIRS+1][5];
  int int11[NBPAIRS+1][NBPAIRS+1][5][5];
  int int21[NBPAIRS+1][NBPAIRS+1][5][5][5];
  int int22[NBPAIRS+1][NBPAIRS+1][5][5][5][5];
  int ninio[5];
  double  lxc;
  int     MLbase;
  int     MLintern[NBPAIRS+1];
  int     MLclosing;
  int     TerminalAU;
  int     DuplexInit;
  int     Tetraloop_E[200];
  char    Tetraloops[1401];
  int     Triloop_E[40];
  char    Triloops[241];
  int     Hexaloop_E[40];
  char    Hexaloops[1801];
  int     TripleC;
  int     MultipleCA;
  int     MultipleCB;
  int     gquad [VRNA_GQUAD_MAX_STACK_SIZE + 1]
                [3*VRNA_GQUAD_MAX_LINKER_LENGTH + 1];

  double  temperature;            /**<  \brief  Temperature used for loop contribution scaling */

  model_detailsT model_details;   /**<  \brief  Model details to be used in the recursions */

}  paramT;

/**
 *  \brief  The datastructure that contains temperature scaled Boltzmann weights of the energy parameters.
 */
typedef struct{
  int     id;
  double  expstack[NBPAIRS+1][NBPAIRS+1];
  double  exphairpin[31];
  double  expbulge[MAXLOOP+1];
  double  expinternal[MAXLOOP+1];
  double  expmismatchExt[NBPAIRS+1][5][5];
  double  expmismatchI[NBPAIRS+1][5][5];
  double  expmismatch23I[NBPAIRS+1][5][5];
  double  expmismatch1nI[NBPAIRS+1][5][5];
  double  expmismatchH[NBPAIRS+1][5][5];
  double  expmismatchM[NBPAIRS+1][5][5];
  double  expdangle5[NBPAIRS+1][5];
  double  expdangle3[NBPAIRS+1][5];
  double  expint11[NBPAIRS+1][NBPAIRS+1][5][5];
  double  expint21[NBPAIRS+1][NBPAIRS+1][5][5][5];
  double  expint22[NBPAIRS+1][NBPAIRS+1][5][5][5][5];
  double  expninio[5][MAXLOOP+1];
  double  lxc;
  double  expMLbase;
  double  expMLintern[NBPAIRS+1];
  double  expMLclosing;
  double  expTermAU;
  double  expDuplexInit;
  double  exptetra[40];
  double  exptri[40];
  double  exphex[40];
  char    Tetraloops[1401];
  double  expTriloop[40];
  char    Triloops[241];
  char    Hexaloops[1801];
  double  expTripleC;
  double  expMultipleCA;
  double  expMultipleCB;
  double  expgquad[VRNA_GQUAD_MAX_STACK_SIZE + 1]
                  [3*VRNA_GQUAD_MAX_LINKER_LENGTH + 1];

  double  kT;
  double  pf_scale;     /**<  \brief    Scaling factor to avoid over-/underflows */

  double  temperature;  /**<  \brief    Temperature used for loop contribution scaling */
  double  alpha;        /**<  \brief    Scaling factor for the thermodynamic temperature
                              \details  This allows for temperature scaling in Boltzmann
                                        factors independently from the energy contributions.
                                        The resulting Boltzmann factors are then computed by
                                        \f$ e^{-E/(\alpha \cdot K \cdot T)} \f$
                        */

  model_detailsT model_details; /**<  \brief  Model details to be used in the recursions */

}  pf_paramT;

/**
 *  \brief  The hard constraints data structure
 *
 *  The content of this data structure determines the decomposition pattern
 *  used in the folding recursions. Attribute 'matrix' is used as source for
 *  the branching pattern of the decompositions during all folding recursions.
 *  Any entry in matrix[i,j] consists of the 6 LSB that allows to distinguish the
 *  following types of base pairs:
 *  - in the exterior loop (#IN_EXT_LOOP)
 *  - enclosing a hairpin (#IN_HP_LOOP)
 *  - enclosing an interior loop (#IN_INT_LOOP)
 *  - enclosed by an exterior loop (#IN_INT_LOOP_ENC)
 *  - enclosing a multi branch loop (#IN_MB_LOOP)
 *  - enclosed by a multi branch loop (#IN_MB_LOOP_ENC)
 *
 *  The four linear arrays 'up_xxx' provide the number of available unpaired
 *  nucleotides (including position i) 3' of each position in the sequence.
 *
 *  \see  get_hard_constraints(), destroy_hard_constraints(), #IN_EXT_LOOP,
 *        #IN_HP_LOOP, #IN_INT_LOOP, #IN_EXT_LOOP_ENC, #IN_MB_LOOP, #IN_MB_LOOP_ENC
 *        
 *  \ingroup hard_constraints
 */
typedef struct {
  char    *matrix;  /**<  \brief  Upper triangular matrix encoding where a
                                  base pair or unpaired nucleotide is allowed
                    */
  int     *up_ext;  /**<  \brief  A linear array that holds the number of allowed
                                  unpaired nucleotides in an exterior loop
                    */
  int     *up_hp;   /**<  \brief  A linear array that holds the number of allowed
                                  unpaired nucleotides in a hairpin loop
                    */
  int     *up_int;  /**<  \brief  A linear array that holds the number of allowed
                                  unpaired nucleotides in an interior loop
                    */
  int     *up_ml;   /**<  \brief  A linear array that holds the number of allowed
                                  unpaired nucleotides in a multi branched loop
                    */
} hard_constraintT;

/**
 *  \brief  The soft constraints data structure
 *
 *  \ingroup soft_constraints
 */
typedef struct {
  double      *constraints;         /**<  \brief Backup storage for energy contributions of single nucleotides */
  int         **free_energies;      /**<  \brief Energy contribution for unpaired sequence stretches */
  int         *en_basepair;         /**<  \brief Energy contribution for base pairs */
  FLT_OR_DBL  **boltzmann_factors;  /**<  \brief Boltzmann Factors of the energy contributions for unpaired sequence stretches */
  FLT_OR_DBL  *exp_en_basepair;     /**<  \brief Boltzmann Factors of the energy contribution for base pairs */

  int         *en_stack;            /**<  \brief Pseudo Energy contribution per base pair involved in a stack */
  FLT_OR_DBL  *exp_en_stack;        /**<  \brief Boltzmann weighted pseudo energy contribution per nucleotide involved in a stack */

  /* generalized soft contraints */
  int (*f)( int,
            int,
            int,
            int,
            char,
            void *);            /**<  \brief  A function pointer used for pseudo
                                              energy contribution in MFE calculations
                                */

  FLT_OR_DBL (*exp_f)(int,
                      int,
                      int,
                      int,
                      char,
                      void *);  /**<  \brief  A function pointer used for pseudo energy
                                              contribution boltzmann factors in PF
                                              calculations
                                */

  void *data;                   /**<  \brief  A pointer to the data object necessary for
                                              for pseudo energy contribution functions
                                */
} soft_constraintT;


typedef struct{

  unsigned int  type;            /**<  \brief The type of the fold_compound */
  unsigned int  length;
  int           cutpoint;               /**<  \brief  The position of the (cofold) cutpoint within the provided sequence.
                                      If there is no cutpoint, this field will be set to -1
                                */
  union {
    struct {
      char  *sequence;
      short *sequence_encoding;
      short *sequence_encoding2;
      char  *ptype;                 /**<  \brief Pair type array
                                     
                                          Contains the numerical encoding of the pair type for each pair (i,j) used
                                          in MFE, Partition function and Evaluation computations.
                                          \note This array is always indexed via jindx, in contrast to previously
                                          different indexing between mfe and pf variants!
                                          \see  get_indx(), vrna_get_ptypes()
                                    */
      char  *ptype_pf_compat;       /**<  \brief  ptype array indexed via iindx
                                          \deprecated  This attribute will vanish in the future!
                                          It's meant for backward compatibility only!
                                    */
      soft_constraintT  *sc;
    };
    struct {
      char  **sequences;
      unsigned int    n_seq;
      char            *cons_seq;
      short           *S_cons;
      short           **S;
      short           **S5;     /*S5[s][i] holds next base 5' of i in sequence s*/
      short           **S3;     /*Sl[s][i] holds next base 3' of i in sequence s*/
      char            **Ss;
      unsigned short  **a2s;
      int               *pscore;     /* precomputed array of pair types */
      soft_constraintT  **scs;
      int               oldAliEn;
    };
  };

  hard_constraintT  *hc;

  mfe_matricesT     *matrices;
  pf_matricesT      *exp_matrices;

  paramT            *params;
  pf_paramT         *exp_params;

  int               *iindx;
  int               *jindx;

} vrna_fold_compound;


/*
* ############################################################
* SUBOPT data structures
* ############################################################
*/


/**
 *  \brief  Base pair data structure used in subopt.c
 */
typedef struct {
  int i;
  int j;
} PAIR;

/**
 *  \brief  Sequence interval stack element used in subopt.c
 */
typedef struct {
    int i;
    int j;
    int array_flag;
} INTERVAL;

/**
 *  \brief  Solution element from subopt.c
 */
typedef struct {
  float energy;       /**< \brief Free Energy of structure in kcal/mol */
  char *structure;    /**< \brief Structure in dot-bracket notation */
} SOLUTION;

/*
* ############################################################
* COFOLD data structures
* ############################################################
*/

/**
 *  \brief
 */
typedef struct cofoldF {
  /* free energies for: */
  double F0AB;  /**< \brief Null model without DuplexInit */
  double FAB;   /**< \brief all states with DuplexInit correction */
  double FcAB;  /**< \brief true hybrid states only */
  double FA;    /**< \brief monomer A */
  double FB;    /**< \brief monomer B */
} cofoldF;

/**
 *  \brief
 */
typedef struct ConcEnt {
  double A0;    /**< \brief start concentration A */
  double B0;    /**< \brief start concentration B */
  double ABc;   /**< \brief End concentration AB */
  double AAc;
  double BBc;
  double Ac;
  double Bc;
} ConcEnt;

/**
 *  \brief
 */
typedef struct pairpro{
  struct plist *AB;
  struct plist *AA;
  struct plist *A;
  struct plist *B;
  struct plist *BB;
}pairpro;

/**
 *  \brief A base pair info structure
 *
 *  For each base pair (i,j) with i,j in [0, n-1] the structure lists:
 *  - its probability 'p'
 *  - an entropy-like measure for its well-definedness 'ent'
 *  - the frequency of each type of pair in 'bp[]'
 *    + 'bp[0]' contains the number of non-compatible sequences
 *    + 'bp[1]' the number of CG pairs, etc.
 */
typedef struct {
   unsigned i;    /**<  \brief  nucleotide position i */
   unsigned j;    /**<  \brief  nucleotide position j */
   float p;       /**< \brief  Probability */
   float ent;     /**< \brief  Pseudo entropy for \f$ p(i,j) = S_i + S_j - p_ij*ln(p_ij) \f$ */
   short bp[8];   /**< \brief  Frequencies of pair_types */
   char comp;     /**< \brief  1 iff pair is in mfe structure */
} pair_info;


/*
* ############################################################
* FINDPATH data structures
* ############################################################
*/

/**
 *  \brief
 */
typedef struct move {
  int i;  /* i,j>0 insert; i,j<0 delete */
  int j;
  int when;  /* 0 if still available, else resulting distance from start */
  int E;
} move_t;

/**
 *  \brief
 */
typedef struct intermediate {
  short *pt;      /**<  \brief  pair table */
  int Sen;        /**<  \brief  saddle energy so far */
  int curr_en;    /**<  \brief  current energy */
  move_t *moves;  /**<  \brief  remaining moves to target */
} intermediate_t;

/**
 *  \brief
 */
typedef struct path {
  double en;
  char *s;
} path_t;

/*
* ############################################################
* RNAup data structures
* ############################################################
*/

/**
 *  \brief contributions to p_u
 */
typedef struct pu_contrib {
  double **H; /**<  \brief  hairpin loops */
  double **I; /**<  \brief  interior loops */
  double **M; /**<  \brief  multi loops */
  double **E; /**<  \brief  exterior loop */
  int length; /**<  \brief  length of the input sequence */
  int w;      /**<  \brief  longest unpaired region */
} pu_contrib;

/**
 *  \brief
 */
typedef struct interact {
  double *Pi;       /**<  \brief  probabilities of interaction */
  double *Gi;       /**<  \brief  free energies of interaction */
  double Gikjl;     /**<  \brief  full free energy for interaction between [k,i] k<i
                                  in longer seq and [j,l] j<l in shorter seq */
  double Gikjl_wo;  /**<  \brief  Gikjl without contributions for prob_unpaired */
  int i;            /**<  \brief  k<i in longer seq */
  int k;            /**<  \brief  k<i in longer seq */
  int j;            /**<  \brief  j<l in shorter seq */
  int l;            /**<  \brief  j<l in shorter seq */
  int length;       /**<  \brief  length of longer sequence */
} interact;

/**
 *  \brief  Collection of all free_energy of beeing unpaired values for output
 */
typedef struct pu_out {
  int len;            /**<  \brief  sequence length */
  int u_vals;         /**<  \brief  number of different -u values */
  int contribs;       /**<  \brief  [-c "SHIME"] */
  char **header;      /**<  \brief  header line */
  double **u_values;  /**<  \brief  (the -u values * [-c "SHIME"]) * seq len */
} pu_out;

/**
 *  \brief  constraints for cofolding
 */
typedef struct constrain{
  int *indx;
  char *ptype;
} constrain;

/*
* ############################################################
* RNAduplex data structures
* ############################################################
*/

/**
 *  \brief
 */
typedef struct {
  int i;
  int j;
  int end;
  char *structure;
  double energy;
  double energy_backtrack;
  double opening_backtrack_x;
  double opening_backtrack_y;
  int offset;
  double dG1;
  double dG2;
  double ddG;
  int tb;
  int te;
  int qb;
  int qe;
} duplexT;

/*
* ############################################################
* RNAsnoop data structures
* ############################################################
*/

/**
 *  \brief
 */
typedef struct node {
  int k;
  int energy;
  struct node *next;
} folden;

/**
 *  \brief
 */
typedef struct {
  int i;
  int j;
  int u;
  char *structure;
  float energy;
  float Duplex_El;
  float Duplex_Er;
  float Loop_E;
  float Loop_D;
  float pscd;
  float psct;
  float pscg;
  float Duplex_Ol;
  float Duplex_Or;
  float Duplex_Ot;
  float fullStemEnergy;
} snoopT;







/*
* ############################################################
* PKplex data structures
* ############################################################
*/

/**
 *  \brief
 */
typedef struct dupVar{
  int i;
  int j;
  int end;
  char *pk_helix;
  char *structure;
  double energy;
  int offset;
  double dG1;
  double dG2;
  double ddG;
  int tb;
  int te;
  int qb;
  int qe;
  int inactive;
  int processed;
} dupVar;



/*
* ############################################################
* 2Dfold data structures
* ############################################################
*/

/**
 *  \brief Solution element returned from TwoDfoldList
 *
 *  This element contains free energy and structure for the appropriate
 *  kappa (k), lambda (l) neighborhood
 *  The datastructure contains two integer attributes 'k' and 'l'
 *  as well as an attribute 'en' of type float representing the free energy
 *  in kcal/mol and an attribute 's' of type char* containg the secondary
 *  structure representative,
 *
 *  A value of #INF in k denotes the end of a list
 *
 *  \see  TwoDfoldList()
 */
typedef struct{
  int k;          /**<  \brief  Distance to first reference */
  int l;          /**<  \brief  Distance to second reference */
  float en;       /**<  \brief  Free energy in kcal/mol */
  char *s;        /**<  \brief  MFE representative structure in dot-bracket notation */
} TwoDfold_solution;

/**
 *  \brief Variables compound for 2Dfold MFE folding
 *
 *  \see get_TwoDfold_variables(), destroy_TwoDfold_variables(), TwoDfoldList()
 */
typedef struct{
  paramT          *P;             /**<  \brief  Precomputed energy parameters and model details */
  int             do_backtrack;   /**<  \brief  Flag whether to do backtracing of the structure(s) or not */
  char            *ptype;         /**<  \brief  Precomputed array of pair types */
  char            *sequence;      /**<  \brief  The input sequence  */
  short           *S, *S1;        /**<  \brief  The input sequences in numeric form */
  unsigned int    maxD1;          /**<  \brief  Maximum allowed base pair distance to first reference */
  unsigned int    maxD2;          /**<  \brief  Maximum allowed base pair distance to second reference */


  unsigned int    *mm1;           /**<  \brief  Maximum matching matrix, reference struct 1 disallowed */
  unsigned int    *mm2;           /**<  \brief  Maximum matching matrix, reference struct 2 disallowed */

  int             *my_iindx;      /**<  \brief  Index for moving in quadratic distancy dimensions */

  double          temperature;

  unsigned int    *referenceBPs1; /**<  \brief  Matrix containing number of basepairs of reference structure1 in interval [i,j] */
  unsigned int    *referenceBPs2; /**<  \brief  Matrix containing number of basepairs of reference structure2 in interval [i,j] */
  unsigned int    *bpdist;        /**<  \brief  Matrix containing base pair distance of reference structure 1 and 2 on interval [i,j] */

  short           *reference_pt1;
  short           *reference_pt2;
  int             circ;
  int             dangles;
  unsigned int    seq_length;

  int             ***E_F5;
  int             ***E_F3;
  int             ***E_C;
  int             ***E_M;
  int             ***E_M1;
  int             ***E_M2;

  int             **E_Fc;
  int             **E_FcH;
  int             **E_FcI;
  int             **E_FcM;

  int             **l_min_values;
  int             **l_max_values;
  int             *k_min_values;
  int             *k_max_values;

  int             **l_min_values_m;
  int             **l_max_values_m;
  int             *k_min_values_m;
  int             *k_max_values_m;

  int             **l_min_values_m1;
  int             **l_max_values_m1;
  int             *k_min_values_m1;
  int             *k_max_values_m1;

  int             **l_min_values_f;
  int             **l_max_values_f;
  int             *k_min_values_f;
  int             *k_max_values_f;

  int             **l_min_values_f3;
  int             **l_max_values_f3;
  int             *k_min_values_f3;
  int             *k_max_values_f3;

  int             **l_min_values_m2;
  int             **l_max_values_m2;
  int             *k_min_values_m2;
  int             *k_max_values_m2;

  int             *l_min_values_fc;
  int             *l_max_values_fc;
  int             k_min_values_fc;
  int             k_max_values_fc;

  int             *l_min_values_fcH;
  int             *l_max_values_fcH;
  int             k_min_values_fcH;
  int             k_max_values_fcH;

  int             *l_min_values_fcI;
  int             *l_max_values_fcI;
  int             k_min_values_fcI;
  int             k_max_values_fcI;

  int             *l_min_values_fcM;
  int             *l_max_values_fcM;
  int             k_min_values_fcM;
  int             k_max_values_fcM;

  /* auxilary arrays for remaining set of coarse graining (k,l) > (k_max, l_max) */
  int             *E_F5_rem;
  int             *E_F3_rem;
  int             *E_C_rem;
  int             *E_M_rem;
  int             *E_M1_rem;
  int             *E_M2_rem;

  int             E_Fc_rem;
  int             E_FcH_rem;
  int             E_FcI_rem;
  int             E_FcM_rem;

#ifdef COUNT_STATES
  unsigned long             ***N_F5;
  unsigned long             ***N_C;
  unsigned long             ***N_M;
  unsigned long             ***N_M1;
#endif
} TwoDfold_vars;

/**
 *  \brief Solution element returned from TwoDpfoldList
 *
 *  This element contains the partition function for the appropriate
 *  kappa (k), lambda (l) neighborhood
 *  The datastructure contains two integer attributes 'k' and 'l'
 *  as well as an attribute 'q' of type #FLT_OR_DBL
 *
 *  A value of #INF in k denotes the end of a list
 *
 *  \see  TwoDpfoldList()
 */
typedef struct{
  int k;          /**<  \brief  Distance to first reference */
  int l;          /**<  \brief  Distance to second reference */
  FLT_OR_DBL  q;  /**<  \brief  partition function */
} TwoDpfold_solution;

/**
 *  \brief  Variables compound for 2Dfold partition function folding
 *
 *  \see    get_TwoDpfold_variables(), get_TwoDpfold_variables_from_MFE(),
 *          destroy_TwoDpfold_variables(), TwoDpfoldList()
 */
typedef struct{

  unsigned int    alloc;
  char            *ptype;         /**<  \brief  Precomputed array of pair types */
  char            *sequence;      /**<  \brief  The input sequence  */
  short           *S, *S1;        /**<  \brief  The input sequences in numeric form */
  unsigned int    maxD1;          /**<  \brief  Maximum allowed base pair distance to first reference */
  unsigned int    maxD2;          /**<  \brief  Maximum allowed base pair distance to second reference */

  double          temperature;    /* temperature in last call to scale_pf_params */
  double          init_temp;      /* temperature in last call to scale_pf_params */
  FLT_OR_DBL      *scale;
  FLT_OR_DBL      pf_scale;
  pf_paramT       *pf_params;     /* holds all [unscaled] pf parameters */

  int             *my_iindx;      /**<  \brief  Index for moving in quadratic distancy dimensions */
  int             *jindx;         /**<  \brief  Index for moving in the triangular matrix qm1 */

  short           *reference_pt1;
  short           *reference_pt2;

  unsigned int    *referenceBPs1; /**<  \brief  Matrix containing number of basepairs of reference structure1 in interval [i,j] */
  unsigned int    *referenceBPs2; /**<  \brief  Matrix containing number of basepairs of reference structure2 in interval [i,j] */
  unsigned int    *bpdist;        /**<  \brief  Matrix containing base pair distance of reference structure 1 and 2 on interval [i,j] */

  unsigned int    *mm1;           /**<  \brief  Maximum matching matrix, reference struct 1 disallowed */
  unsigned int    *mm2;           /**<  \brief  Maximum matching matrix, reference struct 2 disallowed */

  int             circ;
  int             dangles;
  unsigned int    seq_length;

  FLT_OR_DBL      ***Q;
  FLT_OR_DBL      ***Q_B;
  FLT_OR_DBL      ***Q_M;
  FLT_OR_DBL      ***Q_M1;
  FLT_OR_DBL      ***Q_M2;

  FLT_OR_DBL      **Q_c;
  FLT_OR_DBL      **Q_cH;
  FLT_OR_DBL      **Q_cI;
  FLT_OR_DBL      **Q_cM;

  int             **l_min_values;
  int             **l_max_values;
  int             *k_min_values;
  int             *k_max_values;

  int             **l_min_values_b;
  int             **l_max_values_b;
  int             *k_min_values_b;
  int             *k_max_values_b;

  int             **l_min_values_m;
  int             **l_max_values_m;
  int             *k_min_values_m;
  int             *k_max_values_m;

  int             **l_min_values_m1;
  int             **l_max_values_m1;
  int             *k_min_values_m1;
  int             *k_max_values_m1;

  int             **l_min_values_m2;
  int             **l_max_values_m2;
  int             *k_min_values_m2;
  int             *k_max_values_m2;

  int             *l_min_values_qc;
  int             *l_max_values_qc;
  int             k_min_values_qc;
  int             k_max_values_qc;

  int             *l_min_values_qcH;
  int             *l_max_values_qcH;
  int             k_min_values_qcH;
  int             k_max_values_qcH;

  int             *l_min_values_qcI;
  int             *l_max_values_qcI;
  int             k_min_values_qcI;
  int             k_max_values_qcI;

  int             *l_min_values_qcM;
  int             *l_max_values_qcM;
  int             k_min_values_qcM;
  int             k_max_values_qcM;

  /* auxilary arrays for remaining set of coarse graining (k,l) > (k_max, l_max) */
  FLT_OR_DBL      *Q_rem;
  FLT_OR_DBL      *Q_B_rem;
  FLT_OR_DBL      *Q_M_rem;
  FLT_OR_DBL      *Q_M1_rem;
  FLT_OR_DBL      *Q_M2_rem;

  FLT_OR_DBL      Q_c_rem;
  FLT_OR_DBL      Q_cH_rem;
  FLT_OR_DBL      Q_cI_rem;
  FLT_OR_DBL      Q_cM_rem;

} TwoDpfold_vars;


/*
* ############################################################
* Useful functions to retrieve/destroy data structures
* ############################################################
*/

mfe_matricesT *get_mfe_matrices_alloc( unsigned int n,
                                       unsigned int alloc_vector);

void destroy_mfe_matrices(mfe_matricesT *self);

pf_matricesT  *get_pf_matrices_alloc(unsigned int n,
                                    unsigned int alloc_vector);

void destroy_pf_matrices(pf_matricesT *self);

/*
* ############################################################
* VRNA fold compound related functions
* ############################################################
*/

/* General stuff */

vrna_fold_compound *vrna_get_fold_compound( const char *sequence,
                                            model_detailsT *md_p,
                                            unsigned int options);

vrna_fold_compound *vrna_get_fold_compound_ali( const char **sequence,
                                                model_detailsT *md_p,
                                                unsigned int options);

void destroy_fold_compound(vrna_fold_compound *vc);


/* partition function stuff */

#endif