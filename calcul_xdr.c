/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "calcul.h"

bool_t
xdr_Param (XDR *xdrs, Param *objp)
{
	register int32_t *buf;

	 if (!xdr_long (xdrs, &objp->base))
		 return FALSE;
	 if (!xdr_long (xdrs, &objp->exponent))
		 return FALSE;
	return TRUE;
}
