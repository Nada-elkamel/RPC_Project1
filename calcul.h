/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _CALCUL_H_RPCGEN
#define _CALCUL_H_RPCGEN

#include <tirpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct Param {
	long base;
	long exponent;
};
typedef struct Param Param;

#define CAL_BIN_PROG 0x20000001
#define CAL_VERS_ONE 1

#if defined(__STDC__) || defined(__cplusplus)
#define CALNULL 0
extern  void * calnull_1(void *, CLIENT *);
extern  void * calnull_1_svc(void *, struct svc_req *);
#define PUISS 1
extern  long * puiss_1(struct Param *, CLIENT *);
extern  long * puiss_1_svc(struct Param *, struct svc_req *);
#define DEC2BIN 2
extern  long * dec2bin_1(int *, CLIENT *);
extern  long * dec2bin_1_svc(int *, struct svc_req *);
extern int cal_bin_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define CALNULL 0
extern  void * calnull_1();
extern  void * calnull_1_svc();
#define PUISS 1
extern  long * puiss_1();
extern  long * puiss_1_svc();
#define DEC2BIN 2
extern  long * dec2bin_1();
extern  long * dec2bin_1_svc();
extern int cal_bin_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_Param (XDR *, Param*);

#else /* K&R C */
extern bool_t xdr_Param ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_CALCUL_H_RPCGEN */
