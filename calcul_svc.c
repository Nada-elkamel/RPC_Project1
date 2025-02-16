/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "calcul.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <math.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static void
cal_bin_prog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		struct Param puiss_1_arg;
		int dec2bin_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case CALNULL:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_void;
		local = (char *(*)(char *, struct svc_req *)) calnull_1_svc;
		break;

	case PUISS:
		_xdr_argument = (xdrproc_t) xdr_Param;
		_xdr_result = (xdrproc_t) xdr_long;
		local = (char *(*)(char *, struct svc_req *)) puiss_1_svc;
		break;

	case DEC2BIN:
		_xdr_argument = (xdrproc_t) xdr_int;
		_xdr_result = (xdrproc_t) xdr_long;
		local = (char *(*)(char *, struct svc_req *)) dec2bin_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

long int *puiss_1_svc(Param *argp, struct svc_req *rqstp) {
    static long int result;
    result = pow(argp->base, argp->exposant);
    return &result;
}

long int *dec2bin_1_svc(int *n, struct svc_req *rqstp) {
    static long int result = 0;
    int num = *n, place = 1;
    while (num > 0) {
        result += (num % 2) * place;
        num /= 2;
        place *= 10;
    }
    return &result;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (CAL_BIN_PROG, CAL_VERS_ONE);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, CAL_BIN_PROG, CAL_VERS_ONE, cal_bin_prog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (CAL_BIN_PROG, CAL_VERS_ONE, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, CAL_BIN_PROG, CAL_VERS_ONE, cal_bin_prog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (CAL_BIN_PROG, CAL_VERS_ONE, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
