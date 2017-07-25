/** @file class.c 
 * Julien Lesgourgues, 17.04.2011    
 */
 
#include "class.h"

/* this main runs only the background part */

int main(int argc, char **argv) {

  struct precision pr;        /* for precision parameters */
  struct background ba;       /* for cosmological background */
  struct thermo th;           /* for thermodynamics */
  struct perturbs pt;         /* for source functions */
  struct transfers tr;        /* for transfer functions */
  struct primordial pm;       /* for primordial spectra */
  struct spectra sp;          /* for output spectra */
  struct nonlinear nl;        /* for non-linear spectra */
  struct lensing le;          /* for lensed spectra */
  struct output op;           /* for output files */
  ErrorMsg errmsg;            /* for error messages */

  if (input_init_from_arguments(argc, argv,&pr,&ba,&th,&pt,&tr,&pm,&sp,&nl,&le,&op,errmsg) == _FAILURE_) {
    printf("\n\nError running input_init_from_arguments \n=>%s\n",errmsg); 
    return _FAILURE_;
  }

  if (background_init(&pr,&ba) == _FAILURE_) {
    printf("\n\nError running background_init \n=>%s\n",ba.error_message);
    return _FAILURE_;
  }

  /****** here you can output the evolution of any background
	  quanitity you are interested in ******/

  int index_tau;

  for (index_tau=0; index_tau<ba.bt_size; index_tau++) {

    fprintf(stdout,
	   // "tau=%e z=%e a=%e H=%e Omega_phi=%e\n",
        "%e %e %e\n",
//	    ba.tau_table[index_tau],
//	    ba.z_table[index_tau],
	    ba.background_table[index_tau*ba.bg_size+ba.index_bg_a],
//	    ba.background_table[index_tau*ba.bg_size+ba.index_bg_H],
        ba.background_table[index_tau*ba.bg_size+ba.index_bg_Omega_phi_scf],
        ba.background_table[index_tau*ba.bg_size+ba.index_bg_theta_phi_scf]);

  }

  /****** all calculations done, now free the structures ******/

  if (background_free(&ba) == _FAILURE_) {
    printf("\n\nError in background_free \n=>%s\n",ba.error_message);
    return _FAILURE_;
  }

  return _SUCCESS_;

}